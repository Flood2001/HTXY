/////////////////////////////////////////////////////
/// Copyright (C) 2014 Hrsoft Corporation, All rights reserved.
/// @file nm3000_app_main.c
/// @version 1.0
/// @date 2014-09-26
/// @brief nm3000程序主入口
/////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hrutil/hrutil.h>
#include <gtkutil/gtkutil.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "windows_sys.h"
#include "win_login.h"
#include "win_main_frame.h"
#include "win_show_info.h"
#include "win_show_set.h"
#include "gtk_win.h"
#include "data_calc_util.h"

#ifdef __cplusplus
extern "C"{ 
#endif

typedef struct tag_WIN_INIT_THREAD_PARAM {
    HINSTANCE hInstance ;
    HINSTANCE hPrevInstance ;
    LPTSTR    lpCmdLine ;
    int       nCmdShow ;
} WIN_INIT_THREAD_PARAM ;

DWORD WINAPI ThreadProc(LPVOID lpParam)  
{  
    WIN_INIT_THREAD_PARAM *Info = (WIN_INIT_THREAD_PARAM *)lpParam;  
    usbChange_tWinMain(Info->hInstance,
                     Info->hPrevInstance,
                     Info->lpCmdLine,
                     Info->nCmdShow);
    return 0 ;
}

void init_win(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    WIN_INIT_THREAD_PARAM Info ;
    DWORD dwThreadID ;
    Info.hInstance = hInstance ;
    Info.hPrevInstance = hPrevInstance ;
    Info.lpCmdLine = lpCmdLine ;
    Info.nCmdShow = nCmdShow ;
    CreateThread(NULL,0,ThreadProc,&Info,0,&dwThreadID);
}


///////////
// 窗体
//////
void exit_process()
{
    gtk_main_quit();
}

static void hide_all();
#define GLOBAL_WINDOW(name) \
static GtkWidget *mg_##name##Widget ; \
gboolean widget_show_##name() \
{ \
  hide_all(); \
  gtk_widget_show_all (mg_##name##Widget); \
  return FALSE ; \
} \
gboolean widget_hide_##name() \
{ \
  gtk_widget_hide(mg_##name##Widget); \
  return FALSE ; \
} \
gboolean widget_switch_##name() \
{ \
    if(mg_##name##Widget) \
    { \
        if(GTK_WIDGET_VISIBLE(mg_##name##Widget)) \
        { \
            gtk_widget_hide(mg_##name##Widget); \
        } \
        else \
        { \
            hide_all(); \
            gtk_widget_show_all(mg_##name##Widget); \
        } \
    } \
    return FALSE ; \
}

//定义窗体
GLOBAL_WINDOW(init) ///< 初始化窗口
GLOBAL_WINDOW(set) ///< 设置窗口
GLOBAL_WINDOW(info) ///< 设置窗口

static void hide_all()
{
    widget_hide_init();
    widget_hide_set();
    widget_hide_info();
}

static Cwin_show_info *mg_info_window ; ///< Info

gboolean widget_update_and_show_info()
{
    widget_show_info();
    Cwin_show_info_updata_info(mg_info_window);
    return FALSE ;
}

//////////////////
T_LANGUAGE_STRING sc_setting = {"设置","Settting"};

HTXY_GLOBAL mg_htxy_global = //{0};
{
    25,12,32,
    "",22,14};

static void init_global()
{
    mg_htxy_global.listenser_watch = 500 ;
}


static char * mg_rc[2]  ;
#ifdef _WIN32
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
#else
int main(int argc,char **argv)
#endif
{
#ifdef _WIN32
    int argc=__argc;
    char **argv = __argv ;
#endif

    GtkWidget *window;
    GtkWidget *child ;

    g_type_init();
    init_global();

    //载入程序所在目录下的gtkrc/grkrc
    {
        char path[256];
        char hrAppiface_cfg_path[256];
        hrutil_get_exe_dir(path);
        g_snprintf(hrAppiface_cfg_path,sizeof(hrAppiface_cfg_path),"%sgtkrc/gtkrc",path);
        mg_rc[0] = hrAppiface_cfg_path ;
        mg_rc[1] = NULL ;
        gtk_rc_set_default_files(mg_rc);
    }

#ifndef USE_GTK3
    g_thread_init(NULL);
#endif

    read_config();

    init_win(hInstance,hPrevInstance,lpCmdLine,nCmdShow);

    gtk_init(&argc,&argv);// --g-fatal-warnings

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    child = GTK_WIDGET(Cwin_main_frame_new());
    gtk_container_add (GTK_CONTAINER (window), GTK_WIDGET(child));
    Cwin_login_set_parent_window(WIN_LOGIN(child), GTK_WINDOW(window));
    Cwin_login_set_help_info(WIN_LOGIN(child), "abcdefg");
    gtk_window_set_title(GTK_WINDOW(window), mg_htxy_global.platform_name);
    mg_initWidget  = window ;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    child = GTK_WIDGET(Cwin_show_set_new());
    gtk_container_add (GTK_CONTAINER (window), GTK_WIDGET(child));
    Cwin_login_set_parent_window(WIN_LOGIN(child), GTK_WINDOW(window));
    Cwin_login_set_title(WIN_LOGIN(child),LOCAL_STRING(sc_setting));
    gtk_window_set_title(GTK_WINDOW(window), mg_htxy_global.platform_name);
    mg_setWidget  = window ;

    window = gtk_window_new (GTK_WINDOW_POPUP);
    child = GTK_WIDGET(Cwin_show_info_new());
    mg_info_window = (Cwin_show_info*)child;
    gtk_container_add (GTK_CONTAINER (window), GTK_WIDGET(child));
    Cwin_login_set_parent_window(WIN_LOGIN(child), GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(window), mg_htxy_global.platform_name);
    mg_infoWidget  = window ;

    gtk_main ();
    return 0 ;
}


#ifdef __cplusplus
}
#endif

