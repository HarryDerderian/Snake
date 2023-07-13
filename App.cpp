#include "App.h"
#include "MainFrame.h"
#include <iostream>

wxIMPLEMENT_APP(App);
bool App::OnInit()
{
	MainFrame* mainFrame = new MainFrame("Snake");
	mainFrame->Fit();
	mainFrame->Show();
	mainFrame->Center();
	return true;
}