#include <iostream>
#include <stdlib.h>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#define MAXSTACK (1000)

class Position {
public:
	int x;
	int y;
	Position() {
		x = 0; y = 0;
	}
	Position(int a,int b) {
		x = a; y = b;
	}
	Position(Position &pos) {
		x = pos.x;
		y = pos.y;
	}
	bool operator==(Position pos) {
		if (x == pos.x && y == pos.y) return true;
		return false;
	}
};


class PositionStack {
private:
	int _top;
	Position _s[MAXSTACK];
public:
	PositionStack() {
		_top = -1;
	}
	void push(Position pos) {
		if (_top >= MAXSTACK-1) {
			cerr << "stack overflow error\n";
			exit(-1);
		}
		_top++;
		_s[_top] = pos;
	}
	Position pop() {
		if (_top < 0) {
			cerr << "stack empty error\n";
			exit(-1);
		}
		_top--;
		return _s[_top+1];
	}
	Position top() {
		if (_top < 0) {
			cerr << "stack empty error\n";
			exit(-1);
		}
		return _s[_top];
	}
	void print() {
		if (_top < 0) {
			cerr << "stack empty error\n";
			exit(-1);
		}
		cout << "\n === Success !!! ===\n";
		for(int i = 0; i <= _top; i++) {
			cout << "(" << _s[i].x << "," << _s[i].y << ")\n";
		}
	}
	bool isEmpty() {
		if (_top == -1) return true;
		else return false;
	}
};

class Maze {
	int **_room;
	int **_visitedRoom;
	int _nRow;
	int _nCol;
	Position _offset[4];
public:
	~Maze() {
		for(int i = 0; i < _nRow; i++) {
			delete []_room[i];
		}
		delete []_room;
		for(i = 0; i < _nRow; i++) {
			delete []_visitedRoom[i];
		}
		delete []_visitedRoom;
	}
	Maze(int r,int c) {
		_nRow = r;
		_nCol = c;
		_room = new int*[_nRow];
		for(int i = 0; i < _nRow; i++) {
			_room[i] = new int[_nCol];
		}
		_visitedRoom = new int*[_nRow];
		for(i = 0; i < _nRow; i++) {
			_visitedRoom[i] = new int[_nCol];
			for(int j = 0; j < _nCol; j++) {
				_visitedRoom[i][j] = 0;
			}
		}
		_offset[0].x = -1;
		_offset[0].y = 0;
		_offset[1].x = 0;
		_offset[1].y = 1;
		_offset[2].x = 1;
		_offset[2].y = 0;
		_offset[3].x = 0;
		_offset[3].y = -1;
	}
	void loadMapFromFile(FILE *fp) {
		for(int i = 0; i < _nRow; i++) {
			for(int j = 0; j < _nCol; j++) {
				int temp;

				fscanf(fp,"%d",&temp);
				_room[i][j] = temp;
			}
		}
	}
	void printMap() {
		for(int i = 0; i < _nRow; i++) {
			for(int j = 0; j < _nCol; j++) {
				cout << _room[i][j];
			}
			cout << "\n";
		}
	}
	void findWay(Position start,Position destination) {
		int dir;

		PositionStack stack;

		_visitedRoom[start.x][start.y] = 1;
		stack.push(start);

		while(!stack.isEmpty()) {
			Position currentRoom = stack.top();

			if (currentRoom == destination) {
				cout << "found\n";
				stack.print();
				return;
			}
			for (dir = 0; dir < 4; dir++) {
				int nextX,nextY;
				nextX = currentRoom.x + _offset[dir].x;
				nextY = currentRoom.y + _offset[dir].y;
				if (nextX < 0 || nextX >= _nRow || nextY < 0 || nextY >= _nCol) continue;
				if (_room[nextX][nextY] || _visitedRoom[nextX][nextY]) continue;
				_visitedRoom[nextX][nextY] = 1;
				currentRoom.x = nextX;
				currentRoom.y = nextY;
				stack.push(currentRoom);
				break;
			}
			if (dir >= 4) stack.pop();
		}
		cout << "can't find exit\n";
	}
};

void main(int argc, char *argv[])
{
	int nRow,nCol;
	
	FILE *inFile=fopen("data.txt","r"); 
	if(inFile == NULL)//파일 체크
	{
		cerr << "파일 열기 실패!\n";
		exit(-1);
	}
	
	fscanf(inFile,"%d %d",&nRow,&nCol);

	Maze maze(nRow,nCol);
	
	maze.loadMapFromFile(inFile);
	maze.printMap();

	Position start(0,0);
	Position destination(nRow-1,nCol-1);
	maze.findWay(start,destination);

	fclose(inFile);
}

/***** data.txt
5 5
0 1 1 1 1
0 0 0 0 1
1 0 1 1 1
1 0 0 1 0
1 1 0 0 0
*****/