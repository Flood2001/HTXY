/////////////////////////////////////////////////////
/// Copyright (C) 2017 Hrsoft Corporation, All rights reserved.
/// @file win_show_shishi.c
/// @author 张洪峰
/// @version 1.0
/// @date 2017-10-18 
/// @brief 显示查询到的信息
/////////////////////////////////////////////////////
#include <hrutil/hrutil.h>
#include "gtk_win.h"
#include "win_show_shishi.h"

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
struct _c_win_show_shishi_private {
    GtkWidget *m_label_name ;
    GtkWidget *m_entry_name ;
    GtkWidget *m_label_haoma ;
    GtkWidget *m_entry_haoma ;
    GtkWidget *m_label_cuoshi ;
    GtkWidget *m_entry_cuoshi ;
    GtkWidget *m_label_shijian ;
    GtkWidget *m_entry_shijian ;
    GtkWidget *m_label_shiyou ;
    GtkWidget *m_entry_shiyou ;
    GtkWidget *m_entry_shiyou_table ;
    GtkWidget *m_label_yiju ;
    GtkWidget *m_entry_yiju ;

    GtkWidget *m_label_shuoming ;
    GtkWidget *m_entry_shuoming ;

    //
    ST_TIME m_shijian ;
};

#define  WIN_SHOW_SHISHI_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj),WIN_SHOW_SHISHI_TYPE,Cwin_show_shishi_private))

#ifdef USE_GENE_CLASS_PRIVATE_CODE

//类的共有私有数据
typedef struct _c_win_show_shishi_class_private {
    int pri;
}Cwin_show_shishi_class_private;

#define WIN_SHOW_SHISHI_CLASS_GET_PRIVATE(klass) (G_TYPE_CLASS_GET_PRIVATE((klass),WIN_SHOW_SHISHI_TYPE,Cwin_show_shishi_class_private))

#endif //USE_GENE_CLASS_PRIVATE_CODE

#ifdef USE_GENE_PROPERTY_CODE
///类属性，增加类属性的步骤：
///    1.在此处增加一个属性的ENUM，
///    2.在class_init函数中增加属性注册函数
///    3.在get_property/set_property中增加属性的读/写函数
///    4.在.h中增加说明以便用户使用
enum {
    WIN_SHOW_SHISHI_CLASS_PROPERTY_0,///<不可使用
    WIN_SHOW_SHISHI_CLASS_PROPERTY_NAME,
    WIN_SHOW_SHISHI_CLASS_N_PROPERTYS
};
#endif

#ifdef USE_GENE_SIGNAL_CODE
/// 信号，增加信号的步骤：
///    1.在此处增加一个信号的ENUM，
///    2.在class_init函数中增加信号注册函数
///    3.在产生信号的地方使用g_signal_emit发送信号
///    4.在.h中增加说明以便用户使用
enum {
    WIN_SHOW_SHISHI_SIGNAL_FIRST_SIG,
    WIN_SHOW_SHISHI_SIGNAL_SIG_LAST
};
static int mg_signal[WIN_SHOW_SHISHI_SIGNAL_SIG_LAST]={0};
#endif

//////////////////////////////////////////////////
///
/// 私有函数
///
///////////////////////////////////////////////////
static void Cwin_show_shishi_base_init(Cwin_show_shishiClass *windowClass);
static void Cwin_show_shishi_base_finalize(Cwin_show_shishiClass *windowClass);
static void Cwin_show_shishi_class_init(Cwin_show_shishiClass *windowClass,gpointer class_data);
static void Cwin_show_shishi_class_finalize(Cwin_show_shishiClass *windowClass,gpointer class_data);
static void Cwin_show_shishi_inst_init(Cwin_show_shishi *window);
static void Cwin_show_shishi_inst_finalize(Cwin_show_shishi *window);
static void Cwin_show_shishi_inst_dispose(Cwin_show_shishi *window);

#ifdef USE_GENE_PROPERTY_CODE
static void Cwin_show_shishi_set_property(GObject *object,
        guint  property_id,
        const GValue *value,
        GParamSpec  *pspec);
static void Cwin_show_shishi_get_property(GObject *object,
        guint  property_id,
        GValue *value,
        GParamSpec *pspec);
