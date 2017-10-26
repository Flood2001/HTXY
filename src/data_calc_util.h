#ifndef _HRSOFT_DATA_CALC_UTIL_H_2017_10_18_
#define _HRSOFT_DATA_CALC_UTIL_H_2017_10_18_

#ifdef __cplusplus
extern "C"{
#endif



void read_config();
void write_config();

/// 成功返回NULL，否则返回失败原因
char* user_login(const char* usrname , const char* password);
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

void update_all_db();
void update_organs_db();
void update_person_db();
void stat_db();

#ifdef __cplusplus
}
#endif

#endif // _HRSOFT_DATA_CALC_UTIL_H_2017_10_18_

