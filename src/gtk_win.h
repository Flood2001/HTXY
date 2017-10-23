#ifndef _HRSOFT_GTK_WIN_H_2017_10_15_
#define _HRSOFT_GTK_WIN_H_2017_10_15_

#include <gtk/gtk.h>

#ifdef __cplusplus
extern "C"{
#endif

#define TYPE_URL_MAX_LEN 1024
/// 全局
typedef struct tag_htxy_global {
    //登录信息
    char organId[TYPE_URL_MAX_LEN];
    char session[TYPE_URL_MAX_LEN];

    // 统计信息
    int stat_chengjie ;
    int stat_faren ;
    int stat_ziranren ;

    // 当前Info
    char info_name[1024];
    int info_jiangli ;
    int info_chengjie ;

    //剪切板
    char clipboard_text[TYPE_URL_MAX_LEN];

    //配置文件
    int listenser_delay ;
    int listenser_watch ;
    gboolean listenser_isync ;
    char listenser_last_sync_time[TYPE_URL_MAX_LEN] ;

    char platform_api_login_type[TYPE_URL_MAX_LEN] ;
    char platform_api_login_url[TYPE_URL_MAX_LEN] ;
    char platform_api_roster_type[TYPE_URL_MAX_LEN] ;
    char platform_api_roster_url[TYPE_URL_MAX_LEN] ;
    char platform_api_count_type[TYPE_URL_MAX_LEN] ;
    char platform_api_count_url[TYPE_URL_MAX_LEN] ;
    char platform_api_context_type[TYPE_URL_MAX_LEN] ;
    char platform_api_context_url[TYPE_URL_MAX_LEN] ;
    char platform_type[TYPE_URL_MAX_LEN] ;
    char platform_name[TYPE_URL_MAX_LEN] ;
    char platform_url[TYPE_URL_MAX_LEN] ;
    char platform_web[TYPE_URL_MAX_LEN] ;
} HTXY_GLOBAL ;

void exit_process();
gboolean widget_show_init();
gboolean widget_hide_init();
gboolean widget_switch_init();
gboolean widget_show_set();
gboolean widget_hide_set();
gboolean widget_switch_set();
gboolean widget_show_info();
gboolean widget_hide_info();
gboolean widget_switch_info();
gboolean widget_update_and_show_info();

extern HTXY_GLOBAL mg_htxy_global ;

#define RUN_GTK_FUNC(func) gtk_idle_add((GtkFunction)func,NULL);

#ifdef __cplusplus
}
#endif

#endif // _HRSOFT_GTK_WIN_H_2017_10_15_

