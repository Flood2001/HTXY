#ifndef _HRSOFT_WIN_SHOW_SHISHI_H_2017_10_18_
#define _HRSOFT_WIN_SHOW_SHISHI_H_2017_10_18_

#include <glib.h>
#include <glib-object.h>
#include "win_login.h"

#ifdef __cplusplus
extern "C" {
#endif

//����ת����
#define WIN_SHOW_SHISHI_TYPE (Cwin_show_shishi_type())
#define WIN_SHOW_SHISHI(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),WIN_SHOW_SHISHI_TYPE,Cwin_show_shishi))
#define WIN_SHOW_SHISHI_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), WIN_SHOW_SHISHI_TYPE, Cwin_show_shishicim_attrClass))
#define WIN_SHOW_SHISHI_IS_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj),WIN_SHOW_SHISHI_TYPE,Cwin_show_shishiClass))
#define WIN_SHOW_SHISHI_IS_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),WIN_SHOW_SHISHI_TYPE))
#define WIN_SHOW_SHISHI_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj),WIN_SHOW_SHISHI_TYPE,Cwin_show_shishiClass))

//�����������
typedef struct _c_win_show_shishi Cwin_show_shishi;
typedef struct _c_win_show_shishi_Class Cwin_show_shishiClass;
typedef struct _c_win_show_shishi_private Cwin_show_shishi_private;

//��ṹ����
struct _c_win_show_shishi {
    Cwin_login parent;

    Cwin_show_shishi_private *prv;   ///<˽�г�Ա
};

//�������ṹ�����д����͵Ķ�����
struct _c_win_show_shishi_Class {
    Cwin_loginClass parent_class;
};

//�Ա���Ĺ��ò�������
GType Cwin_show_shishi_type(void);
Cwin_show_shishi* Cwin_show_shishi_new(void);
void Cwin_show_shishi_set_organs_data(Cwin_show_shishi *window ,DB_ORGANS_ITEM *item , JC_INFO *info);

#ifdef __cplusplus
}
#endif

#endif // _HRSOFT_WIN_SHOW_SHISHI_H_2017_10_18_

