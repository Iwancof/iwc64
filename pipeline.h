#ifndef INCLUDED_PIPELINE_H
#define INCLUDED_PIPELINE_H

#include "common.h"
#include "cpu.h"

void wait_for_reset_signal();
void pipe_inst_fetch(CPU* const cpu);
void pipe_inst_decode(CPU* const cpu);
void pipe_execute(CPU* const cpu);
void pipe_momacc(CPU* const cpu);
void pipe_wb(CPU* const cpu);

#endif
