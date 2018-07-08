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

#include "assets.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "map.h"
#include "main.h"
#include "tile.h"
#include "sound.h"
#include "tname.h"
#include "world.h"
#include "puzzle.h"
#include "screen.h"
#include "useful.h"
#include "player.h"
#include "palette.h"
#include "character.h"

FILE *yodesk_fileptr;
long yodesk_size = 0;
void *yodesk_data;

float ASSETS_PERCENT = 0.0f;
u8 ASSETS_LOADING = 1;
u16 NUM_MAPS = 0;

u32 version = 4;
u32* tile;
char **sound_files;

void *texture_buffers[0x2001];
#ifdef RENDER_GL
    GLuint texture[0x2001];
#endif
izon_data **zone_data;
//TNAME **tile_names;

u32 yodesk_seek = 0;

u8 load_demo = 0;
u8 is_yoda = 1;
u16 ipuznum = 0;

#ifdef PC_BUILD
#define log(f_, ...) printf((f_), __VA_ARGS__)
#elif WIIU
    #include <coreinit/debug.h>
    #define log(f_, ...) OSReport((f_), __VA_ARGS__)
#endif

#ifdef DAT_IN_EXEC
#define DAT_IN_RAM
extern u8 *yodesk_bin;
extern u32 yodesk_bin_size;
#endif

