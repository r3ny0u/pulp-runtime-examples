#include <stdio.h>
#include <stdint.h>
#include "pulp.h"
// #include <custom_axi_ip.h>
// #include <custom_axi_ip_driver.h>

// #define BASE_ADDR 0x1A500000

// #define DIN_OFFSET 0x0
// #define DOUT_OFFSET 0x4
// #define ENABLE_OFFSET 0x8
// #define STATUS_OFFSET 0xc

// typedef enum {
//     IDLE = 0,
//     BUSY = 1,
//     DONE = 2,
//     ERROR = 3
// } status_e;

// uint32_t read_reg(uint32_t offset) {
//     return *(volatile uint32_t *)(BASE_ADDR + offset);
// }

// void write_data(uint32_t data) {
//     uint32_t volatile *reg = (uint32_t *)(BASE_ADDR + DIN_OFFSET);
//     *reg = data;
//     asm volatile ("": : : "memory");
// }

// void enable() {
//     uint32_t volatile *reg = (uint32_t *)(BASE_ADDR + ENABLE_OFFSET);
//     *reg = 1;
//     asm volatile ("": : : "memory");
// }

// void test_axi_ip() {
//     uint32_t data = 0x12345678;

//     status_e status;
//     do {
//         status = read_reg(STATUS_OFFSET);
//     } while (status != IDLE);

//     printf("Begin test\n");
//     write_data(data);
//     enable();

//     uint32_t output_data = read_reg(DOUT_OFFSET);
//     uint32_t expected_output_data = data + 1;
//     uint32_t enable = read_reg(ENABLE_OFFSET);
//     status_e current_status = read_reg(STATUS_OFFSET);

//     printf("Output data: %x\n", output_data);
//     printf("Expected output data: %x\n", expected_output_data);
//     printf("Enable: %x\n", enable);
//     printf("Status: %x\n", status);

//     if (output_data == expected_output_data) {
//         printf("Test passed\n");
//     } else {
//         printf("Test failed\n");
//     }
// }

int main() {
    uint32_t din[1];
    uint32_t dout[1];
    memset(din, 0, sizeof(din));
    memset(dout, 0, sizeof(dout));

    din[0] = 0x12345678;

    printf("Begin test\n");
    start_test(din, dout);
    return 0;
}