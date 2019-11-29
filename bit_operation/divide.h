
// round without floatpoint instruction
// 10/3 -> 3, 11/3 -> 4
int divide_round_to_int(int numerator,int denominator){
    return (((numerator << 1) / denominator) + 1) >> 1;
}
