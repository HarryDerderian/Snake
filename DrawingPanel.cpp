#include "DrawingPanel.h"
#include <iostream>
#include <cstdlib>

DrawingPanel::DrawingPanel(wxWindow* parent, int width, int height, HeaderPanel* scoreboard) : wxPanel(parent)
{
    SetDoubleBuffered(true);
    SetBackgroundColour(*wxBLACK);
    SetMinSize(wxSize(width, height));
    timer = new wxTimer(this, wxID_ANY);
    setupBinds();
    SetDoubleBuffered(true);
    timer->Start(FRAME_RATE);
    this->scoreboard = scoreboard;
    SetFocus();
}

void DrawingPanel::setupBinds()
{
    Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
    Bind(wxEVT_SIZE, &DrawingPanel::OnSize, this);
    Bind(wxEVT_KEY_DOWN, &DrawingPanel::OnKeyDown, this);
    Bind(wxEVT_TIMER, &DrawingPanel::OnTimer, this, timer->GetId());
}

void DrawingPanel::drawApple(wxPaintDC& dc)
{
    dc.SetBrush(*wxRED_BRUSH);
    dc.DrawRectangle(wxPoint(appleX, appleY), wxSize(SCALE, SCALE));
}

void DrawingPanel::checkCollisions()
{
    Snake::Cord head = snake.getHead();
    gameOver = snake.headIntersectsBody() || head.x < 0 
        || head.y < 0 || head.x > (GetSize().x - SCALE) || head.y > (GetSize().y - SCALE);
    if (gameOver) return;
    Snake::Cord cord;
    cord.x = appleX;
    cord.y = appleY;
    if (snake.containsCord(cord))
    {
        snake.grow();
        updateAppleCord();
        score += 100;
        scoreboard->updateScore(score);
        scoreboard->Refresh();
    }
}

void DrawingPanel::checkBorderCollisions()
{
    Snake::Cord head = snake.getHead();
    int maxX = GetSize().x;
    int maxY = GetSize().y;
   
    if (head.x < 0 || head.y < 0)
    {
        gameOver = true;
    }
}


void DrawingPanel::updateAppleCord()
{
    int width = GetSize().x;
    int height = GetSize().y;
    int rand();
    Snake::Cord cord;
    do
    {
        appleX = (rand() % (width / SCALE)) * SCALE;
        appleY = (rand() % (height / SCALE)) * SCALE;
        cord.x = appleX;
        cord.y = appleY;
    } while (snake.containsCord(cord));
}

void DrawingPanel::OnSize(wxSizeEvent& event)
{
    Refresh();
    event.Skip();
}

void DrawingPanel::OnPaint(wxPaintEvent& event) // repaint
{
    wxPaintDC dc(this);
    dc.Clear();
    drawPlayer(dc);
    drawApple(dc);
    if (gameOver)
    {
        displayGameOver(dc);
    }
    dc.SetPen(wxColour(0, 234, 255));
    dc.DrawLine(wxPoint(0, 0), wxPoint(this->GetSize().x, 0));
    dc.DrawLine(wxPoint(0, 0), wxPoint(0, this->GetSize().y));
    dc.DrawLine(wxPoint(0, this->GetSize().y - 1), wxPoint(this->GetSize().x, this->GetSize().y - 1));
    dc.DrawLine(wxPoint(this->GetSize().x - 1, 0), wxPoint(this->GetSize().x - 1, this->GetSize().y));
}

void DrawingPanel::displayGameOver(wxPaintDC& dc)
{
    dc.SetTextForeground(wxColour(0, 234, 255));
    dc.SetFont(wxFont(wxFontInfo(50).Family(wxFONTFAMILY_TELETYPE).Bold()));
    wxString text = "G A M E  O V E R";
    wxSize textSize = dc.GetTextExtent(text);
    int x = (GetSize().GetWidth() - textSize.GetWidth()) / 2; 
    int y = (GetSize().GetHeight() - textSize.GetHeight()) / 2;  
    dc.DrawText(text, x, y);
}

void DrawingPanel::restartGame()
{
    appleX = SCALE;
    appleY = 0;
    snake.reset();

    currentDir = Direction::EAST;
    score = 0;
    scoreboard->updateScore(score);
    scoreboard->Refresh();
    gameOver = false;
}



void DrawingPanel::drawPlayer(wxPaintDC& dc)
{
    dc.SetBrush(*wxGREEN_BRUSH);
    std::list<Snake::Cord> ssssssnake = snake.getSnake();
    for (Snake::Cord cord : ssssssnake)
    {
        dc.DrawRectangle(wxPoint(cord.x, cord.y), wxSize(SCALE, SCALE));
    }
}

void DrawingPanel::OnKeyDown(wxKeyEvent& event)
{
    char keyCode = event.GetKeyCode();
    switch (keyCode)
    {
    case 65: // [A] left
        if(currentDir != Direction::EAST)
        currentDir = Direction::WEST;
        break;
    case 68: // [D] right
        if(currentDir != Direction::WEST)
        currentDir = Direction::EAST;
        break;
    case 87: // [W] north
        if (currentDir != Direction::SOUTH)
        currentDir = Direction::NORTH;
        break;
    case 83: // [S] south
        if (currentDir != Direction::NORTH)
        currentDir = Direction::SOUTH;
        break;
    case 32: // [SPACE BAR]
        if (gameOver)
            restartGame();
        break;
    }
}

void DrawingPanel::OnTimer(wxTimerEvent& event)
{
    if (!gameOver)
    {
        switch (currentDir)
        {
        case Direction::NORTH:
            snake.move(0, -SCALE);
            break;
        case Direction::EAST:
            snake.move(SCALE, 0);
            break;
        case Direction::SOUTH:
            snake.move(0, SCALE);
            break;
        case Direction::WEST:
            snake.move(-SCALE, 0);
            break;
        }
        checkCollisions();
    }
    Refresh();
}

void DrawingPanel::exit()
{
    delete timer;
}