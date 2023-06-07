/***************************************************************************//**
 * @file
 * @brief MVP Core driver.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include "sl_mvp.h"
#include "em_device.h"
#include "sl_assert.h"
#include "sl_mvp_hal.h"
#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#if defined(SL_CATALOG_STATUS_STRING_PRESENT)
#include "sl_status_string_config.h"
#endif

#include <stddef.h>
#include <string.h>

#define NUM_PERF_CNT              2
#define MAX_NUM_ARRAYS            5
#define MAX_NUM_LOOPS             8
#define MAX_NUM_INSTRUCTIONS      8
#define MAX_NUM_REGS              8
#define MAX_ARRAY_DIM_SIZE     1024
#define MAX_ARRAY_STRIDE_SIZE  2047
#define MIN_ARRAY_STRIDE_SIZE -2048
#define MAX_LOOP_COUNT         1024

#define SLI_MVP_FAULT_MASK (MVP_IF_LOOPFAULT | MVP_IF_BUSERRFAULT    \
                            | MVP_IF_BUSALIGNFAULT | MVP_IF_ALUFAULT \
                            | MVP_IF_ARRAYFAULT)

static uint32_t mvp_numerical_exception_flags;
bool sli_mvp_fault_flag;
static uint32_t mvp_program_count = 0;
static volatile uint32_t perfcnt[NUM_PERF_CNT] = { 0 };
// Software retained MVP registers.
static volatile uint32_t mvp_reg_cfg = MVP_CFG_PERF0CNTSEL_RUN | MVP_CFG_PERF1CNTSEL_STALL | MVP_CFG_PERFCNTEN;
static volatile bool mvp_is_enabled = false;

static void enable_callback(void)
{
  MVP->EN_SET = MVP_EN_EN;
  MVP->IEN_SET = MVP_IEN_PERFCNT0 | MVP_IEN_PERFCNT1 | MVP_IEN_PROGDONE
                 | SLI_MVP_FAULT_MASK;
  MVP->CFG = mvp_reg_cfg;
  mvp_is_enabled = true;
}

static void disable_callback(void)
{
  mvp_reg_cfg = MVP->CFG;
  MVP->EN_CLR = MVP_EN_EN;
  while (MVP->EN & MVP_EN_DISABLING)
    ;
  MVP->IEN_CLR = 0xffffffff;
  mvp_is_enabled = false;
}

static bool isr_callback(void)
{
  uint32_t pending, tmp;
  bool done = false;

  pending = MVP->IF;
  pending &= MVP->IEN;

  if (pending & SLI_MVP_FAULT_MASK) {
    sli_mvp_fault_flag = true;
    done = true;
  }
  if (pending & MVP_IF_PROGDONE) {
    while (!(MVP->STATUS & MVP_STATUS_IDLE)) {
    }
    tmp = MVP->PERF[0].CNT;
    perfcnt[0] += tmp;
    tmp = MVP->PERF[1].CNT;
    perfcnt[1] += tmp;
    done = true;
  }
  if (pending & MVP_IF_PERFCNT0) {
    perfcnt[0] += (_MVP_PERFCNT_COUNT_MASK + 1);
  }
  if (pending & MVP_IF_PERFCNT1) {
    perfcnt[1] += (_MVP_PERFCNT_COUNT_MASK + 1);
  }

  MVP->IF_CLR = pending;

  return done;
}

void sli_mvp_clear_error_flags(uint32_t flags)
{
  mvp_numerical_exception_flags &= ~(flags & SLI_MVP_NUMERIC_EXCEPTION_FLAG_MASK);
  if (flags & SLI_MVP_FAULT_FLAG) {
    sli_mvp_fault_flag = false;
  }
}

sl_status_t sli_mvp_get_error(sl_status_t *error_code,
                              char *error_message,
                              uint32_t buffer_length)
{
  if (!error_code) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  uint32_t flag = 0;
  uint32_t flags = mvp_numerical_exception_flags & SLI_MVP_NUMERIC_EXCEPTION_FLAG_MASK;

  if (sli_mvp_fault_flag) {
    sli_mvp_fault_flag = false;
    *error_code = SL_STATUS_COMPUTE_DRIVER_FAULT;

  } else if (flags & MVP_IF_ALUNAN) {
    *error_code = SL_STATUS_COMPUTE_DRIVER_ALU_NAN;
    flag = MVP_IF_ALUNAN;
  } else if (flags & MVP_IF_ALUOF) {
    *error_code = SL_STATUS_COMPUTE_DRIVER_ALU_OVERFLOW;
    flag = MVP_IF_ALUOF;
  } else if (flags & MVP_IF_ALUUF) {
    *error_code = SL_STATUS_COMPUTE_DRIVER_ALU_UNDERFLOW;
    flag = MVP_IF_ALUUF;

  } else if (flags & MVP_IF_STORECONVERTOF) {
    *error_code = SL_STATUS_COMPUTE_DRIVER_STORE_CONVERSION_OVERFLOW;
    flag = MVP_IF_STORECONVERTOF;
  } else if (flags & MVP_IF_STORECONVERTUF) {
    *error_code = SL_STATUS_COMPUTE_DRIVER_STORE_CONVERSION_UNDERFLOW;
    flag = MVP_IF_STORECONVERTUF;
  } else if (flags & MVP_IF_STORECONVERTINF) {
    *error_code = SL_STATUS_COMPUTE_DRIVER_STORE_CONVERSION_INFINITY;
    flag = MVP_IF_STORECONVERTINF;
  } else if (flags & MVP_IF_STORECONVERTNAN) {
    *error_code = SL_STATUS_COMPUTE_DRIVER_STORE_CONVERSION_NAN;
    flag = MVP_IF_STORECONVERTNAN;

  } else {
    return SL_STATUS_NOT_FOUND;
  }

  mvp_numerical_exception_flags &= ~flag;

#if defined(SL_CATALOG_STATUS_STRING_PRESENT) && (SL_STATUS_STRING_ENABLE_COMPUTE == 1)
  if (error_message != NULL) {
    sl_status_get_string_n(*error_code, error_message, buffer_length);
  }
#else
  if ((error_message != NULL) && (buffer_length > 0)) {
    error_message[0] = '\0';
  }
#endif

  return SL_STATUS_OK;
}

uint32_t sli_mvp_get_error_flags(void)
{
  uint32_t flags = mvp_numerical_exception_flags & SLI_MVP_NUMERIC_EXCEPTION_FLAG_MASK;
  if (sli_mvp_fault_flag) {
    flags |= SLI_MVP_FAULT_FLAG;
  }
  return flags;
}

sl_status_t sli_mvp_init(void)
{
  sli_mvp_fault_flag = false;
  mvp_numerical_exception_flags = 0U;
  return sli_mvp_hal_init(enable_callback, disable_callback, isr_callback);
}

sl_status_t sli_mvp_deinit(void)
{
  return sli_mvp_hal_deinit();
}

void sli_mvp_cmd_enable(void)
{
  sli_mvp_hal_cmd_wait_for_completion();
  sli_mvp_hal_cmd_enable();
}

void sli_mvp_cmd_wait_for_completion(void)
{
  sli_mvp_hal_cmd_wait_for_completion();
  mvp_numerical_exception_flags |= MVP->IF;
  MVP->IF_CLR = SLI_MVP_NUMERIC_EXCEPTION_FLAG_MASK;
}

sl_status_t sli_mvp_prog_execute(sli_mvp_program_t *program, bool wait)
{
  program->CMD = MVP_CMD_INIT | MVP_CMD_START;
  mvp_program_count++;
  sli_mvp_hal_cmd_wait_for_completion();
  sli_mvp_hal_cmd_enable();
  sli_mvp_hal_load_program(program, &MVP->ALU[0], sizeof(sli_mvp_program_t));
  if (wait) {
    sli_mvp_hal_cmd_wait_for_completion();
    mvp_numerical_exception_flags |= MVP->IF;
    MVP->IF_CLR = SLI_MVP_NUMERIC_EXCEPTION_FLAG_MASK;
  }
  return SL_STATUS_OK;
}

void sli_mvp_prog_set_reg_s8(sli_mvp_program_t *prog, uint8_t reg, int8_t value)
{
  sli_mvp_prog_set_reg_f16c(prog, reg, value, 0);
}

void sli_mvp_prog_set_reg_s8c(sli_mvp_program_t *prog, uint8_t reg, int8_t real, int8_t imag)
{
  sli_mvp_prog_set_reg_f16c(prog, reg, real, imag);
}

void sli_mvp_prog_set_reg_s16(sli_mvp_program_t *prog, uint8_t reg, int16_t value)
{
  sli_mvp_prog_set_reg_f16c(prog, reg, value, 0);
}

void sli_mvp_prog_set_reg_s16c(sli_mvp_program_t *prog, uint8_t reg, int16_t real, int16_t imag)
{
  sli_mvp_prog_set_reg_f16c(prog, reg, real, imag);
}

void sli_mvp_prog_set_reg_s32(sli_mvp_program_t *prog, uint8_t reg, int32_t value)
{
  sli_mvp_prog_set_reg_f16c(prog, reg, (float16_t)value, 0);
}

void sli_mvp_prog_set_reg_s32c(sli_mvp_program_t *prog, uint8_t reg, int32_t real, int32_t imag)
{
  sli_mvp_prog_set_reg_f16c(prog, reg, (float16_t)real, (float16_t)imag);
}

void sli_mvp_prog_set_reg_f16(sli_mvp_program_t *prog, uint8_t reg, float16_t value)
{
  sli_mvp_prog_set_reg_f16c(prog, reg, value, 0);
}

void sli_mvp_prog_set_reg_f16c(sli_mvp_program_t *prog, uint8_t reg, float16_t real, float16_t imag)
{
  EFM_ASSERT(reg < MAX_NUM_REGS);

  prog->ALU[reg].reg.value.real = real;
  prog->ALU[reg].reg.value.imag = imag;
}

void sli_mvp_prog_set_reg_f32(sli_mvp_program_t *prog, uint8_t reg, float value)
{
  sli_mvp_prog_set_reg_f16c(prog, reg, value, 0);
}

void sli_mvp_prog_set_reg_f32c(sli_mvp_program_t *prog, uint8_t reg, float real, float imag)
{
  sli_mvp_prog_set_reg_f16c(prog, reg, real, imag);
}

void sli_mvp_prog_set_array_full(sli_mvp_program_t *prog,
                                 uint8_t index,
                                 void *addr,
                                 sli_mvp_datatype_t type,
                                 unsigned short vecs,
                                 unsigned short rows,
                                 unsigned short cols,
                                 int vecstride,
                                 int rowstride,
                                 int colstride)
{
  EFM_ASSERT(index < MAX_NUM_ARRAYS);
  EFM_ASSERT(vecs <= MAX_ARRAY_DIM_SIZE);
  EFM_ASSERT(rows <= MAX_ARRAY_DIM_SIZE);
  EFM_ASSERT(cols <= MAX_ARRAY_DIM_SIZE);
  EFM_ASSERT(vecstride >= MIN_ARRAY_STRIDE_SIZE && vecstride <= MAX_ARRAY_STRIDE_SIZE);
  EFM_ASSERT(rowstride >= MIN_ARRAY_STRIDE_SIZE && rowstride <= MAX_ARRAY_STRIDE_SIZE);
  EFM_ASSERT(colstride >= MIN_ARRAY_STRIDE_SIZE && colstride <= MAX_ARRAY_STRIDE_SIZE);

  uint32_t datatype = (uint32_t)type;
  prog->ARRAY[index].DIM0CFG = (((vecs - 1) << _MVP_ARRAYDIM0CFG_SIZE_SHIFT) & _MVP_ARRAYDIM0CFG_SIZE_MASK);
  prog->ARRAY[index].DIM1CFG = (((rows - 1) << _MVP_ARRAYDIM1CFG_SIZE_SHIFT) & _MVP_ARRAYDIM1CFG_SIZE_MASK);
  prog->ARRAY[index].DIM2CFG = (((cols - 1) << _MVP_ARRAYDIM2CFG_SIZE_SHIFT) & _MVP_ARRAYDIM2CFG_SIZE_MASK);

  // Set up Array Strides This is a 10-bit signed integer between -512 and +511
  prog->ARRAY[index].DIM0CFG |= ((vecstride << _MVP_ARRAYDIM0CFG_STRIDE_SHIFT) & _MVP_ARRAYDIM0CFG_STRIDE_MASK);
  prog->ARRAY[index].DIM1CFG |= ((rowstride << _MVP_ARRAYDIM1CFG_STRIDE_SHIFT) & _MVP_ARRAYDIM1CFG_STRIDE_MASK);
  prog->ARRAY[index].DIM2CFG |= ((colstride << _MVP_ARRAYDIM2CFG_STRIDE_SHIFT) & _MVP_ARRAYDIM2CFG_STRIDE_MASK);

  // Set up datatype
  prog->ARRAY[index].DIM0CFG |= ((datatype << _MVP_ARRAYDIM0CFG_BASETYPE_SHIFT) & _MVP_ARRAYDIM0CFG_BASETYPE_MASK);
  if ((datatype & 0x4) == 0x4) {
    prog->ARRAY[index].DIM0CFG |= (_MVP_ARRAYDIM0CFG_COMPLEX_COMPLEX << _MVP_ARRAYDIM0CFG_COMPLEX_SHIFT);
  }

  // Program array base address
  prog->ARRAY[index].ADDRCFG = (sli_mvp_addr_reg_t)addr;
}

void sli_mvp_prog_set_array(sli_mvp_program_t *prog,
                            uint8_t index,
                            void *addr,
                            sli_mvp_datatype_t type,
                            unsigned short vecs,
                            unsigned short rows,
                            unsigned short cols)
{
  int colstride = 1;
  int rowstride = cols;
  int vecstride = rows * cols;
  sli_mvp_prog_set_array_full(prog, index, addr, type, vecs, rows, cols, vecstride, rowstride, colstride);
}

void sli_mvp_prog_set_vector(sli_mvp_program_t *prog,
                             uint8_t index,
                             void *addr,
                             sli_mvp_datatype_t type,
                             unsigned short len)
{
  int colstride = 1;
  sli_mvp_prog_set_array_full(prog, index, addr, type, 1, 1, len, 0, 0, colstride);
}

void sli_mvp_prog_set_matrix(sli_mvp_program_t *prog,
                             uint8_t index,
                             void *addr,
                             sli_mvp_datatype_t type,
                             unsigned short rows,
                             unsigned short cols)
{
  int colstride = 1;
  int rowstride = cols;
  sli_mvp_prog_set_array_full(prog, index, addr, type, 1, rows, cols, 0, rowstride, colstride);
}

void sli_mvp_prog_set_instr(sli_mvp_program_t *prog,
                            uint8_t index,
                            uint32_t opcode,
                            uint32_t alu_cfg,
                            uint32_t load_cfg,
                            uint32_t store_cfg,
                            bool end)
{
  EFM_ASSERT(index < MAX_NUM_INSTRUCTIONS);

  prog->INSTR[index].CFG0 = alu_cfg;
  prog->INSTR[index].CFG1 = load_cfg | store_cfg;
  // This implicitly clears any loop controls
  prog->INSTR[index].CFG2 = opcode << _MVP_INSTRCFG2_ALUOP_SHIFT;
  if (end) {
    prog->INSTR[index].CFG2 |= MVP_INSTRCFG2_ENDPROG;
  }
}

void sli_mvp_prog_set_loop(sli_mvp_program_t *prog,
                           uint8_t index,
                           unsigned short count,
                           uint8_t istart,
                           uint8_t iend,
                           uint32_t incrarray,
                           uint32_t rstarray)
{
  EFM_ASSERT(index < MAX_NUM_LOOPS);
  EFM_ASSERT(count > 0 && count <= MAX_LOOP_COUNT);
  EFM_ASSERT(istart < MAX_NUM_INSTRUCTIONS);
  EFM_ASSERT(iend < MAX_NUM_INSTRUCTIONS);

  // Program loop iterations, increment and reset bit masks
  prog->LOOP[index].CFG = ((count - 1) << _MVP_LOOPCFG_NUMITERS_SHIFT)
                          | (incrarray << _MVP_LOOPCFG_ARRAY0INCRDIM0_SHIFT);
  prog->LOOP[index].RST = rstarray << _MVP_LOOPRST_ARRAY0RESETDIM0_SHIFT;

  // Update instruction field with loop information
  // This is done with a read-modify-write since it overlays fields set by the instruction call
  if (istart == iend) {
    prog->INSTR[istart].CFG2 |= (3 << (2 * index));
  } else {
    prog->INSTR[istart].CFG2 |= (1 << (2 * index));
    prog->INSTR[iend].CFG2 |= (2 << (2 * index));
  }
}

void sli_mvp_perfcnt_conf(unsigned id, sli_mvp_perfcnt_t type)
{
  if (id >= NUM_PERF_CNT) {
    return;
  }

  if (mvp_is_enabled) {
    if (id == 0) {
      MVP->CFG = (MVP->CFG & ~(_MVP_CFG_PERF0CNTSEL_MASK))
                | ((uint32_t) type << _MVP_CFG_PERF0CNTSEL_SHIFT);
    } else if (id == 1) {
      MVP->CFG = (MVP->CFG & ~(_MVP_CFG_PERF1CNTSEL_MASK))
                | ((uint32_t) type << _MVP_CFG_PERF1CNTSEL_SHIFT);
    }
  } else {
    if (id == 0) {
      mvp_reg_cfg = (mvp_reg_cfg & ~(_MVP_CFG_PERF0CNTSEL_MASK))
                | ((uint32_t)type << _MVP_CFG_PERF0CNTSEL_SHIFT);
    } else if (id == 1) {
      mvp_reg_cfg = (mvp_reg_cfg & ~(_MVP_CFG_PERF1CNTSEL_MASK))
                | ((uint32_t)type << _MVP_CFG_PERF1CNTSEL_SHIFT);
    }
  }
  perfcnt[id] = 0;
}

void sli_mvp_perfcnt_reset_all(void)
{
  for (size_t i = 0; i < NUM_PERF_CNT; i++) {
    perfcnt[i] = 0;
  }
}

uint32_t sli_mvp_perfcnt_get(unsigned id)
{
  if (id >= NUM_PERF_CNT) {
    return 0;
  }
  return perfcnt[id];
}

void sli_mvp_progcnt_reset(void)
{
  mvp_program_count = 0;
}

uint32_t sli_mvp_progcnt_get(void)
{
  return mvp_program_count;
}

void sli_mvp_pb_begin_loop(sli_mvp_program_context_t *p,
                           int iterations,
                           sl_status_t *status)
{
  if (p->last_loop >= 7) {
    if (status != NULL) {
      *status = SL_STATUS_INVALID_PARAMETER;
    }
    return;
  }

  if ((iterations <= 0) || (iterations > MAX_LOOP_COUNT)) {
    if (status != NULL) {
      *status = SL_STATUS_INVALID_PARAMETER;
    }
    return;
  }

  p->last_loop++;
  sli_mvp_prog_set_loop(p->p,
                        SLI_MVP_LOOP(p->last_loop),
                        iterations,
                        0, 0, 0, 0);
  p->loop_level++;
  // Update loop stack with loop number of current loop level.
  p->loop_stack[p->loop_level] = p->last_loop;
  // Record loop begin bit for instruction.
  p->loop_begin_end[p->last_instr + 1] |= 1 << (p->last_loop << 1);
}

void sli_mvp_pb_begin_program(sli_mvp_program_context_t *p)
{
  p->last_loop  = -1;
  p->last_instr = -1;
  p->loop_level = -1;
  memset(p->loop_begin_end, 0, sizeof(p->loop_begin_end));
}

void sli_mvp_pb_compute(sli_mvp_program_context_t *p,
                        uint32_t opcode,
                        uint32_t alu_cfg,
                        uint32_t load_cfg,
                        uint32_t store_cfg,
                        sl_status_t *status)
{
  if (p->last_instr >= 7) {
    if (status != NULL) {
      *status = SL_STATUS_INVALID_PARAMETER;
    }
    return;
  }

  p->last_instr++;
  sli_mvp_prog_set_instr(p->p, p->last_instr, opcode, alu_cfg, load_cfg, store_cfg, false);
}

void sli_mvp_pb_config_array_full(sli_mvp_program_t *prog,
                                  uint8_t index,
                                  void *addr,
                                  sli_mvp_datatype_t type,
                                  unsigned short vecs,
                                  unsigned short rows,
                                  unsigned short cols,
                                  int vecstride,
                                  int rowstride,
                                  int colstride,
                                  sl_status_t *status)
{
  if (index >= MAX_NUM_ARRAYS) {
    if (status != NULL) {
      *status = SL_STATUS_INVALID_PARAMETER;
    }
    return;
  }

  if ((vecs > MAX_ARRAY_DIM_SIZE)
      || (rows > MAX_ARRAY_DIM_SIZE)
      || (cols > MAX_ARRAY_DIM_SIZE)
      || (vecstride < MIN_ARRAY_STRIDE_SIZE || vecstride > MAX_ARRAY_STRIDE_SIZE)
      || (rowstride < MIN_ARRAY_STRIDE_SIZE || rowstride > MAX_ARRAY_STRIDE_SIZE)
      || (colstride < MIN_ARRAY_STRIDE_SIZE || colstride > MAX_ARRAY_STRIDE_SIZE)) {
    if (status != NULL) {
      *status = SL_STATUS_INVALID_RANGE;
    }
    return;
  }

  sli_mvp_prog_set_array_full(prog, index, addr, type,
                              vecs, rows, cols,
                              vecstride, rowstride, colstride);
}

void sli_mvp_pb_config_array_nhwc(sli_mvp_program_t *prog,
                                  uint8_t index,
                                  void *addr,
                                  sli_mvp_datatype_t type,
                                  unsigned short h,
                                  unsigned short w,
                                  unsigned short c,
                                  sl_status_t *status)
{
  sli_mvp_pb_config_array_full(prog, index, addr, type,
                               c,        // vecs (DIM0)
                               h,        // rows (DIM1)
                               w,        // cols (DIM2)
                               1,        // vecstride
                               w * c,    // rowstride
                               c,        // colstride
                               status);
}

void sli_mvp_pb_config_matrix(sli_mvp_program_t *prog,
                              uint8_t index,
                              void *addr,
                              sli_mvp_datatype_t type,
                              unsigned short rows,
                              unsigned short cols,
                              sl_status_t *status)
{
  int colstride = 1;
  int rowstride = cols;
  sli_mvp_pb_config_array_full(prog, index, addr, type,
                               1, rows, cols,
                               0, rowstride, colstride,
                               status);
}

void sli_mvp_pb_config_vector(sli_mvp_program_t *prog,
                              uint8_t index,
                              void *addr,
                              sli_mvp_datatype_t type,
                              unsigned short len,
                              sl_status_t *status)
{
  int colstride = 1;
  sli_mvp_pb_config_array_full(prog, index, addr, type,
                               1, 1, len,
                               0, 0, colstride,
                               status);
}

void sli_mvp_pb_end_loop(sli_mvp_program_context_t *p)
{
  // Record loop end bit for instruction.
  p->loop_begin_end[p->last_instr] |= 2 << (p->loop_stack[p->loop_level] << 1);
  p->loop_level--;
}

void sli_mvp_pb_execute_program(sli_mvp_program_context_t *p)
{
  // Patch instruction loop begin & end bits.
  for (int i = 0; i <= p->last_instr; i++) {
    p->p->INSTR[i].CFG2 = (p->p->INSTR[i].CFG2 & 0xFFFF0000U) | p->loop_begin_end[i];
  }
  // Mark end of program.
  p->p->INSTR[p->last_instr].cfg2.endprog = 1;

  sli_mvp_prog_execute(p->p, false);
  p->prog_index ^= 1;
  p->p = &p->program[p->prog_index];
}

void sli_mvp_pb_init_program(sli_mvp_program_context_t *p)
{
  p->prog_index = 0;
  p->p = &p->program[p->prog_index];
}

void sli_mvp_pb_postloop_incr_dim(sli_mvp_program_context_t *p,
                                  uint8_t array_index,
                                  uint8_t dimension)
{
  p->p->LOOP[p->loop_stack[p->loop_level + 1]].CFG
    |= dimension << ((array_index * 4) + _MVP_LOOPCFG_ARRAY0INCRDIM0_SHIFT);
}

void sli_mvp_pb_postloop_reset_dim(sli_mvp_program_context_t *p,
                                   uint8_t array_index,
                                   uint8_t dimension)
{
  p->p->LOOP[p->loop_stack[p->loop_level + 1]].RST
    |= dimension << ((array_index * 4) + _MVP_LOOPRST_ARRAY0RESETDIM0_SHIFT);
}
