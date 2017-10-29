////////////////////////////////////////////////////
/// Copyright (C) 2017 Hrsoft Corporation, All rights reserved.
/// @file win_show_list.c
/// @author �ź��
/// @version 1.0
/// @date 2017-10-18 
/// @brief 
/// @note 
/////////////////////////////////////////////////////
#include <hrutil/hrutil.h>
#include "win_show_list.h"
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

enum {
    COL_TYPE_ORGANS ,
    COL_TYPE_PERSON
};
/// �б���
enum {
    COL_POINTER ,  ///< NMCFG_PLUGIN_TMPT_MANAGER_ITEM_T * 
    COL_TYPE ,     ///< COL_TYPE_ORGANS ,COL_TYPE_PERSON
    COL_INDEX ,

    COL_NUMS ,
};

#define MAX_ON_ONE_PAGE 4

//�����˽������
struct _c_win_show_list_private {
    GtkWidget *m_table ;
    int curr_type ;
    DB_ORGANS_ITEM m_organs_data[MAX_ON_ONE_PAGE] ;
    DB_PERSON_ITEM m_person_data[MAX_ON_ONE_PAGE] ;
    int m_data_count ;
    int m_curr_page ;
    int m_total_page ;
    
    /// 
    int m_table_curr_line ; ///< Table��ǰ��䵽������

    /// 
    GtkTreeView  *m_treeView ;          ///< �б���
    GtkTreeStore *m_treeStore ;
    GdkPixbuf *m_pix_jiang ;
    GdkPixbuf *m_pix_cheng ;
    GdkPixbuf *m_pix_shishi ;
    GdkPixbuf *m_pix_zancun ;
    GdkPixbuf *m_pix_huanyuan ;
    GdkPixbuf *m_pix_shanchu ;
};

#define  WIN_SHOW_LIST_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj),WIN_SHOW_LIST_TYPE,Cwin_show_list_private))

#ifdef USE_GENE_CLASS_PRIVATE_CODE

//��Ĺ���˽������
typedef struct _c_win_show_list_class_private {
    int pri;
}Cwin_show_list_class_private;

#define WIN_SHOW_LIST_CLASS_GET_PRIVATE(klass) (G_TYPE_CLASS_GET_PRIVATE((klass),WIN_SHOW_LIST_TYPE,Cwin_show_list_class_private))

#endif //USE_GENE_CLASS_PRIVATE_CODE

#ifdef USE_GENE_PROPERTY_CODE
///�����ԣ����������ԵĲ��裺
///    1.�ڴ˴�����һ�����Ե�ENUM��
///    2.��class_init��������������ע�ắ��
///    3.��get_property/set_property���������ԵĶ�/д����
///    4.��.h������˵���Ա��û�ʹ��
enum {
    WIN_SHOW_LIST_CLASS_PROPERTY_0,///<����ʹ��
    WIN_SHOW_LIST_CLASS_PROPERTY_NAME,
    WIN_SHOW_LIST_CLASS_N_PROPERTYS
};
#endif

#ifdef USE_GENE_SIGNAL_CODE
/// �źţ������źŵĲ��裺
///    1.�ڴ˴�����һ���źŵ�ENUM��
///    2.��class_init�����������ź�ע�ắ��
///    3.�ڲ����źŵĵط�ʹ��g_signal_emit�����ź�
///    4.��.h������˵���Ա��û�ʹ��
enum {
    WIN_SHOW_LIST_SIGNAL_FIRST_SIG,
    WIN_SHOW_LIST_SIGNAL_SIG_LAST
};
static int mg_signal[WIN_SHOW_LIST_SIGNAL_SIG_LAST]={0};
#endif

//////////////////////////////////////////////////
///
/// ˽�к���
///
///////////////////////////////////////////////////
static void Cwin_show_list_base_init(Cwin_show_listClass *windowClass);
static void Cwin_show_list_base_finalize(Cwin_show_listClass *windowClass);
static void Cwin_show_list_class_init(Cwin_show_listClass *windowClass,gpointer class_data);
static void Cwin_show_list_class_finalize(Cwin_show_listClass *windowClass,gpointer class_data);
static void Cwin_show_list_inst_init(Cwin_show_list *window);
static void Cwin_show_list_inst_finalize(Cwin_show_list *window);
static void Cwin_show_list_inst_dispose(Cwin_show_list *window);

#ifdef USE_GENE_PROPERTY_CODE
static void Cwin_show_list_set_property(GObject *object,
        guint  property_id,
        const GValue *value,
        GParamSpec  *pspec);
static void Cwin_show_list_get_property(GObject *object,
        guint  property_id,
        GValue *value,
        GParamSpec *pspec);
#endif

