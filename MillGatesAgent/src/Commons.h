/*
 * Commons.h
 *
 *  Created on: Apr 21, 2018
 *      Author: Luca
 */

#ifndef COMMONS_H_
#define COMMONS_H_

//#define DEBUG

#define CUBE_SIZE_X 3
#define CUBE_SIZE_Y 3
#define CUBE_SIZE_Z 3

#define PAWN_NONE  'O'
#define PAWN_WHITE 'W'
#define PAWN_BLACK 'B'

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

#define ACTION_VECTOR_DEFAULT_SIZE 4
#define AVERAGE_PAWNS_ON_BOARD 4
#define MAX_MOVES_PHASE_2 4

#define MIN_SEARCH_DEPTH 5
#define MAX_SEARCH_DEPTH 30
#define COMPUTATION_TIME 50

#define WHITE_PAWNS_COUNT 9
#define BLACK_PAWNS_COUNT 9

#define PAWNS_TO_ENTER_3RD_PHASE 3

#define HASH_TABLE_WIDTH 27
#define HASH_TABLE_HEIGHT 2
#define HASH_PAWN_WHITE 0
#define HASH_PAWN_BLACK 1
#define HASH_MASK ((1 << HASH_SET_BITS) - 1)
#define HASH_SET_BITS 24

typedef unsigned char pawn;
typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned long long hashcode;
typedef short eval_t;

#define MAX_EVAL_T ((1 << ((sizeof(eval_t) * 8) - 1)) - 1)

/*
 * XXYYZZVV
 * XX : 2 bits representing X axis index
 * YY : 2 bits representing Y axis index
 * ZZ : 2 bits representing Z axis index
 * VV : 2 bits that state whether this position is valid or not, 11 for 'invalid', otherwise for 'valid'
 */

#define IS_VALID(pos) (pos.x != -1)
#define FWX(a) (a == CUBE_SIZE_X - 1 ? 0 : a + 1)
#define FWY(a) (a == CUBE_SIZE_Y - 1 ? 0 : a + 1)
#define FWZ(a) (a == CUBE_SIZE_Z - 1 ? 0 : a + 1)
#define BWX(a) (a == 0 ? CUBE_SIZE_X - 1 : a - 1)
#define BWY(a) (a == 0 ? CUBE_SIZE_Y - 1 : a - 1)
#define BWZ(a) (a == 0 ? CUBE_SIZE_Z - 1 : a - 1)
#define POS_ENABLED(x,y) (x != 1 || y != 1)
#define ON_DIAGONAL(x,y) (x != 1 && y != 1)
#define ON_PERPENDICULAR(x,y) (x == 1 || y == 1)
//#define DIAGONALS
#define PERPENDICULARS

#define OPP(pawn) ((pawn == PAWN_NONE) ? PAWN_NONE : ((pawn == PAWN_WHITE) ? PAWN_BLACK : PAWN_WHITE))

#endif /* COMMONS_H_ */
