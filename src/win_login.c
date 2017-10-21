/////////////////////////////////////////////////////
/// Copyright (C) 2017 Hrsoft Corporation, All rights reserved.
/// @file win_login.c
/// @author 张洪峰
/// @version 1.0
/// @date 2017-10-15 
/// @brief 登录窗口
/////////////////////////////////////////////////////
#include <hrutil/hrutil.h>
#include "win_login.h"

#ifdef __cplusplus
extern "C" {
#endif

//#define USE_GENE_PROPERTY_CODE ///< 使用类对象属性
//#define USE_GENE_SIGNAL_CODE ///< 使用信号
//#define USE_GENE_CLASS_PRIVATE_CODE ///< 使用类静态私有对象,需要glib2.24以上版本

//////////////////////////////////////////////////
///
///  私有成员数据结构
///
///////////////////////////////////////////////////


//对象的私有数据
struct _c_win_login_private {
    GtkWidget *child_frame ;
    GtkWidget *child_table ;
    GtkWidget *label_title;
    GtkWidget *m_bt_help;
    GtkWindow *parent_window ;
};

#define  WIN_LOGIN_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj),WIN_LOGIN_TYPE,Cwin_login_private))

#ifdef USE_GENE_CLASS_PRIVATE_CODE

//类的共有私有数据
typedef struct _c_win_login_class_private {
    int pri;
}Cwin_login_class_private;

#define WIN_LOGIN_CLASS_GET_PRIVATE(klass) (G_TYPE_CLASS_GET_PRIVATE((klass),WIN_LOGIN_TYPE,Cwin_login_class_private))

#endif //USE_GENE_CLASS_PRIVATE_CODE

#ifdef USE_GENE_PROPERTY_CODE
///类属性，增加类属性的步骤：
///    1.在此处增加一个属性的ENUM，
///    2.在class_init函数中增加属性注册函数
///    3.在get_property/set_property中增加属性的读/写函数
///    4.在.h中增加说明以便用户使用
enum {
    WIN_LOGIN_CLASS_PROPERTY_0,///<不可使用
    WIN_LOGIN_CLASS_PROPERTY_NAME,
    WIN_LOGIN_CLASS_N_PROPERTYS
};
#endif

#ifdef USE_GENE_SIGNAL_CODE
/// 信号，增加信号的步骤：
///    1.在此处增加一个信号的ENUM，
///    2.在class_init函数中增加信号注册函数
///    3.在产生信号的地方使用g_signal_emit发送信号
///    4.在.h中增加说明以便用户使用
enum {
    WIN_LOGIN_SIGNAL_FIRST_SIG,
    WIN_LOGIN_SIGNAL_SIG_LAST
};
static int mg_signal[WIN_LOGIN_SIGNAL_SIG_LAST]={0};
#endif

//////////////////////////////////////////////////
///
/// 私有函数
///
///////////////////////////////////////////////////
static void Cwin_login_base_init(Cwin_loginClass *windowClass);
static void Cwin_login_base_finalize(Cwin_loginClass *windowClass);
static void Cwin_login_class_init(Cwin_loginClass *windowClass,gpointer class_data);
static void Cwin_login_class_finalize(Cwin_loginClass *windowClass,gpointer class_data);
static void Cwin_login_inst_init(Cwin_login *window);
static void Cwin_login_inst_finalize(Cwin_login *window);
static void Cwin_login_inst_dispose(Cwin_login *window);

#ifdef USE_GENE_PROPERTY_CODE
static void Cwin_login_set_property(GObject *object,
        guint  property_id,
        const GValue *value,
        GParamSpec  *pspec);
static void Cwin_login_get_property(GObject *object,
        guint  property_id,
        GValue *value,
        GParamSpec *pspec);
#endif

void slog_bt_min_clicked(GtkButton *button, gpointer   user_data) ;
void slog_bt_clicked_help(GtkButton *button, gpointer   user_data) ;

//////////////////////////////////////////////////
///
///  类基本函数实现
///
///////////////////////////////////////////////////

//生成对象类的ID标识
GType Cwin_login_type(void)
{
    static GType window_type=0;
    if(!window_type)
    {
        static const GTypeInfo window_info = {
            sizeof(Cwin_loginClass),
            (GBaseInitFunc)Cwin_login_base_init,
            (GBaseFinalizeFunc)Cwin_login_base_finalize,

            (GClassInitFunc)Cwin_login_class_init,
            NULL,

            //(GClassFinalizeFunc)Cwin_login_class_finalize,
            NULL,

            sizeof(Cwin_login),0,
            (GInstanceInitFunc)Cwin_login_inst_init
        };
        window_type = g_type_register_static(GTK_GRID_TABLE_TYPE,"Cwin_login",&window_info,0);

#ifdef USE_GENE_CLASS_PRIVATE_CODE
        g_type_add_class_private(window_type,sizeof(Cwin_login_class_private));
#endif
    }
    return window_type;
}

static void Cwin_login_base_init(Cwin_loginClass *windowClass)
{
    UNUSED_VAR(windowClass);
}
static void Cwin_login_base_finalize(Cwin_loginClass *windowClass)
{
    UNUSED_VAR(windowClass);
}

//类构造函数
static void Cwin_login_class_init(Cwin_loginClass *windowClass,gpointer class_data)
{
    GObjectClass *base_class = G_OBJECT_CLASS(windowClass);
#ifdef USE_GENE_PROPERTY_CODE
    GParamSpec *property = NULL ;
#endif
#ifdef USE_GENE_CLASS_PRIVATE_CODE
    Cwin_login_class_private *p = WIN_LOGIN_CLASS_GET_PRIVATE(windowClass);
#endif

    UNUSED_VAR(class_data);

    //加入对象私有数据
    g_type_class_add_private(windowClass,sizeof(Cwin_login_private));
    //初始化类函数
    base_class->dispose = (void(*)(GObject *object))Cwin_login_inst_dispose ;
    base_class->finalize = (void(*)(GObject *object))Cwin_login_inst_finalize;

#ifdef USE_GENE_PROPERTY_CODE
    base_class->set_property = Cwin_login_set_property;
    base_class->get_property = Cwin_login_get_property;

    //注册属性
    property = g_param_spec_string("name","Name","The Attr Name",NULL,G_PARAM_READWRITE);
    g_object_class_install_property(base_class,WIN_LOGIN_CLASS_PROPERTY_NAME,property);
#endif

#ifdef USE_GENE_SIGNAL_CODE
    //注册信号
    mg_signal[WIN_LOGIN_SIGNAL_FIRST_SIG] = g_signal_new("first_sig",
            G_TYPE_FROM_CLASS(windowClass),
            G_SIGNAL_RUN_FIRST,
            0,NULL,NULL,g_cclosure_marshal_VOID__VOID,
            G_TYPE_NONE,0,NULL);
    //当要产生信号时，使用 g_signal_emit(G_OBJECT(window), mg_signal[WIN_LOGIN_SIGNAL_FIRST_SIG], 0);发送信号
#endif
}

//类析构函数
static void Cwin_login_class_finalize(Cwin_loginClass *windowClass,gpointer class_data)
{
    UNUSED_VAR(windowClass);
    UNUSED_VAR(class_data);
}

//对象构造函数
static void Cwin_login_inst_init(Cwin_login *window)
{
    GtkWidget *hbox_bar ;   ///< 工具栏
    Cfunc_button* bt_min ;  ///< 左侧Info
    GtkWidget *img_info ;    ///< 右侧最小化
    GtkWidget *label ;
    GtkWidget *hbox_down ;   ///< 帮助栏
    char path[256];
    char exe_path[256];
    GtkWidget *top_frame ;
    GtkWidget *top_table ;

    window->prv = WIN_LOGIN_GET_PRIVATE(window);

    hrutil_get_exe_dir(exe_path);
    g_snprintf(path,sizeof(path),"%simage/info.png",exe_path);
    hbox_bar = gtk_hbox_new(FALSE,0);
    bt_min = Cfunc_button_new();
    img_info = gtk_image_new_from_file(path);
    gtk_widget_set_usize(GTK_WIDGET(img_info),64,64);

    g_snprintf(path,sizeof(path),"%simage/minimize.png",exe_path);
    Cfunc_button_set_image_and_text(bt_min,path,NULL,32,32);
    g_signal_connect(G_OBJECT(bt_min),"clicked",G_CALLBACK(slog_bt_min_clicked),window);
    gtk_widget_set_can_focus(GTK_WIDGET(bt_min),FALSE);
    gtk_box_pack_start(GTK_BOX(hbox_bar),GTK_WIDGET(img_info),FALSE,FALSE,0);
    window->prv->label_title = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(hbox_bar),window->prv->label_title,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox_bar),GTK_WIDGET(bt_min),FALSE,FALSE,0);


    window->prv->child_frame = gtk_frame_new(NULL);
    window->prv->child_table = GTK_WIDGET(Cgtk_grid_table_new());
    gtk_container_add(GTK_CONTAINER(window->prv->child_frame),GTK_WIDGET(window->prv->child_table));

    hbox_down = gtk_hbox_new(FALSE,0);
    window->prv->m_bt_help = GTK_WIDGET(Cfunc_button_new());
    gtk_widget_set_can_focus(GTK_WIDGET(window->prv->m_bt_help),FALSE);
    g_snprintf(path,sizeof(path),"%simage/help.png",exe_path);
    Cfunc_button_set_image_and_text((Cfunc_button*)window->prv->m_bt_help ,path,NULL,32,32);
    g_signal_connect(G_OBJECT(window->prv->m_bt_help),"clicked",G_CALLBACK(slog_bt_clicked_help),window);
    label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(hbox_down),GTK_WIDGET(label),TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox_down),GTK_WIDGET(window->prv->m_bt_help),FALSE,FALSE,0);

    top_frame = gtk_frame_new(NULL);
    top_table = GTK_WIDGET(Cgtk_grid_table_new());
    gtk_container_add(GTK_CONTAINER(top_frame),top_table);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(window),GTK_WIDGET(top_frame),
        0,0,1,1, TRUE , TRUE , TRUE ,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(top_table),GTK_WIDGET(hbox_bar),
        0,0,1,1, TRUE , FALSE , TRUE ,FALSE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(top_table),GTK_WIDGET(window->prv->child_frame),
        0,1,1,1, TRUE , TRUE , TRUE ,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(top_table),GTK_WIDGET(hbox_down),
        0,2,1,1, TRUE , FALSE , TRUE ,FALSE);
}
//对象析构函数
static void Cwin_login_inst_finalize(Cwin_login *window)
{
    G_OBJECT_CLASS(g_type_class_peek(g_type_parent(g_type_from_name("Cwin_login"))))->finalize(G_OBJECT(window));
}
//对象释放函数
static void Cwin_login_inst_dispose(Cwin_login *window)
{
    G_OBJECT_CLASS(g_type_class_peek(g_type_parent(g_type_from_name("Cwin_login"))))->dispose(G_OBJECT(window));
}

