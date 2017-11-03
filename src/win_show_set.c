////////////////////////////////////////////////////
/// Copyright (C) 2017 Hrsoft Corporation, All rights reserved.
/// @file win_show_set.c
/// @author 张洪峰
/// @version 1.0
/// @date 2017-10-18 
/// @brief 
/// @note 
/////////////////////////////////////////////////////
#include <hrutil/hrutil.h>
#include "win_show_set.h"
#include "gtk_win.h"
#include "data_calc_util.h"

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

/// 列表树
enum {
    COL_POINTER ,  ///< API_ITEM *
    COL_INDEX ,

    COL_NUMS ,
};
//对象的私有数据
struct _c_win_show_set_private {
    gboolean m_is_login ;
    //用户
    GtkWidget *m_user_child_frame;
    GtkWidget *m_user_child_table;
    //登录界面
    GtkWidget *m_en_usrname ;
    GtkWidget *m_en_password ;
    GtkWidget *m_label_error_str ;
    //登录成功
    GtkWidget *m_en_dept ;
    GtkWidget *m_en_user ;

    //应用
    GtkWidget *m_en_url ;
    GtkWidget *m_en_web ;
    GtkWidget *m_en_app_name;
    GtkWidget *m_ck_auto_sync ;
    GtkWidget *m_ck_faren ;
    GtkWidget *m_ck_ziranren ;
    GtkWidget *m_en_delay ;

    //接口管理
    GtkTreeView  *m_treeView ;          ///< 接口树
    GtkTreeStore *m_treeStore ;
};

#define  WIN_SHOW_SET_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj),WIN_SHOW_SET_TYPE,Cwin_show_set_private))

#ifdef USE_GENE_CLASS_PRIVATE_CODE

//类的共有私有数据
typedef struct _c_win_show_set_class_private {
    int pri;
}Cwin_show_set_class_private;

#define WIN_SHOW_SET_CLASS_GET_PRIVATE(klass) (G_TYPE_CLASS_GET_PRIVATE((klass),WIN_SHOW_SET_TYPE,Cwin_show_set_class_private))

#endif //USE_GENE_CLASS_PRIVATE_CODE

#ifdef USE_GENE_PROPERTY_CODE
///类属性，增加类属性的步骤：
///    1.在此处增加一个属性的ENUM，
///    2.在class_init函数中增加属性注册函数
///    3.在get_property/set_property中增加属性的读/写函数
///    4.在.h中增加说明以便用户使用
enum {
    WIN_SHOW_SET_CLASS_PROPERTY_0,///<不可使用
    WIN_SHOW_SET_CLASS_PROPERTY_NAME,
    WIN_SHOW_SET_CLASS_N_PROPERTYS
};
#endif

#ifdef USE_GENE_SIGNAL_CODE
/// 信号，增加信号的步骤：
///    1.在此处增加一个信号的ENUM，
///    2.在class_init函数中增加信号注册函数
///    3.在产生信号的地方使用g_signal_emit发送信号
///    4.在.h中增加说明以便用户使用
enum {
    WIN_SHOW_SET_SIGNAL_FIRST_SIG,
    WIN_SHOW_SET_SIGNAL_SIG_LAST
};
static int mg_signal[WIN_SHOW_SET_SIGNAL_SIG_LAST]={0};
#endif

//////////////////////////////////////////////////
///
/// 私有函数
///
///////////////////////////////////////////////////
static void Cwin_show_set_base_init(Cwin_show_setClass *windowClass);
static void Cwin_show_set_base_finalize(Cwin_show_setClass *windowClass);
static void Cwin_show_set_class_init(Cwin_show_setClass *windowClass,gpointer class_data);
static void Cwin_show_set_class_finalize(Cwin_show_setClass *windowClass,gpointer class_data);
static void Cwin_show_set_inst_init(Cwin_show_set *window);
static void Cwin_show_set_inst_finalize(Cwin_show_set *window);
static void Cwin_show_set_inst_dispose(Cwin_show_set *window);

#ifdef USE_GENE_PROPERTY_CODE
static void Cwin_show_set_set_property(GObject *object,
        guint  property_id,
        const GValue *value,
        GParamSpec  *pspec);
static void Cwin_show_set_get_property(GObject *object,
        guint  property_id,
        GValue *value,
        GParamSpec *pspec);
#endif

static void slog_bt_update_utl(GtkButton *button, gpointer   user_data) ;
static void slog_bt_clicked_liji(GtkButton *button, gpointer   user_data) ;
static void slog_bt_clicked_update(GtkButton *button, gpointer   user_data) ;
static void slog_bt_clicked_update_cfg(GtkButton *button, gpointer   user_data) ;
static gboolean slog_main_book_change_page(GtkNotebook *notebook,
          gint         arg1, gpointer     user_data);
static void slog_bt_login(GtkButton *button, gpointer   user_data) ;
static void slog_bt_relogin(GtkButton *button, gpointer   user_data) ;

static void no_cell_data_func (GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data);
static void name_cell_data_func (GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data);
static void url_cell_data_func (GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data);
static void type_cell_data_func (GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data);
//////////////////////////////////////////////////
///
///  类基本函数实现
///
///////////////////////////////////////////////////

