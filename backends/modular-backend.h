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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef BACKENDS_MODULAR_BACKEND_H
#define BACKENDS_MODULAR_BACKEND_H

#include "common/system.h"
#include "common/timer.h"
#include "common/savefile.h"

class GraphicsManager;
class MutexManager;

/**
 * Base class for modular backends.
 * 
 * It wraps most functions to their manager equivalent, but not
 * all OSystem functions are implemented here.
 * 
 * A backend derivated from this class, will need to implement
 * these functions on its own:
 *   OSystem::pollEvent()
 *   OSystem::createConfigReadStream()
 *   OSystem::createConfigWriteStream()
 *   OSystem::getMillis()
 *   OSystem::delayMillis()
 *   OSystem::getTimeAndDate()
 * 
 * And, it should also initialize all the managers variables
 * declared in this class, or override their related functions.
 */
class ModularBackend : public OSystem {
public:
	ModularBackend();
	virtual ~ModularBackend();

	/** @name Features */
	//@{

	virtual bool hasFeature(Feature f);
	virtual void setFeatureState(Feature f, bool enable);
	virtual bool getFeatureState(Feature f);

	//@}

	/** @name Graphics */
	//@{

	virtual GraphicsManager *getGraphicsManager();
	virtual const GraphicsMode *getSupportedGraphicsModes() const;
	virtual int getDefaultGraphicsMode() const;
	virtual bool setGraphicsMode(int mode);
	virtual int getGraphicsMode() const;
	virtual void resetGraphicsScale();
#ifdef USE_RGB_COLOR
	virtual Graphics::PixelFormat getScreenFormat() const;
	virtual Common::List<Graphics::PixelFormat> getSupportedFormats() const;
#endif
	virtual void initSize(uint width, uint height, const Graphics::PixelFormat *format = NULL);
	virtual int getScreenChangeID() const;

	virtual void beginGFXTransaction();
	virtual OSystem::TransactionError endGFXTransaction();

	virtual int16 getHeight();
	virtual int16 getWidth();
	virtual PaletteManager *getPaletteManager();
	virtual void copyRectToScreen(const byte *buf, int pitch, int x, int y, int w, int h);
	virtual Graphics::Surface *lockScreen();
	virtual void unlockScreen();
	virtual void fillScreen(uint32 col);
	virtual void updateScreen();
	virtual void setShakePos(int shakeOffset);
	virtual void setFocusRectangle(const Common::Rect& rect);
	virtual void clearFocusRectangle();

	virtual void showOverlay();
	virtual void hideOverlay();
	virtual Graphics::PixelFormat getOverlayFormat() const;
	virtual void clearOverlay();
	virtual void grabOverlay(OverlayColor *buf, int pitch);
	virtual void copyRectToOverlay(const OverlayColor *buf, int pitch, int x, int y, int w, int h);
	virtual int16 getOverlayHeight();
	virtual int16 getOverlayWidth();

	virtual bool showMouse(bool visible);
	virtual void warpMouse(int x, int y);
	virtual void setMouseCursor(const byte *buf, uint w, uint h, int hotspotX, int hotspotY, uint32 keycolor, int cursorTargetScale = 1, const Graphics::PixelFormat *format = NULL);
	virtual void setCursorPalette(const byte *colors, uint start, uint num);
	virtual void disableCursorPalette(bool disable);

	//@}

	/** @name Events and Time */
	//@{
	
	virtual Common::TimerManager *getTimerManager();
	virtual Common::EventManager *getEventManager();
	virtual Common::HardwareKeySet *getHardwareKeySet() { return 0; }

	//@}
	
	/** @name Mutex handling */
	//@{

	virtual MutexRef createMutex();
	virtual void lockMutex(MutexRef mutex);
	virtual void unlockMutex(MutexRef mutex);
	virtual void deleteMutex(MutexRef mutex);

	//@}

	/** @name Sound */
	//@{

	virtual Audio::Mixer *getMixer();

	//@}

	/** @name Audio CD */
	//@{

	virtual AudioCDManager *getAudioCDManager();

	//@}

	/** @name Miscellaneous */
	//@{

	virtual Common::SaveFileManager *getSavefileManager();
	virtual FilesystemFactory *getFilesystemFactory();
	virtual void quit();
	virtual void displayMessageOnOSD(const char *msg);

	//@}

protected:
	/** @name Managers variables */
	//@{

	FilesystemFactory *_fsFactory;
	Common::EventManager *_eventManager;
	Common::SaveFileManager *_savefileManager;
	Common::TimerManager *_timerManager;
	MutexManager *_mutexManager;
	GraphicsManager *_graphicsManager;
	Audio::Mixer *_mixer;
	AudioCDManager *_audiocdManager;

	//@}
};

#endif
