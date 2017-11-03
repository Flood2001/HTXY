#ifndef _HRSOFT_DATA_CALC_UTIL_H_2017_10_18_
#define _HRSOFT_DATA_CALC_UTIL_H_2017_10_18_

#include <hrjson/hrjson.h>

#ifdef __cplusplus
extern "C"{
#endif

const char* get_const_str(int id);

void read_config();
void write_config();

/// �ɹ�����NULL�����򷵻�ʧ��ԭ��
char* user_login(const char* usrname , const char* password);
void user_logout();
gboolean info_find_user(const char* usrname);
void read_url();

/////////////////////////////
///  
///  ���ݿ�
///
///////////////////////////////
enum {
    JC_TYPE_JIANGLI = 1 ,
    JC_TYPE_CHENGJIE = 2 
};

typedef struct tag_db_organs_item {
    char enterprise_id[256] ;
    char qymc[256] ;
    char xydm[256] ;
    int counts ;
    int jcType ;        ///< JC_TYPE_JIANGLI etc...
    int dataType ;
    char id[128] ;
    guint64 timestamp ;
    char outDate[128] ;

    //��ʵʩ����
    gboolean is_shishi ;    ///< �Ƿ�ʵʩ��
    char cdate[128] ;   ///< c
} DB_ORGANS_ITEM ;

typedef struct tag_db_person_item {
    char person_id[256] ;
    char xm[64] ;
    char sfzhm[128] ;
    int counts ;
    int jcType ;        ///< JC_TYPE_JIANGLI etc...
    int dataType ;
    char id[128] ;
    guint64 timestamp ;
    char outDate[128] ;

    //��ʵʩ����
    gboolean is_shishi ;    ///< �Ƿ�ʵʩ��
    char cdate[128] ;   ///< c
} DB_PERSON_ITEM ;

/// ������Ϣ
typedef struct tag_jc_info {
#define JC_INFO_REASON_ITEM_LEN  128
#define JC_INFO_SY_ITEM_LEN  128
    GArray *reasons ;    ///< �϶�����   ///< ÿ��Ϊһ�� char[JC_INFO_REASON_ITEM_LEN]
    char jc_type[128] ; ///< �ͷ���ʩ
    GArray *sy ;         ///< sy    ÿ��Ϊһ�� char[JC_INFO_SY_ITEM_LEN]
    char measure_name[128] ;
    char jc_basis[128] ;
    char temp_id[128];
    char zt_id[128];
    char jcDate[128];
    char jcDesc[128];
    HR_JSON recordReason;
} JC_INFO ;
typedef char JC_INFO_REASON_ITEM_TYPE[JC_INFO_REASON_ITEM_LEN];
typedef char JC_INFO_SY_ITEM_TYPE[JC_INFO_SY_ITEM_LEN];

void update_all_db();
void update_organs_db();
void update_person_db();
void update_organs_item(DB_ORGANS_ITEM *item);
void update_person_item(DB_PERSON_ITEM*item);
void delete_organs_item(DB_ORGANS_ITEM *item);
void delete_person_item(DB_PERSON_ITEM*item);
void stat_db();

/// ��ȡorgans�ĵ� start �� end �� ��¼
///start��0��ʼ , item_arrayΪ���飬���ڷ���ֵ
/// ����ֵ��ʾʵ�ʶ�ȡ��������
int db_get_organs_all(DB_ORGANS_ITEM *item_array,int start , int count , gboolean is_shishi);
int db_get_person_all(DB_PERSON_ITEM *item_array,int start , int count , gboolean is_shishi);
gboolean db_get_organs_info(const char* qymc, int jcType , DB_ORGANS_ITEM *rv);
gboolean db_get_person_info(const char* sfzhm, int jcType ,DB_PERSON_ITEM *rv);
int db_get_organs_jc_info(DB_ORGANS_ITEM*item,JC_INFO *info);
void db_init_info(JC_INFO *info);
void db_clear_info(JC_INFO *info);

/// Զ������
gboolean update_check_is_new(); ///< ����Ƿ����°汾���з���TRUE
gboolean update_download_packet(); ///< ������������ ./update/last_update.exe
void update_do_update();        ///< �رճ��򣬲�ִ��./update/last_update.exe

#ifdef __cplusplus
}
#endif

#endif // _HRSOFT_DATA_CALC_UTIL_H_2017_10_18_

