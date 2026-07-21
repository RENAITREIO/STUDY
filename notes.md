# CS61C notes
## Intro
### great ideas in computer architecture
- abstraction
- Moore's Law
- principle of locality/memory hierarchy
- parallelism
- performance measurement & improvement
- dependability via redundancy

## Number Representation
### signed integers
- sign and magnitude
- one's complement
- two's complement & bias encoding

## Floating Point
### IEEE Standard 754
$(-1)^S\times (1+\text{Significand}\times 2^{\text{Exponent}-\text{bias}})$

![floating point](pic/float.png)

association and rounding

## RISC-V (RV32)
32 registers: x0 - x31
x0 always holds value zero

### instructions
```asm
add x1, x2, x3
sub x1, x2, x3
addi x1, x2, imm

lw sw
lb sb
lbu

beq reg1, reg2, L1
bne blt bge
bltu bgeu

and x5, x6, x7
andi x5, x6, 2
xor

slli x11, x12, 2
sll srl sra srai

jal jalr
```

### calling convention
a0-a7 for argument registers(x10-x17) for function calls\
8 argument registers to pass parameters and 2 return values(a0-a1)

ra: one return address register to return to the point of origin(x1)

`sp` is the stack pointer(x2)

### caller & callee
![caller vs callee](pic/caller-and-callee.png)

### Memory Management
stack starts in 0xbffffff0\
stack must be aligned on 16-byte boundary\
RV32 programs(text segment) in low end(0x00010000)\
static data segment above text for static variables\
use global pointer`gp` to point to static\
RV32 `gq` = 0x10000000\
heap above static

![memory structure](pic/memory.png)

![instructions](pic/instructions.png)

6 basic types of instruction formats
- R-type\
![R](pic/R.png)
- I-type\
![I](pic/I.png)
- S-type\
![S](pic/S.png)
- B-type\
![B](pic/B.png)
- U-type\
![U](pic/U.png)
- J-type\
![J](pic/J.png)

PC-relative addressing

### compressed instructions
ISA support 16-bit compressed instructions\
to enable this, RISCV scales the branch offset by 2 bytes

### special instructions
`LUI` writes the upper 20 bits to the destination with the immediate value. it can be used to load a 32-bit constant into a register.\
`AUIPC` adds the PC to the immediate value and places result in destination register.

## Compiling, Assembling, Linking, and Loading
### assembler directives
- `.text`: Subsequent items put in user text segment (machine code)
- `.data`: Subsequent items put in user data segment (source file data in binary)
- `.globl sym`: Declares sym global and can be referenced from other files
- `.string str`: Store the string str in memory and null-terminate it
- `.word w1…wn`: Store the n 32-bit quantities in successive memory words

### pseudo-instructions
```asm
# pseudo-instruction replacement
nop                 addi x0, x0, 0
mv t0, t1           addi t0, t1, 0
neg t0, t1          sub t0, zero, t1
li t0, imm          addi t0, zero, imm
li t0, t1           addi t0, zero, t1
not t0, t1          xor t0, t1, -1
beqz t0, loop       beq t0, zero, loop
la t0, str          lui t0, str[31:12]
                    addi t0, t0, str[11:0] or
                    auipc t0, str[31:12]
                    addi t0, t0, str[11:0]
j Label
```

## Synchronous Digital System
maximum clock frequency\
max delay = CLK-to-Q delay + CL delay + setup time

## Single-Cycle CPU Control
### CSRs
control and status registers(CSRs) are separate from the register file(x0-x31)\
not in the base ISA, but almost all RISC-V implementations have them\
there can be up to 4096 CSRs

the `CSRRW` is atomic read and write CSR

![CSR-instructions](pic/csr.png)
![CSRi-instructions](pic/csri.png)

```asm
# pseudo-instruction
csrw csr, rs1 = csrrw x0, csr, rs1
csrwi csr, uimm = csrrwi x0, csr, uimm
```

### system instructions
- `ecall`: make requests to OS, such as system calls
- `ebreak`: used by debuggers to transfer control to the debugger
- `fence`: sequences memory and I/O accesses as viewed by other threads or co-processors

## Pipelining
### Performance Measurement
- instruction timing
- progamm execution time
- throughput
- energy per task
> [!note]
> power is not a good measure, because it is not always related to performance

Iron Law:
$\frac{\text{time}}{\text{program}}=\frac{\text{instructions}}{\text{program}}\cdot \frac{\text{cycles}}{\text{instruction}}\cdot \frac{\text{time}}{\text{cycle}}$

CPI(Cycles Per Instruction):
$\frac{\text{cycles}}{\text{instruction}}$

#### instructions per program detemined by
- task
- algorithm
- programming language
- compiler
- instruction set architecture

#### CPI detemined by
- ISA
- processor implementation
- complex instructions
- superscalar processors

#### time per cycle determined by
- processor microachitecture
- technology
- power budget

### Energy Efficiency
![energy in CMOS](pic/energy.png)

