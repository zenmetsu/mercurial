/*
 * Mercurial - a novel of sorts. a sourcebook of magic, perhaps.    
 * 
 * 202
 *    Hg
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
 *  is the buffer that we are defining here and we just named
 *  it `buffer0`.  
 */



float tiles = 128;
float tileSize = tft.width()/tiles;

/*  the OLED display chosen has 128 pixels in both height and width
 *   
 *  we are dividing up the canvas into tiles.  this can be any number,
 *  but initially we are choosing to have a one-to-one relationship.
 *  
 *  the canvas is thus divided up into 128 tiles both vertically and
 *  horizontally, and tileSize is calculated to be the OLED width divided
 *  by the number of tiles.  as it stands, tileSize is one point naught.
 */



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

/*  this is an array.  it is also a sprite.  we have named it `mercury`
 * 
 *  as an array, it consists of 256 members where each member is of
 *  type `int`. it is a one-dimensional array.
 * 
 *  as a sprite, it represents the alchemical symbol for `mercury`.  the
 *  one-dimensional array has been divided into 16 rows of 16 columns
 *  to provide insight into its two-dimensional nature. one can see the
 *  image represented by this arrangement of values. 
 */



int penColor = random(65536);

/*  we are defining a color to use.
 *   it appears that we have chosen a pen over a brush.
 *    chance will dictate the color
 */



void setup(void) {
  tft.init();
  tft.setRotation(2);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);

/*
 * necessary evils to bring about a functional canvas.
 * 
 * we start by painting it black.  no reason other than symbolic.
 * we also point out that the fillscreen `function` within TFT_eSPI
 * is used here as it is speed optimized.  `fillScreen` is one of only
 * four functions within the library that we will invoke with the intent
 * of exacting change upon the canvas.  the second will be `drawPixel` which,  
 * along with the third function `pushSprite` will form the basis of our work.
 * the fourth will be the `fillEllipse` function which we will use to 
 * paint a large point on the canvas for strictly illustrative purposes.  
 * creating anything more substantial than points will require us to graduate 
 * to the first level of magic, thus `fillScreen` and `fillEllipse` are 
 * forbidden rituals, invoked by the initiate temporarily until rights to these
 * methods can be secured.
 */


                                               //
  buffer0.createSprite(128,128);              //  we previously named this buffer, now we give it breadth and length
  buffer0.setSwapBytes(true);                //  and we set the buffer's byte order to match that of the display
                                            //

                                                //
  for (int x = 0; x < 128; x++) {              // we are going to iterate over each pixel column...
    for (int y = 0; y < 128; y++){            // and over each pixel row...
      if (random(2) == 0) {                  // and for each, flip a coin, and if zero
        buffer0.drawPixel(x,y,TFT_BLACK);   // we paint the pixel black in the buffer
      } else {                             // otherwise
        buffer0.drawPixel(x,y,penColor);  // we paint it the color previously chosen by fate
      }                                  //
    }
  }                                //
  buffer0.pushSprite(0,0);        // and once we are finished, we push the buffer to the canvas          
}                                // and we are done... a random landscape with half of the pixels
                                // black and the other half a randomly chosen color
                               //

                                
void loop() {
                                        //
  tiles += random(0,3) - 1;            // now we permit chance to nudge the tile size slightly
  if (tiles < 8){                     // and perform corrections to keep the tile count
    tiles++;                         // within an aesthetically pleasing range
  } else {                          //
    if (tiles > 32) {              //
      tiles--;                    //
    }                            //                     
  }                             //

                                       // 
  tileSize = tft.width()/tiles;       // and since the tile count may have changed, we update their size
                                     //

                                               //
  for (int x = 0; x < 128; x++){              // if this looks familiar, then you are paying attention
    for (int y = 0; y < 128; y++){           //
      penColor = rand() % 65536 + 1;        // this time, however, we are picking a different color each time
      if (penColor < 32768) {              // but if the color is represented by a number in the lower half of the range
        buffer0.drawPixel(x,y,TFT_BLACK); // we paint it black instead
      } else {                           //
        buffer0.drawPixel(x,y,penColor);// otherwise, we let chance decide
      }                                //
    }
  }  


                                                        //
  for (int x = 0; x < tiles; x++){                     // again, you ask?  not so fast.  we just filled the canvas
    for (int y = 0; y < tiles; y++){                  // randomly and pixel-wise... now it is tile-wise and `tiles` is random
      int nx = map(x,0,tiles,0,16);                  // so we normalize the value of `x` and `y` to remain in a range of 
      int ny = map(y,0,tiles,0,16);                 // zero through 15 inclusive.                
      int c = map(mercury[ 16 * nx + ny ],0,1,1,0);// we are referencing the sprite. this might need explanation
                                                  // 
/*  what is `c`? well, to understand that, we must understand what was just done
 *   
 *  for starters, `c` is a variable of type `int`.  its value was set based upon   
 *  the value of the array `mercury`, more specifically, one of its elements. as
 *  the array represents a two-dimensional sprite with a height and width of 16,
 *  we mapped the values of `x` and `y` to `nx` and `ny`, and we set the value of   
 *  `c` to be the value of `mercury` at that given point.  in a nutshell, since the
 *  sprite has a 16x16 resolution, depending upon the tile count, we are either
 *  sub-sampling, critically-sampling, or super-sampling the bitmap within `mercury`
 */
                                                                                                            //
      buffer0.fillEllipse(x*tileSize+(tileSize/2),y*tileSize+(tileSize/2),tileSize*c,tileSize*c,TFT_BLACK);// here we draw
                                                                                                          // a black ellipse
                                                                                                         // in the buffer, 
                                                                                                        // over pixels 
                                                                                                       // previously painted 
                                                                                                      // random colors.
                                                                                    // in cases where the screen position corresponds
                                                                                   // to a value of one within the sprite, 
                                                                                  // then `c` will be zero due to the inverse mapping
                                                                                 // and thus the radius of our ellipse will be zero, 
                                                                                // thus not drawn, permitting the sprite to remain,
    }                                                                          // its form approximated by a multitude of colored pixes
  }                                                                           // surrounded by a sea of black.
  buffer0.pushSprite(0,0);                                                   // we push the buffer to the canvas to see our work
}                                                                           // and we finish defining the loop
                                                                           //
                                                                           
