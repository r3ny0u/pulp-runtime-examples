#include <stdio.h>
#include <stdint.h>
#include <pulp.h>

#define CUSTOM_AXI_IP_BASE_ADDR  0x1A400000  // Replace this with the actual base address of your IP

// Define offsets for the registers
#define REG0_OFFSET  0x00
#define REG1_OFFSET  0x04
#define REG2_OFFSET  0x08
#define REG_EN_OFFSET  0x0C   // Assuming this address is where output data is read

// Function to write to a register in the custom AXI IP
static inline void custom_axi_ip_write(uint32_t offset, uint32_t value) {
    *(volatile uint32_t *)(CUSTOM_AXI_IP_BASE_ADDR + offset) = value;
}

// Function to read from a register in the custom AXI IP
static inline uint32_t custom_axi_ip_read(uint32_t offset) {
    return *(volatile uint32_t *)(CUSTOM_AXI_IP_BASE_ADDR + offset);
}

int main() {
    uint32_t read_value;

    // Write to reg0, reg1, and reg2
    printf("Writing to reg0, reg1, and reg2...\n");
    custom_axi_ip_write(REG_EN_OFFSET, 0x7);  // Enable writing to reg0
    custom_axi_ip_write(REG0_OFFSET, 0x12345678);  // Write some data to reg0
    custom_axi_ip_write(REG1_OFFSET, 0x9ABCDEF0);  // Write some data to reg1
    custom_axi_ip_write(REG2_OFFSET, 0x13579BDF);  // Write some data to reg2

    // Read back the data from reg0, reg1, and reg2
    printf("Reading from reg0, reg1, and reg2...\n");
    read_value = custom_axi_ip_read(REG0_OFFSET);
    printf("Read from reg0: 0x%08X\n", read_value);

    read_value = custom_axi_ip_read(REG1_OFFSET);
    printf("Read from reg1: 0x%08X\n", read_value);

    read_value = custom_axi_ip_read(REG2_OFFSET);
    printf("Read from reg2: 0x%08X\n", read_value);

    // Read output data from the IP
    printf("Reading output data from custom AXI IP...\n");
    read_value = custom_axi_ip_read(REG_EN_OFFSET);
    printf("Read output data: 0x%08X\n", read_value);

    return 0;
}
