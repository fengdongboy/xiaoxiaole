#include "GameManager.h"
#include <iostream>
int main()
{
	GameManager g;
	g.init();
	g.print();
	g.checkData();
	std::cout << "���:" << std::endl;
	g.print();
	return 0;
}