//生成对象类的ID标识
GType Cwin_show_set_type(void)
{
    static GType window_type=0;
    if(!window_type)
    {
        static const GTypeInfo window_info = {
            sizeof(Cwin_show_setClass),
            (GBaseInitFunc)Cwin_show_set_base_init,
            (GBaseFinalizeFunc)Cwin_show_set_base_finalize,

            (GClassInitFunc)Cwin_show_set_class_init,
            NULL,

            //(GClassFinalizeFunc)Cwin_show_set_class_finalize,
            NULL,

            sizeof(Cwin_show_set),0,
            (GInstanceInitFunc)Cwin_show_set_inst_init
        };
        window_type = g_type_register_static(WIN_LOGIN_TYPE,"Cwin_show_set",&window_info,0);

#ifdef USE_GENE_CLASS_PRIVATE_CODE
        g_type_add_class_private(window_type,sizeof(Cwin_show_set_class_private));
#endif
    }
    return window_type;
}

static void Cwin_show_set_base_init(Cwin_show_setClass *windowClass)
{
    UNUSED_VAR(windowClass);
}
static void Cwin_show_set_base_finalize(Cwin_show_setClass *windowClass)
{
    UNUSED_VAR(windowClass);
}

//类构造函数
static void Cwin_show_set_class_init(Cwin_show_setClass *windowClass,gpointer class_data)
{
    GObjectClass *base_class = G_OBJECT_CLASS(windowClass);
#ifdef USE_GENE_PROPERTY_CODE
    GParamSpec *property = NULL ;
#endif
#ifdef USE_GENE_CLASS_PRIVATE_CODE
    Cwin_show_set_class_private *p = WIN_SHOW_SET_CLASS_GET_PRIVATE(windowClass);
#endif

    UNUSED_VAR(class_data);

    //加入对象私有数据
    g_type_class_add_private(windowClass,sizeof(Cwin_show_set_private));
    //初始化类函数
    base_class->dispose = (void(*)(GObject *object))Cwin_show_set_inst_dispose ;
    base_class->finalize = (void(*)(GObject *object))Cwin_show_set_inst_finalize;

#ifdef USE_GENE_PROPERTY_CODE
    base_class->set_property = Cwin_show_set_set_property;
    base_class->get_property = Cwin_show_set_get_property;

    //注册属性
    property = g_param_spec_string("name","Name","The Attr Name",NULL,G_PARAM_READWRITE);
    g_object_class_install_property(base_class,WIN_SHOW_SET_CLASS_PROPERTY_NAME,property);
#endif

#ifdef USE_GENE_SIGNAL_CODE
    //注册信号
    mg_signal[WIN_SHOW_SET_SIGNAL_FIRST_SIG] = g_signal_new("first_sig",
            G_TYPE_FROM_CLASS(windowClass),
            G_SIGNAL_RUN_FIRST,
            0,NULL,NULL,g_cclosure_marshal_VOID__VOID,
            G_TYPE_NONE,0,NULL);
    //当要产生信号时，使用 g_signal_emit(G_OBJECT(window), mg_signal[WIN_SHOW_SET_SIGNAL_FIRST_SIG], 0);发送信号
#endif
}

//类析构函数
static void Cwin_show_set_class_finalize(Cwin_show_setClass *windowClass,gpointer class_data)
{
    UNUSED_VAR(windowClass);
    UNUSED_VAR(class_data);
}

static void update_date(Cwin_show_set *window)
{
    char buff[256];

    // 用户
    if(window->prv->m_is_login)
    {
        gtk_entry_set_text(GTK_ENTRY(window->prv->m_en_user),mg_htxy_global.userinfo_user);
        gtk_entry_set_text(GTK_ENTRY(window->prv->m_en_dept),mg_htxy_global.userinfo_dept);
    }

    // 系统参数
    gtk_entry_set_text(GTK_ENTRY(window->prv->m_en_url),mg_htxy_global.platform_url);
    gtk_entry_set_text(GTK_ENTRY(window->prv->m_en_web),mg_htxy_global.platform_web);
    gtk_entry_set_text(GTK_ENTRY(window->prv->m_en_app_name),mg_htxy_global.platform_name);

    //通信
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(window->prv->m_ck_auto_sync),mg_htxy_global.listenser_isync);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(window->prv->m_ck_faren),mg_htxy_global.is_use_organs);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(window->prv->m_ck_ziranren),mg_htxy_global.is_use_person);
    g_snprintf(buff,sizeof(buff),"%d",mg_htxy_global.listenser_delay);
    gtk_entry_set_text(GTK_ENTRY(window->prv->m_en_delay),buff);
}

