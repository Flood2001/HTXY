/////////////////////////////////////////////////////
/// Copyright (C) 2017 Hrsoft Corporation, All rights reserved.
/// @file win_show_info.c
/// @author �ź��
/// @version 1.0
/// @date 2017-10-18 
/// @brief ��ʾ��ѯ������Ϣ
/////////////////////////////////////////////////////
#include <hrutil/hrutil.h>
#include "win_show_info.h"
#include "gtk_win.h"

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

T_LANGUAGE_STRING sc_jianglixinxi = {"<span foreground='black' font_desc='15'>������Ϣ</span>","ChengJie"} ;
T_LANGUAGE_STRING sc_chengjiexinxi = {"<span foreground='black' font_desc='15'>�ͽ���Ϣ</span>","ChengJie"} ;
static const char *mg_name_str ="<span foreground='#606000' font_desc='18'>%s</span>";
static const char *mg_jiangli_str ="<span foreground='white' bgcolor='#007000' font_desc='15'> %d </span>";
static const char *mg_chengjie_str="<span foreground='white' bgcolor='red' font_desc='15'> %d </span>";

//�����˽������
struct _c_win_show_info_private {
    GtkWidget *m_label_name ;
    GtkWidget *m_label_jiangli ;
    GtkWidget *m_label_chengjie ;
};

#define  WIN_SHOW_INFO_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj),WIN_SHOW_INFO_TYPE,Cwin_show_info_private))

#ifdef USE_GENE_CLASS_PRIVATE_CODE

//��Ĺ���˽������
typedef struct _c_win_show_info_class_private {
    int pri;
}Cwin_show_info_class_private;

#define WIN_SHOW_INFO_CLASS_GET_PRIVATE(klass) (G_TYPE_CLASS_GET_PRIVATE((klass),WIN_SHOW_INFO_TYPE,Cwin_show_info_class_private))

#endif //USE_GENE_CLASS_PRIVATE_CODE

#ifdef USE_GENE_PROPERTY_CODE
///�����ԣ����������ԵĲ��裺
///    1.�ڴ˴�����һ�����Ե�ENUM��
///    2.��class_init��������������ע�ắ��
///    3.��get_property/set_property���������ԵĶ�/д����
///    4.��.h������˵���Ա��û�ʹ��
enum {
    WIN_SHOW_INFO_CLASS_PROPERTY_0,///<����ʹ��
    WIN_SHOW_INFO_CLASS_PROPERTY_NAME,
    WIN_SHOW_INFO_CLASS_N_PROPERTYS
};
#endif

#ifdef USE_GENE_SIGNAL_CODE
/// �źţ������źŵĲ��裺
///    1.�ڴ˴�����һ���źŵ�ENUM��
///    2.��class_init�����������ź�ע�ắ��
///    3.�ڲ����źŵĵط�ʹ��g_signal_emit�����ź�
///    4.��.h������˵���Ա��û�ʹ��
enum {
    WIN_SHOW_INFO_SIGNAL_FIRST_SIG,
    WIN_SHOW_INFO_SIGNAL_SIG_LAST
};
static int mg_signal[WIN_SHOW_INFO_SIGNAL_SIG_LAST]={0};
#endif

//////////////////////////////////////////////////
///
/// ˽�к���
///
///////////////////////////////////////////////////
static void Cwin_show_info_base_init(Cwin_show_infoClass *windowClass);
static void Cwin_show_info_base_finalize(Cwin_show_infoClass *windowClass);
static void Cwin_show_info_class_init(Cwin_show_infoClass *windowClass,gpointer class_data);
static void Cwin_show_info_class_finalize(Cwin_show_infoClass *windowClass,gpointer class_data);
static void Cwin_show_info_inst_init(Cwin_show_info *window);
static void Cwin_show_info_inst_finalize(Cwin_show_info *window);
static void Cwin_show_info_inst_dispose(Cwin_show_info *window);

#ifdef USE_GENE_PROPERTY_CODE
static void Cwin_show_info_set_property(GObject *object,
        guint  property_id,
        const GValue *value,
        GParamSpec  *pspec);
static void Cwin_show_info_get_property(GObject *object,
        guint  property_id,
        GValue *value,
        GParamSpec *pspec);
#endif

//////////////////////////////////////////////////
///
///  ���������ʵ��
///
///////////////////////////////////////////////////

