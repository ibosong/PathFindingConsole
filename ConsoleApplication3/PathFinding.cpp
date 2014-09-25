#include "PathFinding.h"
#include <algorithm>

bool compa(PathFindNode* n1, PathFindNode* n2)
{
	return n1->weight > n2->weight;
}


std::vector<PathFindNode*> PathFinding::m_openList = std::vector<PathFindNode*>();
std::vector<PathFindNode*> PathFinding::m_closeList = std::vector<PathFindNode*>();

PathFindNode* PathFinding::Contains(std::vector<PathFindNode*> nodes, PathFindNode* node)
{
	if (nodes.size() == 0)
	{
		return nullptr;
	}
	auto it = std::find_if(nodes.begin(), nodes.end(), [=](PathFindNode* tempNode){
		return tempNode->position.x == node->position.x &&
			tempNode->position.y == node->position.y &&
			tempNode->position.z == node->position.z;
	});

	if (it == nodes.end())
	{
		return nullptr;
	}
	else
	{
		return *it;
	}
}

std::vector<PathFindNode*> PathFinding::SurroundPoints(PathFindNode* node, std::function<bool(int, int)> isAvailable)
{
	std::vector<PathFindNode*> nodes = std::vector<PathFindNode*>();
	PathFindNode* rightNode = new PathFindNode();
	rightNode->position = XMFLOAT3(node->position.x + 1, node->position.y, node->position.z);
	if (Contains(m_closeList, rightNode) == nullptr && isAvailable((int)rightNode->position.x, (int)rightNode->position.y))
	{		
		if (Contains(m_openList, rightNode) == nullptr)
		{
			rightNode->parent = node;
		}
		nodes.push_back(rightNode);
	}

	PathFindNode* leftNode = new PathFindNode();
	leftNode->position = XMFLOAT3(node->position.x - 1, node->position.y, node->position.z);
	if (Contains(m_closeList, leftNode) == nullptr&& isAvailable((int)leftNode->position.x, (int)leftNode->position.y))
	{
		if (Contains(m_openList, leftNode) == nullptr)
		{
			leftNode->parent = node;
		}
		nodes.push_back(leftNode);
	}

	PathFindNode* upNode = new PathFindNode();
	
	upNode->position = XMFLOAT3(node->position.x, node->position.y + 1, node->position.z);
	if (Contains(m_closeList, upNode) == nullptr&& isAvailable((int)upNode->position.x, (int)upNode->position.y))
	{
		if (Contains(m_openList, upNode) == nullptr)
		{
			upNode->parent = node;
		}
		nodes.push_back(upNode);
	}


	PathFindNode* downNode = new PathFindNode();
	
	downNode->position = XMFLOAT3(node->position.x, node->position.y - 1, node->position.z);
	if (Contains(m_closeList, downNode) == nullptr&& isAvailable((int)downNode->position.x, (int)upNode->position.y))
	{
		if (Contains(m_openList, downNode) == nullptr)
		{
			downNode->parent = node;
		}
		nodes.push_back(downNode);
	}

	return nodes;
}

PathFindNode* PathFinding::FindPath(PathFindNode* start, PathFindNode* goal, std::function<bool(int, int)> isAvailable)
{
	PathFindNode* tempNode = start;
	while (tempNode->position.x != goal->position.x || 
		tempNode->position.y != goal->position.y ||
		tempNode->position.z != goal->position.z)
	{
		m_closeList.push_back(tempNode);
		for (PathFindNode* node : SurroundPoints(tempNode, isAvailable))
		{

			// Find that node is in the open list.
			if (Contains(m_openList, node) != nullptr)
			{
				node = Contains(m_openList, node);
				if (node->GetgWeight(tempNode->position) < node->gWeight)
				{
					node->parent = tempNode;
					node->gWeight = node->GetgWeight(tempNode->position);
					node->CalculateWeight(tempNode->position, goal->position);
				}
			}
			else
			{
				node->CalculateWeight(tempNode->position, goal->position);
			}

			m_openList.push_back(node);

		}

		std::sort(m_openList.begin(), m_openList.end(), compa);
		// The node whose weight is the smallest.
		PathFindNode* node = *(m_openList.end() - 1);
		m_openList.erase(m_openList.end() - 1);
		tempNode = node;
	}
	return tempNode;
}