static void switch_user_view(Cwin_show_set*window, int is_login )
{
    GtkWidget *label ;
    GtkWidget *bt ;
    GtkWidget *entry ;
    GdkPixbuf *bf; 
    char path[256];

    if(is_login == window->prv->m_is_login )
    {
        return ;
    }

    window->prv->m_is_login = is_login ;

    if(window->prv->m_user_child_table != NULL)
    {
        gtk_container_remove(GTK_CONTAINER(window->prv->m_user_child_frame),GTK_WIDGET(window->prv->m_user_child_table));
        window->prv->m_user_child_table = NULL ;
    }
    window->prv->m_user_child_table = GTK_WIDGET(Cgtk_grid_table_new());
    gtk_container_add(GTK_CONTAINER(window->prv->m_user_child_frame),GTK_WIDGET(window->prv->m_user_child_table));

    if(is_login==0)
    {
        label = gtk_label_new(get_const_str(101));
        gtk_label_set_markup(GTK_LABEL(label),get_const_str(101));
        window->prv->m_en_usrname = gtk_entry_new();
        g_snprintf(path,sizeof(path),"%simage/usr.png",mg_htxy_global.exe_dir);
        gtk_entry_set_text(GTK_ENTRY(window->prv->m_en_usrname),"gonganju");
        bf = gdk_pixbuf_new_from_file(path,NULL);
        if(bf)
        {
            gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(window->prv->m_en_usrname),GTK_ENTRY_ICON_SECONDARY,bf);
            gtk_entry_set_icon_activatable(GTK_ENTRY(window->prv->m_en_usrname),GTK_ENTRY_ICON_SECONDARY,FALSE);
            g_object_unref(G_OBJECT(bf));
        }
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_user_child_table),GTK_WIDGET(label),
            0,0,1,1, FALSE, TRUE , FALSE,TRUE);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_user_child_table),GTK_WIDGET(window->prv->m_en_usrname),
            1,0,2,1, TRUE, TRUE , TRUE,TRUE);

        label = gtk_label_new(get_const_str(102));
        gtk_label_set_markup(GTK_LABEL(label),get_const_str(102));
        window->prv->m_en_password = gtk_entry_new();
        g_snprintf(path,sizeof(path),"%simage/password.png",mg_htxy_global.exe_dir);
        gtk_entry_set_text(GTK_ENTRY(window->prv->m_en_password),"gonganju");
        bf = gdk_pixbuf_new_from_file(path,NULL);
        if(bf)
        {
            gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(window->prv->m_en_password),GTK_ENTRY_ICON_SECONDARY,bf);
            gtk_entry_set_icon_activatable(GTK_ENTRY(window->prv->m_en_password),GTK_ENTRY_ICON_SECONDARY,FALSE);
            g_object_unref(G_OBJECT(bf));
        }
        gtk_entry_set_visibility(GTK_ENTRY(window->prv->m_en_password),FALSE);
        gtk_entry_set_activates_default(GTK_ENTRY(window->prv->m_en_password),TRUE);
        g_signal_connect(G_OBJECT(window->prv->m_en_password),"activate",G_CALLBACK(slog_bt_login),window);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_user_child_table),GTK_WIDGET(label),
            0,1,1,1, FALSE, TRUE , FALSE,TRUE);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_user_child_table),GTK_WIDGET(window->prv->m_en_password),
            1,1,2,1, TRUE, TRUE , TRUE,TRUE);

        bt = gtk_button_new_with_label("  ");
        label = gtk_label_new(get_const_str(103));
        gtk_label_set_markup(GTK_LABEL(label),get_const_str(103));
        gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(label));
        g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_login),window);
        label = gtk_label_new("");
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_user_child_table),GTK_WIDGET(label),
            0,2,1,1, TRUE , TRUE , TRUE ,TRUE);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_user_child_table),GTK_WIDGET(bt),
            2,2,1,1, FALSE, TRUE , FALSE,TRUE);

        window->prv->m_label_error_str = gtk_label_new("");
        gtk_misc_set_alignment(GTK_MISC(window->prv->m_label_error_str), 0.1f , 0.5f);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_user_child_table),GTK_WIDGET(window->prv->m_label_error_str),
            0,3,3,1, TRUE , TRUE , TRUE ,FALSE);

    }
    else
    {
        label = gtk_label_new(get_const_str(105));
        gtk_label_set_markup(GTK_LABEL(label),get_const_str(105));
        entry = gtk_entry_new();
        window->prv->m_en_user = entry ;
        g_snprintf(path,sizeof(path),"%simage/usr.png",mg_htxy_global.exe_dir);
        gtk_entry_set_text(GTK_ENTRY(entry),mg_htxy_global.userinfo_dept);
        bf = gdk_pixbuf_new_from_file(path,NULL);
        if(bf)
        {
            gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(entry),GTK_ENTRY_ICON_SECONDARY,bf);
            gtk_entry_set_icon_activatable(GTK_ENTRY(entry),GTK_ENTRY_ICON_SECONDARY,FALSE);
            g_object_unref(G_OBJECT(bf));
        }
        gtk_widget_set_sensitive(GTK_WIDGET(entry),FALSE);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_user_child_table),GTK_WIDGET(label),
            0,0,1,1, FALSE, TRUE , FALSE,TRUE);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_user_child_table),GTK_WIDGET(entry),
            1,0,2,1, TRUE, TRUE , TRUE,TRUE);

        label = gtk_label_new(get_const_str(106));
        gtk_label_set_markup(GTK_LABEL(label),get_const_str(106));
        entry = gtk_entry_new();
        window->prv->m_en_dept = entry ;
        g_snprintf(path,sizeof(path),"%simage/password.png",mg_htxy_global.exe_dir);
        gtk_entry_set_text(GTK_ENTRY(entry),mg_htxy_global.userinfo_user);
        bf = gdk_pixbuf_new_from_file(path,NULL);
        if(bf)
        {
            gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(entry),GTK_ENTRY_ICON_SECONDARY,bf);
            gtk_entry_set_icon_activatable(GTK_ENTRY(entry),GTK_ENTRY_ICON_SECONDARY,FALSE);
            g_object_unref(G_OBJECT(bf));
        }
        gtk_widget_set_sensitive(GTK_WIDGET(entry),FALSE);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_user_child_table),GTK_WIDGET(label),
            0,1,1,1, FALSE, TRUE , FALSE,TRUE);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_user_child_table),GTK_WIDGET(entry),
            1,1,2,1, TRUE, TRUE , TRUE,TRUE);

        bt = gtk_button_new_with_label("  ");
        label = gtk_label_new(get_const_str(107));
        gtk_label_set_markup(GTK_LABEL(label),get_const_str(107));
        gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(label));
        g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_relogin),window);
        label = gtk_label_new("");
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_user_child_table),GTK_WIDGET(label),
            0,2,1,1, TRUE , TRUE , TRUE ,TRUE);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_user_child_table),GTK_WIDGET(bt),
            2,2,1,1, FALSE, TRUE , FALSE,TRUE);

        window->prv->m_label_error_str = gtk_label_new("");
        gtk_misc_set_alignment(GTK_MISC(window->prv->m_label_error_str), 0.1f , 0.5f);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_user_child_table),GTK_WIDGET(window->prv->m_label_error_str),
            0,3,3,1, TRUE , TRUE , TRUE ,FALSE);
    }

    gtk_widget_show_all(GTK_WIDGET(window));
    
}


