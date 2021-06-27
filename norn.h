#ifndef INCLUDED_NORN_H
#define INCLUDED_NORN_H

#include<stdint.h>

#define NORN_TYPE_MASK 0b11

enum NornType {
  N_EXEC = 0b01,
  N_TEST = 0b10
};

typedef struct {
  enum NornType n_type;
  uint64_t n_text_start_offset;
  uint64_t n_text_size;
  uint64_t n_rodata_start_offset;
  uint64_t n_rodata_size;
  uint64_t n_test_case_start_offset;
  uint64_t n_test_case_size;
} NornHeader;

void dump_header(const NornHeader* const header);
char* check_norn_vaildity(const NornHeader* const header, uint64_t file_size);


#endif
