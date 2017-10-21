
#ifndef _INCLUDED_SYSTEMTRAY_H_
#define _INCLUDED_SYSTEMTRAY_H_

#include <Windows.h>
#include "Shellapi.h"

/////////////////////////////////////////////////////////////////////////////
// CSystemTray window

class CSystemTray
{
// Construction/destruction
public:
	CSystemTray();
	CSystemTray(HWND m_hwnd, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID);
	virtual ~CSystemTray();

// Operations
public:
	BOOL Enabled() { return m_bEnabled; }
	BOOL Visible() { return !m_bHidden; }

	//Create the tray icon
	BOOL Create(HWND m_hwnd, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID);

	//Change or retrieve the icon displayed
	BOOL SetIcon(HICON hIcon);
	BOOL SetIcon(UINT nIDResource);


// Overrides
// ClassWizard generated virtual function overrides
//{{AFX_VIRTUAL(CSystemTray)
//}}AFX_VIRTUAL

// Implementation
protected:
	HWND m_pFrame;
	BOOL m_bEnabled; // does O/S support tray icon?
	BOOL m_bHidden; // Has the icon been hidden?
	NOTIFYICONDATA m_tnd;

    //DECLARE_DYNAMIC(CSystemTray)

public:
    HINSTANCE hInstance;
	void RemoveIcon();

};


#endif
