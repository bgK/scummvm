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

#ifndef ULTIMA6_KEYBINDING_UTILS_H
#define ULTIMA6_KEYBINDING_UTILS_H

#include <fstream>
#include "ultima/shared/std/string.h" // exception handling include

namespace Ultima {
namespace Ultima6 {

bool openFile
(
    std::ifstream &in,          // Input stream to open.
    const char *fname           // May be converted to upper-case.
);

bool fileExists(
    const char *fname
);

/*
 *  File errors
 */

class file_exception : public std::exception {
	std::string  what_;
public:
	file_exception(const std::string &what_arg): what_(what_arg) {  }
	const char *what() const throw () {
		return what_.c_str();
	}
	virtual ~file_exception() throw() {}
};

class   file_open_exception : public file_exception {
	static const std::string  prefix_;
public:
	file_open_exception(const std::string &file): file_exception("Error opening file " + file) {  }
};

} // End of namespace Ultima6
} // End of namespace Ultima

#endif
