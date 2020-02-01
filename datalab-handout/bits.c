/* 
 * CSE205 Data Lab 
 * 
 * <Megi Dervishi and userid here>
 * 
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler and the ./driver.pl script 
 *      to check that your solutions conform to the coding rules.
 */

#endif

/* bit manipulation */
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */

int bitAnd(int x, int y) {
  return ~(~x | ~y);
}
/* 
 * upperBits - pads n upper bits with 1's
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) {
  return (!!n << 31) >> (n + ~0);
}
/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x) {
  // The magic number 0x1010101010101 and x will return the sequence of bits that are in the even positions.
  // If there is no bit in even position that means that (magic & x) == 0. 
  // So I use !!(magic & x) which returns 1 if (magic & x) != 0
  int magic = 0x55;
  magic |= magic << 8;
  magic |= magic << 16; // 0x1010101010101 
  return !!(x & magic); // 1 if n != 0 else 0
}
/* 
 * byteSwap - swaps the nth byte and the mth bytse
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEE! ~ & ^ | + << >>FBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */

//I read byte as bit so i solved bit swapping before byte swapping :P

/*int bitswap (int x, int n, int m) {
  int nth = (x >> n) & 1; //get nth bit
  int mth = (x >> m) & 1; //get mth bit
  int b = nth ^ mth; //if (x,y) = (1,1) or (0,0) then b = 0 else 1
  int ns = (b << n) + (b << m); // create the number ns which is b at possition n and position m and 0 elsewhere.
  // Now we want to make the flipping possible when x != y. If x = y (b = 0) then technically there is no flipping happening 
  // Flipping is possible with XOR 1. 
  return x ^ ns;

}*/

