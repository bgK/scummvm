/* ScummVM - Scumm Interpreter
 * Copyright (C) 2002 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 */

#include "stdafx.h"
#include "util.h"

//
// 8-bit alpha blending routines
//
static int BlendCache[256][256];

//
// Find the entry in the given palette which matches the color defined by
// the tripel (r,b,g) most closely.
//
int RGBMatch(byte *palette, int r, int g, int b) {
	int i, bestidx = 0, besterr = 0xFFFFFF;
	int error = 0;

	for (i = 0;i < 256;i++) {
		byte *pal = palette + (i * 3);
		int r_diff = r - (int)*pal++; 
		int g_diff = g - (int)*pal++; 
		int b_diff = b - (int)*pal++; 
		r_diff *= r_diff; g_diff *= g_diff; b_diff *= b_diff;

		error = r_diff + g_diff + b_diff;
		if (error < besterr) {
			besterr = error;
			bestidx = i;
		}
	}
	return bestidx;
}

//
// Blend two 8 bit colors into a third, all colors being defined by palette indices.
//
int Blend(int src, int dst, byte *palette) {
	int r, g, b;
	int alpha = 128;	// Level of transparency [0-256]
	byte *srcpal = palette + (dst * 3);
	byte *dstpal = palette + (src * 3);

	if (BlendCache[dst][src] > -1)
		return BlendCache[dst][src];

	r =  (*srcpal++ * alpha);
	r += (*dstpal++ * (256 - alpha));
	r /= 256;

	g =  (*srcpal++ * alpha);
	g += (*dstpal++ * (256 - alpha));
	g /= 256;

	b =  (*srcpal++ * alpha);
	b += (*dstpal++  * (256 - alpha));
	b /= 256;

	return (BlendCache[dst][src] = RGBMatch(palette, r , g , b ));
}

//
// Reset the blending cache
//
void ClearBlendCache(byte *palette, int weight) {
	for (int i = 0; i < 256; i++)
		for (int j = 0 ; j < 256 ; j++)
//			BlendCache[i][j] = i;	// No alphablending
//			BlendCache[i][j] = j;	// 100% translucent
			BlendCache[i][j] = -1;	// Enable alphablending
}

//
// Print hexdump of the data passed in, 8 bytes a row
//
void hexdump(const byte * data, int len) {
	int i;
	byte c;
	while (len >= 8) {
		for (i = 0; i < 8; i++)
			printf("%02x ", data[i]);
		printf(" |");
		for (i = 0; i < 8; i++) {
			c = data[i];
			if (c < 32 || c >= 127)
				c = '.';
			printf("%c", c);
		}
		printf("|\n");
		data += 8;
		len -= 8;
	}

	if (len <= 0) 
		return;

	for (i = 0; i < len; i++)
		printf("%02x ", data[i]);
	for (; i < 8; i++)
		printf("   ");
	printf(" |");
	for (i = 0; i < len; i++) {
		c = data[i];
		if (c < 32 || c >= 127)
			c = '.';
		printf("%c", c);
	}
	for (; i < 8; i++)
		printf(" ");
	printf("|\n");
}

RandomSource::RandomSource(uint32 seed) {
	_randSeed = seed;
}

void RandomSource::setSeed(uint32 seed) {
	_randSeed = seed;
}

uint RandomSource::getRandomNumber(uint max) {
	/* TODO: my own random number generator */
	_randSeed = 0xDEADBF03 * (_randSeed + 1);
	_randSeed = (_randSeed >> 13) | (_randSeed << 19);
	return _randSeed % (max + 1);
}

uint RandomSource::getRandomNumberRng(uint min, uint max) {
	return getRandomNumber(max - min) + min;
}

