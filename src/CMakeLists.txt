INCLUDE_DIRECTORIES(AFTER ${CMAKE_SOURCE_DIR}/HTXY/trunk/libsoup/include/libsoup-2.4)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/HTXY/trunk/libsoup/lib)
ADD_EXECUTABLE(HTXY WIN32 ${NM3000_APP_SRC}
    main.c
    windows_sys.cpp
    CsystemTray.cpp
    CsystemTray.h
    win_login.c
    win_login.h
    win_main_frame.c
    win_main_frame.h
    win_show_info.c
    win_show_info.h
    win_show_set.c
    win_show_set.h
    data_calc_util.c
    data_calc_util.h
    resource.h
    UsbChange.rc
    )
SET_TARGET_PROPERTIES(HTXY PROPERTIES LINK_FLAGS "-Wl,--allow-shlib-undefined")

TARGET_LINK_LIBRARIES(HTXY gtkutil)
TARGET_LINK_LIBRARIES(HTXY hrxml)
TARGET_LINK_LIBRARIES(HTXY hrutil)
TARGET_LINK_LIBRARIES(HTXY hrjson)
TARGET_LINK_LIBRARIES(HTXY libdb60.lib)
TARGET_LINK_LIBRARIES(HTXY libsoup-2.4.dll)
#GTK联接库
if(FOR_GTK3)
    TARGET_LINK_LIBRARIES(HTXY glib-2.0)
    TARGET_LINK_LIBRARIES(HTXY gthread-2.0)
    TARGET_LINK_LIBRARIES(HTXY gio-2.0)
    TARGET_LINK_LIBRARIES(HTXY atk-1.0)
    TARGET_LINK_LIBRARIES(HTXY pango-1.0)
    TARGET_LINK_LIBRARIES(HTXY cairo)
    TARGET_LINK_LIBRARIES(HTXY gdk_pixbuf-2.0)
    TARGET_LINK_LIBRARIES(HTXY gmodule-2.0)
    TARGET_LINK_LIBRARIES(HTXY gobject-2.0)
    if(WIN32)
    TARGET_LINK_LIBRARIES(HTXY iconv)
    TARGET_LINK_LIBRARIES(HTXY gtk-win32-3.0)
    TARGET_LINK_LIBRARIES(HTXY gdk-win32-3.0)
    TARGET_LINK_LIBRARIES(HTXY gailutil)
    else(WIN32)
    TARGET_LINK_LIBRARIES(HTXY gtk-3)
    TARGET_LINK_LIBRARIES(HTXY gdk-3)
    TARGET_LINK_LIBRARIES(HTXY z)
    TARGET_LINK_LIBRARIES(HTXY gailutil-3)
    TARGET_LINK_LIBRARIES(HTXY m)
    endif(WIN32)
else(FOR_GTK3)
    TARGET_LINK_LIBRARIES(HTXY glib-2.0)
    TARGET_LINK_LIBRARIES(HTXY gthread-2.0)
    TARGET_LINK_LIBRARIES(HTXY gio-2.0)
    TARGET_LINK_LIBRARIES(HTXY atk-1.0)
    TARGET_LINK_LIBRARIES(HTXY pango-1.0)
    TARGET_LINK_LIBRARIES(HTXY cairo)
    TARGET_LINK_LIBRARIES(HTXY gdk_pixbuf-2.0)
    TARGET_LINK_LIBRARIES(HTXY gmodule-2.0)
    TARGET_LINK_LIBRARIES(HTXY gobject-2.0)
    if(WIN32)
    TARGET_LINK_LIBRARIES(HTXY iconv)
    TARGET_LINK_LIBRARIES(HTXY gtk-win32-2.0)
    TARGET_LINK_LIBRARIES(HTXY gdk-win32-2.0)
    else(WIN32)
    TARGET_LINK_LIBRARIES(HTXY gtk-x11-2.0)
    TARGET_LINK_LIBRARIES(HTXY gdk-x11-2.0)
    TARGET_LINK_LIBRARIES(HTXY z)
    TARGET_LINK_LIBRARIES(HTXY m)
    endif(WIN32)
endif(FOR_GTK3)

