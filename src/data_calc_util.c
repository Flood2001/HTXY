/////////////////////////////////////////////////////
/// Copyright (C) 2017 Hrsoft Corporation, All rights reserved.
/// @file data_calc_util.c
/// @author 张洪峰
/// @version 1.0
/// @date 2017-10-18 
/// @brief 数据算法
/////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hrutil/hrutil.h>
#include <hrjson/hrjson.h>
#include <db.h>
#include "gtk_win.h"
#include "data_calc_util.h"
#include "libsoup/soup.h"

#ifdef __cplusplus
extern "C"{
#endif

void read_config()
{
    HR_JSON root ;
    HR_JSON listenser ;
    HR_JSON platform ;
    HR_JSON value ;
    gint i ;
    int rv = -1 ;
    const char* str;

    char exe_path[256];
    char path[256];

    hrutil_get_exe_dir(exe_path);
    g_snprintf(path,sizeof(path),"%sdata/setting.json",exe_path);

    root = hrjson_load_file(path);
    if(root == NULL)
    {
        goto end ;
    }

    //listenser
    listenser = hrjson_object_get_key(root,"listenser");
    if(listenser)
    {
        value = hrjson_object_get_key(listenser,"delay");
        if(value)
        {
            i = (gint)hrjson_get_integer(value);
            if( i > 0 )
            {
                mg_htxy_global.listenser_delay = i ;
            }
            hrjson_destroy(value);
        }

        value = hrjson_object_get_key(listenser,"watch");
        if(value)
        {
            i = (gint)hrjson_get_integer(value);
            if( i > 0 )
            {
                mg_htxy_global.listenser_watch = i ;
            }
            hrjson_destroy(value);
        }
    }

    //platform
    platform = hrjson_object_get_key(root,"platform");
    if(platform)
    {
        HR_JSON api ;

        api = hrjson_object_get_key(platform,"api");
        if(api)
        {
            HR_JSON login ;
            HR_JSON roster ;
            HR_JSON count ;
            HR_JSON context ;

            login = hrjson_object_get_key(api,"login");
            if(login)
            {
                value = hrjson_object_get_key(login,"type");
                if(value)
                {
                    str = hrjson_get_string(value);
                    if(str)
                    {
                        g_strlcpy(mg_htxy_global.platform_api_login_type,str,sizeof(mg_htxy_global.platform_api_login_type));
                    }
                    hrjson_destroy(value);
                }

                value = hrjson_object_get_key(login,"url");
                if(value)
                {
                    str = hrjson_get_string(value);
                    if(str)
                    {
                        g_strlcpy(mg_htxy_global.platform_api_login_url,str,sizeof(mg_htxy_global.platform_api_login_url));
                    }
                    hrjson_destroy(value);
                }
            }

            roster = hrjson_object_get_key(api,"roster");
            if(roster)
            {
                value = hrjson_object_get_key(roster,"type");
                if(value)
                {
                    str = hrjson_get_string(value);
                    if(str)
                    {
                        g_strlcpy(mg_htxy_global.platform_api_roster_type,str,sizeof(mg_htxy_global.platform_api_roster_type));
                    }
                    hrjson_destroy(value);
                }

                value = hrjson_object_get_key(roster,"url");
                if(value)
                {
                    str = hrjson_get_string(value);
                    if(str)
                    {
                        g_strlcpy(mg_htxy_global.platform_api_roster_url,str,sizeof(mg_htxy_global.platform_api_roster_url));
                    }
                    hrjson_destroy(value);
                }
            }

            count = hrjson_object_get_key(api,"count");
            if(count)
            {
                value = hrjson_object_get_key(count,"type");
                if(value)
                {
                    str = hrjson_get_string(value);
                    if(str)
                    {
                        g_strlcpy(mg_htxy_global.platform_api_count_type,str,sizeof(mg_htxy_global.platform_api_count_type));
                    }
                    hrjson_destroy(value);
                }

                value = hrjson_object_get_key(count,"url");
                if(value)
                {
                    str = hrjson_get_string(value);
                    if(str)
                    {
                        g_strlcpy(mg_htxy_global.platform_api_count_url,str,sizeof(mg_htxy_global.platform_api_count_url));
                    }
                    hrjson_destroy(value);
                }
            }

            context = hrjson_object_get_key(api,"context");
            if(context)
            {
                value = hrjson_object_get_key(context,"type");
                if(value)
                {
                    str = hrjson_get_string(value);
                    if(str)
                    {
                        g_strlcpy(mg_htxy_global.platform_api_context_type,str,sizeof(mg_htxy_global.platform_api_context_type));
                    }
                    hrjson_destroy(value);
                }

                value = hrjson_object_get_key(context,"url");
                if(value)
                {
                    str = hrjson_get_string(value);
                    if(str)
                    {
                        g_strlcpy(mg_htxy_global.platform_api_context_url,str,sizeof(mg_htxy_global.platform_api_context_url));
                    }
                    hrjson_destroy(value);
                }
            }
        }

        value = hrjson_object_get_key(platform,"name");
        if(value)
        {
            str = hrjson_get_string(value);
            if(str)
            {
                g_strlcpy(mg_htxy_global.platform_name,str,sizeof(mg_htxy_global.platform_name));
            }
            hrjson_destroy(value);
        }

        value = hrjson_object_get_key(platform,"url");
        if(value)
        {
            str = hrjson_get_string(value);
            if(str)
            {
                g_strlcpy(mg_htxy_global.platform_url,str,sizeof(mg_htxy_global.platform_url));
            }
            hrjson_destroy(value);
        }

        value = hrjson_object_get_key(platform,"web");
        if(value)
        {
            str = hrjson_get_string(value);
            if(str)
            {
                g_strlcpy(mg_htxy_global.platform_web,str,sizeof(mg_htxy_global.platform_web));
            }
            hrjson_destroy(value);
        }

        value = hrjson_object_get_key(platform,"type");
        if(value)
        {
            str = hrjson_get_string(value);
            if(str)
            {
                if(strcmp(str,"organsdb")==0)
                {
                    mg_htxy_global.is_use_organs = TRUE ;
                    mg_htxy_global.is_use_person = FALSE ;
                }
                else if(strcmp(str,"persondb")==0)
                {
                    mg_htxy_global.is_use_organs = FALSE ;
                    mg_htxy_global.is_use_person = TRUE ;
                }
                else
                {
                    mg_htxy_global.is_use_organs = TRUE ;
                    mg_htxy_global.is_use_person = TRUE ;
                }
            }
            hrjson_destroy(value);
        }
    }

    rv = 0 ;

end:
    ;
//    if(root)
//    {
//        hrjson_destroy(root);
//    }
}

void write_config();

char* user_login(const char* usrname , const char* password)
{
    SoupSession *ss ;
    SoupMessage *msg;
    guint status;
    char url[1024];
    char url_body[1024];
    const char *str ;
    HR_JSON root = NULL ;
    HR_JSON body = NULL ;
    HR_JSON message = NULL ;
    HR_JSON organUser= NULL ;
    HR_JSON value = NULL ;

    g_snprintf(url,sizeof(url),"%s%s",mg_htxy_global.platform_url,mg_htxy_global.platform_api_login_url);
    ss = soup_session_sync_new();
    msg = soup_message_new (mg_htxy_global.platform_api_login_type, url);
    if(msg)
    {
        //soup_message_headers_append(msg->request_headers,"Cache-Control","max-age=0");
        //soup_message_headers_append(msg->request_headers,"Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
        //soup_message_headers_append(msg->request_headers,"Accept-Language","zh-CN,zh;q=0.8");
        //soup_message_headers_append(msg->request_headers,"Origin","null");
        //soup_message_headers_append(msg->request_headers,"Upgrade-Insecure-Requests","1");
        //soup_message_headers_append(msg->request_headers,"User-Agent","Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/49.0.2623.112 Safari/537.36");
        soup_message_headers_append(msg->request_headers,"Content-Type","application/x-www-form-urlencoded");
        soup_message_headers_append(msg->request_headers,"Accept-Encoding","gzip, deflate");

        g_snprintf(url_body,sizeof(url_body),"username=%s&password=%s",usrname,password);
        soup_message_body_append(msg->request_body ,SOUP_MEMORY_TEMPORARY,url_body,strlen(url_body));
    }

    mg_htxy_global.session[0] = '\0' ;
    status = soup_session_send_message (ss , msg);
    url_body[0] = '\0' ;
    if(status == 200 )
    {
        root = hrjson_load_string(msg->response_body->data);
        if(root)
        {
            body = hrjson_object_get_key(root,"body");
            if(body)
            {
                organUser = hrjson_object_get_key(body,"organUser");
                if(organUser)
                {
                    value = hrjson_object_get_key(organUser,"organId");
                    if(value)
                    {
                        str = hrjson_get_string(value);
                        if(str)
                        {
                            g_strlcpy(mg_htxy_global.organId,str,sizeof(mg_htxy_global.organId));
                            goto end ;
                        }
                        hrjson_destroy(value);
                        value = NULL ;
                    }
                }
                else
                {
                    message = hrjson_object_get_key(body,"message");
                    if(message)
                    {
                        str = hrjson_get_string(message);
                        if(str)
                        {
                            g_strlcpy(url_body,str,sizeof(url_body));
                            goto end ;
                        }
                    }
                }
            }

            value = hrjson_object_get_key(organUser,"session");
            if(value)
            {
                str = hrjson_get_string(value);
                if(str)
                {
                    g_strlcpy(mg_htxy_global.session,str,sizeof(mg_htxy_global.session));
                }
                hrjson_destroy(value);
                value = NULL ;
            }
        }
        g_snprintf(url_body,sizeof(url_body),"Parse Json Error : %s",msg->response_body->data);
    }
    else
    {
        g_snprintf(url_body,sizeof(url_body),"HTTP Error status : %d",status);
    }

end :

//    if(value) { hrjson_destroy(value); value = NULL ; }
//    if(organUser) { hrjson_destroy(organUser); }
//    if(message) { hrjson_destroy(message); }
//    if(body) { hrjson_destroy(body); }
//    if(root) { hrjson_destroy(root); }

    if(msg)
    {
        g_object_unref(G_OBJECT(msg));
    }
    if(ss)
    {
        g_object_unref(G_OBJECT(ss));
    }

    if(url_body[0] == '\0' )
    {
        return NULL ;
    }
    return g_strdup(url_body);
}

gboolean read_roster()
{
    SoupSession *ss ;
    SoupMessage *msg;
    guint status;
    char url[1024];
    HR_JSON root = NULL ;
    HR_JSON body = NULL ;
    HR_JSON message = NULL ;
    HR_JSON organUser= NULL ;
    HR_JSON value = NULL ;

    ss = soup_session_sync_new();
    g_snprintf(url,sizeof(url),"%s%s?organId=%s&dataType=1",mg_htxy_global.platform_url,
        mg_htxy_global.platform_api_roster_url,mg_htxy_global.organId);
    msg = soup_message_new (mg_htxy_global.platform_api_roster_type, url);
    if(msg)
    {
        soup_message_headers_append(msg->request_headers,"Content-Type","application/x-www-form-urlencoded");
        soup_message_headers_append(msg->request_headers,"Accept-Encoding","gzip, deflate");
        if(mg_htxy_global.session[0] != '\0' )
        {
            g_snprintf(url,sizeof(url),"SESSION=%s",mg_htxy_global.session);
            soup_message_headers_append(msg->request_headers,"Cookie",url);
        }
    }

    status = soup_session_send_message (ss , msg);

    if(msg)
    {
        g_object_unref(G_OBJECT(msg));
    }
    if(ss)
    {
        g_object_unref(G_OBJECT(ss));
    }

    return TRUE ;
}

/////////////////////////////////////
//
//  数据库
//
/////////////////////////////////////

static gboolean mg_is_update_ing = FALSE ;
static DB *mg_db_organs = NULL ;
static DB *mg_db_person = NULL ;
#define DB_ORGANS_FILE "organs.db"
#define DB_PERSON_FILE "person.db"

static int db_comp_id(DB *db, const DBT *dbt1, const DBT *dbt2,size_t *locp)
{
    return strcmp((char*)dbt1->data,(char*)dbt2->data) ;
}

static DB* open_db(const char* relative_path)
{
    DB *dbp=NULL ;
    int ret ;
    char path[256] ;
    char dir[256] ;
    u_int32_t db_flag = DB_CREATE | DB_THREAD ;

    hrutil_get_exe_dir(dir);
    g_snprintf(path,sizeof(path),"%sdata/%s",dir,relative_path);
    ret = db_create(&dbp, NULL,0);
    if(0 != ret)
    {
        dbp = NULL ;
        goto quit ;
    }
    ret = dbp->set_bt_compare(dbp, db_comp_id);
    ret = dbp->open(dbp, NULL, path, relative_path, DB_BTREE, db_flag , 0664);
    if(ret != 0)
    {
        dbp->close(dbp,0);
        dbp = NULL ;
        goto quit ;
    }

quit :
    return dbp ;
}

static void open_search_db()
{
    if(mg_db_organs == NULL)
    {
        mg_db_organs = open_db(DB_ORGANS_FILE);
    }
    if(mg_db_person == NULL)
    {
        mg_db_person = open_db(DB_PERSON_FILE);
    }
}

void update_organs_db()
{
    DBT k={0},d={0};
    DB_ORGANS_ITEM item ;
    int i ;

    if(mg_is_update_ing )
    {
        return ;
    }

    mg_is_update_ing = TRUE ;
    open_search_db();

    if(mg_db_organs != NULL)
    {
        //TEST
        for(i=0;i<1000;i++)
        {
            memset(&item,0,sizeof(item));
            g_snprintf(item.enterprise_id,sizeof(item.enterprise_id),"en%d",i);
            g_snprintf(item.qymc,sizeof(item.qymc),"%d",i);
            g_snprintf(item.id,sizeof(item.id),"id%d",i);
            item.counts  =  i+5 ;
            item.jcType =  1 ;
            item.dataType = 2 ;

            k.data = &item.id;
            k.size = sizeof(item.id);
            d.data = &item ;
            d.size = sizeof(item);
            mg_db_organs->put(mg_db_organs, NULL,&k, &d,0);
        }
        for(i=0;i<1000;i++)
        {
            memset(&item,0,sizeof(item));
            g_snprintf(item.enterprise_id,sizeof(item.enterprise_id),"en%d",i);
            g_snprintf(item.qymc,sizeof(item.qymc),"%d",i);
            g_snprintf(item.id,sizeof(item.id),"id%d",i);
            item.counts  =  i+15 ;
            item.jcType =  2 ;
            item.dataType = 2 ;

            k.data = &item.id;
            k.size = sizeof(item.id);
            d.data = &item ;
            d.size = sizeof(item);
            mg_db_organs->put(mg_db_organs, NULL,&k, &d,0);
        }
        mg_db_organs->sync(mg_db_organs,0);
    }
    mg_is_update_ing = FALSE ;
}

void update_person_db()
{
    DBT k={0},d={0};
    DB_PERSON_ITEM item ;
    int i ;

    if(mg_is_update_ing )
    {
        return ;
    }

    mg_is_update_ing = TRUE ;
    open_search_db();

    if(mg_db_person != NULL)
    {
        //TEST
        for(i=10000;i<20000;i++)
        {
            memset(&item,0,sizeof(item));
            g_snprintf(item.person_id,sizeof(item.person_id),"per%d",i);
            g_snprintf(item.xm,sizeof(item.xm),"xm%d",i);
            g_snprintf(item.sfzhm,sizeof(item.sfzhm),"%d",i);
            g_snprintf(item.id,sizeof(item.id),"id%d",i);
            item.counts  =  i+5 ;
            item.jcType =  1 ;
            item.dataType = 2 ;

            k.data = &item.id;
            k.size = sizeof(item.id);
            d.data = &item ;
            d.size = sizeof(item);
            mg_db_person->put(mg_db_person, NULL,&k, &d,0);
        }
        mg_db_person->sync(mg_db_person,0);
    }
    mg_is_update_ing = FALSE ;
}

/// 统计数据库
void stat_db()
{
    int ret ;
    DBT k ;
    DBT d ;
    DBC *dbcp = NULL ;
    DB_ORGANS_ITEM organs_item ;
    DB_PERSON_ITEM person_item ;

    open_search_db();

    mg_htxy_global.stat_organs_all = 0 ;
    mg_htxy_global.stat_person_all = 0 ;
    mg_htxy_global.stat_organs_shishi = 0 ;
    mg_htxy_global.stat_person_shishi = 0 ;

    memset(&organs_item,0,sizeof(organs_item));
    memset(&person_item,0,sizeof(person_item));

    if(mg_db_organs != NULL)
    {
        ret = mg_db_organs->cursor(mg_db_organs, NULL, &dbcp, 0);
        if(ret == 0)
        {
            memset(&k,0,sizeof(k));
            memset(&d,0,sizeof(d));
            k.data = &organs_item.id ;
            k.size = sizeof(organs_item.id);
            k.ulen = sizeof(organs_item.id);
            k.flags = DB_DBT_USERMEM;
            d.data = &organs_item;
            d.size = sizeof(organs_item);
            d.ulen = sizeof(organs_item);
            d.flags = DB_DBT_USERMEM;
            ret = dbcp->get(dbcp,&k,&d,DB_FIRST);
            if(ret == 0 )
            {
                do{
                    if(organs_item.is_shishi)
                    {
                        mg_htxy_global.stat_organs_shishi ++ ;
                    }
                    else
                    {
                        mg_htxy_global.stat_organs_all ++ ;
                    }
                    memset(&k,0,sizeof(k));
                    memset(&d,0,sizeof(d));
                    k.data = &organs_item.id ;
                    k.size = sizeof(organs_item.id);
                    k.ulen = sizeof(organs_item.id);
                    k.flags = DB_DBT_USERMEM;
                    d.data = &organs_item;
                    d.size = sizeof(organs_item);
                    d.ulen = sizeof(organs_item);
                    d.flags = DB_DBT_USERMEM;
                }while( (dbcp->get(dbcp,&k,&d,DB_NEXT) == 0 ) );
                dbcp->close(dbcp);
            }
        }
    }

    if(mg_db_person != NULL)
    {
        ret = mg_db_person->cursor(mg_db_person, NULL, &dbcp, 0);
        if(ret == 0)
        {
            memset(&k,0,sizeof(k));
            memset(&d,0,sizeof(d));
            k.data = &person_item.id ;
            k.size = sizeof(person_item.id);
            k.ulen = sizeof(person_item.id);
            k.flags = DB_DBT_USERMEM;
            d.data = &person_item;
            d.size = sizeof(person_item);
            d.ulen = sizeof(person_item);
            d.flags = DB_DBT_USERMEM;
            ret = dbcp->get(dbcp,&k,&d,DB_FIRST);
            if(ret == 0 )
            {
                do{
                    if(person_item.is_shishi)
                    {
                        mg_htxy_global.stat_person_shishi++ ;
                    }
                    else
                    {
                        mg_htxy_global.stat_person_all++ ;
                    }
                    memset(&k,0,sizeof(k));
                    memset(&d,0,sizeof(d));
                    k.data = &person_item.id ;
                    k.size = sizeof(person_item.id);
                    k.ulen = sizeof(person_item.id);
                    k.flags = DB_DBT_USERMEM;
                    d.data = &person_item;
                    d.size = sizeof(person_item);
                    d.ulen = sizeof(person_item);
                    d.flags = DB_DBT_USERMEM;
                }while( (dbcp->get(dbcp,&k,&d,DB_NEXT) == 0 ) );
                dbcp->close(dbcp);
            }
        }
    }
    RUN_GTK_FUNC(widget_update_init);
}

void update_all_db()
{
    if(mg_htxy_global.is_use_organs)
    {
        update_organs_db();
    }
    if(mg_htxy_global.is_use_person)
    {
        update_person_db();
    }
    stat_db() ;
}


gboolean info_find_user(const char* usrname)
{
    int ret ;
    DBT k ;
    DBT d ;
    DBC *dbcp = NULL ;
    DB_ORGANS_ITEM organs_item ;
    DB_PERSON_ITEM person_item ;
    gboolean is_find = FALSE ;

    memset(&organs_item,0,sizeof(organs_item));
    memset(&person_item,0,sizeof(person_item));

    open_search_db();
    mg_htxy_global.info_jiangli = 0 ;
    mg_htxy_global.info_chengjie = 0 ;

    if(mg_htxy_global.is_use_organs)
    {
        if(mg_db_organs != NULL)
        {
            ret = mg_db_organs->cursor(mg_db_organs, NULL, &dbcp, 0);
            if(ret == 0)
            {
                memset(&k,0,sizeof(k));
                memset(&d,0,sizeof(d));
                k.data = &organs_item.id ;
                k.size = sizeof(organs_item.id);
                k.ulen = sizeof(organs_item.id);
                k.flags = DB_DBT_USERMEM;
                d.data = &organs_item;
                d.size = sizeof(organs_item);
                d.ulen = sizeof(organs_item);
                d.flags = DB_DBT_USERMEM;
                ret = dbcp->get(dbcp,&k,&d,DB_FIRST);
                if(ret == 0 )
                {
                    do{
                        if(strcmp(organs_item.qymc,usrname) == 0 )
                        {
                            is_find = TRUE ;
                            g_strlcpy(mg_htxy_global.info_name,organs_item.qymc,sizeof(mg_htxy_global.info_name));
                            if(organs_item.jcType == JC_TYPE_JIANGLI  )
                            {
                                mg_htxy_global.info_jiangli = organs_item.counts ;
                            }
                            else
                            {
                                mg_htxy_global.info_chengjie = organs_item.counts ;
                            }
                        }
                        memset(&k,0,sizeof(k));
                        memset(&d,0,sizeof(d));
                        k.data = &organs_item.id ;
                        k.size = sizeof(organs_item.id);
                        k.ulen = sizeof(organs_item.id);
                        k.flags = DB_DBT_USERMEM;
                        d.data = &organs_item;
                        d.size = sizeof(organs_item);
                        d.ulen = sizeof(organs_item);
                        d.flags = DB_DBT_USERMEM;
                    }while( (dbcp->get(dbcp,&k,&d,DB_NEXT) == 0 ) );
                }
                dbcp->close(dbcp);
            }
        }
    }

    if(mg_htxy_global.is_use_person)
    {
        if(mg_db_person != NULL)
        {
            ret = mg_db_person->cursor(mg_db_person, NULL, &dbcp, 0);
            if(ret == 0)
            {
                memset(&k,0,sizeof(k));
                memset(&d,0,sizeof(d));
                k.data = &person_item.id ;
                k.size = sizeof(person_item.id);
                k.ulen = sizeof(person_item.id);
                k.flags = DB_DBT_USERMEM;
                d.data = &person_item;
                d.size = sizeof(person_item);
                d.ulen = sizeof(person_item);
                d.flags = DB_DBT_USERMEM;
                ret = dbcp->get(dbcp,&k,&d,DB_FIRST);
                if(ret == 0 )
                {
                    do{
                        if(strcmp(person_item.sfzhm,usrname) == 0 )
                        {
                            is_find = TRUE ;
                            g_strlcpy(mg_htxy_global.info_name,person_item.xm,sizeof(mg_htxy_global.info_name));
                            if(person_item.jcType == JC_TYPE_JIANGLI  )
                            {
                                mg_htxy_global.info_jiangli = person_item.counts ;
                            }
                            else
                            {
                                mg_htxy_global.info_chengjie = person_item.counts ;
                            }
                        }
                        memset(&k,0,sizeof(k));
                        memset(&d,0,sizeof(d));
                        k.data = &person_item.id ;
                        k.size = sizeof(person_item.id);
                        k.ulen = sizeof(person_item.id);
                        k.flags = DB_DBT_USERMEM;
                        d.data = &person_item;
                        d.size = sizeof(person_item);
                        d.ulen = sizeof(person_item);
                        d.flags = DB_DBT_USERMEM;
                    }while( (dbcp->get(dbcp,&k,&d,DB_NEXT) == 0 ) );
                }
                dbcp->close(dbcp);
            }
        }
    }

    return is_find ;
}

#ifdef __cplusplus
}
#endif

