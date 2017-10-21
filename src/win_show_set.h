#ifndef _HRSOFT_WIN_SHOW_SET_H_2017_10_18_
#define _HRSOFT_WIN_SHOW_SET_H_2017_10_18_

#include <glib.h>
#include <glib-object.h>
#include "win_login.h"

#ifdef __cplusplus
extern "C" {
#endif

//类型转换宏
#define WIN_SHOW_SET_TYPE (Cwin_show_set_type())
#define WIN_SHOW_SET(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),WIN_SHOW_SET_TYPE,Cwin_show_set))
#define WIN_SHOW_SET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), WIN_SHOW_SET_TYPE, Cwin_show_setcim_attrClass))
#define WIN_SHOW_SET_IS_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj),WIN_SHOW_SET_TYPE,Cwin_show_setClass))
#define WIN_SHOW_SET_IS_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),WIN_SHOW_SET_TYPE))
#define WIN_SHOW_SET_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj),WIN_SHOW_SET_TYPE,Cwin_show_setClass))

//窗口类的声明
typedef struct _c_win_show_set Cwin_show_set;
typedef struct _c_win_show_set_Class Cwin_show_setClass;
typedef struct _c_win_show_set_private Cwin_show_set_private;

//类结构声明
struct _c_win_show_set {
    Cwin_login parent;

    Cwin_show_set_private *prv;   ///<私有成员
};

//对象的类结构，所有此类型的对象共用
struct _c_win_show_set_Class {
    Cwin_loginClass parent_class;
};

//对本类的公用操作函数
GType Cwin_show_set_type(void);
Cwin_show_set* Cwin_show_set_new(void);

#ifdef __cplusplus
}
#endif

#endif // _HRSOFT_WIN_SHOW_SET_H_2017_10_18_

