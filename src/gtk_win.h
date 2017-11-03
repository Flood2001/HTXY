#ifndef _HRSOFT_GTK_WIN_H_2017_10_15_
#define _HRSOFT_GTK_WIN_H_2017_10_15_

#include <gtk/gtk.h>
#include "data_calc_util.h"

#ifdef __cplusplus
extern "C"{
#endif

#define TYPE_URL_MAX_LEN 1024
#define TYPE_URL_MAX_API_COUNT 10
/// ȫ��
typedef struct tag_htxy_global_api_item {
    char name[TYPE_URL_MAX_LEN] ; 
    char type[TYPE_URL_MAX_LEN] ; 
    char url[TYPE_URL_MAX_LEN] ; 
} API_ITEM ;

typedef struct tag_htxy_global {
    char exe_dir[TYPE_URL_MAX_LEN];
    //��¼��Ϣ
    char organId[TYPE_URL_MAX_LEN];
    char session[TYPE_URL_MAX_LEN];

    // ͳ����Ϣ
    int stat_organs_all ;
    int stat_person_all ;
    int stat_organs_shishi ;
    int stat_person_shishi ;

    // ��ǰInfo
    char info_findKey[1024];    ///< ���ҵ��ַ���
    char info_name[1024];   ///< ��ʾ�ַ���
    int info_jiangli ;
    int info_chengjie ;

    //���а�
    char clipboard_text[TYPE_URL_MAX_LEN];

    //�����ļ�
    int listenser_delay ;
    int listenser_watch ;
    gboolean listenser_isync ;
    gboolean is_use_organs ;    ///< �Ƿ�ʹ�÷��˿�
    gboolean is_use_person ;    ///< �Ƿ�ʹ����Ȼ�˿�

    //�ӿ�����
    API_ITEM api[TYPE_URL_MAX_API_COUNT] ;
    char platform_type[TYPE_URL_MAX_LEN] ;
    char platform_name[TYPE_URL_MAX_LEN] ;
    char platform_url[TYPE_URL_MAX_LEN] ;
    char platform_web[TYPE_URL_MAX_LEN] ;

    // �û���Ϣ
    gboolean userinfo_status ;
    char userinfo_dept[TYPE_URL_MAX_LEN] ;
    char userinfo_user[TYPE_URL_MAX_LEN] ;
    char userinfo_token[TYPE_URL_MAX_LEN] ;
    char userinfo_deptId[TYPE_URL_MAX_LEN] ;
    char userinfo_userId[TYPE_URL_MAX_LEN] ;

} HTXY_GLOBAL ;

/// ����
extern GtkWidget *mg_initWidget ;
extern GtkWidget *mg_setWidget ;
extern GtkWidget *mg_infoWidget ;
extern GtkWidget *mg_listWidget ;
extern GtkWidget *mg_shishiWidget ;

void exit_process();
gboolean widget_update_init();
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
gboolean widget_show_list_window_with_type(int type);
gboolean widget_show_shishi_organs(DB_ORGANS_ITEM *item , JC_INFO *info);
void gtk_show_msg_dlg(int title_string_id,int context_string_id);

extern HTXY_GLOBAL mg_htxy_global ;

#define RUN_GTK_FUNC(func) gtk_idle_add((GtkFunction)func,NULL);

#ifdef __cplusplus
}
#endif

#endif // _HRSOFT_GTK_WIN_H_2017_10_15_

