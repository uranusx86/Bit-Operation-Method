#ifndef BASIC_BIT_OPERATION_H_INCLUDED
#define BASIC_BIT_OPERATION_H_INCLUDED

/***** All example show in binary format *****/

// 0111_1000 ==pos 2==> 0111_1100
// position index start from zero
int set_bit(int input, unsigned char pos){
    if(pos > 31)  exit(EXIT_FAILURE);
    return (input |  (0x1<< pos) );
}

// 0111_1000 ==pos 4==> 0110_1000
// position index start from zero
int clear_bit(int input, unsigned char pos){
    if(pos > 31)  exit(EXIT_FAILURE);
    return (input & ( ~(0x1<< pos) ));
}

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

// using n number bit 1, get next large number
// 0000_1111_0000 => 0001_0000_0111
int n_bit1_get_next_large(int input){
    if(input == 0)  return 0;
    int smallest_1 = input & (-input);
    int ripple = input + smallest_1;
    int y = ((ripple ^ input)>>2) / smallest_1;
    return (ripple | y);
}

// 1111_1111_1000 ==right shift 2==> 1111_1111_1110
// in C, if variable is unsigned, right shift is logic version
// if variable is signed, right shift is arithmetic version
// so you dont have to use this function
int arithmetic_right_shift(int input, unsigned char shift){
    if(shift > 31)  exit(EXIT_FAILURE);
    return (((input + 0x80000000) >>shift) - (0x80000000 >>shift));
}

// x<0, return -1
// x=0, return 0
// x>0, return 1
int sign_function(int input){
    return ( (input >>31) | (((unsigned int)(-input)) >>31)   );
}

// -43 => 43
int absolute(int input){
    int y = input >> 31;
    return ( input - ((input<<1) & y) );
}

// 1111_0000 ==left shift 1==> 1110_0001
int circular_left_shift(int input, unsigned char shift){
    if(shift > 31) exit(EXIT_FAILURE);
    return ( (input<< shift) | ((unsigned int)input >>(32-shift)) );
}

// 0000_1111 ==right shift 1==> 1000_0111
int circular_right_shift(int input, unsigned char shift){
    if(shift > 31) exit(EXIT_FAILURE);
    return ( ((unsigned int)input >>shift) | (input<< (32-shift)) );
}

// test x!=y
int x_neq_y(int input1, int input2){
    return ((unsigned int)((input1-input2) | (input2-input1)) >>31);
}

// test x==y
int x_eq_y(int input1, int input2){
    return !x_neq_y(input1, input2);
}

// test x<y
int x_smaller_y(int input1, int input2){
    //return (unsigned int)((input1 & ~input2) | ((~(input1 ^ input2)) & (input1-input2))) >>31;
    return (unsigned int)((input1 >>1) - (input2 >>1) - (~input1 & input2 & 0x1)) >>31;
}

// test x<=y
int x_smaller_eq_y(int input1, int input2){
    return (unsigned int)((input1 | ~input2) & ((input1^input2) | (~(input2-input1)))) >>31;
}

// if x>=y, return x-y
// else return 0
int doz(int input1, int input2){
    int d = input1 - input2;
    return (d & ((~(d ^ ( (input1^input2) & (d^input1) ))) >>31));
}

// return max
int max__(int input1, int input2){
    return input2 + doz(input1, input2);
}

// return min
int min__(int input1, int input2){
    return input1 - doz(input1, input2);
}

#endif // BASIC_BIT_OPERATION_H_INCLUDED
