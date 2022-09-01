#include <stdlib.h>

#include "cMazeAI.h"

/// <summary>
/// Constructor for cMazeAI that defines the x and y position of the AI
/// Defaults to a standard catAI
/// </summary>
/// <param name="x">the x position of the AI</param>
/// <param name="y">the y position of the AI</param>
cMazeAI::cMazeAI(int x, int y) 
{
	id = 3;
	faceDirection = 'N';
	interestId = 2;
	xPos = x;
	yPos = y;
	moveNum = rand() % 5 + 1; //set moveNum to a value between 1 and 5
}

/// <summary>
/// Constructor for cMazeAI that defines all variables except its initial moveNum
/// </summary>
/// <param name="thisId">The id of the AI</param>
/// <param name="direction">The direction the AI is facing</param>
/// <param name="x">the x position of the AI</param>
/// <param name="y">the y position of the AI</param>
/// <param name="interest">the target of the AI</param>
cMazeAI::cMazeAI(int thisId, char direction, int x, int y, int interest)
{
	id = thisId;
	faceDirection = direction;
	interestId = interest;
	xPos = x;
	yPos = y;
	moveNum = rand() % 5 + 1; //set moveNum to a value between 1 and 5
}

cMazeAI::~cMazeAI() 
{
}

/// <summary>
/// Getter for faceDirection
/// </summary>
/// <returns>The direction the AI is facing</returns>
char cMazeAI::GetFaceDirection() 
{
	return faceDirection;
}

/// <summary>
/// Change the x or y position of the AI based on its current direction
/// </summary>
void cMazeAI::MoveForward() 
{
	switch (faceDirection) 
	{
	case('N'):
		yPos--;
		break;
	case('E'):
		xPos++;
		break;
	case('S'):
		yPos++;
		break;
	case('W'):
		xPos--;
		break;
	}
}

/// <summary>
/// Change direction of the AI to one of the three other directions
/// </summary>
void cMazeAI::ChangeDirection() 
{
	int choice = rand() % 3;

	switch (faceDirection) 
	{
	case('N'):
		if (choice == 0) 
		{
			faceDirection = 'E';
		}
		else if (choice == 1) 
		{
			faceDirection = 'S';
		}
		else 
		{
			faceDirection = 'W';
		}
		break;
	case('E'):
		if (choice == 0)
		{
			faceDirection = 'S';
		}
		else if (choice == 1)
		{
			faceDirection = 'W';
		}
		else
		{
			faceDirection = 'N';
		}
		break;
	case('S'):
		if (choice == 0)
		{
			faceDirection = 'W';
		}
		else if (choice == 1)
		{
			faceDirection = 'N';
		}
		else
		{
			faceDirection = 'E';
		}
		break;
	case('W'):
		if (choice == 0)
		{
			faceDirection = 'N';
		}
		else if (choice == 1)
		{
			faceDirection = 'E';
		}
		else
		{
			faceDirection = 'S';
		}
		break;
	}
}

/// <summary>
/// standard routine for the AI which is run every cycle
/// </summary>
/// <param name="nextTile">The tile directly in front of the AI</param>
void cMazeAI::RunRoutine(int nextTile)
{
	if (nextTile = 1 && moveNum > 0)
	{
		MoveForward();
	}
	else
	{
		ChangeDirection();
	}
}