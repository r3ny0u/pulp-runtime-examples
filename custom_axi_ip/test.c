#include <stdio.h>
#include <stdint.h>
#include <pulp.h>

#define BASE_ADDR 0x1A400000

#define REG0_OFFSET 0x00
#define REG1_OFFSET 0x04
#define REG2_OFFSET 0x08
#define REG_EN_OFFSET 0x0C

void set_reg(uint32_t offset, uint32_t *value) {
    // *addr = value;

    volatile uint32_t *addr = (volatile uint32_t *)(BASE_ADDR + offset);
    
    for (int i = 0; i < 256/32; i++) {
        addr[i] = value[i];
    }
}

void set_en(uint32_t value) {
    volatile uint32_t *addr = (volatile uint32_t *)(BASE_ADDR + REG_EN_OFFSET);
    *addr = value;
}

uint32_t read_reg(volatile uint32_t *addr) {
    return *addr;
}

int main() {
    // Pointers to the IP registers
    uint32_t reg0[32];
    uint32_t reg1[32];
    uint32_t reg2[32];
    uint32_t reg_en[3];

    memset(reg0, 0, sizeof(reg0));
    memset(reg1, 0, sizeof(reg1));
    memset(reg2, 0, sizeof(reg2));
    memset(reg_en, 0, sizeof(reg_en));

    reg0[0] = 3;
    reg_en = 1;

    set_reg(REG0_OFFSET, reg0);
    printf("Reg0_test read: %d\n", read_reg((volatile uint32_t *)(BASE_ADDR + REG0_OFFSET)));
    printf("Reg0_test: %d\n", reg0);
    set_reg(REG1_OFFSET, reg1);
    set_reg(REG2_OFFSET, reg2);
    set_en(reg_en);

    return 0;
}