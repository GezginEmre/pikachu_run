#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <vector>

#include "vertex.h"
#include "node.h"

class Route {
	public:
		int id = -1;
		std::vector<Vertex*> vertexChainFiFo;
		int health = 10;
		int length = 0;
		
	Route(int routeNumber) {
		id = routeNumber;
	}
	
	void operator = (Route route) {
		id = route.id;
		health = route.health;
		length = route.length;
		
		vertexChainFiFo.clear();
		
		for (int index = 0; index < route.vertexChainFiFo.size(); index++)  {
			vertexChainFiFo.push_back(new Vertex(route.vertexChainFiFo.at(index)));
		}
	}
		
	bool CheckLeftNode(Node*& pNextNode, Node* pCurrentNode, Node*** map, int oldGameNumber, int oldStepNumber) {
		if (pCurrentNode->x - 1 < 0)
			return false;

		if (map[pCurrentNode->y][pCurrentNode->x - 1]->stepPoint.size() < oldStepNumber + 1)
			map[pCurrentNode->y][pCurrentNode->x - 1]->stepPoint.resize(oldStepNumber + 1);
			
		bool isVisited = 
			map[pCurrentNode->y][pCurrentNode->x - 1]->type == 0 ||
			(map[pCurrentNode->y][pCurrentNode-> x - 1]->visited &&
			map[pCurrentNode->y][pCurrentNode->x - 1]->gameNumber == pCurrentNode->gameNumber) ||
			map[pCurrentNode->y][pCurrentNode->x - 1]->stepPoint.at(oldStepNumber);
		
		if (!isVisited) {
			pNextNode = map[pCurrentNode->y][pCurrentNode->x - 1];
			pCurrentNode->direction = 1;
		}
		
		return !isVisited;
	}

	bool CheckUpNode(Node*& pNextNode, Node* pCurrentNode, Node*** map, int oldGameNumber, int oldStepNumber) {
		if (pCurrentNode->y - 1 < 0)
			return false;
	
		if (map[pCurrentNode->y - 1][pCurrentNode->x]->stepPoint.size() < oldStepNumber + 1)
			map[pCurrentNode->y - 1][pCurrentNode->x]->stepPoint.resize(oldStepNumber + 1);
	
		bool isVisited = 
			map[pCurrentNode->y - 1][pCurrentNode->x]->type == 0 ||
			(map[pCurrentNode->y - 1][pCurrentNode->x]->visited &&
			map[pCurrentNode->y - 1][pCurrentNode->x]->gameNumber == pCurrentNode->gameNumber) ||
			map[pCurrentNode->y - 1][pCurrentNode->x]->stepPoint.at(oldStepNumber);
		
		if (!isVisited) {
			pNextNode = map[pCurrentNode->y - 1][pCurrentNode->x];
			pCurrentNode->direction = 2;
		}
		
		return !isVisited;
	}
		
	bool CheckRightNode(Node*& pNextNode, Node* pCurrentNode, Node*** map, int oldGameNumber, int oldStepNumber) {
		if (pCurrentNode->x + 1 > pCurrentNode->columnCount - 1)
			return false;
			
		if (map[pCurrentNode->y][pCurrentNode->x + 1]->stepPoint.size() < oldStepNumber + 1)
			map[pCurrentNode->y][pCurrentNode->x + 1]->stepPoint.resize(oldStepNumber + 1);
		
		bool isVisited = 
			map[pCurrentNode->y][pCurrentNode->x + 1]->type == 0 ||
			(map[pCurrentNode->y][pCurrentNode->x + 1]->visited &&
			map[pCurrentNode->y][pCurrentNode->x + 1]->gameNumber == pCurrentNode->gameNumber) ||
			map[pCurrentNode->y][pCurrentNode->x + 1]->stepPoint.at(oldStepNumber);

		if (!isVisited) {
			pNextNode = map[pCurrentNode->y][pCurrentNode->x + 1];
			pCurrentNode->direction = 3;
		}
		
		return !isVisited;
	}
		
	bool CheckDownNode(Node*& pNextNode, Node* pCurrentNode, Node*** map, int oldGameNumber, int oldStepNumber) {
		if (pCurrentNode->y + 1 > pCurrentNode->rowCount - 1)
			return false;

		if (map[pCurrentNode->y + 1][pCurrentNode->x]->stepPoint.size() < oldStepNumber + 1)
			map[pCurrentNode->y + 1][pCurrentNode->x]->stepPoint.resize(oldStepNumber + 1);

		bool isVisited = 
			map[pCurrentNode->y + 1][pCurrentNode->x]->type == 0 ||
			(map[pCurrentNode->y + 1][pCurrentNode->x]->visited &&
			map[pCurrentNode->y + 1][pCurrentNode->x]->gameNumber == pCurrentNode->gameNumber) ||
			map[pCurrentNode->y + 1][pCurrentNode->x]->stepPoint.at(oldStepNumber);
		
		if (!isVisited) {
			pNextNode = map[pCurrentNode->y + 1][pCurrentNode->x];
			pCurrentNode->direction = 4;
		}
		
		return !isVisited;
	}
	
