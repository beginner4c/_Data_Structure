import java.io.*;

class MazeTest
{
	public static void main(String[] args) 
	{
		int nRow = 0;
		int nCol = 0;
		BufferedReader in = null;

		Maze maze = null;
		try
		{
			in = new BufferedReader(new InputStreamReader(new FileInputStream("data.txt")));
			String temp = in.readLine();
			String []numbers = temp.split(" ");
			nRow = Integer.parseInt(numbers[0]);
			nCol = Integer.parseInt(numbers[1]);
			maze = new Maze(nRow,nCol);
			maze.loadMapFromFile(in);
			maze.printMap();
			in.close();
		}
		catch (IOException ex)
		{
		}
		Position start = new Position(0,0);
		Position destination = new Position(nRow-1,nCol-1);
		maze.findWay(start,destination);
	}
}

class Position {
	int x;
	int y;
	Position() {
		x = 0; y = 0;
	}
	Position(int a,int b) {
		x = a; y = b;
	}
	Position(Position pos) {
		x = pos.x;
		y = pos.y;
	}
	boolean equals(Position pos) {
		if (x == pos.x && y == pos.y) return true;
		return false;
	}
}

class PositionStack {
	private static int MAXSTACK = 1000;
	private int _top;
	private Position _s[];
	PositionStack() {
		_top = -1;
		_s = new Position[MAXSTACK];
	}
	void push(Position pos) {
		if (_top >= MAXSTACK-1) {
			System.out.println("stack overflow error");
			System.exit(-1);
		}
		_top++;
		_s[_top] = new Position(pos);
	}
	Position pop() {
		if (_top < 0) {
			System.out.println("stack empty error");
			System.exit(-1);
		}
		_top--;
		return _s[_top+1];
	}
	Position top() {
		if (_top < 0) {
			System.out.println("stack empty error");
			System.exit(-1);
		}
		return _s[_top];
	}
	void print() {
		if (_top < 0) {
			System.out.println("stack empty error");
			System.exit(-1);
		}
		System.out.println();
		System.out.println("=== Success !!! ===");
		for(int i = 0; i <= _top; i++) {
			System.out.println("(" + _s[i].x + "," + _s[i].y + ")");
		}
	}
	boolean isEmpty() {
		if (_top == -1) return true;
		else return false;
	}
}

class Maze {
	private int _room[][];
	private int _visitedRoom[][];
	private int _nRow;
	private int _nCol;
	private Position _offset[];
	Maze(int r,int c) {
		_nRow = r;
		_nCol = c;
		_room = new int[_nRow][_nCol];
		_visitedRoom = new int[_nRow][_nCol];
		_offset = new Position[4];
		for(int i = 0; i < 4; i++) {
			_offset[i] = new Position();
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
	void loadMapFromFile(BufferedReader in) {
		try
		{
			for(int i = 0; i < _nRow; i++) {
				String temp = in.readLine();
				String []numbers = temp.split(" ");
				for(int j = 0; j < _nCol; j++) {
					_room[i][j] = Integer.parseInt(numbers[j]);
				}
			}			
		}
		catch (IOException ex)
		{
		}
	}
	void printMap() {
		for(int i = 0; i < _nRow; i++) {
			for(int j = 0; j < _nCol; j++) {
				System.out.print(_room[i][j]);
			}
			System.out.println();
		}
	}
	void findWay(Position start,Position destination) {
		int dir;

		PositionStack stack = new PositionStack();

		_visitedRoom[start.x][start.y] = 1;
		stack.push(start);

		while(!stack.isEmpty()) {
			Position currentRoom = new Position(stack.top());

			if (currentRoom.equals(destination)) {
				System.out.println("found");
				stack.print();
				return;
			}
			for (dir = 0; dir < 4; dir++) {
				int nextX,nextY;
				nextX = currentRoom.x + _offset[dir].x;
				nextY = currentRoom.y + _offset[dir].y;
				if (nextX < 0 || nextX >= _nRow || nextY < 0 || nextY >= _nCol) continue;
				if (_room[nextX][nextY] == 1 || _visitedRoom[nextX][nextY] == 1) continue;
				_visitedRoom[nextX][nextY] = 1;
				currentRoom.x = nextX;
				currentRoom.y = nextY;
				stack.push(currentRoom);
				break;
			}
			if (dir >= 4) stack.pop(); 
		}
		System.out.println("can't find exit");
	}
}

/***** data.txt
5 5
0 1 1 1 1
0 0 0 0 1
1 0 1 1 1
1 0 0 1 0
1 1 0 0 0
*****/