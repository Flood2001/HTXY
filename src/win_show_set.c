/////////////////////////////////////////////////////
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

T_LANGUAGE_STRING sc_url = {"<span weight='bold' font_desc='12'> �����ַ��</span>","Name:"} ;
T_LANGUAGE_STRING sc_web = {"<span weight='bold' font_desc='12'> ƽ̨��ַ��</span>","Name:"} ;
T_LANGUAGE_STRING sc_tongbu = {"<span weight='bold' font_desc='12'> ����ͬ����</span>","Name:"} ;
T_LANGUAGE_STRING sc_bt_liji = {"<span weight='bold' foreground='#0000C0' font_desc='12'> ����ͬ�� </span>","Name:"} ;
T_LANGUAGE_STRING sc_bt_update = {"<span foreground='white' bgcolor='#00C000' font_desc='12'> �������� </span>","Name:"} ;

//�����˽������
struct _c_win_show_set_private {
    GtkWidget *m_en_url ;
    GtkWidget *m_en_web ;
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
    g_snprintf(buff,sizeof(buff),"%d",mg_htxy_global.listenser_delay);
    gtk_entry_set_text(GTK_ENTRY(window->prv->m_en_delay),buff);
}

//�����캯��
static void Cwin_show_set_inst_init(Cwin_show_set *window)
{
    GtkWidget *label ;
    GtkWidget *bt ;
    GtkWidget *table ;
    int line = 0 ;

    window->prv = WIN_SHOW_SET_GET_PRIVATE(window);

    table = GTK_WIDGET(Cgtk_grid_table_new());

    // url
    label = gtk_label_new(LOCAL_STRING(sc_url));
    gtk_label_set_markup(GTK_LABEL(label),LOCAL_STRING(sc_url));
    gtk_misc_set_alignment(GTK_MISC(label), 0.0f , 0.5f);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(label),
        0,line,2,1, TRUE, TRUE , TRUE,TRUE);
    line++ ;

    window->prv->m_en_url = gtk_entry_new();
    bt = gtk_button_new_with_label("   ");
    label = gtk_label_new(LOCAL_STRING(sc_bt_update));
    gtk_label_set_markup(GTK_LABEL(label),LOCAL_STRING(sc_bt_update));
    gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(label));
    g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_update_utl),window);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_en_url),
        0,line,1,1, TRUE , TRUE , TRUE ,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(bt),
        1,line,1,1, FALSE, TRUE , FALSE,TRUE);
    line++ ;

    // web
    label = gtk_label_new(LOCAL_STRING(sc_web));
    gtk_label_set_markup(GTK_LABEL(label),LOCAL_STRING(sc_web));
    gtk_misc_set_alignment(GTK_MISC(label), 0.0f , 0.5f);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(label),
        0,line,2,1, TRUE, TRUE , TRUE,TRUE);
    line++ ;

    window->prv->m_en_web = gtk_entry_new();
    bt = gtk_button_new_with_label("   ");
    label = gtk_label_new(LOCAL_STRING(sc_bt_update));
    gtk_label_set_markup(GTK_LABEL(label),LOCAL_STRING(sc_bt_update));
    gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(label));
    g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_update_utl),window);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_en_web),
        0,line,1,1, TRUE , TRUE , TRUE ,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(bt),
        1,line,1,1, FALSE, TRUE , FALSE,TRUE);
    line++ ;

    // delay
    label = gtk_label_new(LOCAL_STRING(sc_tongbu));
    gtk_label_set_markup(GTK_LABEL(label),LOCAL_STRING(sc_tongbu));
    gtk_misc_set_alignment(GTK_MISC(label), 0.0f , 0.5f);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(label),
        0,line,1,1, TRUE, TRUE , TRUE,TRUE);
    bt = gtk_button_new_with_label("   ");
    label = gtk_label_new(LOCAL_STRING(sc_bt_liji));
    gtk_label_set_markup(GTK_LABEL(label),LOCAL_STRING(sc_bt_liji));
    gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(label));
    g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_clicked_liji),window);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(bt),
        1,line,1,1, FALSE, TRUE , FALSE,TRUE);
    line++ ;

    window->prv->m_en_delay = gtk_entry_new();
    bt = gtk_button_new_with_label("   ");
    label = gtk_label_new(LOCAL_STRING(sc_bt_update));
    gtk_label_set_markup(GTK_LABEL(label),LOCAL_STRING(sc_bt_update));
    gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(label));
    g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_update_utl),window);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(window->prv->m_en_delay),
        0,line,1,1, TRUE , TRUE , TRUE ,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(bt),
        1,line,1,1, FALSE, TRUE , FALSE,TRUE);
    line++ ;

    gtk_widget_set_usize(GTK_WIDGET(window), 400,350);
    Cwin_login_set_child((Cwin_login*)window , GTK_WIDGET(table));
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
    update_organs_db();
}

#ifdef __cplusplus
}
#endif

