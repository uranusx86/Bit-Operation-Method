#ifndef BASIC_BIT_OPERATION_H_INCLUDED
#define BASIC_BIT_OPERATION_H_INCLUDED

// 0101_1000 => 0101_0000
int clear_rightmost_bit_1(int input){
    return ( input & (input - 1) );
}

// 0000_1000 => true
// only work for unsigned int
int test_is_exp_of_2(unsigned int input){
    return (clear_rightmost_bit_1(input) == 0);
}

// 0101_1000 => 3
int cnt_bit_1(int input){
    short cnt = 0;
    while(input){
        cnt++;
        input = clear_rightmost_bit_1(input);
    }
    return cnt;
}

// test 2^n - 1
// 0000_003F => true
// only work for unsigned int
int test_is_exp_of_2_minus_1(unsigned int input){
    return ((input & (input+1)) == 0);
}

// 0101_1000 => 0000_1000
int get_rightmost_1_pos(int input){
    return ( input & (-input) );
}

// 1010_0111 => 0000_1000
/*
int get_rightmost_0_pos(int input){
    return ( (~input) & (input+1) );
}
*/

#endif // BASIC_BIT_OPERATION_H_INCLUDED
