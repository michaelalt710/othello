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

/* FUNCTION: initGameBoard()
 *
 * PARAMETERS: NONE
 * 
 * RETURN: NONE
 *
 * DESCRIPTION: Sets up the game board manager 
 */
extern void initGameBoard();

/* FUNCTION: GameBoardSpotOwner()
 *
 * PARAMETERS: location - spot on the game board to check
 *
 * RETURN: The owner of the provided location on the game board
 *
 * DESCRIPTION: Lets the caller know who owns a specific spot on the game board
 */
extern GameBoardSpotOwner whoOwnsSpotOnGameBoard(GameBoardLocation location);

/* FUNCTION: checkFlankDirection()
 *
 * PARAMETERS: direction       - The x and y values determine which direction to check, 
 *                               positives values are to the RIGHT and DOWN. 
 *             
 *             locationClicked - The location of the spot that was clicked to see if it flanks
 *                               the opponent in the provided direction.
 *             
 *             player          - The player that is trying to flank the opponent
 *
 * RETURNS:    TRUE/FALSE      - Whether or not the player successfully flanked the opponent in
 *                               the provided direction
 *
 * DESCRIPTION: Starts one square away from the clicked location in the provided direction.
 *              Checks the owner of each spot in the provided direction and determines if
 *              the provided player flanked the other player.  A successful flank is when
 *              a player has pieces on either side of any number of opponents pieces in one
 *              direction. A flank does not go through the flanking players piece. The provided
 *              direction tells how many spots to move in both the x and y direction.
 */
extern int8_t checkFlankDirection(GameBoardLocation direction, GameBoardLocation locationClicked, 
                                  Player player);

/* FUNCTION: isYOnBoard()
 *
 * PARAMETERS: y          - y location to check if it's on the game board
 *
 * RETURNS:    TRUE/FALSE - Whether or not the y location is on the board
 *
 * DESCRIPTION: Checks if the provided y value is on the game board
 */
extern int8_t isYOnBoard(int8_t y);

/* FUNCTION: isXOnBoard()
 *
 * PARAMETERS: x          - x location to check if it's on the game board
 *
 * RETURNS:    TRUE/FALSE - Whether or not the x location is on the board
 *
 * DESCRIPTION: Checks if the provided x value is on the game board
 */
extern int8_t isXOnBoard(int8_t x);

/* FUNCTION: convertPixelToGameBoard()
 *
 * PARAMETERS: pixel - location in pixels on the screen to convert to a location on the
 *                     game board.
 *
 * RETURNS: The game board location of the provided pixel
 *
 * DESCRIPTON: Converts the provided pixel location on the screen to a location on
 *             the game board.
 */
extern GameBoardLocation convertPixelToGameBoard(Pixel pixel);

/* FUNCTION: convertGameBoardToPixel()
 *
 * PARAMETERS: location - location on the game board to convert to pixels on the screen.
 *
 * RETURNS: The center of the provided square on the game board in pixels.
 *
 * DESCRIPTON: Converts the provided location on the game board to a location on
 *             the screen in pixels.
 */
extern Pixel convertGameBoardToPixel(GameBoardLocation location);

/* FUNCTION: setGameBoardLocationOwner()
 *
 * PARAMETERS: location - spot on the game board to change the owner of.
 *           
 *             owner    - the owner to set the spot to.
 *
 * RETURNS: NONE
 *
 * DESCRIPTON: Changes the owner of a square on the game board to the provided owner
 */
extern void setGameBoardLocationOwner(GameBoardLocation location, GameBoardSpotOwner owner);

/* FUNCTION: changeOwnerInFlankedDirection()
 *
 * PARAMETERS: direction       - direction of the successful flank. Positive values are RIGHT
 *                               DOWN.
 *
 *             locationClicked - location on the game board of the piece that was placed to
 *                               cause the flank.
 *
 *             newOwner        - new owner of all the flanked spots
 *
 * RETURNS: NONE
 *
 * DESCRIPTION: Changes the owner of all the flanked spots in a provided direction.  
 *              Must make sure the player has successfully flanked in the provided
 *              direction before calling this function.
 */
extern void changeOwnerInFlankedDirection(GameBoardLocation direction, 
                                          GameBoardLocation locationClicked, 
                                          GameBoardSpotOwner newOwner);


#endif
