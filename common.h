/*************************************************************************
	> File Name: common.h
	> Author: Yanxw
	> Mail: winston.yan@outlook.com
	> Created Time: Sat 18 Sep 2021 01:52:00 PM CST
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H

#ifdef DEBUG
#  define D(x) (x)
#else
#  define D(x) do {} while (0)
#endif

#define BEGINS(x) namespace x { // begin of namespace
#define ENDS(x) } // end of namespace

#define COLOR(color_id, str) \
        "\033[" #color_id "m" str "\033[0m"
#define BG_BLACK(str)   COLOR(40, str)
#define BG_RED(str)     COLOR(41, str)
#define BG_GREEN(str)   COLOR(42, str)
#define BG_YELLOW(str)  COLOR(43, str)
#define BG_BLUE(str)    COLOR(44, str)
#define BG_MAGENTA(str) COLOR(45, str)
#define BG_CYAN(str)    COLOR(46, str)
#define BG_WHITE(str)   COLOR(47, str)

#define FG_BLACK(str)   COLOR(30, str)
#define FG_RED(str)     COLOR(31, str)
#define FG_GREEN(str)   COLOR(32, str)
#define FG_YELLOW(str)  COLOR(33, str)
#define FG_BLUE(str)    COLOR(34, str)
#define FG_MAGENTA(str) COLOR(35, str)
#define FG_CYAN(str)    COLOR(36, str)
#define FG_WHITE(str)   COLOR(37, str)



#endif
