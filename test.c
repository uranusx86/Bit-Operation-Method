#include <stdio.h>
#include <stdlib.h>
#include "bit_operation/basic_bit_operation.h"
#include "bit_operation/exp_2_boundary_operation.h"
#include "bit_operation/arithmetic_bound.h"
#include "bit_operation/calc_bit.h"

int main()
{
    unsigned int arr[] = {0x00000001, 0x0000F000, 0x000000A3};
    printf("%d\n",calc_array_bit1_num(arr, sizeof(arr)/sizeof(unsigned int)));
    return 0;
}
