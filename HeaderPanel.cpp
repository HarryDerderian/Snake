#include "HeaderPanel.h"

HeaderPanel::HeaderPanel(wxWindow* parent, int width, int height) : wxPanel(parent)
{
    Bind(wxEVT_PAINT, &HeaderPanel::OnPaint, this);
    Bind(wxEVT_SIZE, &HeaderPanel::OnSize, this);
    SetMinSize(wxSize(width, height));
    SetBackgroundColour(wxColour(61, 62, 64));
}

void HeaderPanel::OnPaint(wxPaintEvent& event) // repaint
{
    wxPaintDC dc(this);
    dc.Clear();
    displayScore(dc);
}

void HeaderPanel::updateScore(int score)
{
    this->score = score;
}

void HeaderPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    event.Skip();
}

void HeaderPanel::displayScore(wxPaintDC& dc)
{
    dc.SetTextForeground(wxColour(0, 234, 255));
    dc.SetFont(wxFont(wxFontInfo(22).Family(wxFONTFAMILY_TELETYPE).Bold()));
    wxString text = "SCORE: " + wxString(std::to_string(score));
    wxSize textSize = dc.GetTextExtent(text);
    int x = (GetSize().GetWidth() - textSize.GetWidth()) / 2;
    int y = (GetSize().GetHeight() - textSize.GetHeight()) / 2;
    dc.DrawText(text, x, y);

    dc.DrawText(wxString("SNAKE"), 10, y);
    dc.DrawText(wxString("C++"), GetSize().x - 100, y);
}