static void slog_bt_organs_shishi(GtkButton *button, gpointer user_data) ;
static void slog_bt_organs_zancun(GtkButton *button, gpointer user_data) ;
static void slog_bt_organs_huanyuan(GtkButton *button, gpointer user_data) ;
static void slog_bt_organs_shanchu(GtkButton *button, gpointer user_data) ;
static void slog_bt_person_shishi(GtkButton *button, gpointer user_data) ;
static void slog_bt_person_zancun(GtkButton *button, gpointer user_data) ;
static void slog_bt_person_huanyuan(GtkButton *button, gpointer user_data) ;
static void slog_bt_person_shanchu(GtkButton *button, gpointer user_data) ;

static void slog_bt_first(GtkButton *button, gpointer user_data) ;
static void slog_bt_prev(GtkButton *button, gpointer user_data) ;
static void slog_bt_next(GtkButton *button, gpointer user_data) ;
static void slog_bt_end(GtkButton *button, gpointer user_data) ;

static void no_cell_data_func (GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data);
static void pix_cell_data_func (GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data);
static void name_cell_data_func (GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data);
static void pix_shishi_cell_data_func(GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data);
static void pix_zancun_cell_data_func(GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data);
static void pix_huanyuan_cell_data_func(GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data);
static void pix_shanchu_cell_data_func(GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data);
//////////////////////////////////////////////////
///
///  ���������ʵ��
///
///////////////////////////////////////////////////

//���ɶ������ID��ʶ
GType Cwin_show_list_type(void)
{
    static GType window_type=0;
    if(!window_type)
    {
        static const GTypeInfo window_info = {
            sizeof(Cwin_show_listClass),
            (GBaseInitFunc)Cwin_show_list_base_init,
            (GBaseFinalizeFunc)Cwin_show_list_base_finalize,

            (GClassInitFunc)Cwin_show_list_class_init,
            NULL,

            //(GClassFinalizeFunc)Cwin_show_list_class_finalize,
            NULL,

            sizeof(Cwin_show_list),0,
            (GInstanceInitFunc)Cwin_show_list_inst_init
        };
        window_type = g_type_register_static(WIN_LOGIN_TYPE,"Cwin_show_list",&window_info,0);

#ifdef USE_GENE_CLASS_PRIVATE_CODE
        g_type_add_class_private(window_type,sizeof(Cwin_show_list_class_private));
#endif
    }
    return window_type;
}

static void Cwin_show_list_base_init(Cwin_show_listClass *windowClass)
{
    UNUSED_VAR(windowClass);
}
static void Cwin_show_list_base_finalize(Cwin_show_listClass *windowClass)
{
    UNUSED_VAR(windowClass);
}

//�๹�캯��
static void Cwin_show_list_class_init(Cwin_show_listClass *windowClass,gpointer class_data)
{
    GObjectClass *base_class = G_OBJECT_CLASS(windowClass);
#ifdef USE_GENE_PROPERTY_CODE
    GParamSpec *property = NULL ;
#endif
#ifdef USE_GENE_CLASS_PRIVATE_CODE
    Cwin_show_list_class_private *p = WIN_SHOW_LIST_CLASS_GET_PRIVATE(windowClass);
#endif

    UNUSED_VAR(class_data);

    //�������˽������
    g_type_class_add_private(windowClass,sizeof(Cwin_show_list_private));
    //��ʼ���ຯ��
    base_class->dispose = (void(*)(GObject *object))Cwin_show_list_inst_dispose ;
    base_class->finalize = (void(*)(GObject *object))Cwin_show_list_inst_finalize;

#ifdef USE_GENE_PROPERTY_CODE
    base_class->set_property = Cwin_show_list_set_property;
    base_class->get_property = Cwin_show_list_get_property;

    //ע������
    property = g_param_spec_string("name","Name","The Attr Name",NULL,G_PARAM_READWRITE);
    g_object_class_install_property(base_class,WIN_SHOW_LIST_CLASS_PROPERTY_NAME,property);
#endif

#ifdef USE_GENE_SIGNAL_CODE
    //ע���ź�
    mg_signal[WIN_SHOW_LIST_SIGNAL_FIRST_SIG] = g_signal_new("first_sig",
            G_TYPE_FROM_CLASS(windowClass),
            G_SIGNAL_RUN_FIRST,
            0,NULL,NULL,g_cclosure_marshal_VOID__VOID,
            G_TYPE_NONE,0,NULL);
    //��Ҫ�����ź�ʱ��ʹ�� g_signal_emit(G_OBJECT(window), mg_signal[WIN_SHOW_LIST_SIGNAL_FIRST_SIG], 0);�����ź�
#endif
}

//����������
static void Cwin_show_list_class_finalize(Cwin_show_listClass *windowClass,gpointer class_data)
{
    UNUSED_VAR(windowClass);
    UNUSED_VAR(class_data);
}

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

