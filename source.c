#include "instruction.h"
#include<stdio.h>

extern size_t program_writing_index;
extern Word* program_text;

#define DEF_INS(name, arg) \
  __attribute__ ((unused)) void name(T_##arg) { \
    program_text[program_writing_index++] = ins_##arg(I_##name A_##arg); \
  }

    // program_text[program_writing_index++] = c_##arg(name, A_##arg);


DEF_INS(ADD, dabi);
DEF_INS(SUB, dabi);
DEF_INS(MUL_ADD, dabi);
DEF_INS(DIV_ADD, dabi);

DEF_INS(LOAD_WORD, fdai);
DEF_INS(STORE_WORD, fdabi);

DEF_INS(JUMP, fdai);
DEF_INS(JUMP_EQ, fdabi);

DEF_INS(CMP, dabi);

DEF_INS(NOP, none);
DEF_INS(SHUTDOWN, none);
DEF_INS(DEBUG, a);

#define MOV(dest, immd) \
  ADD(dest, 0, 0, immd);

MOV(1, 1);
DEBUG(1);

JUMP_EQ(0, 0, 0, 1, sizeof(Word) * 2);

MOV(1, 0);
NOP();
NOP();
NOP();

SHUTDOWN();


