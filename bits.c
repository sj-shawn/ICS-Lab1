/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 周益轩 25303090066
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~x & ~y) & ~(x & y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  return (~x + 1) & (x >> 31);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int s = src << 3;
  int d = dst << 3;
  int mask_d = ~(0x000000FF<<d);
  return (x & mask_d) | (((x >> s) & 0x000000FF) <<d);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  return (x >> n) & ~ (( 1 << 31 ) >> n << 1);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask = 0x0f;
    mask = mask | (mask << 8);
    mask = mask | (mask << 16);
    return ((x & mask) << 4) | ((x >> 4) & mask);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int first_zero = x | (x + 1);
  return  ~first_zero & (first_zero + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  int y = x ^ (x >> 16);
    y = y ^ (y >> 8);
    y = y ^ (y >> 4);
    y = y ^ (y >> 2);
    y = y ^ (y >> 1);
    return (y & 1) ^ 1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int m = n & 31;
  int k = (32 + (~m + 1)) & 31;        
  return ((x >> m) & ~(~0 << k)) | (x << k);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int half = 1 << (n + ~0);               
  int bias = half + ~0 + ((x >> n) & 1);  
  return (x + bias) & ~((1 << n) + ~0);
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int sx = (x >> 31) & 1;
  int sy = (y >> 31) & 1;

  int samesign = !(sx ^ sy);
  int large =((sx ^ sy) & sy) |(samesign & (((y + (~x + 1)) >> 31) & 1));

  int odd = (x ^ y) & 1;

  return (x >> 1) + (y >> 1) + ((x & y & 1) | (large & odd));
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int sx = (x >> 31) & 1;
  int sa = (a >> 31) & 1;
  int sb = (b >> 31) & 1;

  int xa = x + (~a + 1);
  int xb = x + (~b + 1);

  int diffA = sx ^ sa;
  int diffB = sx ^ sb;

  int x_ge_a = (diffA & !sx) | (!diffA & !(xa >> 31));
  int x_le_a = (diffA & sx) | (!diffA & ((xa >> 31) | !xa));

  int x_ge_b = (diffB & !sx) | (!diffB & !(xb >> 31));
  int x_le_b = (diffB & sx) | (!diffB & ((xb >> 31) | !xb));

  return (x_ge_a & x_le_b) | (x_ge_b & x_le_a);
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int sx = x >> 31;
  int x_abs = (x ^ sx) + (sx & 1);

  int m = !!(x_abs >> 29);
  int x_5_abs = (x_abs << 2) + x_abs;
  int n = (x_5_abs >> 31) & 1;

  int overflow = m | n;
  int mask = overflow << 31 >> 31;
  int int_min = 1 << 31;
  int int_max = ~int_min;

  int saturated = (sx & int_min) | (~sx & int_max);
  int result = (x_5_abs ^ sx) + (sx & 1);

  return (mask & saturated) | (~mask & result);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  int sx = (x >> 31) & 1;
  int sy = (y >> 31) & 1;
  int sum_xy = x + y;
  int sxy = (sum_xy >> 31) & 1;

  int pos1 = !(sx | sy) & sxy;
  int neg1 = sx & sy & !sxy;
  int overflow1 = pos1 + (~neg1 + 1);

  int sz = (z >> 31) & 1;
  int sum_xyz = sum_xy + z;
  int sxyz = (sum_xyz >> 31) & 1;

  int pos2 = !(sxy | sz) & sxyz;
  int neg2 = sxy & sz & !sxyz;
  int overflow2 = pos2 + (~neg2 + 1);

  int total_overflow = overflow1 + overflow2;
  return (total_overflow >> 31) | !!total_overflow;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned F = uf & 0x7FFFFF;
  unsigned E = (uf >> 23) & 0xFF;
  unsigned S = uf >> 31;
  unsigned F_3;
  unsigned q;
  unsigned F_new =F;
  unsigned E_new = E;

  if(E == 0xFF){  // NaN与无穷大这两种情况合并，返回原值 
    E_new = E;
    F_new = F;
  }
  else if (E == 0) {
        // 零或非规格化数
        F_3 = (F << 1) + F;
        q = F_3 >> 1;

        // 除以2，正好一半时舍入到偶数
        if ((F_3 & 1u) && (q & 1u)) {
            q++;
        }

        // 必须在舍入之后判断是否进入规格化范围 
        if (q & (1u << 23)) {
            E_new = 1;
        }
        else {
            E_new = 0;
        }

        F_new = q & 0x7FFFFFu;
    }
  else{     // 来判断规格化数的情况
        F = F | (1 << 23);  // 补上隐式1
        F_3 = (F << 1) + F;
        unsigned n = !!(F_3 & (1 << 25));  // 判断是否有进位
        if (n){  // 进位了，最高位在第26位
              E_new = E + 1;
              // 下面开始判断最后一位的保留情况
              if ((F_3 & 1) && (F_3 & 2)){  // 最后两位都是1
              F_new = ((F_3 + 1) >> 2) & 0x7FFFFF;
              }
              else if(!(F_3 & 1) && (F_3 & 2)){ // 最后两位是10，看倒数第三位
                    if (F_3 & 4){  // 倒数第三位为1，进位
                    F_new = ((F_3 >> 2) + 1) & 0x7FFFFF;
                    }
                    else{
                          F_new = (F_3 >> 2) & 0x7FFFFF;
                    }
              }
              else{  // 剩下的情况都不用进位
                    F_new = (F_3 >> 2) & 0x7FFFFF;
              }
        }
        else{ // 没有进位
              E_new = E;
              // 只用考虑最后一位
              if ((F_3 & 1) && (F_3 & 2)){
                    F_new = ((F_3 + 1) >> 1) & 0x7FFFFF;
              }
              else{
                    F_new = (F_3 >> 1) & 0x7FFFFF;
              }
        }
        if (E_new == 0xFFu) {
          // 溢出为无穷大 
          F_new = 0;
        }
      }
  
      return (S << 31) | (E_new << 23) | F_new;
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned F = uf & 0x7FFFFF;
  unsigned E = (uf >> 23) & 0xFF;
  unsigned S = (uf >> 31) & 1;
  unsigned F_new = F;
  unsigned near_int;
  unsigned shift;
  unsigned m;  // 取整后的小数部分 
  unsigned E_new = E;
  if (E == 0xFF){   //NaN 或者 无穷大不变
        E_new = E;
        F_new = F;
  }
  else{
        if (E < (0x7F - 1)){  // 系数最大为2的-2次方,直接返回0
              E_new = 0;
              F_new = 0;  
        }
        else if (E >= (0x7F + 23)){ //没有小数，整数直接保留
              E_new = E;
              F_new = F;
        }  
        else{
              F = F | (1 << 23); // 加上隐式1
              shift = 150 - E; // 需要移动的位数
              near_int = F >> shift;
              m = F & ((1u << shift) - 1);  // 小数部分
              if((near_int & 1) && (m >> (shift - 1))){    // 进位到偶数,超过一半
                    near_int = near_int + 1;
              }
              else if(!(near_int & 1) && (m > (1 << (shift-1)))){ // 刚好中间，进位到偶数
                    near_int = near_int + 1;
              }
              if (near_int == 0) {
                    E_new = 0;
                    F_new = 0;
              }
              else {
                    E_new = E;
                    F_new = near_int << shift;

              if (F_new & (1u << 24)) {
                    F_new >>= 1;
                    E_new++;
              }

              F_new &= 0x7FFFFFu;
              }
        }
  }
  return (S << 31) | (E_new << 23) | F_new;
}
  


// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
    unsigned ux = x;
    unsigned S = ux & 0x80000000u;
    unsigned x_abs;

    unsigned E = 0;
    unsigned F = 0;
    unsigned shift;
    unsigned q;
    unsigned remainder;
    unsigned half;

    int i = 31;
    // 转换成绝对值
    if (S) {
        x_abs = ~ux + 1u;
    }
    else {
        x_abs = ux;
    }

    // 找到最高位的1
    while (i >= 0 && ((x_abs >> i) & 1u) == 0) {
        i--;
    }

    if (i >= 0) {
        E = i + 127;

        if (i <= 23) {
            // 未超过23位+1位隐藏
            F = (x_abs << (23 - i)) & 0x7FFFFFu;
        }
        else {
            // 有效位超过24位，需要舍弃低位。
             
            shift = i - 23;
            q = x_abs >> shift;

            remainder = x_abs & ((1u << shift) - 1u);
            half = 1u << (shift - 1u);

            if ((remainder > half) ||
                ((remainder == half) && (q & 1u))) {
                q++;
            }

            // 处理舍入的进位
            if (q & (1u << 24)) {
                q >>= 1;
                E++;
            }

            // 去除最高位的1
            F = q & 0x7FFFFFu;
        }
    }

    return S | (E << 23) | F;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  return 18;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  return 19;
}