#define APPEND_PIX_BT(cell_func,call_back) \
    do { \
        renderer = custom_cell_renderer_button_new(); \
        gtk_cell_renderer_set_alignment(renderer,0.5f,0.5f); \
        gtk_tree_view_column_pack_start(column,renderer,TRUE); \
        gtk_tree_view_column_set_cell_data_func(column, renderer, cell_func, window, NULL); \
    }while(0)

static void Cwin_show_list_clean_table(Cwin_show_list *window)
{
    GtkWidget *frame ;
    GtkWidget *label ;
    GtkTreeViewColumn *column ;
    GtkCellRenderer *renderer ;
    int line = 0 ;

    if(window->prv->m_table)
    {
        Cwin_login_clean_child((Cwin_login*)window);
        window->prv->m_table = NULL ;
    }
    window->prv->m_table = GTK_WIDGET(Cgtk_grid_table_new());
    Cwin_login_set_child((Cwin_login*)window , GTK_WIDGET(window->prv->m_table));
    window->prv->m_table_curr_line = 0 ;

    window->prv->m_treeStore = gtk_tree_store_new(COL_NUMS, G_TYPE_POINTER,G_TYPE_INT,G_TYPE_INT);
    gtk_tree_store_clear(window->prv->m_treeStore);

    // ��
    window->prv->m_treeView = GTK_TREE_VIEW(gtk_tree_view_new());
    Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_table),GTK_WIDGET(window->prv->m_treeView),
        0,0,4,1, TRUE, TRUE, TRUE,TRUE);
    gtk_tree_view_set_model(GTK_TREE_VIEW(window->prv->m_treeView),GTK_TREE_MODEL(window->prv->m_treeStore));
    gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(window->prv->m_treeView), TRUE);
    gtk_tree_view_set_grid_lines(GTK_TREE_VIEW(window->prv->m_treeView), GTK_TREE_VIEW_GRID_LINES_HORIZONTAL);
    gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(window->prv->m_treeView)), GTK_SELECTION_NONE);
    

    NEW_CLOUMN(35,100) ;
    renderer = gtk_cell_renderer_text_new(); 
    gtk_cell_renderer_set_alignment(renderer,1.0f,0.5f);
    gtk_tree_view_column_pack_start(column,renderer,TRUE);
    gtk_tree_view_column_set_cell_data_func(column, renderer, no_cell_data_func, window, NULL);

    NEW_CLOUMN(36,70) ;
    renderer = gtk_cell_renderer_pixbuf_new(); 
    gtk_cell_renderer_set_alignment(renderer,0.5f,0.5f);
    gtk_tree_view_column_pack_start(column,renderer,TRUE);
    gtk_tree_view_column_set_cell_data_func(column, renderer, pix_cell_data_func, window, NULL);

    NEW_CLOUMN(37,400) ;
    renderer = gtk_cell_renderer_text_new(); 
    gtk_cell_renderer_set_alignment(renderer,0.0f,0.5f);
    gtk_tree_view_column_pack_start(column,renderer,TRUE);
    gtk_tree_view_column_set_cell_data_func(column, renderer, name_cell_data_func, window, NULL);

    NEW_CLOUMN(38,180) ;
    if(window->prv->curr_type == 1 )
    {
        APPEND_PIX_BT(pix_shishi_cell_data_func,call_back);
        APPEND_PIX_BT(pix_zancun_cell_data_func,call_back);
        APPEND_PIX_BT(pix_shanchu_cell_data_func,call_back);
    }

    window->prv->m_table_curr_line ++ ;
    
    frame = gtk_frame_new(NULL);
    label = gtk_label_new(get_const_str(35));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(35));
    gtk_misc_set_alignment(GTK_MISC(label), 0.5f , 0.5f);
    gtk_container_add(GTK_CONTAINER(frame),GTK_WIDGET(label));
    Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_table),GTK_WIDGET(frame),
        0,1,1,1, FALSE, FALSE , TRUE,TRUE);

    frame = gtk_frame_new(NULL);
    label = gtk_label_new(get_const_str(36));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(36));
    gtk_misc_set_alignment(GTK_MISC(label), 0.5f , 0.5f);
    gtk_container_add(GTK_CONTAINER(frame),GTK_WIDGET(label));
    Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_table),GTK_WIDGET(frame),
        1,1,1,1, FALSE, FALSE , TRUE,TRUE);

    frame = gtk_frame_new(NULL);
    label = gtk_label_new(get_const_str(37));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(37));
    gtk_misc_set_alignment(GTK_MISC(label), 0.5f , 0.5f);
    gtk_container_add(GTK_CONTAINER(frame),GTK_WIDGET(label));
    Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_table),GTK_WIDGET(frame),
        2,1,1,1, TRUE, FALSE , TRUE,TRUE);

    frame = gtk_frame_new(NULL);
    label = gtk_label_new(get_const_str(38));
    gtk_label_set_markup(GTK_LABEL(label),get_const_str(38));
    gtk_misc_set_alignment(GTK_MISC(label), 0.5f , 0.5f);
    gtk_container_add(GTK_CONTAINER(frame),GTK_WIDGET(label));
    Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_table),GTK_WIDGET(frame),
        3,1,1,1, FALSE, FALSE , TRUE,TRUE);
    window->prv->m_table_curr_line ++ ;
}


