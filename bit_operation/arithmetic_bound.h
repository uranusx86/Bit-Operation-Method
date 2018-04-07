#ifndef ARITHMETIC_BOUND_H_INCLUDED
#define ARITHMETIC_BOUND_H_INCLUDED
#include "basic_bit_operation.h"

typedef struct{
    int min_range;
    int max_range;
} pair_int_int;

// test is min<= x <= max
// x, min, max can be signed integer
bool check_in_bound(int x, int min_, int max_){
    return (unsigned int)(x-min_) <= (unsigned int)(max_-min_);
}

// test is greater equal than min, less than max
bool ge_min_ls_max(int x, int min_, int max_){
    return (unsigned int)(x-min_) < (unsigned int)(max_-min_);
}

// test is greater than min, less equal than max
bool gt_min_le_max(int x, int min_, int max_){
    return (unsigned int)(max_-x) < (unsigned int)(max_-min_);
}

// test is greater than min, less than max
bool gt_min_ls_max(int x, int min_, int max_){
    return (unsigned int)(x-min_-1) < (unsigned int)(max_-min_-1);
}

// test is -2^(n-1) <= x <= 2^(n-1) - 1
bool check_in_signed_bit_range(int x, int bitwidth){
    return (x >>(bitwidth-1)) ==  (x >>31);
}

// test is a <= x <= a + 2^(n-1) - 1
bool check_in_offset_unsigned_bit_range(int x, int a, int bitwidth){
    return ((unsigned int)(x-a) >>bitwidth) ==  0;
}

// a <= x <= b, c <= y <= d,  get  x+y  range
// s is lower bound, t is upper bound
// note if b+d > 2^31, set to 2^31
// if a+c < -2^31, set to -2^31
pair_int_int get_combine_range(int a, int b, int c, int d){
    int s = a + c, t = b + d;
    int u = a & c & ~s & ~(b & d & ~t);
    int v = ((a ^ c) | ~(a ^ s)) & (~b & ~d & t);
    if((u|v) < 0){
        s = 0x80000000;
        t = 0x7FFFFFFF;
    }
    pair_int_int result = {s, t};
    return result;
}

// a <= x <= b, c <= y <= d,  get  x|y  min range
int get_OR_min_range(unsigned int a, unsigned int b, unsigned int c, unsigned int d){
    unsigned int m = 0x80000000, temp;
    while(m != 0){
        if(~a & c & m){
            temp = (a | m) & -m;
            if(temp <= b)   {a = temp;    break;}
        }else if(a & ~c & m){
            temp = (c | m) & -m;
            if(temp <= d)   {c = temp;    break;}
        }
        m = m >>1;
    }
    return a | c;
}

// a <= x <= b, c <= y <= d,  get  x|y  max range
int get_OR_max_range(unsigned int a, unsigned int b, unsigned int c, unsigned int d){
    unsigned int m = 0x80000000, temp;
    while(m != 0){
        if(b & d & m){
            temp = (b - m) | (m - 1);
            if(temp >= a)   {b = temp;    break;}
            temp = (d - m) | (m - 1);
            if(temp >= c)   {d = temp;    break;}
        }
        m = m >>1;
    }
    return b | d;
}

// a <= x <= b, c <= y <= d,  get  x&y  min range
int get_AND_min_range(unsigned int a, unsigned int b, unsigned int c, unsigned int d){
    unsigned int m = 0x80000000, temp;
    while(m != 0){
        if(~a & ~c & m){
            temp = (a | m) & -m;
            if(temp <= b)   {a = temp;    break;}
            temp = (c | m) & -m;
            if(temp <= d)   {c = temp;    break;}
        }
        m = m >>1;
    }
    return a & c;
}

// a <= x <= b, c <= y <= d,  get  x&y  max range
int get_AND_max_range(unsigned int a, unsigned int b, unsigned int c, unsigned int d){
    unsigned int m = 0x80000000, temp;
    while(m != 0){
        if(b & ~d & m){
            temp = (b & -m) | (m - 1);
            if(temp >= a)   {b = temp;    break;}
        }else if(~b & d & m){
            temp = (d & -m) | (m - 1);
            if(temp >= c)   {d = temp;    break;}
        }
        m = m >>1;
    }
    return b&d;
}

// a <= x <= b, c <= y <= d,  get  x^y  min range
int get_XOR_min_range(unsigned int a, unsigned int b, unsigned int c, unsigned int d){
    unsigned int m = 0x80000000, temp;
    while(m != 0){
        if(~a & c & m){
            temp = (a | m) & -m;
            if(temp <= b)   {a = temp; }
        }else if(a & ~c & m){
            temp = (c | m) & -m;
            if(temp <= d)   {c = temp; }
        }
        m = m >>1;
    }
    return a ^ c;
}

// a <= x <= b, c <= y <= d,  get  x^y  max range
int get_XOR_max_range(unsigned int a, unsigned int b, unsigned int c, unsigned int d){
    unsigned int m = 0x80000000, temp;
    while(m != 0){
        if(b & d & m){
            temp = (b - m) | (m - 1);
            if(temp >= a)   {b = temp; }
            else{
                temp = (d - m) | (m - 1);
                if(temp >= c)   {d = temp; }
            }
        }
        m = m >>1;
    }
    return b ^ d;
}

#endif // ARITHMETIC_BOUND_H_INCLUDED
