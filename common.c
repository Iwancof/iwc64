#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>


#include "common.h"

void die_with_error(const char* const msg) {
  fprintf(stderr, "error occured. msg = %s\n", msg);
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

typedef struct {
  char* program;
  size_t program_size;
  uint64_t* test_cases;
  size_t test_size;
} ProgramData;

void open_binary(const char* const filename, const int test_case) {
  int fd = open(filename, O_RDONLY);

  if(fd == -1) {
    die_with_error("Can't open file");
  }

  const size_t max_contents_size = 0x1000;

}
