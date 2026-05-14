.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
# 	a0 (int*) is the pointer to the array
#	a1 (int)  is the # of elements in the array
# Returns:
#	None
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 78.
# ==============================================================================
relu:
    bge zero, a0, exp
    # i
    mv t0, zero

loop_start:
    lw t1, 0(a0)
    bge t1, zero, loop_continue
    sw x0, 0(a0)

loop_continue:
    addi a0, a0, 4
    addi t0, t0, 1

loop_end:
    blt t0, a1, loop_start
	ret

exp:
    li a0, 78
    ret
