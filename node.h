#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include "vertex.h"

class Node : public Vertex {
	public:
		int id = -1;
		std::vector<bool> stepPoint;
		int gameNumber = 0;
		bool visited = false;
		int direction = 0;
		Node* pPreviousN = nullptr;
		Node* pNextN = nullptr;
		
		Node() {
		}
		
		Node(int x, int y, int rowCount, int columnCount, int type) :
			Vertex(x, y, rowCount, columnCount, type),
			id(x + y * columnCount)  {
			}
			
		Node(Node* pNode) {
			x = pNode->x;
			y = pNode->y;
			rowCount = pNode->rowCount;
			columnCount = pNode->columnCount;
			type = pNode->type;
			id = pNode->id;
			visited = pNode->visited;
			pPreviousN = pNode->pPreviousN;
			pNextN = pNode->pNextN;
		}
		
		void GetMapType(Node* pNode) {
			type = pNode->type;
		}
			
		FirstNode(int gameNumber) {
			visited = true;
			this->gameNumber = gameNumber;
			stepPoint.resize(1);
			stepPoint[0] = true;
		}
};

#endif
