.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
# Exceptions:
# - If you receive an fopen error or eof,
#   this function terminates the program with error code 93.
# - If you receive an fwrite error or eof,
#   this function terminates the program with error code 94.
# - If you receive an fclose error or eof,
#   this function terminates the program with error code 95.
# ==============================================================================
write_matrix:
    # Save registers
    addi sp, sp, -28
    sw s1, 16(sp)
    sw s2, 12(sp)
    sw ra, 8(sp)
    sw a0, 4(sp)
    sw a1, 0(sp)
    sw a2, 20(sp)
    sw a3, 24(sp)

    mul s1, a2, a3

    # call fopen
    lw a1, 4(sp)
    li a2, 1
    jal fopen
    # check fopen error
    bge zero, a0, fopen_err
    mv s2, a0

    # call fwrite
    mv a1, s2
    addi t0, sp, 20
    mv a2, t0
    li a3, 2
    li a4, 4
    jal fwrite
    # check fwrite error
    li t0, 2
    bne a0, t0, fwrite_err

    mv a1, s2
    lw a2, 0(sp)
    mv a3, s1
    li a4, 4
    jal fwrite
    # check fwrite error
    bne a0, s1, fwrite_err

    # call fclose
    mv a0, s2
    jal fclose
    # check fclose error
    bne a0, zero, fclose_err

    # Restore registers
    lw s1, 16(sp)
    lw s2, 12(sp)
    lw ra, 8(sp)
    addi sp, sp, 28

    ret


fopen_err:
    li a1, 93
    jal exit2

fwrite_err:
    li a1, 94
    jal exit2

fclose_err:
    li a1, 95
    jal exit2