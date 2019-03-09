#ifndef CALC_BIT_H_INCLUDED
#define CALC_BIT_H_INCLUDED

// calculate how many bit 1 in the integer
// 0101_0001 => 3
int calc_bit1_num(int x){
    x = (x & 0x55555555) + ((x >> 1) & 0x55555555);  // (x >> 1) & 0x55555555 instead of using (x & 0xAAAAAAAA)>>1 to prevent one more clock cycle
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
    x = (x & 0x00FF00FF) + ((x >> 8) & 0x00FF00FF);
    x = (x & 0x0000FFFF) + ((x >> 16) & 0x0000FFFF);
    return x;
}
int calc_bit1_num_v1(unsigned int x){
    return x - (x>>1) - (x>>2) - (x>>3) - (x>>4) - (x>>5) - (x>>6) - (x>>7) - (x>>8) -
                    (x>>9) - (x>>10) - (x>>11) - (x>>12) - (x>>13) - (x>>14) - (x>>15) - (x>>16) -
                    (x>>17) - (x>>18) - (x>>19) - (x>>20) - (x>>21) - (x>>22) - (x>>23) - (x>>24) -
                    (x>>25) - (x>>26) - (x>>27) - (x>>28) - (x>>29) - (x>>30) - (x>>31);
}
int calc_bit1_num_v2(unsigned int x){
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x0000003F;
}
int calc_bit1_num_v3(unsigned int x){
    int n = (x >> 1) & 0xDB6DB6DB;   // count bits in
    x = x - n;                                               // each 3-bit
    n = (n >> 1) & 0xDB6DB6DB;         // field
    x = x - n;
    x = (x + (x >> 3)) & 0xC71C71C7;  // 6-bit sum
    x = x % 63;                                            // add 6-bit sum
    return x;
}

// calculate the digit sum
// 123 => 6
// NO EFFICIENCY, just the general form of calc_bit1_num_v1()
int calc_digit_sum(unsigned int x){
    return x - 9*(x/10) - 9*(x/100) - 9*(x/1000) - 9*(x/10000) - 9*(x/100000) - 9*(x/1000000) - 9*(x/10000000) - 9*(x/100000000) - 9*(x/1000000000);
}



#endif // CALC_BIT_H_INCLUDED