//���ɶ������ID��ʶ
GType Cwin_show_info_type(void)
{
    static GType window_type=0;
    if(!window_type)
    {
        static const GTypeInfo window_info = {
            sizeof(Cwin_show_infoClass),
            (GBaseInitFunc)Cwin_show_info_base_init,
            (GBaseFinalizeFunc)Cwin_show_info_base_finalize,

            (GClassInitFunc)Cwin_show_info_class_init,
            NULL,

            //(GClassFinalizeFunc)Cwin_show_info_class_finalize,
            NULL,

            sizeof(Cwin_show_info),0,
            (GInstanceInitFunc)Cwin_show_info_inst_init
        };
        window_type = g_type_register_static(WIN_LOGIN_TYPE ,"Cwin_show_info",&window_info,0);

#ifdef USE_GENE_CLASS_PRIVATE_CODE
        g_type_add_class_private(window_type,sizeof(Cwin_show_info_class_private));
#endif
    }
    return window_type;
}

static void Cwin_show_info_base_init(Cwin_show_infoClass *windowClass)
{
    UNUSED_VAR(windowClass);
}
static void Cwin_show_info_base_finalize(Cwin_show_infoClass *windowClass)
{
    UNUSED_VAR(windowClass);
}

//�๹�캯��
static void Cwin_show_info_class_init(Cwin_show_infoClass *windowClass,gpointer class_data)
{
    GObjectClass *base_class = G_OBJECT_CLASS(windowClass);
#ifdef USE_GENE_PROPERTY_CODE
    GParamSpec *property = NULL ;
#endif
#ifdef USE_GENE_CLASS_PRIVATE_CODE
    Cwin_show_info_class_private *p = WIN_SHOW_INFO_CLASS_GET_PRIVATE(windowClass);
#endif

    UNUSED_VAR(class_data);

    //�������˽������
    g_type_class_add_private(windowClass,sizeof(Cwin_show_info_private));
    //��ʼ���ຯ��
    base_class->dispose = (void(*)(GObject *object))Cwin_show_info_inst_dispose ;
    base_class->finalize = (void(*)(GObject *object))Cwin_show_info_inst_finalize;

#ifdef USE_GENE_PROPERTY_CODE
    base_class->set_property = Cwin_show_info_set_property;
    base_class->get_property = Cwin_show_info_get_property;

    //ע������
    property = g_param_spec_string("name","Name","The Attr Name",NULL,G_PARAM_READWRITE);
    g_object_class_install_property(base_class,WIN_SHOW_INFO_CLASS_PROPERTY_NAME,property);
#endif

#ifdef USE_GENE_SIGNAL_CODE
    //ע���ź�
    mg_signal[WIN_SHOW_INFO_SIGNAL_FIRST_SIG] = g_signal_new("first_sig",
            G_TYPE_FROM_CLASS(windowClass),
            G_SIGNAL_RUN_FIRST,
            0,NULL,NULL,g_cclosure_marshal_VOID__VOID,
            G_TYPE_NONE,0,NULL);
    //��Ҫ�����ź�ʱ��ʹ�� g_signal_emit(G_OBJECT(window), mg_signal[WIN_SHOW_INFO_SIGNAL_FIRST_SIG], 0);�����ź�
#endif
}

//����������
static void Cwin_show_info_class_finalize(Cwin_show_infoClass *windowClass,gpointer class_data)
{
    UNUSED_VAR(windowClass);
    UNUSED_VAR(class_data);
}

static void update_stat(Cwin_show_info *window)
{
    char buff[256];

    g_snprintf(buff,sizeof(buff),mg_name_str,mg_htxy_global.info_name);
    gtk_label_set_label(GTK_LABEL(window->prv->m_label_name),buff);
    gtk_label_set_markup(GTK_LABEL(window->prv->m_label_name),buff);
    g_snprintf(buff,sizeof(buff),mg_jiangli_str,mg_htxy_global.info_jiangli);
    gtk_label_set_label(GTK_LABEL(window->prv->m_label_jiangli),buff);
    gtk_label_set_markup(GTK_LABEL(window->prv->m_label_jiangli),buff);
    g_snprintf(buff,sizeof(buff),mg_chengjie_str,mg_htxy_global.info_chengjie);
    gtk_label_set_label(GTK_LABEL(window->prv->m_label_chengjie),buff);
    gtk_label_set_markup(GTK_LABEL(window->prv->m_label_chengjie),buff);
    gtk_widget_show_all(GTK_WIDGET(window));
}

