 # See LICENSE for license details.

#*****************************************************************************
# addi.S
#-----------------------------------------------------------------------------
#
# Test addi instruction.
#
#define TEST_FUNC_NAME addi
#define TEST_FUNC_TXT  "addi"
#define TEST_FUNC_RET  addi_ret
#include "riscv_test.h"
#include "test_macros.h"

RVTEST_RV32U
RVTEST_CODE_BEGIN

  #-------------------------------------------------------------
  # Arithmetic tests
  #-------------------------------------------------------------

  TEST_IMM_OP( 2,  addi, 0x00000000, 0x00000000, 0x000 );
  TEST_IMM_OP( 3,  addi, 0x00000002, 0x00000001, 0x001 );
  TEST_IMM_OP( 4,  addi, 0x0000000a, 0x00000003, 0x007 );

  TEST_IMM_OP( 5,  addi, 0xfffff800, 0x00000000, 0x800 );
  TEST_IMM_OP( 6,  addi, 0x80000000, 0x80000000, 0x000 );
  TEST_IMM_OP( 7,  addi, 0x7ffff800, 0x80000000, 0x800 );

  TEST_IMM_OP( 8,  addi, 0x000007ff, 0x00000000, 0x7ff );
  TEST_IMM_OP( 9,  addi, 0x7fffffff, 0x7fffffff, 0x000 );
  TEST_IMM_OP( 10, addi, 0x800007fe, 0x7fffffff, 0x7ff );

  TEST_IMM_OP( 11, addi, 0x800007ff, 0x80000000, 0x7ff );
  TEST_IMM_OP( 12, addi, 0x7ffff7ff, 0x7fffffff, 0x800 );

  TEST_IMM_OP( 13, addi, 0xffffffff, 0x00000000, 0xfff );
  TEST_IMM_OP( 14, addi, 0x00000000, 0xffffffff, 0x001 );
  TEST_IMM_OP( 15, addi, 0xfffffffe, 0xffffffff, 0xfff );

  TEST_IMM_OP( 16, addi, 0x80000000, 0x7fffffff, 0x001 );


  TEST_PASSFAIL

RVTEST_CODE_END

  .data
RVTEST_DATA_BEGIN

  TEST_DATA

RVTEST_DATA_END
