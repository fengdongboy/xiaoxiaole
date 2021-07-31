#pragma once
#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__
/*!
 * \class classname
 *
 * \brief π‹¿Ì¿‡
 *
 * \author fdl
 * \date 2021/06/19
 */

#include "typedef.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	void init(void);
	void update(void);
	void print(void);
	void check(int x, int y);

	void checkData(void);

	CellState getNeighbour(const Pos& pos, neighbour n, Pos& outPos);

private:
	int mCells[GAME_ROWS][GAME_CLOS];
};

#endif