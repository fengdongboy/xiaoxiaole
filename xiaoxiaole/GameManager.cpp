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
	std::fill(std::begin(mCells), std::end(mCells), cell_empty);
	std::default_random_engine e;
	for (int i = 0; i < GAME_ROWS; i++)
	{
		for (int j = 0; j < GAME_CLOS; j++)
		{

		}
	}
}

void GameManager::update(void)
{
	for (int i = 0; i < GAME_CLOS; i++)
	{
		for (int j = GAME_ROWS-1; j>=0; j--)
		{
			/// ÖØÁ¦Ä£Äâ
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
	for (auto &row : mCells) 
	{
		for (auto &col : row) 
		{
			std::cout << col << " ";
		}
		std::cout << std::endl;
	}
}
