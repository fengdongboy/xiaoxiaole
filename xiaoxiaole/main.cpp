#include "GameManager.h"
#include <iostream>
int main()
{
	GameManager g;
	g.init();
	g.print();
	g.checkData();
	std::cout << "½á¹û:" << std::endl;
	g.print();
	return 0;
}