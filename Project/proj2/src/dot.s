.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int vectors
# Arguments:
#   a0 (int*) is the pointer to the start of v0
#   a1 (int*) is the pointer to the start of v1
#   a2 (int)  is the length of the vectors
#   a3 (int)  is the stride of v0
#   a4 (int)  is the stride of v1
# Returns:
#   a0 (int)  is the dot product of v0 and v1
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 75.
# - If the stride of either vector is less than 1,
#   this function terminates the program with error code 76.
# =======================================================

# arr0 t0
# arr1 a1
# len  a2
# inc0 a3
# inc1 a4
# tmp0  t1
# tmp1  t2
# i     t3

dot:
    bge zero, a1, exp
    mv t0, a0
    mv a0, zero
    mv t3, zero
    li t1, 4
    mul a3, a3, t1
    mul a4, a4, t1

loop_start:
    lw t1, 0(t0)
    lw t2, 0(a1)
    mul t1, t1, t2
    add a0, a0, t1

    add t0, t0, a3
    add a1, a1, a4
    addi t3, t3, 1

loop_end:
    blt t3, a2, loop_start
    ret

exp:
    li a0, 76
    ret