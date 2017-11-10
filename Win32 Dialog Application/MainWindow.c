#include "stdafx.h"
#include "AboutDialog.h"
#include "Globals.h"
#include "MainWindow.h"
#include "Resource.h"

static LPCTSTR MainWndClass = TEXT("Win32 Dialog Application");

/* Window procedure for our main window */
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
    case WM_COMMAND:
    {
      WORD id = LOWORD(wParam);

      switch (id)
      {
        case ID_HELP_ABOUT:
        {
          ShowAboutDialog(hWnd);
          return 0;
        }

        case IDOK:
        case IDCANCEL:
        {
          DestroyWindow(hWnd);
          return 0;
        }
      }
      break;
    }

    /* Item from system menu has been invoked */
    case WM_SYSCOMMAND:
    {
      WORD id = LOWORD(wParam);

      switch (id)
      {
        /* Show "about" dialog on about system menu item */
        case ID_HELP_ABOUT:
        {
          ShowAboutDialog(hWnd);
          return 0;
        }
      }
      break;
    }

    case WM_CREATE:
    {
      HWND dummyWnd;
      RECT rect;

      /* We want the OS to position the window, but this can't be done with windows created using CreateDialog.
       * Therefore we create a temporary dummy window to see where it would have been positioned, and then move the
       * dialog to that position. */
      dummyWnd = CreateWindowEx(0, TEXT("STATIC"), TEXT("STATIC"), 0, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, NULL, NULL,
                                g_hInstance, NULL);
      GetWindowRect(dummyWnd, &rect);
      DestroyWindow(dummyWnd);

      /* Move the dialog to where the dummy window was positioned */
      SetWindowPos(hWnd, 0, rect.left, rect.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

      return 0;
    }

    case WM_DESTROY:
    {
      PostQuitMessage(0);
      return 0;
    }
  }

  return DefWindowProc(hWnd, msg, wParam, lParam);
}

/* Register a class for our main window */
BOOL RegisterMainWindowClass()
{
  WNDCLASSEX wc;

  /* Class for our main window */
  wc.cbSize        = sizeof(wc);
  wc.style         = 0;
  wc.lpfnWndProc   = &MainWndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = DLGWINDOWEXTRA;
  wc.hInstance     = g_hInstance;
  wc.hIcon         = (HICON)LoadImage(g_hInstance, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE |
                                      LR_DEFAULTCOLOR | LR_SHARED);
  wc.hCursor       = (HCURSOR)LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED);
  wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = MainWndClass;
  wc.hIconSm       = (HICON)LoadImage(g_hInstance, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);

  return (RegisterClassEx(&wc)) ? TRUE : FALSE;
}

/* Create an instance of our main window */
HWND CreateMainWindow()
{
  /* Create instance of main window */
  HWND hWnd = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, NULL);

  if (hWnd)
  {
    /* Add "about" to the system menu */
    HMENU hSysMenu = GetSystemMenu(hWnd, FALSE);
    InsertMenu(hSysMenu, 5, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
    InsertMenu(hSysMenu, 6, MF_BYPOSITION, ID_HELP_ABOUT, TEXT("About"));
  }

  return hWnd;
}
