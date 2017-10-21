#ifndef _HRSOFT_WIN_SHOW_INFO_H_2017_10_18_
#define _HRSOFT_WIN_SHOW_INFO_H_2017_10_18_

#include <glib.h>
#include <glib-object.h>
#include "win_login.h"

#ifdef __cplusplus
extern "C" {
#endif

//类型转换宏
#define WIN_SHOW_INFO_TYPE (Cwin_show_info_type())
#define WIN_SHOW_INFO(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),WIN_SHOW_INFO_TYPE,Cwin_show_info))
#define WIN_SHOW_INFO_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), WIN_SHOW_INFO_TYPE, Cwin_show_infocim_attrClass))
#define WIN_SHOW_INFO_IS_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj),WIN_SHOW_INFO_TYPE,Cwin_show_infoClass))
#define WIN_SHOW_INFO_IS_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),WIN_SHOW_INFO_TYPE))
#define WIN_SHOW_INFO_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj),WIN_SHOW_INFO_TYPE,Cwin_show_infoClass))

//窗口类的声明
typedef struct _c_win_show_info Cwin_show_info;
typedef struct _c_win_show_info_Class Cwin_show_infoClass;
typedef struct _c_win_show_info_private Cwin_show_info_private;

//类结构声明
struct _c_win_show_info {
    Cwin_login parent;

    Cwin_show_info_private *prv;   ///<私有成员
};

//对象的类结构，所有此类型的对象共用
struct _c_win_show_info_Class {
    Cwin_loginClass parent_class;
};

//对本类的公用操作函数
GType Cwin_show_info_type(void);
Cwin_show_info* Cwin_show_info_new(void);
void Cwin_show_info_updata_info(Cwin_show_info *window);

#ifdef __cplusplus
}
#endif

#endif // _HRSOFT_WIN_SHOW_INFO_H_2017_10_18_

