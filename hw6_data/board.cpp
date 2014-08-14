#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <list>

#include "board.h"
using namespace std;
// ==================================================================
// ==================================================================
// Implementation of the Position class


// allows a position to be output to a stream
std::ostream& operator<<(std::ostream &ostr, const Position &p) {
  ostr << '(' << p.row << "," << p.col << ')';
  return ostr;
}


// equality and inequality comparision of positions
bool operator==(const Position &a, const Position &b) {
  return (a.row == b.row && a.col == b.col);
}
bool operator!=(const Position &a, const Position &b) {
  return !(a==b);
}


// ==================================================================
// ==================================================================
// Implementation of the Board class


// ===================
// CONSTRUCTOR
// ===================

Board::Board(int r, int c) { 
  // initialize the dimensions
  rows = r; 
  cols = c; 

  // allocate space for the contents of each grid cell
  board = std::vector<std::vector<char> >(rows,std::vector<char>(cols,' '));

  // allocate space for booleans indicating the presense of each wall
  // by default, these are false == no wall
  // (note that there must be an extra column of vertical walls
  //  and an extra row of horizontal walls)
  vertical_walls = std::vector<std::vector<bool> >(rows,std::vector<bool>(cols+1,false));
  horizontal_walls = std::vector<std::vector<bool> >(rows+1,std::vector<bool>(cols,false));

  // initialize the outermost edges of the grid to have walls
  for (int i = 0; i < rows; i++) {
    vertical_walls[i][0] = vertical_walls[i][cols] = true;
  }
  for (int i = 0; i < cols; i++) {
    horizontal_walls[0][i] = horizontal_walls[rows][i] = true;
  }
}


// ===================
// ACCESSORS related to board geometry
// ===================

// Query the existance of a horizontal wall
bool Board::getHorizontalWall(double r, int c) const {
  // verify that the requested wall is valid
  // the row coordinate must be a half unit
  assert (fabs((r - floor(r))-0.5) < 0.005);
  assert (r >= 0.4 && r <= rows+0.6);
  assert (c >= 1 && c <= cols);
  // subtract one and round down because the corner is (0,0) not (1,1)
  return horizontal_walls[floor(r)][c-1];
}

// Query the existance of a vertical wall
bool Board::getVerticalWall(int r, double c) const {
  // verify that the requested wall is valid
  // the column coordinate must be a half unit
  assert (fabs((c - floor(c))-0.5) < 0.005);
  assert (r >= 1 && r <= rows);
  assert (c >= 0.4 && c <= cols+0.6);
  // subtract one and round down because the corner is (0,0) not (1,1)
  return vertical_walls[r-1][floor(c)];
}


// ===================
// MODIFIERS related to board geometry
// ===================

// Add an interior horizontal wall
void Board::addHorizontalWall(double r, int c) {
  // verify that the requested wall is valid
  // the row coordinate must be a half unit
  assert (fabs((r - floor(r))-0.5) < 0.005);
  assert (r >= 0 && r <= rows);
  assert (c >= 1 && c <= cols);
  // verify that the wall does not already exist
  assert (horizontal_walls[floor(r)][c-1] == false);
  // subtract one and round down because the corner is (0,0) not (1,1)
  horizontal_walls[floor(r)][c-1] = true;
}

// Add an interior vertical wall
void Board::addVerticalWall(int r, double c) {
  // verify that the requested wall is valid
  // the column coordinate must be a half unit
  assert (fabs((c - floor(c))-0.5) < 0.005);
  assert (r >= 1 && r <= rows);
  assert (c >= 0 && c <= cols);
  // verify that the wall does not already exist
  assert (vertical_walls[r-1][floor(c)] == false);
  // subtract one and round down because the corner is (0,0) not (1,1)
  vertical_walls[r-1][floor(c)] = true;
}


// ===================
// PRIVATE HELPER FUNCTIONS related to board geometry
// ===================

