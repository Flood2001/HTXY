#ifndef _HRSOFT_DATA_CALC_UTIL_H_2017_10_18_
#define _HRSOFT_DATA_CALC_UTIL_H_2017_10_18_

#ifdef __cplusplus
extern "C"{
#endif



void read_config();
void write_config();

/// �ɹ�����NULL�����򷵻�ʧ��ԭ��
char* user_login(const char* usrname , const char* password);
gboolean info_find_user(const char* usrname);
void read_url();

/////////////////////////////
///  
///  ���ݿ�
///
///////////////////////////////
typedef struct tag_db_organs_item {
    char enterprise_id[256] ;
    char qymc[256] ;
    char xydm[256] ;
    int counts ;
    int jcType ;
    int dataType ;
    char id[128] ;
} DB_ORGANS_ITEM ;

void update_organs_db();

#ifdef __cplusplus
}
#endif

#endif // _HRSOFT_DATA_CALC_UTIL_H_2017_10_18_

