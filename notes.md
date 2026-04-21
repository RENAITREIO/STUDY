# CS61C notes
## Intro
great ideas in computer architecture
1. abstraction
2. Moore's Law
3. principle of locality/memory hierarchy
4. parallelism
5. performance measurement & improvement
6. dependability via redundancy

## Number Representation
binary decimal hex

sign and magnitude  
one's complement  
two's complement & bias encoding

## Floating Point
IEEE Standard 754  
$(-1)^S\times (1+\text{Significand}\times 2^{\text{Exponent}-\text{bias}}$

![floating point](pic/float.png)

association and rounding

## RISC-V (RV32)
32 registers: x0 - x31  
x0 always holds value zero

`add x1, x2, x3`  
`sub x1, x2, x3`  
`addi x1, x2, imm`