#pragma once
#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__
#include <vector>

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
	Pos(int x_=0,int y_=0):x(x_),y(y_){}
	bool operator==(const Pos& other)
	{
		return (x == other.x && y == other.y);
	}
};

enum LineType
{
	LineType_horizontal,		/// 水平
	LineType_vertical			/// 垂直
};

enum SwipType
{
	SwipType_null = -1,
	SwipType_3_h = 0,
	SwipType_3_v,
	SwipType_4_h,
	SwipType_4_v,
	SwipType_5_5,
	SwipType_3_3
};

enum neighbour
{
	neighbour_left = 0,
	neighbour_right,
	neighbour_top,
	neighbour_bottom
};


struct LineTwo		/// 二元素体
{
	Pos pos;				/// 位置
	LineType type;			/// 水平还是垂直
	CellState cellType;		/// 什么颜色的

	LineTwo():type(LineType_horizontal),cellType(cell_empty){}
	LineTwo(const Pos& p, LineType lt, CellState ct):pos(p), type(lt),cellType(ct){}

	Pos getHead(void) const
	{
		Pos p;
		if (type == LineType_horizontal)
		{
			p.x = pos.x - 1;
			p.y = pos.y;
		}
		else
		{
			p.x = pos.x;
			p.y = pos.y - 1;
		}
		return p;
	}

	Pos getTail(void) const
	{
		Pos p;
		if (type == LineType_horizontal)
		{
			p.x = pos.x +2;
			p.y = pos.y;
		}
		else
		{
			p.x = pos.x;
			p.y = pos.y +2;
		}
		return p;
	}

	auto checkLineTwo(const LineTwo& other, Pos& p) const
	{
		if (cellType != other.cellType)
			return SwipType_null;

		if (getHead() == other.getTail() || other.getHead() == getTail())
		{
			p = getHead() == other.getTail() ? getHead() : getTail();
			if (type == other.type)
			{
				return SwipType_5_5;
			}
			else
			{
				return SwipType_3_3;
			}
		}
		return SwipType_null;
	}
};


typedef std::vector<LineTwo> LineTwos;

struct Swip
{
	Pos pos;				/// 位置
	LineType type;			/// 水平还是垂直
	int score;				/// 得分
	Swip():type(LineType_horizontal),score(-1){}

};
typedef std::vector<Swip> Swips;

#define GAME_CLOS 20
#define GAME_ROWS 20

#endif