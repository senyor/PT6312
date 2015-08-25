/* mbed VFD Font Library, for Princeton PT6312 VFD controller
 * Copyright (c) 2015, v01: WH, Initial version
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// Segment bit positions for 14 or 16 Segment display following the Philips DVD625 and DVD737 mapping for PT6312
// Modify this table for different hardware. The Font definition table below will be automatically adapted.
#define S_A1   0x0001
#define S_A2   0x0001
#define S_J    0x0002
#define S_P    0x0002
#define S_H    0x0004
#define S_K    0x0008
#define S_B    0x0010
#define S_F    0x0020
#define S_G2   0x0040
#define S_G1   0x0080
#define S_C    0x0100
#define S_E    0x0200
#define S_R    0x0400
#define S_N    0x0800
#define S_D1   0x1000
#define S_D2   0x1000
#define S_COL  0x2000
#define S_S    0x4000
//#define S_DP   0x8000

#define LO(x)  ( x & 0xFF)
#define HI(x)  ((x >> 8) & 0xFF)

// Segment definition for each character

#define C_A    (S_A1 | S_A2 | S_B  | S_C  | S_E  | S_F  | S_G1 | S_G2 | S_S)
#define C_B    (S_A1 | S_A2 | S_B  | S_C  | S_D1 | S_D2 | S_J  | S_P  | S_G2 | S_S)
#define C_C    (S_A1 | S_A2 | S_D1 | S_D2 | S_E  | S_F)
#define C_D    (S_A1 | S_A2 | S_B  | S_C  | S_D1 | S_D2 | S_J  | S_P  | S_S)
#define C_E    (S_A1 | S_A2 | S_D1 | S_D2 | S_E  | S_F  | S_G1 | S_S)
#define C_F    (S_A1 | S_A2 | S_E  | S_F  | S_G1 | S_S)
#define C_G    (S_A1 | S_A2 | S_C  | S_D1 | S_D2 | S_E  | S_F  | S_G2 | S_S)
#define C_H    (S_B  | S_C  | S_E  | S_F  | S_G1 | S_G2 | S_S)
#define C_I    (S_A1 | S_A2 | S_D1 | S_D2 | S_J  | S_P  | S_S)
#define C_J    (S_B  | S_C  | S_D1 | S_D2 | S_E)
#define C_K    (S_E  | S_F  | S_G1 | S_K  | S_N  | S_S)
#define C_L    (S_D1 | S_D2 | S_E  | S_F)
#define C_M    (S_B  | S_C  | S_E  | S_F  | S_H  | S_K  | S_S)
#define C_N    (S_B  | S_C  | S_E  | S_F  | S_H  | S_N  | S_S)
#define C_O    (S_A1 | S_A2 | S_B  | S_C  | S_D1 | S_D2 | S_E  | S_F)
#define C_P    (S_A1 | S_A2 | S_B  | S_E  | S_F  | S_G1 | S_G2 | S_S)
#define C_Q    (S_A1 | S_A2 | S_B  | S_C  | S_D1 | S_D2 | S_E  | S_F  | S_N)
#define C_R    (S_A1 | S_A2 | S_B  | S_E  | S_F  | S_G1 | S_G2 | S_N  | S_S)
#define C_S    (S_A1 | S_A2 | S_C  | S_D1 | S_D2 | S_F  | S_G1 | S_G2 | S_S)
#define C_T    (S_A1 | S_A2 | S_J  | S_P  | S_S)
#define C_U    (S_B  | S_C  | S_D1 | S_D2 | S_E  | S_F)
#define C_V    (S_E  | S_F  | S_R  | S_K  | S_S)
#define C_W    (S_B  | S_C  | S_E  | S_F  | S_N  | S_R  | S_S)
#define C_X    (S_H  | S_K  | S_N  | S_R  | S_S)
//#define C_Y    (S_H | S_K | S_P | S_S) // Not correct when J and P are linked
#define C_Y    (S_B  | S_C  | S_D1 | S_D2 | S_F  | S_G1 | S_G2 | S_S)
#define C_Z    (S_A1 | S_A1 | S_A2 | S_D1 | S_D2 | S_K  | S_R  | S_S)

const char font_16A[][2] = { {LO(C_A), HI(C_A)},
                             {LO(C_B), HI(C_B)},
                             {LO(C_C), HI(C_C)},
                             {LO(C_D), HI(C_D)},
                             {LO(C_E), HI(C_E)},
                             {LO(C_F), HI(C_F)},
                             {LO(C_G), HI(C_G)},
                             {LO(C_H), HI(C_H)},
                             {LO(C_I), HI(C_I)},
                             {LO(C_J), HI(C_J)},                   
                             {LO(C_K), HI(C_K)},
                             {LO(C_L), HI(C_L)},
                             {LO(C_M), HI(C_M)},
                             {LO(C_N), HI(C_N)},
                             {LO(C_O), HI(C_O)},
                             {LO(C_P), HI(C_P)},
                             {LO(C_Q), HI(C_Q)},
                             {LO(C_R), HI(C_R)},
                             {LO(C_S), HI(C_S)},
                             {LO(C_T), HI(C_T)},
                             {LO(C_U), HI(C_U)},
                             {LO(C_V), HI(C_V)},
                             {LO(C_W), HI(C_W)},
                             {LO(C_X), HI(C_X)},
                             {LO(C_Y), HI(C_Y)},
                             {LO(C_Z), HI(C_Z)}};
                          