/*
 * State.cpp
 *
 *  Created on: 26 apr 2018
 *      Author: Lorenzo Rosa (lorenzo.rosa.bo@gmail.com)
 */

#include "State.h"

#include <string>
#include <stdlib.h>
#include "stdio.h"

/*
7 O--------O--------O
6 |--O-----O-----O--|
5 |--|--O--O--O--|--|
4 O--O--O     O--O--O
3 |--|--O--O--O--|--|
2 |--O-----O-----O--|
1 O--------O--------O
  a  b  c  d  e  f  g
 */

bool State::setPawnAt2D(uint8 x, uint8 y, pawn value){
	int i, j, k;
	i = j = k = -1;

	//Convert from char to int
	y= y - '1' + 1;

	if ( x == 'd') { // 'd'
		//Coordinate 'x'
		j = 1;
		//Coordinate 'y'
		if ( y > 0 && y < 4) {
			i = 2;
			k =  3 - y;
		}
		else if ( y == 4) {
			i = 1;
			k = 0;
		}
		else if (y > 4 && y < 8) {
			i = 0;
			k = y % 5;
		}
		else return false;
	}
	else {
		//Coordinate 'x'
		if (x >= 'a' && (x/100) == 0) { // 'a','b','c'
			j = 0;
			k = 2 - (x % 'a');
		}
		else if (x <= 'g' && (x/100) == 1) { // 'e','f','g'
			j = 2;
			k = x % 'e';
		} else return false;

		//Coordinate 'y'
		if ( y > 0 && y < 4 )
			i = 2;
		else if ( y == 4)
			i = 1;
		else if (y > 4 && y < 8)
			i = 0;
		else return false;
	}

	if (i<0 || j<0 || k<0)
		return false;

	setPawnAt(i,j,k, value);
	return true;
}

// If coordinate is not valid, returns -1;
pawn State::getPawnAt2D(uint8 x, uint8 y) const{
	int i, j, k;
	i = j = k = -1;

	//Convert from char to int
	y= y - '1' + 1;

	if ( x == 'd') { // 'd'
		//Coordinate 'x'
		j = 1;
		//Coordinate 'y'
		if ( y > 0 && y < 4) {
			i = 2;
			k =  3 - y;
		}
		else if ( y == 4) {
			i = 1;
			k = 1;
		}
		else if (y > 4 && y < 8) {
			i = 0;
			k = y % 5;
		}
		else return -1;
	}
	else {
		//Coordinate 'x'
		if (x >= 'a' && (x/100) == 0) { // 'a','b','c'
			j = 0;
			k = 2 - (x % 'a');
		}
		else if (x <= 'g' && (x/100) == 1) { // 'e','f','g'
			j = 2;
			k = x % 'e';
		} else return -1;

		//Coordinate 'y'
		if ( y > 0 && y < 4 )
			i = 2;
		else if ( y == 4)
			i = 1;
		else if (y > 4 && y < 8)
			i = 0;
		else return -1;
	}

	if (i<0 || j<0 || k<0)
		return -1;

	return getPawnAt(i,j,k);
}


void State::setWhitePawnsOnBoardStr(std::string number){
	setPawnsOnBoard(PAWN_WHITE, atoi(number.c_str()));
}
uint8 State::getWhitePawnsOnBoardStr() const {
	return getPawnsOnBoard(PAWN_WHITE) + '1' - 1;
}

void State::setBlackPawnsOnBoardStr(std::string  number) {
	setPawnsOnBoard(PAWN_BLACK, atoi(number.c_str()));
}
uint8 State::getBlackPawnsOnBoardStr() const {
	return getPawnsOnBoard(PAWN_BLACK) + '1' - 1;
}

void State::setPawnsOnBoard(pawn pawn, uint8 count) {
	if (pawn == PAWN_WHITE)
		setPawnAt(1,1,1, (getPawnAt(1,1,1) & 15) | (count << 4));
	else if (pawn == PAWN_BLACK)
		setPawnAt(1,1,1, (getPawnAt(1,1,1) & 240) | count);
}

uint8 State::getPawnsOnBoard(pawn pawn) const {
	if (pawn == PAWN_WHITE)
		return (getPawnAt(1,1,1) & 240) >> 4;
	else if (pawn == PAWN_BLACK)
		return getPawnAt(1,1,1) & 15;
	return 0;
}

