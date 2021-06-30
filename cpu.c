#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "common.h"
#include "cpu.h"
#include "instruction.h"
#include "pipeline.h"

/// Initialize CPU memory with heap allocation.
/// And initialize CPU registers with 0
int initialize_cpu(CPU* const cpu) {
  if(cpu == NULL) {
    return 1;
  }

  if((cpu->memory = (Word*)malloc(sizeof(Word) * MEMORY_SIZE)) == NULL) {
    return 2;
  }

  Register init_reg;
  init_reg.raw = 0;
  for(int i = 0;i < REGISTER_SIZE;i++) {
    init_reg.raw = i;
    cpu->register_file[i] = init_reg;
  }

  cpu->pc = 0;
  cpu->down = 0;

  cpu->if_id_register.inst.raw = 0;

  cpu->id_ex_register.opecode = I_NOP;
  cpu->id_ex_register.func = 0;
  cpu->id_ex_register.dest_reg = 0;
  cpu->id_ex_register.reg1 = 0;
  cpu->id_ex_register.reg2 = 0;
  cpu->id_ex_register.immediate = 0;

  cpu->ex_mem_register.opecode = I_NOP;
  cpu->ex_mem_register.dest_reg = 0;
  cpu->ex_mem_register.address = 0;
  cpu->ex_mem_register.result = 0;
  cpu->ex_mem_register.enable_forwarding = 0;
  
  cpu->mem_wb_register.opecode = I_NOP;
  cpu->mem_wb_register.result = 0;
  cpu->mem_wb_register.dest_reg = 0;
  cpu->mem_wb_register.enable_forwarding = 0;

  return 0;
}

int initialize_memory_and_check(const CPU* const cpu) {
  if(cpu == NULL) {
    return 1;
  }

  if(cpu->memory == NULL) {
    return 2;
  }

  cpu->memory[0].raw = 0xdeadbeefcafebabe;
  cpu->memory[MEMORY_SIZE - 1].raw = 0xBAAAAAAAAAADC0DE;
  if(cpu->memory[0].raw != 0xdeadbeefcafebabe) {
    return 3;
  }
  if(cpu->memory[MEMORY_SIZE - 1].raw != 0xBAAAAAAAAAADC0DE) {
    return 3;
  }

  Word word;
  word.raw = 0;
  for(int i = 0;i < MEMORY_SIZE;i++) {
    cpu->memory[i] = word;
  }

  return 0;
}

Word* access_memory(CPU* const cpu, const uint64_t addr) {
  if(addr < 0 || MEMORY_SIZE <= addr) {
    die_with_error("Access to out of memory. addr = 0x%lx", addr);
  }
  return (Word*)&((char*)cpu->memory)[addr];
}

Register* access_register(CPU* const cpu, const uint64_t index) {
  if(index < 0 || REGISTER_SIZE <= index) {
    die_with_error("Access to invaild registers. index %ld", index);
  }

  cpu->register_file[0].raw = 0;
  return &cpu->register_file[index];
}

void load_program(CPU* const cpu, ProgramData prog) {
  char* buf = (char*)&cpu->memory[0];
  memcpy(buf, &prog.program[prog.header->n_text_start_offset], prog.header->n_text_size); // load .text 

  buf += prog.header->n_text_size;

  memcpy(buf, &prog.program[prog.header->n_rodata_start_offset], prog.header->n_rodata_size); // load .rodata
}

#define EXE_FUNC_DECL(name) \
  Word EX_##name(CPU* const cpu, const uint64_t funct, const uint64_t reg1, const uint64_t reg2, const uint64_t immd)

EXE_FUNC_DECL(ADD) {
  Word result;
  result.raw = reg1 + (reg2 + immd);

  return result;
}

EXE_FUNC_DECL(SUB) {
  Word result;
  result.raw = reg1 - (reg2 + immd);

  return result;
}

EXE_FUNC_DECL(LOAD_WORD) {
  Word result;
  result.raw = 0;

  return result;
}

