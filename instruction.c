#include "cpu.h"
#include "instruction.h"

Word from_raw(const uint64_t raw) {
  Word ret;
  ret.raw = raw;

  return ret;
}

Word ins_1reg(const uint64_t opecode, const uint64_t reg1) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.reg1 = reg1;

  return ret;
}

Word ins_2reg(const uint64_t opecode, const uint64_t dest, const uint64_t reg1) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.dest = dest;
  ret.reg1 = reg1;

  return ret;
}

Word ins_3reg(const uint64_t opecode, const uint64_t dest, const uint64_t reg1, const uint64_t reg2) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.dest = dest;
  ret.reg1 = reg1;
  ret.reg2 = reg2;

  return ret;
}

Word ins_2regi(const uint64_t opecode, const uint64_t dest, const uint64_t reg1, const uint64_t imm) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.dest = dest;
  ret.reg1 = reg1;
  ret.immediate = imm;
  
  return ret;
}

Word ins_3regi(const uint64_t opecode, const uint64_t dest, const uint64_t reg1, const uint64_t reg2, const uint64_t imm) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.dest = dest;
  ret.reg1 = reg1;
  ret.reg2 = reg2;
  ret.immediate = imm;

  return ret;
}

Word ins_2regfi(const uint64_t opecode, const uint64_t func, const uint64_t dest, const uint64_t reg1, const uint64_t imm) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.func = func;
  ret.dest = dest;
  ret.reg1 = reg1;
  ret.immediate = imm;

  return ret;
}

Word ins_no_arg(const uint64_t opecode) {
  return from_raw(opecode);
};
