#include "Resources.h"
#include "Methods.h"

int CALLBACK wWinMain(_In_ HINSTANCE hInst, _In_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

    srand(time(NULL));

    WNDCLASS mainClass = NewWindowClass(
        (HBRUSH)COLOR_WINDOW,
        LoadCursor(NULL, IDC_ARROW),
        hInst,
        LoadIcon(NULL, IDI_APPLICATION),
        L"MainWndClass",
        MainWindowProcedure
    );

    if (RegisterClass(&mainClass) == 0) {
        return EXIT_FAILURE;
    }

    hMainWND = CreateWindow(
        L"MainWndClass",
        L"Game of life",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
        100,
        100,
        StartButtonsSize_X + ButtonsSize_X + FieldSize_X * CellSize_X + 35,
        StartButtonsSize_Y + ButtonsSize_Y + FieldSize_Y * CellSize_Y + TitleSizeY,
        NULL,
        NULL,
        hInst,
        NULL
    );

    hFieldWND = InitField(hMainWND, hInst);

    ShowWindow(hMainWND, nCmdShow);
    UpdateWindow(hMainWND);

    MSG message = { 0 };

    while (GetMessage(&message, NULL, NULL, NULL)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    TerminateThread(thread, 0);
    
    return 0;
}

void CloseThread() {
    isStarting = false;
    isThreading = false;
    CloseHandle(thread);
    PostQuitMessage(0);
}


WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON hIcon, LPCWSTR Name, WNDPROC Procedure) {

    WNDCLASS  wc = { 0 };

    wc.hbrBackground = BGColor;
    wc.hCursor = Cursor;
    wc.hInstance = hInst;
    wc.hIcon = hIcon;
    wc.lpszClassName = Name;
    wc.lpfnWndProc = Procedure;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    return wc;
}


LRESULT CALLBACK MainWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        MainWNDAddMenus(hWnd);
        MainWndAddWidgets(hWnd);
        break;
    case WM_COMMAND:

        switch (wp) {
        case OnMenuClickedAboutAuthor:
            MessageBoxA(hWnd, "About author was clicked!", "Author", MB_ICONINFORMATION);
            break;
        case OnMenuClickedAboutProgram:
            MessageBoxA(hWnd, "About program was clicked!", "Program", MB_ICONINFORMATION);
            break;
        case OnButtonClickedStart:
            SendMessage(hFieldWND, msg, OnButtonClickedStart, NULL);
            break;
        case OnButtonClickedOneStep:
            SendMessage(hFieldWND, msg, OnButtonClickedOneStep, NULL);
            break;
        case OnButtonClickedReset:
            SendMessage(hFieldWND, msg, OnButtonClickedReset, NULL);
            break;
        case OnButtonClickedStop:
            SendMessage(hFieldWND, msg, OnButtonClickedStop, NULL);
            break;
        default:
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wp, lp);
    }
}


void MainWNDAddMenus(HWND hWnd) {
    HMENU RootMenu = CreateMenu();
    HMENU SubMenu = CreateMenu();

    AppendMenu(SubMenu, MF_STRING, OnMenuClickedAboutAuthor, L"About author");
    AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(SubMenu, MF_STRING, OnMenuClickedAboutProgram, L"About program");

    AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"About");

    SetMenu(hWnd, RootMenu);
}

void MainWndAddWidgets(HWND hWnd) {

    CreateWindowA("static", "Game of Life", WS_VISIBLE | WS_CHILD | ES_CENTER, 0, 10, ButtonsSize_X + FieldSize_X * CellSize_X + 35, TitleSizeY, hWnd, NULL, NULL, NULL);

    //Parametrs
    /*CreateWindowA("static", "Rows:", WS_VISIBLE | WS_CHILD | ES_RIGHT, StartButtonsSize_X, StartButtonsSize_Y, ButtonsSize_X, ButtonsSize_Y, hWnd, NULL, NULL, NULL);
    hEditRows = CreateWindowA("edit", "50", WS_VISIBLE | WS_CHILD | ES_LEFT | WS_BORDER | ES_NUMBER, StartButtonsSize_X + ButtonsSize_X + 10, StartButtonsSize_Y, ButtonsSize_X, ButtonsSize_Y, hWnd, NULL, NULL, NULL);
    CreateWindowA("static", "Cols:", WS_VISIBLE | WS_CHILD | ES_RIGHT, StartButtonsSize_X + ButtonsSize_X * 2 + 10, StartButtonsSize_Y, ButtonsSize_X, ButtonsSize_Y, hWnd, NULL, NULL, NULL);
    hEditCols = CreateWindowA("edit", "50", WS_VISIBLE | WS_CHILD | ES_LEFT | WS_BORDER | ES_NUMBER, StartButtonsSize_X + ButtonsSize_X * 3 + 10, StartButtonsSize_Y, ButtonsSize_X, ButtonsSize_Y, hWnd, NULL, NULL, NULL);
    CreateWindowA("static", "Delay:", WS_VISIBLE | WS_CHILD | ES_RIGHT, StartButtonsSize_X + ButtonsSize_X * 4 + 10, StartButtonsSize_Y, ButtonsSize_X, ButtonsSize_Y, hWnd, NULL, NULL, NULL);
    hEditDelay = CreateWindowA("edit", "10", WS_VISIBLE | WS_CHILD | ES_LEFT | WS_BORDER | ES_NUMBER, StartButtonsSize_X + ButtonsSize_X * 5 + 10, StartButtonsSize_Y, ButtonsSize_X, ButtonsSize_Y, hWnd, NULL, NULL, NULL);
    */
    //Buttons
    CreateWindowA("button", "Start", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_PUSHBUTTON, StartButtonsSize_X, StartButtonsSize_Y + ButtonsSize_Y * 5 + 10 * 5, ButtonsSize_X, ButtonsSize_Y, hWnd, (HMENU)OnButtonClickedStart, NULL, NULL);
    CreateWindowA("button", "One step", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_PUSHBUTTON, StartButtonsSize_X, StartButtonsSize_Y + ButtonsSize_Y * 6 + 10 * 6, ButtonsSize_X, ButtonsSize_Y, hWnd, (HMENU)OnButtonClickedOneStep, NULL, NULL);
    CreateWindowA("button", "Reset", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_PUSHBUTTON, StartButtonsSize_X, StartButtonsSize_Y + ButtonsSize_Y * 7 + 10 * 7, ButtonsSize_X, ButtonsSize_Y, hWnd, (HMENU)OnButtonClickedReset, NULL, NULL);
    CreateWindowA("button", "Stop", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_PUSHBUTTON, StartButtonsSize_X, StartButtonsSize_Y + ButtonsSize_Y * 8 + 10 * 8, ButtonsSize_X, ButtonsSize_Y, hWnd, (HMENU)OnButtonClickedStop, NULL, NULL);

}