typedef void (*BT_CLICK_CALL_BACK)(GtkButton *button, gpointer user_data) ;
typedef struct tag_bt_def {
    guint flag ;
    int name_id ;
    BT_CLICK_CALL_BACK callback ;
} BT_DEF ;

enum {
    BT_FLAG_ORGANS_SHISHI   = 0x00000001 ,
    BT_FLAG_ORGANS_ZANCUN   = 0x00000002 ,
    BT_FLAG_ORGANS_HUANYUAN = 0x00000004 ,
    BT_FLAG_ORGANS_SHANCHU  = 0x00000008 ,
    BT_FLAG_PERSON_SHISHI   = 0x00000010 ,
    BT_FLAG_PERSON_ZANCUN   = 0x00000020 ,
    BT_FLAG_PERSON_HUANYUAN = 0x00000040 ,
    BT_FLAG_PERSON_SHANCHU  = 0x00000080
};

static BT_DEF mg_bt_def[] = {
    { BT_FLAG_ORGANS_SHISHI   , 41 , slog_bt_organs_shishi } ,
    { BT_FLAG_ORGANS_ZANCUN   , 42 , slog_bt_organs_zancun } ,
    { BT_FLAG_ORGANS_HUANYUAN , 43 , slog_bt_organs_huanyuan } ,
    { BT_FLAG_ORGANS_SHANCHU  , 44 , slog_bt_organs_shanchu } ,
    { BT_FLAG_PERSON_SHISHI   , 41 , slog_bt_person_shishi } ,
    { BT_FLAG_PERSON_ZANCUN   , 42 , slog_bt_person_zancun } ,
    { BT_FLAG_PERSON_HUANYUAN , 43 , slog_bt_person_huanyuan } ,
    { BT_FLAG_PERSON_SHANCHU  , 44 , slog_bt_person_shanchu } ,
};

static void Cwin_show_list_append_line(Cwin_show_list *window,
       int no,int jcType ,const char* str ,guint bt_flag,gpointer user_data)
{
    GtkWidget *frame ;
    GtkWidget *label ;
    GtkWidget *type ; 
    GtkWidget *bt ;
    GtkWidget *hbox ;
    char buff[1024] ;
    char path[256] ;
    int i ;

    g_snprintf(buff,sizeof(buff),get_const_str(39),no);
    frame = gtk_frame_new(NULL);
    label = gtk_label_new(buff);
    gtk_label_set_markup(GTK_LABEL(label),buff);
    gtk_misc_set_alignment(GTK_MISC(label), 0.9f , 0.5f);
    gtk_container_add(GTK_CONTAINER(frame),GTK_WIDGET(label));
    Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_table),GTK_WIDGET(frame),
        0,window->prv->m_table_curr_line,1,1, FALSE, FALSE , TRUE,TRUE);

    frame = gtk_frame_new(NULL);
    if(jcType == JC_TYPE_JIANGLI )
    {
        g_snprintf(path,sizeof(path),"%simage/jiangli.png",mg_htxy_global.exe_dir);
    }
    else
    {
        g_snprintf(path,sizeof(path),"%simage/chengjie.png",mg_htxy_global.exe_dir);
    }
    type = gtk_image_new_from_file(path);
    gtk_container_add(GTK_CONTAINER(frame),GTK_WIDGET(type));
    Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_table),GTK_WIDGET(frame),
        1,window->prv->m_table_curr_line,1,1, FALSE, FALSE , TRUE,TRUE);

    g_snprintf(buff,sizeof(buff),get_const_str(40),str);
    frame = gtk_frame_new(NULL);
    label = gtk_label_new(buff);
    gtk_label_set_markup(GTK_LABEL(label),buff);
    gtk_misc_set_alignment(GTK_MISC(label), 0.0f , 0.5f);
    gtk_container_add(GTK_CONTAINER(frame),GTK_WIDGET(label));
    Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_table),GTK_WIDGET(frame),
        2,window->prv->m_table_curr_line,1,1, TRUE, FALSE , TRUE,TRUE);

    frame = gtk_frame_new(NULL);
    hbox = gtk_hbox_new(FALSE,1);
    gtk_container_add(GTK_CONTAINER(frame),GTK_WIDGET(hbox));
    Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_table),GTK_WIDGET(frame),
        3 ,window->prv->m_table_curr_line,1,1, FALSE, FALSE , TRUE,TRUE);
    for(i=0; i< sizeof(mg_bt_def)/sizeof(BT_DEF) ; i++)
    {
        if(bt_flag & mg_bt_def[i].flag)
        {
            label = gtk_label_new(get_const_str(mg_bt_def[i].name_id));
            gtk_label_set_markup(GTK_LABEL(label),get_const_str(mg_bt_def[i].name_id));
            bt = gtk_button_new_with_label("");
            gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(label));
            g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(mg_bt_def[i].callback),user_data);
            gtk_box_pack_start(GTK_BOX(hbox),bt,FALSE,FALSE,0);
        }
    }

    window->prv->m_table_curr_line ++ ;
}

