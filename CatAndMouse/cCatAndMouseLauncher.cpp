#include "cCatAndMouseLauncher.h"

wxIMPLEMENT_APP(cCatAndMouseLauncher);

cCatAndMouseLauncher::cCatAndMouseLauncher() 
{
}

cCatAndMouseLauncher::~cCatAndMouseLauncher() 
{
}

bool cCatAndMouseLauncher::OnInit() 
{
	//Create the new maze frame and show it
	m_frame1 = new cMain("Mazes/Maze-0002.txt");
	m_frame1->Show(true);	

	return true;
}