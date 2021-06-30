#include<stdio.h>
#include<stdlib.h>

#include "common.h"
#include "instruction.h"

void objdump_show_menu(const char* const pn) {
  printf("Usage: %s [option]\n", pn);
  puts("Options:");
  show_option("-d BINARY", "show assembly list");
}

int main(int argc, char* argv[]) {

  int disas_flag = 0;
  int edit_flag = 0;
  int spec_flag = 0;
  int new_flag = 0;
  char* filename = NULL;
  
  int opt;
  while((opt = getopt(argc, argv, "n:d:e:")) != -1) {
    switch(opt) {
      case 'd': {
        spec_flag += 1;
        disas_flag = 1;
        filename = optarg;
        break;
      }
      case 'e': {
        spec_flag += 1;
        edit_flag = 1;
        filename = optarg;
        break;
      }
      case 'n': {
        spec_flag += 1;
        new_flag = 1;
        filename = optarg;
        break;
      }
      case '?': {
        objdump_show_menu(argv[0]);
        exit(-1);
      }
    }
  }

  if(spec_flag != 1) {
    objdump_show_menu(argv[0]);
    exit(-1);
  }
 
  if(disas_flag) {
    ProgramData prog = open_program(filename, 0);
    dump_header(prog.header);

    char* valid_msg = check_norn_vaildity(prog.header, prog.program_size);
    if(valid_msg) {
      die_with_error("%s", valid_msg);
    }
  } else if(edit_flag) {
    ProgramData prog = open_program(filename, 0);

    write_program(filename, prog);
  } else if(new_flag) {
    Word* text = (Word*)malloc(sizeof(Word) * 0x100);

    text[0] = ins_di(I_ADD, 1, 0x20);
    text[1] = ins_di(I_ADD, 2, 0x2);
    text[2] = ins_dab(I_MUL_ADD, 1, 1, 2);
    text[3] = ins_a(I_DEBUG, 1); // 0x20 * 2
    text[4] = ins_di(I_ADD, 2, 0x10);
    text[5] = ins_dab(I_DIV_ADD, 1, 1, 2);
    text[6] = ins_a(I_DEBUG, 1); // 0x40 / 4
    text[7] = ins_none(I_SHUTDOWN);

    char rodata[] = "ABCDEFGH";

    ProgramData prog =  assemble_program((char*)text, 0x40 * sizeof(Word), rodata, 8);

    prog.header->n_type = N_EXEC;
    prog.header->n_test_case_start_offset = 0;
    prog.header->n_test_case_size = 0;

    dump_header(prog.header);

    write_program(filename, prog);
  }
}

