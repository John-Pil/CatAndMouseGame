#pragma once

#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	wxImage *imgMap[16][16];
	wxListBox *listLog = nullptr;
};

