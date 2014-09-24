#include <memory>
#include <functional>
#include <iostream>
#include "PathFinding.h"

int main(){
	
	PathFindNode * start = new PathFindNode();
	start->position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	PathFindNode * end = new PathFindNode();
	end->position = XMFLOAT3(6.0f, 10.0f, 0.0f);
	PathFindNode* node = PathFinding::FindPath(start, end);
	while (node->parent != nullptr)
	{
		std::cout << node->position.x << " " << node->position.y << std::endl;
		node = node->parent;
	}
	return 0;
}