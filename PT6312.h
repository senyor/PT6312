/* mbed PT6312 Library, for Princeton PT6312 VFD controller
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

#ifndef PT6312_H
#define PT6312_H

/** An interface for driving Princeton PT6312 VFD controller
 *
 * @code
 * #include "mbed.h"
 * 
 * DisplayData_t size is 8 bytes (4 digits max 16 segments) ... 22 bytes (11 digits at max 11 segments) 
 * DisplayData_t size default is 14 bytes (7 digits max 15 segments) 
 * PT6312::DisplayData_t mbed_str = {0xDA,0x00, 0x7C,0x00, 0x3C,0x01, 0xF6,0x00, 0x00,0x00, 0x00,0x00, 0x00,0x00};  
 * PT6312::DisplayData_t all_str  = {0xFF,0x0F, 0xFF,0x0F, 0xFF,0x0F, 0xFF,0x0F, 0xFF,0x0F, 0xFF,0x0F, 0xFF,0x0F};  
 *
 * // KeyData_t size is 3 bytes  
 * PT6312::KeyData_t keydata; 
 *
 * // PT6191 declaration, Default setting x Digits, y Segments
 * PT6312 PT6312(p5,p6,p7, p8);
 *
 * int main() {
 *   PT6312.cls(); 
 *   PT6312.writeData(all_str);
 *   wait(4);
 *   PT6312.writeData(mbed_str);    
 *   wait(1);
 *   PT6312.setBrightness(PT6312_BRT0);
 *   wait(1);
 *   PT6312.setBrightness(PT6312_BRT3);
 *
 *   while (1) {
 *    // Check and read keydata
 *    if (PT6312.getKeys(&keydata)) {
 *      pc.printf("Keydata 0..2 = 0x%02x 0x%02x 0x%02x\r\n", keydata[0], keydata[1], keydata[2]);
 *
 *      if (keydata[0] == 0x10) { //sw2   
 *        PT6312.cls(); 
 *        PT6312.writeData(all_str);
 *      }  
 *    } 
 *   }   
 * }
 * @endcode
 */

//Memory size in bytes for Display and Keymatrix
#define PT6312_DISPLAY_MEM    22
#define PT6312_KEY_MEM         3
//Significant bits Keymatrix data
#define PT6312_KEY_BITS        8 

//Reserved bits for commands
#define PT6312_CMD_MSK      0xE0

//Mode setting command
#define PT6312_MODE_SET_CMD 0x00
#define PT6312_DIG4_SEG16   0x00
#define PT6312_DIG5_SEG16   0x01
#define PT6312_DIG6_SEG16   0x02
#define PT6312_DIG7_SEG15   0x03 //default
#define PT6312_DIG8_SEG14   0x04
#define PT6312_DIG9_SEG13   0x05
#define PT6312_DIG10_SEG12  0x06
#define PT6312_DIG11_SEG11  0x07


//Data setting commands
#define PT6312_DATA_SET_CMD 0x40
#define PT6312_DATA_WR      0x00
#define PT6312_LED_WR       0x01
#define PT6312_KEY_RD       0x02
#define PT6312_SW_RD        0x03
#define PT6312_ADDR_INC     0x00
#define PT6312_ADDR_FIXED   0x04
#define PT6312_MODE_NORM    0x00
#define PT6312_MODE_TEST    0x08

//LED settings data
#define PT6312_LED_MSK      0x0F
#define PT6312_LED1         0x01
#define PT6312_LED2         0x02
#define PT6312_LED3         0x04
#define PT6312_LED4         0x08

//Switch settings data
#define PT6312_SW_MSK       0x0F
#define PT6312_SW1          0x01
#define PT6312_SW2          0x02
#define PT6312_SW3          0x04
#define PT6312_SW4          0x08

//Address setting commands
#define PT6312_ADDR_SET_CMD 0xC0
#define PT6312_ADDR_MSK     0x1F

//Display control commands
#define PT6312_DSP_CTRL_CMD 0x80
#define PT6312_BRT_MSK      0x07
#define PT6312_BRT0         0x00 //Pulsewidth 1/16
#define PT6312_BRT1         0x01
#define PT6312_BRT2         0x02
#define PT6312_BRT3         0x03
#define PT6312_BRT4         0x04
#define PT6312_BRT5         0x05
#define PT6312_BRT6         0x06
#define PT6312_BRT7         0x07 //Pulsewidth 14/16

#define PT6312_BRT_DEF      PT6312_BRT3

#define PT6312_DSP_OFF      0x00
#define PT6312_DSP_ON       0x08


/** A class for driving Princeton PT6312 VFD controller
 *
 * @brief Supports 4 Digits of 16 Segments upto 11 Digits of 11 Segments. Also supports a scanned keyboard of upto 24 keys, 4 switches and 4 LEDs.
 *        SPI bus interface device. 
 */
class PT6312 {
 public:

  /** Enums for display mode */
  enum Mode {
    Dig4_Seg16  = PT6312_DIG4_SEG16,
    Dig5_Seg16  = PT6312_DIG5_SEG16,
    Dig6_Seg16  = PT6312_DIG6_SEG16,
    Dig7_Seg15  = PT6312_DIG7_SEG15,
    Dig8_Seg14  = PT6312_DIG8_SEG14,
    Dig9_Seg13  = PT6312_DIG9_SEG13,
    Dig10_Seg12 = PT6312_DIG10_SEG12,
    Dig11_Seg11 = PT6312_DIG11_SEG11   
  };
  
