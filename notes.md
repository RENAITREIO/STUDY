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
$(-1)^S\times (1+\text{Significand}\times 2^{\text{Exponent}-\text{bias}})$

![floating point](pic/float.png)

association and rounding

## RISC-V (RV32)
32 registers: x0 - x31  
x0 always holds value zero

`add x1, x2, x3`  
`sub x1, x2, x3`  
`addi x1, x2, imm`

little endian

`lw` `sw`  
`lb` `sb`  
`lbu`

`beq reg1, reg2, L1`  
`bne` `blt` `bge`  
`bltu` `bgeu`

`and x5, x6, x7`  
`andi x5, x6, 2`  
`xor`

`slli x11, x12, 2`  
`sll` `srl` `sra` `srai`

a0-a7 for argument registers(x10-x17) for function calls  
8 argument registers to pass parameters and 2 return values(a0-a1)

ra: one return address register to return to the point of origin(x1)

pseudo-instructions
```asm
mv rd, rs = addi rd, xs, 0
li rd, 13 = addi rd, x0, 13
nop       = addi x0, x0, 0
j Label
```

`jal` `jalr`