//�����캯��
static void Cwin_show_info_inst_init(Cwin_show_info *window)
{
    GtkWidget *label ;
    GtkWidget *bt ;
    GtkWidget *table ;
    char path[256];
    char exe_path[256];
    GtkWidget *hbox ;
    GtkWidget *img_info ;
    GtkWidget *f ;

    window->prv = WIN_SHOW_INFO_GET_PRIVATE(window);

    table = GTK_WIDGET(Cgtk_grid_table_new());

    hrutil_get_exe_dir(exe_path);
    g_snprintf(path,sizeof(path),"%simage/warnning.png",exe_path);
    hbox = gtk_hbox_new(FALSE,10);
    img_info = gtk_image_new_from_file(path);
    label = gtk_label_new(" ");
    window->prv->m_label_name = gtk_label_new("");
    gtk_misc_set_alignment(GTK_MISC(window->prv->m_label_name), 0.1f , 0.5f);
    gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox),img_info,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox),window->prv->m_label_name,TRUE,TRUE,0);
    f = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(f),hbox);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(f),
        0,0,4,1, TRUE , TRUE , TRUE,TRUE);

    label = gtk_label_new(LOCAL_STRING(sc_jianglixinxi));
    gtk_label_set_markup(GTK_LABEL(label),LOCAL_STRING(sc_jianglixinxi));
    gtk_misc_set_alignment(GTK_MISC(label), 0.1f , 0.5f);
    window->prv->m_label_jiangli = gtk_label_new("   ");
    bt = gtk_button_new_with_label("      ");
    gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(window->prv->m_label_jiangli));
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(label),
        0,1,3,1, TRUE , TRUE , TRUE ,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),bt,
        3,1,1,1, TRUE , TRUE , TRUE ,TRUE);

    label = gtk_label_new(LOCAL_STRING(sc_chengjiexinxi));
    gtk_label_set_markup(GTK_LABEL(label),LOCAL_STRING(sc_chengjiexinxi));
    gtk_misc_set_alignment(GTK_MISC(label), 0.1f , 0.5f);
    window->prv->m_label_chengjie = gtk_label_new("   ");
    bt = gtk_button_new_with_label("      ");
    gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(window->prv->m_label_chengjie));
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),GTK_WIDGET(label),
        0,2,3,1, TRUE , TRUE , TRUE ,TRUE);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(table),bt,
        3,2,1,1, TRUE , TRUE , TRUE ,TRUE);

    update_stat(window);
    gtk_widget_set_usize(GTK_WIDGET(window), 500,300);
    Cwin_login_set_child((Cwin_login*)window , table);
}
//������������
static void Cwin_show_info_inst_finalize(Cwin_show_info *window)
{
    G_OBJECT_CLASS(g_type_class_peek(g_type_parent(g_type_from_name("Cwin_show_info"))))->finalize(G_OBJECT(window));
}
//�����ͷź���
static void Cwin_show_info_inst_dispose(Cwin_show_info *window)
{
    G_OBJECT_CLASS(g_type_class_peek(g_type_parent(g_type_from_name("Cwin_show_info"))))->dispose(G_OBJECT(window));
}

#ifdef USE_GENE_PROPERTY_CODE
static void Cwin_show_info_set_property(GObject *object,
        guint  property_id,
        const GValue *value,
        GParamSpec *pspec)
{
    Cwin_show_info *window = WIN_SHOW_INFO(object);

    UNUSED_VAR(window);

    switch(property_id)
    {
        case WIN_SHOW_INFO_CLASS_PROPERTY_NAME:
            //��������name��value�Ĵ���
            break ;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,pspec);
            break;
    }
}
static void Cwin_show_info_get_property(GObject  *object,
        guint property_id,
        GValue *value,
        GParamSpec *pspec)
{
    Cwin_show_info *window = WIN_SHOW_INFO(object);

    UNUSED_VAR(window);

    switch(property_id)
    {
        case WIN_SHOW_INFO_CLASS_PROPERTY_NAME:
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
Cwin_show_info* Cwin_show_info_new(void)
{
    Cwin_show_info* window;
    window = (Cwin_show_info*)g_object_new(WIN_SHOW_INFO_TYPE,NULL);

    return window;
}

void Cwin_show_info_updata_info(Cwin_show_info *window)
{
    update_stat(window);
}

//////////////////////////////////////////////////
///
///  ˽�к���ʵ��
///
///////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

