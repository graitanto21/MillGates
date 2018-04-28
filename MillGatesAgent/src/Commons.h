/*
 * Commons.h
 *
 *  Created on: Apr 21, 2018
 *      Author: Luca
 */

#ifndef COMMONS_H_
#define COMMONS_H_

#define CUBE_SIZE_X 3
#define CUBE_SIZE_Y 3
#define CUBE_SIZE_Z 3

#define PAWN_NONE  'O'
#define PAWN_WHITE 'W'
#define PAWN_BLACK 'B'

#define PHASE_1 '1'
#define PHASE_2	'2'
#define PHASE_3	'3'

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

#define ACTION_VECTOR_DEFAULT_SIZE 4
#define AVERAGE_PAWNS_ON_BOARD 4

typedef unsigned char pawn;
typedef unsigned char int8;

/*
 * XXYYZZVV
 * XX : 2 bits representing X axis index
 * YY : 2 bits representing Y axis index
 * ZZ : 2 bits representing Z axis index
 * VV : 2 bits that state whether this position is valid or not, 11 for 'invalid', otherwise for 'valid'
 */

#define IS_VALID(pos) (!((pos & 3) == 3))
#define NEW_POS(x,y,z) ((x << 6) | (y << 4) | (z << 2))
#define POS_NULL 3
#define GETX(pos) ((pos >> 6) & 3)
#define GETY(pos) ((pos >> 4) & 3)
#define GETZ(pos) ((pos >> 2) & 3)
#define FWX(pos) (GETX(pos) == 2 ? NEW_POS(0, GETY(pos), GETZ(pos)) : NEW_POS(GETX(pos)+1, GETY(pos), GETZ(pos)))
#define FWY(pos) (GETY(pos) == 2 ? NEW_POS(GETX(pos), 0, GETZ(pos)) : NEW_POS(GETX(pos), GETY(pos)+1, GETZ(pos)))
#define FWZ(pos) (GETZ(pos) == 2 ? NEW_POS(GETX(pos), GETY(pos), 0) : NEW_POS(GETX(pos), GETY(pos), GETZ(pos)+1))
#define BWX(pos) (GETX(pos) == 0 ? NEW_POS(2, GETY(pos), GETZ(pos)) : NEW_POS(GETX(pos)-1, GETY(pos), GETZ(pos)))
#define BWY(pos) (GETY(pos) == 0 ? NEW_POS(GETX(pos), 2, GETZ(pos)) : NEW_POS(GETX(pos), GETY(pos)-1, GETZ(pos)))
#define BWZ(pos) (GETZ(pos) == 0 ? NEW_POS(GETX(pos), GETY(pos), 2) : NEW_POS(GETX(pos), GETY(pos), GETZ(pos)-1))

#endif /* COMMONS_H_ */
