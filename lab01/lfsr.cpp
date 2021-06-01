#include <iostream>
#include "lfsr.h"

void lfsr_calculate(uint16_t *reg) {
    char lbit = (*reg >> 5) ^ (*reg >> 3) ^
        (*reg >> 2) ^ (*reg & 1);

    *reg = *reg >> 1;
    *reg = (*reg & ~(1 << 15)) | (lbit << 15);
}