#endif

static void slog_clicked_time(GtkButton *button, gpointer user_data) ;
static void slog_clicked_cancel(GtkButton *button, gpointer user_data) ;
static void slog_clicked_fankui(GtkButton *button, gpointer user_data) ;
//////////////////////////////////////////////////
///
///  类基本函数实现
///
///////////////////////////////////////////////////

//生成对象类的ID标识
GType Cwin_show_shishi_type(void)
{
    static GType window_type=0;
    if(!window_type)
    {
        static const GTypeInfo window_info = {
            sizeof(Cwin_show_shishiClass),
            (GBaseInitFunc)Cwin_show_shishi_base_init,
            (GBaseFinalizeFunc)Cwin_show_shishi_base_finalize,

            (GClassInitFunc)Cwin_show_shishi_class_init,
            NULL,

            //(GClassFinalizeFunc)Cwin_show_shishi_class_finalize,
            NULL,

            sizeof(Cwin_show_shishi),0,
            (GInstanceInitFunc)Cwin_show_shishi_inst_init
        };
        window_type = g_type_register_static(WIN_LOGIN_TYPE ,"Cwin_show_shishi",&window_info,0);

#ifdef USE_GENE_CLASS_PRIVATE_CODE
        g_type_add_class_private(window_type,sizeof(Cwin_show_shishi_class_private));
#endif
    }
    return window_type;
}

static void Cwin_show_shishi_base_init(Cwin_show_shishiClass *windowClass)
{
    UNUSED_VAR(windowClass);
}
static void Cwin_show_shishi_base_finalize(Cwin_show_shishiClass *windowClass)
{
    UNUSED_VAR(windowClass);
}

//类构造函数
static void Cwin_show_shishi_class_init(Cwin_show_shishiClass *windowClass,gpointer class_data)
{
    GObjectClass *base_class = G_OBJECT_CLASS(windowClass);
#ifdef USE_GENE_PROPERTY_CODE
    GParamSpec *property = NULL ;
#endif
#ifdef USE_GENE_CLASS_PRIVATE_CODE
    Cwin_show_shishi_class_private *p = WIN_SHOW_SHISHI_CLASS_GET_PRIVATE(windowClass);
#endif

    UNUSED_VAR(class_data);

    //加入对象私有数据
    g_type_class_add_private(windowClass,sizeof(Cwin_show_shishi_private));
    //初始化类函数
    base_class->dispose = (void(*)(GObject *object))Cwin_show_shishi_inst_dispose ;
    base_class->finalize = (void(*)(GObject *object))Cwin_show_shishi_inst_finalize;

#ifdef USE_GENE_PROPERTY_CODE
    base_class->set_property = Cwin_show_shishi_set_property;
    base_class->get_property = Cwin_show_shishi_get_property;

    //注册属性
    property = g_param_spec_string("name","Name","The Attr Name",NULL,G_PARAM_READWRITE);
    g_object_class_install_property(base_class,WIN_SHOW_SHISHI_CLASS_PROPERTY_NAME,property);
#endif

#ifdef USE_GENE_SIGNAL_CODE
    //注册信号
    mg_signal[WIN_SHOW_SHISHI_SIGNAL_FIRST_SIG] = g_signal_new("first_sig",
            G_TYPE_FROM_CLASS(windowClass),
            G_SIGNAL_RUN_FIRST,
            0,NULL,NULL,g_cclosure_marshal_VOID__VOID,
            G_TYPE_NONE,0,NULL);
    //当要产生信号时，使用 g_signal_emit(G_OBJECT(window), mg_signal[WIN_SHOW_SHISHI_SIGNAL_FIRST_SIG], 0);发送信号
#endif
}

//类析构函数
static void Cwin_show_shishi_class_finalize(Cwin_show_shishiClass *windowClass,gpointer class_data)
{
    UNUSED_VAR(windowClass);
    UNUSED_VAR(class_data);
}

