// win32_main.c

#include <Windows.h>
#include <gl/gl.h>

static bool global_running = false;

LRESULT CALLBACK Win32MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch(uMsg)
  {
    case WM_CLOSE:
    {
      global_running = false;
      PostQuitMessage(0);
    } break;
    default:
    {
      return DefWindowProc(hWnd, uMsg, wParam, lParam);
    } break;
  }

  return 0;
}

int main(int argc, char** argv)
{
  WNDCLASSEX wcex = {};  
  wcex.cbSize = sizeof(WNDCLASSEX);  
  wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wcex.lpfnWndProc = Win32MainWindowProc;  
  wcex.cbClsExtra = 0;  
  wcex.cbWndExtra = 0;  
  wcex.hInstance = GetModuleHandle(NULL);  
  wcex.hIcon = NULL;
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);  
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);  
  wcex.lpszMenuName = NULL;  
  wcex.lpszClassName = L"tbgWindowClass";  
  wcex.hIconSm = NULL;
  if (!RegisterClassEx(&wcex))
  {
    return -1;
  }

  HWND hWnd = CreateWindow(  
    wcex.lpszClassName,  
    L"Jump",  
    (DWORD)(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU),
    CW_USEDEFAULT, 
    CW_USEDEFAULT,  
    720, 
    1280,
    NULL,  
    NULL,  
    wcex.hInstance,  
    NULL);
  if (!hWnd)
  {
    return -1;
  }

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  global_running = true;
  while(global_running)
  {
    MSG msg;  
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))  
    {  
      TranslateMessage(&msg);  
      DispatchMessage(&msg);  
    }

    Sleep(5);
  }  

  return 0;
}
