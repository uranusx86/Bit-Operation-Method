#include <stdio.h>
#include <stdlib.h>
#include "bit_operation/basic_bit_operation.h"
#include "bit_operation/exp_2_boundary_operation.h"
#include "bit_operation/arithmetic_bound.h"

int main()
{
    printf("%d\n", check_in_offset_unsigned_bit_range(8,0,3));
    return 0;
}