static void Cwin_show_list_append_page_select(Cwin_show_list *window )
{
    GtkWidget *frame ;
    GtkWidget *label ;
    GtkWidget *frame_hbox ;
    GtkWidget *hbox ;
    GtkWidget *bt ;
    GtkWidget *img ;
    char path[256];
    char buff[256];

    // �Label
    label = gtk_label_new("");
    Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_table),GTK_WIDGET(label),
        0 ,window->prv->m_table_curr_line,4,1, FALSE, FALSE , TRUE,TRUE);
    window->prv->m_table_curr_line ++ ;

    /// 
    frame_hbox = gtk_hbox_new(FALSE,0);
    frame = gtk_frame_new(NULL);
    hbox = gtk_hbox_new(FALSE,0);
    label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(frame_hbox),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(frame_hbox),frame,FALSE,FALSE,0);
    gtk_container_add(GTK_CONTAINER(frame),hbox);
    Cgtk_grid_table_attach(GTK_GRID_TABLE(window->prv->m_table),GTK_WIDGET(frame_hbox),
        0 ,window->prv->m_table_curr_line,4,1, FALSE, FALSE , TRUE,TRUE);
    window->prv->m_table_curr_line ++ ;

    /// ���θ���ť
    bt = gtk_button_new_with_label("");
    g_snprintf(path,sizeof(path),"%simage/g_first.png",mg_htxy_global.exe_dir);
    img = gtk_image_new_from_file(path);
    gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(img));
    g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_first),window);
    gtk_box_pack_start(GTK_BOX(hbox),bt,FALSE,FALSE,0);

    bt = gtk_button_new_with_label("");
    g_snprintf(path,sizeof(path),"%simage/g_prev.png",mg_htxy_global.exe_dir);
    img = gtk_image_new_from_file(path);
    gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(img));
    g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_prev),window);
    gtk_box_pack_start(GTK_BOX(hbox),bt,FALSE,FALSE,0);

    g_snprintf(buff,sizeof(buff),get_const_str(46),window->prv->m_curr_page + 1, window->prv->m_total_page);
    label = gtk_label_new(buff);
    gtk_label_set_markup(GTK_LABEL(label),buff);
    gtk_box_pack_start(GTK_BOX(hbox),label,TRUE ,TRUE,0);


    bt = gtk_button_new_with_label("");
    g_snprintf(path,sizeof(path),"%simage/g_next.png",mg_htxy_global.exe_dir);
    img = gtk_image_new_from_file(path);
    gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(img));
    g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_next),window);
    gtk_box_pack_start(GTK_BOX(hbox),bt,FALSE,FALSE,0);

    bt = gtk_button_new_with_label("");
    g_snprintf(path,sizeof(path),"%simage/g_end.png",mg_htxy_global.exe_dir);
    img = gtk_image_new_from_file(path);
    gtk_button_set_image(GTK_BUTTON(bt),GTK_WIDGET(img));
    g_signal_connect(G_OBJECT(bt),"clicked",G_CALLBACK(slog_bt_end),window);
    gtk_box_pack_start(GTK_BOX(hbox),bt,FALSE,FALSE,0);
}

