#include "GameManager.h"


#include <algorithm>
#include<random>
#include <iostream>

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::init(void)
{
	for (auto& d : mCells)
	{
		std::fill(std::begin(d), std::end(d), cell_empty);
	}

	auto checkPos = [=](const Pos& pos, CellState s) 
	{
		int sum = 0;
		for (int i = pos.x-1;i >=0,i>=pos.x-2;i --)
		{
			if (mCells[pos.y][i] == s)
				sum++;
		}
		if (sum==2)		
			return false;
		sum = 0;
		for (int i = pos.y - 1; i >= 0, i >= pos.y - 2; i--)
		{
			if (mCells[i][pos.x] == s)
				sum++;
		}
		if (sum == 2)
			return false;

		return true;
	};

	std::default_random_engine g;
	std::uniform_int_distribution<int> rand(cell_empty, cell_type3);
	for (int i = 0; i < GAME_ROWS; i++)
	{
		for (int j = 0; j < GAME_CLOS; j++)
		{
			for (int k = 0; k <= 10; k++)
			{
				CellState d = (CellState)rand(g);
				bool b = checkPos(Pos(i, j), d);
				if (b)
				{
					mCells[j][i] = d;
					break;
				}
			}			
		}
	}
}

void GameManager::update(void)
{
	for (int i = 0; i < GAME_CLOS; i++)
	{
		for (int j = GAME_ROWS-1; j>=0; j--)
		{
			/// 重力模拟
			if (mCells[j][i] == cell_empty)
			{
				for (int m = j; m>0;m--)
				{
					mCells[m][i] = mCells[m - 1][i];
				}
			}
		}
	}
}

void GameManager::print(void)
{
	int index = 0;
	for (auto &row : mCells) 
	{
		std::cout << index++ << ":";
		for (auto &col : row) 
		{
			std::cout << col << "    ";
		}
		std::cout << std::endl;
	}
}

