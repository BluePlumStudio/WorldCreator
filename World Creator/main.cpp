#include "Game.h"

using namespace std;
Game WorldCreator;
int main()
{
	if (WorldCreator.init())
	{
		return EXIT_FAILURE;
	}
	/*
	{
		std::vector<int> v;
		for (size_t i = 0; i < 128; i++)
		{
			v.push_back(128 - i);
		}
		double begin = glfwGetTime();
		
		sort(v.begin(), v.end());
		cout << glfwGetTime() - begin << endl;
	}
	*/
	//return 0;
	
	WorldCreator.run();
#ifndef _DEBUG
	system("pause");
#endif
	return 0;
}