static void Cwin_show_list_show_organs_all(Cwin_show_list *window)
{
    int i ;
    GtkTreeIter iter ;
    DB_ORGANS_ITEM *item ;
    DB_PERSON_ITEM *person ;
    guint bt_flag = BT_FLAG_ORGANS_SHISHI | BT_FLAG_ORGANS_ZANCUN | BT_FLAG_ORGANS_SHANCHU ;
    for( i = 0 ; i < window->prv->m_data_count ; i++)
    {
        if(window->prv->curr_type == 1)
        {
            item = &window->prv->m_organs_data[i] ;

            gtk_tree_store_append(window->prv->m_treeStore, &iter, NULL);
            gtk_tree_store_set(window->prv->m_treeStore, &iter, 
                COL_POINTER, item ,
                COL_INDEX , window->prv->m_curr_page*MAX_ON_ONE_PAGE + i + 1,
                COL_TYPE, COL_TYPE_ORGANS ,
                -1 );

            Cwin_show_list_append_line(window, window->prv->m_curr_page*MAX_ON_ONE_PAGE + i + 1,
                item->jcType, item->qymc , 
                BT_FLAG_ORGANS_SHISHI | BT_FLAG_ORGANS_ZANCUN | BT_FLAG_ORGANS_SHANCHU , item);
        }
        else if(window->prv->curr_type == 2)
        {
            item = &window->prv->m_organs_data[i] ;
            Cwin_show_list_append_line(window, window->prv->m_curr_page*MAX_ON_ONE_PAGE + i + 1,
                item->jcType, item->qymc , 
                BT_FLAG_ORGANS_SHISHI | BT_FLAG_ORGANS_HUANYUAN | BT_FLAG_ORGANS_SHANCHU , item);
        }
        else if(window->prv->curr_type == 3)
        {
            person = &window->prv->m_person_data[i] ;
            Cwin_show_list_append_line(window, window->prv->m_curr_page*MAX_ON_ONE_PAGE + i + 1,
                person->jcType, person->xm ,
                BT_FLAG_PERSON_SHISHI | BT_FLAG_PERSON_ZANCUN | BT_FLAG_PERSON_SHANCHU , person);
        }
        else if(window->prv->curr_type == 4)
        {
            person = &window->prv->m_person_data[i] ;
            Cwin_show_list_append_line(window, window->prv->m_curr_page*MAX_ON_ONE_PAGE + i + 1,
                person->jcType, person->xm ,
                BT_FLAG_PERSON_SHISHI | BT_FLAG_PERSON_HUANYUAN | BT_FLAG_PERSON_SHANCHU , person);
        }
    }
}

#define PIX_INIT(pix,png) \
    do{ \
        g_snprintf(path,sizeof(path),"%simage/%s",mg_htxy_global.exe_dir,png); \
        window->prv->pix = gdk_pixbuf_new_from_file(path,NULL); \
    }while(0)

#define PIX_CLEAN(pix) \
    do { \
        if(window->prv->pix) \
	    { \
             g_object_unref( G_OBJECT(window->prv->pix) ); \
             window->prv->pix = NULL ; \
	    } \
    }while(0)

//�����캯��
static void Cwin_show_list_inst_init(Cwin_show_list *window)
{
    char path[256];
    window->prv = WIN_SHOW_LIST_GET_PRIVATE(window);

    gtk_widget_set_usize(GTK_WIDGET(window), 800,780);

    PIX_INIT(m_pix_jiang,"jiangli.png");
    PIX_INIT(m_pix_cheng ,"chengjie.png");
    PIX_INIT(m_pix_shishi,"shishi.png");
    PIX_INIT(m_pix_zancun,"zancun.png");
    PIX_INIT(m_pix_huanyuan,"huanyuan.png");
    PIX_INIT(m_pix_shanchu,"shanchu.png");
}


//������������
static void Cwin_show_list_inst_finalize(Cwin_show_list *window)
{
    PIX_CLEAN(m_pix_jiang) ;
    PIX_CLEAN(m_pix_cheng) ;
    PIX_CLEAN(m_pix_shishi) ;
    PIX_CLEAN(m_pix_zancun) ;
    PIX_CLEAN(m_pix_huanyuan) ;
    PIX_CLEAN(m_pix_shanchu) ;

    G_OBJECT_CLASS(g_type_class_peek(g_type_parent(g_type_from_name("Cwin_show_list"))))->finalize(G_OBJECT(window));
}
//�����ͷź���
static void Cwin_show_list_inst_dispose(Cwin_show_list *window)
{
    G_OBJECT_CLASS(g_type_class_peek(g_type_parent(g_type_from_name("Cwin_show_list"))))->dispose(G_OBJECT(window));
}

