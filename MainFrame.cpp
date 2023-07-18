#include "MainFrame.h"

MainFrame::MainFrame(const wxString title) : wxFrame(nullptr, wxID_ANY, title)
{
	wxBoxSizer* topsizer = new wxBoxSizer(wxVERTICAL);
	this->header = new HeaderPanel(this, 1000, 50);
	this->panel = new DrawingPanel(this, 1000, 700, header);
	topsizer->Add(
		header,
		0,            // make vertically stretchable
		wxEXPAND |    // make horizontally stretchable
		wxALL,        //   and make border all around
		0);         // set border width to 10
	topsizer->Add(
		panel,
		1,            // make vertically stretchable
		wxEXPAND |    // make horizontally stretchable
		wxALL,        //   and make border all around
		0);         // set border width to 10
	SetSizerAndFit(topsizer);
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::exit, this);
	
}

void MainFrame::exit(wxCloseEvent& event)
{
	this->panel->exit();
	event.Skip();
}
