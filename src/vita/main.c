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

#include <stdio.h>
#include <time.h>

#include "useful.h"
#include "assets.h"
#include "screen.h"
#include "input.h"
#include "map.h"
#include "ui.h"

uint16_t current_map = 0;
bool quit = false;
bool win95_sim = false;

#ifdef VITA_NET_DEBUG
// from https://gist.github.com/xerpi/e426284df19c217a8128
int _dbgsock = 0;
void *net_memory = NULL;

void net_send(const char *fmt, ...)
{
    char str[512];
    va_list args;
    va_start(args, fmt);
    vsprintf(str, fmt, args);
    va_end(args);

    if(str[strlen(str)-1] == '\n')
    str[strlen(str)-1] = 0;

    sceNetSend(_dbgsock, str, strlen(str), 0);
    sceNetSend(_dbgsock, "\n\x00", 2, 0);

}

#define NET_INIT_SIZE 1*1024*1024
void net_init()
{
    SceNetSockaddrIn server;

    sceSysmoduleLoadModule(SCE_SYSMODULE_NET);

    if (sceNetShowNetstat() == SCE_NET_ERROR_ENOTINIT)
    {

        net_memory = malloc(NET_INIT_SIZE);

        SceNetInitParam initparam;
        initparam.memory = net_memory;
        initparam.size = NET_INIT_SIZE;
        initparam.flags = 0;

        sceNetInit(&initparam);
        sceKernelDelayThread(100*1000);
    }

    server.sin_len = sizeof(server);
    server.sin_family = SCE_NET_AF_INET;
    sceNetInetPton(SCE_NET_AF_INET, NET_DEBUG_HOST, &server.sin_addr);
    server.sin_port = sceNetHtons(NET_DEBUG_PORT);
    memset(server.sin_zero, 0, sizeof(server.sin_zero));

    _dbgsock = sceNetSocket("vitanetdbg", SCE_NET_AF_INET, SCE_NET_SOCK_STREAM, 0);
    sceNetConnect(_dbgsock, (SceNetSockaddr *)&server, sizeof(server));
}
#endif

u32 random_val()
{
    u32 val;
    sceKernelGetRandomNumber(&val, 4);
    return val;
}

int main()
{
    #ifdef VITA_NET_DEBUG
    net_init();
    #endif

    vglInit(0x80000);
    vglWaitVblankStart(GL_TRUE);

    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    glEnable(GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glViewport(0,0,960,544);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
    glOrtho(0,960,544,0,1,-1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, 0);

    load_resources();

    clock_t last_time = clock();
    while (!quit)
    {
        clock_t time = clock();
        double delta = (double)(time - last_time)/(CLOCKS_PER_SEC/1000.0);
        last_time = time;

        reset_input_state();
        update_input();
        ui_update();
        update_world(delta);

        if(quit) break;
    }

    // Exit services
    vglEnd();
    return 0;
}

void render_flip_buffers()
{
}

void update_input()
{
    SceCtrlData ctrl;
    sceCtrlPeekBufferPositive(0, &ctrl, 1);

    if (ctrl.buttons & SCE_CTRL_START)
    quit = true;

    if(ctrl.buttons & SCE_CTRL_SQUARE)
    {
        if(current_map < NUM_MAPS)
        {
            unload_map();
            current_map++;
            load_map(current_map);
        }
    }
    else if(ctrl.buttons & SCE_CTRL_CIRCLE)
    {
        if(current_map > 0)
        {
            unload_map();
            current_map--;
            load_map(current_map);
        }
    }

    if(ctrl.buttons & SCE_CTRL_UP)
    button_move_up();
    else if(ctrl.buttons & SCE_CTRL_RIGHT)
    button_move_right();
    else if(ctrl.buttons & SCE_CTRL_LEFT)
    button_move_left();
    else if(ctrl.buttons & SCE_CTRL_DOWN)
    button_move_down();

    if(ctrl.buttons & SCE_CTRL_CROSS)
    button_fire();
}

void render_pre()
{
    vglStartRendering();
}

void render_post()
{
    vglStopRendering();
}

void drawFillRect(int x1, int y1, int x2, int y2, char r, char g, char b, char a)
{
}

void drawPixel(int x, int y, char r, char g, char b, char a)
{
}

void fillScreen(char r, char g, char b, char a)
{
}

void render_set_target(ui_render_target* target)
{
}
