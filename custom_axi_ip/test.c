#include <stdio.h>
#include <stdint.h>
// #include <pulp.h>

#define BASE_ADDR 0x1A400000
#define CUSTOM_AXI_IP_DIN_REG_OFFSET 0x00
#define CUSTOM_AXI_IP_DOUT_REG_OFFSET 0x04
#define CUSTOM_AXI_IP_ENABLE_REG_OFFSET 0x08
#define CUSTOM_AXI_IP_STATUS_REG_OFFSET 0x0C

void write_data(uint32_t din) {
    uint32_t volatile *reg = (uint32_t *)(BASE_ADDR + CUSTOM_AXI_IP_DIN_REG_OFFSET);
    // *reg = din;
    *reg = 1;
}

void read_data() {
    uint32_t volatile *reg = (uint32_t *)(BASE_ADDR + CUSTOM_AXI_IP_DOUT_REG_OFFSET);
    printf("Result: %x\n", *reg);
}

void enable() {
    uint32_t volatile *reg = (uint32_t *)(BASE_ADDR + CUSTOM_AXI_IP_ENABLE_REG_OFFSET);
    *reg = 1;
}

void wait() {
    uint32_t volatile *reg = (uint32_t *)(BASE_ADDR + CUSTOM_AXI_IP_STATUS_REG_OFFSET);
    uint32_t status;
    do {
        status = *reg;
    } while (status != 2);
}

void start_test (uint32_t din) {
    printf("Begin test\n");
    // write_data(din);
    *(uint32_t volatile *)(BASE_ADDR + CUSTOM_AXI_IP_DIN_REG_OFFSET) = 0x12345678;
    __asm__ __volatile__ ("" : : : "memory");
    enable();
    // wait();
    // read_data();
}

int main() {
    uint32_t din = 0x1;
    // start_test(din);
    *(uint32_t volatile *)(BASE_ADDR + CUSTOM_AXI_IP_DIN_REG_OFFSET) = 0x12345678;
    __asm__ __volatile__ ("" : : : "memory");
    enable();
    printf("End test\n");
    return 0;
}