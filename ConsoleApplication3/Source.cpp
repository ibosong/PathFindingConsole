#include <memory>
#include <functional>
#include <iostream>
#include "PathFinding.h"

int array[][12] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1 },
		{ 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

bool isAvailable(int x, int y)
{
	if (array[x][y] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main(){
	
	PathFindNode * start = new PathFindNode();
	start->position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	PathFindNode * end = new PathFindNode();
	end->position = XMFLOAT3(6.0f, 10.0f, 0.0f);
	PathFindNode* node = PathFinding::FindPath(start, end, isAvailable);
	if (node == nullptr)
	{
		std::cout << "Not find the path." << std::endl;
	}
	else
	{
		while (node->parent != nullptr)
		{
			std::cout << node->position.x << " " << node->position.y << std::endl;
			node = node->parent;
		}
	}
	
	return 0;
}