#ifndef INCLUDED_COMMON_H
#define INCLUDED_COMMON_H

#include<stdint.h>
#include<unistd.h>

#include "norn.h" 
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

typedef struct {
  char* program;
  size_t program_size;
  NornHeader *header;
} ProgramData;

void die_with_error(const char* const format, ...);
void show_option(const char* const cmd, const char* const desc);
void show_menu(const char* const pn);
ProgramData open_program(const char* const filename, const int test_enable);
void write_program(const char* const filename, const ProgramData prog);
ProgramData assemble_program(const char* const text, const size_t text_size, const char* const rodata, const size_t rodata_size);

#endif
