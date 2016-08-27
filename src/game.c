#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "sdlInterface.h"
#include "gameBoardManager.h"
#include "game.h"

#define GAME_TITLE "Othello"
#define FPS_60 16
#define LEFT -1
#define RIGHT 1
#define UP -1
#define DOWN 1

#define FLANKED_RIGHT 0x00
#define FLANKED_LEFT 0x01
#define FLANKED_UP 0x02
#define FLANKED_DOWN 0x04
#define FLANKED_DIAG_UP_RIGHT 0x08
#define FLANKED_DIAG_DOWN_RIGHT 0x10
#define FLANKED_DIAG_UP_LEFT 0x20
#define FLANKED_DIAG_DOWN_LEFT 0x40


static void initInput();
static void playerTurn(Player whichPlayer);
static int8_t checkValidInput(Player player);
static int8_t checkFlank(Pixel pixelClicked, Player player);

static Input *input;
static uint8_t flankDirections;

int main()
{
  uint32_t yellow, white, black, color;
  uint16_t radius = 30;
  Player whichPlayersTurn = PLAYER1;

  initInput();
  initGameBoard();
  initSDLOthelloBoard(GAME_TITLE);
  yellow = getSDLColor(0xff, 0xff, 0x00);
  black = getSDLColor(0x00, 0x00, 0x00);
  white = getSDLColor(0xff, 0xff, 0xff);
  color = black;

  while (1) {
    getSDLInput(input);
    if (input->leftClick->clicked == 1)
    {
      playerTurn(whichPlayersTurn);
      whichPlayersTurn = whichPlayersTurn == PLAYER1 ? PLAYER2 : PLAYER1;
    }
    input->leftClick->clicked = 0;
    SDL_Delay(FPS_60);
  }

  SDL_Quit();
}

static void initInput()
{
  input = calloc(sizeof(Input), 0);
  input->leftClick = calloc(sizeof(ButtonEvent), 0);

}

static void playerTurn(Player whichPlayer)
{
  uint32_t playerColor, otherPlayerColor, white, black;
  GameBoardLocation locationClicked, whichDirection;
  GameBoardSpotOwner playerOwned;
  uint8_t direction;

  black = getSDLColor(0x00, 0x00, 0x00);
  white = getSDLColor(0xff, 0xff, 0xff);

  /* Determine the color of each player */
  playerColor = whichPlayer == PLAYER1 ? black : white;
  otherPlayerColor = whichPlayer == PLAYER1 ? white : black;
  playerOwned = whichPlayer == PLAYER1 ? OWNER_PLAYER1 : OWNER_PLAYER2;

  locationClicked = convertPixelToGameBoard(input->leftClick->location);
  if (checkValidInput(whichPlayer) == TRUE)
  {
    drawSDLCircle(input->leftClick->location, RADIUS, playerColor);
    setGameBoardLocationOwner(locationClicked, playerOwned);
    for (direction = FLANKED_RIGHT; direction < 0x41; direction++)
    {
      if ((direction & flankDirections) == direction)
      {
        whichDirection.x = 0;
        whichDirection.y = 0;
        switch (direction)
        {
            case FLANKED_RIGHT: 
                                whichDirection.x = 1;
                                break;
            case FLANKED_LEFT: 
                                whichDirection.x = -1;
                                break;
            case FLANKED_UP:
                                whichDirection.y = -1;
                                break;
            case FLANKED_DOWN:
                                whichDirection.y = 1;
                                break;
            case FLANKED_DIAG_UP_LEFT:
                                whichDirection.x = -1;
                                whichDirection.y = -1;
                                break;
            case FLANKED_DIAG_DOWN_RIGHT:
                                whichDirection.x = 1;
                                whichDirection.y = 1;
                                break;
            case FLANKED_DIAG_UP_RIGHT:
                                whichDirection.x = 1;
                                whichDirection.y = -1;
                                break;
            case FLANKED_DIAG_DOWN_LEFT:
                                whichDirection.x = -1;
                                whichDirection.y = 1;
                                break;
            default:
                                break;

        }
        changeOwnerInFlankedDirection(whichDirection, locationClicked, playerOwned);
      }
    }
    flankDirections = 0;
    printf("Player %d Input Valid\n", whichPlayer + 1); 
  }
  else
  {
    printf("Player %d Input Invalid\n", whichPlayer + 1); 
  }
}

static int8_t checkValidInput(Player player)
{
  Pixel location;
  
  if (input == NULL || input->leftClick == NULL)
    return ERROR;
  
  location = input->leftClick->location;

  return checkFlank(location, player); 
}

