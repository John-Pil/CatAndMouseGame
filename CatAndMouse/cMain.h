#pragma once

#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();


	int mapWidth = 16, mapHeight = 16;
	wxStaticBitmap **imgMap;
	wxListBox *listLog = nullptr;

};

