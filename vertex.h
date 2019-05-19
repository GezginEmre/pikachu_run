#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
	public:
		int x = -1;
		int y = -1;
		int rowCount = -1;
		int columnCount = -1;
		int type = -1;
		
		Vertex() {
		}
		
		Vertex(int x, int y, int rowCount, int columnCount, int type) :
			x(x), y(y),
			rowCount(rowCount), columnCount(columnCount), 
			type(type) {
			}
};

#endif
