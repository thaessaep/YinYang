#pragma once

#include <Windows.h>
#include "CellGeneration.h"

#define FieldSize_X				50
#define FieldSize_Y				50
#define CellSize_X				12
#define CellSize_Y				12
#define TitleSizeY				40
#define ParameterFieldSize_Y	50
#define SPEED					10


#define StartButtonsSize_X	10
#define StartButtonsSize_Y	50
#define ButtonsSize_X		120
#define ButtonsSize_Y		30
#define InscriprionSize_X   80

//Command menu
#define OnMenuClickedAboutAuthor	1
#define OnMenuClickedAboutProgram	2

//Buttons menu
#define OnButtonClickedStart	3
#define OnButtonClickedOneStep	4
#define OnButtonClickedReset	5
#define OnButtonClickedStop		6

//edit controls
HWND hEditRows;
HWND hEditCols;
HWND hEditDelay;


//HWND
HWND hMainWND;
HWND hFieldWND;
PAINTSTRUCT ps;


HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
HBRUSH yinBrush = CreateSolidBrush(RGB(0, 206, 209));
HBRUSH yangBrush = CreateSolidBrush(RGB(65, 105, 225));

//Thread
HANDLE thread;
volatile bool isThreading = true;
volatile bool isStarting = false;

//Generation
CellGeneration cellGeneration(FieldSize_X, FieldSize_Y);