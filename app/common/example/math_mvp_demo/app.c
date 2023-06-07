/***************************************************************************//**
 * @file app.c
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#if defined(SL_CATALOG_STATUS_STRING_PRESENT)
#include "sl_status_string_config.h"
#endif
#include "sl_math_mvp.h"
#include "sl_common.h"
#include <stdio.h>

static float16_t input_a[256] SL_ATTRIBUTE_ALIGN(4);
static float16_t input_b[256] SL_ATTRIBUTE_ALIGN(4);
static float16_t input_c[256] SL_ATTRIBUTE_ALIGN(4);
static float16_t output[256] SL_ATTRIBUTE_ALIGN(4);
static int8_t    byte_buffer[32] SL_ATTRIBUTE_ALIGN(4);

void print_vector(float16_t *data, size_t num_elements)
{
  printf("  ");
  for (size_t i = 0; i < num_elements; i++) {
    printf("(%6.2f),  ", data[i]);
  }
  printf("\n");
}

void print_complex_vector(float16_t *data, size_t num_elements)
{
  printf("  ");
  for (size_t i = 0; i < num_elements; i++) {
    printf("[%6.2f,%6.2f],  ", data[i * 2], data[i * 2 + 1]);
  }
  printf("\n");
}

void print_matrix(sl_math_matrix_f16_t *matrix)
{
  for (size_t rows = 0; rows < matrix->num_rows; rows++) {
    print_vector(&matrix->data[rows * matrix->num_cols], matrix->num_cols);
  }
}

void print_complex_matrix(sl_math_matrix_f16_t *matrix)
{
  for (size_t rows = 0; rows < matrix->num_rows; rows++) {
    print_complex_vector(&matrix->data[rows * matrix->num_cols * 2], matrix->num_cols);
  }
}

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  sl_status_t status;
  sl_status_t err_code;
  char err_string[40];
  sl_math_matrix_f16_t matrix_a;
  sl_math_matrix_f16_t matrix_b;
  sl_math_matrix_f16_t matrix_c;
  sl_math_matrix_f16_t matrix_z;

  printf("=== Math MVP demo ===\n");
  printf("\n");

  printf("Demonstrate various vector and matrix functions that are accelerated by use of the MVP:\n");
  printf("- All numbers are 16-bit floating points.\n");
  printf("- Both scalar and complex numbers are used, and scalar values are printed as (value),\n");
  printf("  while complex numbers are printed as [real, imaginary].\n");
  printf("- Please note that both vectors and matrixes, scalar and complex are using one-dimensional\n");
  printf("  sequential memory for storage.\n");
  printf("- Some operations are similar for vectors and matrixes, and in those cases vector functions\n");
  printf("  will work for matrixes as well.\n");
  printf("\n");

  // Clear any errors frm previous operations.
  sl_math_mvp_clear_errors();

  printf("Fill vector A with 1.0:\n");
  sl_math_mvp_vector_fill_f16(input_a, 1.0f, 6);
  print_vector(input_a, 6);

  printf("Fill vector B with -3.0:\n");
  sl_math_mvp_vector_fill_f16(input_b, -3.0f, 6);
  print_vector(input_b, 6);

  printf("Add vector A and B:\n");
  sl_math_mvp_vector_add_f16(input_a, input_b, output, 6);
  print_vector(output, 6);

  printf("\n");
  printf("Fill vector A with complex values:\n");
  input_a[0] = 1.0;
  input_a[1] = 2.0;
  input_a[2] = 3.0;
  input_a[3] = -4.0;
  input_a[4] = 5.0;
  input_a[5] = 6.0;
  input_a[6] = 7.0;
  input_a[7] = -8.0;
  print_complex_vector(input_a, 4);

  printf("Complex conjugate vector A into vector B:\n");
  sl_math_mvp_complex_vector_conjugate_f16(input_a, input_b, 4);
  print_complex_vector(input_b, 4);

  printf("Complex multiplicate vector A with vector B:\n");
  sl_math_mvp_complex_vector_mult_f16(input_a, input_b, output, 4);
  print_complex_vector(output, 4);

  printf("Add vector A to the result:\n");
  sl_math_mvp_vector_add_f16(input_a, output, output, 8);
  print_complex_vector(output, 4);

  printf("Clip the result to -5..10:\n");
  sl_math_mvp_vector_clip_f16(output, output, -5.0, 10.0, 8);
  print_complex_vector(output, 4);

  printf("\n");
  printf("Fill matrix A with values:\n");
  input_a[0] = 1.0;
  input_a[1] = 2.0;
  input_a[2] = 3.0;
  input_a[3] = -4.0;
  input_a[4] = 5.0;
  input_a[5] = 6.0;
  input_a[6] = 7.0;
  input_a[7] = -8.0;
  input_a[8] = 9.0;
  input_a[9] = 10.0;
  input_a[10] = 11.0;
  input_a[11] = -12.0;
  sl_math_matrix_init_f16(&matrix_a, 3, 4, input_a);
  print_matrix(&matrix_a);

  printf("Transpose matrix A into matrix B:\n");
  sl_math_matrix_init_f16(&matrix_b, 4, 3, input_b);
  sl_math_mvp_matrix_transpose_f16(&matrix_a, &matrix_b);
  print_matrix(&matrix_b);

  printf("Multiply matrix A with matrix B:\n");
  sl_math_matrix_init_f16(&matrix_z, 3, 3, output);
  sl_math_mvp_matrix_mult_f16(&matrix_a, &matrix_b, &matrix_z);
  print_matrix(&matrix_z);

  printf("\n");
  printf("Fill matrix A with complex values:\n");
  input_a[0] = 1.0;
  input_a[1] = 1.5;
  input_a[2] = 2.0;
  input_a[3] = -2.5;
  input_a[4] = 3.0;
  input_a[5] = 3.5;
  input_a[6] = 4.0;
  input_a[7] = -4.5;
  input_a[8] = 5.0;
  input_a[9] = 5.5;
  input_a[10] = 6.0;
  input_a[11] = -6.5;
  input_a[12] = 7.0;
  input_a[13] = 7.5;
  input_a[14] = 8.0;
  input_a[15] = -8.5;
  input_a[16] = 9.0;
  input_a[17] = 9.5;
  input_a[18] = 10.0;
  input_a[19] = -10.5;
  input_a[20] = 11.0;
  input_a[21] = 11.5;
  input_a[22] = 12.0;
  input_a[23] = -12.5;
  sl_math_matrix_init_f16(&matrix_a, 3, 4, input_a);
  print_complex_matrix(&matrix_a);

  printf("Conjugate matrix A into matrix B:\n");
  sl_math_mvp_complex_vector_conjugate_f16(input_a, input_b, 24);
  sl_math_matrix_init_f16(&matrix_b, 3, 4, input_b);
  print_complex_matrix(&matrix_b);

  printf("Complex transpose matrix B into matrix C:\n");
  sl_math_matrix_init_f16(&matrix_c, 4, 3, input_c);
  sl_math_mvp_complex_matrix_transpose_f16(&matrix_b, &matrix_c);
  print_complex_matrix(&matrix_c);

  printf("Complex multiply matrix A with matrix C:\n");
  sl_math_matrix_init_f16(&matrix_z, 3, 3, output);
  sl_math_mvp_complex_matrix_mult_f16(&matrix_a, &matrix_c, &matrix_z);
  print_complex_matrix(&matrix_z);

  printf("\n");
  printf("Demonstrate that none of the previous math library functions gave any errors or exceptions:\n");
  err_code = 0;
  err_string[0] = '\0';
  // Do one function call to get the accumulated status.
  status = sl_math_mvp_vector_fill_f16(input_a, 1.0f, 1);
  printf("  Execution status: expected=%lu, actual=%lu\n", SL_STATUS_OK, status);
  status = sl_math_mvp_get_error(&err_code, err_string, sizeof(err_string));
  printf("  Error status:     expected=%lu, actual=%lu\n", SL_STATUS_NOT_FOUND, status);
  printf("  Exception value:  expected=%lu, actual=%lu\n", (sl_status_t)0, err_code);
  printf("  Exception string: %s\n", err_string);

  printf("\n");
  printf("Demonstrate use of parameter validation:\n");
  status = sl_math_mvp_vector_fill_f16(input_a, 1.0f, 1);
  printf("  Valid parameters,   status: expected=%lu, actual=%lu\n", SL_STATUS_OK, status);
  status = sl_math_mvp_vector_fill_f16(NULL, 1.0f, 1);
  printf("  Invalid parameters, status: expected=%lu, actual=%lu\n", SL_STATUS_INVALID_PARAMETER, status);

#if !defined(SL_CATALOG_STATUS_STRING_PRESENT) || (SL_STATUS_STRING_ENABLE_COMPUTE == 0)
  printf("\n");
  printf("Please note: To get an error string from the sl_math_mvp_get_error function,\n");
  printf("             the status_string component must be included to the project.\n");
#endif

  printf("\n");
  printf("Demonstrate detection of numerical overflow:\n");
  byte_buffer[0] = 100;
  byte_buffer[1] = 100;
  status = sl_math_mvp_vector_add_i8(&byte_buffer[0], &byte_buffer[1], &byte_buffer[2], 1);
  printf("  Execution status: expected=%lu, actual=%lu\n", SL_STATUS_OK, status);
  err_code = 0;
  status = sl_math_mvp_get_error(&err_code, err_string, sizeof(err_string));
  printf("  Error status:     expected=%lu, actual=%lu\n", SL_STATUS_OK, status);
  printf("  Exception value:  expected=%lu, actual=%lu\n", SL_STATUS_COMPUTE_MATH_OVERFLOW, err_code);
  printf("  Exception string: %s\n", err_string);
  status = sl_math_mvp_get_error(&err_code, NULL, 0);
  printf("  Error status:     expected=%lu, actual=%lu\n", SL_STATUS_NOT_FOUND, status);

  printf("\n");
  printf("Demonstrate detection of 'Not a Number', NaN:\n");
  byte_buffer[0] = 0xff;
  byte_buffer[1] = 0xff;
  status = sl_math_mvp_vector_copy_f16((float16_t *)byte_buffer, output, 1);
  printf("  Execution status: expected=%lu, actual=%lu\n", SL_STATUS_OK, status);
  err_code = 0;
  err_string[0] = '\0';
  status = sl_math_mvp_get_error(&err_code, err_string, sizeof(err_string));
  printf("  Error status:     expected=%lu, actual=%lu\n", SL_STATUS_OK, status);
  printf("  Exception value:  expected=%lu, actual=%lu\n", SL_STATUS_COMPUTE_MATH_NAN, err_code);
  printf("  Exception string: %s\n", err_string);
  status = sl_math_mvp_get_error(&err_code, NULL, 0);
  printf("  Error status:     expected=%lu, actual=%lu\n", SL_STATUS_NOT_FOUND, status);

  printf("\n");
  printf("Demonstrate the use of an unaligned address:\n");
  status = sl_math_mvp_vector_fill_f16((float16_t *)&byte_buffer[1], 1.0f, 1);
  printf("  Execution status: expected=%lu, actual=%lu\n", SL_STATUS_FAIL, status);
  status = sli_mvp_get_error(&err_code, err_string, sizeof(err_string));
  printf("  Error code:       expected=%lu, actual=%lu\n", SL_STATUS_COMPUTE_DRIVER_FAULT, err_code);
  printf("  Error string:     %s\n", err_string);
  sli_mvp_clear_error_flags(SLI_MVP_FAULT_FLAG);

  printf("\n");
  printf("Demonstrate the use of an invalid address:\n");
  status = sl_math_mvp_vector_fill_f16((float16_t *)4, 1.0f, 1);
  printf("  Execution status: expected=%lu, actual=%lu\n", SL_STATUS_FAIL, status);
  status = sli_mvp_get_error(&err_code, err_string, sizeof(err_string));
  printf("  Error code:       expected=%lu, actual=%lu\n", SL_STATUS_COMPUTE_DRIVER_FAULT, err_code);
  printf("  Error string:     %s\n", err_string);
  sli_mvp_clear_error_flags(SLI_MVP_FAULT_FLAG);

  printf("\n");
  printf("Demonstrate a sequence of function calls with a math exception in the first, the last is good:\n");
  err_code = 0;
  err_string[0] = '\0';
  byte_buffer[0] = 100;
  byte_buffer[1] = 100;
  // Execute one command that will generate a math overflow.
  sl_math_mvp_vector_add_i8(&byte_buffer[0], &byte_buffer[1], &byte_buffer[2], 1);
  byte_buffer[0] = 1;
  byte_buffer[1] = 2;
  // Execute one command that has no math exceptions.
  status = sl_math_mvp_vector_add_i8(&byte_buffer[0], &byte_buffer[1], &byte_buffer[2], 1);
  printf("  Last function,         status: expected=%lu, actual=%lu\n", SL_STATUS_OK, status);
  status = sl_math_mvp_get_error(&err_code, err_string, sizeof(err_string));
  printf("  Get exception, status: expected=%lu, actual=%lu\n", SL_STATUS_OK, status);
  printf("  Exception value:       expected=%lu, actual=%lu\n", SL_STATUS_COMPUTE_MATH_OVERFLOW, err_code);
  printf("  Exception string:      %s\n", err_string);

  printf("\n");
  printf("Demonstrate a sequence of function calls with an error in the first, the last is good:\n");
  err_code = 0;
  err_string[0] = '\0';
  // Execute one command with error.
  sl_math_mvp_vector_fill_f16((float16_t *)4, 1.0f, 1);
  // Execute one command that is OK.
  // If it wasn't for the previous command, this would have returned SL_STATUS_OK.
  status = sl_math_mvp_vector_fill_f16(input_a, 1.0f, 1);
  printf("  Last function,  status: expected=%lu, actual=%lu\n", SL_STATUS_FAIL, status);
  status = sli_mvp_get_error(&err_code, err_string, sizeof(err_string));
  printf("  Get error code, status: expected=%lu, actual=%lu\n", SL_STATUS_OK, status);
  printf("  Error code:             expected=%lu, actual=%lu\n", SL_STATUS_COMPUTE_DRIVER_FAULT, err_code);
  printf("  Error string:           %s\n", err_string);
  sli_mvp_clear_error_flags(SLI_MVP_FAULT_FLAG);

  printf("\n");
  printf("=== Math MVP demo, done. ===\n");
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}
