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

#ifndef ULTIMA6_GUI_GUI_YES_NO_DIALOG_H
#define ULTIMA6_GUI_GUI_YES_NO_DIALOG_H

#include "ultima/ultima6/gui/gui_Dialog.h"

namespace Ultima {
namespace Ultima6 {

class GUI;
class GUI_CallBack;
class GUI_Button;

// Callback message types

#define YESNODIALOG_CB_YES 0x1
#define YESNODIALOG_CB_NO  0x2

class GUI_YesNoDialog : public GUI_Dialog {
protected:

	sint8 b_index_num;
	GUI_Button *yes_button, *no_button;
	GUI_CallBack *yes_callback_object, *no_callback_object;
	GUI_Button *button_index[2];

public:

	GUI_YesNoDialog(GUI *gui, int x, int y, int w, int h, const char *msg, GUI_CallBack *yesCallback, GUI_CallBack *noCallback);

	~GUI_YesNoDialog();

	GUI_status KeyDown(const Common::KeyState &key);

	GUI_status callback(uint16 msg, GUI_CallBack *caller, void *data);
};

} // End of namespace Ultima6
} // End of namespace Ultima

#endif
