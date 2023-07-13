#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H
#include <wx/wx.h>
#include "Snake.h"
#include "HeaderPanel.h";

class DrawingPanel : public wxPanel
{
public:
	DrawingPanel(wxWindow* parent, int width, int height, HeaderPanel*);
	void exit();
private:
	const int SCALE = 40; // Represents the size of squares in pixels: I.E. SCALE^2 = Area of square.
							// Also determines the extent of movement adjustments.
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void drawPlayer(wxPaintDC& dc);
	void OnTimer(wxTimerEvent& event);
	void setupBinds();
	wxTimer* timer;
	HeaderPanel* scoreboard;
	const int FRAME_RATE = 1000 / 14;
	Snake snake;
	int appleX = SCALE;
	int appleY = 0;
	enum class Direction
	{
		NORTH, SOUTH, EAST, WEST
	};
	Direction currentDir = Direction::EAST;
	void updateAppleCord();
	void drawApple(wxPaintDC& dc);
	void checkCollisions();
	bool gameOver = false;
	void checkBorderCollisions();
	int score = 0;
	void displayGameOver(wxPaintDC& dc);
	void restartGame();
};
#endif