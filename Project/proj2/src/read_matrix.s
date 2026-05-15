.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
# - If malloc returns an error,
#   this function terminates the program with error code 88.
# - If you receive an fopen error or eof, 
#   this function terminates the program with error code 90.
# - If you receive an fread error or eof,
#   this function terminates the program with error code 91.
# - If you receive an fclose error or eof,
#   this function terminates the program with error code 92.
# ==============================================================================
read_matrix:
    # save registers
    addi sp, sp, -28
    sw s1, 28(sp)
    sw s2, 24(sp)
    sw s3, 16(sp)
    sw ra, 12(sp)
    sw a0, 8(sp)
    sw a1, 4(sp)
    sw a2, 0(sp)

    # call fopen
    lw a1, 8(sp)
    li a2, 0
    jal fopen
    # check fopen error
    bge zero, a0, fopen_err
    mv s1, a0

    # call fread, load row and col
    mv a1, s1
    lw a2, 4(sp)
    li a3, 4
    jal fread
    # check fread error
    li t0, 4
    bne a0, t0, fread_err
    mv a1, s1
    lw a2, 0(sp)
    li a3, 4
    jal fread
    # check fread error
    li t0, 4
    bne a0, t0, fread_err

    # calculate size
    lw t0, 4(sp)
    lw t1, 0(sp)
    lw s2, 0(t0)
    lw t0, 0(t1)
    mul s2, s2, t0

    # call malloc
    mv a0, s2
    jal malloc
    mv s3, a0
    # check malloc error
    beq a0, zero, malloc_err
    
    # call fread, load matrix
    mv a1, s1
    mv a2, s3
    mv a3, s2
    jal fread
    # check fread error
    bne a0, s2, fread_err

    # restore registers
    mv a0, s3
    lw ra, 12(sp)
    lw s3, 16(sp)
    lw s2, 24(sp)
    lw s1, 28(sp)
    addi sp, sp, 28
    ret


malloc_err:
    li a1, 88
    jal exit2

fopen_err:
    li a1, 90
    jal exit2

fread_err:
    li a1, 91
    jal exit2

fclose_err:
    li a1, 92
    jal exit2