bool load_resources()
{
    char *file_to_load = is_yoda ? (load_demo ? "YodaDemo.dta" : "YODESK.DTA") : "DESKTOP.DAW";

#ifdef DAT_IN_EXEC
    log("%s is compiled in\n", file_to_load);
    yodesk_data = &yodesk_bin;
    yodesk_size = yodesk_bin_size;
#elif defined __vita__
    file_to_load = "ux0:/data/yoda/YODESK.DTA";
    SceUID yodesk_fd = sceIoOpen(file_to_load, SCE_O_RDONLY, 0777);
    if(yodesk_fd < 0) {
      log("Failed to load '%s'!\n", file_to_load);
      return false;
    }

    SceIoStat stat;
    if (sceIoGetstatByFd(yodesk_fd, &stat) < 0) {
      log("Failed to get size of '%s'!\n", file_to_load);
      return false;
    }
    yodesk_size = stat.st_size;
    log("Reading %s to RAM...\n", file_to_load);
    yodesk_data = malloc(yodesk_size);

    int bytes_read;
    if ((bytes_read=sceIoRead(yodesk_fd, yodesk_data, yodesk_size)) != yodesk_size) {
      log("only %d/%d bytes read to RAM!!\n", bytes_read, yodesk_size);
    }
    sceIoClose(yodesk_fd);
#else
    yodesk_fileptr = fopen(file_to_load, "rb");

    if(!yodesk_fileptr)
    {
        log("Failed to load '%s'!\n", file_to_load);
        printf("Failed to load '%s'!\n", file_to_load);
        return false;
    }

    fseek(yodesk_fileptr, 0, SEEK_END);
    yodesk_size = ftell(yodesk_fileptr);
    rewind(yodesk_fileptr);
#ifdef DAT_IN_RAM
    log("Reading %s to RAM...\n", file_to_load);
    yodesk_data = malloc(yodesk_size);
    fread(yodesk_data, yodesk_size, sizeof(u8), yodesk_fileptr);
#endif
#endif
    log("%s loaded, %lx bytes large\n", file_to_load, yodesk_size);

    u16 izon_count = 0;
    u8 found = 1;
    float last_percent = 0.0f;
    memset(texture_buffers, 0, sizeof(texture_buffers));
    while(1)
    {
        u32 tag_seek = get_location();
        char *tag = get_strn(4);

        ASSETS_PERCENT = ((float)tag_seek / (float)yodesk_size);
        if(found && ASSETS_PERCENT - last_percent > 0.1)
        {
            draw_screen();
            last_percent = ASSETS_PERCENT;
        }

        found = 1;
        if(!strncmp(tag, "VERS", 4)) //VERSion
        {
            log("Found VERS at %x, version number %x\n", tag_seek, read_long());
        }
        else if(!strncmp(tag, "STUP", 4)) //STartUP Graphic, uses yodesk_palette
        {
            log("Found STUP at %x\n", tag_seek);
            load_texture(288, get_location()+sizeof(u32), 0x2000); //Load Startup Texture past the last tile

            u32 len = read_long();
            seek(len+sizeof(u64)+tag_seek);
            draw_screen();
        }
        else if(!strncmp(tag, "ZONE", 4)) //ZONEs (maps)
        {
            log("Found ZONE at %x, ", tag_seek);

            u32 ZONE_LENGTH;

            if(is_yoda)
            {
                NUM_MAPS = read_short();
                u16 unknown = read_short();
                ZONE_LENGTH = read_long();
                seek(tag_seek+sizeof(u32)+sizeof(u16)+sizeof(u16)+sizeof(u32));

                log("unk %x, len %x\n", unknown, ZONE_LENGTH);
            }
            else
            {
                ZONE_LENGTH = read_long();
                NUM_MAPS = read_short();
                seek(tag_seek+sizeof(u32)+sizeof(u32)+sizeof(u16));

                log("len %x\n", ZONE_LENGTH);
            }
            zone_data = malloc(NUM_MAPS * sizeof(char*));
            for(int j = 0; j < NUM_MAPS; j++)
                zone_data[j] = (izon_data*)calloc(sizeof(izon_data), sizeof(u8));

            log("%i maps in DAT\n", NUM_MAPS);
            //world_init();
            map_init(NUM_MAPS);
        }
        else if(!strncmp(tag, "IZON", 4)) //Index of ZONE
        {
            izon_count++;
            log("Found IZON %i at %x\n", izon_count-1, tag_seek);
            zone_data[izon_count-1]->izon_offset = tag_seek;

            u32 len = read_long();
            seek(tag_seek+len);
        }
        else if(!strncmp(tag, "ZAUX", 4)) //Zone AuXiliary
        {
            log("Found ZAUX at %x, len %x\n", tag_seek, read_long());
            izon_count = 1;
        }
        else if(!strncmp(tag, "IZAX", 4)) //Index of ZAUX
        {
            log("Found IZAX at %x\n", tag_seek);
            zone_data[izon_count-1]->izax_offset = tag_seek;

            if(!is_yoda)
                izon_count++;

            u32 len = read_long();
            seek(tag_seek+len);
        }
        else if(!strncmp(tag, "ZAX2", 4)) //Zone AuXiliary 2
        {
            log("Found ZAX2 at %x, len %x\n", tag_seek, read_long());
            izon_count = 1;
        }
        else if(!strncmp(tag, "IZX2", 4)) //Index of ZAX2
        {
            log("Found IZX2 at %x\n", tag_seek);
            zone_data[izon_count-1]->izx2_offset = tag_seek;

            u32 len = read_long();
            seek(tag_seek+len);
        }
        else if(!strncmp(tag, "ZAX3", 4)) //Zone AuXiliary 3
        {
            log("Found ZAX3 at %x, len %x\n", tag_seek, read_long());
            izon_count = 1;
        }
        else if(!strncmp(tag, "IZX3", 4)) //Index of ZAX3
        {
            log("Found IZX3 at %x\n", tag_seek);
            zone_data[izon_count-1]->izx3_offset = tag_seek;

            u32 len = read_long();
            seek(tag_seek+len);
        }
        else if(!strncmp(tag, "ZAX4", 4)) //Zone AuXiliary 4
        {
            log("Found ZAX4 at %x, len %x\n", tag_seek, read_long());
            izon_count = 1;
        }
        else if(!strncmp(tag, "IZX4", 4)) //Index of ZAX4
        {
            log("Found IZX4 at %x\n", tag_seek);
            zone_data[izon_count-1]->izx4_offset = tag_seek;

            u32 len = read_long();
            seek(tag_seek+8+len+2);
        }
        else if(!strncmp(tag, "HTSP", 4)) //HoTSPot
        {
            log("Found HTSP at %x, len %x\n", tag_seek, read_long());
            izon_count = 1;

            while(1)
            {
                u16 id = read_short();
                u32 offset = get_location();

                log("Found Zone %x HTSP at %x\n", id, offset);

                if(id == 0xFFFF)
                    break;

                izon_count = id+1;
                zone_data[izon_count-1]->htsp_offset = offset;

                u16 num = read_short();
                seek_add(0xC*num);
            }
        }
        else if(!strncmp(tag, "ACTN", 4)) //ACToNs
        {
            log("Found ACTN at %x, len %x\n", tag_seek, read_long());
            izon_count = 1;
        }
        else if(!strncmp(tag, "IACT", 4)) //Index of ACTN
        {
            if(zone_data[izon_count-1]->iact_offset == 0)
            {
                zone_data[izon_count-1]->num_iacts = read_prefix();
                zone_data[izon_count-1]->iact_offset = tag_seek;
                zone_data[izon_count-1]->iact_offsets[0] = tag_seek;
                log("Found %u IACT%s at %x\n", zone_data[izon_count-1]->num_iacts, (zone_data[izon_count-1]->num_iacts > 1 && zone_data[izon_count-1]->num_iacts != 0 ? "s" : ""), tag_seek);

                //Indy lumps all their IACTs into one giant section
                //so we have to sift through them to link them to zones.
                //However we want to index all of our IACT items anyhow,
                //so this works.
                seek(tag_seek);
                u32 remaining_iacts = zone_data[izon_count - 1]->num_iacts+1;
                zone_data[izon_count - 1]->num_iacts = 0;
                u32 iact_index = 1;
                while (remaining_iacts > 0)
                {
                    char *tag_iact_look = get_strn(4);
                    if (!strncmp(tag_iact_look, "IACT", 4))
                    {
                        zone_data[izon_count-1]->iact_offsets[iact_index++] = get_location()-sizeof(u32);
                        remaining_iacts--;
                        zone_data[izon_count - 1]->num_iacts++;

                        if(remaining_iacts == 0 && is_yoda)
                        {
                            tag_seek = zone_data[izon_count-1]->iact_offsets[iact_index-2];
                        }
                    }
                    else if (!strncmp(tag_iact_look, "PUZ2", 4))
                    {
                        break;
                    }
                    else
                    {
                        seek_sub(sizeof(u32) - sizeof(u8));
                        u8 search_val = read_byte();
                        while(search_val != 'I' && search_val != 'P')
                        {
                            search_val = read_byte();
                        }
                        seek_sub(sizeof(u8));

                    }
                    free(tag_iact_look);
                }
                seek_sub(sizeof(u32));

                if(!is_yoda)
                    izon_count++;
            }

            //Yoda Stories actually has length identifiers for these...
            if(is_yoda)
            {
                seek(tag_seek + sizeof(u32));
                u32 len = read_long();
                seek(tag_seek + len + 0x8);
            }
        }
        else if(!strncmp(tag, "SNDS", 4)) //SouNDS
        {
            log("Found SNDS at %x, ", tag_seek);

            u32 length = read_long();
            u16 unk1 = read_short();
            sound_files = malloc(256 * sizeof(char*));
            log("unk1 %x\n", unk1);

            for(int j = 0; (get_location() - tag_seek) < (length - 2); j++)
            {
                u32 str_length = read_short();
                sound_files[j] = get_strn(str_length);
                log("%x: %x %s\n", j, str_length, sound_files[j]);
            }
            seek(tag_seek+length+0x8);
        }
        else if(!strncmp(tag, "TILE", 4)) //TILEs (graphics)
        {
            log("Found TILE at %x\n", tag_seek);
            int section_length = read_long();
            log("0x%x tiles in TILES\n", section_length / ((32*32)+4));
            for(u32 j = 0; j < section_length / ((32*32)+4); j++)
            {
                if(j % 0x100 == 0 || j == (section_length / ((32*32)+4))-1)
                {
                    log("%x of %x...\n", j, section_length / ((32 * 32) + 4));
                    ASSETS_PERCENT = ((float)get_location() / (float)yodesk_size);
                    draw_screen();
                }

                u32 tile_stuff = read_long();
                tile_metadata[j] = tile_stuff;
                load_texture(32, get_location(), j);
                seek_add(32*32*sizeof(u8));
            }
            seek(tag_seek+section_length+0x8);
        }
        else if(!strncmp(tag, "PUZ2", 4)) //Puzzle configurations maybe?
        {
            log("Found PUZ2 at %x, len %x\n", tag_seek, read_long());
            ipuz_data = malloc(512 * sizeof(char*));

            seek_add(sizeof(u16));
        }
        else if(!strncmp(tag, "IPUZ", 4)) //Index of PUZ2
        {
            log("Found IPUZ at %x\n", tag_seek);
            u16 id = read_prefix();

            ipuz_element *e = malloc(sizeof(ipuz_element));
            e->size = read_long();
            e->unk1 = read_long();
            e->unk2 = read_long();
            if(is_yoda)
            {
                e->unk3 = read_long();
            }
            e->unk4 = read_short();

            e->string1_len = read_short();
            for(u16 j = 0; j < e->string1_len; j++)
                e->string1[j] = read_byte();

            e->string2_len = read_short();
            for(u16 j = 0; j < e->string2_len; j++)
                e->string2[j] = read_byte();

            e->string3_len = read_short();
            for(u16 j = 0; j < e->string3_len; j++)
                e->string3[j] = read_byte();

            e->string4_len = read_short();
            for(u16 j = 0; j < e->string4_len; j++)
                e->string4[j] = read_byte();

            e->unused_len = read_short();
            for(u16 j = 0; j < e->unused_len; j++)
                e->unused[j] = read_byte();

            e->item_a = read_short();

            if(is_yoda)
            {
                e->item_b = read_short();
            }

            ipuz_data[id] = e;
            ipuznum++;

            seek(tag_seek+e->size+0xA);
        }
        else if(!strncmp(tag, "CHAR", 4)) //CHARacters
        {
            u32 size = read_long();
            log("Found CHAR at %x, size %x\n", tag_seek, size);

            char_data = malloc((size / (is_yoda ? 0x54 : 0x4E)) * sizeof(char*));

            for(int j = 0; j < (size / (is_yoda ? 0x54 : 0x4E)); j++)
            {
                u16 id = read_short();

                ichr_data *new_entry = malloc(sizeof(ichr_data));

                u32 start = get_location();
                new_entry->magic = read_long();
                new_entry->unk_1 = read_long();
                read_bytes(new_entry->name, 0x10); seek_add(0x10);
                new_entry->flags = read_long();
                new_entry->unk_4 = read_short();
                new_entry->unk_5 = read_long();
                for(int k = 0; k < 26; k++)
                    new_entry->frames[k] = read_short();

                char_data[id] = new_entry;
                log("%x - %-16s %x %x %x %x\n", id, char_data[id]->name, char_data[id]->unk_1, char_data[id]->flags, char_data[id]->unk_4, char_data[id]->unk_5);
                seek(start + (u32)(is_yoda ? 0x54 : 0x4E) - 2);
            }
            seek(tag_seek+size+8);
        }
        else if(!strncmp(tag, "CHWP", 4)) //CHaracter WeaPons
        {
            log("Found CHWP at %x\n", tag_seek);

            u32 len = read_long();

            chwp_data = malloc(((len/sizeof(chwp_entry))+1) * sizeof(chwp_entry*));

            u16 entry_index = 0;
            while(1)
            {
                chwp_entry *new_entry = malloc(sizeof(chwp_entry));
                chwp_data[entry_index++] = new_entry;

                u16 id_1 = read_short();
                u16 id_2 = read_short();
                u16 health = read_short();

                new_entry->id_1 = id_1;
                new_entry->id_2 = id_2;
                new_entry->health = health;

                if(id_1 == 0xFFFF)
                    break;

                if(char_data[id_1]->flags & ICHR_IS_WEAPON)
                    log("%-16s is a weapon with sound %-14s, health %x?\n", char_data[id_1]->name, sound_files[id_2], health);
                else
                    log("%-16s gets weapon %-25s, health %x\n", char_data[id_1]->name, (id_2 == 0xFFFF ? "none" : (char*)char_data[id_2]->name), health);
            }
            seek(tag_seek+len+8);
        }
        else if(!strncmp(tag, "CAUX", 4)) //Character AUXiliary
        {
            log("Found CAUX at %x\n", tag_seek);

            u32 len = read_long();

            caux_data = malloc(((len/sizeof(caux_entry))+1) * sizeof(caux_entry*));

            u16 entry_index = 0;
            while(1)
            {
                caux_entry *new_entry = malloc(sizeof(caux_entry));
                caux_data[entry_index++] = new_entry;

                u16 id_1 = read_short();
                u16 damage = read_short();

                new_entry->id_1 = id_1;
                new_entry->damage = damage;

                if(id_1 == 0xFFFF)
                    break;

                if(char_data[id_1]->flags & ICHR_IS_WEAPON)
                    log("%-16s is a weapon,          damage: %x\n", char_data[id_1]->name, damage);
                else
                    log("%-16s not a weapon, ambient damage: %x\n", char_data[id_1]->name, damage);
            }
            seek(tag_seek+len+8);
        }
        else if (!strncmp(tag, "ANAM", 4)) //Action names
        {
            log("Found ANAM at %x\n", tag_seek);
        }
        else if (!strncmp(tag, "PNAM", 4)) //Prize names?
        {
            log("Found PNAM at %x\n", tag_seek);
        }
        else if(!strncmp(tag, "TNAM", 4)) //Tile names
        {
            log("Found TNAM at %x\n", tag_seek);

            u32 len = read_long();

            char *nop = "NO NAME";

            for(int j = 0; j < 0x10000; j++)
                tile_names[j] = nop;

            for(int j = 0; j < len / (is_yoda ? 26 : 18); j++)
            {
                u16 id = read_short();
                char *name;
                if (id == 0xFFFF)
                    name = nop;
                else
                    name = get_strn((is_yoda ? 24 : 16));

                tile_names[id] = name;

                //log("%x, %s\n", id, tile_names[id]);
            }
            seek(tag_seek+len+8);
        }
        else if(!strncmp(tag, "ENDF", 4))
        {
            //print_iact_stats();
            for(int j = 0; j < ipuznum; j++)
            {
                ipuz_element *e = ipuz_data[j];
                if(e == 0)
                    continue;

                /*if(is_yoda)
                	log("%x: %x %x %x %x \"%s\" \"%s\" \"%s\" \"%s\", %s (%x %x), %s (%x, %x)\n", j, e->unk1, e->unk2, e->unk3, e->unk4, e->string1, e->string2, e->string3, e->string4, tile_names[e->item_a], e->item_a, tile_metadata[e->item_b], tile_names[e->item_b], e->item_b, tile_metadata[e->item_b]);
                else
                	log("%x: %x %x %x \"%s\" \"%s\" \"%s\" \"%s\", %s (%x)\n", j, e->unk1, e->unk2, e->unk4, e->string1, e->string2, e->string3, e->string4, tile_names[e->item_a], e->item_a);*/
            }
            log("Found ENDF at %x\n", tag_seek);
            break;
        }
        else
        {
            //Skip all bytes which cannot possibly be tags
            seek_sub(sizeof(u32)-sizeof(u8));
            u8 seek_tag = read_byte();
            while(seek_tag < 'A' || seek_tag > 'Z')
            {
                seek_tag = read_byte();
            }
            seek_sub(sizeof(u8));

            found = 0;
        }
        free(tag);
    }

    player_init();
    load_map(0);
    init_screen();
    render_map();
    ASSETS_LOADING = 0;

    return true;
}

