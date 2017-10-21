#ifndef _HRSOFT_WINDOWS_SYS_H_2017_10_15_
#define _HRSOFT_WINDOWS_SYS_H_2017_10_15_

#ifdef __cplusplus
extern "C"{
#endif

//////////////////////////////
//  
// ×Ö·û×ª»»Ïà¹Ø
//
/////////////////////////////

#ifdef UNICODE  
#define CHAR2TCHAR(c,tc,tc_len) MultiByteToWideChar(CP_ACP, 0, c, -1, tc, tc_len);  
#else  
#define CHAR2TCHAR(c,tc,tc_len) strcpy(tc, c);  
#endif  

int APIENTRY usbChange_tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow);

#ifdef __cplusplus
}
#endif

#endif // _HRSOFT_WINDOWS_SYS_H_2017_10_15_

