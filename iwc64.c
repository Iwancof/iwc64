#include<stdio.h>
#include<stdlib.h>

#include "common.h"
#include "cpu.h"
#include "pipeline.h"

void die_with_error(const char* const msg) {
  fprintf(stderr, "error occured. msg = %s\n", msg);
  exit(-1);
}

static uint64_t code_start = 0;
// static uint64_t data_start = 0;

int main() {
  CPU cpu;

  if(initialize_cpu(&cpu)) {
    die_with_error("Could not initialize CPU");
  }
  if(initialize_memory_and_check(&cpu)) {
    die_with_error("Could not initialize CPU memory");
  }

  write_testing_program(&cpu);
  cpu.pc = code_start;

  while(!cpu.down) {
    pipe_wb(&cpu);
    pipe_momacc(&cpu);
    pipe_execute(&cpu);
    pipe_inst_decode(&cpu);
    pipe_inst_fetch(&cpu);

    cpu.pc += 1;
  }
}

