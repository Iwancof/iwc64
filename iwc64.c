#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include "common.h"
#include "cpu.h"
#include "pipeline.h"

static uint64_t code_start = 0;
// static uint64_t data_start = 0;

int main(int argc, char* argv[]) {
  int spec_flag = 0;
  int test_flag = 0;
  const char* program_name = NULL;

  int opt; 
  while((opt = getopt(argc, argv, "r:t:")) != -1) {
    switch(opt) {
      case 'r': {
        spec_flag = 1;
        program_name = optarg;
        break;
      }
      case 't': {
        spec_flag = 1;
        test_flag = 1;

        program_name = optarg;
        break;
      }
      case '?': {
        show_menu(argv[0]);
        exit(-1);
      }
    }
  }

  if(!spec_flag) {
    show_menu(argv[0]);
    exit(-1);
  }

  ProgramData prog = open_program(program_name, test_flag);

  CPU cpu;

  if(initialize_cpu(&cpu)) {
    die_with_error("Could not initialize CPU");
  }
  if(initialize_memory_and_check(&cpu)) {
    die_with_error("Could not initialize CPU memory");
  }

  // write_testing_program(&cpu);
  load_program(&cpu, prog);
  


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

