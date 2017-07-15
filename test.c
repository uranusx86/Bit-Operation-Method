#include <stdio.h>
#include <stdlib.h>
#include "basic/basic_bit_operation.h"

int main()
{
    printf("%x\n", arithmetic_right_shift(0xFFFFFFF8, 2));
    return 0;
}