void load_texture(u16 width, u32 data_loc, u32 texture_num)
{
    u32 orig_seek = get_location();
    seek(data_loc);

#ifdef RENDER_GL
    u32 *data_buffer = malloc((size_t)(width * width * 4));
    texture_buffers[texture_num] = data_buffer;
    int index = 0;
    for(int i = 0; i < width * width; i++)
    {
        int color_index = read_byte();
        u32 color;
        if(is_yoda)
            color = ((u8)(yodesk_palette[(color_index * 4)]) << 16) + ((u8)(yodesk_palette[(color_index * 4) + 1]) << 8) + ((u8)(yodesk_palette[(color_index * 4) + 2]) << 0);
        else
            color = ((u8)(indy_palette[(color_index * 4)]) << 16) + ((u8)(indy_palette[(color_index * 4) + 1]) << 8) + ((u8)(indy_palette[(color_index * 4) + 2]) << 0);

        if(color_index != 0)
            color |= 0xFF000000; //Make sure it's not transparent

        data_buffer[(width * width) - i - 1] = color;
        index++;
    }
    glGenTextures(0x1, &texture[texture_num]);
    glBindTexture( GL_TEXTURE_2D, texture[texture_num]);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, width, 0, GL_RGBA, GL_UNSIGNED_BYTE, data_buffer);

