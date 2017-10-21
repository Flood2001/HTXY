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
    int rv = -1 ;
    const char* str;

    char exe_path[256];
    char path[256];

    hrutil_get_exe_dir(exe_path);
    g_snprintf(path,sizeof(path),"%sconfig.json",exe_path);

    root = hrjson_load_file(path);
    if(root == NULL)
    {
        goto end ;
    }

    //listenser
    listenser = hrjson_object_get_key(root,"listenser");
    if(listenser)
    {
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

static DB *mg_db_organs = NULL ;
#define DB_ORGANS_FILE "data/organs.db"

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
    g_snprintf(path,sizeof(path),"%s%s",dir,relative_path);
    ret = db_create(&dbp, NULL,0);
    if(0 != ret)
    {
        dbp = NULL ;
        goto quit ;
    }
    ret = dbp->set_bt_compare(dbp, db_comp_id);
    ret = dbp->open(dbp, NULL, path, path, DB_BTREE, db_flag , 0664);
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
}

void update_organs_db()
{
    DBT k={0},d={0};
    DB_ORGANS_ITEM item ;
    int i ;

    open_search_db();

    if(mg_db_organs != NULL)
    {
        //TEST
        for(i=0;i<256;i++)
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
        mg_db_organs->sync(mg_db_organs,0);
    }
}

gboolean info_find_user(const char* usrname)
{
    int ret ;
    DBT k ;
    DBT d ;
    DBC *dbcp = NULL ;
    DB_ORGANS_ITEM organs_item ;
    gboolean is_find = FALSE ;

    memset(&organs_item,0,sizeof(organs_item));

    open_search_db();

    if(mg_db_organs == NULL)
    {
        return FALSE ;
    }

    ret = mg_db_organs->cursor(mg_db_organs, NULL, &dbcp, 0);
    if(ret != 0)
    {
        return FALSE ;
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
    ret = dbcp->get(dbcp,&k,&d,DB_FIRST);
    if(ret == 0 )
    {
        do{
            if(strcmp(organs_item.qymc,usrname) == 0 )
            {
                is_find = TRUE ;
                break ;
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

    if(is_find)
    {
        g_strlcpy(mg_htxy_global.info_name,organs_item.qymc,sizeof(mg_htxy_global.info_name));
        if(organs_item.jcType ==1 )
        {
            mg_htxy_global.info_jiangli = organs_item.counts ;
        }
        else
        {
            mg_htxy_global.info_chengjie = organs_item.counts ;
        }
    }

    return is_find ;
}

#ifdef __cplusplus
}
#endif