//对象构造函数
static void Cwin_show_set_inst_init(Cwin_show_set *window)
{
    GtkWidget *main_notebook ;
    GtkWidget *sys_table ;  ///< 系统
    GtkWidget *user_table ; ///< 用户
    GtkWidget *update_table ; ///< 升级
    GtkWidget *param_table ;    ///< 参数
    GtkWidget *port_table ;    ///< 接口
    GtkWidget *label ;
    GtkWidget *bt ;
    GtkWidget *frame;
    GtkWidget *sep ;
    GdkPixbuf *bf; 
    GtkWidget *hbox ;
    GtkWidget *vbox ;
    int line = 0 ;
    char path[256];
    GtkTreeViewColumn *column ;
    GtkCellRenderer *renderer ;

    window->prv = WIN_SHOW_SET_GET_PRIVATE(window);
    window->prv->m_is_login = -1 ;

    /// 修改配置BT
    label = gtk_label_new(get_const_str(97));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(97));
    bt = gtk_button_new_with_label("");
    gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(label));
    g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_clicked_update_cfg),window);
    vbox = gtk_vbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox),bt,FALSE,FALSE,0);

    /// 主NoteBook
    main_notebook = gtk_notebook_new();
    gtk_box_pack_start(GTK_BOX(vbox),main_notebook,TRUE,TRUE,0);
    sys_table = GTK_WIDGET(Cgtk_grid_table_new());
    port_table = GTK_WIDGET(Cgtk_grid_table_new());

    label = GTK_WIDGET(Cfunc_label_new());
    g_snprintf(path,sizeof(path),"%simage/sys.png",mg_htxy_global.exe_dir);
    Cfunc_label_set_image_and_text((Cfunc_label*)label,path,get_const_str(81),24,24);
    Cfunc_label_markup_text((Cfunc_label*)label,get_const_str(81));
    gtk_notebook_append_page(GTK_NOTEBOOK(main_notebook),sys_table,label);
    label = GTK_WIDGET(Cfunc_label_new());
    g_snprintf(path,sizeof(path),"%simage/port.png",mg_htxy_global.exe_dir);
    Cfunc_label_set_image_and_text((Cfunc_label*)label,path,get_const_str(82),24,24);
    Cfunc_label_markup_text((Cfunc_label*)label,get_const_str(82));
    gtk_notebook_append_page(GTK_NOTEBOOK(main_notebook),port_table,label);

    /// 系统设置
    user_table = GTK_WIDGET(Cgtk_grid_table_new());
    update_table = GTK_WIDGET(Cgtk_grid_table_new());
    param_table = GTK_WIDGET(Cgtk_grid_table_new());
    gtk_grid_table_set_row_spacings(GTK_GRID_TABLE(sys_table),10);
    gtk_grid_table_set_col_spacings(GTK_GRID_TABLE(sys_table),10);
    gtk_grid_table_set_row_spacings(GTK_GRID_TABLE(user_table),10);
    gtk_grid_table_set_col_spacings(GTK_GRID_TABLE(user_table),10);
    gtk_grid_table_set_row_spacings(GTK_GRID_TABLE(update_table),10);
    gtk_grid_table_set_col_spacings(GTK_GRID_TABLE(update_table),10);
    
    frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(frame),user_table);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(sys_table),GTK_WIDGET(frame),
        0,0,1,1, TRUE, TRUE , TRUE,TRUE);
    frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(frame),update_table);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(sys_table),GTK_WIDGET(frame),
        0,1,1,1, TRUE, TRUE , TRUE,TRUE);
    frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(frame),param_table);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(sys_table),GTK_WIDGET(frame),
        1,0,1,2, TRUE, TRUE , TRUE,TRUE);

    /// 用户
    label = GTK_WIDGET(Cfunc_label_new());
    sep = gtk_hseparator_new();
    g_snprintf(path,sizeof(path),"%simage/user.png",mg_htxy_global.exe_dir);
    Cfunc_label_set_image_and_text((Cfunc_label*)label,path,get_const_str(83),24,24);
    Cfunc_label_markup_text((Cfunc_label*)label,get_const_str(83));
    window->prv->m_user_child_frame = gtk_frame_new(NULL);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(user_table),GTK_WIDGET(label),
        0,0,1,1, TRUE, FALSE, TRUE,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(user_table),GTK_WIDGET(sep),
        0,1,1,1, TRUE, FALSE, TRUE,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(user_table),GTK_WIDGET(window->prv->m_user_child_frame),
        0,2,1,1, TRUE, TRUE , TRUE,TRUE);
    switch_user_view(window, mg_htxy_global.userinfo_status ) ;

    /// 自动升级
    label = gtk_label_new(get_const_str(184));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(184));
    gtk_misc_set_alignment(GTK_MISC(label),0.1f,0.5f);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(update_table),GTK_WIDGET(label),
        0,0,1,1, TRUE , TRUE , TRUE,TRUE);
    label = gtk_label_new(mg_htxy_global.this_version);
    gtk_misc_set_alignment(GTK_MISC(label),1.0f,0.5f);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(update_table),GTK_WIDGET(label),
        0,1,1,1, TRUE , TRUE , TRUE,TRUE);
    label = gtk_label_new(get_const_str(181));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(181));
    bt = gtk_button_new_with_label("  ");
    gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(label));
    g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_clicked_update),window);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(update_table),GTK_WIDGET(bt),
        0,2,1,1, TRUE , FALSE , TRUE,FALSE );

    /// 应用参数
    line = 0 ;
    label = GTK_WIDGET(Cfunc_label_new());
    sep = gtk_hseparator_new();
    g_snprintf(path,sizeof(path),"%simage/param.png",mg_htxy_global.exe_dir);
    Cfunc_label_set_image_and_text((Cfunc_label*)label,path,get_const_str(84),24,24);
    Cfunc_label_markup_text((Cfunc_label*)label,get_const_str(84));
    Cgtk_grid_table_attach(GTK_GRID_TABLE(param_table),GTK_WIDGET(label),
        0,line++,2,1, TRUE, FALSE, TRUE,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(param_table),GTK_WIDGET(sep),
        0,line++,2,1, TRUE, FALSE, TRUE,TRUE);

    // url
    label = gtk_label_new(get_const_str(85));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(85));
    gtk_misc_set_alignment(GTK_MISC(label), 0.0f , 0.5f);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(param_table),GTK_WIDGET(label),
        0,line++,2,1, TRUE, TRUE , TRUE,TRUE);

    window->prv->m_en_url = gtk_entry_new();
    g_snprintf(path,sizeof(path),"%simage/link.png",mg_htxy_global.exe_dir);
    bf = gdk_pixbuf_new_from_file(path,NULL);
    if(bf)
    {
        gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(window->prv->m_en_url),GTK_ENTRY_ICON_PRIMARY,bf);
        g_object_unref(G_OBJECT(bf));
    }
    Cgtk_grid_table_attach(GTK_GRID_TABLE(param_table),GTK_WIDGET(window->prv->m_en_url),
        0,line,2,1, TRUE , TRUE , TRUE ,TRUE);
    line++ ;

    // web
    label = gtk_label_new(get_const_str(86));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(86));
    gtk_misc_set_alignment(GTK_MISC(label), 0.0f , 0.5f);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(param_table),GTK_WIDGET(label),
        0,line++,2,1, TRUE, TRUE , TRUE,TRUE);

    window->prv->m_en_web = gtk_entry_new();
    g_snprintf(path,sizeof(path),"%simage/link.png",mg_htxy_global.exe_dir);
    bf = gdk_pixbuf_new_from_file(path,NULL);
    if(bf)
    {
        gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(window->prv->m_en_web),GTK_ENTRY_ICON_PRIMARY,bf);
        g_object_unref(G_OBJECT(bf));
    }
    Cgtk_grid_table_attach(GTK_GRID_TABLE(param_table),GTK_WIDGET(window->prv->m_en_web),
        0,line,2,1, TRUE , TRUE, TRUE ,TRUE);
    line++ ;

    // 应用名称
    label = gtk_label_new(get_const_str(87));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(87));
    gtk_misc_set_alignment(GTK_MISC(label), 0.0f , 0.5f);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(param_table),GTK_WIDGET(label),
        0,line++,2,1, TRUE, TRUE , TRUE,TRUE);

    window->prv->m_en_app_name = gtk_entry_new();
    g_snprintf(path,sizeof(path),"%simage/app_name.png",mg_htxy_global.exe_dir);
    bf = gdk_pixbuf_new_from_file(path,NULL);
    if(bf)
    {
        gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(window->prv->m_en_app_name),GTK_ENTRY_ICON_PRIMARY,bf);
        g_object_unref(G_OBJECT(bf));
    }
    Cgtk_grid_table_attach(GTK_GRID_TABLE(param_table),GTK_WIDGET(window->prv->m_en_app_name),
        0,line,2,1, TRUE , TRUE , TRUE ,TRUE);
    line++ ;

    /// 数据同步
    sep = gtk_hseparator_new();
    Cgtk_grid_table_attach(GTK_GRID_TABLE(param_table),GTK_WIDGET(sep),
        0,line++,2,1, TRUE, TRUE, TRUE,TRUE);

    hbox = gtk_hbox_new(FALSE,0);
    label = GTK_WIDGET(Cfunc_label_new());
    g_snprintf(path,sizeof(path),"%simage/sync.png",mg_htxy_global.exe_dir);
    Cfunc_label_set_image_and_text((Cfunc_label*)label,path,get_const_str(88),24,24);
    Cfunc_label_markup_text((Cfunc_label*)label,get_const_str(88));
    gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(label),FALSE,FALSE,0);
    label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(label),TRUE,TRUE,0);
    label = gtk_label_new(get_const_str(89));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(89));
    bt = gtk_button_new_with_label("");
    gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(label));
    g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_clicked_liji),window);
    gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(bt),FALSE,FALSE,0);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(param_table),GTK_WIDGET(hbox),
        0,line++,2,1, TRUE, TRUE , TRUE,TRUE);

    //数据类型
    label = gtk_label_new(get_const_str(94));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(94));
    gtk_misc_set_alignment(GTK_MISC(label),1.0f,0.5f);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(param_table),GTK_WIDGET(label),
        0,line,1,1, FALSE, TRUE , TRUE ,TRUE);
    hbox = gtk_hbox_new(FALSE,0);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(param_table),GTK_WIDGET(hbox),
        1,line,1,1, TRUE , TRUE , TRUE ,TRUE);
    label = gtk_label_new(get_const_str(95));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(95));
    window->prv->m_ck_faren = gtk_check_button_new_with_label("");
    gtk_button_set_image(GTK_BUTTON(window->prv->m_ck_faren),GTK_WIDGET(label));
    gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(window->prv->m_ck_faren),FALSE,FALSE,0);
    label = gtk_label_new(get_const_str(96));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(96));
    window->prv->m_ck_ziranren = gtk_check_button_new_with_label("");
    gtk_button_set_image(GTK_BUTTON(window->prv->m_ck_ziranren ),GTK_WIDGET(label));
    gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(window->prv->m_ck_ziranren),FALSE,FALSE,0);
    line++ ;

    //自动同步
    label = gtk_label_new(get_const_str(91));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(91));
    gtk_misc_set_alignment(GTK_MISC(label),1.0f,0.5f);
    window->prv->m_ck_auto_sync = gtk_check_button_new_with_label("");
    gtk_button_set_image(GTK_BUTTON(window->prv->m_ck_auto_sync),GTK_WIDGET(label));
    hbox = gtk_hbox_new(FALSE,0);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(param_table),GTK_WIDGET(window->prv->m_ck_auto_sync),
        0,line,1,1, FALSE, TRUE , FALSE,TRUE);
    hbox = gtk_hbox_new(FALSE,0);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(param_table),GTK_WIDGET(hbox),
        1,line,1,1, TRUE , TRUE , TRUE ,TRUE);
    line++ ;
    label = gtk_label_new(get_const_str(92));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(92));
    gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(label),FALSE,FALSE,0);
    window->prv->m_en_delay = gtk_entry_new();
    g_snprintf(path,sizeof(path),"%simage/clock.png",mg_htxy_global.exe_dir);
    bf = gdk_pixbuf_new_from_file(path,NULL);
    if(bf)
    {
        gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(window->prv->m_en_delay),GTK_ENTRY_ICON_PRIMARY,bf);
        g_object_unref(G_OBJECT(bf));
    }
    gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(window->prv->m_en_delay),TRUE,TRUE,0);
    label = gtk_label_new(get_const_str(93));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(93));
    gtk_box_pack_start(GTK_BOX(hbox),GTK_WIDGET(label),FALSE,FALSE,0);

    // 接口管理
    window->prv->m_treeStore = gtk_tree_store_new(COL_NUMS, G_TYPE_POINTER,G_TYPE_INT);
    gtk_tree_store_clear(window->prv->m_treeStore);

