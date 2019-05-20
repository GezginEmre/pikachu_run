#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>

#include "vertex.h"
#include "node.h"
#include "route.h"

std::string fileName = "map.txt";
int firstNodeNumber = 3;
int lastNodeNumber = 4;
int gameIndex = 0;

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
	
	Node** map = new Node*[rowCount];
		
	for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {
		map[rowIndex] = new Node[columnCount];
		
		for (int columnIndex = 0; columnIndex < columnCount; columnIndex++) {
			map[rowIndex][columnIndex].GetMapType(matrix[rowIndex][columnIndex]);
		}
	}
	
	int routeCount = 0;
	
	Route firstRoute(++routeCount);
	firstRoute.FindRoute(first, last, matrix, ++gameIndex);
	Route bestRoute(-1);
	bestRoute = firstRoute;
	
	bool isRepeated;
	
	do {		
		for (int rowIndex = 0; rowIndex < rowCount; rowIndex++) {			
			for (int columnIndex = 0; columnIndex < columnCount; columnIndex++) {
				matrix[rowIndex][columnIndex]->GetMapType(&map[rowIndex][columnIndex]);
			}
		}
			
		Route route(++routeCount);
		route.FindRoute(first, last, matrix, ++gameIndex);
		
		if (firstRoute.vertexChainFiFo.size() == route.vertexChainFiFo.size())
			for (int stepIndex = 0; stepIndex < firstRoute.vertexChainFiFo.size(); stepIndex++) {
				if (firstRoute.vertexChainFiFo.at(stepIndex)->id == route.vertexChainFiFo.at(stepIndex)->id) {
					isRepeated = true;
				} else {
					isRepeated = false;
					break;
				}
			}
		
		if (route.health > 0 && route.length < bestRoute.length || 
			(route.health > bestRoute.health && route.length == bestRoute.length)) 
		{
			bestRoute = route;
		}
	} while (!isRepeated);
	
	std::cout << std::endl << routeCount << " adet rota denendi." << std::endl;
	std::cout << "En iyi rota " << bestRoute.length << " adim ile " << bestRoute.id << ". rota oldu:" << std::endl;
	
	for (int stepIndex = 0; stepIndex < bestRoute.vertexChainFiFo.size() - 1; stepIndex++) {
		Vertex* pCurrent = bestRoute.vertexChainFiFo.at(stepIndex);
		Vertex* pNext = bestRoute.vertexChainFiFo.at(stepIndex + 1);
		std::cout << pCurrent->x << "-" << pCurrent->y;
		
		if (pCurrent->direction == 1)
			std::cout << " sola ";
		if (pCurrent->direction == 2)
			std::cout << " yukariya ";
		if (pCurrent->direction == 3)
			std::cout << " saga ";
		if (pCurrent->direction == 4)
			std::cout << " asagiya ";
		
		std::cout << pNext->x << "-" << pNext->y << std::endl;
	}
	
	return 0;
}