void GameManager::checkData(void)
{
	LineTwos lines;
	for (int j = 0; j < GAME_ROWS; j++)
	for (int i = 0; i < GAME_CLOS;i++)
	{
		if (i>0)
		{
			if (mCells[j][i-1] == mCells[j][i] && mCells[j][i]>0)
			{
				lines.push_back(LineTwo(Pos(i-1,j), LineType_horizontal,(CellState) mCells[j][i]));
			}
		}
		if (j > 0)
		{
			if (mCells[j - 1][i] == mCells[j][i]&& mCells[j][i]>0)
			{
				lines.push_back(LineTwo(Pos(i, j-1), LineType_vertical, (CellState)mCells[j][i]));
			}
		}
	}

	std::sort(lines.begin(), lines.end(), [](const LineTwo&one, const LineTwo&two) {return one.cellType < two.cellType; });

	Swips swips;
	Pos pos, outPos;
	Swip s;
	for (int i = 0; i < lines.size();i++)
	{
		for (int j = i+1; j < lines.size(); j++)
		{
			if (lines[i].cellType != lines[j].cellType)			
				break;
			auto t = lines[i].checkLineTwo(lines[j], pos);
			if (t == SwipType_null)
				continue;

			if (t == SwipType_5_5)
			{
				if (lines[i].type == LineType_horizontal &&( lines[i].cellType == getNeighbour(pos, neighbour_top, outPos) || lines[i].cellType == getNeighbour(pos, neighbour_bottom, outPos)))
				{
					s.pos = outPos;
					s.type = LineType_horizontal;
					s.score = 100;
					swips.push_back(s);
				}
				else if (lines[i].type == LineType_vertical &&( lines[i].cellType == getNeighbour(pos, neighbour_left, outPos) || lines[i].cellType == getNeighbour(pos, neighbour_right, outPos)))
				{
					s.pos = outPos;
					s.type = LineType_vertical;
					s.score = 100;
					swips.push_back(s);
				}
			}
			else if (t == SwipType_3_3)
			{
				if (lines[i].getHead() == lines[j].getTail())
				{
					if (lines[i].type == LineType_horizontal && lines[i].cellType ==getNeighbour(pos, neighbour_left, outPos))
					{
						s.pos = outPos;
						s.type = LineType_horizontal;
						s.score = 80;
						swips.push_back(s);
					}
					else if (lines[i].type == LineType_vertical && lines[i].cellType == getNeighbour(pos, neighbour_top, outPos))
					{
						s.pos = outPos;
						s.type = LineType_vertical;
						s.score = 80;
						swips.push_back(s);
					}
				}
				else if (lines[i].getTail() == lines[j].getHead() )
				{					
					if (lines[i].type == LineType_horizontal && lines[i].cellType ==getNeighbour(pos, neighbour_right, outPos))
					{
						s.pos = pos;
						s.type = LineType_horizontal;
						s.score = 80;
						swips.push_back(s);
					}
					else if (lines[i].type == LineType_vertical && lines[i].cellType == getNeighbour(pos, neighbour_bottom, outPos))
					{
						s.pos = pos;
						s.type = LineType_vertical;
						s.score = 80;
						swips.push_back(s);
					}
				}
			}
		}
	}

	if (!swips.empty())
	{
		std::sort(swips.begin(), swips.end(), [](const Swip& first, const Swip& second) {return first.score > second.score; });
		if (swips[0].type = LineType_horizontal)
			getNeighbour(swips[0].pos, neighbour_right, outPos);
		else
			getNeighbour(swips[0].pos, neighbour_bottom, outPos);

		std::cout << "pos(" << swips[0].pos.y << "," << swips[0].pos.x << ") 和" << "pos(" << outPos.y << "," << outPos.x << ")" << "type:" << swips[0].type << std::endl;
		std::swap(mCells[swips[0].pos.y][swips[0].pos.x], mCells[outPos.y][outPos.x]);
	}
	else
	{
		CellState left, right, top, botton;
		Pos outPosL, outPosR, outPosT, outPosB;
		for (int i = 0; i < lines.size(); i ++)
		{
			left = getNeighbour(lines[i].getHead(), neighbour_left, outPosL);
			right = getNeighbour(lines[i].getHead(), neighbour_right, outPosR);
			top = getNeighbour(lines[i].getHead(), neighbour_top, outPosT);
			botton = getNeighbour(lines[i].getHead(), neighbour_bottom, outPosB);

			if (lines[i].cellType == left )
			{
				s.pos = outPosL;
				s.score = 70;
				s.type = LineType_horizontal;
				swips.push_back(s);
			}
			else if (lines[i].cellType == right && lines[i].type == LineType_vertical)
			{
				s.pos = outPosR;
				s.score = 70;
				s.type = LineType_vertical;
				swips.push_back(s);
			}
			else if (lines[i].cellType == top)
			{
				s.pos = outPosT;
				s.score = 70;
				s.type = LineType_vertical;
				swips.push_back(s);
			}
			else if (lines[i].cellType == botton && lines[i].type == LineType_horizontal)
			{
				s.pos = lines[i].getHead();
				s.score = 70;
				s.type = LineType_vertical;
				swips.push_back(s);
			}			
		}

		std::sort(swips.begin(), swips.end(), [](const Swip& first, const Swip& second) {return first.score > second.score; });
		if (swips[0].type = LineType_horizontal)
			getNeighbour(swips[0].pos, neighbour_right, outPos);
		else
			getNeighbour(swips[0].pos, neighbour_bottom, outPos);

		std::cout << "pos(" << swips[0].pos.y << "," << swips[0].pos.x << ") 和" << "pos(" << outPos.y << "," << outPos.x << ")" << "type:" << swips[0].type << std::endl;
		std::swap(mCells[swips[0].pos.y][swips[0].pos.x], mCells[outPos.y][outPos.x]);
	}
}

CellState GameManager::getNeighbour(const Pos& pos, neighbour n, Pos& outPos)
{
	int x = pos.x;
	int y = pos.y;
	switch (n)
	{
	case neighbour_left:
		x--;
		break;
	case neighbour_right:
		x++;
		break;
	case neighbour_top:
		y--;
		break;
	case neighbour_bottom:
		y++;
		break;
	}
	outPos.x = x;
	outPos.y = y;
	if (x < 0 || x >= GAME_CLOS || y < 0 || y >= GAME_ROWS)
	{
		return cell_empty;
	}
	return (CellState)mCells[y][x];
}