void State::setWhitePawnsToPlayStr(std::string number) {
	setPawnsToPlay(PAWN_WHITE, atoi(number.c_str()));
}
uint8 State::getWhitePawnsToPlayStr() const {
	return getPawnsToPlay(PAWN_WHITE) + '1' - 1;
}

void State::setBlackPawnsToPlayStr(std::string number) {
	setPawnsToPlay(PAWN_BLACK, atoi(number.c_str()));
}
uint8 State::getBlackPawnsToPlayStr() const {
	return getPawnsToPlay(PAWN_BLACK) + '1' - 1;
}

uint8 State::getPawnsToPlay(pawn player) const {
	if (player == PAWN_WHITE)
		return (getPawnAt(1,1,2) & 240) >> 4;
	else if (player == PAWN_BLACK)
		return getPawnAt(1,1,2) & 15;
	return 0;
}

void State::setPawnsToPlay(pawn player, uint8 count) {
	if (player == PAWN_WHITE)
		setPawnAt(1,1,2, (getPawnAt(1,1,2) & 15) | (count << 4));
	else if (player == PAWN_BLACK)
		setPawnAt(1,1,2, (getPawnAt(1,1,2) & 240) | count);
}

void State::setMorrisLastTurn(pawn player, bool value) {
	if (player == PAWN_WHITE)
		setPawnAt(1,1,0, (getPawnAt(1,1,0) & 15) | (value << 4));
	else if (player == PAWN_BLACK)
		setPawnAt(1,1,0, (getPawnAt(1,1,0) & 240) | value);
}

bool State::getMorrisLastTurn(pawn player) const {
	if (player == PAWN_WHITE)
		return (getPawnAt(1,1,0) & 240) >> 4;
	else if (player == PAWN_BLACK)
		return getPawnAt(1,1,0) & 15;
	return false;
}

std::string State::toString() const {

	char res[CUBE_SIZE_X*CUBE_SIZE_Y*CUBE_SIZE_Z + 1];

	int l = 0;
	for (uint8 i = 0; i < CUBE_SIZE_X; i++)
		for (uint8 j = 0; j < CUBE_SIZE_Y; j++)
			for (uint8 k = 0; k < CUBE_SIZE_Z; k++){
				if (i==1 && j==1 && k==1 && getPawnAt(i,j,k) != PAWN_NONE)
					res[l] = getPawnAt(i,j,k) < 10 ? (getPawnAt(1,1,1) + '0') : 'A' + (getPawnAt(i,j,k)%10);
				else if (i==1 && j==1 && k==2 && getPawnAt(i,j,k) != PAWN_NONE)
					res[l] = getPawnAt(i,j,k) < 10 ? (getPawnAt(1,1,2) + '0') : 'A' + (getPawnAt(i,j,k)%10);
				else res[l] = getPawnAt(i,j,k);
				l++;
			}
	res[l] = '\0';
	return std::string(res);

}

std::string State::toNiceString() const {
	std::string result = std::string();
	result = result + "7 " + (char)getPawnAt(0, 0, 2) + "--------" + (char)getPawnAt(0, 1, 2) + "--------" + (char)getPawnAt(0, 2, 2) + "\n" +
			"6 |--" + (char)getPawnAt(0, 0, 1) + "-----" + (char)getPawnAt(0, 1, 1) + "-----" + (char)getPawnAt(0, 2, 1) + "--|\n" +
			"5 |--|--" + (char)getPawnAt(0, 0, 0) + "--" + (char)getPawnAt(0, 1, 0) + "--" + (char)getPawnAt(0, 2, 0) + "--|--|\n" +
			"4 " + (char)getPawnAt(1, 0, 2) + "--" + (char)getPawnAt(1, 0, 1) + "--" + (char)getPawnAt(1, 0, 0) + "     "
			+ (char)getPawnAt(1, 2, 0) + "--" + (char)getPawnAt(1, 2, 1) + "--" + (char)getPawnAt(1, 2, 2) + "\n" +
			"3 |--|--" + (char)getPawnAt(2, 0, 0) + "--" + (char)getPawnAt(2, 1, 0) + "--" + (char)getPawnAt(2, 2, 0) + "--|--|\n" +
			"2 |--" + (char)getPawnAt(2, 0, 1) + "-----" + (char)getPawnAt(2, 1, 1) + "-----" + (char)getPawnAt(2, 2, 1) + "--|\n" +
			"1 " + (char)getPawnAt(2, 0, 2) + "--------" + (char)getPawnAt(2, 1, 2) + "--------" + (char)getPawnAt(2, 2, 2) + "\n" +
			"  a  b  c  d  e  f  g\n" ;
	return result;
}

