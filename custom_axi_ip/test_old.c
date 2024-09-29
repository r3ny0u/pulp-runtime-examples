#include <stdio.h>
#include <stdint.h>
#include <pulp.h>

#define BASE_ADDR 0x1A400000

#define REG0_OFFSET 0x00
#define REG1_OFFSET 0x04
#define REG2_OFFSET 0x08
#define REG_EN_OFFSET 0x0C
#define REG_STATUS_OFFSET 0x10

void write_reg(volatile uint32_t *addr, uint32_t value) {
    *addr = value;
}

uint32_t read_reg(volatile uint32_t *addr) {
    return *addr;
}

void write_enable(volatile uint32_t *addr, uint32_t value) {
    uint32_t old_value = *addr;
    *addr = value | old_value;
}

int main() {
    // Pointers to the IP registers
    volatile uint32_t *reg0 = (volatile uint32_t *)(BASE_ADDR + REG0_OFFSET);
    volatile uint32_t *reg1 = (volatile uint32_t *)(BASE_ADDR + REG1_OFFSET);
    volatile uint32_t *reg2 = (volatile uint32_t *)(BASE_ADDR + REG2_OFFSET);

    volatile uint32_t *reg_en = (volatile uint32_t *)(BASE_ADDR + REG_EN_OFFSET);

    volatile uint32_t *reg_status = (volatile uint32_t *)(BASE_ADDR + REG_STATUS_OFFSET);

    // Write to the registers
    printf("Writing to the reg0\n");
    write_reg(reg_en, 0x1);
    printf("Wrote to the reg0\n");
    write_reg(reg0, 0x3);

    write_reg(reg1, 0x1);
    write_reg(reg_en, 0x2);
    printf("Writing to the reg1\n");

    write_reg(reg2, 0xFFFFFFFF);
    write_reg(reg_en, 0x4);
    printf("Writing to the reg2\n");

    // Read from the registers
    uint32_t reg0_val = read_reg(reg0);
    uint32_t reg1_val = read_reg(reg1);
    uint32_t reg2_val = read_reg(reg2);
    uint32_t reg_en_val = read_reg(reg_en);

    printf("Reg0: 0x%X\n", reg0_val);
    printf("Reg1: 0x%X\n", reg1_val);
    printf("Reg2: 0x%X\n", reg2_val);
    printf("Reg_en: 0x%X\n", reg_en_val);

    return 0;
}