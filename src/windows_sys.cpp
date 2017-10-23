#pragma once
#include "resource.h"

#include <stdio.h>
#include <string>
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <windows.h>
#include <Dbt.h>
#include <initguid.h>
#include <winioctl.h>
#include <winsock2.h>
#include <devguid.h>
#include <hrutil/hrutil.h>
#include "windows_sys.h"
#include "CSystemTray.h"
#include "gtk_win.h"
#include "data_calc_util.h"

#define MAX_LOADSTRING 100      

//////////////////////////////
//  
// 字符转换相关
//
/////////////////////////////

#ifdef UNICODE  
#define CHAR2TCHAR(c,tc,tc_len) MultiByteToWideChar(CP_ACP, 0, c, -1, tc, tc_len);  
#else  
#define CHAR2TCHAR(c,tc,tc_len) strcpy(tc, c);  
#endif  

char* ConvertLPWSTRToLPSTR (LPWSTR lpwszStrIn)  
{  
    LPSTR pszOut = NULL;  
    if (lpwszStrIn != NULL)  
    {  
        int nInputStrLen = wcslen (lpwszStrIn);  
  
        // Double NULL Termination  
        int nOutputStrLen = WideCharToMultiByte (CP_ACP, 0, lpwszStrIn, nInputStrLen, NULL, 0, 0, 0) + 2;  
        pszOut = new char [nOutputStrLen];  
  
        if (pszOut)  
        {  
            memset (pszOut, 0x00, nOutputStrLen);  
            WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, pszOut, nOutputStrLen, 0, 0);  
        }  
    }  
    return pszOut;  
}  

/***************************************************************************** 
 * 将一个字符的Unicode(UCS-2和UCS-4)编码转换成UTF-8编码. 
 * 
 * 参数: 
 *    unic     字符的Unicode编码值 
 *    pOutput  指向输出的用于存储UTF8编码值的缓冲区的指针 
 *    outsize  pOutput缓冲的大小 
 * 
 * 返回值: 
 *    返回转换后的字符的UTF8编码所占的字节数, 如果出错则返回 0 . 
 * 
 * 注意: 
 *     1. UTF8没有字节序问题, 但是Unicode有字节序要求; 
 *        字节序分为大端(Big Endian)和小端(Little Endian)两种; 
 *        在Intel处理器中采用小端法表示, 在此采用小端法表示. (低地址存低位) 
 *     2. 请保证 pOutput 缓冲区有最少有 6 字节的空间大小! 
 ****************************************************************************/ 

static int enc_unicode_to_utf8_one(TCHAR unic, unsigned char *pOutput,  
        int outSize)  
{  
    if ( unic <= 0x0000007F )  
    {  
        // * U-00000000 - U-0000007F:  0xxxxxxx  
        *pOutput     = (unic & 0x7F);  
        return 1;  
    }  
    else if ( unic >= 0x00000080 && unic <= 0x000007FF )  
    {  
        // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx  
        *(pOutput+1) = (unic & 0x3F) | 0x80;  
        *pOutput     = ((unic >> 6) & 0x1F) | 0xC0;  
        return 2;  
    }  
    else if ( unic >= 0x00000800 && unic <= 0x0000FFFF )  
    {  
        // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx  
        *(pOutput+2) = (unic & 0x3F) | 0x80;  
        *(pOutput+1) = ((unic >>  6) & 0x3F) | 0x80;  
        *pOutput     = ((unic >> 12) & 0x0F) | 0xE0;  
        return 3;  
    }  
    else if ( unic >= 0x00010000 && unic <= 0x001FFFFF )  
    {  
        // * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx  
        *(pOutput+3) = (unic & 0x3F) | 0x80;  
        *(pOutput+2) = ((unic >>  6) & 0x3F) | 0x80;  
        *(pOutput+1) = ((unic >> 12) & 0x3F) | 0x80;  
        *pOutput     = ((unic >> 18) & 0x07) | 0xF0;  
        return 4;  
    }  
    else if ( unic >= 0x00200000 && unic <= 0x03FFFFFF )  
    {  
        // * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx  
        *(pOutput+4) = (unic & 0x3F) | 0x80;  
        *(pOutput+3) = ((unic >>  6) & 0x3F) | 0x80;  
        *(pOutput+2) = ((unic >> 12) & 0x3F) | 0x80;  
        *(pOutput+1) = ((unic >> 18) & 0x3F) | 0x80;  
        *pOutput     = ((unic >> 24) & 0x03) | 0xF8;  
        return 5;  
    }  
    else if ( unic >= 0x04000000 && unic <= 0x7FFFFFFF )  
    {  
        // * U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx  
        *(pOutput+5) = (unic & 0x3F) | 0x80;  
        *(pOutput+4) = ((unic >>  6) & 0x3F) | 0x80;  
        *(pOutput+3) = ((unic >> 12) & 0x3F) | 0x80;  
        *(pOutput+2) = ((unic >> 18) & 0x3F) | 0x80;  
        *(pOutput+1) = ((unic >> 24) & 0x3F) | 0x80;  
        *pOutput     = ((unic >> 30) & 0x01) | 0xFC;  
        return 6;  
    }  
  
    return 0;  
}  

