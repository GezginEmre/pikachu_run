#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <stack>

#include "vertex.h"
#include "node.h"
#include "route.h"

std::string fileName = "map.txt";
int firstNodeNumber = 3;
int lastNodeNumber = 4;
int gameCount = 10;

int** GetRawMap(std::string fileName, int& rowCount, int& columnCount) {
	std::ifstream file;
	file.open(fileName);
	
	if (file.fail()) {
		std::cout << "There is no file to read!";
	}
	
	std::string line;
	rowCount = 0;
	columnCount = 0;
	
	while (std::getline(file, line)) {
		rowCount++;
		std::stringstream sstream(line);
		std::string token;
		
		while (rowCount == 1 && std::getline(sstream, token, ',')) {
			columnCount++;
		}
	}
	
	file.clear();
	file.seekg(0, file.beg);
	int** rawMap = new int*[rowCount];
	int rowIndex = 0;
	
	while (std::getline(file, line)) {
		rawMap[rowIndex] = new int[columnCount];
		std::stringstream sstream(line);
		std::string token;
		int columnIndex = 0;

		while (std::getline(sstream, token, ',')) {
			rawMap[rowIndex][columnIndex] = std::atoi(token.c_str());
			columnIndex++;
		}
		
		rowIndex++;
	}
	
	file.close();
	
	return rawMap;
}

Node*** GetMatrix(int** rawMap, int rowCount, int columnCount) {
	Node*** nodes = new Node**[rowCount];
	
	for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
		nodes[rowIndex] = new Node*[columnCount];
		
		for (int columnIndex = 0; columnIndex < columnCount; columnIndex++) {
			nodes[rowIndex][columnIndex] = new Node(columnIndex, rowIndex, rowCount, columnCount, rawMap[rowIndex][columnIndex]);
		}
	}
	
	return nodes;
}

Node* GetFirst(Node*** matrix, int rowCount, int columnCount) {
	for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
		if (firstNodeNumber == matrix[rowIndex][0]->type)
			return matrix[rowIndex][0];
		
		if (firstNodeNumber == matrix[rowIndex][columnCount - 1]->type)
			return matrix[rowIndex][columnCount - 1];
	}
	
	for (int columnIndex = 0; columnIndex < columnCount; columnIndex++) {
		if (firstNodeNumber == matrix[0][columnIndex]->type)
			return matrix[0][columnIndex];
			
		if (firstNodeNumber == matrix[rowCount - 1][columnIndex]->type)
			return matrix[rowCount - 1][columnIndex];
	}
	
	return new Node();
}

Node* GetLast(Node*** matrix, int rowCount, int columnCount) {
	for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
		if (lastNodeNumber == matrix[rowIndex][0]->type)
			return matrix[rowIndex][0];
		
		if (lastNodeNumber == matrix[rowIndex][columnCount - 1]->type)
			return matrix[rowIndex][columnCount - 1];
	}
	
	for (int columnIndex = 0; columnIndex < columnCount; columnIndex++) {
		if (lastNodeNumber == matrix[0][columnIndex]->type)
			return matrix[0][columnIndex];
			
		if (lastNodeNumber == matrix[rowCount - 1][columnIndex]->type)
			return matrix[rowCount - 1][columnIndex];
	}
	
	return new Node();
}

int main(int argc, char** argv) {
	int rowCount;
	int columnCount;
	int** rawMap = GetRawMap(fileName, rowCount, columnCount);
	
	if (!rawMap || rowCount < 1 || columnCount < 1) {
		std::cout << "There is no suitable map!";
		return 0;
	}
	
	Node*** matrix = GetMatrix(rawMap, rowCount, columnCount);	
	Node* first = GetFirst(matrix, rowCount, columnCount);
	
	if (first->type == -1) {
		std::cout << "There is no entry point on matris!";
		return 0;
	}
	
	Node* last = GetLast(matrix, rowCount, columnCount);
	
	if (last->type == -1) {
		std::cout << "There is no exit point on matris!";
		return 0;
	}
	
	Route* routes = new Route[gameCount];
	Route* bestRoute;
	
	Node** map = new Node*[rowCount];
		
	for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
		map[rowIndex] = new Node[columnCount];
		
		for (int columnIndex = 0; columnIndex < columnCount; columnIndex++) {
			map[rowIndex][columnIndex].GetMapType(matrix[rowIndex][columnIndex]);
		}
	}
	
	for (int gameIndex = 0; gameIndex < gameCount; gameIndex++) {
		
		routes[gameIndex].FindRoute(first, last, matrix, gameIndex);
		
		if (bestRoute == nullptr || routes[gameIndex].length < bestRoute->length)
			bestRoute = &routes[gameIndex];
			
		if (gameIndex < gameCount)
			for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {			
				for (int columnIndex = 0; columnIndex < columnCount; columnIndex++) {
					matrix[rowIndex][columnIndex]->GetMapType(&map[rowIndex][columnIndex]);
				}
			}
	}
	
	std::cout << std::endl << "En iyi rota: " << bestRoute->length << " adim." << std::endl;
	
	do {
		Node* pCurrent = bestRoute->nodeChainFiFo.front();
		std::cout << pCurrent->x << "-" << pCurrent->y;
		
		if (pCurrent->direction == 1)
			std::cout << " sola ";
		if (pCurrent->direction == 2)
			std::cout << " yukariya ";
		if (pCurrent->direction == 3)
			std::cout << " saga ";
		if (pCurrent->direction == 4)
			std::cout << " asagiya ";
		
		std::cout << pCurrent->pNextN->x << "-" << pCurrent->pNextN->y << std::endl;
		
		bestRoute->nodeChainFiFo.pop();
	} while (bestRoute->nodeChainFiFo.size() > 1);
	
	return 0;
}