//对象构造函数
static void Cwin_show_shishi_inst_init(Cwin_show_shishi *window)
{
    GtkWidget *table ;
    GtkWidget *bt ;
    GtkWidget *hbox ;
    GtkWidget *sep ;
    GtkWidget *label ;
    int line = 0 ;

    window->prv = WIN_SHOW_SHISHI_GET_PRIVATE(window);

    table = GTK_WIDGET(Cgtk_grid_table_new());

    window->prv->m_label_name = gtk_label_new(get_const_str(151));
    gtk_label_set_markup(GTK_LABEL(window->prv->m_label_name), get_const_str(151));
    gtk_misc_set_alignment(GTK_MISC(window->prv->m_label_name), 1.0f , 0.5f);
    window->prv->m_entry_name = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(window->prv->m_entry_name), 0.0f , 0.5f);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_label_name),
        0,line,1,1, TRUE , TRUE , TRUE,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_entry_name),
        1,line,1,1, TRUE , TRUE , TRUE,TRUE);
    line++ ;

    window->prv->m_label_haoma = gtk_label_new(get_const_str(153));
    gtk_label_set_markup(GTK_LABEL(window->prv->m_label_haoma), get_const_str(153));
    gtk_misc_set_alignment(GTK_MISC(window->prv->m_label_haoma), 1.0f , 0.5f);
    window->prv->m_entry_haoma = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(window->prv->m_entry_haoma), 0.0f , 0.5f);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_label_haoma),
        0,line,1,1, TRUE , TRUE , TRUE,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_entry_haoma),
        1,line,1,1, TRUE , TRUE , TRUE,TRUE);
    line++ ;

    window->prv->m_label_cuoshi = gtk_label_new(get_const_str(155));
    gtk_label_set_markup(GTK_LABEL(window->prv->m_label_cuoshi), get_const_str(155));
    gtk_misc_set_alignment(GTK_MISC(window->prv->m_label_cuoshi), 1.0f , 0.5f);
    window->prv->m_entry_cuoshi = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(window->prv->m_entry_cuoshi), 0.0f , 0.5f);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_label_cuoshi),
        0,line,1,1, TRUE , TRUE , TRUE,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_entry_cuoshi),
        1,line,1,1, TRUE , TRUE , TRUE,TRUE);
    line++ ;

    window->prv->m_label_shijian = gtk_label_new(get_const_str(161));
    gtk_label_set_markup(GTK_LABEL(window->prv->m_label_shijian), get_const_str(161));
    gtk_misc_set_alignment(GTK_MISC(window->prv->m_label_shijian), 1.0f , 0.5f);
    bt = gtk_button_new_with_label("");
    window->prv->m_entry_shijian = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(window->prv->m_entry_shijian), 0.0f , 0.5f);
    gtk_button_set_image(GTK_BUTTON(bt),window->prv->m_entry_shijian);
    g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_clicked_time),window);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_label_shijian),
        0,line,1,1, TRUE , TRUE , TRUE,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(bt),
        1,line,1,1, TRUE , TRUE , TRUE,TRUE);
    line++ ;

    window->prv->m_label_shiyou = gtk_label_new(get_const_str(159));
    gtk_label_set_markup(GTK_LABEL(window->prv->m_label_shiyou), get_const_str(159));
    gtk_misc_set_alignment(GTK_MISC(window->prv->m_label_shiyou), 1.0f , 0.5f);
    window->prv->m_entry_shiyou = gtk_vbox_new(FALSE,0);
    window->prv->m_entry_shiyou_table = gtk_vbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(window->prv->m_entry_shiyou),
        GTK_WIDGET(window->prv->m_entry_shiyou_table),TRUE,TRUE,0);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_label_shiyou),
        0,line,1,1, TRUE , TRUE , TRUE,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_entry_shiyou),
        1,line,1,1, TRUE , TRUE , TRUE,TRUE);
    line++ ;

    window->prv->m_label_yiju = gtk_label_new(get_const_str(155));
    gtk_label_set_markup(GTK_LABEL(window->prv->m_label_yiju), get_const_str(155));
    gtk_misc_set_alignment(GTK_MISC(window->prv->m_label_yiju), 1.0f , 0.5f);
    window->prv->m_entry_yiju = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(window->prv->m_entry_yiju), 0.0f , 0.5f);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_label_yiju),
        0,line,1,1, TRUE , TRUE , TRUE,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_entry_yiju),
        1,line,1,1, TRUE , TRUE , TRUE,TRUE);
    line++ ;

    window->prv->m_label_shuoming = gtk_label_new(get_const_str(155));
    gtk_label_set_markup(GTK_LABEL(window->prv->m_label_shuoming), get_const_str(155));
    gtk_misc_set_alignment(GTK_MISC(window->prv->m_label_shuoming), 1.0f , 0.5f);
    window->prv->m_entry_shuoming = gtk_entry_new();
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_label_shuoming),
        0,line,1,1, TRUE , TRUE , TRUE,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_entry_shuoming),
        1,line,1,1, TRUE , TRUE , TRUE,TRUE);
    line++ ;

    sep = gtk_hseparator_new();
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(sep),
        0,line,2,1, TRUE , TRUE , TRUE,TRUE);
    line++ ;

    hbox = gtk_hbox_new(FALSE,0);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(hbox),
        0,line,2,1, TRUE , TRUE , TRUE,TRUE);
    line++ ;

    bt = gtk_button_new_with_label("");
    label = gtk_label_new(get_const_str(166));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(166));
    gtk_button_set_image(GTK_BUTTON(bt),label);
    g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_clicked_cancel),window);
    gtk_box_pack_end(GTK_BOX(hbox),bt,FALSE,FALSE,0);

    bt = gtk_button_new_with_label("");
    label = gtk_label_new(get_const_str(165));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(165));
    gtk_button_set_image(GTK_BUTTON(bt),label);
    g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_clicked_fankui),window);
    gtk_box_pack_end(GTK_BOX(hbox),bt,FALSE,FALSE,0);

    gtk_widget_set_usize(GTK_WIDGET(window), 550,400);
    Cwin_login_set_child((Cwin_login*)window , table);
    Cwin_login_set_min_window((Cwin_login*)window,(Cwin_login *)mg_listWidget); ///< 设置当最小化时显示的窗体
}
//对象析构函数
static void Cwin_show_shishi_inst_finalize(Cwin_show_shishi *window)
{
    G_OBJECT_CLASS(g_type_class_peek(g_type_parent(g_type_from_name("Cwin_show_shishi"))))->finalize(G_OBJECT(window));
}
//对象释放函数
static void Cwin_show_shishi_inst_dispose(Cwin_show_shishi *window)
{
    G_OBJECT_CLASS(g_type_class_peek(g_type_parent(g_type_from_name("Cwin_show_shishi"))))->dispose(G_OBJECT(window));
}

