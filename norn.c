#include<stdio.h>

#include "norn.h"

void dump_header(const NornHeader* const header) {
  int type_flag = 0;

  printf("Norn type: ");
  if(header->n_type & N_EXEC) {
    type_flag = 1;
    printf("E");
  }
  if(header->n_type & N_TEST) {
    type_flag = 1;
    printf("T");
  }
  if(!type_flag) {
    printf("None");
  }
  puts("");

  puts(".text");
  printf("  start offset: 0x%lx\n", header->n_text_start_offset);
  printf("  size: 0x%lx\n", header->n_text_size);

  puts("rodata");
  printf("  start offset: 0x%lx\n", header->n_rodata_start_offset);
  printf("  size: 0x%lx\n", header->n_rodata_size);

  puts("test cases");
  printf("  start offset: 0x%lx\n", header->n_test_case_start_offset);
  printf("  size: 0x%lx\n", header->n_test_case_size);
}

char* check_norn_vaildity(const NornHeader* const header, uint64_t file_size) {
  if(header->n_type & (~NORN_TYPE_MASK)) {
    return "Invalid norn type.";
  }

  if(file_size < header->n_text_start_offset + header->n_text_size) {
    return ".text too long";
  }

  if(file_size < header->n_rodata_start_offset + header->n_rodata_size) {
    return ".rodata too long";
  }

  if(file_size < header->n_test_case_start_offset + header->n_test_case_size) {
    return "test cases too long";
  }

  return NULL;
}

