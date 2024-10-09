#include <stdio.h>
#include <stdint.h>
#include <pulp.h>

#define BASE_ADDR 0x1A400000

#define DATA_OFFSET 0x0
#define ENABLE_OFFSET 0x4
#define STATUS_OFFSET 0x8

typedef enum {
    IDLE = 0,
    BUSY = 1,
    DONE = 2,
    ERROR = 3
} status_e;

void write_reg(uint32_t offset, uint32_t value) {
    *(volatile uint32_t *)(BASE_ADDR + offset) = value;
}

uint32_t read_reg(uint32_t offset) {
    return *(volatile uint32_t *)(BASE_ADDR + offset);
}

void test_axi_ip() {
    uint32_t data = 0x12345678;
    write_reg(DATA_OFFSET, data);

    write_reg(ENABLE_OFFSET, 1);
    printf("Enable after write: %x\n", read_reg(ENABLE_OFFSET));

    status_e status;
    do {
        status = (status_e)read_reg(STATUS_OFFSET);
    } while (status != DONE);

    uint32_t output_data = read_reg(DATA_OFFSET);
    uint32_t expected_output_data = data + 1;
    uint32_t enable = read_reg(ENABLE_OFFSET);

    printf("Output data: %x\n", output_data);
    printf("Expected output data: %x\n", expected_output_data);
    printf("Enable: %x\n", enable);

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