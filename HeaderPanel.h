#ifndef HEADERPANEL_H
#define HEADERPANEL_H
#include <wx/wx.h>

class HeaderPanel : public wxPanel
{
public:
	HeaderPanel(wxWindow* parent, int width, int height);
	void OnPaint(wxPaintEvent& event);
	void displayScore(wxPaintDC& dc);
	void updateScore(int score);
	void OnSize(wxSizeEvent& event);
private:
	int score = 0;
	
};
#endif