#define NEW_CLOUMN(string_id,width) \
    do { \
        column = gtk_tree_view_column_new(); \
        label = GTK_WIDGET(Cfunc_label_new()); \
        Cfunc_label_markup_text((Cfunc_label*)label,(char*)get_const_str(string_id)); \
        gtk_tree_view_column_set_sizing(column,GTK_TREE_VIEW_COLUMN_FIXED);\
        gtk_tree_view_column_set_widget(column,GTK_WIDGET(label)); \
        gtk_tree_view_column_set_resizable(column,FALSE);\
        gtk_tree_view_column_set_fixed_width(column,width); \
        gtk_tree_view_append_column(GTK_TREE_VIEW(window->prv->m_treeView), column); \
    }while(0)

    // 树
    window->prv->m_treeView = GTK_TREE_VIEW(gtk_tree_view_new());
    Cgtk_grid_table_attach(GTK_GRID_TABLE(port_table),GTK_WIDGET(window->prv->m_treeView),
        0,0,1,1, TRUE, TRUE, TRUE,TRUE);
    gtk_tree_view_set_model(GTK_TREE_VIEW(window->prv->m_treeView),GTK_TREE_MODEL(window->prv->m_treeStore));
    gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(window->prv->m_treeView), TRUE);
    gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(window->prv->m_treeView), GTK_TREE_VIEW_GRID_LINES_HORIZONTAL);
    gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(window->prv->m_treeView)), GTK_SELECTION_NONE);

    NEW_CLOUMN(121,50) ;
    renderer = gtk_cell_renderer_text_new(); 
    gtk_cell_renderer_set_alignment(renderer,1.0f,0.5f);
    gtk_tree_view_column_pack_start(column,renderer,TRUE);
    gtk_tree_view_column_set_cell_data_func(column, renderer, no_cell_data_func, window, NULL);

    NEW_CLOUMN(122,160) ;
    renderer = gtk_cell_renderer_text_new(); 
    gtk_cell_renderer_set_alignment(renderer,1.0f,0.5f);
    gtk_tree_view_column_pack_start(column,renderer,TRUE);
    gtk_tree_view_column_set_cell_data_func(column, renderer, name_cell_data_func, window, NULL);

    NEW_CLOUMN(123,350) ;
    renderer = gtk_cell_renderer_text_new(); 
    gtk_cell_renderer_set_alignment(renderer,1.0f,0.5f);
    gtk_tree_view_column_pack_start(column,renderer,TRUE);
    gtk_tree_view_column_set_cell_data_func(column, renderer, url_cell_data_func, window, NULL);

    NEW_CLOUMN(124,100) ;
    renderer = gtk_cell_renderer_text_new(); 
    gtk_cell_renderer_set_alignment(renderer,1.0f,0.5f);
    gtk_tree_view_column_pack_start(column,renderer,TRUE);
    gtk_tree_view_column_set_cell_data_func(column, renderer, type_cell_data_func, window, NULL);

    //初始化树数据
    {
        GtkTreeIter iter ;
        int i;

        for(i=0;i< TYPE_URL_MAX_API_COUNT ; i++)
        {
            if(mg_htxy_global.api[i].name[0] != '\0' )
            {
                gtk_tree_store_append(window->prv->m_treeStore, &iter, NULL);
                gtk_tree_store_set(window->prv->m_treeStore, &iter, 
                    COL_POINTER, &mg_htxy_global.api[i],
                    COL_INDEX , i ,
                    -1 );
            }
        }
    }

    gtk_widget_set_usize(GTK_WIDGET(window), 700,600);
    Cwin_login_set_child((Cwin_login*)window , GTK_WIDGET(vbox));
    update_date(window);
    gtk_widget_show_all(GTK_WIDGET(window));
}

