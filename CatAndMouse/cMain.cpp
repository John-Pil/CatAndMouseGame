#include <iostream>
#include <fstream>

#include "cMain.h"

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
	
	//Logic that fills the image grid with the appropriate tiles
	for (int x = 0; x < mapWidth; x++) 
	{
		for (int y = 0; y < mapHeight; y++)
		{
			//If the current tile is not an edge then add a floor tile, otherwise add a wall tile
			if (x != 0 && x != 15 && y != 0 && y != 15) 
			{
				imgMap[y * mapWidth + x] = new wxStaticBitmap(this, 0, wxBitmap("Sprites/FloorTile-0001.png", wxBITMAP_TYPE_PNG));
			}
			else 
			{
				imgMap[y * mapWidth + x] = new wxStaticBitmap(this, 1, wxBitmap("Sprites/WallTile-0001.png", wxBITMAP_TYPE_PNG));
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
				imgMap[y * mapWidth + x] = new wxStaticBitmap(this, 0, wxBitmap("Sprites/FloorTile-0001.png", wxBITMAP_TYPE_PNG));
				break;
			case '1':
				imgMap[y * mapWidth + x] = new wxStaticBitmap(this, 1, wxBitmap("Sprites/WallTile-0001.png", wxBITMAP_TYPE_PNG));
				break;
			case '2':
				imgMap[y * mapWidth + x] = new wxStaticBitmap(this, 2, wxBitmap("Sprites/Mouse-0001.png", wxBITMAP_TYPE_PNG));
				mouse = new cMazeAI(2, 'N', x, y, 4);
				break;
			case '3':
				imgMap[y * mapWidth + x] = new wxStaticBitmap(this, 3, wxBitmap("Sprites/Cat-0001.png", wxBITMAP_TYPE_PNG));
				cat = new cMazeAI(x, y);
				break;
			case '4':
				imgMap[y * mapWidth + x] = new wxStaticBitmap(this, 4, wxBitmap("Sprites/Cheese-0001.png", wxBITMAP_TYPE_PNG));
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

void cMain::SwapTiles(int firstTile, int secondTile) 
{

}

void cMain::NextStep() 
{

}

void cMain::AutoCycle() 
{
	while (true) 
	{
		NextStep();
	}
}