#ifdef PC_BUILD
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
#endif
#elif RENDER_BUFFER
    void *data_buffer = malloc((size_t)(width * width * sizeof(u8)));
    read_bytes(data_buffer, (size_t)(width * width * sizeof(u8)));
    texture_buffers[texture_num] = data_buffer;
#endif

    seek(orig_seek);
}

void seek(u32 location)
{
    yodesk_seek = location;
}

void seek_add(u32 amount)
{
    yodesk_seek += amount;
}

void seek_sub(u32 amount)
{
    yodesk_seek -= amount;
}

u32 get_location()
{
    return yodesk_seek;
}

char *get_str()
{
    void *buffer = malloc(0x100);
#ifndef DAT_IN_RAM
    fseek(yodesk_fileptr, yodesk_seek, SEEK_SET);
    fread(buffer, 0x100, 1, yodesk_fileptr);
#else
    memcpy(buffer, yodesk_data+yodesk_seek, 0x100);
#endif

    u32 len = strlen((char*)(buffer));
    char *out = malloc(len+1);
    strcpy(out, (char*)(buffer));
    free(buffer);

    yodesk_seek += len;
    return out;
}

char *get_strn(size_t len)
{
    char *out = calloc(len+1, sizeof(u8));
#ifndef DAT_IN_RAM
    fseek(yodesk_fileptr, yodesk_seek, SEEK_SET);
    fread(out, len, 1, yodesk_fileptr);
#else
    memcpy(out, yodesk_data+yodesk_seek, len);
#endif
    out[len] = 0;

    yodesk_seek += len;
    return out;
}

