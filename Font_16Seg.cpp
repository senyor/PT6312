/* mbed VFD Font Library, for Princeton PT6312 VFD controller as used in Philips DVP630
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
#include "Font_16Seg.h"

// ASCII Font definition table for transmission to PT6312
//
//#define FONT_16S_START     0x20
//#define FONT_16S_END       0x7F
//#define FONT_16S_NR_CHARS (FONT_16S_END - FONT_16S_START + 1)
 
const char FONT_16S[][2] = { 
                             {LO(C_SPC), HI(C_SPC)}, //32 0x20, Space
                             {LO(C_EXC), HI(C_EXC)},
                             {LO(C_QTE), HI(C_QTE)},
                             {LO(C_HSH), HI(C_HSH)},
                             {LO(C_DLR), HI(C_DLR)},
                             {LO(C_PCT), HI(C_PCT)},
                             {LO(C_AMP), HI(C_AMP)},
                             {LO(C_ACC), HI(C_ACC)},
                             {LO(C_LBR), HI(C_LBR)},
                             {LO(C_RBR), HI(C_RBR)},                   
                             {LO(C_MLT), HI(C_MLT)},                            
                             {LO(C_PLS), HI(C_PLS)},
                             {LO(C_CMA), HI(C_CMA)},
                             {LO(C_MIN), HI(C_MIN)},
                             {LO(C_DOT), HI(C_DOT)},                             
                             {LO(C_RS), HI(C_RS)},
                             {LO(C_0), HI(C_0)}, //48 0x30
                             {LO(C_1), HI(C_1)},
                             {LO(C_2), HI(C_2)},
                             {LO(C_3), HI(C_3)},
                             {LO(C_4), HI(C_4)},                   
                             {LO(C_5), HI(C_5)},
                             {LO(C_6), HI(C_6)},
                             {LO(C_7), HI(C_7)},
                             {LO(C_8), HI(C_8)},
                             {LO(C_9), HI(C_9)},
                             {LO(C_COL), HI(C_COL)}, //58 0x3A
                             {LO(C_SCL), HI(C_SCL)},
                             {LO(C_LT), HI(C_LT)},
                             {LO(C_EQ), HI(C_EQ)},
                             {LO(C_GT), HI(C_GT)},
                             {LO(C_QM), HI(C_QM)},                             
                             {LO(C_AT), HI(C_AT)}, //64 0x40
                             {LO(C_A), HI(C_A)}, //65 0x41, A
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
                             {LO(C_Z), HI(C_Z)}, //90 0x5A, Z
                             {LO(C_SBL), HI(C_SBL)}, //91 0x5B
                             {LO(C_LS), HI(C_LS)},
                             {LO(C_SBR), HI(C_SBR)},
                             {LO(C_PWR), HI(C_PWR)},
                             {LO(C_UDS), HI(C_UDS)},  
                             {LO(C_ACC), HI(C_ACC)},                             
                             {LO(C_A), HI(C_A)}, //97 0x61, A replacing a
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
                             {LO(C_Z), HI(C_Z)}, // 122 0x7A, Z replacing z
                             {LO(C_CBL), HI(C_CBL)}, // 123 0x7B
                             {LO(C_OR), HI(C_OR)},
                             {LO(C_CBR), HI(C_CBR)},
                             {LO(C_TLD), HI(C_TLD)},
                             {LO(C_DEL), HI(C_DEL)} };// 127                             
  
  
 // Wheel definition table for transmission to PT6312
const int WHEEL_ANI[] = { UDC_WHEEL0,
                          UDC_WHEEL1,
                          UDC_WHEEL2,
                          UDC_WHEEL3,
                          UDC_WHEEL4,
                          UDC_WHEEL5,
                          UDC_WHEEL6,
                          UDC_WHEEL7 };
  