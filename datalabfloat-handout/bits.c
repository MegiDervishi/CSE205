/* 
 * CSE205 Data Lab 
 * 
 * <Megi Dervishi and megi.dervishi>
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
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
  
  You can use arbitrary integer and unsigned constants. You can use any 
arithmetic, logical, or comparison operations on int or unsigned data.

  You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
  cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.

#endif

/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* float */
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {

  int real = uf & 0x7FFFFFFF;
  int fraction = uf &  0x007FFFFF;
  int exponent = real>> 23;
  
  if ((exponent == 0x000000FF) && (!!fraction)){ 
    // if exponent is all 1s and fraction not all zeros
    return uf;
  }
  else {
    return real;
}
}
/* 

 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  //same as the previous function
  int fraction = uf &  0x007FFFFF;
  int exponent = uf & 0x7F800000;

  if ((exponent == 0x7F800000) && (!!fraction)){ 
    // if exponent is all 1s and fraction not all zeros
    return uf;
  }
  else {
    return uf ^ 0x80000000;
}
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  int fraction = uf &  0x007FFFFF;
  int exponent = uf & 0x7F800000;
  int sign = uf & 0x80000000;
  int bias = 0x0000007F;
  int E = (exponent >> 23) - bias;
  int result =  (fraction >> (23 - E)) | 0x00800000;

  if (exponent == 0) {  //when 0+- 
    return 0;
  }
  if (E > 32) { //when overflow and infinity
    return  0x80000000u;
  }
  if (E < 0) { 
    return 0;  
  }
  if (E ==0) { 
    if (sign == 0x80000000) {
      return -1;
    }
    else{
      return 1;
    }
  }
  if (sign == 0x80000000) { //checking the sign of the result
      return -result;
    }
  else{
      return result;
  }
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  int exponent = uf & 0x7F800000; //011111111000...
  int fraction = uf &  0x007FFFFF;
  int sign = uf & 0x80000000;
  if(exponent == 0x7F800000) { 
    //not neccessary to check fraction -> its always impossible
    return uf;
  }
  //when it is +0 
  if(uf==0){
    return 0;
  }
  //when it is -0 
  if (uf == 0x80000000) {
    return 0x80000000;
  }

  if (exponent == 0){ // denormalized case
    return (fraction << 1) | sign; //shift the fraction which will give the exponent a 1 immediately and then u just input the sign
  }
  //increase exponent by 1
	return uf +  0x00800000;
}
