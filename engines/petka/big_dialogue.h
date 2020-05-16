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

#ifndef PETKA_BIG_DIALOGUE_H
#define PETKA_BIG_DIALOGUE_H

#include "common/array.h"
#include "common/ustr.h"

namespace Petka {

enum {
	kOpcodePlay = 1,
	kOpcodeMenu,
	kOpcodeEnd,
	kOpcode4
};

enum {
	kOperationBreak = 1,
	kOperationMenu,
	kOperationGoTo,
	kOperationMenuRet,
	kOperation5,
	kOperationReturn,
	kOperationPlay,
	kOperationCircle,
	kOperation9
};

struct Operation {
	union {
		struct {
			byte bits;
			uint16 bitField;
		} menu;
		struct {
			uint16 opIndex;
		} goTo;
		struct {
			uint16 opIndex;
			byte bit;
		} menuRet;
		struct {
			uint16 opIndex;
			byte bit;
		} op5;
		struct {
			uint16 messageIndex;
		} play;
		struct {
			uint16 count;
			byte curr;
		} circle;
		struct {
			uint16 arg;
		} op9;
	};
	byte type;
};

struct Dialog {
	uint32 startOpIndex;
	// uint32 opsCount;
	// Operation *ops;
};

struct DialogHandler {
	uint16 opcode;
	uint16 objId;
	uint32 startDialogIndex;
	Common::Array<Dialog> dialogs;
};

struct DialogGroup {
	uint32 objId;
	Common::Array<DialogHandler> handlers;
};

struct SpeechInfo {
	uint32 speakerId;
	char soundName[16];
	Common::U32String text;
};

class BigDialogue {
public:
	BigDialogue();

	uint opcode();

	uint choicesCount();

	void next(int choice = -1);

	const DialogHandler *findHandler(uint objId, uint opcode, bool *res) const;
	void setHandler(uint objId, uint opcode, int index);

	const Common::U32String *getSpeechInfo(int *talkerId, const char **soundName, int unk);

	void load(Common::ReadStream *s);
	void save(Common::WriteStream *s);

private:
	void loadSpeechesInfo();
	bool checkMenu(uint opIndex);
	bool findOperation(uint startOpIndex, uint opType, uint *resIndex);

private:
	Operation *_currOp;
	Common::Array<Operation> _ops;
	uint _startOpIndex;

	Common::Array<SpeechInfo> _speeches;
	Common::Array<DialogGroup> _objDialogs;
};

} // End of namespace Petka

#endif