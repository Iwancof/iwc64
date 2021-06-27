#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdarg.h>
#include<string.h>
#include<fcntl.h>

#include "common.h"
#include "norn.h"

void die_with_error(const char* const format, ...) {
  va_list ap;

  va_start(ap, format);

  vfprintf(stderr, format, ap);
  puts("");

  va_end(ap);

  exit(-1);
}

const int command_left_padding = 2;
const int description_padding = 30;

void show_option(const char* const cmd, const char* const desc) {
  for(size_t i = 0;i < command_left_padding;i++) {
    printf(" ");
  }
  printf("%s", cmd);

  const size_t len = strlen(cmd);
  if(description_padding < command_left_padding + len) {
    printf("\n");
    for(size_t i = 0;i < description_padding;i++) {
      printf(" ");
    }
    printf("%s\n", desc);
  } else {
    for(size_t i = 0;i < description_padding - command_left_padding - len;i++) {
      printf(" ");
    }
    printf("%s\n", desc);
  }
}

void show_menu(const char* const pn) {
  printf("Usage: %s [option]\n", pn);
  puts("Options:");
  show_option("-r BINARY", "Run BINARY");
  show_option("-t BINARY", "Run BINARY as test");
}

char* open_binary(const char* const filename, size_t* const size) {
  int fd = open(filename, O_RDONLY);

  if(fd == -1) {
    die_with_error("Can't open file %p\n", filename);
  }

  const size_t max_contents_size = 0x1000;

  char* ptr;
  if((ptr = (char*)malloc(sizeof(char) * max_contents_size)) == NULL) {
    die_with_error("malloc error");
  }
  if((*size = read(fd, ptr, max_contents_size)) == max_contents_size) {
    die_with_error("file %s is too long", filename);
  }
  if((ptr = (char*)realloc(ptr, *size)) == NULL) {
    die_with_error("realloc error");
  }

  return ptr;
}

ProgramData open_program(const char* const filename, const int test_enable) {
  ProgramData prog;

  size_t bin_size;
  char* bin = open_binary(filename, &bin_size);

  // if program size is smaller than norn header.
  if(bin_size < sizeof(NornHeader)) {
    die_with_error("Program size was smaller than norn header");
  }

  NornHeader *header = (NornHeader*)bin;

  // test enabled but program file dosen't have any test cases.
  if(test_enable && (header->n_type & N_TEST)) {
    die_with_error("Test enabled but file dosen't have any test cases");
  }

  prog.program = bin;
  prog.program_size = bin_size;
  prog.header = header;

  return prog;
}


