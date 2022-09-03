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
	int GetNextTileOffset(char direction);
	void SwapTiles(int firstTile, int secondTile);
	bool NextStep(cMazeAI * entity);
	void AutoCycle();
	
	//public variables
	int mapWidth = 16, mapHeight = 16;
	int *tileIds;
	wxStaticBitmap **imgMap;
	wxToolBar *listLog = nullptr;

	//ai entities
	cMazeAI *cat = nullptr;
	cMazeAI *mouse = nullptr;

private:
	void OnKeyPress(wxKeyEvent &evt);

	bool cycling = false;

	wxDECLARE_EVENT_TABLE();
};

