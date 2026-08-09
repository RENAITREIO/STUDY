# EECS 151

## Intro
### Dennand Scaling
scale the gate length by a factor of k
![dennd scaling](pic/dennd_scaling.png)

this has ended a decade ago

### design space & optimality
![design space](pic/design_space.png)

### basic design tradeoff
![design tradeoff](pic/design_tradeoff.png)

all design decisions involve tradeoffs between performance, cost, and power

## Design
### implement digital systems
given a functional description and performance, cost and power constraints, come up with and implementation using a set of primitives
### design process
![design process](pic/design_process.png)
### performance
- throughput
- latency
### cost
cost per IC = variable cost per IC + $\frac{\text{fixed cost}}{\text{volume}}$

variable cost = $\frac{\text{cost of die}+\text{cost of die test}+\text{cost of packaging}}{\text{final test yield}}$

cost of die = $\frac{\text{cost of wafer}}{\text{dies per wafer}*\text{yield}}$
### yield
$\text{Y}=\frac{\text{No. of good chips per wafer}}{total no. of chips per wafer}$

$\text{die cost}=\frac{\text{wafer cost}}{\text{dies per wafer}*\text{die yield}}$

$\text{dies per wafer}=\frac{\pi (\text{wafer diameter}/2)^2}{\text{die area}}-\frac{\pi \cdot \text{wafer diameter}}{\sqrt{2\cdot \text{die area}}}$
### defects
$\text{die yield}=(1+\frac{\text{defects per unit area}\cdot \text{die area}}{\alpha})^{-\alpha}$\
$\alpha$ is approximately 3

die cost = $f(\text{die area})^4$

### restoration/regeneration

### implementation alternative
![implementation alternative](pic/implementation_alternative.png)

### FPGA vs ASIC
![fpga vs asic](pic/fpga_vs_asic.png)

## verilog
- structural
- behavioral

### generator
```verilog
...
genvar i;

generate
    for (i=0; i<N; i=i+1) begin: bit
        FullAdder add(.a(A[i]), .b(B[i]), .ci(C[i]), .co(C[i+1]), .r(R[i]));
    end
endgenerate
...
```

## FPGA
use Ball Grid Array (BGA) package

a latch is a 1-bit memory\
![latch](pic/latch.png)

### FPGA programmablility
1. define function of configurable logic blocks (CLBs)
2. establish interconnection between CLBs
3. set other options, such as clock, reset connections, and I/O

### simplified FPGA logic block
- LUT: implement combinational logic fucntion
- register: optionally store output of LUT

![CLB](pic/CLB.png)

### 4-LUT
![4-LUT](pic/4-LUT.png)

## CL