static int8_t checkFlank(Pixel pixelClicked, Player player)
{
  GameBoardLocation locationClicked, direction, temp;
  GameBoardSpotOwner playerOwned, otherPlayerOwned;
  int8_t flanked = FALSE;
  
  playerOwned = player == PLAYER1 ? OWNER_PLAYER1 : OWNER_PLAYER2;
  otherPlayerOwned = player == PLAYER1 ? OWNER_PLAYER2 : OWNER_PLAYER1;

  flankDirections = 0;

  locationClicked = convertPixelToGameBoard(pixelClicked);

  /* Only check each direction if there is at least two in that direction  and the 
   * one immediately next to the clicked location in that direction is owned by the 
   * other player */
  temp.x = locationClicked.x + 1;
  temp.y = locationClicked.y;
  if ((locationClicked.x < NUM_COLUMNS - 2) &&
      (whoOwnsSpotOnGameBoard(temp) == otherPlayerOwned))
  {
    direction.x = 1;
    direction.y = 0;
    if (checkFlankDirection(direction, locationClicked, player))
    {
      flanked = TRUE;
      flankDirections |= FLANKED_RIGHT;
    }
  }

  temp.x = locationClicked.x - 1;
  temp.y = locationClicked.y;
  if (locationClicked.x > 1 &&
      (whoOwnsSpotOnGameBoard(temp) == otherPlayerOwned))
  {
    direction.x = -1;
    direction.y = 0;
    if (checkFlankDirection(direction, locationClicked, player) == TRUE)
    {
      flanked = TRUE;
      flankDirections |= FLANKED_LEFT;
    }
  }

  temp.x = locationClicked.x;
  temp.y = locationClicked.y + 1;
  if ((locationClicked.y < NUM_ROWS - 2) &&
      (whoOwnsSpotOnGameBoard(temp) == otherPlayerOwned))
  {
    direction.x = 0;
    direction.y = 1;
    if (checkFlankDirection(direction, locationClicked, player) == TRUE)
    {
      flanked = TRUE;
      flankDirections |= FLANKED_DOWN;
    }
  }

  temp.x = locationClicked.x;
  temp.y = locationClicked.y - 1;
  if ((locationClicked.y > 1) &&
      (whoOwnsSpotOnGameBoard(temp) == otherPlayerOwned))
  {
    direction.x = 0;
    direction.y = -1;
    if (checkFlankDirection(direction, locationClicked, player) == TRUE)
    {
      flanked = TRUE;
      flankDirections |= FLANKED_UP;
    }
  }

  temp.x = locationClicked.x + 1;
  temp.y = locationClicked.y + 1;
  if ((locationClicked.x < NUM_COLUMNS - 2) && (locationClicked.y < NUM_ROWS - 2) &&
      (whoOwnsSpotOnGameBoard(temp) == otherPlayerOwned))
  {
    direction.x = 1;
    direction.y = 1;
    if (checkFlankDirection(direction, locationClicked, player) == TRUE)
    {
      flanked = TRUE;
      flankDirections |= FLANKED_DIAG_DOWN_RIGHT;
    }
  }

  temp.x = locationClicked.x - 1;
  temp.y = locationClicked.y - 1;
  if ((locationClicked.x > 1) && (locationClicked.y > 1) &&
      (whoOwnsSpotOnGameBoard(temp) == otherPlayerOwned))
  {
    direction.x = -1;
    direction.y = -1;
    if (checkFlankDirection(direction, locationClicked, player) == TRUE)
    {
      flanked = TRUE;
      flankDirections |= FLANKED_DIAG_UP_LEFT;
    }
  }

  temp.x = locationClicked.x - 1;
  temp.y = locationClicked.y + 1;
  if ((locationClicked.x > 1) && (locationClicked.y < NUM_ROWS - 2) &&
      (whoOwnsSpotOnGameBoard(temp) == otherPlayerOwned))
  {
    direction.x = -1;
    direction.y = 1;
    if (checkFlankDirection(direction, locationClicked, player) == TRUE)
    {
      flanked = TRUE;
      flankDirections |= FLANKED_DIAG_DOWN_LEFT;
    }
  }

  temp.x = locationClicked.x + 1;
  temp.y = locationClicked.y - 1;
  if ((locationClicked.x < NUM_COLUMNS - 2) && (locationClicked.y > 1) &&
      (whoOwnsSpotOnGameBoard(temp) == otherPlayerOwned))
  {
    direction.x = 1;
    direction.y = -1;
    if (checkFlankDirection(direction, locationClicked, player) == TRUE)
    {
      flanked = TRUE;
      flankDirections |= FLANKED_DIAG_UP_RIGHT;
    }
  }


  return flanked;
}
