/* 
 *                      L E V E L Z E R O
 *  
 *                            A K A
 *                  M A K I N G A P O I N T .
 *  
 *  
 *  welcome to the zero level of wizardry. the entirety of this level 
 *  of magic is the process of making a point.  it doesn't matter how
 *  you do it, just get the point drawn. to master this level, you need
 *  to be able to repeatedly and consistently guide your tool to the
 *  correct point on the canvas and make a mark with the desired properties.
 *  
 *  for this tutorial, which happens to be a computer program in disguise, 
 *  we will choose a microcontroller to be our painter.  we will choose  
 *  an OLED module connected via SPI to be our canvas. this makes the
 *  TFT_eSPI library included by this level a paint of sorts.  whilst
 *  TFT_eSPI contains many features which will be replicated by this tutorial,
 *  we are simply using it for the purpose of allowing the painter to make a 
 *  single point upon the canvas. 
 *  
 *  the focus of this project is the process of turning a generic,
 *  writable canvas into a multi-dimensional renderer.  the goal is
 *  to teach this in a way that is understandable by anyone aspiring
 *  to learn multi-dimensional graphics, ideally by having the source code
 *  be self-explanatory and serving as a progressive tutorial that is easy
 *  to follow.  one need not even be a programmer, as it is possible to read
 *  this code, understand what is being accomplished, and then set out a physical
 *  canvas, some paints, and a brush.  a person with seemingly zero artistic skill 
 *  could, in fact, create a realistic or visually interesting scene by their 
 *  own hand driven by a mathematical method.
 *  
 *  (in the initial incarnation of this project, a sparkfun stm32 thing plus 
 *  was chosen. it proved to be problematic with TFT_eSPI when attempting to  
 *  invoke the STM32 optimizations via the `#define STM32` declaration.  because
 *  of this, it was not possible to use DMA and drawing was going to be
 *  unacceptably slow. as a consequence, the author elected to move to an esp32
 *  based board)
 */

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

/* bit depth must be 16 to use DMA with TFT_eSPI.  the initial hardware
 * chosen for this project, the sparkfun stm32 thing plus, would not 
 * work with DMA, and in fact when the stm32 optimizations were enabled, no
 * graphics output was possible.  this prompted the move to an esp32 device.
 */
#define COLOR_DEPTH 16