u32 read_long()
{
    u32 value;
#ifndef DAT_IN_RAM
    fseek(yodesk_fileptr, yodesk_seek, SEEK_SET);
    fread(&value, sizeof(u32), 1, yodesk_fileptr);
#else
    value = *(u32*)(yodesk_data+yodesk_seek);
#endif

#if BIG_ENDIAN && !LITTLE_ENDIAN
    value = (value >> 24) | ((value & 0xFF0000) >> 8) | ((value & 0xFF00) << 8) | (value << 24);
#endif

    yodesk_seek += 4;
    return value;
}

u16 read_short()
{
    u16 value;
#ifndef DAT_IN_RAM
    fseek(yodesk_fileptr, yodesk_seek, SEEK_SET);
    fread(&value, sizeof(u16), 1, yodesk_fileptr);
#else
    value = *(u16*)(yodesk_data+yodesk_seek);
#endif

#if BIG_ENDIAN && !LITTLE_ENDIAN
    value = (u16)((value & 0xFF00) >> 8) | ((value & 0xFF) << 8);
#endif

    yodesk_seek += 2;
    return value;
}

u16 read_prefix()
{
    seek_sub(sizeof(u32)+sizeof(u16));
    u16 prefix = read_short();
    seek_add(sizeof(u32));

    return prefix;
}

u8 read_byte()
{
    u8 value;
#ifndef DAT_IN_RAM
    fseek(yodesk_fileptr, yodesk_seek, SEEK_SET);
    fread(&value, sizeof(u8), 1, yodesk_fileptr);
#else
    value = *(u8*)(yodesk_data+yodesk_seek);
#endif

    yodesk_seek += 1;
    return value;
}

void read_bytes(void *out, size_t size)
{
#ifndef DAT_IN_RAM
    fseek(yodesk_fileptr, yodesk_seek, SEEK_SET);
    fread(out, size, 1, yodesk_fileptr);
#else
    memcpy(out, yodesk_data+yodesk_seek, size);
#endif
}