HWND InitField(HWND hMainWND, HINSTANCE hInst) {

    WNDCLASS FieldClass = NewWindowClass(whiteBrush,
        LoadCursor(NULL, IDC_ARROW),
        hInst,
        LoadIcon(NULL, IDI_APPLICATION),
        L"FiledWndClass",
        FieldProcedure
    );

    RegisterClass(&FieldClass);

    HWND field = CreateWindow(L"FiledWndClass",
        L"Field",
        WS_CHILD | WS_VISIBLE,
        StartButtonsSize_X + ButtonsSize_X + 10,
        StartButtonsSize_Y,
        FieldSize_X * CellSize_X,
        FieldSize_Y * CellSize_Y,
        hMainWND,
        NULL,
        NULL,
        NULL
    );

    return field;
}

LRESULT CALLBACK FieldProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        break;
    case WM_PAINT:
        BeginPaint(hWnd, &ps);
        DrawField(hWnd);
        EndPaint(hWnd, &ps);
        break;
    case WM_COMMAND:
        switch (wp) {
        case OnButtonClickedStart:
            if (!isStarting) {
                isStarting = true;
                isThreading = true;
                thread = CreateThread(NULL, 0, RenderingThread, (LPVOID)hWnd, 0, NULL);
            }
            break;
        case OnButtonClickedOneStep:
            DrawGeneration(hWnd);
            break;
        case OnButtonClickedReset:
            if (!isStarting) {
                cellGeneration.~CellGeneration();
                DrawGeneration(hWnd);
            }
            break;
        case OnButtonClickedStop:
            isStarting = false;
            isThreading = false;
            break;
        }
        break;
    case WM_DESTROY:
        CloseThread();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wp, lp);
    }
}

DWORD WINAPI RenderingThread(LPVOID lp) {

    while (cellGeneration.CompareGeneration()) {
        if (!isThreading) {
            break;
        }
        DrawGeneration((HWND)lp);
        Sleep(SPEED);
    }

    return -1;
}

void DrawField(HWND hWnd) {

    cellGeneration.FillCellGeneration();

    vector<vector<Cell>> generation = cellGeneration.GetGeneration();

    for (int i = 0; i < generation.size(); i++) {
        for (int j = 0; j < generation[0].size(); j++) {
            SelectBrush(generation[i][j].GetState());
            RECT cell = { CellSize_X * j, CellSize_Y * i, CellSize_X * (j + 1), CellSize_Y * (i + 1) };
            Rectangle(ps.hdc, CellSize_X * j, CellSize_Y * i, CellSize_X * (j + 1), CellSize_Y * (i + 1));
        }
    }

}

void DrawGeneration(HWND hWnd) {

    cellGeneration.FillCellGeneration();

    vector<vector<Cell>> generation = cellGeneration.GetGeneration();

    for (int i = 0; i < generation.size(); i++) {
        for (int j = 0; j < generation[0].size(); j++) {
            SelectBrush(generation[i][j].GetState());
            RECT cell = { CellSize_X * j, CellSize_Y * i, CellSize_X * (j + 1), CellSize_Y * (i + 1) };
            InvalidateRect(hWnd, &cell, FALSE);
        }
    }
    UpdateWindow(hWnd);
}

void SelectBrush(int state) {

    if (state == 0) {
        SelectObject(ps.hdc, whiteBrush);
    }
    if (state == 1) {
        SelectObject(ps.hdc, yinBrush);
    }
    else if (state == 2) {
        SelectObject(ps.hdc, yangBrush);
    }
 
}