void enc_unicode_to_utf8_str(TCHAR* unic, char *pOutput)
{
    int un = 0 ;
    int utf8 = 0 ;
    int len ;

    for(un=0; unic[un] != 0  ; un++ )
    {
        len = enc_unicode_to_utf8_one(unic[un], (unsigned char *)(pOutput+utf8), 6);
        utf8+= len ;
    }
    pOutput[utf8] = '\0' ;
}

/////////////////////////////////
//
// 窗体显示
//
////////////////////////////////

#define WM_ICON_NOTIFY (WM_USER + 10056)
CSystemTray m_TrayIcon;

// 全局变量:
HINSTANCE hInst;                                // 当前实例
TCHAR szTitle[MAX_LOADSTRING] = _T("TEst");                  // 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING] = _T("TEst") ;            // 主窗口类名

// 显示输出
HWND g_hEdit ;
#define MAX_MSG_TEXT_LEN    1024*20         ///< 最多显示的文字长度
#define MSG_TEXT_DELETE_LEN    1024         ///< 每次删除的长度
TCHAR g_msg_text[MAX_MSG_TEXT_LEN];
int g_msg_text_end_index ;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK SET_UDP(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY usbChange_tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MSG msg;
    HACCEL hAccelTable;

    // 初始化全局字符串
    //LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    g_strlcpy(szTitle,hrutil_utf8_to_gb2312(mg_htxy_global.platform_name),sizeof(szTitle));
    LoadString(hInstance, IDC_USBCHANGE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 系统未登录时，应用程序初始化会失败，登录后，就会成功
    // 所以，此处反复执行，直到成功
    while(!InitInstance (hInstance, nCmdShow))
    {
        Sleep(1000);
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_USBCHANGE));

    // 主消息循环:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)0;// msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style            = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra        = 0;
    wcex.cbWndExtra        = 0;
    wcex.hInstance        = hInstance;
    wcex.hIcon            = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_USBCHANGE));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName    = MAKEINTRESOURCE(IDC_USBCHANGE);
    wcex.lpszClassName    = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd,SW_HIDE);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    int cxClient,cyClient ;

    switch (message)
    {
    case WM_CREATE :
        g_hEdit = CreateWindow (TEXT ("edit"), NULL,
            WS_CHILD | WS_VISIBLE | WS_VSCROLL |
            WS_BORDER | ES_LEFT | ES_MULTILINE | ES_WANTRETURN |
            ES_AUTOVSCROLL,
            0, 0, 0, 0, hWnd, (HMENU) ID_EDIT,
            ((LPCREATESTRUCT) lParam) -> hInstance, NULL) ;
        if(g_hEdit)
        {
            SetWindowText(g_hEdit,g_msg_text);
        }
        SetTimer(hWnd,1,mg_htxy_global.listenser_watch,NULL);
        SetTimer(hWnd,2,mg_htxy_global.listenser_delay,NULL);

        //系统图标
        m_TrayIcon.hInstance = hInst ;
        //此处若系统未登录，则可能不会成功，应一直调用到其成功
        while(!m_TrayIcon.Create(hWnd, WM_ICON_NOTIFY,szTitle, NULL, 0))
        {
            Sleep(1000);
        }
        m_TrayIcon.SetIcon(IDI_USBCHANGE);
        return 0 ;
    case WM_SIZE :
        cxClient = LOWORD (lParam) ;
        cyClient = HIWORD (lParam) ;
        MoveWindow(g_hEdit,0,0,cxClient,cyClient,TRUE);
        return 0 ;
    case WM_TIMER :
        if(wParam == 1)
        {
            char new_data[TYPE_URL_MAX_LEN] ;
            new_data[0] = '\0' ; 
            if ( OpenClipboard(NULL) )
            {
                HANDLE hData = GetClipboardData(CF_TEXT);
                char * buffer = (char*)GlobalLock(hData);
                g_strlcpy(new_data,buffer,sizeof(new_data));
                GlobalUnlock(hData);
                CloseClipboard();

                if( ( new_data[0] != '\0' )
                    && (strcmp(new_data,mg_htxy_global.clipboard_text) != 0 ) )
                {
                    g_strlcpy(mg_htxy_global.clipboard_text,new_data,sizeof(mg_htxy_global.clipboard_text));
                    if(info_find_user(mg_htxy_global.clipboard_text))
                    {
                        RUN_GTK_FUNC(widget_update_and_show_info);
                    }
                }
            }
        }
        else if(wParam == 2)
        {
            update_organs_db();
        }
        break ;
    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);

        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case ID_CLEAR_TEXT:
            break;
        case ID_SET_UDP:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SET_UDP), hWnd, SET_UDP);
            break;
        case IDM_EXIT:
            m_TrayIcon.RemoveIcon();
            DestroyWindow(hWnd);
            break;
        case ID_SYS_BAR_MENU_EXIT:
            exit_process();
        case ID_SYS_BAR_MENU_VIEW:
            RUN_GTK_FUNC(widget_switch_init);
            break ;
        case ID_SYS_BAR_MENU_SET:
            RUN_GTK_FUNC(widget_switch_set);
            break ;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        // TODO: 在此添加任意绘图代码...
        EndPaint(hWnd, &ps);
        break;
    case WM_SYSCOMMAND :
        if (wParam == SC_CLOSE)
        { 
            ShowWindow(hWnd,SW_SHOWMINIMIZED);
            ShowWindow(hWnd,SW_HIDE);
        }
        else
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break ;
    case WM_ICON_NOTIFY :
        if (LOWORD(lParam) == WM_LBUTTONDBLCLK) 
        {
            RUN_GTK_FUNC(widget_switch_init);
        }
        else if (LOWORD(lParam) == WM_RBUTTONDOWN) 
        {
            HMENU menu ;
            HMENU pPopup ;
            POINT pt ;

            menu = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU_SYS_BAR));
            if(menu)
            {
                GetCursorPos(&pt);  //取得鼠标位置
                SetForegroundWindow(hWnd); 
                pPopup=GetSubMenu(menu , 0);
                //ClientToScreen(hWnd,&pt);
                TrackPopupMenu(pPopup,TPM_LEFTALIGN | TPM_RIGHTBUTTON,pt.x,pt.y,0,hWnd,NULL);
            }

        }
        break ;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