#ifdef USE_GENE_PROPERTY_CODE
static void Cwin_show_list_set_property(GObject *object,
        guint  property_id,
        const GValue *value,
        GParamSpec *pspec)
{
    Cwin_show_list *window = WIN_SHOW_LIST(object);

    UNUSED_VAR(window);

    switch(property_id)
    {
        case WIN_SHOW_LIST_CLASS_PROPERTY_NAME:
            //��������name��value�Ĵ���
            break ;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,pspec);
            break;
    }
}
static void Cwin_show_list_get_property(GObject  *object,
        guint property_id,
        GValue *value,
        GParamSpec *pspec)
{
    Cwin_show_list *window = WIN_SHOW_LIST(object);

    UNUSED_VAR(window);

    switch(property_id)
    {
        case WIN_SHOW_LIST_CLASS_PROPERTY_NAME:
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
Cwin_show_list* Cwin_show_list_new(void)
{
    Cwin_show_list* window;
    window = (Cwin_show_list*)g_object_new(WIN_SHOW_LIST_TYPE,NULL);

    return window;
}

void Cwin_show_list_set_show_curr_page(Cwin_show_list *window)
{
    Cwin_show_list_clean_table(window);
    if(window->prv->curr_type == 1)
    {
        window->prv->m_data_count = db_get_organs_all(window->prv->m_organs_data,
            window->prv->m_curr_page*MAX_ON_ONE_PAGE , MAX_ON_ONE_PAGE, FALSE);
        Cwin_show_list_show_organs_all(window);
    }
    if(window->prv->curr_type == 2)
    {
        window->prv->m_data_count = db_get_organs_all(window->prv->m_organs_data,
            window->prv->m_curr_page*MAX_ON_ONE_PAGE , MAX_ON_ONE_PAGE,TRUE);
        Cwin_show_list_show_organs_all(window);
    }
    else if(window->prv->curr_type == 3)
    {
        window->prv->m_data_count = db_get_person_all(window->prv->m_person_data,
            window->prv->m_curr_page*MAX_ON_ONE_PAGE , MAX_ON_ONE_PAGE,FALSE);
        Cwin_show_list_show_organs_all(window);
    }
    else if(window->prv->curr_type == 4)
    {
        window->prv->m_data_count = db_get_person_all(window->prv->m_person_data,
            window->prv->m_curr_page*MAX_ON_ONE_PAGE , MAX_ON_ONE_PAGE,TRUE);
        Cwin_show_list_show_organs_all(window);
    }
    Cwin_show_list_append_page_select(window);
    gtk_widget_show_all(GTK_WIDGET(window));
}

void Cwin_show_list_set_show_type(Cwin_show_list *window ,int type)
{
    window->prv->curr_type = type ;
    window->prv->m_total_page = 0 ;
    if(type == 1)
    {
        Cwin_login_set_title((Cwin_login*)window,get_const_str(31));
        window->prv->m_total_page = (mg_htxy_global.stat_organs_all-1) / MAX_ON_ONE_PAGE + 1 ;
    }
    else if(type == 2)
    {
        Cwin_login_set_title((Cwin_login*)window,get_const_str(32));
        window->prv->m_total_page = (mg_htxy_global.stat_organs_shishi-1) / MAX_ON_ONE_PAGE + 1 ;
    }
    else if(type == 3)
    {
        Cwin_login_set_title((Cwin_login*)window,get_const_str(33));
        window->prv->m_total_page = (mg_htxy_global.stat_person_all -1) / MAX_ON_ONE_PAGE + 1 ;
    }
    else if(type == 4)
    {
        Cwin_login_set_title((Cwin_login*)window,get_const_str(34));
        window->prv->m_total_page = (mg_htxy_global.stat_person_shishi -1) / MAX_ON_ONE_PAGE + 1 ;
    }
    window->prv->m_curr_page = 0 ;
    Cwin_show_list_set_show_curr_page(window);
}

//////////////////////////////////////////////////
///
///  ˽�к���ʵ��
///
///////////////////////////////////////////////////

static void slog_bt_organs_shishi(GtkButton *button, gpointer user_data) 
{
}
static void slog_bt_organs_zancun(GtkButton *button, gpointer user_data) 
{
    DB_ORGANS_ITEM *item = (DB_ORGANS_ITEM *)user_data ;

    item->is_shishi = TRUE ;
    update_organs_item(item);
}
static void slog_bt_organs_huanyuan(GtkButton *button, gpointer user_data) 
{
    DB_ORGANS_ITEM *item = (DB_ORGANS_ITEM *)user_data ;

    item->is_shishi = FALSE ;
    update_organs_item(item);
}
static void slog_bt_organs_shanchu(GtkButton *button, gpointer user_data) 
{
}
static void slog_bt_person_shishi(GtkButton *button, gpointer user_data) 
{
}
static void slog_bt_person_zancun(GtkButton *button, gpointer user_data) 
{
}
static void slog_bt_person_huanyuan(GtkButton *button, gpointer user_data) 
{
}
static void slog_bt_person_shanchu(GtkButton *button, gpointer user_data) 
{
}

static void slog_bt_first(GtkButton *button, gpointer user_data) 
{
    Cwin_show_list *window = (Cwin_show_list *)user_data ;

    window->prv->m_curr_page = 0 ;
    Cwin_show_list_set_show_curr_page(window);
}

static void slog_bt_prev(GtkButton *button, gpointer user_data) 
{
    Cwin_show_list *window = (Cwin_show_list *)user_data ;

    window->prv->m_curr_page -- ;
    if(window->prv->m_curr_page < 0 )
    {
        window->prv->m_curr_page = 0 ;
    }
    Cwin_show_list_set_show_curr_page(window);
}

static void slog_bt_next(GtkButton *button, gpointer user_data) 
{
    Cwin_show_list *window = (Cwin_show_list *)user_data ;

    window->prv->m_curr_page ++ ;
    if(window->prv->m_curr_page >= window->prv->m_total_page )
    {
        window->prv->m_curr_page = window->prv->m_total_page - 1 ;
    }
    if(window->prv->m_curr_page < 0 )
    {
        window->prv->m_curr_page = 0 ;
    }
    Cwin_show_list_set_show_curr_page(window);
}

static void slog_bt_end(GtkButton *button, gpointer user_data) 
{
    Cwin_show_list *window = (Cwin_show_list *)user_data ;

    window->prv->m_curr_page = window->prv->m_total_page - 1 ;
    if(window->prv->m_curr_page < 0 )
    {
        window->prv->m_curr_page = 0 ;
    }
    Cwin_show_list_set_show_curr_page(window);
}

static void no_cell_data_func (GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data)
{
    Cwin_show_list *window = (Cwin_show_list *)user_data ;

    gint no ;
    char text[1024];
    gtk_tree_model_get(model, iter, COL_INDEX , &no,  -1);
    g_snprintf(text,sizeof(text),get_const_str(39),no);
    g_object_set(renderer, "text", text, NULL);
    g_object_set(renderer, "markup", text, NULL);
}

static void pix_cell_data_func (GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data)
{
    Cwin_show_list *window = (Cwin_show_list *)user_data ;
    gint type ;
    gpointer p ;
    gtk_tree_model_get(model, iter, COL_POINTER, &p,  COL_TYPE , &type ,-1);

    if(type == COL_TYPE_ORGANS )
    {
        DB_ORGANS_ITEM *item = (DB_ORGANS_ITEM*)p;

        if(item->jcType == JC_TYPE_JIANGLI )
        {
            g_object_set(renderer, "pixbuf", window->prv->m_pix_jiang, NULL);
        }
        else
        {
            g_object_set(renderer, "pixbuf", window->prv->m_pix_jiang, NULL);
        }
    }
    else 
    {
        DB_PERSON_ITEM *item = (DB_PERSON_ITEM*)p;

        if(item->jcType == JC_TYPE_JIANGLI )
        {
            g_object_set(renderer, "pixbuf", window->prv->m_pix_jiang, NULL);
        }
        else
        {
            g_object_set(renderer, "pixbuf", window->prv->m_pix_jiang, NULL);
        }
    }
}

static void name_cell_data_func (GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data)
{
    Cwin_show_list *window = (Cwin_show_list *)user_data ;
    gint type ;
    gpointer p ;
    char text[1024];

    gtk_tree_model_get(model, iter, COL_POINTER, &p,  COL_TYPE , &type ,-1);

    if(type == COL_TYPE_ORGANS )
    {
        DB_ORGANS_ITEM *item = (DB_ORGANS_ITEM*)p;

        g_snprintf(text,sizeof(text),get_const_str(40),item->qymc);
        g_object_set(renderer, "text", text, NULL);
        g_object_set(renderer, "markup", text, NULL);
    }
    else 
    {
        DB_PERSON_ITEM *item = (DB_PERSON_ITEM*)p;

        g_snprintf(text,sizeof(text),get_const_str(40),item->xm);
        g_object_set(renderer, "text", text, NULL);
        g_object_set(renderer, "markup", text, NULL);
    }
}

static void pix_shishi_cell_data_func(GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data)
{
    Cwin_show_list *window = (Cwin_show_list *)user_data ;
    g_object_set(renderer, "pixbuf", window->prv->m_pix_shishi, NULL);
}

static void pix_zancun_cell_data_func(GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data)
{
    Cwin_show_list *window = (Cwin_show_list *)user_data ;
    g_object_set(renderer, "pixbuf", window->prv->m_pix_zancun, NULL);
}

static void pix_huanyuan_cell_data_func(GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data)
{
    Cwin_show_list *window = (Cwin_show_list *)user_data ;
    g_object_set(renderer, "pixbuf", window->prv->m_pix_huanyuan , NULL);
}
static void pix_shanchu_cell_data_func(GtkTreeViewColumn *col,
                    GtkCellRenderer   *renderer,
                    GtkTreeModel      *model,
                    GtkTreeIter       *iter,
                    gpointer           user_data)
{
    Cwin_show_list *window = (Cwin_show_list *)user_data ;
    g_object_set(renderer, "pixbuf", window->prv->m_pix_shanchu , NULL);
}


#ifdef __cplusplus
}
#endif