  /** Datatypes for display and keymatrix data */
  typedef char DisplayData_t[PT6312_DISPLAY_MEM];
  typedef char KeyData_t[PT6312_KEY_MEM];
    
 /** Constructor for class for driving Princeton PT6312 VFD controller
  *
  * @brief Supports 4 Digits of 16 Segments upto 11 Digits of 11 Segments. Also supports a scanned keyboard of upto 24 keys, 4 switches and 4 LEDs.
  *        SPI bus interface device.   
  *  @param  PinName mosi, miso, sclk, cs SPI bus pins
  *  @param  Mode selects either number of Digits and 12 Segments (default 7 Digits, 15 Segments)
  */
  PT6312(PinName mosi, PinName miso, PinName sclk, PinName cs, Mode mode=Dig7_Seg15);
      
  /** Clear the screen and locate to 0
   */ 
  void cls();  

  /** Write databyte to PT6312
   *  @param  int address display memory location to write byte
   *  @param  char data byte written at given address
   *  @return none
   */ 
  void writeData(int address, char data); 
 
  /** Write Display datablock to PT6312
   *  @param  DisplayData_t data Array of PT6312_DISPLAY_MEM (=16) bytes for displaydata (starting at address 0)
   *  @param  length number bytes to write (valide range 0..PT6312_DISPLAY_MEM (=16), starting at address 0)   
   *  @return none
   */   
  void writeData(DisplayData_t data, int length = PT6312_DISPLAY_MEM);


  /** Read keydata block from PT6312
   *  @param  *keydata Ptr to Array of PT6312_KEY_MEM (=3) bytes for keydata
   *  @return bool keypress True when at least one key was pressed
   *
   * Note: Due to the hardware configuration the PT6312 key matrix scanner will detect multiple keys pressed at same time,
   *       but this may result in some spurious keys also being set in keypress data array.
   *       It may be best to ignore all keys in those situations. That option is implemented in this method depending on #define setting.
   */   
  bool getKeys(KeyData_t *keydata);


  /** Read switches from PT6312
   *
   *  @param  none
   *  @return char for switch data (4 least significant bits)
   *
   */   
  char getSwitches();

  /** Set LEDs
    *
    * @param  char leds (4 least significant bits)  
    * @return none
    */
  void setLED (char leds = 0);

  /** Set Brightness
    *
    * @param  char brightness (3 significant bits, valid range 0..7 (1/16 .. 14/14 dutycycle)  
    * @return none
    */
  void setBrightness(char brightness = PT6312_BRT_DEF);
  
  /** Set the Display mode On/off
    *
    * @param bool display mode
    */
  void setDisplay(bool on);
  
 private:  
  SPI _spi;
  DigitalOut _cs;
  Mode _mode;
  char _display;
  char _bright; 
  
  /** Init the SPI interface and the controller
    * @param  none
    * @return none
    */ 
  void _init();

  /** Helper to reverse all command or databits. The PT6312 expects LSB first, whereas SPI is MSB first
    *  @param  char data
    *  @return bitreversed data
    */ 
  char _flip(char data);

  /** Write command and parameter to PT6312
    *  @param  int cmd Command byte
    *  &Param  int data Parameters for command
    *  @return none
    */ 
  void _writeCmd(int cmd, int data);  
};



#define DVP630_NR_DIGITS 7

/** Constructor for class for driving Princeton PT6312 VFD controller as used in Philips DVP630
  *
  * @brief Supports 7 Digits of 15 Segments. Also supports a scanned keyboard of 3 keys, 3 switches and 1 LED.
  *        SPI bus interface device.   
  *  @param  PinName mosi, miso, sclk, cs SPI bus pins
  */
class PT6312_DVP630 : public PT6312, public Stream {
 public:

 /** Constructor for class for driving Princeton PT6312 VFD controller as used in Philips DVP630
   *
   * @brief Supports 7 Digits of 15 Segments. Also supports a scanned keyboard of 3 keys, 3 switches and 1 LED.
   *        SPI bus interface device.   
   * @param  PinName mosi, miso, sclk, cs SPI bus pins
   */
  PT6312_DVP630(PinName mosi, PinName miso, PinName sclk, PinName cs);

#if DOXYGEN_ONLY
    /** Write a character to the LCD
     *
     * @param c The character to write to the display
     */
    int putc(int c);

    /** Write a formatted string to the LCD
     *
     * @param format A printf-style format string, followed by the
     *               variables to use in formatting the string.
     */
    int printf(const char* format, ...);   
#endif

     /** Locate cursor to a screen column
     *
     * @param column  The horizontal position from the left, indexed from 0
     */
    void locate(int column);
    
    /** Clear the screen and locate to 0
     */
    void cls();

   /** Number of screen columns
    *
    * @param none
    * @return columns
    */
    int columns();   

  /** Write Display datablock to PT6312
   *  @param  DisplayData_t data Array of PT6312_DISPLAY_MEM (=16) bytes for displaydata (starting at address 0)
   *  @param  length number bytes to write (valide range 0..DVP630_NR_DIGITS*2 (=14), starting at address 0)   
   *  @return none
   */   
  void writeData(DisplayData_t data, int length = (DVP630_NR_DIGITS*2)) {
    PT6312::writeData(data, length);
  }  


protected:  
    // Stream implementation functions
    virtual int _putc(int value);
    virtual int _getc();

private:
    int _column;
    int _columns;   
    
    DisplayData_t _displaybuffer;
};

#endif