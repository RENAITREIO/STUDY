.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
# 	d = matmul(m0, m1)
# Arguments:
# 	a0 (int*)  is the pointer to the start of m0 
#	a1 (int)   is the # of rows (height) of m0
#	a2 (int)   is the # of columns (width) of m0
#	a3 (int*)  is the pointer to the start of m1
# 	a4 (int)   is the # of rows (height) of m1
#	a5 (int)   is the # of columns (width) of m1
#	a6 (int*)  is the pointer to the the start of d
# Returns:
#	None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 72.
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 73.
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 74.
# =======================================================
matmul:
    bge zero, a1, exp0
    bge zero, a2, exp0
    bge zero, a4, exp1
    bge zero, a5, exp1
    bne a2, a4, exp2

    addi sp, sp, -48
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw s4, 16(sp)
    sw s5, 20(sp)
    sw s6, 24(sp)
    sw s7, 28(sp)
    sw s8, 32(sp)
    sw ra, 36(sp)

    mv s0, a0      # s0 = m0
    mv s1, a1      # s1 = m0 rows
    mv s2, a2      # s2 = m0 cols
    mv s3, a3      # s3 = m1
    mv s4, a4      # s4 = m1 rows
    mv s5, a5      # s5 = m1 cols
    mv s6, a6      # s6 = d

    li s7, 0       # i = 0

outer_loop_cond:
    bge s7, s1, outer_loop_end

    li s8, 0       # j = 0

inner_loop_cond:
    bge s8, s5, inner_loop_end

    mul t0, s7, s2
    slli t0, t0, 2
    add a0, s0, t0

    slli t1, s8, 2
    add a1, s3, t1

    mv a2, s2
    li a3, 1
    mv a4, s5

    jal ra, dot

    mul t2, s7, s5
    add t2, t2, s8
    slli t2, t2, 2
    add t2, s6, t2
    sw a0, 0(t2)

    addi s8, s8, 1
    j inner_loop_cond

inner_loop_end:
    addi s7, s7, 1
    j outer_loop_cond

outer_loop_end:
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw s4, 16(sp)
    lw s5, 20(sp)
    lw s6, 24(sp)
    lw s7, 28(sp)
    lw s8, 32(sp)
    lw ra, 36(sp)
    addi sp, sp, 48
    ret

exp0:
    li a1, 72
    jal exit2

exp1:
    li a1, 73
    jal exit2

exp2:
    li a1, 74
    jal exit2
