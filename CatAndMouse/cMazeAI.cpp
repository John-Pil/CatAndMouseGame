#include <stdlib.h>
#include <ctime>

#include "cMazeAI.h"

/// <summary>
/// Constructor for cMazeAI that defines the x and y position of the ai
/// Defaults to a standard catAI
/// </summary>
/// <param name="x">the x position of the ai</param>
/// <param name="y">the y position of the ai</param>
cMazeAI::cMazeAI(int x, int y) 
{
	id = 3;
	faceDirection = 'N';
	interestId = 2;
	xPos = x;
	yPos = y;

	srand((unsigned)time(NULL));
	moveNum = rand() % 3 + 3; //set moveNum to a value between 3 and 6
}

/// <summary>
/// Constructor for cMazeAI that defines all variables except its initial moveNum
/// </summary>
/// <param name="thisId">The id of the ai</param>
/// <param name="direction">The direction the ai is facing</param>
/// <param name="x">the x position of the ai</param>
/// <param name="y">the y position of the ai</param>
/// <param name="interest">the target of the ai</param>
cMazeAI::cMazeAI(int thisId, char direction, int x, int y, int interest)
{	
	id = thisId;
	faceDirection = direction;
	interestId = interest;
	xPos = x;
	yPos = y;

	srand((unsigned)time(NULL));
	moveNum = rand() % 3 + 3; //set moveNum to a value between 3 and 6
}

cMazeAI::~cMazeAI() 
{
}

/// <summary>
/// Getter for faceDirection
/// </summary>
/// <returns>The direction the ai is facing</returns>
char cMazeAI::GetFaceDirection() 
{
	return faceDirection;
}

/// <summary>
/// Getter for xPos
/// </summary>
/// <returns>The x position of the ai</returns>
int cMazeAI::GetXPos() 
{
	return xPos;
}

/// <summary>
/// Getter for yPos
/// </summary>
/// <returns>The y position of the ai</returns>
int cMazeAI::GetYPos()
{
	return yPos;
}

/// <summary>
/// Change the x or y position of the ai based on its current direction
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
/// Change direction of the ai. The ai will make a choice to go left or right.
/// If the choice of the ai is blocked off then it will go the other direction.
/// If both the left and right are blocked it will go back the way it came.
/// </summary>
int cMazeAI::ChangeDirection(int rightTileId, int leftTileId)
{
	//if the left and right are blocked off then reverse direction
	if (rightTileId == 1 && leftTileId == 1)
	{
		switch (faceDirection) 
		{
		case('N'):
			faceDirection = 'S';
			break;
		case('E'):
			faceDirection = 'W';
			break;
		case('S'):
			faceDirection = 'N';
			break;
		case('W'):
			faceDirection = 'E';
			break;
		}
		return 3;
	}

	//1 = right, 2 = left
	int choice = (rand() % 2) + 1;

	//attempt to turn in the direction of the ai's choice based on where its facing
	//if the choice of the ai is blocked then go the other direction
	switch (faceDirection) 
	{
	case('N'):
		if (choice == 1) 
		{
			if (rightTileId == 0)
			{
				faceDirection = 'E';
				return 1;
			}
			else
			{
				faceDirection = 'W';
				return 2;
			}
		}
		else 
		{
			if (leftTileId == 0)
			{
				faceDirection = 'W';
				return 2;
			}
			else
			{
				faceDirection = 'E';
				return 1;
			}
		}
	case('E'):
		if (choice == 1)
		{
			if (rightTileId == 0)
			{
				faceDirection = 'S';
				return 1;
			}
			else
			{
				faceDirection = 'N';
				return 2;
			}
		}
		else
		{
			if (leftTileId == 0)
			{
				faceDirection = 'N';
				return 2;
			}
			else
			{
				faceDirection = 'S';
				return 1;
			}
		}
	case('S'):
		if (choice == 1)
		{
			if (rightTileId == 0)
			{
				faceDirection = 'W';
				return 1;
			}
			else
			{
				faceDirection = 'E';
				return 2;
			}
		}
		else
		{
			if (leftTileId == 0)
			{
				faceDirection = 'E';
				return 2;
			}
			else
			{
				faceDirection = 'W';
				return 1;
			}
		}
	case('W'):
		if (choice == 1)
		{
			if (rightTileId == 0)
			{
				faceDirection = 'N';
				return 1;
			}
			else
			{
				faceDirection = 'S';
				return 2;
			}
		}
		else
		{
			if (leftTileId == 0)
			{
				faceDirection = 'S';
				return 2;
			}
			else
			{
				faceDirection = 'N';
				return 1;
			}
		}
	}
}

/// <summary>
/// Standard routine for the ai which is run every cycle
/// </summary>
/// <param name="visibleTileIds">The ids of all tiles visible to the ai</param>
/// /// <returns>The tile in visibleTileIds that the ai chose to move to</returns>
int cMazeAI::RunRoutine(int * visibleTileIds)
{	

	//if the tile in front of the ai is not a floor tile then change direction
	if (visibleTileIds[0] != 0)
	{
		int tile = ChangeDirection(visibleTileIds[1], visibleTileIds[2]);
		MoveForward();
		moveNum = rand() % 3 + 1; //reset moveNum to a value between 1 and 5
		return tile;		
	}
	else
	{
		//check to see if the ai sees its target
		//if it does move towards it and set its moveNum to the number of spaces
		//ahead its target is. This should work so that if the ai sees its target
		//it will only lose it under the condition the ai can turn left or right
		//or if the target turns before the this ai's next move.
		for (int i = 1; i < 16; i++)
		{
			if (visibleTileIds[i + 3] == 1)
			{
				break;
			}
			else if (visibleTileIds[i + 3] == interestId) 
			{
				MoveForward();
				moveNum = i;
				return 0;
			}
		}

		//if the ai wants to move forward or doesn't but cant turn left or right
		//then continue moving forward. otherwise change direction
		if (moveNum > 0 || (visibleTileIds[1] == 1 && visibleTileIds[2] == 1))
		{
			MoveForward();
			moveNum--;
			return 0;
		}
		else
		{
			int tile = ChangeDirection(visibleTileIds[1], visibleTileIds[2]);
			MoveForward();
			moveNum = rand() % 3 + 1; //reset moveNum to a value between 1 and 5
			return tile;
		}
	}
}