State::~State() {}

std::ostream& operator<<(std::ostream &strm, const State &s){
	return strm << s.toString();
}

void State::toStringToSend() const{
	char ret[25]; //TODO migliorare per inserire la casella al centro
	//24 + \0

	//Insert left face
	int count = 0;
	int i, j=0, k;

	for(k=2; k>=0; k--)
		for(i=2; i>=0; i--){
			ret[count++] = getPawnAt(i,j,k);
			printf("%c", ret[count - 1]);
		}

	//Insert middle line
	j=1;
	i=2;
	for(k=2; k>=0; k--){
		ret[count++] = getPawnAt(i,j,k);
		printf("%c", ret[count - 1]);
	}
	i=0;
	for(k=0; k<=2; k++){
		ret[count++] = getPawnAt(i,j,k);
		printf("%c", ret[count - 1]);
	}

	//Insert right face
	j=2;
	for(k=0; k<=2; k++)
		for(i=2; i>=0; i--){
			ret[count++] = getPawnAt(i,j,k);
			printf("%c", ret[count - 1]);
		}


	ret[count] = '\0';
}

uint8 State::morrisCount(pawn player) const {

	uint8 res = 0;

	for (uint8 x = 0; x < CUBE_SIZE_X; x++)
		for (uint8 y = 0; y < CUBE_SIZE_Y; y++)
			if (isInMorrisAxis(NEW_POS(x,y,0), Z_AXIS) && getPawnAt(x,y,0) == player)
				res++;
	for (uint8 y = 0; y < CUBE_SIZE_Y; y++)
		for (uint8 z = 0; z < CUBE_SIZE_Z; z++)
			if (isInMorrisAxis(NEW_POS(0,y,z), X_AXIS) && getPawnAt(0,y,z) == player)
				res++;

	for (uint8 x = 0; x < CUBE_SIZE_X; x++)
		for (uint8 z = 0; z < CUBE_SIZE_Z; z++)
			if (isInMorrisAxis(NEW_POS(x,0,z), Y_AXIS) && getPawnAt(x,0,z) == player)
				res++;
	return res;

}

