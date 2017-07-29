#include <stdio.h>
#include <stdlib.h>
#include "basic/basic_bit_operation.h"

int main()
{
    printf("%x\n", swap_inside_section(0xA6, 5, 0x7));
    return 0;
}
