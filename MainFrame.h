#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <wx/wx.h>
#include "DrawingPanel.h"
#include "HeaderPanel.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString title);
private:
	DrawingPanel* panel;
	HeaderPanel* header;
	void exit(wxCloseEvent& event);

};
#endif