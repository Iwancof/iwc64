#ifndef INCLUDED_COMMON_H
#define INCLUDED_COMMON_H

#include<stdint.h>

void die_with_error(const char* const msg);

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

#endif
