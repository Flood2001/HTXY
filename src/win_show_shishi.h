#ifndef _HRSOFT_WIN_SHOW_SHISHI_H_2017_10_18_
#define _HRSOFT_WIN_SHOW_SHISHI_H_2017_10_18_

#include <glib.h>
#include <glib-object.h>
#include "win_login.h"

#ifdef __cplusplus
extern "C" {
#endif

//类型转换宏
#define WIN_SHOW_SHISHI_TYPE (Cwin_show_shishi_type())
#define WIN_SHOW_SHISHI(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),WIN_SHOW_SHISHI_TYPE,Cwin_show_shishi))
#define WIN_SHOW_SHISHI_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), WIN_SHOW_SHISHI_TYPE, Cwin_show_shishicim_attrClass))
#define WIN_SHOW_SHISHI_IS_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj),WIN_SHOW_SHISHI_TYPE,Cwin_show_shishiClass))
#define WIN_SHOW_SHISHI_IS_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),WIN_SHOW_SHISHI_TYPE))
#define WIN_SHOW_SHISHI_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj),WIN_SHOW_SHISHI_TYPE,Cwin_show_shishiClass))

//窗口类的声明
typedef struct _c_win_show_shishi Cwin_show_shishi;
typedef struct _c_win_show_shishi_Class Cwin_show_shishiClass;
typedef struct _c_win_show_shishi_private Cwin_show_shishi_private;

//类结构声明
struct _c_win_show_shishi {
    Cwin_login parent;

    Cwin_show_shishi_private *prv;   ///<私有成员
};

//对象的类结构，所有此类型的对象共用
struct _c_win_show_shishi_Class {
    Cwin_loginClass parent_class;
};

//对本类的公用操作函数
GType Cwin_show_shishi_type(void);
Cwin_show_shishi* Cwin_show_shishi_new(void);
void Cwin_show_shishi_set_organs_data(Cwin_show_shishi *window ,DB_ORGANS_ITEM *item , JC_INFO *info);

#ifdef __cplusplus
}
#endif

#endif // _HRSOFT_WIN_SHOW_SHISHI_H_2017_10_18_

