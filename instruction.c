#include "cpu.h"
#include "instruction.h"

Word from_raw(uint64_t raw) {
  Word ret;
  ret.raw = raw;

  return ret;
}

Word ins_2reg(uint64_t opecode, uint64_t dest, uint64_t reg1) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.dest = dest;
  ret.reg1 = reg1;

  return ret;
}

Word ins_3reg(uint64_t opecode, uint64_t dest, uint64_t reg1, uint64_t reg2) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.dest = dest;
  ret.reg1 = reg1;
  ret.reg2 = reg2;

  return ret;
}

Word ins_2regi(uint64_t opecode, uint64_t dest, uint64_t reg1, uint64_t imm) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.dest = dest;
  ret.reg1 = reg1;
  ret.immediate = imm;
  
  return ret;
}

Word ins_3regi(uint64_t opecode, uint64_t dest, uint64_t reg1, uint64_t reg2, uint64_t imm) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.dest = dest;
  ret.reg1 = reg1;
  ret.reg2 = reg2;
  ret.immediate = imm;

  return ret;
}

Word ins_no_arg(uint64_t opecode) {
  return from_raw(opecode);
};
