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
#ifndef MBED_FONT_16SEG_H
#define MBED_FONT_16SEG_H

// Segment bit positions for 14 or 16 Segment display using the Philips DVP630 and DVD737 mapping for PT6312
// Modify this table for different 'bit-to-segment' mappings. The ASCII character defines and the FONT_16S const table below 
// will be adapted automatically according to the bit-to-segment mapping. Obviously this will only work when the segment
// mapping is identical for every digit position. This will be the case unless the hardware designer really hates software developers.
//
#define S_A1   0x0001  // Assuming 2 part A segment
#define S_A2   0x0001
#define S_J    0x0002  // Assuming linked J and P segments
#define S_P    0x0002
#define S_H    0x0004
#define S_K    0x0008
#define S_B    0x0010
#define S_F    0x0020
#define S_G2   0x0040  // Assuming 2 part G segment (ie linked G and M segment) 
#define S_G1   0x0080
#define S_C    0x0100
#define S_E    0x0200
#define S_R    0x0400
#define S_N    0x0800
#define S_D1   0x1000  // Assuming 2 part D segment
#define S_D2   0x1000
#define S_COL  0x2000
#define S_S    0x4000
//#define S_DP   0x8000  // Assuming single DP segment

//Mask for blending out and restoring Icons
//One mask pattern will be sufficient assuming that all digits use the same mapping.
#define S_ICON_MSK (S_COL)


// ASCII Font definitions for segments in each character
//
//32 0x20
#define C_SPC  (0x0000)    //Space
#define C_EXC  (S_B | S_C) //!
#define C_QTE  (S_B | S_F) //"
#define C_HSH  (S_B | S_C | S_D1 | S_D2 | S_G1 | S_G2 | S_J | S_P) //#
#define C_DLR  (S_A1 | S_A2 | S_C | S_D1 | S_D2 | S_F | S_G1 | S_G2 | S_J | S_P | S_S) //$
#define C_PCT  (S_C | S_F | S_K | S_R | S_S) //%
//#define C_AMP    (S_A1 | S_C | S_D1 | S_D2 | S_E | S_G1 | S_J | S_H | S_N) // Not correct when J and P are linked
#define C_AMP  (S_C | S_D1 | S_D2 | S_E | S_F | S_G1 | S_H | S_N | S_S) //&
#define C_ACC  (S_B) //'
#define C_LBR  (S_K | S_N) //(
#define C_RBR  (S_H | S_R) //)
#define C_MLT  (S_G1 | S_G2 | S_J | S_P | S_K | S_N | S_H | S_R | S_S)  //*
#define C_PLS  (S_G1 | S_G2 | S_J | S_P | S_S) //+
#define C_CMA  (S_C) //,
#define C_MIN  (S_G1 | S_G2 | S_S) //-
#define C_DOT  (S_C) //.
#define C_RS   (S_K | S_R  | S_S)  // /
//48 0x30 digits
#define C_0    (S_A1 | S_A2 | S_B | S_C  | S_D1 | S_D2 | S_E  | S_F)
#define C_1    (S_B  | S_C)
#define C_2    (S_A1 | S_A2 | S_B | S_D1 | S_D2 | S_E  | S_G1 | S_G2 | S_S)
#define C_3    (S_A1 | S_A2 | S_B | S_C  | S_D1 | S_D2 | S_G2 | S_S)
#define C_4    (S_B  | S_C  | S_F | S_G1 | S_G2 | S_S)
#define C_5    (S_A1 | S_A2 | S_C | S_D1 | S_D2 | S_F | S_G1 | S_G2 | S_S)
#define C_6    (S_A1 | S_A2 | S_C | S_D1 | S_D2 | S_E | S_F  | S_G1 | S_G2 | S_S)
#define C_7    (S_A1 | S_A2 | S_B | S_C)
#define C_8    (S_A1 | S_A2 | S_B | S_C  | S_D1 | S_D2 | S_E | S_F  | S_G1 | S_G2 | S_S)
#define C_9    (S_A1 | S_A2 | S_B | S_C  | S_D1 | S_D2 | S_F | S_G1 | S_G2 | S_S)
//58 0x3A
#define C_COL  (S_D1 | S_D2 | S_G1 | S_G2 | S_S) // :
#define C_SCL  (S_D1 | S_D2 | S_G1 | S_G2 | S_S) // ;
#define C_LT   (S_K  | S_N  | S_S)               // <
#define C_EQ   (S_D1 | S_D2 | S_G1 | S_G2 | S_S) // =
#define C_GT   (S_H  | S_R  | S_S)               // >   
//#define C_QM   (S_A1 | S_A2 | S_B | S_G2 | S_P) // Not correct when J and P are linked
#define C_QM   (S_A1 | S_A2 | S_B | S_G2 | S_R | S_S)  // ?
//64 0x40
//#define C_AT   (S_A1 | S_A2 | S_B  | S_C  | S_D1 | S_D2 | S_E | S_G1  | S_P | S_S) // Not correct when J and P are linked
#define C_AT   (S_A1 | S_A2 | S_B  | S_C  | S_D1 | S_D2 | S_E  | S_G1 | S_S)  // @
#define C_A    (S_A1 | S_A2 | S_B  | S_C  | S_E  | S_F  | S_G1 | S_G2 | S_S)  // Upper case alphabet
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
#define C_Z    (S_A1 | S_A2 | S_D1 | S_D2 | S_K  | S_R  | S_S)
//91 0x5B
#define C_SBL  (S_A1 | S_D1 | S_E  | S_F)  // [
#define C_LS   (S_H  | S_N  | S_S)         // left slash
#define C_SBR  (S_A2 | S_B | S_C | S_D2)   // ]
#define C_PWR  (S_N  | S_R  | S_S)         // ^
#define C_UDS  (S_D1 | S_D2)
#define C_DSH  (S_H)                       // `  
//97 0x61
// a...z No defines provided. Just use the Upper case characters again
//122