#ifdef USE_GENE_PROPERTY_CODE
static void Cwin_login_set_property(GObject *object,
        guint  property_id,
        const GValue *value,
        GParamSpec *pspec)
{
    Cwin_login *window = WIN_LOGIN(object);

    UNUSED_VAR(window);

    switch(property_id)
    {
        case WIN_LOGIN_CLASS_PROPERTY_NAME:
            //加入设置name到value的代码
            break ;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,pspec);
            break;
    }
}
static void Cwin_login_get_property(GObject  *object,
        guint property_id,
        GValue *value,
        GParamSpec *pspec)
{
    Cwin_login *window = WIN_LOGIN(object);

    UNUSED_VAR(window);

    switch(property_id)
    {
        case WIN_LOGIN_CLASS_PROPERTY_NAME:
            //加入设置value到name的代码
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,pspec);
            break;
    }
}
#endif

//////////////////////////////////////////////////
///
///  公有函数实现
///
///////////////////////////////////////////////////

//新建类对象
Cwin_login* Cwin_login_new(void)
{
    Cwin_login* window;
    window = (Cwin_login*)g_object_new(WIN_LOGIN_TYPE,NULL);

    return window;
}

void Cwin_login_set_parent_window(Cwin_login *window , GtkWindow *parent_window)
{
    gtk_window_set_position(GTK_WINDOW(parent_window),GTK_WIN_POS_CENTER);
    gtk_window_set_decorated(GTK_WINDOW(parent_window),FALSE);
    gtk_widget_show_all(GTK_WIDGET(parent_window));
    gtk_widget_hide(GTK_WIDGET(parent_window));
    window->prv->parent_window = parent_window ;
}

