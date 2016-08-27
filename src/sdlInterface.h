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

extern void getSDLInput(Input *input);
extern void initSDLOthelloBoard(char *title);
extern void putSDLPixel(Pixel location, uint32_t color);
extern uint32_t getSDLColor(int red, int green, int blue);
extern void drawSDLCircle(Pixel center, uint16_t radius, uint32_t color);
#endif //INPUTS_H
