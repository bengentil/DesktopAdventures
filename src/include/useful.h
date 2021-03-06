/*  DesktopAdventures, A reimplementation of the Desktop Adventures game engine
 *
 *  DesktopAdventures is the legal property of its developers, whose names
 *  can be found in the AUTHORS file distributed with this source
 *  distribution.
 *
 *  DesktopAdventures is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, see <http://www.gnu.org/licenses/>
 */

#ifndef USEFUL_H
#define USEFUL_H

#ifdef PC_BUILD
    #include <stdint.h>
    #define random_val() rand()
    typedef uint8_t u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;

    typedef int8_t s8;
    typedef int16_t s16;
    typedef int32_t s32;
    typedef int64_t s64;

    typedef volatile u8 vu8;
    typedef volatile u16 vu16;
    typedef volatile u32 vu32;
    typedef volatile u64 vu64;

    typedef volatile s8 vs8;
    typedef volatile s16 vs16;
    typedef volatile s32 vs32;
    typedef volatile s64 vs64;

    #define bool u8
    #define BIT(n) (1<<n)
    #define true 0x1
    #define false 0x0
#elif defined _3DS
    #include <3ds.h>
    #include <stdarg.h>
    #define random_val() rand()

    static inline void log(const char *fmt, ...)
    {
        char *str = malloc(0x400);
        va_list args;
        va_start(args, fmt);
        vsprintf(str, fmt, args);
        va_end(args);

        if(str[strlen(str)-1] == '\n')
            str[strlen(str)-1] = 0;

        svcOutputDebugString(str, strlen(str));
        free(str);
    }
#elif defined SWITCH
    #include <switch.h>
    #include <stdarg.h>
    #define random_val() rand()

    static inline void log(const char *fmt, ...)
    {
        char *str = malloc(0x400);
        va_list args;
        va_start(args, fmt);
        vsprintf(str, fmt, args);
        va_end(args);

        if(str[strlen(str)-1] == '\n')
            str[strlen(str)-1] = 0;

        svcOutputDebugString(str, strlen(str));
        free(str);
    }
#elif defined WIIU
    #include <time.h>
    #include <wut.h>
    #include <coreinit/thread.h>
    #include <coreinit/systeminfo.h>
    #define BIT(n) (1<<n)
    static inline int usleep(useconds_t usec)
    {
        OSSleepTicks((usec/1000/1000) * (OSGetSystemInfo()->clockSpeed / 4));
        return 0;
    }
    #define random_val() 1 //https://xkcd.com/221 (TODO)
#endif

#ifdef __EMSCRIPTEN__
int usleep(unsigned);
#endif

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#define CONTAINED(x, x1, x2) (x > x1 && x < x2)
#define CONTAINED_2D(x, y, x1, y1, x2, y2) (CONTAINED(x,x1,x2) && CONTAINED(y,y1,y2))

#define SCREEN_TILE_WIDTH (SCREEN_WIDTH / 32)
#define SCREEN_TILE_HEIGHT (SCREEN_HEIGHT / 32)

#define SCREEN_BPP     32

u8 *readFileToBytes(char* file, long *size);

#endif
