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
	
	std::shared_ptr<PathFindNode> start = std::make_shared<PathFindNode>();
	start->position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	std::shared_ptr<PathFindNode> end = std::make_shared<PathFindNode>();
	end->position = XMFLOAT3(6.0f, 10.0f, 0.0f);
	PathFinding pathFinding;
	std::shared_ptr<PathFindNode> node = pathFinding.FindPath(start, end, isAvailable);
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