uint8 State::blockedPawnCount(pawn player) const {

	uint8 res = 0, p;
	ExpVector<uint8> pawns = getAllPositions(player);

	for (uint8 i = 0; i < pawns.getLogicSize(); i++) {
		p = FWX(pawns.get(i));
		if (GETX(p) != 0 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
			continue;

		p = BWX(pawns.get(i));
		if (GETX(p) != 2 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
			continue;

		p = FWY(pawns.get(i));
		if (GETY(p) != 0 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
			continue;

		p = BWY(pawns.get(i));
		if (GETY(p) != 2 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
			continue;

#if defined(DIAGONALS) && defined(PERPENDICULARS)
		p = FWZ(pawns.get(i));
		if (GETZ(p) != 0 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
			continue;

		p = BWZ(pawns.get(i));
		if (GETZ(p) != 2 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
			continue;
#endif

#if !defined(DIAGONALS) && defined(PERPENDICULARS)
		p = FWZ(pawns.get(i));
		if (ON_PERPENDICULAR(p)) {
			if (GETZ(p) != 0 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
				continue;

			p = BWZ(pawns.get(i));
			if (GETZ(p) != 2 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
				continue;
		}
#endif

#if defined(DIAGONALS) && !defined(PERPENDICULARS)
		p = FWZ(pawns.get(i));
		if (ON_DIAGONAL(p)) {
			if (GETZ(p) != 0 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
				continue;

			p = BWZ(pawns.get(i));
			if (GETZ(p) != 2 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
				continue;
		}
#endif
		res++;
	}
	return res;
}

uint8 State::potentialMorrisCount(pawn player) const {
	uint8 res = 0;

	ExpVector<uint8> empty = getAllPositions(PAWN_NONE);
	for (uint8 i = 0; i < empty.getLogicSize(); i++) {
		if (willBeInMorrisAxis(POS_NULL, empty.get(i), player, X_AXIS))
			res++;
		if (willBeInMorrisAxis(POS_NULL, empty.get(i), player, Y_AXIS))
			res++;
		if (willBeInMorrisAxis(POS_NULL, empty.get(i), player, Z_AXIS))
			res++;
	}

	return res;
}

uint8 State::potentialDoubleMorrisCount(pawn player) const {

	uint8 res = 0;

	ExpVector<uint8> empty = getAllPositions(PAWN_NONE);
	for (uint8 i = 0; i < empty.getLogicSize(); i++) {
		uint8 pos = empty.get(i);
		uint8 app;
		if (willBeInMorrisAxis(POS_NULL, empty.get(i), player, X_AXIS)) {
			for (uint8 j = 0; j < CUBE_SIZE_X - 1; j++) { // 2 iterations
				pos = FWX(pos);
				app = pos;
				for (uint8 k = 0; k < CUBE_SIZE_Y - 1; k++) {
					app = FWY(app);
					if (getPawnAt(GETX(app), GETY(app), GETZ(app)) == PAWN_NONE && willBeInMorrisAxis(POS_NULL, app, player, Y_AXIS))
						res++;
				}
			}
		}
		if (willBeInMorrisAxis(POS_NULL, empty.get(i), player, Y_AXIS)) {
			for (uint8 j = 0; j < CUBE_SIZE_Y - 1; j++) { // 2 iterations
				pos = FWY(pos);
				app = pos;
				for (uint8 k = 0; k < CUBE_SIZE_Z - 1; k++) {
					app = FWZ(app);
					if (getPawnAt(GETX(app), GETY(app), GETZ(app)) == PAWN_NONE && willBeInMorrisAxis(POS_NULL, app, player, Z_AXIS))
						res++;
				}
			}
		}
		if (willBeInMorrisAxis(POS_NULL, empty.get(i), player, Z_AXIS)) {
			for (uint8 j = 0; j < CUBE_SIZE_Z - 1; j++) { // 2 iterations
				pos = FWZ(pos);
				app = pos;
				for (uint8 k = 0; k < CUBE_SIZE_X - 1; k++) {
					app = FWX(app);
					if (getPawnAt(GETX(app), GETY(app), GETZ(app)) == PAWN_NONE && willBeInMorrisAxis(POS_NULL, app, player, X_AXIS))
						res++;
				}
			}
		}
	}

	return res;

}

uint8 State::doubleMorrisCount(pawn player) const {

	uint8 res = 0;

	for (uint8 x = 0; x < CUBE_SIZE_X; x++)
		for (uint8 y = 0; y < CUBE_SIZE_Y; y++)
			if (isInMorrisAxis(NEW_POS(x,y,0), Z_AXIS) && getPawnAt(x,y,0) == player)
				for (uint8 z = 0; z < CUBE_SIZE_Z; z++)
					if (isInMorrisAxis(NEW_POS(x,y,z), X_AXIS))
						res++;
	for (uint8 y = 0; y < CUBE_SIZE_Y; y++)
		for (uint8 z = 0; z < CUBE_SIZE_Z; z++)
			if (isInMorrisAxis(NEW_POS(0,y,z), X_AXIS) && getPawnAt(0,y,z) == player)
				for (uint8 x = 0; x < CUBE_SIZE_X; x++)
					if (isInMorrisAxis(NEW_POS(x,y,z), Y_AXIS))
						res++;

	for (uint8 x = 0; x < CUBE_SIZE_X; x++)
		for (uint8 z = 0; z < CUBE_SIZE_Z; z++)
			if (isInMorrisAxis(NEW_POS(x,0,z), Y_AXIS) && getPawnAt(x,0,z) == player)
				for (uint8 y = 0; y < CUBE_SIZE_Y; y++)
					if (isInMorrisAxis(NEW_POS(x,y,z), Z_AXIS))
						res++;
	return res;

}

bool State::isInMorris(uint8 pos) const {

	bool morrisX = true;
	bool morrisY = true;
	bool morrisZ = true;
	pawn selected = getPawnAt(GETX(pos), GETY(pos), GETZ(pos));

	if (selected == PAWN_NONE)
		return false;

	for (int x = 0; x < CUBE_SIZE_X; x++) {
		if (POS_ENABLED_FAST(x, GETY(pos))) {
			if (getPawnAt(x, GETY(pos), GETZ(pos)) != selected) {
				morrisX = false;
				break;
			}
		}
		else {
			morrisX = false;
			break;
		}
	}


	for (int y = 0; y < CUBE_SIZE_Y; y++) {
		if (POS_ENABLED_FAST(GETX(pos), y)) {
			if (getPawnAt(GETX(pos), y, GETZ(pos)) != selected) {
				morrisY = false;
				break;
			}
		}
		else {
			morrisY = false;
			break;
		}

	}

#if defined(DIAGONALS) && defined(PERPENDICULARS)
	for (int z = 0; z < CUBE_SIZE_Z; z++) {
		if (POS_ENABLED_FAST(GETX(pos), GETY(pos))) {
			if (getPawnAt(GETX(pos), GETY(pos), z) != selected) {
				morrisZ = false;
				break;
			}
		}
		else {
			morrisZ = false;
			break;
		}
	}
#endif

#if !defined(DIAGONALS) && defined(PERPENDICULARS)
	if (ON_PERPENDICULAR(pos)) {
		for (int z = 0; z < CUBE_SIZE_Z; z++) {
			if (POS_ENABLED_FAST(GETX(pos), GETY(pos))) {
				if (getPawnAt(GETX(pos), GETY(pos), z) != selected) {
					morrisZ = false;
					break;
				}
			}
			else {
				morrisZ = false;
				break;
			}
		}
	}
	else
		morrisZ = false;

#endif

#if defined(DIAGONALS) && !defined(PERPENDICULARS)
	if (ON_DIAGONAL(pos)) {
		for (int z = 0; z < CUBE_SIZE_Z; z++) {
			if (POS_ENABLED_FAST(GETX(pos), GETY(pos))) {
				if (getPawnAt(GETX(pos), GETY(pos), z) != selected) {
					morrisZ = false;
					break;
				}
			}
			else {
				morrisZ = false;
				break;
			}
		}
	}
	else
		morrisZ = false;
#endif

	return morrisX || morrisY || morrisZ;

}

bool State::isInMorrisAxis(uint8 pos, uint8 axis) const {

	pawn selected = getPawnAt(GETX(pos), GETY(pos), GETZ(pos));

	if (selected == PAWN_NONE)
		return false;

	if (axis == X_AXIS) {
		for (int x = 0; x < CUBE_SIZE_X; x++) {
			if (POS_ENABLED_FAST(x, GETY(pos))) {
				if (getPawnAt(x, GETY(pos), GETZ(pos)) != selected)
					return false;
			}
			else
				return false;
		}
		return true;
	}

	else if (axis == Y_AXIS) {
		for (int y = 0; y < CUBE_SIZE_Y; y++) {
			if (POS_ENABLED_FAST(GETX(pos), y)) {
				if (getPawnAt(GETX(pos), y, GETZ(pos)) != selected)
					return false;
			}
			else
				return false;
		}
		return true;
	}

	else if (axis == Z_AXIS) {
#if defined(DIAGONALS) && defined(PERPENDICULARS)
		for (int z = 0; z < CUBE_SIZE_Z; z++) {
			if (POS_ENABLED_FAST(GETX(pos), GETY(pos))) {
				if (getPawnAt(GETX(pos), GETY(pos), z) != selected)
					return false;
			}
			else
				return false;
		}
		return true;
#endif

#if !defined(DIAGONALS) && defined(PERPENDICULARS)
		if (ON_PERPENDICULAR(pos)) {
			for (int z = 0; z < CUBE_SIZE_Z; z++) {
				if (POS_ENABLED_FAST(GETX(pos), GETY(pos))) {
					if (getPawnAt(GETX(pos), GETY(pos), z) != selected)
						return false;
				}
				else
					return false;
			}
			return true;
		}
		else
			return false;

#endif

#if defined(DIAGONALS) && !defined(PERPENDICULARS)
		if (ON_DIAGONAL(pos)) {
			for (int z = 0; z < CUBE_SIZE_Z; z++) {
				if (POS_ENABLED_FAST(GETX(pos), GETY(pos))) {
					if (getPawnAt(GETX(pos), GETY(pos), z) != selected)
						return false;
				}
				else
					return false;
			}
			return true;
		}
		else
			return false;
#endif
	}
	return false;
}

bool State::willBeInMorris(uint8 src, uint8 dest, pawn pawn) const {

	bool morrisX = true;
	bool morrisY = true;
	bool morrisZ = true;

	if (pawn == PAWN_NONE)
		return false;

	if (getPawnAt(GETX(dest), GETY(dest), GETZ(dest)) != PAWN_NONE)
		return false;

	for (int x = 0; x < CUBE_SIZE_X; x++) {
		if (src == NEW_POS(x,GETY(dest), GETZ(dest))) {
			morrisX = false;
			break;
		}
		if (!POS_ENABLED_FAST(x, GETY(dest))) {
			morrisX = false;
			break;
		}
		if (x != GETX(dest)) {
			if (getPawnAt(x, GETY(dest), GETZ(dest)) != pawn) {
				morrisX = false;
				break;
			}
		}
	}

	for (int y = 0; y < CUBE_SIZE_Y; y++) {
		if (src == NEW_POS(GETX(dest), y, GETZ(dest))) {
			morrisY = false;
			break;
		}
		if (!POS_ENABLED_FAST(GETX(dest), y)) {
			morrisY = false;
			break;
		}
		if (y != GETY(dest)) {
			if (getPawnAt(GETX(dest), y, GETZ(dest)) != pawn) {
				morrisY = false;
				break;
			}
		}
	}

#if defined(DIAGONALS) && defined(PERPENDICULARS)
	for (int z = 0; z < CUBE_SIZE_Z; z++) {
		if (src == NEW_POS(GETX(dest), GETY(dest), z)) {
			morrisZ = false;
			break;
		}
		if (!POS_ENABLED_FAST(GETX(dest), GETY(dest))) {
			morrisZ = false;
			break;
		}
		if (z != GETZ(dest)) {
			if (getPawnAt(GETX(dest), GETY(dest), z) != pawn) {
				morrisZ = false;
				break;
			}
		}
	}
#endif

#if !defined(DIAGONALS) && defined(PERPENDICULARS)
	if (ON_PERPENDICULAR(dest))
		for (int z = 0; z < CUBE_SIZE_Z; z++) {
			if (src == NEW_POS(GETX(dest), GETY(dest), z)) {
				morrisZ = false;
				break;
			}
			if (!POS_ENABLED_FAST(GETX(dest), GETY(dest))) {
				morrisZ = false;
				break;
			}
			if (z != GETZ(dest)) {
				if (getPawnAt(GETX(dest), GETY(dest), z) != pawn) {
					morrisZ = false;
					break;
				}
			}
		}
	else
		morrisZ = false;
#endif

#if defined(DIAGONALS) && !defined(PERPENDICULARS)
	if (ON_DIAGONAL(dest))
		for (int z = 0; z < CUBE_SIZE_Z; z++) {
			if (src == NEW_POS(GETX(dest), GETY(dest), z)) {
				morrisZ = false;
				break;
			}
			if (!POS_ENABLED_FAST(GETX(dest), GETY(dest))) {
				morrisZ = false;
				break;
			}
			if (z != GETZ(dest)) {
				if (getPawnAt(GETX(dest), GETY(dest), z) != pawn) {
					morrisZ = false;
					break;
				}
			}
		}
	else
		morrisZ = false;
#endif

	return morrisX || morrisY || morrisZ;
}

bool State::willBeInMorrisAxis(uint8 src, uint8 dest, pawn pawn, uint8 axis) const {

	if (pawn == PAWN_NONE)
		return false;

	if (getPawnAt(GETX(dest), GETY(dest), GETZ(dest)) != PAWN_NONE)
		return false;

	if (axis == X_AXIS) {
		for (int x = 0; x < CUBE_SIZE_X; x++) {
			if (src == NEW_POS(x,GETY(dest), GETZ(dest)))
				return false;
			if (!POS_ENABLED_FAST(x, GETY(dest)))
				return false;
			if (x != GETX(dest)) {
				if (getPawnAt(x, GETY(dest), GETZ(dest)) != pawn)
					return false;
			}
		}
		return true;
	}

	else if (axis == Y_AXIS) {
		for (int y = 0; y < CUBE_SIZE_Y; y++) {
			if (src == NEW_POS(GETX(dest), y, GETZ(dest)))
				return false;
			if (!POS_ENABLED_FAST(GETX(dest), y))
				return false;
			if (y != GETY(dest)) {
				if (getPawnAt(GETX(dest), y, GETZ(dest)) != pawn)
					return false;
			}
		}
		return true;
	}

	else if (axis == Z_AXIS) {
#if defined(DIAGONALS) && defined(PERPENDICULARS)
		for (int z = 0; z < CUBE_SIZE_Z; z++) {
			if (src == NEW_POS(GETX(dest), GETY(dest), z))
				return false;
			if (!POS_ENABLED_FAST(GETX(dest), GETY(dest)))
				return false;
			if (z != GETZ(dest)) {
				if (getPawnAt(GETX(dest), GETY(dest), z) != pawn)
					return false;
			}
		}
		return true;
#endif

#if !defined(DIAGONALS) && defined(PERPENDICULARS)
		if (ON_PERPENDICULAR(dest)) {
			for (int z = 0; z < CUBE_SIZE_Z; z++) {
				if (src == NEW_POS(GETX(dest), GETY(dest), z))
					return false;
				if (!POS_ENABLED_FAST(GETX(dest), GETY(dest)))
					return false;
				if (z != GETZ(dest)) {
					if (getPawnAt(GETX(dest), GETY(dest), z) != pawn)
						return false;
				}
			}
			return true;
		}
		else
			return false;
#endif

#if defined(DIAGONALS) && !defined(PERPENDICULARS)
		if (ON_DIAGONAL(dest)) {
			for (int z = 0; z < CUBE_SIZE_Z; z++) {
				if (src == NEW_POS(GETX(dest), GETY(dest), z))
					return false;
				if (!POS_ENABLED_FAST(GETX(dest), GETY(dest)))
					return false;
				if (z != GETZ(dest)) {
					if (getPawnAt(GETX(dest), GETY(dest), z) != pawn)
						return false;
				}
			}
			return true;
		}
		else
			return false;
#endif
	}
	return false;
}

ExpVector<uint8> State::getAllPositions(pawn pawn) const {

	ExpVector<uint8> result(AVERAGE_PAWNS_ON_BOARD);

	for (uint8 x = 0; x < CUBE_SIZE_X; x++)
		for (uint8 y = 0; y < CUBE_SIZE_Y; y++)
			for (uint8 z = 0; z < CUBE_SIZE_Z; z++)
				if (getPawnAt(x, y, z) == pawn && POS_ENABLED_FAST(x,y)) {
					result.add(NEW_POS(x,y,z));
				}

	return result;

}

ExpVector<uint8> State::getAvailablePositions(uint8 pos) const {

	pawn myPawn = getPawnAt(GETX(pos), GETY(pos), GETZ(pos));

	if (getPawnsToPlay(getPlayer()) > 0 || getPawnsOnBoard(myPawn) == 3)
		return getAllPositions(PAWN_NONE);

	ExpVector<uint8> result(MAX_MOVES_PHASE_2);
	uint8 p;

	p = FWX(pos);
	if (GETX(p) != 0 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
		result.add(p);

	p = BWX(pos);
	if (GETX(p) != 2 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
		result.add(p);

	p = FWY(pos);
	if (GETY(p) != 0 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
		result.add(p);

	p = BWY(pos);
	if (GETY(p) != 2 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
		result.add(p);

#if defined(DIAGONALS) && defined(PERPENDICULARS)
	p = FWZ(pos);
	if (GETZ(p) != 0 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
		result.add(p);

	p = BWZ(pos);
	if (GETZ(p) != 2 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
		result.add(p);
#endif

#if !defined(DIAGONALS) && defined(PERPENDICULARS)
	p = FWZ(pos);
	if (ON_PERPENDICULAR(p)) {
		if (GETZ(p) != 0 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
			result.add(p);

		p = BWZ(pos);
		if (GETZ(p) != 2 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
			result.add(p);
	}
#endif

#if defined(DIAGONALS) && !defined(PERPENDICULARS)
	p = FWZ(pos);
	if (ON_DIAGONAL(p)) {
		if (GETZ(p) != 0 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
			result.add(p);

		p = BWZ(pos);
		if (GETZ(p) != 2 && getPawnAt(GETX(p), GETY(p), GETZ(p)) == PAWN_NONE && POS_ENABLED(p))
			result.add(p);
	}
#endif

	return result;

}

ExpVector<Action> * State::getActions() const {

	ExpVector<Action> * result = new ExpVector<Action>(ACTION_VECTOR_DEFAULT_SIZE);

	if (getPawnsToPlay(getPlayer()) > 0) {
		*result = addActionsForPawn(POS_NULL, *result);
	}
	else {
		ExpVector<uint8> myPawns = getAllPositions(getPlayer());
		for (uint8 k = 0; k < myPawns.getLogicSize(); k++)
			*result = addActionsForPawn(myPawns.get(k), *result);
	}

	return result;

}

State * State::result(Action action) const {

	State * state = clone();

	uint8 src = action.getSrc();
	uint8 dest = action.getDest();
	uint8 toRemove = action.getRemovedPawn();

	// fase 1 (pedina in dest)
	if(!IS_VALID(src) && IS_VALID(dest)) {
		state->setPawnAt(GETX(dest), GETY(dest), GETZ(dest), getPlayer());
		state->setPawnsOnBoard(getPlayer(), state->getPawnsOnBoard(getPlayer()) + 1);
		state->setPawnsToPlay(getPlayer(), state->getPawnsToPlay(getPlayer()) - 1);
	}
	// fasi 2 e 3 (pedina da src a dest)
	if(IS_VALID(src) && IS_VALID(dest)) {
		state->setPawnAt(GETX(src), GETY(src), GETZ(src), PAWN_NONE);
		state->setPawnAt(GETX(dest), GETY(dest), GETZ(dest), getPlayer());
	}

	// rimozione pedina avversaria
	if(IS_VALID(toRemove)) {
		state->setPawnAt(GETX(toRemove), GETY(toRemove), GETZ(toRemove), PAWN_NONE);
		state->setPawnsOnBoard(OPP(getPlayer()), state->getPawnsOnBoard(OPP(getPlayer())) - 1);
	}

	state->setMorrisLastTurn(getPlayer(), IS_VALID(toRemove));
	state->setPlayer(OPP(getPlayer()));

	return state;

}

ExpVector<Action> State::addActionsForPawn(uint8 src, ExpVector<Action> actionBuffer) const {

	ExpVector<uint8> available = getAvailablePositions(src);
	for (uint8 i = 0; i < available.getLogicSize(); i++) {
		if (willBeInMorris(src, available.get(i), getPlayer())) {
			ExpVector<uint8> pos = getAllPositions(OPP(getPlayer()));
			bool added = false;
			for (uint8 j = 0; j < pos.getLogicSize(); j++)
				if (!isInMorris(pos.get(j))) {
					added = true;
					actionBuffer.add(Action(src, available.get(i), pos.get(j)));
				}
			if (!added)
				for (uint8 j = 0; j < pos.getLogicSize(); j++)
					actionBuffer.add(Action(src, available.get(i), pos.get(j)));
		}
		else
			actionBuffer.add(Action(src, available.get(i), POS_NULL));
	}

	return actionBuffer;

}

bool State::isTerminal() const {

	if (getPawnsToPlay(getPlayer()) > 0)
		return false;

	ExpVector<Action> * actions = getActions();
	bool result;

	result = (getPawnsOnBoard(PAWN_WHITE) < 3 || getPawnsOnBoard(PAWN_BLACK) < 3 || actions->getLogicSize() == 0);
	delete actions;

	return result;
}

sint8 State::utility() const {

	return getPlayer() == PAWN_WHITE ? -MAX_EVAL_T : MAX_EVAL_T;

}
