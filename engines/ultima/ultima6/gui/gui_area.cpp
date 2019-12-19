/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

//#include <cmath>
#include "ultima/ultima6/core/nuvie_defs.h"
#include "ultima/ultima6/gui/gui.h"
#include "ultima/ultima6/gui/gui_area.h"

namespace Ultima {
namespace Ultima6 {

GUI_Area:: GUI_Area(int x, int y, int w, int h, uint8 r, uint8 g, uint8 b, int aShape)
	: GUI_Widget(NULL, x, y, w, h) {
	R = r;
	G = g;
	B = b;
	color = 0;
	useFrame = 0;
	shape = aShape;
	frameThickness = 0;
}

GUI_Area:: GUI_Area(int x, int y, int w, int h, uint8 r, uint8 g, uint8 b,
                    uint8 fr, uint8 fg, uint8 fb, int fthick, int aShape)
	: GUI_Widget(NULL, x, y, w, h) {
	R = r;
	G = g;
	B = b;
	color = 0;
	useFrame = 1;
	fR = fr;
	fG = fg;
	fB = fb;
	frameColor = 0;
	frameThickness = fthick;
	shape = aShape;
}

/* Map the color to the display */
void
GUI_Area:: SetDisplay(Screen *s) {
	GUI_Widget::SetDisplay(s);
	color = SDL_MapRGB(surface->format, R, G, B);
	if (useFrame)
		frameColor = SDL_MapRGB(surface->format, fR, fG, fB);
}

/* Show the widget  */
void GUI_Area::Display(bool full_redraw) {
	Common::Rect framerect;
	int x, dy, r1, r2, x0, y0;

	switch (shape) {
	case AREA_ROUND:

		r1 = area.width() >> 1;
		r2 = area.height() >> 1;
		x0 = area.left + r1;
		y0 = area.top + r2;
		for (x = area.left; x < area.left + area.width(); x++) {
			dy = (int)((double) r2 * sin(acos((double)(x - x0) / (double) r1)));
			framerect.x = x;
			framerect.y = y0 - dy;
			framerect.w = 1;
			framerect.h = dy << 1;
			SDL_FillRect(surface, &framerect, color);
			if (useFrame) {
				if ((x == area.left) || (x == area.left + area.width() - 1)) {
					SDL_FillRect(surface, &framerect, frameColor);
				}
				framerect.h = frameThickness;
				SDL_FillRect(surface, &framerect, frameColor);
				framerect.y = y0 + dy - frameThickness;
				SDL_FillRect(surface, &framerect, frameColor);
			}
		}
		/*
		******** GUI_FillEllipse is not ready yet, GUI_BoundaryFill either *****
		        framerect=area;
		        if (useFrame)
		        {
		          GUI_FillEllipse(screen,&framerect,frameColor);
		          area.left+=frameThickness; area.width()-=frameThickness << 1;
		          area.top+=frameThickness; area.height()-=frameThickness << 1;
		        }
		        GUI_FillEllipse(screen,&framerect,color);
		*/
		break;

	case AREA_ANGULAR:
		framerect = area;
		SDL_FillRect(surface, &framerect, color);

		/* draw frame */
		if (useFrame) {
			framerect = area;
			framerect.h = frameThickness;
			SDL_FillRect(surface, &framerect, frameColor);
			framerect = area;
			framerect.h = frameThickness;
			framerect.y += area.height() - frameThickness;
			SDL_FillRect(surface, &framerect, frameColor);
			framerect = area;
			framerect.w = frameThickness;
			SDL_FillRect(surface, &framerect, frameColor);
			framerect = area;
			framerect.w = frameThickness;
			framerect.x += area.width() - frameThickness;
			SDL_FillRect(surface, &framerect, frameColor);
		}
		break;
	}

	DisplayChildren();

	screen->update(area.left, area.top, area.width(), area.height());

	return;
}

} // End of namespace Ultima6
} // End of namespace Ultima
