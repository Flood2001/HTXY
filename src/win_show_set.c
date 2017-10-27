////////////////////////////////////////////////////
/// Copyright (C) 2017 Hrsoft Corporation, All rights reserved.
/// @file win_show_set.c
/// @author �ź��
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

//#define USE_GENE_PROPERTY_CODE ///< ʹ�����������
//#define USE_GENE_SIGNAL_CODE ///< ʹ���ź�
//#define USE_GENE_CLASS_PRIVATE_CODE ///< ʹ���ྲ̬˽�ж���,��Ҫglib2.24���ϰ汾

//////////////////////////////////////////////////
///
///  ˽�г�Ա���ݽṹ
///
///////////////////////////////////////////////////

T_LANGUAGE_STRING sc_tongbu = {"<span weight='bold' font_desc='12'> ����ͬ����</span>","Name:"} ;
T_LANGUAGE_STRING sc_bt_liji = {"<span weight='bold' foreground='#0000C0' font_desc='12'> ����ͬ�� </span>","Name:"} ;

//�����˽������
struct _c_win_show_set_private {
    //�û�
    GtkWidget *m_user_child_frame;

    GtkWidget *m_en_url ;
    GtkWidget *m_en_web ;
    GtkWidget *m_en_app_name;
    GtkWidget *m_ck_auto_sync ;
    GtkWidget *m_ck_faren ;
    GtkWidget *m_ck_ziranren ;
    GtkWidget *m_en_delay ;
};

#define  WIN_SHOW_SET_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj),WIN_SHOW_SET_TYPE,Cwin_show_set_private))

#ifdef USE_GENE_CLASS_PRIVATE_CODE

//��Ĺ���˽������
typedef struct _c_win_show_set_class_private {
    int pri;
}Cwin_show_set_class_private;

#define WIN_SHOW_SET_CLASS_GET_PRIVATE(klass) (G_TYPE_CLASS_GET_PRIVATE((klass),WIN_SHOW_SET_TYPE,Cwin_show_set_class_private))

#endif //USE_GENE_CLASS_PRIVATE_CODE

#ifdef USE_GENE_PROPERTY_CODE
///�����ԣ����������ԵĲ��裺
///    1.�ڴ˴�����һ�����Ե�ENUM��
///    2.��class_init��������������ע�ắ��
///    3.��get_property/set_property���������ԵĶ�/д����
///    4.��.h������˵���Ա��û�ʹ��
enum {
    WIN_SHOW_SET_CLASS_PROPERTY_0,///<����ʹ��
    WIN_SHOW_SET_CLASS_PROPERTY_NAME,
    WIN_SHOW_SET_CLASS_N_PROPERTYS
};
#endif

#ifdef USE_GENE_SIGNAL_CODE
/// �źţ������źŵĲ��裺
///    1.�ڴ˴�����һ���źŵ�ENUM��
///    2.��class_init�����������ź�ע�ắ��
///    3.�ڲ����źŵĵط�ʹ��g_signal_emit�����ź�
///    4.��.h������˵���Ա��û�ʹ��
enum {
    WIN_SHOW_SET_SIGNAL_FIRST_SIG,
    WIN_SHOW_SET_SIGNAL_SIG_LAST
};
static int mg_signal[WIN_SHOW_SET_SIGNAL_SIG_LAST]={0};
#endif

//////////////////////////////////////////////////
///
/// ˽�к���
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
void slog_bt_clicked_liji(GtkButton *button, gpointer   user_data) ;
//////////////////////////////////////////////////
///
///  ���������ʵ��
///
///////////////////////////////////////////////////

//���ɶ������ID��ʶ
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

//�๹�캯��
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

    //�������˽������
    g_type_class_add_private(windowClass,sizeof(Cwin_show_set_private));
    //��ʼ���ຯ��
    base_class->dispose = (void(*)(GObject *object))Cwin_show_set_inst_dispose ;
    base_class->finalize = (void(*)(GObject *object))Cwin_show_set_inst_finalize;

#ifdef USE_GENE_PROPERTY_CODE
    base_class->set_property = Cwin_show_set_set_property;
    base_class->get_property = Cwin_show_set_get_property;

    //ע������
    property = g_param_spec_string("name","Name","The Attr Name",NULL,G_PARAM_READWRITE);
    g_object_class_install_property(base_class,WIN_SHOW_SET_CLASS_PROPERTY_NAME,property);
#endif

