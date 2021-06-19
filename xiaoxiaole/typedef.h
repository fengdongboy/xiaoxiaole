#pragma once
#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

enum CellState
{
	cell_empty = -1,
	cell_type0 = 1,
	cell_type1,
	cell_type2,
	cell_type3
};

struct Pos
{
	int x;
	int y;

};

#define GAME_CLOS 20
#define GAME_ROWS 20

#endif