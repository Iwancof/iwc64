#include "cpu.h"
#include "instruction.h"

Word from_raw(const uint64_t raw) {
  Word ret;
  ret.raw = raw;

  return ret;
}

Word ins_a(const uint64_t opecode, const uint64_t a) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.reg1 = a;

  return ret;
}

Word ins_di(const uint64_t opecode, const uint64_t dest, const uint64_t imm) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.dest = dest;
  ret.immediate = imm;

  return ret;
}

Word ins_da(const uint64_t opecode, const uint64_t dest, const uint64_t a) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.dest = dest;
  ret.reg1 = a;

  return ret;
}

Word ins_dab(const uint64_t opecode, const uint64_t dest, const uint64_t reg1, const uint64_t reg2) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.dest = dest;
  ret.reg1 = reg1;
  ret.reg2 = reg2;

  return ret;
}

Word ins_dai(const uint64_t opecode, const uint64_t dest, const uint64_t reg1, const uint64_t imm) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.dest = dest;
  ret.reg1 = reg1;
  ret.immediate = imm;
  
  return ret;
}

Word ins_dabi(const uint64_t opecode, const uint64_t dest, const uint64_t reg1, const uint64_t reg2, const uint64_t imm) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.dest = dest;
  ret.reg1 = reg1;
  ret.reg2 = reg2;
  ret.immediate = imm;

  return ret;
}

Word ins_fdai(const uint64_t opecode, const uint64_t func, const uint64_t dest, const uint64_t reg1, const uint64_t imm) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.func = func;
  ret.dest = dest;
  ret.reg1 = reg1;
  ret.immediate = imm;

  return ret;
}

Word ins_fabi(const uint64_t opecode, const uint64_t func, const uint64_t a, const uint64_t b, const uint64_t imm) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.func = func;
  ret.reg1 = a;
  ret.reg2 = b;
  ret.immediate = imm;

  return ret;
}

Word ins_fdabi(const uint64_t opecode, const uint64_t func, const uint64_t dest, const uint64_t a, const uint64_t b, const uint64_t imm) {
  Word ret = from_raw(0);
  ret.opecode = opecode;
  ret.func = func;
  ret.dest = dest;
  ret.reg1 = a;
  ret.reg2 = b;
  ret.immediate = imm;

  return ret;
}


Word ins_none(const uint64_t opecode) {
  return from_raw(opecode);
};
