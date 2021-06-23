#ifndef INCLUDED_CPU_H
#define INCLUDED_CPU_H

#include<stdint.h>

#include "common.h"

#define MEMORY_SIZE 0x1000
#define REGISTER_SIZE 16

typedef struct {
  // Basic
  Word *memory;
  Register register_file[REGISTER_SIZE];
  uint64_t pc;
  int down;

  // Pipeline registers
  IF_ID_Register if_id_register;
  ID_EX_Register id_ex_register;
  EX_MEM_Register ex_mem_register;
  MEM_WB_Register mem_wb_register;
} CPU;

int initialize_cpu(CPU* const cpu);
int initialize_memory_and_check(const CPU* const cpu);
Word* access_memory(CPU* const cpu, const uint64_t addr);
Register* access_register(CPU* const cpu, const uint64_t index);
void write_testing_program(const CPU* const cpu);
Word execute_inst(CPU* const cpu, uint64_t opecode, uint64_t func, uint64_t reg1, uint64_t reg2, uint64_t immd);
uint64_t calc_address(uint64_t func, uint64_t reg1, uint64_t reg2, uint64_t immd);
Word memory_inst(CPU* const cpu, uint64_t opecode, uint64_t address, uint64_t value);

#endif