energy per task:
$\frac{\text{energy}}{\text{program}}=\frac{\text{instructions}}{\text{program}}\cdot \frac{\text{energy}}{\text{instruction}}=\frac{\text{instructions}}{\text{program}}\cdot CV^2$

Iron Law:
$\text{performance}=\text{power}\cdot \text{energy efficiency}$

### Pipelining
#### pipelining stages
![stages](pic/stages.png)
![pipeline](pic/pipeline.png)

#### control logic:
![control logic](pic/control-logic.png)

#### Hazards
1. structural hazard: a required resource is busy
   - stall
   - add more hardware
2. data hazard: data dependencies between instructions
   - stall
   - forwarding
   - code scheduling: reorder instructions to avoid data hazards

3. control hazard: flow of execution depends on previous instruction\
   for branch:
   - stall for 2 cycles
   - use branch prediction and flush pipeline

### Superscalar Processors
#### increasing processor performance
1. clock rate
   - limited by technology
2. pipelining
   - more potential for hazards
3. superscalar
   - multiple EXUs
   - generally with out of order execution

#### superscalar architecture
![superscalar](pic/superscalar.png)

## Cache
cache is a copy of a subset of main memory, becase of the SRAM is much faster but expensive than DRAM

### locality
- temporal locality
- spatial locality

### cache organization
- registers <-> memory
- cache <-> memory
- memory <-> disk

### cache address
- tag
- index
- offset

### type of cache
- direct mapped
- fully associative
- set associative

### write hit
- write through
- write back

### cache miss
- compulsory miss: first access to a block
- conflict miss: two blocks mapped to the same set
- capacity miss: cache is full

### replacement policy
- LRU
- FIFO
- random

### Average Access Time
T = Hit Time + Miss Penalty × Miss Rate

## OS
### what OS does
- OS is the first program to run on a computer
- find and control hardware
- provide services to user programs
- load and run user programs
- provide isolation between programs

### what OS need from hardware
- memory translation
- protection and privilege
- traps & interrupts

### boot
1. BIOS: find a storage device and load the first sector
2. bootloader: load the OS kernel
3. OS boot: initialize services, drivers, etc.
4. init: launch an application that waits for input in loop

thread: shared memory\
process: separate memory

supervisor mode: can using more instructions

syscall: provide a API for user programs

### Interrupts & Exceptions
interrupt: something external to the running program

exception: something done by the running program

trap: action of servicing interrupt or exception by hardware jump to trap handler code

### multiprogramming
- switches between processes
- set timer, jump into process
- schedule processes

## Virtual Memory
### memory
- DRAM: volatile
- disk
  - SSD
  - HDD
- flash

### memory manager
- map virtual address to physical address
- protection

### paging
page is usually 4KB in many OS\
page table entries: map virtual page to physical page, stored in memory\
so, one lw/sw take **two** memory accesses actualy

### page faults
- is a exception
- cause by accessing a page that is not in memory
  - allocate a new page in memory
  - swap from disk to memory

### page table problems
> 256 processes, each with 32 bits address, each with 4KB pages, page table takes out 1GiB memory

#### options
- increase page size
- hierarchical page table\
  ![hierarchical page table](pic/hierarchical-page-table.png)

### 32-bit RISC-V
![RV32 PTE](pic/RV32-PTE.png)
> [!NOTE]
> PPN[1] + PPN[0] = 12 bits

### TLB
Translation Lookaside Buffer

adress translation is expensive, there are four-level page table in the 64-bit CPU, so we need TLB to speed up the translation

### design
- typically 32-128 entries, usually fully associative
- random or FIFO replacement policy

### cache & TLB
![cache & TLB](pic/cache-tlb.png)

## I/O
need interface to communicate with devices

### interact with devices
define a range of addresses for devices, and map them to the device registers

a simple device has two registers:
- status register
- data register

but the speed of devices is different from the CPU, so we need to use a special way to interact with devices
- polling
- interrupt
- DMA: need DMA engine
   - between L1 cache and CPU\
   free coherency but trash the CPU's working set
   - between last-level cache and main memory\
   dont mess with caches but need to manage coherency
   - dynamic mixing

### example: networking
need NIC and DMA

#### send
1. application copies data to OS buffer
2. OS calculates checksum, starts timer
3. OS sends data to network interface and says start

#### receive
1. OS copies data form network interface to OS buffer
2. OS calculates checksum, if OK, send ACK; if not, delete message
3. if OK, OS copies data to user address space, and send signal to application to continue

## Parallelism
application: machine learning

