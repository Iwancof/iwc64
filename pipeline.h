#ifndef INCLUDED_PIPELINE_H
#define INCLUDED_PIPELINE_H

#include "cpu.h"

typedef struct {
  Word inst;
} IF_ID_Register;

typedef struct {
  uint64_t opecode: 14;
  uint64_t func: 3;
  uint64_t dest_reg: 5;
  uint64_t reg1: 5;
  uint64_t reg2: 5;
  uint64_t immediate: 32;
} ID_EX_Register;

typedef struct {
  uint64_t opecode: 14;
  uint64_t dest_reg: 5;
  uint64_t address: 64;
  uint64_t result: 64;
} EX_MEM_Register;

typedef struct {
  uint64_t opecode: 14;
  uint64_t result: 64;
  uint64_t dest_reg: 5;
} MEM_WB_Register;

void wait_for_reset_signal();
void pipe_inst_fetch(CPU* const cpu);
void pipe_inst_decode(CPU* const cpu);
void pipe_execute(CPU* const cpu);
void pipe_momacc(CPU* const cpu);
void pipe_wb(CPU* const cpu);

#endif
