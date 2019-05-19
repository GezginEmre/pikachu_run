#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <queue>
#include <vector>

#include "vertex.h"
#include "node.h"

class Route {
	public:
		int id = -1;
		std::queue<Node*> nodeChainFiFo;
		int health = 10;
		int length = 0;
		
	bool CheckLeftNode(Node*& pNextNode, Node* pCurrentNode, Node*** map, int oldGameNumber, int oldStepNumber) {
		if (pCurrentNode->x - 1 < 0)
			return false;
		
//		bool isVisited = 
//			map[pCurrentNode->y][pCurrentNode->x - 1]->type == 0 ||
//			(map[pCurrentNode->y][pCurrentNode-> x - 1]->visited &&
//			map[pCurrentNode->y][pCurrentNode->x - 1]->gameNumber < oldGameNumber) ||
//			map[pCurrentNode->y][pCurrentNode->x - 1]->gameNumber != oldGameNumber;

		if (map[pCurrentNode->y][pCurrentNode->x - 1]->stepPoint.size() < oldStepNumber + 1)
			map[pCurrentNode->y][pCurrentNode->x - 1]->stepPoint.resize(oldStepNumber + 1);
		
//		bool isStepped = false;
//		
//		for (int stepIndex = oldStepNumber; stepIndex >= 0; stepIndex--)
//			if (map[pCurrentNode->y][pCurrentNode->x - 1]->stepPoint.at(stepIndex)) {
//				isStepped = true;
//				break;
//				
//			}
			
		bool isVisited = 
			map[pCurrentNode->y][pCurrentNode->x - 1]->type == 0 ||
			(map[pCurrentNode->y][pCurrentNode-> x - 1]->visited &&
			map[pCurrentNode->y][pCurrentNode->x - 1]->gameNumber == pCurrentNode->gameNumber) ||
//			isStepped;
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

//		bool isVisited = 
//			map[pCurrentNode->y - 1][pCurrentNode->x]->type == 0 ||
//			(map[pCurrentNode->y - 1][pCurrentNode->x]->visited &&
//			map[pCurrentNode->y - 1][pCurrentNode->x]->gameNumber < oldGameNumber) ||
//			map[pCurrentNode->y - 1][pCurrentNode->x]->gameNumber != oldGameNumber;
	
		if (map[pCurrentNode->y - 1][pCurrentNode->x]->stepPoint.size() < oldStepNumber + 1)
			map[pCurrentNode->y - 1][pCurrentNode->x]->stepPoint.resize(oldStepNumber + 1);
		
//		bool isStepped = false;
//		
//		for (int stepIndex = map[pCurrentNode->y - 1][pCurrentNode->x]->stepPoint.size() - 1; stepIndex == oldStepNumber; stepIndex--)
//			if (map[pCurrentNode->y - 1][pCurrentNode->x]->stepPoint.at(stepIndex)) {
//				isStepped = true;
//				break;
//				
//			}
	
		bool isVisited = 
			map[pCurrentNode->y - 1][pCurrentNode->x]->type == 0 ||
			(map[pCurrentNode->y - 1][pCurrentNode->x]->visited &&
			map[pCurrentNode->y - 1][pCurrentNode->x]->gameNumber == pCurrentNode->gameNumber) ||
//			isStepped;
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
		
//		bool isStepped = false;
//		
//		for (int stepIndex = oldStepNumber; stepIndex >= 0; stepIndex--)
//			if (map[pCurrentNode->y][pCurrentNode->x + 1]->stepPoint.at(stepIndex)) {
//				isStepped = true;
//				break;
//				
//			}
		
		bool isVisited = 
			map[pCurrentNode->y][pCurrentNode->x + 1]->type == 0 ||
			(map[pCurrentNode->y][pCurrentNode->x + 1]->visited &&
			map[pCurrentNode->y][pCurrentNode->x + 1]->gameNumber == pCurrentNode->gameNumber) ||
//			isStepped;
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
			
//		bool isVisited = 
//			map[pCurrentNode->y + 1][pCurrentNode->x]->type == 0 ||
//			(map[pCurrentNode->y + 1][pCurrentNode->x]->visited &&
//			map[pCurrentNode->y + 1][pCurrentNode->x]->gameNumber < oldGameNumber) ||
//			map[pCurrentNode->y + 1][pCurrentNode->x]->gameNumber != oldGameNumber;

		if (map[pCurrentNode->y + 1][pCurrentNode->x]->stepPoint.size() < oldStepNumber + 1)
			map[pCurrentNode->y + 1][pCurrentNode->x]->stepPoint.resize(oldStepNumber + 1);
		
//		bool isStepped = false;
//		
//		for (int stepIndex = oldStepNumber; stepIndex >= 0; stepIndex--)
//			if (map[pCurrentNode->y + 1][pCurrentNode->x]->stepPoint.at(stepIndex)) {
//				isStepped = true;
//				break;
//				
//			}

		bool isVisited = 
			map[pCurrentNode->y + 1][pCurrentNode->x]->type == 0 ||
			(map[pCurrentNode->y + 1][pCurrentNode->x]->visited &&
			map[pCurrentNode->y + 1][pCurrentNode->x]->gameNumber == pCurrentNode->gameNumber) ||
//			isStepped;
			map[pCurrentNode->y + 1][pCurrentNode->x]->stepPoint.at(oldStepNumber);
		
		if (!isVisited) {
			pNextNode = map[pCurrentNode->y + 1][pCurrentNode->x];
			pCurrentNode->direction = 4;
		}
		
		return !isVisited;
	}
	
