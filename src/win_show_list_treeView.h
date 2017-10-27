#ifndef _HRSOFT_WIN_SHOW_LIST_H_2017_10_26_
#define _HRSOFT_WIN_SHOW_LIST_H_2017_10_26_

#include <glib.h>
#include <glib-object.h>
#include "win_login.h"

#ifdef __cplusplus
extern "C" {
#endif

//����ת����
#define WIN_SHOW_LIST_TYPE (Cwin_show_list_type())
#define WIN_SHOW_LIST(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),WIN_SHOW_LIST_TYPE,Cwin_show_list))
#define WIN_SHOW_LIST_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), WIN_SHOW_LIST_TYPE, Cwin_show_listcim_attrClass))
#define WIN_SHOW_LIST_IS_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj),WIN_SHOW_LIST_TYPE,Cwin_show_listClass))
#define WIN_SHOW_LIST_IS_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),WIN_SHOW_LIST_TYPE))
#define WIN_SHOW_LIST_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj),WIN_SHOW_LIST_TYPE,Cwin_show_listClass))

//�����������
typedef struct _c_win_show_list Cwin_show_list;
typedef struct _c_win_show_list_Class Cwin_show_listClass;
typedef struct _c_win_show_list_private Cwin_show_list_private;

//��ṹ����
struct _c_win_show_list {
    Cwin_login parent;

    Cwin_show_list_private *prv;   ///<˽�г�Ա
};

//�������ṹ�����д����͵Ķ�����
struct _c_win_show_list_Class {
    Cwin_loginClass parent_class;
};

//�Ա���Ĺ��ò�������
GType Cwin_show_list_type(void);
Cwin_show_list* Cwin_show_list_new(void);
/// TYPE 1 ,2 , 3 , 4, �ֱ�Ϊ ���˺�ڡ�ʵʩ����Ȼ�˺�ڡ�ʵʩ
void Cwin_show_list_set_show_type(Cwin_show_list *window ,int type);

#ifdef __cplusplus
}
#endif

#endif // _HRSOFT_WIN_SHOW_LIST_H_2017_10_26_

