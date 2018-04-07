#ifndef EXP_2_BOUNDARY_OPERATION_H_INCLUDED
#define EXP_2_BOUNDARY_OPERATION_H_INCLUDED
#include "basic_bit_operation.h"

// test is 2^n
// 0000_1000 => true
// only work for unsigned int
int is_exp_of_2(unsigned int input){
    return (clear_rightmost_bit_1(input) == 0);
}

// test 2^n - 1
// 0000_003F => true
// only work for unsigned int
int is_exp_of_2_minus_1(unsigned int input){
    return ((input & (input+1)) == 0);
}

// test result is 2^n - 2^m, n > m
// only work for unsign int
int is_exp_of_2_subtract_exp_of_2(int input1, int input2){
    int input = input1 - input2;
    if(input < 0)
        exit(EXIT_FAILURE);
    else
        return (clear_rightmost_continuous_1(input) == 0);
}

// round 8
// exp_of_2_base: round base, must be exp_of_2
// round_down_up: true, round_up, otherwise.
// 15 == exp_of_2_base=8,round_down ==> 8
// -37 == exp_of_2_base=8,round_up ==> -32
int round_exp_of_2(int input1, short exp_of_2_base, bool round_down_up){
    if(!is_exp_of_2(exp_of_2_base))  exit(EXIT_FAILURE);
    if(round_down_up)  input1 += (exp_of_2_base-1);
    return (input1 & -exp_of_2_base);
}

// find nearest the number of exp of 2
// 37 ==> 32
int floor_2(unsigned int input1){
    // idea: broadcast rightmost 1, let all bit set to 1
    // ex: 100101 => 111111
    input1 |= (input1 >>1);
    input1 |= (input1 >>2);
    input1 |= (input1 >>4);
    input1 |= (input1 >>8);
    input1 |= (input1 >>16);
    return input1 - (input1 >>1);  // 111111 - 11111 = 100000
}
int floor_2_v1(unsigned int input1){
    unsigned int y = 0x80000000;
    while(y > input1)
        y = y >>1;
    return y;
}
int floor_2_v2(unsigned int input1){
    unsigned int y = 0;
    do{
        y = input1;
        input1 = clear_rightmost_bit_1(input1);
    }while(input1 != 0);
    return y;
}

// find nearest the number of exp of 2
// 37 ==> 64
int ceil_2(unsigned int input1){
    // idea: broadcast rightmost 1, let all bit set to 1
    // ex: 100101 => 111111
    input1 -= 1;            // when input1 is exp of 2, need substract 1 first let last step add 1 wont incorrect
    input1 |= (input1 >>1);
    input1 |= (input1 >>2);
    input1 |= (input1 >>4);
    input1 |= (input1 >>8);
    input1 |= (input1 >>16);
    return input1 + 1;  // carry to 100...000
}

#endif // EXP_2_BOUNDARY_OPERATION_H_INCLUDED