BOOL WINAPI CenterWindow(HWND hWnd)
{
    HWND parent ;
    RECT    rtWindow = {0};
    RECT    rtContainer = {0};

    GetWindowRect(hWnd,&rtWindow);
    rtWindow.right -= rtWindow.left;
    rtWindow.bottom -= rtWindow.top;

    parent = GetParent(hWnd);
    if(parent == NULL)
    {
        SystemParametersInfo(SPI_GETWORKAREA,0,&rtContainer,0);
    }
    else
    {
        GetWindowRect(parent,&rtContainer);
    }
    return SetWindowPos(hWnd,NULL,(rtContainer.right - rtWindow.right) / 2,(rtContainer.bottom - rtWindow.bottom) / 2,0,0,SWP_NOSIZE);
}
 
// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//extern int test_use_ddk();
// “设置UDP”框的消息处理程序。
INT_PTR CALLBACK SET_UDP(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND hEdit ;

    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        hEdit = GetDlgItem (hDlg, IDC_EDIT_IPADDR) ;
        SetWindowText(hEdit,_T("22"));

        hEdit = GetDlgItem (hDlg, IDC_EDIT_PORT) ;
        SetWindowText(hEdit,_T("11"));
        EnableWindow(hEdit,FALSE);

        CenterWindow(hDlg);

        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            //test_use_ddk();
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDOK)
        {
        }
        break;
    }
    return (INT_PTR)FALSE;
}
