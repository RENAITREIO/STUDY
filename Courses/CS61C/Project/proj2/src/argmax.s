.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 77.
# =================================================================
argmax:
    bge zero, a1, exp
    # arr
    mv t0, a0
    # i
    mv t1, zero
    # max idx
    mv a0, zero
    # max val
    lw t3, 0(t0)

loop_start:
    # tmp
    lw t2, 0(t0)
    bge t3, t2, loop_continue
    mv a0, t1
    lw t3, 0(t0)

loop_continue:
    addi t0, t0, 4
    addi t1, t1, 1

loop_end:
    blt t1, a1, loop_start
    ret

exp:
    li a1, 77
    jal exit2