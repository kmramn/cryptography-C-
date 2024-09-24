
#include <Windows.h>
#include <winerror.h>

#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib")

#include "resource.h"

BOOL CALLBACK DialogProc(HWND H, UINT M, WPARAM W, LPARAM L)
{
	switch (M)
	{
	case WM_INITDIALOG:
		return TRUE;
    case WM_COMMAND:
        switch (LOWORD(W))
        {
        case IDOK:
            EndDialog(H, IDOK);
            break;
        case IDCANCEL:
            EndDialog(H, IDCANCEL);
            break;
        }
        break;
    default:
		return FALSE;
		break;
	}
    return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    InitCommonControls();
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DialogProc);
}
