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
	m_frame1 = new cMain();
	m_frame1->Show(true);

	return true;
}