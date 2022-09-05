#include <iostream>
#include <fstream>

#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_KEY_DOWN(cMain::OnKeyPress)
wxEND_EVENT_TABLE()

/// <summary>
/// Default constructor for cMain. Creates an empty map with walls around the edges.
/// </summary>
cMain::cMain() : wxFrame(nullptr, wxID_ANY, "CatAndMouse", wxPoint(300, 30), wxSize(1124, 1024))
{
	//Create the handler for  reading PNG bitmaps
	wxImage::AddHandler(new wxPNGHandler);

	//Declare the array for storing images and the grid sizer that represents it in the GUI	
	imgMap = new wxStaticBitmap * [mapWidth * mapHeight];
	wxGridSizer *imgGrid = new wxGridSizer(mapWidth, mapHeight, 0, 0);

	tileIds = new int[mapWidth * mapHeight];
	
	//Logic that fills the image grid with the appropriate tiles
	for (int x = 0; x < mapWidth; x++) 
	{
		for (int y = 0; y < mapHeight; y++)
		{
			//If the current tile is not an edge then add a floor tile, otherwise add a wall tile
			if (x != 0 && x != 15 && y != 0 && y != 15) 
			{
				imgMap[y * mapWidth + x] = new wxStaticBitmap(this, wxID_ANY, wxBitmap("Sprites/FloorTile-0001.png", wxBITMAP_TYPE_PNG));
				tileIds[y * mapWidth + x] = 0;
			}
			else 
			{
				imgMap[y * mapWidth + x] = new wxStaticBitmap(this, wxID_ANY, wxBitmap("Sprites/WallTile-0001.png", wxBITMAP_TYPE_PNG));
				tileIds[y * mapWidth + x] = 1;
			}
			imgGrid->Add(imgMap[y * mapWidth + x], wxSizerFlags().Expand());
		}
	}
	
	//Set the sizer for the GUI to the image grid and add it to the layout
	this->SetSizer(imgGrid);
	imgGrid->Layout();
}

/// <summary>
/// Constructor for cMain that loads a maze from a text file.
/// Tiles in the file are represented by space separated numbers that represent what tile should be placed at the current grid location.
/// </summary>
/// <param name="file"> The path to the maze file in the project directory</param>
cMain::cMain(std::string file) : wxFrame(nullptr, wxID_ANY, "CatAndMouse", wxPoint(300, 30), wxSize(1024, 1047))
{
	//Create the handler for  reading PNG bitmaps
	wxImage::AddHandler(new wxPNGHandler);

	//Declare the array for storing images and the grid sizer that represents it in the GUI
	imgMap = new wxStaticBitmap * [mapWidth * mapHeight];
	wxGridSizer *imgGrid = new wxGridSizer(mapWidth, mapHeight, 0, 0);

	tileIds = new int[mapWidth * mapHeight];

	//File reader reads in each tile number into block
	std::ifstream fileReader;
	fileReader.open(file);
	char *block;

	for (int y = 0; y < mapWidth; y++)
	{
		for (int x = 0; x < mapHeight; x++)
		{
			block = new char[2];
			fileReader.read(block, 2);

			//Switch on block 0 which should always be the id number of the  corresponding tile
			switch (block[0])
			{
			case '0':
				imgMap[y * mapWidth + x] = new wxStaticBitmap(this, wxID_ANY, wxBitmap("Sprites/FloorTile-0001.png", wxBITMAP_TYPE_PNG));
				tileIds[y * mapWidth + x] = 0;
				break;
			case '1':
				imgMap[y * mapWidth + x] = new wxStaticBitmap(this, wxID_ANY, wxBitmap("Sprites/WallTile-0001.png", wxBITMAP_TYPE_PNG));
				tileIds[y * mapWidth + x] = 1;
				break;
			case '2':
				imgMap[y * mapWidth + x] = new wxStaticBitmap(this, 2, wxBitmap("Sprites/Mouse-0001.png", wxBITMAP_TYPE_PNG));
				tileIds[y * mapWidth + x] = 2;
				mouse = new cMazeAI(2, 'E', x, y, 4);
				break;
			case '3':
				imgMap[y * mapWidth + x] = new wxStaticBitmap(this, 3, wxBitmap("Sprites/Cat-0001.png", wxBITMAP_TYPE_PNG));
				tileIds[y * mapWidth + x] = 3;
				cat = new cMazeAI(x, y);
				break;
			case '4':
				imgMap[y * mapWidth + x] = new wxStaticBitmap(this, 4, wxBitmap("Sprites/Cheese-0001.png", wxBITMAP_TYPE_PNG));
				tileIds[y * mapWidth + x] = 4;
				break;
			}
			
			//Delete the block object so that a new block can be read in
			delete[] block;

			imgGrid->Add(imgMap[y * mapWidth + x], wxSizerFlags().Expand());			
		}
	}

	//Set the sizer for the GUI to the image grid and add it to the layout
	this->SetSizer(imgGrid);
	imgGrid->Layout();

	//Close the file reader
	fileReader.close();
}

cMain::~cMain()
{
}

