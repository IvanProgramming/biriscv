 #ifndef _RISCV_TEST_H
 #define _RISCV_TEST_H
 
 #define RVTEST_RV32U
 #define TESTNUM      x28               
 
 #ifndef TEST_FUNC_NAME
 # define TEST_FUNC_NAME mytest
 # define TEST_FUNC_TXT  "mytest"
 # define TEST_FUNC_RET  mytest_ret
 #endif
 
 /*-----------------------------------------------------------------------
  *  Code prologue
  *---------------------------------------------------------------------*/
 #define RVTEST_CODE_BEGIN              \
         .text; .globl TEST_FUNC_NAME;  \
         .globl TEST_FUNC_RET;          \
 TEST_FUNC_NAME:                        \
         .balign 4
 
 /*-----------------------------------------------------------------------
  *  PASS / FAIL – restore RA, then return
  *---------------------------------------------------------------------*/
 #define RVTEST_PASS                    \
         li   a0, 0;                    /* success */ \
         ret
 
 #define RVTEST_FAIL                    \
         li   a0, 1;              /* return failed sub‑test */ \
         ret
 
 /*-----------------------------------------------------------------------
  *  Signature section markers (kept for compatibility)
  *---------------------------------------------------------------------*/
 #define RVTEST_CODE_END
 #define RVTEST_DATA_BEGIN  .balign 4
 #define RVTEST_DATA_END
 
 /*-----------------------------------------------------------------------
  *  Universal pass/fail wrapper (requires TESTNUM in x28)
  *---------------------------------------------------------------------*/
 #define TEST_PASSFAIL              \
         bne  x0, TESTNUM, pass;    \
 fail:   RVTEST_FAIL;               \
 pass:   RVTEST_PASS
 
 #endif /* _RISCV_TEST_H */
 