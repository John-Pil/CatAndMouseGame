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

	for (int x = 0; x < mapWidth; x++)
	{
		for (int y = 0; y < mapHeight; y++)
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
				mouse = new cMazeAI(2, 'N', x, y, 4);
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
/// gets the id of the tile directly in front of an ai
/// </summary>
/// <param name="direction">The direction the ai that requested the next tile Id is facing</param>
/// <returns>Tile id of the tile directly in front of the requesting ai</returns>
int cMain::GetNextTileOffset(char direction)
{
	switch (direction) 
	{
	case 'N':
		return -mapWidth;		
	case 'E':
		return 1;		
	case 'S':
		return mapWidth;		
	case 'W':
		return -1;		
	}
}

/// <summary>
/// Swaps the bitmap images and ids of two tiles
/// </summary>
/// <param name="firstTile">The location of the first tile to be swapped in imgMap</param>
/// <param name="secondTile">The location of the second tile to be swapped in imgMap</param>
void cMain::SwapTiles(int firstTile, int secondTile) 
{
	wxBitmap imgTemp = imgMap[firstTile]->GetBitmap();
	int idTemp = tileIds[firstTile];

	imgMap[firstTile]->SetBitmap(imgMap[secondTile]->GetBitmap());	
	imgMap[secondTile]->SetBitmap(imgTemp);

	tileIds[firstTile] = tileIds[secondTile];
	tileIds[secondTile] = idTemp;
}

bool cMain::NextStep(cMazeAI * entity) 
{
	int startingTile, nextTile;
	startingTile = entity->yPos * mapWidth + entity->xPos;
	nextTile = startingTile + GetNextTileOffset(entity->GetFaceDirection());

	//if the entity rotated update the next tile and try moving again
	while(!entity->RunRoutine(tileIds[nextTile])) 
	{
		nextTile = startingTile + GetNextTileOffset(entity->GetFaceDirection());

		//if the entity rotated and is now facing their target then send the signal to end the simulation
		if (tileIds[nextTile] == entity->interestId)
		{
			return false;
		}
	}

	SwapTiles(startingTile, nextTile);

	//if the entity is next to their target then send the signal to end the simulation
	if (tileIds[nextTile] == entity->interestId)
	{
		return false;
	}
	return true;
}

void cMain::AutoCycle() 
{
	bool continuing = true;
	while (continuing) 
	{
		Sleep(300);
		continuing = NextStep(cat);
		if (!continuing) 
		{
			break;
		}
		continuing = NextStep(mouse);
	}
}

void cMain::OnKeyPress(wxKeyEvent& evt) 
{
	if (!cycling) 
	{
		AutoCycle();
		cycling = true;
	}	
}