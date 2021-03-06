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

#ifndef PALETTE_H
#define PALETTE_H

#include "useful.h"

void palette_animate();

//BGRA
u8 yodesk_palette[0x400];


static const u8 indy_palette[0x400] =
{
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0xc1, 0xcc, 0xd9, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xff, 0x00,
    0x00, 0x00, 0xd7, 0x00,
    0x00, 0x00, 0xb3, 0x00,
    0x00, 0x00, 0x8b, 0x00,
    0x00, 0x00, 0x67, 0x00,
    0x00, 0x00, 0x43, 0x00,
    0xfb, 0xfb, 0xfb, 0x00,
    0xe3, 0xe3, 0xe3, 0x00,
    0xd3, 0xd3, 0xd3, 0x00,
    0xc3, 0xc3, 0xc3, 0x00,
    0xb3, 0xb3, 0xb3, 0x00,
    0xab, 0xab, 0xab, 0x00,
    0x9b, 0x9b, 0x9b, 0x00,
    0x8b, 0x8b, 0x8b, 0x00,
    0x7b, 0x7b, 0x7b, 0x00,
    0x73, 0x73, 0x73, 0x00,
    0x63, 0x63, 0x63, 0x00,
    0x53, 0x53, 0x53, 0x00,
    0x4b, 0x4b, 0x4b, 0x00,
    0x3b, 0x3b, 0x3b, 0x00,
    0x2b, 0x2b, 0x2b, 0x00,
    0x23, 0x23, 0x23, 0x00,
    0x00, 0xc7, 0x43, 0x00,
    0x00, 0xb7, 0x3f, 0x00,
    0x00, 0xab, 0x3f, 0x00,
    0x00, 0x9f, 0x3b, 0x00,
    0x00, 0x93, 0x37, 0x00,
    0x00, 0x87, 0x33, 0x00,
    0x00, 0x7b, 0x33, 0x00,
    0x00, 0x6f, 0x2f, 0x00,
    0x00, 0x63, 0x2b, 0x00,
    0x00, 0x53, 0x23, 0x00,
    0x00, 0x47, 0x1f, 0x00,
    0x00, 0x37, 0x17, 0x00,
    0x00, 0x27, 0x0f, 0x00,
    0x00, 0x1b, 0x0b, 0x00,
    0x00, 0x0b, 0x07, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x3b, 0xfb, 0x7b, 0x00,
    0x6b, 0x7b, 0xc3, 0x00,
    0x5b, 0x53, 0xab, 0x00,
    0x53, 0x43, 0x93, 0x00,
    0x53, 0x2b, 0x7b, 0x00,
    0x4b, 0x1b, 0x63, 0x00,
    0x3b, 0x13, 0x3b, 0x00,
    0xab, 0xd7, 0xff, 0x00,
    0x8f, 0xc3, 0xf3, 0x00,
    0x73, 0xb3, 0xe7, 0x00,
    0x5b, 0xa3, 0xdb, 0x00,
    0x43, 0x97, 0xcf, 0x00,
    0x2f, 0x8b, 0xc3, 0x00,
    0x1b, 0x7f, 0xb7, 0x00,
    0x0b, 0x73, 0xaf, 0x00,
    0x00, 0x6b, 0xa3, 0x00,
    0xeb, 0xff, 0xff, 0x00,
    0xd7, 0xf3, 0xf3, 0x00,
    0xc7, 0xe7, 0xe7, 0x00,
    0xb7, 0xdb, 0xdb, 0x00,
    0xa3, 0xcf, 0xcf, 0x00,
    0x97, 0xc3, 0xc3, 0x00,
    0x7f, 0xb3, 0xb3, 0x00,
    0x63, 0xa3, 0xa3, 0x00,
    0x4f, 0x93, 0x93, 0x00,
    0x3b, 0x83, 0x83, 0x00,
    0x2b, 0x73, 0x73, 0x00,
    0x1b, 0x5f, 0x5f, 0x00,
    0x0f, 0x4f, 0x4f, 0x00,
    0x07, 0x3f, 0x3f, 0x00,
    0x00, 0x2f, 0x2f, 0x00,
    0x00, 0x1f, 0x1f, 0x00,
    0x5b, 0xfb, 0xd3, 0x00,
    0x43, 0xfb, 0xc3, 0x00,
    0x23, 0xfb, 0xb3, 0x00,
    0x00, 0xfb, 0xa3, 0x00,
    0x00, 0xe3, 0x93, 0x00,
    0x00, 0xcb, 0x83, 0x00,
    0x00, 0xb3, 0x73, 0x00,
    0x00, 0x9b, 0x63, 0x00,
    0x00, 0x5b, 0x8b, 0x00,
    0x00, 0x4f, 0x77, 0x00,
    0x00, 0x43, 0x67, 0x00,
    0x00, 0x37, 0x57, 0x00,
    0x00, 0x2f, 0x47, 0x00,
    0x00, 0x23, 0x37, 0x00,
    0x00, 0x17, 0x27, 0x00,
    0x00, 0x0f, 0x17, 0x00,
    0x00, 0xfb, 0x4f, 0x00,
    0x00, 0xef, 0x4b, 0x00,
    0x00, 0xdf, 0x47, 0x00,
    0x00, 0xd3, 0x47, 0x00,
    0x00, 0x9f, 0x67, 0x00,
    0x00, 0x7f, 0x5b, 0x00,
    0x00, 0x63, 0x43, 0x00,
    0x00, 0x47, 0x27, 0x00,
    0x00, 0x2b, 0x1b, 0x00,
    0x23, 0x23, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x8b, 0x37, 0xdb, 0x00,
    0x77, 0x2b, 0xb3, 0x00,
    0xfb, 0xfb, 0xdb, 0x00,
    0xfb, 0xfb, 0xbb, 0x00,
    0xfb, 0xfb, 0x9b, 0x00,
    0xfb, 0xfb, 0x7b, 0x00,
    0xfb, 0xfb, 0x5b, 0x00,
    0xfb, 0xfb, 0x43, 0x00,
    0xfb, 0xfb, 0x23, 0x00,
    0xfb, 0xfb, 0x00, 0x00,
    0xe3, 0xe3, 0x00, 0x00,
    0xcb, 0xcb, 0x00, 0x00,
    0xb3, 0xb3, 0x00, 0x00,
    0x9b, 0x9b, 0x00, 0x00,
    0x83, 0x83, 0x00, 0x00,
    0x73, 0x73, 0x00, 0x00,
    0x5b, 0x5b, 0x00, 0x00,
    0x43, 0x43, 0x00, 0x00,
    0xff, 0xbf, 0x47, 0x00,
    0xf7, 0xaf, 0x33, 0x00,
    0xef, 0xa3, 0x1f, 0x00,
    0xe7, 0x97, 0x0f, 0x00,
    0xe3, 0x8b, 0x00, 0x00,
    0xcb, 0x7b, 0x00, 0x00,
    0xb3, 0x6b, 0x00, 0x00,
    0x9b, 0x5b, 0x00, 0x00,
    0x7b, 0x47, 0x00, 0x00,
    0x5f, 0x37, 0x00, 0x00,
    0x43, 0x27, 0x00, 0x00,
    0x27, 0x17, 0x00, 0x00,
    0xfb, 0x63, 0x5b, 0x00,
    0xfb, 0x43, 0x43, 0x00,
    0xfb, 0x23, 0x23, 0x00,
    0xfb, 0x00, 0x00, 0x00,
    0xfb, 0x00, 0x00, 0x00,
    0xdb, 0x00, 0x00, 0x00,
    0xc3, 0x00, 0x00, 0x00,
    0xab, 0x00, 0x00, 0x00,
    0x8b, 0x00, 0x00, 0x00,
    0x73, 0x00, 0x00, 0x00,
    0x5b, 0x00, 0x00, 0x00,
    0x43, 0x00, 0x00, 0x00,
    0xbf, 0xbb, 0xfb, 0x00,
    0xaf, 0xab, 0xf7, 0x00,
    0xa3, 0x9b, 0xf3, 0x00,
    0x97, 0x8f, 0xef, 0x00,
    0x87, 0x7f, 0xeb, 0x00,
    0x7f, 0x73, 0xe7, 0x00,
    0x6b, 0x5b, 0xdf, 0x00,
    0x47, 0x3b, 0xcb, 0x00,
    0xf7, 0xb3, 0x43, 0x00,
    0xf7, 0xbb, 0x4f, 0x00,
    0xf7, 0xc7, 0x5b, 0x00,
    0xf7, 0xcf, 0x6b, 0x00,
    0xf7, 0xd7, 0x77, 0x00,
    0xf7, 0xdf, 0x83, 0x00,
    0xf7, 0xe7, 0x93, 0x00,
    0xf7, 0xcf, 0x6b, 0x00,
    0x00, 0x43, 0xcb, 0x00,
    0x00, 0x33, 0xbb, 0x00,
    0x00, 0x23, 0xa3, 0x00,
    0x00, 0x1b, 0x93, 0x00,
    0x00, 0x0b, 0x7b, 0x00,
    0x00, 0x00, 0x6b, 0x00,
    0x00, 0x00, 0x53, 0x00,
    0x00, 0x00, 0x43, 0x00,
    0x00, 0xff, 0xff, 0x00,
    0x00, 0xe3, 0xf7, 0x00,
    0x00, 0xcf, 0xf3, 0x00,
    0x00, 0xb7, 0xef, 0x00,
    0x00, 0xa3, 0xeb, 0x00,
    0x00, 0x8b, 0xe7, 0x00,
    0x00, 0x77, 0xdf, 0x00,
    0x00, 0x63, 0xdb, 0x00,
    0x00, 0x4f, 0xd7, 0x00,
    0x00, 0x3f, 0xd3, 0x00,
    0x00, 0x2f, 0xcf, 0x00,
    0x77, 0xc7, 0xe3, 0x00,
    0x6b, 0xb7, 0xdb, 0x00,
    0x63, 0xa7, 0xd3, 0x00,
    0x5b, 0x97, 0xcb, 0x00,
    0x53, 0x8b, 0xc3, 0x00,
    0xdb, 0xeb, 0xfb, 0x00,
    0xd3, 0xe3, 0xfb, 0x00,
    0xc3, 0xdb, 0xfb, 0x00,
    0xbb, 0xd3, 0xfb, 0x00,
    0xb3, 0xcb, 0xfb, 0x00,
    0xa3, 0xc3, 0xfb, 0x00,
    0x9b, 0xbb, 0xfb, 0x00,
    0x8f, 0xb7, 0xfb, 0x00,
    0x83, 0xb3, 0xfb, 0x00,
    0x73, 0xa3, 0xfb, 0x00,
    0x63, 0x9b, 0xfb, 0x00,
    0x5b, 0x93, 0xf3, 0x00,
    0x5b, 0x8b, 0xeb, 0x00,
    0x53, 0x8b, 0xdb, 0x00,
    0x53, 0x83, 0xd3, 0x00,
    0x4b, 0x7b, 0xcb, 0x00,
    0x4b, 0x7b, 0xbb, 0x00,
    0x43, 0x73, 0xb3, 0x00,
    0x43, 0x6b, 0xab, 0x00,
    0x3b, 0x63, 0xa3, 0x00,
    0x3b, 0x63, 0x9b, 0x00,
    0x33, 0x5b, 0x93, 0x00,
    0x33, 0x5b, 0x8b, 0x00,
    0x2b, 0x53, 0x83, 0x00,
    0x2b, 0x4b, 0x73, 0x00,
    0x23, 0x4b, 0x6b, 0x00,
    0x23, 0x43, 0x5b, 0x00,
    0x1b, 0x3b, 0x53, 0x00,
    0x1b, 0x3b, 0x4b, 0x00,
    0x1b, 0x33, 0x43, 0x00,
    0x13, 0x2b, 0x3b, 0x00,
    0x0b, 0x23, 0x2b, 0x00,
    0x00, 0xab, 0x6f, 0x00,
    0x00, 0xa3, 0x6b, 0x00,
    0x00, 0x9f, 0x67, 0x00,
    0x00, 0xa3, 0x6b, 0x00,
    0x00, 0xab, 0x6f, 0x00,
    0xe7, 0x93, 0x07, 0x00,
    0xe7, 0x97, 0x0f, 0x00,
    0xeb, 0x9f, 0x17, 0x00,
    0xef, 0xa3, 0x23, 0x00,
    0xf3, 0xab, 0x2b, 0x00,
    0xf7, 0xb3, 0x37, 0x00,
    0xef, 0xa7, 0x27, 0x00,
    0xeb, 0x9f, 0x1b, 0x00,
    0xe7, 0x97, 0x0f, 0x00,
    0x0b, 0xcb, 0xfb, 0x00,
    0x0b, 0xa3, 0xfb, 0x00,
    0x0b, 0x73, 0xfb, 0x00,
    0x0b, 0x4b, 0xfb, 0x00,
    0x0b, 0x23, 0xfb, 0x00,
    0x0b, 0x73, 0xfb, 0x00,
    0x00, 0x13, 0x93, 0x00,
    0x00, 0x0b, 0xd3, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x83, 0x99, 0xb1, 0x00,
    0x4f, 0x65, 0x7d, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0x00
};

#endif