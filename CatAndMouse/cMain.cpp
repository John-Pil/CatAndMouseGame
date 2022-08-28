#include "cMain.h"

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "CatAndMouse", wxPoint(300, 30), wxSize(1124, 1024))
{
	listLog = new wxListBox(this, wxID_ANY, wxPoint(1,1), wxSize(100, 924));
	wxImage::AddHandler(new wxPNGHandler);
	imgMap = new wxStaticBitmap * [mapWidth * mapHeight];
	
	wxGridSizer *imgGrid = new wxGridSizer(mapWidth, mapHeight, 0, 0);

	for (int x = 0; x < mapWidth; x++) 
	{
		for (int y = 0; y < mapHeight; y++)
		{
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

	this->SetSizer(imgGrid);
	imgGrid->Layout();
}

cMain::~cMain()
{
}