	GoBackNode(Node*& pNextNode, Node*& pCurrentNode, Node*** map, int gameNumber, int oldStepNumber) {
		pNextNode = map[pCurrentNode->pPreviousN->y][pCurrentNode->pPreviousN->x];
		std::cout << " geri ";
		
		if (pNextNode->direction == 1) {
			pCurrentNode->direction = 3;
			std::cout << "saga ";
		} else if (pNextNode->direction == 2) {
			pCurrentNode->direction = 4;
			std::cout << "asagiya ";
		} else if (pNextNode->direction == 3) {
			pCurrentNode->direction = 1;
			std::cout << "sola ";
		} else if (pNextNode->direction == 4) {
			pCurrentNode->direction = 2;
			std::cout << "yukariya ";
		}
		
		std::cout << pNextNode->x << "-" << pNextNode->y << std::endl;
		
		if (pNextNode != nullptr && pNextNode->id != -1) {
			if (pNextNode->stepPoint.size() < oldStepNumber + 1) {
				pNextNode->stepPoint.resize(oldStepNumber + 1);
			}
		
			pNextNode->stepPoint[oldStepNumber] = true;
			pNextNode->visited = true;
			pNextNode->gameNumber = gameNumber;
			pNextNode->pPreviousN = pCurrentNode->pPreviousN->pPreviousN;
			pCurrentNode->pNextN = pNextNode;
			
			vertexChainFiFo.push_back(new Vertex(pNextNode->pPreviousN));
		}
		
		pNextNode = NextNode(pNextNode, map, gameNumber, oldStepNumber);
	}
	
	Node* NextNode(Node* pCurrentNode, Node*** map, int gameNumber, int oldStepNumber) {
		if (health == 0)
			return pCurrentNode;
		
		health--;		
		length++;
			
		std::cout << length << ". adim (" << health << " can): ";
		std::cout << pCurrentNode->x << "-" << pCurrentNode->y;
			
		int oldGameNumber = 1;
		oldStepNumber = length - 2;
		Node* pNextNode = nullptr;
		
		do {
			oldStepNumber++;
			
			if (pCurrentNode->pPreviousN != nullptr && pCurrentNode->pPreviousN->stepPoint.size() < oldStepNumber)
				pCurrentNode->pPreviousN->stepPoint.resize(oldStepNumber);
				
			if (CheckLeftNode(pNextNode, pCurrentNode, map, oldGameNumber, oldStepNumber))
			{
				std::cout << " sola " << pNextNode->x << "-" << pNextNode->y << std::endl;
			} else if (CheckUpNode(pNextNode, pCurrentNode, map, oldGameNumber, oldStepNumber))
			{
				std::cout << " yukariya " << pNextNode->x << "-" << pNextNode->y << std::endl;
			} else if (CheckRightNode(pNextNode, pCurrentNode, map, oldGameNumber, oldStepNumber))
			{
				std::cout << " saga " << pNextNode->x << "-" << pNextNode->y << std::endl;
			} else if (CheckDownNode(pNextNode, pCurrentNode, map, oldGameNumber, oldStepNumber))
			{
				std::cout << " asagiya " << pNextNode->x << "-" << pNextNode->y << std::endl;
			} else if (
				pCurrentNode->pPreviousN != nullptr && 
				!pCurrentNode->pPreviousN->isFirstNode &&
				!pCurrentNode->pPreviousN->stepPoint.at(oldStepNumber - 2) &&
				oldGameNumber == pCurrentNode->gameNumber
				) {
				GoBackNode(pNextNode, pCurrentNode, map, gameNumber, oldStepNumber);
			}
			
			if (pNextNode != nullptr && pNextNode->id != -1) {
				if (pNextNode->stepPoint.size() < oldStepNumber + 1) {
					pNextNode->stepPoint.resize(oldStepNumber + 1);
				}
				
				pNextNode->stepPoint[oldStepNumber] = true;
				pNextNode->visited = true;
				pNextNode->gameNumber = gameNumber;
				pNextNode->pPreviousN = pCurrentNode;
				pCurrentNode->pNextN = pNextNode;
			}
			
			oldGameNumber++;
			
			if (oldGameNumber > gameNumber)
				oldGameNumber--;
		} while (pNextNode == nullptr || pNextNode->id == -1);
		
		return pNextNode;
	}
	
	void FindRoute(Node* pFirstNode, Node* pLastNode, Node*** matrix, int gameIndex) {
		std::cout << std::endl << gameIndex << ". rota:" << std::endl;
		id = gameIndex;
		pFirstNode->FirstNode(gameIndex);
		Node* pCurrentNode = pFirstNode;
		
		do {
			Node* pNextNode = NextNode(pCurrentNode, matrix, gameIndex, 1);
					
			if (pNextNode->type > 1 && pNextNode->id != pLastNode->id) {
				health += pNextNode->type;
				std::cout << 
					pNextNode->type << " can kazandi. Simdiki can: " <<
					health << 
				std::endl;
				pNextNode->type = 1;
			}
			
			pCurrentNode = pNextNode;
			vertexChainFiFo.push_back(new Vertex(pCurrentNode->pPreviousN));
		} while (health != 0 && pLastNode->id != pCurrentNode->id);
		
		vertexChainFiFo.push_back(new Vertex(pCurrentNode));
		
		if (pCurrentNode->id == pLastNode->id)
			std::cout << "Cikis " << length << " adimda, " << health << " can ile bulundu." << std::endl;
		else
			std::cout << "Cikis bulunamadi." << std::endl;
	}
};

#endif