/// <summary>
/// gets the locations of all tiles visible to the ai
/// </summary>
/// <param name="direction">The direction the ai is facing</param>
/// <param name="startingTile">The tile the ai is currently located at</param>
/// <returns>int array with the locations of all tiles visible to the ai</returns>
int * cMain::GetVisible(char direction, int startingTile)
{
	static int visibleTiles[20];
	switch (direction) 
	{
	case 'N':
		visibleTiles[0] = startingTile - mapWidth;
		visibleTiles[1] = startingTile + 1;
		visibleTiles[2] = startingTile - 1;
		visibleTiles[3] = startingTile + mapWidth;		
		//gets all tiles directly in front of the ai until it sees a wall
		if (tileIds[visibleTiles[0]] != 1)
		{
			for (int i = 2; i < 16; i++)
			{
				visibleTiles[i + 2] = startingTile - (mapWidth * i);
				if (tileIds[visibleTiles[i + 2]] == 1)
				{
					break;
				}
			}
		}
		break;
	case 'E':
		visibleTiles[0] = startingTile + 1;
		visibleTiles[1] = startingTile + mapWidth;
		visibleTiles[2] = startingTile - mapWidth;
		visibleTiles[3] = startingTile - 1;

		//gets all tiles directly in front of the ai until it sees a wall
		if (tileIds[visibleTiles[0]] != 1)
		{
			for (int i = 2; i < 16; i++)
			{
				visibleTiles[i + 2] = startingTile + i;
				if (tileIds[visibleTiles[i + 2]] == 1)
				{
					break;
				}
			}
		}
		break;
	case 'S':
		visibleTiles[0] = startingTile + mapWidth;
		visibleTiles[1] = startingTile - 1;
		visibleTiles[2] = startingTile + 1;
		visibleTiles[3] = startingTile - mapWidth;

		//gets all tiles directly in front of the ai until it sees a wall
		if (tileIds[visibleTiles[0]] != 1)
		{
			for (int i = 2; i < 16; i++)
			{
				visibleTiles[i + 2] = startingTile + (mapWidth * i);
				if (tileIds[visibleTiles[i + 2]] == 1)
				{
					break;
				}
			}
		}
		break;
	case 'W':
		visibleTiles[0] = startingTile - 1;
		visibleTiles[1] = startingTile - mapWidth;
		visibleTiles[2] = startingTile + mapWidth;
		visibleTiles[3] = startingTile + 1;

		//gets all tiles directly in front of the ai until it sees a wall
		if (tileIds[visibleTiles[0]] != 1)
		{
			for (int i = 2; i < 16; i++)
			{
				visibleTiles[i + 2] = startingTile - i;
				if (tileIds[visibleTiles[i + 2]] == 1)
				{
					break;
				}
			}
		}
		break;
	}

	return visibleTiles;
}

/// <summary>
/// Swaps the bitmap images and ids of two tiles
/// </summary>
/// <param name="firstTile">The location of the first tile to be swapped</param>
/// <param name="secondTile">The location of the second tile to be swapped</param>
void cMain::SwapTiles(int firstTile, int secondTile) 
{
	wxBitmap imgTemp = imgMap[firstTile]->GetBitmap();
	int idTemp = tileIds[firstTile];

	imgMap[firstTile]->SetBitmap(imgMap[secondTile]->GetBitmap());	
	imgMap[secondTile]->SetBitmap(imgTemp);

	tileIds[firstTile] = tileIds[secondTile];
	tileIds[secondTile] = idTemp;
}


/// <summary>
/// Performs the next step for the entity by gathering and passing information
/// needed for the entity to move
/// </summary>
/// <param name="entity">The entity that is taking their turn</param>
/// <returns>True if the entity has not found its target. False otherwise</returns>
bool cMain::NextStep(cMazeAI * entity) 
{
	int startingTile = entity->yPos * mapWidth + entity->xPos, nextTile;
	int * visibleTiles = GetVisible(entity->GetFaceDirection(), startingTile);	
	int visibleTileIds[20];

	//get the ids of all visible tiles	
	//if the entity is next to their target then send the signal to end the simulation
	for (int i = 0; i < 20; i++) 
	{
		visibleTileIds[i] = tileIds[visibleTiles[i]];
		if ( i < 3 && visibleTileIds[i] == entity->interestId)
		{
			return false;
		}
		else if (i > 3 && visibleTileIds[i] == 1) 
		{
			break;
		}
	}

	//move the ai in the GUI based on where it chose to move to
	nextTile = visibleTiles[entity->RunRoutine(visibleTileIds)];
	SwapTiles(startingTile, nextTile);
	
	//update the visible tiles to check if the entity's target is next to it
	//if the entity is next to their target then send the signal to end the simulation
	visibleTiles = GetVisible(entity->GetFaceDirection(), (entity->yPos * mapWidth + entity->xPos, nextTile));
	for (int i = 0; i < 4; i++)
	{
		if (tileIds[visibleTiles[i]] == entity->interestId)
		{
			return false;
		}
	}

	return true;
}

/// <summary>
/// Function that automatically cycles between the turns
/// of the cat and mouse until one has found its target
/// </summary>
void cMain::AutoCycle() 
{	
	while (cycling)
	{
		Sleep(300);
		cycling = NextStep(cat);
		if (!cycling) 
		{
			break;
		}
		Sleep(300);
		cycling = NextStep(mouse);
	}
}

/// <summary>
/// Event called whenever a key is pressed to start autocycling the turns of the ai
/// </summary>
/// <param name="evt">event passed to the function</param>
void cMain::OnKeyPress(wxKeyEvent& evt) 
{
	if (!cycling) 
	{
		cycling = true;
		AutoCycle();		
	}

	evt.Skip();
}