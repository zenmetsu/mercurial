/*
 * Mercurial - a novel of sorts. a sourcebook of magic, perhaps.    
 */

#include "level_zero.h"


                                            //
TFT_eSPI tft = TFT_eSPI();                 // invoke custom library
                                          //
/* what have we done? well, i suppose we just told the painter                                          
 * about the canvas, and we named it `tft`
 * 
 * this is not a tutorial on programming in C, but perhaps it might
 * serve that purpose, but the author will make no effort to write
 * to that effect
 */


                                           //
TFT_eSprite buffer0 = TFT_eSprite(&tft);  // create a buffer
                                         //                                         
/*  what's a buffer? if you understand the prior line, then feel
 *  free to skip this explanation. a buffer is a sort of mock
 *  canvas.  it is not strictly necessary, and it can manifest
 *  in many forms, from the virtual to the physical. 
 *  
 *  in this example a buffer is a region of memory.  instead of 
 *  painting each point upon the canvas individually, we paint a 
 *  point in memory which is much quicker than painting to the 
 *  physical canvas. due to the nature of the OLED display chosen
 *  by the author, it takes less time to paint the entire image 
 *  in one operation than it does to paint one point at a time.
 *  
 *  the region of memory that serves as a scratch space of sorts 
 *  is the buffer that we are defining here, that we just named
 *  `buffer0`.  
 */


float tiles = 128;
float tileSize = tft.width()/tiles;

int mercury[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                      0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,
                      0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,
                      0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,
                      0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,
                      0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,
                      0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,
                      0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,
                      0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,
                      0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
                      0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,
                      0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,
                      0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
                      0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};   

int penColor = random(16536);

void setup(void) {
  tft.init();
  tft.setRotation(2);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
  buffer0.createSprite(128,128);
  buffer0.setSwapBytes(true);
  for (int x = 0; x < 128; x++) {
    for (int y = 0; y < 128; y++){
      if (random(2) == 0) {
        buffer0.drawPixel(x,y,TFT_BLACK);
      } else {
        buffer0.drawPixel(x,y,penColor);
      }
    }
  }
  buffer0.pushSprite(0,0);

}

void loop() {
 
  tiles = random(33);
  tileSize = tft.width()/tiles;
  
  for (int x = 0; x < 128; x++) {
    for (int y = 0; y < 128; y++){
      penColor = random(65536);
      if (penColor < 32768) {
        buffer0.drawPixel(x,y,TFT_BLACK);
      } else {
        buffer0.drawPixel(x,y,penColor);
      }
    }
  }  
  for (int x = 0; x < tiles; x++) {
    for (int y = 0; y < tiles; y++){
      int c = mercury[16*int(x*tileSize/8)+int(y*tileSize/8)];
      float b = map(c,0,1,0,1); 
      
      buffer0.fillEllipse(x*tileSize,y*tileSize,tileSize*b,tileSize*b,TFT_BLACK);
    }
  }
  buffer0.pushSprite(0,0);
}
