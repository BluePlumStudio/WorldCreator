#include "Blocks.h"

using namespace std;

Blocks::Blocks()
{
	data.push_back(new BlockAir);
	data.push_back(new BlockStone);
	data.push_back(new BlockGrass);
	data.push_back(new BlockDirt);
	data.push_back(new BlockCobblestone);
}

Blocks::~Blocks()
{
	for (vector<Block *>::iterator it = data.begin(); it != data.end(); ++it)
	{
		cout << "Blocks£º" << (*it)->getID() << " " << (*it)->getName() << " Îö¹¹£¡" << endl;
		delete *it;
	}
	data.clear();
}