char Board::getspot(const Position &p) const {
  // verify that the requested coordinate is valid
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);
  // subtract one from each coordinate because the corner is (0,0) not (1,1)
  return board[p.row-1][p.col-1];
}


void Board::setspot(const Position &p, char a) {
  // verify that the requested coordinate is valid
  assert (p.row >= 1 && p.row <=  rows);
  assert (p.col >= 1 && p.col <= cols);
  // subtract one from each coordinate because the corner is (0,0) not (1,1)
  board[p.row-1][p.col-1] = a;
}

char Board::isGoal(const Position &p) const {
  // verify that the requested coordinate is valid
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);
  // loop over the goals, see if any match this spot
  for (unsigned int i = 0; i < goals.size(); i++) {
    if (p == goals[i].pos) { return goals[i].which; }
  }
  // else return space indicating that no goal is at this location
  return ' ';
}


// ===================
// MODIFIERS related to robots
// ===================

// for initial placement of a new robot
void Board::placeRobot(const Position &p, char a) {

  // check that input data is reasonable
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);
  assert (getspot(p) == ' ');
  
  // robots must be represented by a capital letter
  assert (isalpha(a) && isupper(a));

  // make sure we don't already have a robot with the same name
  for (unsigned int i = 0; i < robots.size(); i++) {
    assert (robots[i].which != a);
  }

  // add the robot and its position to the vector of robots
  robots.push_back(Robot(p,a));

  // mark the robot on the board
  setspot(p,a);
}


bool Board::moveRobot(int i, const std::string &direction) {
	char identity = getRobot(i);
	Position pos = getRobotPosition(i);
	if (direction == "up"){
		while (!getHorizontalWall(pos.row - .5, pos.col) && board[pos.row-2][pos.col-1] == ' '){
			pos.row--;
		}
	}

	if (direction == "down"){
		while (!getHorizontalWall(pos.row + .5, pos.col) && board[pos.row][pos.col-1] == ' '){
			pos.row++;
		}
	}

	if (direction == "left"){
		while (!getVerticalWall(pos.row, pos.col - .5) && board[pos.row-1][pos.col-2] == ' '){
			pos.col--;
		}
	}

	if (direction == "right"){
		while (!getVerticalWall(pos.row, pos.col + .5) && board[pos.row-1][pos.col] == ' '){
			pos.col++;
		}
	}
	//place the robot

	//return true if spot has changed, or return false if not
	if (pos != getRobotPosition(i)){
		setspot(getRobotPosition(i), ' ');
		robots[i].pos.col = pos.col;
		robots[i].pos.row = pos.row;
		setspot(pos, identity);
		return true;
	}
	else return false;
}


// ===================
// MODIFIER related to the puzzle goal
// ===================

void Board::addGoal(const std::string &gr, const Position &p) {

  // check that input data is reasonable
  assert (p.row >= 1 && p.row <= rows);
  assert (p.col >= 1 && p.col <= cols);

  char goal_robot;
  if (gr == "any") {
    goal_robot = '?';
  } else {
    assert (gr.size() == 1);
    goal_robot = gr[0];
    assert (isalpha(goal_robot) && isupper(goal_robot));
  }

  // verify that a robot of this name exists for this puzzle
  if (goal_robot != '?') {
    int robot_exists = false;
    for (unsigned int i = 0; i < robots.size(); i++) {
      if (getRobot(i) == goal_robot) 
        robot_exists = true;
    }
    assert (robot_exists);
  }
  
  // make sure we don't already have a robot at that location
  assert (isGoal(p) == ' ');

  // add this goal label and position to the vector of goals
  goals.push_back(Goal(p,goal_robot));
}


// ==================================================================
// PRINT THE BOARD
// ==================================================================

