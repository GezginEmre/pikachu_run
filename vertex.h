#ifndef VERTEX_H
#define VERTEX_H

class Vertex {
	public:
		int id = -1;
		int x = -1;
		int y = -1;
		int rowCount = -1;
		int columnCount = -1;
		int type = -1;
		int direction = 0;
		
		Vertex() {
		}
		
		Vertex(int id, int x, int y, int rowCount, int columnCount, int type) :
			id(id),
			x(x), y(y),
			rowCount(rowCount), columnCount(columnCount), 
			type(type) {
			}
			
		Vertex(Vertex* vertex) {
			id = vertex->id;
			x = vertex->x;
			y = vertex->y;
			direction = vertex->direction;
		}
};

#endif