//Same principle as Bitswap
int byteSwap(int x, int n, int m) {
  int shifting  = n << 3; // get the nth byte by multiplying n by 8 == n >> (log_2 (8))
  int shifting2 = m << 3; //get the mth byte by multiplying m by 8 == n >> (log_2 (8))

  //COOL combination to optimize and save operations!!!
  int b = ((x >> shifting) ^ (x >> shifting2)) & 0xFF;// b = nth byte ^ mth byte 
  int ns = (b << shifting) + (b << shifting2); // computing the string of the form "000...0b0...0b0...0" where b byte is on the nth and mth byte
  return x ^ ns; //flipping as in bitswap
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // "if x == 0 then z else y".
  // In other words I will get (y) or (z) depending on (x beign 1 or 0).
  // If x == 1 then I want to return (111111.. & y)
  // If x == 0 then I want to return (111111.. & z)
  // To create the number 111111 or 000000 I use the magic trick below.
  int magic_trick = !x + ~ 0; // if !x = 1 then magic = 0001 + 11111 = 0000 else 0, magic = 0000 + 1111  = 1111
  return (magic_trick & y) | ((~magic_trick) & z); // if 0 then z else y
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // (48 <= x)  and  (x <= 57)
  return ((48 + ~x) & (x + ~57)) >> 31 & 1;
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */

int bitCount(int x) {
  // DONE !!!
  // Divide and conquer using the string combination for all possible divisions
  int count = 0;

  //s16  =       00000000 0000 0000       11111111 11111111
  //s8   =       00000000 1111 1111       00000000 11111111
  //s4   =       00001111 0000 1111       00001111 00001111
  //s2   =       00110011 0011 0011       00110011 00110011
  //s1   =       01010101 0101 0101       01010101 01010101

  //int s1_ = 0x55;
  //int s11 = s1_ | (s1_  << 8);
  //int s1 = s11 | (s11 << 16);

  //int s2_  = 0x33;
  //int s21 = s2_ | (s2_ << 8);
  //int s2 = s21 | (s21 << 16);

  //int s8_ = 0xFF;
  //int s8 = s8_ | (s8_ << 16); 

  //int s16_ = 0xFF;
  //int s16 = s16_| (s16_ << 8);

  int s4_ = 0x0F;
  int s41 = s4_ | (s4_ << 8);
  int s4 =  s41 | (s41 <<16);

  int s2r = s4 << 2;
  int s2 = s2r ^ s4;

  int s1r = s2 << 1;
  int s1 = s1r ^ s2;


  //printf("%08X   %08X   %08X    %08X   %08X  ", s1, s2, s4, s8, s16);

  /*idea :  you start from the bottom to top and you "merge" your array to obtain the counting
            By merging I mean representing e.g 2 1-bits into 1 2-bits; 2 2-bits into 1 4-bits and so on
            01 -> 0+1 -> 01 
            00 -> 0+0 -> 00
            10 -> 1+0 -> 01
            11 -> 1+1 -> 10
            To make this addition one needs to access the bits. In the first algo I do for the first case
            (01 & 01) + ((01 >> 1) & 10) = 01 + 00 = 01
            Recursively you do this for each bit representation until you are left with 2 16-bits and turn it into 1 32-bit
            For the second algorithm we let the first 2 cases the same as the first. 
            The third case 

  */       

  //algorithm 1

  /*count = (x & s1) + ((x >> 1) & s1);
  count = (count & s2) + ((count >> 2) & s2);
  count = (count & s4) + ((count >> 4) & s4);
  count = (count & s8) + ((count >> 8) & s8);
  count = (count & s16) + ((count >> 16) & s16);*/


  // algorithm 2
  //REWRITEN !!!! 
  count = (x & s1) + ((x >> 1) & s1);
  count = (count & s2) + ((count >> 2) & s2);
  count = (count + (count >> 4)) & s4;
  count = count + (count >>8);
  count = count + (count >>16);
  count = count & 63; // 00000000 0000 0000 00000000 00111111

  return count;
}

/* 2's complement */
/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  return ~(1<<31); //0x7FFFFFFF
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */

int fitsBits(int x, int n) {
  // "To fit" means that all the bits are inside the n bits while the rest is 0. 
  // Since the rest is zero if we translate this n-bit-string right and left then I will still obtain the same number.
  // If this number does not fit in n bits then when we shift I will lose some 1s => changing the number.
  // So I basically need to check whether the first and the after-translated number is the same

  int shifting = 33 + ~n;
  //translate the n bit part
  int trans = (x << shifting) >> shifting;
  //if the integer fited in the n bit; after the translation has not changed (equal to x) then return 1 else 0
  return !( x ^ trans); // (x =? y) equiv negation of x ^ y
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */

int addOK(int x, int y) {
  //using truth table to get the desired result one checks if sum has the same sign as x AND y
  //if different signs then overflow(0) else normal(1).
  /*
  
  |X | Y | X+Y | X ^ sum | Y^ sum| Overflow
  |0 | 0 |  1  |  1      | 1     | yes -> 0
  |1 | 1 |  0  |  1      | 1     | yes -> 0
  |0 | 0 |  0  |  0      | 0     | no -> 1
  |1 | 1 |  1  |  0      | 0     | no -> 1
  |0 | 1 |  1  |  1      | 0     | no -> 1
  |1 | 0 |  1  |  0      | 1     | no -> 1
  |0 | 1 |  0  |  0      | 1     | no -> 1
  |1 | 0 |  0  |  1      | 0     | no -> 1

  */

  int s = x +y;
  return !(  ( (x^s)  & (y^s) ) >>31  );

  /*
  int sumth = (x + y) >> 31;
  int yth = y >> 31;
  int xth = x >> 31;
  return !((xth ^ sumth) & (yth ^ sumth));*/

}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */

int isGreater(int x, int y) {
  // x > y = !(y >= x)

  // First thing we take care of the sign of x and y. If sign(x) == sign(y) then x^y =0 so check their difference.
  // So it makes sense to start by finding an expression for x^y = 1 since different signs result to the possibility of overflow.
  // If x ^ y = 1 AND the sign of the difference (y-x) is the same as the sign of y then there is no overflow (no problem).
  // By taking care of cases, which are mentioned below, we observe that (y ^ x) & (dif ^ y) gives a result different from the true value. 
  // so to make them the same I XOR it with !(y-x). 

  // So we have:  x > y ==  !((((y ^ x) & ((y-x) ^ y))>>31&1) ^ (!((y-x)>>31)))
  // To simplify the expression I found out the cool logic relation that !(a ^ !b) = a ^ b
  // SO we have the below result:
  int dif = y + ~x + 1;
  return (  (  (y ^ x) & (dif ^ y)  ) ^ dif ) >> 31&1; 
  
  /* //Third Trial
  return !(  (((y ^ x) & ((y-x) ^ y))>>31&1) ^ (!((y-x)>>31))  );
  int yth = (y >> 31) & 1;
  int xth = (x >> 31) & 1;
  int diff = ((y-x) >> 31) & 1;
  return !(  ((yth ^ xth) & (diff ^ yth) ) ^ (!diff)    );*/

  /* // Second Trial
  int xth = (x >> 31) & 1;
  int yth = (y >> 31) & 1;
  return ((xth ^ yth) & (!xth | yth) ) |  (!((x+~y)>>31) & (!xth | yth));
  return ((xth^yth) | !((x+~y)>>31) )  &  (!xth | yth);*/

  /* //First Trial
  return !!(x ^ y) & (conditional((x^y) >> 31 & 1, !(x>> 31), !((x-y)>> 31 & 1))); */


  /* CASES: x^y = 1  & ((x-y)^y)
                                 (x-y)^y     real
  y>0, x<0 , y-x >0                 0          1
  y>0, x<0 , y-x <0 (overflow)      1          1
  y<0, x>0 , y-x <0                 0          0
  y<0, x>0 , y-x >0 (overflow)      1          0

  */
}

/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  // when x is positive, the absolute value is the same i.e there is no flipping (xor 0);
  // when x is negative, then one has to add 11111 and flip the signs using (xor 1111); 
  //  6so we are able to get the relation of below:
  int y = x >> 31; //11111 = 1 if x < 0 else 000000 = 0
  return (x + y) ^ y; // add y and flip x + y
}
