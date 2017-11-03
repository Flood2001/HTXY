#ifndef _HRSOFT_DATA_CALC_UTIL_H_2017_10_18_
#define _HRSOFT_DATA_CALC_UTIL_H_2017_10_18_

#include <hrjson/hrjson.h>

#ifdef __cplusplus
extern "C"{
#endif

const char* get_const_str(int id);

void read_config();
void write_config();

/// 成功返回NULL，否则返回失败原因
char* user_login(const char* usrname , const char* password);
void user_logout();
gboolean info_find_user(const char* usrname);
void read_url();

/////////////////////////////
///  
///  数据库
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

    //待实施对象
    gboolean is_shishi ;    ///< 是否实施过
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

    //待实施对象
    gboolean is_shishi ;    ///< 是否实施过
    char cdate[128] ;   ///< c
} DB_PERSON_ITEM ;

/// 奖惩信息
typedef struct tag_jc_info {
#define JC_INFO_REASON_ITEM_LEN  128
#define JC_INFO_SY_ITEM_LEN  128
    GArray *reasons ;    ///< 认定事由   ///< 每项为一个 char[JC_INFO_REASON_ITEM_LEN]
    char jc_type[128] ; ///< 惩罚措施
    GArray *sy ;         ///< sy    每项为一个 char[JC_INFO_SY_ITEM_LEN]
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

/// 获取organs的第 start 到 end 条 记录
///start从0开始 , item_array为数组，用于返回值
/// 返回值表示实际读取到的条数
int db_get_organs_all(DB_ORGANS_ITEM *item_array,int start , int count , gboolean is_shishi);
int db_get_person_all(DB_PERSON_ITEM *item_array,int start , int count , gboolean is_shishi);
gboolean db_get_organs_info(const char* qymc, int jcType , DB_ORGANS_ITEM *rv);
gboolean db_get_person_info(const char* sfzhm, int jcType ,DB_PERSON_ITEM *rv);
int db_get_organs_jc_info(DB_ORGANS_ITEM*item,JC_INFO *info);
void db_init_info(JC_INFO *info);
void db_clear_info(JC_INFO *info);

/// 远程升级
gboolean update_check_is_new(); ///< 检测是否有新版本，有返回TRUE
gboolean update_download_packet(); ///< 下载升级包到 ./update/last_update.exe
void update_do_update();        ///< 关闭程序，并执行./update/last_update.exe

#ifdef __cplusplus
}
#endif

#endif // _HRSOFT_DATA_CALC_UTIL_H_2017_10_18_