//对象析构函数
static void Cwin_show_set_inst_finalize(Cwin_show_set *window)
{
    G_OBJECT_CLASS(g_type_class_peek(g_type_parent(g_type_from_name("Cwin_show_set"))))->finalize(G_OBJECT(window));
}
//对象释放函数
static void Cwin_show_set_inst_dispose(Cwin_show_set *window)
{
    G_OBJECT_CLASS(g_type_class_peek(g_type_parent(g_type_from_name("Cwin_show_set"))))->dispose(G_OBJECT(window));
}

#ifdef USE_GENE_PROPERTY_CODE
static void Cwin_show_set_set_property(GObject *object,
        guint  property_id,
        const GValue *value,
        GParamSpec *pspec)
{
    Cwin_show_set *window = WIN_SHOW_SET(object);

    UNUSED_VAR(window);

    switch(property_id)
    {
        case WIN_SHOW_SET_CLASS_PROPERTY_NAME:
            //加入设置name到value的代码
            break ;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,pspec);
            break;
    }
}
static void Cwin_show_set_get_property(GObject  *object,
        guint property_id,
        GValue *value,
        GParamSpec *pspec)
{
    Cwin_show_set *window = WIN_SHOW_SET(object);

    UNUSED_VAR(window);

    switch(property_id)
    {
        case WIN_SHOW_SET_CLASS_PROPERTY_NAME:
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
Cwin_show_set* Cwin_show_set_new(void)
{
    Cwin_show_set* window;
    window = (Cwin_show_set*)g_object_new(WIN_SHOW_SET_TYPE,NULL);

    return window;
}
//////////////////////////////////////////////////
///
///  私有函数实现
///
///////////////////////////////////////////////////

static void slog_bt_update_utl(GtkButton *button, gpointer   user_data)
{
}

static void slog_bt_clicked_liji(GtkButton *button, gpointer   user_data)
{
    if(mg_htxy_global.organId[0] == '\0' )
    {
        gtk_show_msg_dlg(141,142);
        return ;
    }
    update_all_db() ;
}

static void slog_bt_clicked_update(GtkButton *button, gpointer   user_data)
{
    if(update_check_is_new() == FALSE)
    {
        gtk_show_msg_dlg(182,183);
        return ;
    }

    if(update_download_packet())
    {
        update_do_update();
    }
}

static void slog_bt_clicked_update_cfg(GtkButton *button, gpointer   user_data)
{
    Cwin_show_set *window = (Cwin_show_set*)user_data ;
    const char *text ;
    // 系统参数
    text = gtk_entry_get_text(GTK_ENTRY(window->prv->m_en_url));
    if(text)
    {
        g_strlcpy(mg_htxy_global.platform_url,text,sizeof(mg_htxy_global.platform_url));
    }
    text = gtk_entry_get_text(GTK_ENTRY(window->prv->m_en_web));
    if(text)
    {
        g_strlcpy(mg_htxy_global.platform_web,text,sizeof(mg_htxy_global.platform_web));
    }
    text = gtk_entry_get_text(GTK_ENTRY(window->prv->m_en_app_name));
    if(text)
    {
        g_strlcpy(mg_htxy_global.platform_name,text,sizeof(mg_htxy_global.platform_name));
    }

    //通信
    mg_htxy_global.listenser_isync = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(window->prv->m_ck_auto_sync));
    mg_htxy_global.is_use_organs = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(window->prv->m_ck_faren));
    mg_htxy_global.is_use_person = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(window->prv->m_ck_ziranren));
    text = gtk_entry_get_text(GTK_ENTRY(window->prv->m_en_delay));
    if(text)
    {
        mg_htxy_global.listenser_delay = atoi(text);
    }

    //
    write_config();
}

