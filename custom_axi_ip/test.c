#include <stdio.h>
#include <stdint.h>
#include <pulp.h>

#define BASE_ADDR 0x1A400000

#define DATA_OFFSET 0x0
#define DATA2_OFFSET 0x4
#define ENABLE_OFFSET 0x8
#define STATUS_OFFSET 0xc

typedef enum {
    IDLE = 0,
    BUSY = 1,
    DONE = 2,
    ERROR = 3
} status_e;

uint32_t read_reg(uint32_t offset) {
    return *(volatile uint32_t *)(BASE_ADDR + offset);
}

void write_data(uint32_t *data) {
    uint32_t volatile *reg0 = (uint32_t *)(BASE_ADDR + DATA_OFFSET);
    uint32_t volatile *reg1 = (uint32_t *)(BASE_ADDR + DATA2_OFFSET);
    *reg0 = data;
    *reg1 = data + 1;
    asm volatile ("": : : "memory");
}

void enable() {
    uint32_t volatile *reg = (uint32_t *)(BASE_ADDR + ENABLE_OFFSET);
    *reg = 1;
    asm volatile ("": : : "memory");
}

void test_axi_ip() {
    uint32_t data = 0x1;

    status_e status;
    do {
        status = read_reg(STATUS_OFFSET);
    } while (status != IDLE);

    write_data(data);
    printf("Data after write: %x\n", read_reg(DATA_OFFSET));
    printf("Data2 after write: %x\n", read_reg(DATA2_OFFSET));

    enable();
    printf("Enable after write: %x\n", read_reg(ENABLE_OFFSET));

    write_data(data);
    printf("Data after write 2: %x\n", read_reg(DATA_OFFSET));
    printf("Data2 after write 2: %x\n", read_reg(DATA2_OFFSET));
    enable();
    printf("Enable after write 2: %x\n", read_reg(ENABLE_OFFSET));

    uint32_t output_data = read_reg(DATA_OFFSET);
    uint32_t expected_output_data = data[0] + 1;
    uint32_t enable = read_reg(ENABLE_OFFSET);
    status_e current_status = read_reg(STATUS_OFFSET);

    printf("Output data: %x\n", output_data);
    printf("Expected output data: %x\n", expected_output_data);
    printf("Enable: %x\n", enable);
    printf("Status: %x\n", status);

    if (output_data == expected_output_data) {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }
}

int main() {
    test_axi_ip();
    return 0;
}