### Flynn's taxonomy
![Flynn's taxonomy](pic/flynn.png)

### SIMD
Single Instruction Multiple Data

data-level parallelism: operation on multiple data streams
![parallism](pic/parallelism.png)

XMM registers in SSE: 128 bits

#### example
```c
#include <stdio.h>
// header file for SSE compiler intrinsics
#include <emmintrin.h>

// NOTE: vector registers will be represented in
// comments as v1 = [ a | b ]
// where v1 is a variable of type __m128d and
// a, b are doubles

int main(void) {
   // allocate A,B,C aligned on 16-byte boundaries
   double A[4] __attribute__ ((aligned (16)));
   double B[4] __attribute__ ((aligned (16)));
   double C[4] __attribute__ ((aligned (16)));
   int lda = 2;
   int i = 0;
   // declare several 128-bit vector variables
   __m128d c1,c2,a,b1,b2;

   // Initialize A, B, C for example
   /* A =                    (note column order!)
       1 0
       0 1
   */
   A[0] = 1.0; A[1] = 0.0; A[2] = 0.0; A[3] = 1.0;

   /* B =                    (note column order!)
       1 3
       2 4
   */
   B[0] = 1.0; B[1] = 2.0; B[2] = 3.0; B[3] = 4.0;

   /* C =                    (note column order!)
       0 0
       0 0
   */
   C[0] = 0.0; C[1] = 0.0; C[2] = 0.0; C[3] = 0.0;

   // used aligned loads to set
   // c1 = [c_11 | c_21]
   c1 = _mm_load_pd(C+0*lda);
   // c2 = [c_12 | c_22]
   c2 = _mm_load_pd(C+1*lda);

   for (i = 0; i < 2; i++) {
      /* a =
          i = 0: [a_11 | a_21]
          i = 1: [a_12 | a_22]
      */
      a = _mm_load_pd(A+i*lda);
      /* b1 =
          i = 0: [b_11 | b_11]
          i = 1: [b_21 | b_21]
      */
      b1 = _mm_load1_pd(B+i+0*lda);
      /* b2 =
          i = 0: [b_12 | b_12]
          i = 1: [b_22 | b_22]
      */
      b2 = _mm_load1_pd(B+i+1*lda);

      /* c1 =
          i = 0: [c_11 + a_11*b_11 | c_21 + a_21*b_11]
          i = 1: [c_11 + a_21*b_21 | c_21 + a_22*b_21]
      */
      c1 = _mm_add_pd(c1,_mm_mul_pd(a,b1));
      /* c2 =
          i = 0: [c_12 + a_11*b_12 | c_22 + a_21*b_12]
          i = 1: [c_12 + a_21*b_22 | c_22 + a_22*b_22]
      */
      c2 = _mm_add_pd(c2,_mm_mul_pd(a,b2));
   }

   // store c1,c2 back into C for completion
   _mm_store_pd(C+0*lda,c1);
   _mm_store_pd(C+1*lda,c2);

   // print C
   printf("%g,%g\n%g,%g\n",C[0],C[2],C[1],C[3]);
   return 0;
}
```

for RISC-V, use vector extension

### thread-level parallelism
#### multiprocesssor
- shared memory
- cache separation (except L3 cache)

#### thread
a thread is a single stream of instructions\
with a single core, a single cpu can execute many threads by time sharing

#### multicore
- phisical cpu
- logical cpu
- hyperthreading

parallelism
- SIMD: instruction level parallelism
   - implemented in all high perf
- MIMD: thread level parallelism
   - multicore processors
   - suppoerted by OS

#### OpenMP
- a C extension
- multi-threading, shared-memory parallelism

example
```c
#include <stdio.h>
#include <omp.h>
int main()
{
   omp_set_num_threads(4);
   int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
   int N = sizeof(a)/sizeof(int);

   #pragma omp parallel for
   for (int i=0; i<N; i++) {
      printf("thread %d, i = %2d\n",
            omp_get_thread_num(), i);
      a[i] = a[i] + 10 * omp_get_thread_num();
   }

   for (int i=0; i<N; i++) printf("%02d ", a[i]);
   printf("\n");
}
```

#### Fork-Join model
![fork-join](pic/fork-join.png)

to avoid race condition, use lock

#### hardware synchronization
atomic read/write\
read & write in single instruction

RISC-V atomic memory operations
![atomic](pic/atomic.png)

`amoswap.w.aq`\
`amoswap.w.rl`

#### openmp locks
```c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void) {
   omp_lock_t lock;
   omp_init_lock(&lock);

#pragma omp parallel
   {
      int id = omp_get_thread_num();

      // parallel section
      // ...

      omp_set_lock(&lock);
      // start sequential section
      // ...
      printf("id = %d\n", id);

      // end sequential section
      omp_unset_lock(&lock);

      // parallel section
      // ...
   }

   omp_destroy_lock(&lock);
}
```

deadlock

openmp timing\
`double omp_get_wtime(void);`

#### cache coherency
due to multicore with shared memory but cache separation, cache coherency is needed

state for cache coherency
1. shared: other caches may have a copy
2. modified: up-to- date copy in this cache
3. exclusive: no other cache has a copy
4. owner: other caches may have a copy
5. invalid

cache coherency may cause coherency misses

#### Amdahl's law
$\text{speedup} = \frac{1}{s+\frac{(1-s)}{p}}\le\frac{1}{s}$

### MapReduce & Spark
request-level parallelism (RLP)

data-level parallelism (DLP)
- data in memory in parallel
- data on many disks in parallel

#### MapReduce
map: split data into chunks, and map each chunk to a key-value pair\
reduce: group the key-value pairs by key, and reduce the values

#### Spark