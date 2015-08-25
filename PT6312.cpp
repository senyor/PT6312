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
#include "mbed.h" 
#include "PT6312.h"
#include "Font_16Seg.h"

/** Constructor for class for driving Princeton PT6312 VFD controller
 *
 * @brief Supports 4 Digits of 16 Segments upto 10 Digits of 12 Segments. Also supports a scanned keyboard of upto 24 keys, 4 switches and 4 LEDs.
 *        SPI bus interface device. 
 *   
 *  @param  PinName mosi, miso, sclk, cs SPI bus pins
 *  @param  Mode selects either number of Digits and Segments
*/
PT6312::PT6312(PinName mosi, PinName miso, PinName sclk, PinName cs, Mode mode) : _spi(mosi,miso,sclk), _cs(cs), _mode(mode) {

  _init();
}

/** Init the SPI interface and the controller
  * @param  none
  * @return none
  */ 
void PT6312::_init(){
  
//init SPI
  _cs=1;
  _spi.format(8,3); //PT6312 uses mode 3 (Clock High on Idle, Data latched on second (=rising) edge)
//  _spi.frequency(100000);   
  _spi.frequency(500000);     

//init controller  
  _writeCmd(PT6312_MODE_SET_CMD, _mode);                                               // Mode set command

  _display = PT6312_DSP_ON;
  _bright  = PT6312_BRT_DEF; 
  _writeCmd(PT6312_DSP_CTRL_CMD, _display | _bright );                                 // Display control cmd, display on/off, brightness   
  
  _writeCmd(PT6312_DATA_SET_CMD, PT6312_DATA_WR | PT6312_ADDR_INC | PT6312_MODE_NORM); // Data set cmd, normal mode, auto incr, write data  
}   


/** Clear the screen and locate to 0
 */  
void PT6312::cls() {
  
  _cs=0;
  wait_us(1);    
  _spi.write(_flip(PT6312_ADDR_SET_CMD | 0x00)); // Address set cmd, 0
      
  for (int cnt=0; cnt<PT6312_DISPLAY_MEM; cnt++) {
    _spi.write(0x00); // data 
  }
  
  wait_us(1);
  _cs=1;      
  
}  

/** Set Brightness
  *
  * @param  char brightness (3 significant bits, valid range 0..7 (1/16 .. 14/14 dutycycle)  
  * @return none
  */
void PT6312::setBrightness(char brightness){

  _bright = brightness & PT6312_BRT_MSK; // mask invalid bits
  
  _writeCmd(PT6312_DSP_CTRL_CMD, _display | _bright );  // Display control cmd, display on/off, brightness  

}

/** Set the Display mode On/off
  *
  * @param bool display mode
  */
void PT6312::setDisplay(bool on) {
  
  if (on) {
    _display = PT6312_DSP_ON;
  }
  else {
   _display = PT6312_DSP_OFF;
  }
  
  _writeCmd(PT6312_DSP_CTRL_CMD, _display | _bright );  // Display control cmd, display on/off, brightness   
}

/** Write databyte to PT6312
  *  @param  int address display memory location to write byte
  *  @param  char data byte written at given address
  *  @return none
  */ 
void PT6312::writeData(int address, char data) {
  _cs=0;
  wait_us(1);    
  _spi.write(_flip(PT6312_ADDR_SET_CMD | (address & PT6312_ADDR_MSK))); // Set Address cmd
      
  _spi.write(_flip(data)); // data 
  
  wait_us(1);
  _cs=1;         
    
}

/** Write Display datablock to PT6312
  *  @param  DisplayData_t data Array of PT6312_DISPLAY_MEM (=16) bytes for displaydata (starting at address 0)
  *  @return none
  */ 
void PT6312::writeData(DisplayData_t data) {
  _cs=0;
  wait_us(1);    
  _spi.write(_flip(PT6312_ADDR_SET_CMD | 0x00)); // Set Address at 0
      
  for (int idx=0; idx<PT6312_DISPLAY_MEM; idx++) {
    _spi.write(_flip(data[idx])); // data 
  }
  
  wait_us(1);
  _cs=1;         
    
}

/** Read keydata block from PT6312
  *  @param  *keydata Ptr to Array of PT6312_KEY_MEM (=3) bytes for keydata
  *  @return bool keypress True when at least one key was pressed
  *
  * Note: Due to the hardware configuration the PT6312 key matrix scanner will detect multiple keys pressed at same time,
  *       but this may also result in some spurious keys being set in keypress data array.
  *       It may be best to ignore all keys in those situations. That option is implemented in this method depending on #define setting.  
  */ 
bool PT6312::getKeys(KeyData_t *keydata) {
  int keypress = 0;
  char data;

  // Read keys
  _cs=0;
  wait_us(1);    
  
  // Enable Key Read mode
  _spi.write(_flip(PT6312_DATA_SET_CMD | PT6312_KEY_RD | PT6312_ADDR_INC | PT6312_MODE_NORM)); // Data set cmd, normal mode, auto incr, read data

  for (int idx=0; idx < PT6312_KEY_MEM; idx++) {
    data = _flip(_spi.write(0xFF));    // read keys and correct bitorder

    if (data != 0) {  // Check for any pressed key
      for (int bit=0; bit < PT6312_KEY_BITS; bit++) {
        if (data & (1 << bit)) {keypress++;} // Test all significant bits
      }
    }  

    (*keydata)[idx] = data;            // Store keydata after correcting bitorder
  }

  wait_us(1);
  _cs=1;    

  // Restore Data Write mode
  _writeCmd(PT6312_DATA_SET_CMD, PT6312_DATA_WR | PT6312_ADDR_INC | PT6312_MODE_NORM); // Data set cmd, normal mode, auto incr, write data  
      
#if(1)
// Dismiss multiple keypresses at same time
  return (keypress == 1);    
#else
// Allow multiple keypress and accept possible spurious keys
  return (keypress > 0);
#endif  
}