//123 0x7B
#define C_CBL  (S_G1 | S_J  | S_P  | S_S)        // {
#define C_OR   (S_J  | S_P  | S_S)               // |
#define C_CBR  (S_G2 | S_J  | S_P  | S_S)        // }
#define C_TLD  (S_B  | S_E  | S_G1 | S_G2 | S_S) // ~
#define C_DEL  (0x0000)

//User Defined Characters (some examples)
#define UDC_SANDHR  (S_A1 | S_A2 | S_D1 | S_D2 | S_H  | S_K | S_N | S_R | S_S)  //Sandhour

#define UDC_WHEEL0  (S_G1 | S_G2 | S_S)  // -
#define UDC_WHEEL1  (S_H  | S_N  | S_S)  /* \ */
#define UDC_WHEEL2  (S_J  | S_P  | S_S)  // |
#define UDC_WHEEL3  (S_K  | S_R  | S_S)  // /
#define UDC_WHEEL4  (S_G1 | S_G2 | S_S)  // -
#define UDC_WHEEL5  (S_H  | S_N  | S_S)  /* \ */
#define UDC_WHEEL6  (S_J  | S_P  | S_S)  // |
#define UDC_WHEEL7  (S_K  | S_R  | S_S)  // /
                                                                          
// Font data selection for transmission to PT6512 memory
#define LO(x)  ( x & 0xFF)
#define HI(x)  ((x >> 8) & 0xFF)


// ASCII Font definition table
//
#define FONT_16S_START     0x20
#define FONT_16S_END       0x7F
//#define FONT_16S_NR_CHARS (FONT_16S_END - FONT_16S_START + 1)
extern const char FONT_16S[][2]; 


// Wheel animation definition table
extern const int WHEEL_ANI[]; 
#endif                         