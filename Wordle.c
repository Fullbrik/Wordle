
#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <string.h>

// include NESLIB header
#include "neslib.h"

// include CC65 NES Header (PPU)
#include <nes.h>

// link the pattern table into CHR ROM
//#link "chr_generic.s"

// BCD arithmetic support
#include "bcd.h"
//#link "bcd.c"

// VRAM update buffer
#include "vrambuf.h"
//#link "vrambuf.c"

byte i = 0;
byte j = 0;


#include "word.h"

#include "board.h"
#include "keyboard.h"

/*{pal:"nes",layout:"nes"}*/
const char PALETTE[32] = { 
  0x03,			// screen color

  0x0F,0x2D,0x30,0x00,	// background palette 0
  0x0F,0x2A,0x30,0x00,	// background palette 1
  0x0F,0x11,0x30,0x00,	// background palette 2
  0x06,0x16,0x26,0x00,   // background palette 3

  0x16,0x35,0x24,0x00,	// sprite palette 0
  0x00,0x37,0x25,0x00,	// sprite palette 1
  0x0D,0x2D,0x3A,0x00,	// sprite palette 2
  0x0D,0x27,0x2A	// sprite palette 3
};

// setup PPU and tables
void setup_graphics() {
  // clear sprites
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
}

void main(void)
{
  setup_graphics();
  
  setup_board();
  add_letter('A');
  add_letter('A');
  add_letter('A');
  add_letter('A');
  add_letter('A');
  add_letter('A');
  
  // enable rendering
  ppu_on_all();
  
  // infinite loop
  while(1) {
    keyboard_update();
    
    //Render right when vblank starts
    ppu_wait_frame();
  }
}
