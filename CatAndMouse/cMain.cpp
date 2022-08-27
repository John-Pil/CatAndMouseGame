#include "cMain.h"

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "CatAndMouse", wxPoint(300, 30), wxSize(1024, 1024))
{
	byte counter = 0;
	listLog = new wxListBox();
	wxImage::AddHandler(new wxPNGHandler);

	for (int i = 0; i < 16; i++) 
	{
		for (int j = 0; j < 16; j++)
		{
			imgMap[i][j] = new wxImage("Sprites/FloorTile-0001.png", wxBITMAP_TYPE_PNG);
			counter++;
		}
	}
	std::cout << counter;
}

cMain::~cMain()
{
}