#ifdef USE_GENE_PROPERTY_CODE
static void Cwin_show_shishi_set_property(GObject *object,
        guint  property_id,
        const GValue *value,
        GParamSpec *pspec)
{
    Cwin_show_shishi *window = WIN_SHOW_SHISHI(object);

    UNUSED_VAR(window);

    switch(property_id)
    {
        case WIN_SHOW_SHISHI_CLASS_PROPERTY_NAME:
            //加入设置name到value的代码
            break ;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,pspec);
            break;
    }
}
static void Cwin_show_shishi_get_property(GObject  *object,
        guint property_id,
        GValue *value,
        GParamSpec *pspec)
{
    Cwin_show_shishi *window = WIN_SHOW_SHISHI(object);

    UNUSED_VAR(window);

    switch(property_id)
    {
        case WIN_SHOW_SHISHI_CLASS_PROPERTY_NAME:
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
Cwin_show_shishi* Cwin_show_shishi_new(void)
{
    Cwin_show_shishi* window;
    window = (Cwin_show_shishi*)g_object_new(WIN_SHOW_SHISHI_TYPE,NULL);

    return window;
}

void Cwin_show_shishi_set_organs_data(Cwin_show_shishi *window ,DB_ORGANS_ITEM *item , JC_INFO *info)
{
    char buff[1024] ;

    gtk_label_set_markup(GTK_LABEL(window->prv->m_label_name), get_const_str(151));
    g_snprintf(buff,sizeof(buff),get_const_str(152),item->qymc);
    gtk_label_set_markup(GTK_LABEL(window->prv->m_entry_name), buff);

    gtk_label_set_markup(GTK_LABEL(window->prv->m_label_haoma), get_const_str(153));
    g_snprintf(buff,sizeof(buff),get_const_str(154),item->xydm);
    gtk_label_set_markup(GTK_LABEL(window->prv->m_entry_haoma), buff);

    g_snprintf(buff,sizeof(buff),get_const_str(156),info->measure_name);
    gtk_label_set_markup(GTK_LABEL(window->prv->m_entry_cuoshi), buff);

    {//事由
        guint i ;
        GtkWidget *label ;

        if(window->prv->m_entry_shiyou_table)
        {
            gtk_container_remove(GTK_CONTAINER(window->prv->m_entry_shiyou),
                GTK_WIDGET(window->prv->m_entry_shiyou_table));
        }
        window->prv->m_entry_shiyou_table = gtk_vbox_new(FALSE,0);
        gtk_box_pack_start(GTK_BOX(window->prv->m_entry_shiyou),
            GTK_WIDGET(window->prv->m_entry_shiyou_table),TRUE,TRUE,0);
        for(i=0;i<info->reasons->len ;i++)
        {
            g_snprintf(buff,sizeof(buff),get_const_str(160),i+1,
                &g_array_index(info->reasons,JC_INFO_REASON_ITEM_TYPE,i));
            label = gtk_label_new(buff);
            gtk_label_set_markup(GTK_LABEL(label),buff);
            gtk_misc_set_alignment(GTK_MISC(label), 0.0f , 0.5f);
            gtk_box_pack_start(GTK_BOX(window->prv->m_entry_shiyou_table),label,TRUE,TRUE,0);
        }
    }

    g_snprintf(buff,sizeof(buff),get_const_str(158),info->jc_basis);
    gtk_label_set_markup(GTK_LABEL(window->prv->m_entry_yiju), buff);

    //初始化时间
    {
        char text[128];

        st_time_init_get_current_time(&window->prv->m_shijian);
        st_time_to_year_and_time(&window->prv->m_shijian,text);
        g_snprintf(buff,sizeof(buff),get_const_str(163),text);
        gtk_label_set_markup(GTK_LABEL(window->prv->m_entry_shijian),buff);
    }

    gtk_widget_show_all(GTK_WIDGET(window));
}

//////////////////////////////////////////////////
///
///  私有函数实现
///
///////////////////////////////////////////////////

static void SLOG_clicked_edit_time(ST_TIME* st_time , GtkLabel* label,GtkWindow* parent)
{
    GtkWidget *dlg;
    Cfunc_calendar *ctrl ;
    int ret ;
    char text[128];
    char buff[1024];

    dlg = gtk_dialog_new_with_buttons(get_const_str(162) , NULL, GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT,
                                      GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);

    ctrl = Cfunc_calendar_new();
    Cfunc_calendar_set_time(ctrl, *st_time);
    gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dlg))), GTK_WIDGET(ctrl), TRUE, TRUE, 0);
    gtk_widget_show_all(GTK_WIDGET(dlg));

    gtk_window_set_transient_for(GTK_WINDOW(dlg),GTK_WINDOW(parent));
    gtk_window_set_position(GTK_WINDOW(dlg), GTK_WIN_POS_CENTER_ON_PARENT);

    ret = gtk_dialog_run(GTK_DIALOG(dlg));
    if(ret == GTK_RESPONSE_ACCEPT)
    {
        Cfunc_calendar_get_time(ctrl, st_time);
        st_time_to_year_and_time(st_time,text);
        g_snprintf(buff,sizeof(buff),get_const_str(163),text);
        gtk_label_set_markup(label,buff);
    }

    gtk_widget_destroy(GTK_WIDGET(dlg));
}

static void slog_clicked_time(GtkButton *button, gpointer user_data)
{
    Cwin_show_shishi *window = (Cwin_show_shishi *)user_data ;

    SLOG_clicked_edit_time(&window->prv->m_shijian, 
            GTK_LABEL(window->prv->m_entry_shijian),GTK_WINDOW(window));
}

static void slog_clicked_cancel(GtkButton *button, gpointer user_data)
{
    Cwin_show_shishi *window = (Cwin_show_shishi *)user_data ;
    Cwin_login_do_min_window((Cwin_login *)window);
}

static void slog_clicked_fankui(GtkButton *button, gpointer user_data)
{
}

#ifdef __cplusplus
}
#endif

