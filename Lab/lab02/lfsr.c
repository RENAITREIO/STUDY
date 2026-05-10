#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

#define GET_BIT(reg, n)    ((reg & (1 << n)) >> n)

void lfsr_calculate(uint16_t *reg) {
    uint16_t next = GET_BIT(*reg, 0) ^ GET_BIT(*reg, 2) ^ GET_BIT(*reg, 3) ^ GET_BIT(*reg, 5);
    *reg = (next << 15) | (*reg >> 1);
}

