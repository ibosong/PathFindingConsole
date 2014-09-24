#pragma once
#include <DirectXMath.h>
#include <vector>
using namespace DirectX;
struct PathFindNode
{
	PathFindNode* parent = nullptr;
	XMFLOAT3 position{ 0.0f, 0.0f, 0.0f };
	int weight = 0;
	int gWeight = 0;
	const bool operator > (const PathFindNode& node)
	{
		return this->weight > node.weight;
	}
	const bool operator < (const PathFindNode& node)
	{
		return this->weight < node.weight;
	}
	const bool operator == (const PathFindNode* node)
	{
		return this->position.x == node->position.x &&
			this->position.y == node->position.y &&
			this->position.z == node->position.z;
	}
	

	int GetgWeight(XMFLOAT3 start)
	{
		if (parent != nullptr)
		{
			return std::abs((int)(position.x - start.x)) + std::abs((int)(position.y - start.y)) + parent->gWeight;

		}
		else
		{
			return std::abs((int)(position.x - start.x)) + std::abs((int)(position.y - start.y));
		}
	}

	void CalculateWeight(XMFLOAT3 start, XMFLOAT3 goal)
	{
		gWeight = GetgWeight(start);
		int H = std::abs((int)(position.x - goal.x)) + std::abs((int)(position.y - goal.y));
		weight = gWeight + H;
	}
};

class PathFinding
{
public:
	static PathFindNode* FindPath(PathFindNode* start, PathFindNode* goal);

private:
	static std::vector<PathFindNode*> SurroundPoints(PathFindNode* node);
	static PathFindNode* Contains(std::vector<PathFindNode*> nodes, PathFindNode* node);
	static std::vector<PathFindNode*> m_openList;
	static std::vector<PathFindNode*> m_closeList;
};

