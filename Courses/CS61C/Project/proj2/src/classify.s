.globl classify

.text
classify:
    # =====================================
    # COMMAND LINE ARGUMENTS
    # =====================================
    # Args:
    #   a0 (int)    argc
    #   a1 (char**) argv
    #   a2 (int)    print_classification, if this is zero, 
    #               you should print the classification. Otherwise,
    #               this function should not print ANYTHING.
    # Returns:
    #   a0 (int)    Classification
    # Exceptions:
    # - If there are an incorrect number of command line args,
    #   this function terminates the program with exit code 89.
    # - If malloc fails, this function terminats the program with exit code 88.
    #
    # Usage:
    #   main.s <M0_PATH> <M1_PATH> <INPUT_PATH> <OUTPUT_PATH>

    li t0, 5
    bne a0, t0, arg_err

    addi sp, sp, -60
    sw ra, 0(sp)
    sw a2, 4(sp)    # save print_classification
    sw s1, 8(sp)    # save m0 pointer, need free
    sw s2, 12(sp)   # save m1 pointer, need free
    sw s3, 16(sp)   # save input pointer, need free
    sw s4, 20(sp)   # save output pointer, need free
    # 24(sp) m0 row
    # 28(sp) m0 col
    # 32(sp) m1 row
    # 36(sp) m1 col
    # 40(sp) input row
    # 44(sp) input col
    # 48(sp) output file name pointer
    sw s5, 52(sp)   # save tmp0 size, then tmp1 pointer
    sw s6, 56(sp)   # save tmp1 size

	# =====================================
    # LOAD MATRICES
    # =====================================

    lw s1, 4(a1)
    lw s2, 8(a1)
    lw s3, 12(a1)
    lw s4, 16(a1)
    sw s4, 48(sp)

    # Load pretrained m0
    mv a0, s1
    addi a1, sp, 24
    addi a2, sp, 28
    jal read_matrix
    mv s1, a0

    # Load pretrained m1
    mv a0, s2
    addi a1, sp, 32
    addi a2, sp, 36
    jal read_matrix
    mv s2, a0

    # Load input matrix
    mv a0, s3
    addi a1, sp, 40
    addi a2, sp, 44
    jal read_matrix
    mv s3, a0

    # =====================================
    # RUN LAYERS
    # =====================================
    # 1. LINEAR LAYER:    m0 * input
    lw t0, 24(sp)
    lw t1, 44(sp)
    mul s5, t0, t1
    slli a0, s5, 2
    jal malloc
    beq a0, zero, malloc_err
    mv s4, a0

    mv a0, s1
    lw a1, 24(sp)
    lw a2, 28(sp)
    mv a3, s3
    lw a4, 40(sp)
    lw a5, 44(sp)
    mv a6, s4
    jal matmul

    # 2. NONLINEAR LAYER: ReLU(m0 * input)
    mv a0, s4
    mv a1, s5
    jal relu
    mv s5, s4

    # 3. LINEAR LAYER:    m1 * ReLU(m0 * input)
    lw t0, 32(sp)
    lw t1, 44(sp)
    mul s6, t0, t1
    slli a0, s6, 2
    jal malloc
    beq a0, zero, malloc_err
    mv s4, a0

    mv a0, s2
    lw a1, 32(sp)
    lw a2, 36(sp)
    mv a3, s5
    lw a4, 24(sp)
    lw a5, 44(sp)
    mv a6, s4
    jal matmul


    # =====================================
    # WRITE OUTPUT
    # =====================================
    # Write output matrix
    lw a0, 48(sp)
    mv a1, s4
    lw a2, 32(sp)
    lw a3, 44(sp)
    jal write_matrix


    # =====================================
    # CALCULATE CLASSIFICATION/LABEL
    # =====================================
    # Call argmax
    mv a0, s4
    mv a1, s6
    jal argmax
    mv s6, a0

    # Print classification
    lw t0, 4(sp)
    bne t0, zero, continue
    mv a1, s6
    jal print_int

    # Print newline afterwards for clarity
    li a1, '\n'
    jal print_char

continue:
    # free memory
    mv a0, s1
    jal free
    mv a0, s2
    jal free
    mv a0, s3
    jal free
    mv a0, s4
    jal free
    mv a0, s5
    jal free


    # restore registers
    mv a0, s6
    lw ra, 0(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    lw s3, 16(sp)
    lw s4, 20(sp)
    lw s5, 52(sp)
    lw s6, 56(sp)
    addi sp, sp, 60
    ret


arg_err:
    li a1, 89
    jal exit2

malloc_err:
    li a1, 88
    jal exit2