EXE_FUNC_DECL(STORE_WORD) {
  Word result;
  result.raw = reg2;

  return result;
}

EXE_FUNC_DECL(SHUTDOWN) {
  cpu->down = 1;
  Word result;
  result.raw = 0;

  return result;
}

EXE_FUNC_DECL(NOP) {
  Word result;
  result.raw = 0;
  return result;
}

EXE_FUNC_DECL(DEBUG) {
  Word result;
  result.raw = 0;

  switch(funct & 1) {
    case 0: {
      printf("%lx\n", reg1); 
      break;
    }
    case 1: {
      printf("%lx\n", reg1);
    }
  }

  return result;
}

EXE_FUNC_DECL(MUL_ADD) {
  Word result;
  result.raw = reg1 * reg2 + immd;

  return result;
}

EXE_FUNC_DECL(DIV_ADD) {
  Word result;
  result.raw = reg1 / reg2 + immd;

  return result;
}

#define INST_WITH_RESULT(name) \
  case I_##name: { \
    printf("%s, reg1 = %lx, reg2 = %lx, immd = %lx\n", #name, reg1, reg2, immd); \
    result = EX_##name(cpu, func, reg1, reg2, immd); \
    cpu->ex_mem_register.enable_forwarding = 1; \
    break; \
  }
#define IGNORE_RESULT(name) \
  case I_##name: { \
    printf("%s, reg1 = %lx, reg2 = %lx, immd = %lx\n", #name, reg1, reg2, immd); \
    result = EX_##name(cpu, func, reg1, reg2, immd); \
    break; \
  }



Word execute_inst(CPU* const cpu, uint64_t opecode, uint64_t func, uint64_t reg1, uint64_t reg2, uint64_t immd) {
  cpu->ex_mem_register.enable_forwarding = 0;
  Word result;

  switch(opecode) {
    INST_WITH_RESULT(ADD);
    INST_WITH_RESULT(SUB);
    INST_WITH_RESULT(SHUTDOWN);
    INST_WITH_RESULT(NOP);
    INST_WITH_RESULT(DEBUG);
    INST_WITH_RESULT(MUL_ADD)
    INST_WITH_RESULT(DIV_ADD)
    IGNORE_RESULT(LOAD_WORD);
    IGNORE_RESULT(STORE_WORD);
    default: {
      die_with_error("Invalid instruction. opecode = %lu", opecode);
    }
  }

  return result;

}

uint64_t calc_address(uint64_t func, uint64_t reg1, uint64_t reg2, uint64_t immd) {
  switch(func) {
    case 0: { // Direct
      return immd;
    }
    case 1: {
      return reg1 + immd;
    }
    case 2: {
      return (reg1 << 32) + immd;
    }
  }
  return (uint64_t)-1;
}

Word MM_LOAD_WORD(CPU* const cpu, uint64_t address, Word value) {
  // Word w = *access_memory(cpu, address);
  // printf("Access by load %lx\n", w.raw);
  return *access_memory(cpu, address);
}

Word MM_STORE_WORD(CPU* const cpu, uint64_t address, Word value) {
  *access_memory(cpu, address) = value;

  Word result;
  result.raw = 0;
  return result;
}

#define INCLUDE_MEM_INSTRUCTION(name) \
  case I_##name: { \
    result = MM_##name(cpu, address, word); \
    cpu->mem_wb_register.enable_forwarding = 1; \
    break; \
  }

Word memory_inst(CPU* const cpu, uint64_t opecode, uint64_t address, uint64_t value) {
  cpu->mem_wb_register.enable_forwarding = 0;
  Word word, result;
  word.raw = value;

  switch(opecode) {
    INCLUDE_MEM_INSTRUCTION(LOAD_WORD);
    INCLUDE_MEM_INSTRUCTION(STORE_WORD);
    default: {
      result.raw = word.raw;
      break;
    }
  }
 
  // printf("memory inst : %lx\n", result.raw);
  return result;
}
