/* ScummVM - Scumm Interpreter
 * Copyright (C) 2001  Ludvig Strigeus
 * Copyright (C) 2001-2006 The ScummVM project
 * Copyright (C) 2002-2006 Chris Apers - PalmOS Backend
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include <string.h>

#ifdef PALMOS_68K
void *memchr(const void *s, int c, UInt32 n) {
	UInt32 chr;
	for(chr = 0; chr < n;chr++,((UInt8 *)s)++)
		if ( *((UInt8 *)s) == c)
			return (void *)s;

	return NULL;
}

Char *strdup(const Char *s1) {
	Char* buf = (Char *)MemPtrNew(StrLen(s1)+1);

	if(buf)
		StrCopy(buf, s1);

	return buf;
}
#endif