static gboolean slog_main_book_change_page(GtkNotebook *notebook,
          gint         arg1, gpointer     user_data)
{
    return FALSE ;
}

static void slog_bt_login(GtkButton *button, gpointer   user_data) 
{
    Cwin_show_set *window = (Cwin_show_set*)user_data ;

    const char* usrname ;
    const char* password ;
    char *msg ;
    char buff[2056];

    usrname = gtk_entry_get_text(GTK_ENTRY(window->prv->m_en_usrname));
    password = gtk_entry_get_text(GTK_ENTRY(window->prv->m_en_password));

    msg = user_login(usrname , password);
    if(msg != NULL)
    {
        g_snprintf(buff,sizeof(buff),get_const_str(104),msg);
        gtk_label_set_text(GTK_LABEL(window->prv->m_label_error_str),buff);
        gtk_label_set_markup(GTK_LABEL(window->prv->m_label_error_str),buff);
        gtk_widget_show_all(GTK_WIDGET(window));
        g_free(msg);
    }
    else
    {
        mg_htxy_global.userinfo_status = TRUE ;
        switch_user_view(window,1);
        update_date(window);
    }
}

static void slog_bt_relogin(GtkButton *button, gpointer   user_data)
{
    Cwin_show_set *window = (Cwin_show_set*)user_data ;

    mg_htxy_global.userinfo_status = FALSE ;
    user_logout();
    switch_user_view(window,0);
}

