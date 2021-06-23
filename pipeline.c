#include<pthread.h>
#include<stdio.h>

#include "common.h"
#include "pipeline.h"
#include "cpu.h"


pthread_mutex_t if_id_mlock;
IF_ID_Register if_id_register;

pthread_mutex_t id_ex_mlock;
ID_EX_Register id_ex_register;

pthread_mutex_t ex_mem_mlock;
EX_MEM_Register ex_mem_register;

pthread_mutex_t mem_wb_mlock;
MEM_WB_Register mem_wb_register;


pthread_mutex_t reset_mlock;
int reset_signal;

void wait_for_reset_signal() {
  while(1) {
    pthread_mutex_lock(&reset_mlock);
    if(reset_signal) {
      break;
    }
    break;
    pthread_mutex_unlock(&reset_mlock);
  }
}

void pipe_inst_fetch(CPU* const cpu) {
  if(cpu == NULL) {
    die_with_error("CPU is null");
  }
  IF_ID_Register regis;
  Word word;

  word = *access_memory(cpu, cpu->pc);
  regis.inst = word;

  wait_for_reset_signal();

  // write to pipeline register
  pthread_mutex_lock(&if_id_mlock);
  if_id_register = regis;
  pthread_mutex_unlock(&if_id_mlock);
}

void pipe_inst_decode(CPU* const cpu) {
  if(cpu == NULL) {
    die_with_error("CPU is null");
  }

  ID_EX_Register regis;

  pthread_mutex_lock(&if_id_mlock);
  IF_ID_Register prev_regis = if_id_register;
  pthread_mutex_unlock(&if_id_mlock);

  regis.opecode = prev_regis.inst.opecode;
  regis.func = prev_regis.inst.func;
  regis.dest_reg = prev_regis.inst.dest;
  regis.immediate = prev_regis.inst.immediate;
  regis.reg1 = prev_regis.inst.reg1;
  regis.reg2 = prev_regis.inst.reg2;

  wait_for_reset_signal();

  pthread_mutex_lock(&id_ex_mlock);
  id_ex_register = regis;
  pthread_mutex_unlock(&id_ex_mlock);
}

void pipe_execute(CPU* const cpu) {
  ID_EX_Register regis;

  pthread_mutex_lock(&id_ex_mlock);
  regis = id_ex_register;
  pthread_mutex_unlock(&id_ex_mlock);

  // Check pipeline forwardings
  // First, check ex_mem_register

  EX_MEM_Register ex_mem;
  MEM_WB_Register mem_wb;

  pthread_mutex_lock(&ex_mem_mlock);
  ex_mem = ex_mem_register;
  pthread_mutex_unlock(&ex_mem_mlock);

  pthread_mutex_lock(&mem_wb_mlock);
  mem_wb = mem_wb_register;
  pthread_mutex_unlock(&mem_wb_mlock);

  Word reg1_value, reg2_value;
  
  if(regis.reg1 != 0 && ex_mem.dest_reg == regis.reg1) { // forwarding
    reg1_value.raw = ex_mem.result;
  } else if(regis.reg1 != 0 && mem_wb.dest_reg == regis.reg1) {
    // check MEM_WB register after checking EX_MEM register.
    // Because, the result of EX_MEM register is newly than MEM_WB one.
    reg1_value.raw = mem_wb.result;
  } else { // no forwarding
    reg1_value.raw = access_register(cpu, regis.reg1)->raw;
  }

  if(regis.reg2 != 0 && ex_mem.dest_reg == regis.reg2) { // forwarding
    reg2_value.raw = ex_mem.result;
  } else if(regis.reg2 != 0 && mem_wb.dest_reg == regis.reg2) {
    reg2_value.raw = mem_wb.result;
  } else { // no forwarding
    reg2_value.raw = access_register(cpu, regis.reg2)->raw;
  }

  Word result;

  result = execute_inst(cpu, regis.opecode, regis.func, reg1_value.raw, reg2_value.raw, regis.immediate);
  
  EX_MEM_Register next_reg;
  next_reg.address = calc_address(regis.func, reg1_value.raw, reg2_value.raw, regis.immediate);
  next_reg.dest_reg = regis.dest_reg;
  next_reg.opecode = regis.opecode;
  next_reg.result = result.raw;

  wait_for_reset_signal();

  pthread_mutex_lock(&ex_mem_mlock);
  ex_mem_register = next_reg;
  pthread_mutex_unlock(&ex_mem_mlock);
}

void pipe_momacc(CPU* const cpu) {
  EX_MEM_Register prev_regis;

  pthread_mutex_lock(&ex_mem_mlock);
  prev_regis = ex_mem_register ;
  pthread_mutex_unlock(&ex_mem_mlock);

  memory_inst(cpu, prev_regis.opecode, prev_regis.address, prev_regis.result);

  MEM_WB_Register regis;
  regis.dest_reg = prev_regis.dest_reg;
  regis.result = prev_regis.result;
  regis.opecode = prev_regis.opecode;

  wait_for_reset_signal();

  pthread_mutex_lock(&mem_wb_mlock);
  mem_wb_register = regis;
  pthread_mutex_unlock(&mem_wb_mlock);
}

void pipe_wb(CPU* const cpu) {
  MEM_WB_Register prev_regis;

  pthread_mutex_lock(&mem_wb_mlock);
  prev_regis = mem_wb_register;
  pthread_mutex_unlock(&mem_wb_mlock);

  access_register(cpu, prev_regis.dest_reg)->raw = prev_regis.result;
}


