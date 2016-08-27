#ifndef GAMEBOARDMANAGER_H
#define GAMEBOARDMANAGER_H

#include <stdlib.h>
#include <stdio.h>
#include "sdlInterface.h"
#include "game.h"

struct GameBoardLocation
{
  int8_t x;
  int8_t y;
} typedef GameBoardLocation;

typedef enum
{
  NO_OWNER,
  OWNER_PLAYER1,
  OWNER_PLAYER2
} GameBoardSpotOwner;

extern void initGameBoard();
extern GameBoardSpotOwner whoOwnsSpotOnGameBoard(GameBoardLocation location);
extern int8_t checkFlankDirection(GameBoardLocation direction, GameBoardLocation locationClicked, 
                                  Player player);
extern int8_t isYOnBoard(int8_t y);
extern int8_t isXOnBoard(int8_t x);
extern GameBoardLocation convertPixelToGameBoard(Pixel pixel);
extern Pixel convertGameBoardToPixel(GameBoardLocation location);
extern void setGamBoardLocationOwner(GameBoardLocation location, GameBoardSpotOwner owner);
extern void changeOwnerInFlankedDirection(GameBoardLocation direction, 
                                          GameBoardLocation locationClicked, 
                                          GameBoardSpotOwner newOwner);


#endif