static void no_cell_data_func (GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data)
{
    Cwin_show_set *window = (Cwin_show_set*)user_data ;

    gint no ;
    char text[1024];
    gtk_tree_model_get(model, iter, COL_INDEX , &no,  -1);
    g_snprintf(text,sizeof(text),get_const_str(131),no+1);
    g_object_set(renderer, "text", text, NULL);
    g_object_set(renderer, "markup", text, NULL);
}

static void name_cell_data_func (GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data)
{
    Cwin_show_set *window = (Cwin_show_set*)user_data ;
    API_ITEM *item ;
    char text[1024];

    gtk_tree_model_get(model, iter, COL_POINTER, &item,  -1);
    g_snprintf(text,sizeof(text),get_const_str(132),item->name);
    g_object_set(renderer, "text", text, NULL);
    g_object_set(renderer, "markup", text, NULL);
}

static void url_cell_data_func (GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data)
{
    Cwin_show_set *window = (Cwin_show_set*)user_data ;
    API_ITEM *item ;
    char text[1024];

    gtk_tree_model_get(model, iter, COL_POINTER, &item,  -1);
    g_snprintf(text,sizeof(text),get_const_str(133),item->url);
    g_object_set(renderer, "text", text, NULL);
    g_object_set(renderer, "markup", text, NULL);
}

static void type_cell_data_func (GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data)
{
    Cwin_show_set *window = (Cwin_show_set*)user_data ;
    API_ITEM *item ;
    char text[1024];

    gtk_tree_model_get(model, iter, COL_POINTER, &item,  -1);
    g_snprintf(text,sizeof(text),get_const_str(134),item->type);
    g_object_set(renderer, "text", text, NULL);
    g_object_set(renderer, "markup", text, NULL);
}


#ifdef __cplusplus
}
#endif

