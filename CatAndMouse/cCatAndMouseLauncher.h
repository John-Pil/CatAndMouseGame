#pragma once

#include "wx/wx.h"
#include "cMain.h"

class cCatAndMouseLauncher : public wxApp
{
public:
	cCatAndMouseLauncher();
	~cCatAndMouseLauncher();

private:
	cMain *m_frame1 = nullptr;

public:
	virtual bool OnInit();
};

