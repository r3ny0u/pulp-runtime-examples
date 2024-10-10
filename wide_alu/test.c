#include <stdio.h>
#include "pulp.h"

int main()
{
    printf("Hello World!\n");

    uint32_t a[32];
    uint32_t b[32];
    uint32_t result[64];

    memset(a, 0, sizeof (a));
    memset(b, 0, sizeof (b));
    memset(result, 0, sizeof (result));

    a[0] = 3;
    b[0] = 5;
    set_delay(50);

    wide_multiply(a, b, result);

    printf("Result [0]: %d\n", result[0]);

    return 0;
}