#pragma once
class cMazeAI
{
public:	
	//constructors and deconstructor
	cMazeAI(int x, int y);
	cMazeAI(int thisId, char direction, int x, int y, int interest = 4);
	~cMazeAI();

	//public class functions
	void RunRoutine(int nextTile);
	char GetFaceDirection();

	//public variables
	int  id, interestId; //tile ID of the AI and its target
	int xPos, yPos; //location of the AI on the maze grid	

private:
	//private class functions
	void MoveForward();
	void ChangeDirection();

	//private variables
	int moveNum = 0; //the number of moves the AI will take before swapping direction
	char faceDirection; //direction the AI is facing
};

