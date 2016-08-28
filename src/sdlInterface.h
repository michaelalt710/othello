#ifndef SDLINTERFACE_H
#define SDLINTERFACE_H

#include <SDL/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define NUM_COLUMNS 8
#define NUM_ROWS 8
#define NUM_RECTS (NUM_COLUMNS * NUM_ROWS)
#define RECT_WIDTH (SCREEN_WIDTH / NUM_COLUMNS)
#define RECT_HEIGHT (SCREEN_HEIGHT / NUM_ROWS)

struct Pixel
{
  uint16_t x;
  uint16_t y;
} typedef Pixel;

struct ButtonEvent
{
  uint8_t clicked;
  Pixel location;
} typedef ButtonEvent;

struct Input
{
  ButtonEvent *leftClick;
  ButtonEvent *rightClick;
  ButtonEvent *left;
  ButtonEvent *right;
  ButtonEvent *down;
  ButtonEvent *up;
} typedef Input;

/* FUNCTION: getSDLInput()
 *
 * PARAMETERS: input - pointer to the input to be filled out.
 *
 * RETURNS: NONE
 *
 * DESCRIPTION: Fills out the input based on user input to the SDL window.
 */
extern void getSDLInput(Input *input);

/* FUNCTION: initSDLOthelloBoard()
 *
 * PARAMETERS: title - The desired title of the SDL window
 *
 * RETURNS: NONE
 *
 * DESCRIPTION: Sets up an SDL window for an othello game.
 */
extern void initSDLOthelloBoard(char *title);

/* FUNCTION: putSDLPixel()
 *
 * PARAMETERS: location - pixel location on the SDL window 
 *
 *             color    - the color to change the pixel to
 *
 * RETURNS: NONE
 *
 * DESCRIPTION: Sets the provided pixel on the SDL window to the provided SDL color
 */
extern void putSDLPixel(Pixel location, uint32_t color);

/* FUNCTION: getSDLColor()
 *
 * PARAMETERS: red   - The red value of the color 
 *             
 *             green - The green value of the color
 *
 *             blue  - The blue value of the color
 *
 * RETURNS: SDL color value of the provided RGB
 *
 * DESCRIPTION: gets the SDL color value of the provided RGB values
 */
extern uint32_t getSDLColor(int red, int green, int blue);

/* FUNCTION: drawSDLCircle()
 *
 * PARAMETERS: center - The pixel location of the center of the circle to draw
 *
 *             radius - Radius of the circle to draw
 *
 *             color  - color of the circle to draw
 *
 * RETURNS: NONE
 *
 * DESCRIPTON: Draws a circle with the provided center, radius, and color on the screen.
 */
extern void drawSDLCircle(Pixel center, uint16_t radius, uint32_t color);
#endif //SDLINTERFACE_H
