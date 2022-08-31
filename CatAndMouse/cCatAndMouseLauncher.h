#pragma once

#include "wx/wx.h"
#include "cMain.h"

class cCatAndMouseLauncher : public wxApp
{
public:
	cCatAndMouseLauncher();
	~cCatAndMouseLauncher();
	virtual bool OnInit();

private:
	cMain *m_frame1 = nullptr;
};

