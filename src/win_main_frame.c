/////////////////////////////////////////////////////
/// Copyright (C) 2017 Hrsoft Corporation, All rights reserved.
/// @file win_main_frame.c
/// @author �ź��
/// @version 1.0
/// @date 2017-10-18 
/// @brief ������
/////////////////////////////////////////////////////
#include <hrutil/hrutil.h>
#include "win_main_frame.h"
#include "gtk_win.h"
#include "data_calc_util.h"

#ifdef __cplusplus
extern "C" {
#endif

//#define USE_GENE_PROPERTY_CODE ///< ʹ�����������
//#define USE_GENE_SIGNAL_CODE ///< ʹ���ź�
//#define USE_GENE_CLASS_PRIVATE_CODE ///< ʹ���ྲ̬˽�ж���,��Ҫglib2.24���ϰ汾

T_LANGUAGE_STRING sc_usrname = {"  �˺ţ�","User Name:"} ;
T_LANGUAGE_STRING sc_password = {"  ���룺","Password:"} ;
T_LANGUAGE_STRING sc_rem_pass = {" ��ס����","Save password"} ;
T_LANGUAGE_STRING sc_bt_login = {"<span foreground='white' bgcolor='blue' font_desc='12'>  ��¼  </span>","Login"} ;

static const char *mg_error_str ="<span foreground='red' > %s</span>";

//////////////////////////////////////////////////
///
///  ˽�г�Ա���ݽṹ
///
///////////////////////////////////////////////////


//�����˽������
struct _c_win_main_frame_private {
    int m_is_login ;        ///< �Ƿ��ѵ�¼,0:δ��¼

    GtkWidget *m_child_table ;
    //��¼����
    GtkWidget *m_en_usrname ;
    GtkWidget *m_en_password ;
    GtkWidget *m_ck_rem_pass ;  ///< ��ס�û���������
    GtkWidget *m_label_error_str ;
    //ͳ�ƽ���
    GtkWidget *m_label_organs_all ;
    GtkWidget *m_label_organs_shishi ;
    GtkWidget *m_label_person_all ;
    GtkWidget *m_label_person_shishi ;
    GtkWidget *m_en_search ;
};

#define  WIN_MAIN_FRAME_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj),WIN_MAIN_FRAME_TYPE,Cwin_main_frame_private))

#ifdef USE_GENE_CLASS_PRIVATE_CODE

//��Ĺ���˽������
typedef struct _c_win_main_frame_class_private {
    int pri;
}Cwin_main_frame_class_private;

#define WIN_MAIN_FRAME_CLASS_GET_PRIVATE(klass) (G_TYPE_CLASS_GET_PRIVATE((klass),WIN_MAIN_FRAME_TYPE,Cwin_main_frame_class_private))

#endif //USE_GENE_CLASS_PRIVATE_CODE

#ifdef USE_GENE_PROPERTY_CODE
///�����ԣ����������ԵĲ��裺
///    1.�ڴ˴�����һ�����Ե�ENUM��
///    2.��class_init��������������ע�ắ��
///    3.��get_property/set_property���������ԵĶ�/д����
///    4.��.h������˵���Ա��û�ʹ��
enum {
    WIN_MAIN_FRAME_CLASS_PROPERTY_0,///<����ʹ��
    WIN_MAIN_FRAME_CLASS_PROPERTY_NAME,
    WIN_MAIN_FRAME_CLASS_N_PROPERTYS
};
#endif

#ifdef USE_GENE_SIGNAL_CODE
/// �źţ������źŵĲ��裺
///    1.�ڴ˴�����һ���źŵ�ENUM��
///    2.��class_init�����������ź�ע�ắ��
///    3.�ڲ����źŵĵط�ʹ��g_signal_emit�����ź�
///    4.��.h������˵���Ա��û�ʹ��
enum {
    WIN_MAIN_FRAME_SIGNAL_FIRST_SIG,
    WIN_MAIN_FRAME_SIGNAL_SIG_LAST
};
static int mg_signal[WIN_MAIN_FRAME_SIGNAL_SIG_LAST]={0};
#endif

//////////////////////////////////////////////////
///
/// ˽�к���
///
///////////////////////////////////////////////////
static void Cwin_main_frame_base_init(Cwin_main_frameClass *windowClass);
static void Cwin_main_frame_base_finalize(Cwin_main_frameClass *windowClass);
static void Cwin_main_frame_class_init(Cwin_main_frameClass *windowClass,gpointer class_data);
static void Cwin_main_frame_class_finalize(Cwin_main_frameClass *windowClass,gpointer class_data);
static void Cwin_main_frame_inst_init(Cwin_main_frame *window);
static void Cwin_main_frame_inst_finalize(Cwin_main_frame *window);
static void Cwin_main_frame_inst_dispose(Cwin_main_frame *window);

#ifdef USE_GENE_PROPERTY_CODE
static void Cwin_main_frame_set_property(GObject *object,
        guint  property_id,
        const GValue *value,
        GParamSpec  *pspec);
static void Cwin_main_frame_get_property(GObject *object,
        guint  property_id,
        GValue *value,
        GParamSpec *pspec);
#endif

static void slog_bt_login(GtkButton *button, gpointer   user_data) ;
static void slog_search_activate(GtkEntry *button, gpointer   user_data) ;
static void slog_icon_press(GtkEntry            *entry,
    GtkEntryIconPosition icon_pos,
    GdkEvent            *event,
    gpointer             user_data) ;

static void slog_bt_organs_all(GtkButton *button, gpointer   user_data) ;
static void slog_bt_organs_shishi(GtkButton *button, gpointer   user_data) ;
static void slog_bt_person_all(GtkButton *button, gpointer   user_data) ;
static void slog_bt_person_shishi(GtkButton *button, gpointer   user_data) ;
//////////////////////////////////////////////////
///
///  ���������ʵ��
///
///////////////////////////////////////////////////

//���ɶ������ID��ʶ
GType Cwin_main_frame_type(void)
{
    static GType window_type=0;
    if(!window_type)
    {
        static const GTypeInfo window_info = {
            sizeof(Cwin_main_frameClass),
            (GBaseInitFunc)Cwin_main_frame_base_init,
            (GBaseFinalizeFunc)Cwin_main_frame_base_finalize,

            (GClassInitFunc)Cwin_main_frame_class_init,
            NULL,

            //(GClassFinalizeFunc)Cwin_main_frame_class_finalize,
            NULL,

            sizeof(Cwin_main_frame),0,
            (GInstanceInitFunc)Cwin_main_frame_inst_init
        };
        window_type = g_type_register_static(WIN_LOGIN_TYPE ,"Cwin_main_frame",&window_info,0);

#ifdef USE_GENE_CLASS_PRIVATE_CODE
        g_type_add_class_private(window_type,sizeof(Cwin_main_frame_class_private));
#endif
    }
    return window_type;
}

static void Cwin_main_frame_base_init(Cwin_main_frameClass *windowClass)
{
    UNUSED_VAR(windowClass);
}
static void Cwin_main_frame_base_finalize(Cwin_main_frameClass *windowClass)
{
    UNUSED_VAR(windowClass);
}

//�๹�캯��
static void Cwin_main_frame_class_init(Cwin_main_frameClass *windowClass,gpointer class_data)
{
    GObjectClass *base_class = G_OBJECT_CLASS(windowClass);
#ifdef USE_GENE_PROPERTY_CODE
    GParamSpec *property = NULL ;
#endif
#ifdef USE_GENE_CLASS_PRIVATE_CODE
    Cwin_main_frame_class_private *p = WIN_MAIN_FRAME_CLASS_GET_PRIVATE(windowClass);
#endif

    UNUSED_VAR(class_data);

    //�������˽������
    g_type_class_add_private(windowClass,sizeof(Cwin_main_frame_private));
    //��ʼ���ຯ��
    base_class->dispose = (void(*)(GObject *object))Cwin_main_frame_inst_dispose ;
    base_class->finalize = (void(*)(GObject *object))Cwin_main_frame_inst_finalize;

#ifdef USE_GENE_PROPERTY_CODE
    base_class->set_property = Cwin_main_frame_set_property;
    base_class->get_property = Cwin_main_frame_get_property;

    //ע������
    property = g_param_spec_string("name","Name","The Attr Name",NULL,G_PARAM_READWRITE);
    g_object_class_install_property(base_class,WIN_MAIN_FRAME_CLASS_PROPERTY_NAME,property);
#endif

#ifdef USE_GENE_SIGNAL_CODE
    //ע���ź�
    mg_signal[WIN_MAIN_FRAME_SIGNAL_FIRST_SIG] = g_signal_new("first_sig",
            G_TYPE_FROM_CLASS(windowClass),
            G_SIGNAL_RUN_FIRST,
            0,NULL,NULL,g_cclosure_marshal_VOID__VOID,
            G_TYPE_NONE,0,NULL);
    //��Ҫ�����ź�ʱ��ʹ�� g_signal_emit(G_OBJECT(window), mg_signal[WIN_MAIN_FRAME_SIGNAL_FIRST_SIG], 0);�����ź�
#endif
}

//����������
static void Cwin_main_frame_class_finalize(Cwin_main_frameClass *windowClass,gpointer class_data)
{
    UNUSED_VAR(windowClass);
    UNUSED_VAR(class_data);
}

#define UPDATE_ENTRY(entry,str,value) \
    do { \
        g_snprintf(buff,sizeof(buff),str,value); \
        gtk_label_set_label(GTK_LABEL(entry),buff); \
        gtk_label_set_markup(GTK_LABEL(entry),buff); \
    }while(0)

static void update_stat(Cwin_main_frame *window)
{
    char buff[256];
    if(window)
    {
        if(window->prv->m_is_login)
        {
            UPDATE_ENTRY(window->prv->m_label_organs_all, get_const_str(15), mg_htxy_global.stat_organs_all);
            UPDATE_ENTRY(window->prv->m_label_organs_shishi, get_const_str(16), mg_htxy_global.stat_organs_shishi);
            UPDATE_ENTRY(window->prv->m_label_person_all, get_const_str(15), mg_htxy_global.stat_person_all);
            UPDATE_ENTRY(window->prv->m_label_person_shishi , get_const_str(16), mg_htxy_global.stat_person_shishi);

            gtk_widget_show_all(GTK_WIDGET(window));
        }
    }
}

static void switch_view(Cwin_main_frame *window, int is_login )
{
    GtkWidget *label ;
    GtkWidget *bt ;
    GdkPixbuf *bf; 
    char path[256];
    char exe_path[256];
    GtkWidget *frame ;

    if(is_login == window->prv->m_is_login )
    {
        return ;
    }
    hrutil_get_exe_dir(exe_path);

    window->prv->m_is_login = is_login ;
    Cwin_login_clean_child((Cwin_login*)window);

    if(is_login==0)
    {
        window->prv->m_child_table = GTK_WIDGET(Cgtk_grid_table_new());
        
        label = gtk_label_new(LOCAL_STRING(sc_usrname));
        window->prv->m_en_usrname = gtk_entry_new();
        g_snprintf(path,sizeof(path),"%simage/usr.png",exe_path);
        gtk_entry_set_text(GTK_ENTRY(window->prv->m_en_usrname),"gonganju");
        bf = gdk_pixbuf_new_from_file(path,NULL);
        if(bf)
        {
            gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(window->prv->m_en_usrname),GTK_ENTRY_ICON_SECONDARY,bf);
            gtk_entry_set_icon_activatable(GTK_ENTRY(window->prv->m_en_usrname),GTK_ENTRY_ICON_SECONDARY,FALSE);
            g_object_unref(G_OBJECT(bf));
        }
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_child_table),GTK_WIDGET(label),
            0,0,1,1, FALSE, TRUE , FALSE,TRUE);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_child_table),GTK_WIDGET(window->prv->m_en_usrname),
            1,0,1,1, TRUE, TRUE , TRUE,TRUE);

        label = gtk_label_new(LOCAL_STRING(sc_password));
        window->prv->m_en_password = gtk_entry_new();
        g_snprintf(path,sizeof(path),"%simage/password.png",exe_path);
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
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_child_table),GTK_WIDGET(label),
            0,1,1,1, FALSE, TRUE , FALSE,TRUE);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_child_table),GTK_WIDGET(window->prv->m_en_password),
            1,1,1,1, TRUE, TRUE , TRUE,TRUE);

        window->prv->m_ck_rem_pass = gtk_check_button_new_with_label(LOCAL_STRING(sc_rem_pass));
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(window->prv->m_ck_rem_pass),TRUE);
        bt = gtk_button_new_with_label("   ");
        label = gtk_label_new(LOCAL_STRING(sc_bt_login));
        gtk_label_set_markup(GTK_LABEL(label),LOCAL_STRING(sc_bt_login));
        gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(label));
        g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_login),window);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_child_table),GTK_WIDGET(window->prv->m_ck_rem_pass),
            0,2,2,1, TRUE , TRUE , TRUE ,TRUE);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_child_table),GTK_WIDGET(bt),
            2,2,1,1, FALSE, TRUE , FALSE,TRUE);

        window->prv->m_label_error_str = gtk_label_new("");
        gtk_misc_set_alignment(GTK_MISC(window->prv->m_label_error_str), 0.1f , 0.5f);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_child_table),GTK_WIDGET(window->prv->m_label_error_str),
            0,3,3,1, TRUE , FALSE , TRUE ,FALSE);

        Cwin_login_set_child((Cwin_login*)window , window->prv->m_child_table);
        gtk_widget_show_all(GTK_WIDGET(window));
    }
    else
    {
        window->prv->m_child_table = GTK_WIDGET(Cgtk_grid_table_new());

        gtk_grid_table_set_col_spacings(GTK_GRID_TABLE(window->prv->m_child_table), 10);
        gtk_grid_table_set_row_spacings(GTK_GRID_TABLE(window->prv->m_child_table), 10);

        {//����
            Cgtk_grid_table *table ;

            frame = gtk_frame_new(NULL);
            table = Cgtk_grid_table_new();
            gtk_container_add(GTK_CONTAINER(frame),GTK_WIDGET(table));
            Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_child_table),GTK_WIDGET(frame),
                0,0,1,1, TRUE , TRUE , TRUE ,TRUE);

            label = gtk_label_new(get_const_str(11));
            gtk_label_set_markup(GTK_LABEL(label),get_const_str(11));
            gtk_misc_set_alignment(GTK_MISC(label), 0.1f , 0.5f);
            Cgtk_grid_table_attach(table,label, 0,0,2,1, TRUE , TRUE , TRUE ,TRUE);

            label = gtk_label_new(get_const_str(13));
            gtk_label_set_markup(GTK_LABEL(label),get_const_str(13));
            gtk_misc_set_alignment(GTK_MISC(label), 0.1f , 0.5f);
            window->prv->m_label_organs_all = gtk_label_new("   ");
            bt = gtk_button_new_with_label("      ");
            gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(window->prv->m_label_organs_all));
            g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_organs_all),window);
            Cgtk_grid_table_attach(table,label, 0,1,1,1, TRUE , TRUE , TRUE ,TRUE);
            Cgtk_grid_table_attach(table,bt, 1,1,1,1, TRUE , TRUE , TRUE ,TRUE);

            label = gtk_label_new(get_const_str(14));
            gtk_label_set_markup(GTK_LABEL(label),get_const_str(14));
            gtk_misc_set_alignment(GTK_MISC(label), 0.1f , 0.5f);
            window->prv->m_label_organs_shishi = gtk_label_new("   ");
            bt = gtk_button_new_with_label("      ");
            gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(window->prv->m_label_organs_shishi));
            g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_organs_shishi),window);
            Cgtk_grid_table_attach(table,label, 0,2,1,1, TRUE , TRUE , TRUE ,TRUE);
            Cgtk_grid_table_attach(table,bt, 1,2,1,1, TRUE , TRUE , TRUE ,TRUE);
        }
        {//��Ȼ��
            Cgtk_grid_table *table ;

            frame = gtk_frame_new(NULL);
            table = Cgtk_grid_table_new();
            gtk_container_add(GTK_CONTAINER(frame),GTK_WIDGET(table));
            Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_child_table),GTK_WIDGET(frame),
                1,0,1,1, TRUE , TRUE , TRUE ,TRUE);

            label = gtk_label_new(get_const_str(12));
            gtk_label_set_markup(GTK_LABEL(label),get_const_str(12));
            gtk_misc_set_alignment(GTK_MISC(label), 0.1f , 0.5f);
            Cgtk_grid_table_attach(table,label, 0,0,2,1, TRUE , TRUE , TRUE ,TRUE);

            label = gtk_label_new(get_const_str(13));
            gtk_label_set_markup(GTK_LABEL(label),get_const_str(13));
            gtk_misc_set_alignment(GTK_MISC(label), 0.1f , 0.5f);
            window->prv->m_label_person_all = gtk_label_new("   ");
            bt = gtk_button_new_with_label("      ");
            gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(window->prv->m_label_person_all));
            g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_person_all),window);
            Cgtk_grid_table_attach(table,label, 0,1,1,1, TRUE , TRUE , TRUE ,TRUE);
            Cgtk_grid_table_attach(table,bt, 1,1,1,1, TRUE , TRUE , TRUE ,TRUE);

            label = gtk_label_new(get_const_str(14));
            gtk_label_set_markup(GTK_LABEL(label),get_const_str(14));
            gtk_misc_set_alignment(GTK_MISC(label), 0.1f , 0.5f);
            window->prv->m_label_person_shishi = gtk_label_new("   ");
            bt = gtk_button_new_with_label("      ");
            gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(window->prv->m_label_person_shishi));
            g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_person_shishi),window);
            Cgtk_grid_table_attach(table,label, 0,2,1,1, TRUE , TRUE , TRUE ,TRUE);
            Cgtk_grid_table_attach(table,bt, 1,2,1,1, TRUE , TRUE , TRUE ,TRUE);
        }

        window->prv->m_en_search = gtk_entry_new();
        {
            g_snprintf(path,sizeof(path),"%simage/search.png",exe_path);
            bf = gdk_pixbuf_new_from_file(path,NULL);
            if(bf)
            {
                gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(window->prv->m_en_search),GTK_ENTRY_ICON_SECONDARY,bf);
                gtk_entry_set_icon_activatable(GTK_ENTRY(window->prv->m_en_search),GTK_ENTRY_ICON_SECONDARY,TRUE);
                g_signal_connect(G_OBJECT(window->prv->m_en_search),"icon-press",G_CALLBACK(slog_icon_press),window);
                g_object_unref(G_OBJECT(bf));
            }
        }
        gtk_widget_set_size_request(GTK_WIDGET(window->prv->m_en_search),-1,40);
        gtk_entry_set_activates_default(GTK_ENTRY(window->prv->m_en_search),TRUE);
        g_signal_connect(G_OBJECT(window->prv->m_en_search),"activate",G_CALLBACK(slog_search_activate),window);
        Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_child_table),GTK_WIDGET(window->prv->m_en_search),
            0,1,2,1, TRUE , TRUE , TRUE ,TRUE);
        update_stat(window);

        Cwin_login_set_child((Cwin_login*)window , window->prv->m_child_table);
        gtk_widget_show_all(GTK_WIDGET(window));
        gtk_widget_grab_default(GTK_WIDGET(window->prv->m_en_search));
    }
    
}

