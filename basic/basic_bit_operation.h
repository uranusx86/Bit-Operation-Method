#ifndef BASIC_BIT_OPERATION_H_INCLUDED
#define BASIC_BIT_OPERATION_H_INCLUDED

/***** All example show in binary format *****/

// 0101_1000 => 0101_0000
int clear_rightmost_bit_1(int input){
    return ( input & (input - 1) );
}

// 0101_0111 => 0101_1111
int set_rightmost_bit_0(int input){
    return ( input | (input + 1) );
}

// test is 2^n
// 0000_1000 => true
// only work for unsigned int
int is_exp_of_2(unsigned int input){
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
int is_exp_of_2_minus_1(unsigned int input){
    return ((input & (input+1)) == 0);
}

// 0101_1000 => 0000_1000
int get_rightmost_1_pos(int input){
    return ( input & (-input) );
}

// 1010_0111 => 0000_1000
int get_rightmost_0_pos(int input){
    return ( (~input) & (input+1) );
}

// 0101_1000 => 0000_0111
int get_last_continuous_0_pos(int input){
    return ( (~input) & (input-1) );
}

// 0101_1000 => 0000_1111
int get_last_1_continuous_0_pos(int input){
    return ( input ^ (input-1) );
}

// 0101_1000 => 0101_1111
int broadcast_rightmost_1_to_right(int input){
    return ( input | (input-1) );
}

// 0101_1000 => 0100_0000
int clear_rightmost_continuous_1(int input){
    return ((  (input | (input-1)) + 1) & input);
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

// -43 => 43
int absolute(int input){
    int y = input >> 31;
    return ( input - ((input<<1) & y) );
}

#endif // BASIC_BIT_OPERATION_H_INCLUDED
