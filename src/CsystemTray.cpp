#include <stdio.h>
#include <string>
#include <tchar.h>
#include <windows.h>
#include "CSystemTray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////
// CSystemTray construction/creation/destruction

CSystemTray::CSystemTray()
{
    memset(&m_tnd, 0, sizeof(m_tnd));
    m_bEnabled = FALSE;
    m_bHidden = FALSE;
}

CSystemTray::CSystemTray(HWND m_hwnd, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID)
{
    Create(m_hwnd, uCallbackMessage, szTip, icon, uID);
    m_bHidden = FALSE;
}

BOOL CSystemTray::Create(HWND m_hwnd, UINT uCallbackMessage, LPCTSTR szToolTip, HICON icon, UINT uID)
{
    if(!IsWindow(m_hwnd))
    {
        return FALSE;
    }

    //Tray only supports tooltip text up to 64 characters
    if(_tcslen(szToolTip) > 64)
    {
        return FALSE ;
    }

    // load up the NOTIFYICONDATA structure
    memset(&m_tnd,0,sizeof(NOTIFYICONDATA));
    m_tnd.cbSize = sizeof(NOTIFYICONDATA);
    m_tnd.hWnd = m_hwnd;
    m_tnd.uID = uID;
    m_tnd.hIcon = icon;
    m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    m_tnd.uCallbackMessage = uCallbackMessage;
    lstrcpy(m_tnd.szTip, szToolTip);

    // Set the tray icon
    m_pFrame = m_hwnd ;
    m_bEnabled = Shell_NotifyIcon(NIM_ADD, &m_tnd);
    
    if (icon) 
        DestroyIcon(icon); 

    return m_bEnabled;
}

CSystemTray::~CSystemTray()
{
    RemoveIcon();
}

/////////////////////////////////////////////
// CSystemTray icon manipulation

void CSystemTray::RemoveIcon()
{
    if (!m_bEnabled) return;

    m_tnd.uFlags = 0;
    Shell_NotifyIcon(NIM_DELETE, &m_tnd);
    m_bEnabled = FALSE;
}

BOOL CSystemTray::SetIcon(UINT nIDResource)
{
    HICON hIcon = LoadIcon(hInstance,(LPCTSTR)nIDResource);

    return SetIcon(hIcon);
}

BOOL CSystemTray::SetIcon(HICON hIcon)
{
    if (!m_bEnabled) return FALSE;

    m_tnd.uFlags = NIF_ICON;
    m_tnd.hIcon = hIcon;

    return Shell_NotifyIcon(NIM_MODIFY, &m_tnd);
}
