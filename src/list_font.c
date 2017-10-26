/////////////////////////////////////////////////////
/// Copyright (C) 2017 Hrsoft Corporation, All rights reserved.
/// @file list_font.c
/// @version 1.0
/// @date 2017-10-26
/// @brief Ã¶¾Ù×ÖÌå
/////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hrutil/hrutil.h>
#include <gtkutil/gtkutil.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#include <glib.h>
#include <pango/pangocairo.h>

static void list_fonts ()
{
    int i;
    PangoFontFamily ** families;
    int n_families;
    PangoFontMap * fontmap;

    fontmap = pango_cairo_font_map_get_default();
    pango_font_map_list_families (fontmap, & families, & n_families);
    printf ("There are %d families\n", n_families);
    for (i = 0; i < n_families; i++) {
        PangoFontFamily * family = families[i];
        const char * family_name;

        family_name = pango_font_family_get_name (family);
        printf ("Family %d : %s\n", i, family_name);
    }
    g_free (families);
}

int main (int argc, char ** argv)
{
    list_fonts ();
    return 0;
}

#ifdef __cplusplus
}
#endif