#ifdef USE_GENE_SIGNAL_CODE
    //ע���ź�
    mg_signal[WIN_SHOW_SET_SIGNAL_FIRST_SIG] = g_signal_new("first_sig",
            G_TYPE_FROM_CLASS(windowClass),
            G_SIGNAL_RUN_FIRST,
            0,NULL,NULL,g_cclosure_marshal_VOID__VOID,
            G_TYPE_NONE,0,NULL);
    //��Ҫ�����ź�ʱ��ʹ�� g_signal_emit(G_OBJECT(window), mg_signal[WIN_SHOW_SET_SIGNAL_FIRST_SIG], 0);�����ź�
#endif
}

//����������
static void Cwin_show_set_class_finalize(Cwin_show_setClass *windowClass,gpointer class_data)
{
    UNUSED_VAR(windowClass);
    UNUSED_VAR(class_data);
}

static void update_date(Cwin_show_set *window)
{
    char buff[256];

    gtk_entry_set_text(GTK_ENTRY(window->prv->m_en_url),mg_htxy_global.platform_url);
    gtk_entry_set_text(GTK_ENTRY(window->prv->m_en_web),mg_htxy_global.platform_web);
    gtk_entry_set_text(GTK_ENTRY(window->prv->m_en_app_name),mg_htxy_global.platform_name);
    g_snprintf(buff,sizeof(buff),"%d",mg_htxy_global.listenser_delay);
    gtk_entry_set_text(GTK_ENTRY(window->prv->m_en_delay),buff);
}

//�����캯��
static void Cwin_show_set_inst_init(Cwin_show_set *window)
{
    GtkWidget *main_notebook ;
    GtkWidget *sys_table ;  ///< ϵͳ
    GtkWidget *user_table ; ///< �û�
    GtkWidget *param_table ;    ///< ����
    GtkWidget *port_table ;    ///< �ӿ�
    GtkWidget *label ;
    GtkWidget *bt ;
    GtkWidget *frame;
    GtkWidget *sep ;
    GdkPixbuf *bf; 
    GtkWidget *hbox ;
    int line = 0 ;
    char path[256];

    window->prv = WIN_SHOW_SET_GET_PRIVATE(window);

    /// ��NoteBook
    main_notebook = gtk_notebook_new();
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

    /// ϵͳ����
    user_table = GTK_WIDGET(Cgtk_grid_table_new());
    param_table = GTK_WIDGET(Cgtk_grid_table_new());
    gtk_grid_table_set_row_spacings(GTK_GRID_TABLE(sys_table),10);
    gtk_grid_table_set_col_spacings(GTK_GRID_TABLE(sys_table),10);
    gtk_grid_table_set_row_spacings(GTK_GRID_TABLE(user_table),10);
    gtk_grid_table_set_col_spacings(GTK_GRID_TABLE(user_table),10);
    
    frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(frame),user_table);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(sys_table),GTK_WIDGET(frame),
        0,0,1,1, TRUE, TRUE , TRUE,TRUE);
    frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(frame),param_table);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(sys_table),GTK_WIDGET(frame),
        1,0,1,1, TRUE, TRUE , TRUE,TRUE);

    /// �û�
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
    Cgtk_grid_table_attach(GTK_GRID_TABLE(user_table),GTK_WIDGET(frame),
        0,2,1,1, TRUE, TRUE , TRUE,TRUE);


    /// Ӧ�ò���
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

    // Ӧ������
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

    /// ����ͬ��
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

    //��������
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

    //�Զ�ͬ��
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


    gtk_widget_set_usize(GTK_WIDGET(window), 700,600);
    Cwin_login_set_child((Cwin_login*)window , GTK_WIDGET(main_notebook));
    update_date(window);
}

//������������
static void Cwin_show_set_inst_finalize(Cwin_show_set *window)
{
    G_OBJECT_CLASS(g_type_class_peek(g_type_parent(g_type_from_name("Cwin_show_set"))))->finalize(G_OBJECT(window));
}
//�����ͷź���
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
            //��������name��value�Ĵ���
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
            //��������value��name�Ĵ���
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,pspec);
            break;
    }
}
#endif

//////////////////////////////////////////////////
///
///  ���к���ʵ��
///
///////////////////////////////////////////////////

//�½������
Cwin_show_set* Cwin_show_set_new(void)
{
    Cwin_show_set* window;
    window = (Cwin_show_set*)g_object_new(WIN_SHOW_SET_TYPE,NULL);

    return window;
}
//////////////////////////////////////////////////
///
///  ˽�к���ʵ��
///
///////////////////////////////////////////////////

static void slog_bt_update_utl(GtkButton *button, gpointer   user_data)
{
}

static void slog_bt_clicked_liji(GtkButton *button, gpointer   user_data)
{
    update_all_db() ;
}

#ifdef __cplusplus
}
#endif