void Board::print() {

  // print the column headings
  std::cout << " ";
  for (int j = 1; j <= cols; j++) {
    std::cout << std::setw(5) << j;
  }
  std::cout << "\n";
  
  // for each row
  for (int i = 0; i <= rows; i++) {

    // don't print row 0 (it doesnt exist, the first real row is row 1)
    if (i > 0) {
      
      // Note that each grid rows is printed as 3 rows of text, plus
      // the separator.  The first and third rows are blank except for
      // vertical walls.  The middle row has the row heading, the
      // robot positions, and the goals.  Robots are always uppercase,
      // goals are always lowercase (or '?' for any).
      std::string first = "  ";
      std::string middle;
      for (int j = 0; j <= cols; j++) {

        if (j > 0) { 
          // determine if a robot is current located in this cell
          // and/or if this is the goal
          Position p(i,j);
          char c = getspot(p);
          char g = isGoal(p);
          if (g != '?') g = tolower(g);
          first += "    ";
          middle += " "; 
          middle += c; 
          middle += g; 
          middle += " ";
        }

        // the vertical walls
        if (getVerticalWall(i,j+0.5)) {
          first += "|";
          middle += "|";
        } else {
          first += " ";
          middle += " ";
        }
      }

      // output the three rows
      std::cout << first << std::endl;
      std::cout << std::setw(2) << i << middle << std::endl;
      std::cout << first << std::endl;
    }

    // print the horizontal walls between rows
    std::cout << "  +";
    for (double j = 1; j <= cols; j++) {
      (getHorizontalWall(i+0.5,j)) ? std::cout << "----" : std::cout << "    ";
      std::cout << "+";
    }
    std::cout << "\n";
  }
}

// ==================================================================
// ==================================================================

bool Board::canMove(int i, string &direction){
	Position pos = getRobotPosition(i);
	if (direction == "up"){
		if (!getHorizontalWall(pos.row - .5, pos.col) && board[pos.row-2][pos.col-1] == ' ') return true;
	}

	if (direction == "down"){
		if (!getHorizontalWall(pos.row + .5, pos.col) && board[pos.row][pos.col-1] == ' ') return true;
	}

	if (direction == "left"){
		if (!getVerticalWall(pos.row, pos.col - .5) && board[pos.row-1][pos.col-2] == ' ') return true;
	}

	if (direction == "right"){
		if (!getVerticalWall(pos.row, pos.col + .5) && board[pos.row-1][pos.col] == ' ') return true;
	}
	return false;

}

bool Board::makeMove(Vertex * move){
	list<Vertex *> moves;
	
	while (move->path != NULL) {
		moves.push_front(move);
		move = move->path;
	}
	moves.push_front(move);
	list<Vertex *>::iterator itr;
	for (itr = moves.begin(); itr != moves.end(); itr++){
		moveRobot((*itr)->robot, (*itr)->direction);
	}

	for (int i = 0; i < robots.size(); i++){
		for (int k = 0; k < numGoals(); k++){
			if (robots[i].pos == getGoalPosition(0)) return true;

		}
	}

	return false;
	
}

void Board::reset(vector<Position> &pos){
	for (int i = 0; i < robots.size(); i++){
		setspot(getRobotPosition(i), ' ');
		robots[i].pos.col = pos[i].col;
		robots[i].pos.row = pos[i].row;
		setspot(pos[i], getRobot(i));
	}
}

vector<Vertex*> Board::getMoves(){
	
	vector<Vertex *> moves;
	for (int i = 0; i < robots.size(); i++){
		Vertex *move = new Vertex(i, "up");
		if (canMove(i, move->direction)) moves.push_back(move);
		Vertex *move2 = new Vertex(i, "down");
		if (canMove(i, move2->direction)) moves.push_back(move2);
		Vertex *move3 = new Vertex(i, "left");
		if (canMove(i, move3->direction)) moves.push_back(move3);
		Vertex *move4 = new Vertex(i, "right");
		if (canMove(i, move4->direction)) moves.push_back(move4);
	}
	return moves;

}