	GoBackNode(Node*& pNextNode, Node* pCurrentNode, Node*** map, int gameNumber, int oldStepNumber) {
		pNextNode = map[pCurrentNode->pPreviousN->y][pCurrentNode->pPreviousN->x];
		std::cout << " geri ";
		
		if (pNextNode->direction == 1) {
			std::cout << "saga ";
		} else if (pNextNode->direction == 2) {
			std::cout << "asagiya ";
		} else if (pNextNode->direction == 3) {
			std::cout << "sola ";
		} else if (pNextNode->direction == 4) {
			std::cout << "yukariya ";
		}
		
		std::cout << pNextNode->x << "-" << pNextNode->y << std::endl;
		
		pNextNode = NextNode(pNextNode, map, gameNumber, oldStepNumber);
	}
	
	Node* NextNode(Node* pCurrentNode, Node*** map, int gameNumber, int oldStepNumber) {
		if (health == 0)
			return pCurrentNode;
		
		health--;		
		length++;
			
		std::cout << length << ". adim (" << health << " can): ";
		std::cout << pCurrentNode->x << "-" << pCurrentNode->y;
			
		Node* pNextNode = nullptr;
		int oldGameNumber = 1;
		oldStepNumber = length - 1;
		
		if (pCurrentNode->pPreviousN != nullptr && pCurrentNode->pPreviousN->stepPoint.size() < oldStepNumber)
			pCurrentNode->pPreviousN->stepPoint.resize(oldStepNumber);
		
		do {
			oldStepNumber++;
				
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
				!pCurrentNode->pPreviousN->stepPoint.at(oldStepNumber - 2) &&
				oldGameNumber == pCurrentNode->gameNumber
				) {
				GoBackNode(pNextNode, pCurrentNode, map, gameNumber, oldStepNumber);
			}
					
			oldGameNumber++;
				
//			if (oldStepNumber > length + 1)
//				oldStepNumber--;
			
			if (oldGameNumber > gameNumber)
				oldGameNumber--;
		} while (pNextNode == nullptr);
		
		pNextNode->visited = true;
		
		if (pNextNode->stepPoint.size() < oldStepNumber + 1)
			pNextNode->stepPoint.resize(oldStepNumber + 1);
		
		pNextNode->stepPoint[oldStepNumber] = true;
		pNextNode->gameNumber = gameNumber;
		pNextNode->pPreviousN = pCurrentNode;
		pCurrentNode->pNextN = pNextNode;
		
		nodeChainFiFo.push(pNextNode);
		
		return pNextNode;
	}
	
	void FindRoute(Node* pFirstNode, Node* pLastNode, Node*** matrix, int gameIndex) {
		std::cout << std::endl << gameIndex + 1 << ". oyun:" << std::endl;
		id = gameIndex;
		pFirstNode->FirstNode(gameIndex + 1);
		Node* pNextNode = pFirstNode;
		nodeChainFiFo.push(pNextNode);
		
		do {
			Node* pCurrentNode = NextNode(pNextNode, matrix, gameIndex + 1, 1);
					
			if (pCurrentNode->type > 1 && pCurrentNode->type != 4) {
				health += pCurrentNode->type;
				std::cout << 
					pCurrentNode->type << " can kazandi. Simdiki can: " <<
					health << 
				std::endl;
				pCurrentNode->type = 1;
			}
			
			pNextNode = pCurrentNode;
		} while (health != 0 && pLastNode->id != pNextNode->id);
		
		if (pNextNode->id == pLastNode->id)
			std::cout << "Cikis " << length << " adimda, " << health << " can ile bulundu." << std::endl;
		else
			std::cout << "Cikis bulunamadi." << std::endl;
	}
};

#endif
