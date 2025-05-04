#ifndef _TEST_MACROS_H
#define _TEST_MACROS_H

#define SRC1  t5   /* x30: first source operand  */
#define SRC2  t6   /* x31: second source operand */

#define SEXT_IMM(x) ((x) | (-(((x) >> 11) & 1) << 11))

#define TEST_INSERT_NOPS_0
#define TEST_INSERT_NOPS_1  nop; TEST_INSERT_NOPS_0
#define TEST_INSERT_NOPS_2  nop; TEST_INSERT_NOPS_1
#define TEST_INSERT_NOPS_3  nop; TEST_INSERT_NOPS_2
#define TEST_INSERT_NOPS_4  nop; TEST_INSERT_NOPS_3
#define TEST_INSERT_NOPS_5  nop; TEST_INSERT_NOPS_4
#define TEST_INSERT_NOPS_6  nop; TEST_INSERT_NOPS_5
#define TEST_INSERT_NOPS_7  nop; TEST_INSERT_NOPS_6
#define TEST_INSERT_NOPS_8  nop; TEST_INSERT_NOPS_7
#define TEST_INSERT_NOPS_9  nop; TEST_INSERT_NOPS_8
#define TEST_INSERT_NOPS_10 nop; TEST_INSERT_NOPS_9

#define TEST_CASE(testnum, reg, correctval, code... ) \
    code;                                  /* execute test body */ \
    li   t0, correctval;                   /* expected → t0     */ \
    bne  reg, t0, fail;                   /* mismatch → fail   */

// ---------------------------------------------------------------------
// Immediate-operand tests (inst rd, rs1, imm)
// ---------------------------------------------------------------------
#define TEST_IMM_OP(testnum, inst, result, val1, imm)       \
    TEST_CASE(testnum, x3, result,                         \
        li   SRC1, val1;                                   \
        inst x3, SRC1, SEXT_IMM(imm); )

#define TEST_IMM_SRC1_EQ_DEST(testnum, inst, result, val1, imm) \
    TEST_CASE(testnum, SRC1, result,                       \
        li   SRC1, val1;                                   \
        inst SRC1, SRC1, SEXT_IMM(imm); )

#define TEST_IMM_DEST_BYPASS(testnum, nop_cycles, inst, result, val1, imm) \
    TEST_CASE(testnum, x6, result,                         \
        li   x4, 0;                                        \
1:      li   SRC1, val1;                                   \
        inst x3, SRC1, SEXT_IMM(imm);                      \
        TEST_INSERT_NOPS_ ## nop_cycles                    \
        addi x6, x3, 0;                                    \
        addi x4, x4, 1;                                    \
        li   x5, 2;                                        \
        bne  x4, x5, 1b )

#define TEST_IMM_ZEROSRC1(testnum, inst, result, imm)       \
    TEST_CASE(testnum, SRC1, result,                       \
        inst SRC1, x0, SEXT_IMM(imm); )

#define TEST_IMM_SRC1_BYPASS(testnum, nop_cycles, inst, result, val1, imm) \
    TEST_CASE(testnum, x3, result,                         \
        li   x4, 0;                                        \
1:      li   SRC1, val1;                                   \
        TEST_INSERT_NOPS_ ## nop_cycles                    \
        inst x3, SRC1, SEXT_IMM(imm);                      \
        addi x4, x4, 1;                                    \
        li   x5, 2;                                        \
        bne  x4, x5, 1b )

#define TEST_IMM_ZERODEST(testnum, inst, val1, imm)         \
    TEST_CASE(testnum, x0, 0,                              \
        li   SRC1, val1;                                   \
        inst x0, SRC1, SEXT_IMM(imm); )

// ---------------------------------------------------------------------
// Register-operand tests (inst rd, rs1, rs2)
// ---------------------------------------------------------------------
#define TEST_RR_OP(testnum, inst, result, val1, val2)       \
    TEST_CASE(testnum, x3, result,                         \
        li   SRC1, val1;                                   \
        li   SRC2, val2;                                   \
        inst x3, SRC1, SRC2; )

#define TEST_RR_SRC1_EQ_DEST(testnum, inst, result, val1, val2) \
    TEST_CASE(testnum, SRC1, result,                       \
        li   SRC1, val1;                                   \
        li   SRC2, val2;                                   \
        inst SRC1, SRC1, SRC2; )

#define TEST_RR_SRC2_EQ_DEST(testnum, inst, result, val1, val2) \
    TEST_CASE(testnum, SRC2, result,                       \
        li   SRC1, val1;                                   \
        li   SRC2, val2;                                   \
        inst SRC2, SRC1, SRC2; )

#define TEST_RR_SRC12_BYPASS(testnum, s1_nops, s2_nops, inst, result, val1, val2) \
    TEST_CASE(testnum, x3, result,                         \
        li   x4, 0;                                        \
1:      li   SRC1, val1;                                   \
        TEST_INSERT_NOPS_ ## s1_nops                       \
        li   SRC2, val2;                                   \
        TEST_INSERT_NOPS_ ## s2_nops                       \
        inst x3, SRC1, SRC2;                               \
        addi x4, x4, 1;                                    \
        li   x5, 2;                                        \
        bne  x4, x5, 1b )

#define TEST_RR_SRC21_BYPASS(testnum, s1_nops, s2_nops, inst, result, val1, val2) \
    TEST_CASE(testnum, x3, result,                         \
        li   x4, 0;                                        \
1:      li   SRC2, val2;                                   \
        TEST_INSERT_NOPS_ ## s1_nops                       \
        li   SRC1, val1;                                   \
        TEST_INSERT_NOPS_ ## s2_nops                       \
        inst x3, SRC1, SRC2;                               \
        addi x4, x4, 1;                                    \
        li   x5, 2;                                        \
        bne  x4, x5, 1b )

#define TEST_RR_DEST_BYPASS(testnum, nop_cycles, inst, result, val1, val2) \
    TEST_CASE(testnum, x6, result,                         \
        li   x4, 0;                                        \
1:      li   SRC1, val1;                                   \
        li   SRC2, val2;                                   \
        inst x3, SRC1, SRC2;                               \
        TEST_INSERT_NOPS_ ## nop_cycles                    \
        addi x6, x3, 0;                                    \
        addi x4, x4, 1;                                    \
        li   x5, 2;                                        \
        bne  x4, x5, 1b )

#define TEST_RR_ZEROSRC1(testnum, inst, result, val)        \
    TEST_CASE(testnum, SRC2, result,                       \
        li   SRC1, val;                                    \
        inst SRC2, x0, SRC1; )

#define TEST_RR_ZEROSRC2(testnum, inst, result, val)        \
    TEST_CASE(testnum, SRC2, result,                       \
        li   SRC1, val;                                    \
        inst SRC2, SRC1, x0; )

#define TEST_RR_ZEROSRC12(testnum, inst, result)            \
    TEST_CASE(testnum, SRC1, result,                       \
        inst SRC1, x0, x0; )

#define TEST_RR_ZERODEST(testnum, inst, val1, val2)         \
    TEST_CASE(testnum, x0, 0,                              \
        li   SRC1, val1;                                   \
        li   SRC2, val2;                                   \
        inst x0, SRC1, SRC2; )

#define TEST_RR_SRC12_EQ_DEST(testnum, inst, result, val1)  \
    TEST_CASE(testnum, SRC1, result,                       \
        li   SRC1, val1;                                   \
        inst SRC1, SRC1, SRC1; )

#define TEST_DATA \
    /* (empty) */
#endif