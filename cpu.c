#include<stdlib.h>
#include<stdio.h>


#include "common.h"
#include "cpu.h"
#include "instruction.h"

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
    cpu->register_file[i] = init_reg;
  }

  cpu->pc = 0;
  cpu->down = 0;

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
    char msg[256];
    sprintf(msg, "Access to out of memory. addr = 0x%lx", addr);
    die_with_error(msg);
  }
  return &cpu->memory[addr];
}

Register* access_register(CPU* const cpu, const uint64_t index) {
  if(index < 0 || REGISTER_SIZE <= index) {
    char msg[256];
    sprintf(msg, "Access to invalid register. index = %ld\n", index);
    die_with_error(msg);
  }

  cpu->register_file[0].raw = 0;
  return &cpu->register_file[index];
}

void write_testing_program(const CPU* const cpu) {
  Word *m = cpu->memory;

  m[0] = ins_3regi(I_ADD, 1, 1, 2, 0);
  m[1] = ins_no_arg(I_SHUTDOWN);
}

Word EX_ADD(CPU* const cpu, uint64_t reg1, uint64_t reg2, uint64_t immd) {
  Word result;
  result.raw = reg1 + reg2 + immd;

  return result;
}

Word EX_LOAD_WORD(CPU* const cpu, uint64_t reg1, uint64_t reg2, uint64_t immd) {
  Word result;
  result.raw = 0;

  return result;
}

Word EX_STORE_WORD(CPU* const cpu, uint64_t reg1, uint64_t reg2, uint64_t immd) {
  Word result;
  result.raw = reg1;

  return result;
}

Word EX_SHUTDOWN(CPU* const cpu, uint64_t reg1, uint64_t reg2, uint64_t immd) {
  puts("SHUTDOWN");

  cpu->down = 1;
  Word result;
  result.raw = 0;

  return result;
}

Word EX_NOP(CPU* const cpu, uint64_t reg1, uint64_t reg2, uint64_t immd) {
  puts("NOP");
  Word result;
  result.raw = 0;
  return result;
}

#define INCLUDE_INSTRUCTION(name) \
  case I_##name: { \
    result = EX_##name(cpu, reg1, reg2, immd); \
                   break; \
                 }

Word execute_inst(CPU* const cpu, uint64_t opecode, uint64_t reg1, uint64_t reg2, uint64_t immd) {
  Word result;

  switch(opecode) {
    INCLUDE_INSTRUCTION(ADD);
    INCLUDE_INSTRUCTION(SHUTDOWN);
    INCLUDE_INSTRUCTION(NOP);
    default: {
               char msg[256];
               sprintf(msg, "Invalid instruction. opecode = %lu", opecode);
               die_with_error(msg);
             }
  }

  return result;

}

uint64_t calc_address(uint64_t func, uint64_t reg1, uint64_t reg2, uint64_t immd) {
  switch(func) {
  case 0: { // Direct
            return immd;
          }
  }

  return (uint64_t)-1;
}

Word MM_LOAD_WORD(CPU* const cpu, uint64_t address, Word value) {
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
                   break; \
                 } 

Word memory_inst(CPU* const cpu, uint64_t opecode, uint64_t address, uint64_t value) {
  Word word, result;
  word.raw = value;

  switch(opecode) {
    INCLUDE_MEM_INSTRUCTION(LOAD_WORD);
  }

  return result;
}