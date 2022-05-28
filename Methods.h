#pragma once

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON hIcon, LPCWSTR Name, WNDPROC Procedure);
void CloseThread();
LRESULT CALLBACK MainWindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
void MainWNDAddMenus(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);
HWND InitField(HWND hWnd, HINSTANCE hInst);
LRESULT CALLBACK FieldProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
DWORD WINAPI RenderingThread(LPVOID lp);
void DrawField(HWND hWnd);
void DrawGeneration(HWND hWnd);
void SelectBrush(int state);