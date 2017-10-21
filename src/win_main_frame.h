#ifndef _HRSOFT_WIN_MAIN_FRAME_H_2017_10_18_
#define _HRSOFT_WIN_MAIN_FRAME_H_2017_10_18_

#include <glib.h>
#include <glib-object.h>
#include "win_login.h"

#ifdef __cplusplus
extern "C" {
#endif

//����ת����
#define WIN_MAIN_FRAME_TYPE (Cwin_main_frame_type())
#define WIN_MAIN_FRAME(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),WIN_MAIN_FRAME_TYPE,Cwin_main_frame))
#define WIN_MAIN_FRAME_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), WIN_MAIN_FRAME_TYPE, Cwin_main_framecim_attrClass))
#define WIN_MAIN_FRAME_IS_OBJECT(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj),WIN_MAIN_FRAME_TYPE,Cwin_main_frameClass))
#define WIN_MAIN_FRAME_IS_OBJECT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),WIN_MAIN_FRAME_TYPE))
#define WIN_MAIN_FRAME_OBJECT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj),WIN_MAIN_FRAME_TYPE,Cwin_main_frameClass))

//�����������
typedef struct _c_win_main_frame Cwin_main_frame;
typedef struct _c_win_main_frame_Class Cwin_main_frameClass;
typedef struct _c_win_main_frame_private Cwin_main_frame_private;

//��ṹ����
struct _c_win_main_frame {
    Cwin_login parent;

    Cwin_main_frame_private *prv;   ///<˽�г�Ա
};

//�������ṹ�����д����͵Ķ�����
struct _c_win_main_frame_Class {
    Cwin_loginClass parent_class;
};

//�Ա���Ĺ��ò�������
GType Cwin_main_frame_type(void);
Cwin_main_frame* Cwin_main_frame_new(void);

#ifdef __cplusplus
}
#endif

#endif // _HRSOFT_WIN_MAIN_FRAME_H_2017_10_18_