//�����캯��
static void Cwin_main_frame_inst_init(Cwin_main_frame *window)
{
    window->prv = WIN_MAIN_FRAME_GET_PRIVATE(window);

    gtk_widget_set_usize(GTK_WIDGET(window), 550,400);
    window->prv->m_is_login = -1 ;
    switch_view(window, 1);
}
//������������
static void Cwin_main_frame_inst_finalize(Cwin_main_frame *window)
{
    G_OBJECT_CLASS(g_type_class_peek(g_type_parent(g_type_from_name("Cwin_main_frame"))))->finalize(G_OBJECT(window));
}
//�����ͷź���
static void Cwin_main_frame_inst_dispose(Cwin_main_frame *window)
{
    G_OBJECT_CLASS(g_type_class_peek(g_type_parent(g_type_from_name("Cwin_main_frame"))))->dispose(G_OBJECT(window));
}

#ifdef USE_GENE_PROPERTY_CODE
static void Cwin_main_frame_set_property(GObject *object,
        guint  property_id,
        const GValue *value,
        GParamSpec *pspec)
{
    Cwin_main_frame *window = WIN_MAIN_FRAME(object);

    UNUSED_VAR(window);

    switch(property_id)
    {
        case WIN_MAIN_FRAME_CLASS_PROPERTY_NAME:
            //��������name��value�Ĵ���
            break ;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,pspec);
            break;
    }
}
static void Cwin_main_frame_get_property(GObject  *object,
        guint property_id,
        GValue *value,
        GParamSpec *pspec)
{
    Cwin_main_frame *window = WIN_MAIN_FRAME(object);

    UNUSED_VAR(window);

    switch(property_id)
    {
        case WIN_MAIN_FRAME_CLASS_PROPERTY_NAME:
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
Cwin_main_frame* Cwin_main_frame_new(void)
{
    Cwin_main_frame* window;
    window = (Cwin_main_frame*)g_object_new(WIN_MAIN_FRAME_TYPE,NULL);

    return window;
}

void Cwin_main_frame_update(Cwin_main_frame* window)
{
    update_stat(window);
}

//////////////////////////////////////////////////
///
///  ˽�к���ʵ��
///
///////////////////////////////////////////////////

static void slog_bt_login(GtkButton *button, gpointer   user_data) 
{
    Cwin_main_frame *window = (Cwin_main_frame *)user_data ;

    const char* usrname ;
    const char* password ;
    char *msg ;
    char buff[2056];

    usrname = gtk_entry_get_text(GTK_ENTRY(window->prv->m_en_usrname));
    password = gtk_entry_get_text(GTK_ENTRY(window->prv->m_en_password));

    msg = user_login(usrname , password);
    if(msg != NULL)
    {
        g_snprintf(buff,sizeof(buff),mg_error_str,msg);
        gtk_label_set_text(GTK_LABEL(window->prv->m_label_error_str),buff);
        gtk_label_set_markup(GTK_LABEL(window->prv->m_label_error_str),buff);
        gtk_widget_show_all(GTK_WIDGET(window));
        g_free(msg);
    }
    else
    {
        switch_view(window,1);
    }
}

static void slog_search_activate(GtkEntry *button, gpointer   user_data) 
{
    Cwin_main_frame *window = (Cwin_main_frame *)user_data ;

    const char* text ;

    text = gtk_entry_get_text(GTK_ENTRY(window->prv->m_en_search));

    if(info_find_user(text))
    {
        widget_update_and_show_info();
    }
}

static void slog_icon_press(GtkEntry            *entry,
    GtkEntryIconPosition icon_pos,
    GdkEvent            *event,
    gpointer             user_data)
{
    slog_search_activate(entry, user_data) ;
}

static void slog_bt_organs_all(GtkButton *button, gpointer   user_data)
{
    widget_show_list_window_with_type(1);
}

static void slog_bt_organs_shishi(GtkButton *button, gpointer   user_data) 
{
    widget_show_list_window_with_type(2);
}
static void slog_bt_person_all(GtkButton *button, gpointer   user_data) 
{
    widget_show_list_window_with_type(3);
}
static void slog_bt_person_shishi(GtkButton *button, gpointer   user_data) 
{
    widget_show_list_window_with_type(4);
}

#ifdef __cplusplus
}
#endif

