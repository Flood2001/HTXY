#ifndef _HRSOFT_WIN_LOGIN_H_2017_10_15_
#define _HRSOFT_WIN_LOGIN_H_2017_10_15_

#include <glib.h>
#include <glib-object.h>
#include <gtkutil/gtkutil.h>

#ifdef __cplusplus
extern "C" {
#endif

//����ת����
#define WIN_LOGIN_TYPE (Cwin_login_type())
#define WIN_LOGIN(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),WIN_LOGIN_TYPE,Cwin_login))
#define WIN_LOGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), WIN_LOGIN_TYPE, Cwin_logincim_attrClass))
#define WIN_LOGIN_IS_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj),WIN_LOGIN_TYPE,Cwin_loginClass))
#define WIN_LOGIN_IS_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),WIN_LOGIN_TYPE))
#define WIN_LOGIN_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj),WIN_LOGIN_TYPE,Cwin_loginClass))

//�����������
typedef struct _c_win_login Cwin_login;
typedef struct _c_win_login_Class Cwin_loginClass;
typedef struct _c_win_login_private Cwin_login_private;

//��ṹ����
struct _c_win_login {
    Cgtk_grid_table parent;

    Cwin_login_private *prv;   ///<˽�г�Ա
};

//�������ṹ�����д����͵Ķ�����
struct _c_win_login_Class {
    Cgtk_grid_tableClass parent_class;
};

//�Ա���Ĺ��ò�������
GType Cwin_login_type(void);
Cwin_login* Cwin_login_new(void);
void Cwin_login_set_parent_window(Cwin_login *window , GtkWindow *parent_window);
void Cwin_login_set_title(Cwin_login *window , const char* title);
void Cwin_login_set_help_info(Cwin_login *window,const char* help_info);
void Cwin_login_set_child(Cwin_login *window , GtkWidget *child);
void Cwin_login_clean_child(Cwin_login *window);
void Cwin_login_set_min_window(Cwin_login *window,Cwin_login *min); ///< ���õ���С��ʱ��ʾ�Ĵ���
void Cwin_login_do_min_window(Cwin_login *window);

#ifdef __cplusplus
}
#endif

#endif // _HRSOFT_WIN_LOGIN_H_2017_10_15_

