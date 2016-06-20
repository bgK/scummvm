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

#ifndef TITANIC_MAIL_MAN_H
#define TITANIC_MAIL_MAN_H

#include "titanic/core/game_object.h"

namespace Titanic {

class CMailMan : public CGameObject {
public:
	int _value;
public:
	CLASSDEF
	CMailMan() : CGameObject(), _value(1) {}

	/**
	 * Save the data for the class to file
	 */
	virtual void save(SimpleFile *file, int indent) const;

	/**
	 * Load the data for the class from file
	 */
	virtual void load(SimpleFile *file);

	/**
	 * Get the first game object stored in the PET
	 */
	CGameObject *getFirstObject() const;

	/**
	 * Get the next game object stored in the PET following
	 * the passed game object
	 */
	CGameObject *getNextObject(CGameObject *prior) const;

	/**
	 * Add an object to the mail list
	 */
	void addMail(CGameObject *obj, int id);

	/**
	 * Sets the mail identifier for an object
	 */
	static void setMailId(CGameObject *obj, int id);

	/**
	 * Scan the mail list for a specified item
	 */
	CGameObject *findMail(int id) const;

	/**
	 * Remove a mail item
	 */
	void removeMail(int id, int v);

	void resetValue() { _value = 0; }
};


} // End of namespace Titanic

#endif /* TITANIC_MAIL_MAN_H */
