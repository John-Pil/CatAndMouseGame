#pragma once

#include "wx/wx.h"
#include "cMazeAI.h"

class cMain : public wxFrame
{
public:
	//constructors and deconstructor
	cMain();
	cMain(std::string file);
	~cMain();

	//public class functions
	void SwapTiles(int firstTile, int secondTile);
	void NextStep();
	void AutoCycle();
	
	//public variables
	int mapWidth = 16, mapHeight = 16;
	wxStaticBitmap **imgMap;
	wxListBox *listLog = nullptr;

private:
	//private variables
	cMazeAI *cat, *mouse;
};

