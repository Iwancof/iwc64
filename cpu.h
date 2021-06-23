#ifndef INCLUDED_CPU_H
#define INCLUDED_CPU_H

#include<stdint.h>

#define MEMORY_SIZE 0x1000
#define REGISTER_SIZE 16

typedef union {
  uint64_t raw;
  struct {
    uint64_t opecode: 14;
    uint64_t func: 3;
    uint64_t dest: 5;
    uint64_t reg1: 5;
    uint64_t reg2: 5;
    uint64_t immediate: 32;
  };
} Word;

typedef union {
  uint64_t raw;
} Register;

typedef struct {
  Word *memory;
  Register register_file[REGISTER_SIZE];
  uint64_t pc;
  int down;
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