/** Read switches from PT6312
  *
  *  @param  none
  *  @return char for switch data (4 least significant bits) 
  *
  */   
char PT6312::getSwitches() {
  char data;

  // Read switches
  _cs=0;
  wait_us(1);    
  
  // Enable Switch Read mode
  _spi.write(_flip(PT6312_DATA_SET_CMD | PT6312_SW_RD | PT6312_ADDR_INC | PT6312_MODE_NORM)); // Data set cmd, normal mode, auto incr, read data

  data = _flip(_spi.write(0xFF)) & PT6312_SW_MSK;   // read switches and correct bitorder

  wait_us(1);
  _cs=1;    

  // Restore Data Write mode
  _writeCmd(PT6312_DATA_SET_CMD, PT6312_DATA_WR | PT6312_ADDR_INC | PT6312_MODE_NORM); // Data set cmd, normal mode, auto incr, write data  
      
  return data;       
}
   

/** Set LEDs
  *
  * @param  char leds (4 least significant bits)  
  * @return none
  */
void  PT6312::setLED (char leds) {

  // Set LEDs
  _cs=0;
  wait_us(1);    
  
  // Enable LED Write mode
  _spi.write(_flip(PT6312_DATA_SET_CMD | PT6312_LED_WR | PT6312_ADDR_INC | PT6312_MODE_NORM)); // Data set cmd, normal mode, auto incr, write data

  _spi.write(_flip(leds & PT6312_LED_MSK));    // write LEDs in correct bitorder

  wait_us(1);
  _cs=1;    

  // Restore Data Write mode
  _writeCmd(PT6312_DATA_SET_CMD, PT6312_DATA_WR | PT6312_ADDR_INC | PT6312_MODE_NORM); // Data set cmd, normal mode, auto incr, write data  
}



/** Helper to reverse all command or databits. The PT6312 expects LSB first, whereas SPI is MSB first
  *  @param  char data
  *  @return bitreversed data
  */ 
char PT6312::_flip(char data) {
 char value=0;
  
 if (data & 0x01) {value |= 0x80;} ;  
 if (data & 0x02) {value |= 0x40;} ;
 if (data & 0x04) {value |= 0x20;} ;
 if (data & 0x08) {value |= 0x10;} ;
 if (data & 0x10) {value |= 0x08;} ;
 if (data & 0x20) {value |= 0x04;} ;
 if (data & 0x40) {value |= 0x02;} ;
 if (data & 0x80) {value |= 0x01;} ;
 return value;       
}


/** Write command and parameter to PT6312
  *  @param  int cmd Command byte
  *  &Param  int data Parameters for command
  *  @return none
  */  
void PT6312::_writeCmd(int cmd, int data){
    
  _cs=0;
  wait_us(1);    
//  _spi.write(_flip( (cmd & 0xF0) | (data & 0x0F)));  
  _spi.write(_flip( (cmd & PT6312_CMD_MSK) | (data & ~PT6312_CMD_MSK)));   
 
  wait_us(1);
  _cs=1;      
    
};  



/** Constructor for class for driving Princeton PT6312 VFD controller as used in Philips DVD625
  *
  * @brief Supports 4 Digits of 16 Segments upto 11 Digits of 11 Segments. Also supports a scanned keyboard of upto 24 keys, 4 switches and 4 LEDs.
  *        SPI bus interface device.   
  *  @param  PinName mosi, miso, sclk, cs SPI bus pins
  */
PT6312_DVD625::PT6312_DVD625(PinName mosi, PinName miso, PinName sclk, PinName cs) : PT6312(mosi, miso, sclk, cs, Dig7_Seg15) {
  _column = 0;
  _columns = 7;    
}  

#if(0)
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
#endif

/** Locate cursor to a screen column
  *
  * @param column  The horizontal position from the left, indexed from 0
  */
void PT6312_DVD625::locate(int column) {
}


/** Number of screen columns
  *
  * @param none
  * @return columns
  */
int PT6312_DVD625::columns() {
    return _columns;
}

    
/** Clear the screen and locate to 0
  */
void PT6312_DVD625::cls() {
  PT6312::cls();    
}    


/** Write a single character (Stream implementation)
  */
int PT6312_DVD625::_putc(int value) {
  int addr;
    
    if (value == '\n') {
      //No character to write
      
      //Update Cursor      
      _column = 0;
    }
    else {
      //Character to write
      value = value - 'A';
      addr = ((_columns - 1) - _column) * 2;      
      PT6312::writeData(addr, font_16A[value][0]);
      PT6312::writeData(addr + 1, font_16A[value][1]);

      //Update Cursor
      _column++;
      if (_column >= columns()) {
        _column = 0;
      }          
    } //else

//    //Set next memoryaddress, make sure cursor blinks at next location
//    addr = getAddress(_column, _row);
//    _writeCommand(0x80 | addr);
            
    return value;
}


// get a single character (Stream implementation)
int PT6312_DVD625::_getc() {
    return -1;
}