void Cwin_login_set_title(Cwin_login *window , const char* title)
{
    gtk_label_set_text(GTK_LABEL(window->prv->label_title),title);
}

void Cwin_login_set_help_info(Cwin_login *window,const char* help_info)
{
    gtk_widget_set_tooltip_text(GTK_WIDGET(window->prv->m_bt_help),help_info);
    gtk_widget_set_tooltip_markup(GTK_WIDGET(window->prv->m_bt_help),help_info);
}

void Cwin_login_set_child(Cwin_login *window , GtkWidget *child)
{
    Cwin_login_clean_child(window);
    window->prv->child_table = child ;
    gtk_container_add(GTK_CONTAINER(window->prv->child_frame),GTK_WIDGET(window->prv->child_table));
    gtk_widget_show_all(GTK_WIDGET(window));
}

void Cwin_login_clean_child(Cwin_login *window)
{
    if(window->prv->child_table != NULL)
    {
        gtk_container_remove(GTK_CONTAINER(window->prv->child_frame),window->prv->child_table);
    }
}

//////////////////////////////////////////////////
///
///  私有函数实现
///
///////////////////////////////////////////////////

void slog_bt_min_clicked(GtkButton *button, gpointer   user_data) 
{
    Cwin_login *window = (Cwin_login*)user_data ;

    if(window->prv->parent_window)
    {
        gtk_widget_hide(GTK_WIDGET(window->prv->parent_window));
    }
}

void slog_bt_clicked_help(GtkButton *button, gpointer   user_data) 
{
    Cwin_login *window = (Cwin_login*)user_data ;

    update_organs_db();
}

#ifdef __cplusplus
}
#endif

