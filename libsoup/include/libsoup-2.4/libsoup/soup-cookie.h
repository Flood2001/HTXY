/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * Copyright 2007, 2008 Red Hat, Inc.
 */

#ifndef SOUP_COOKIE_H
#define SOUP_COOKIE_H 1

#include <libsoup/soup-types.h>

G_BEGIN_DECLS

struct _SoupCookie {
	char     *name;
	char     *value;
	char     *domain;
	char     *path;
	SoupDate *expires;
	gboolean  secure;
	gboolean  http_only;
};

#define SOUP_COOKIE_MAX_AGE_ONE_HOUR (60 * 60)
#define SOUP_COOKIE_MAX_AGE_ONE_DAY  (SOUP_COOKIE_MAX_AGE_ONE_HOUR * 24)
#define SOUP_COOKIE_MAX_AGE_ONE_WEEK (SOUP_COOKIE_MAX_AGE_ONE_DAY * 7)
#define SOUP_COOKIE_MAX_AGE_ONE_YEAR (SOUP_COOKIE_MAX_AGE_ONE_DAY * 365.2422)

SoupCookie *soup_cookie_new                     (const char  *name,
						 const char  *value,
						 const char  *domain,
						 const char  *path,
						 int          max_age);
SoupCookie *soup_cookie_parse                   (const char  *header,
						 SoupURI     *origin);

void        soup_cookie_set_name                (SoupCookie  *cookie,
						 const char  *name);
void        soup_cookie_set_value               (SoupCookie  *cookie,
						 const char  *value);
void        soup_cookie_set_domain              (SoupCookie  *cookie,
						 const char  *domain);
void        soup_cookie_set_path                (SoupCookie  *cookie,
						 const char  *path);
void        soup_cookie_set_max_age             (SoupCookie  *cookie,
						 int          max_age);
void        soup_cookie_set_expires             (SoupCookie  *cookie,
						 SoupDate    *expires);
void        soup_cookie_set_secure              (SoupCookie  *cookie,
						 gboolean     secure);
void        soup_cookie_set_http_only           (SoupCookie  *cookie,
						 gboolean     secure);

char       *soup_cookie_to_set_cookie_header    (SoupCookie  *cookie);
char       *soup_cookie_to_cookie_header        (SoupCookie  *cookie);

void        soup_cookie_free                    (SoupCookie  *cookie);

GSList     *soup_cookies_from_response          (SoupMessage *msg);
GSList     *soup_cookies_from_request           (SoupMessage *msg);

void        soup_cookies_to_response            (GSList      *cookies,
						 SoupMessage *msg);
void        soup_cookies_to_request             (GSList      *cookies,
						 SoupMessage *msg);

void        soup_cookies_free                   (GSList      *cookies);

char       *soup_cookies_to_cookie_header       (GSList      *cookies);

gboolean    soup_cookie_applies_to_uri          (SoupCookie  *cookie,
						 SoupURI     *uri);

G_END_DECLS

#endif /* SOUP_COOKIE_H */
