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

/*
 * This code is based on original Sfinx source code
 * Copyright (c) 1994-1997 Janus B. Wisniewski and L.K. Avalon
 */

#include "sound.h"
#include "cge2/cge2_main.h"
#include "cge2/cge2.h"
#include "cge2/vga13h.h"
#include "cge2/text.h"
#include "cge2/snail.h"
#include "cge2/hero.h"
#include "cge2/spare.h"
#include "cge2/events.h"

namespace CGE2 {

System::System(CGE2Engine *vm) : Sprite(vm), _vm(vm) {
	warning("STUB: System::System()");
}

void System::touch(uint16 mask, int x, int y, Common::KeyCode keyCode) {
	warning("STUB: System::touch()");
}

void System::tick() {
	warning("STUB: System::tick()");
}

int CGE2Engine::number(char *s) { // TODO: Rework it later to include the preceding token() call!
	int r = atoi(s);
	char *pp = strchr(s, ':');
	if (pp)
		r = (r << 8) + atoi(pp + 1);
	return r;
}

char *CGE2Engine::token(char *s) {
	return strtok(s, " =\t,;/()");
}

char *CGE2Engine::tail(char *s) {
	if (s && (*s == '='))
		s++;
	return s;
}

int CGE2Engine::takeEnum(const char **tab, const char *text) {
	if (text) {
		for (const char **e = tab; *e; e++) {
			if (scumm_stricmp(text, *e) == 0) {
				return e - tab;
			}
		}
	}
	return -1;
}

ID CGE2Engine::ident(const char *s) {
	return ID(takeEnum(EncryptedStream::kIdTab, s));
}

bool CGE2Engine::testBool(char *s) {
	return number(s) != 0;
}

void CGE2Engine::badLab(const char *fn) {
	error("Misplaced label in %s!", fn);
}

void CGE2Engine::loadSprite(const char *fname, int ref, int scene, V3D &pos) {
	int shpcnt = 0;
	int seqcnt = 0;
	int cnt[kActions];
	for (int i = 0; i < kActions; i++)
		cnt[i] = 0;
	ID section = kIdPhase;
	bool frnt = true;
	bool east = false;
	bool port = false;
	bool tran = false;
	Hero *h;
	ID id;

	char tmpStr[kLineMax + 1];
	mergeExt(tmpStr, fname, kSprExt);

	if (_resman->exist(tmpStr)) { // sprite description file exist
		EncryptedStream sprf(this, tmpStr);
		if (sprf.err())
			error("Bad SPR [%s]", tmpStr);

		int label = kNoByte;
		Common::String line;

		for (line = sprf.readLine(); !sprf.eos(); line = sprf.readLine()){
			if (line.size() == 0)
				continue;
			Common::strlcpy(tmpStr, line.c_str(), sizeof(tmpStr));
				
			char *p;
			p = token(tmpStr);
			if (*p == '@') {
				if (label != kNoByte)
					badLab(fname);
				label = atoi(p + 1);
				continue;
			}

			id = ident(p);
			switch (id) {
			case kIdName: // will be taken in Expand routine
				if (label != kNoByte)
					badLab(fname);
				break;
			case kIdType:
				if (label != kNoByte)
					badLab(fname);
				break;
			case kIdNear:
			case kIdMTake:
			case kIdFTake:
			case kIdPhase:
			case kIdSeq:
				if (label != kNoByte)
					badLab(fname);
				section = id;
				break;
			case kIdFront:
				if (label != kNoByte)
					badLab(fname);
				p = token(nullptr);
				frnt = testBool(p);
				break;
			case kIdEast:
				if (label != kNoByte)
					badLab(fname);
				p = token(nullptr);
				east = testBool(p);
				break;
			case kIdPortable:
				if (label != kNoByte)
					badLab(fname);
				p = token(nullptr);
				port = testBool(p);
				break;
			case kIdTransparent:
				if (label != kNoByte)
					badLab(fname);
				p = token(nullptr);
				tran = testBool(p);
				break;
			default:
				if (id >= kIdNear)
					break;
				switch (section) {
				case kIdNear:
				case kIdMTake:
				case kIdFTake:
					if (_commandHandler->getComId(p) >= 0)
						++cnt[section];
					else
						error("Bad line %d [%s]", sprf.getLineCount(), tmpStr);
					break;
				case kIdPhase:
					if (label != kNoByte)
						badLab(fname);
					++shpcnt;
					break;
				case kIdSeq:
					if (label != kNoByte)
						badLab(fname);
					++seqcnt;
					break;
				default:
					break;
				}
				break;
			}
			label = kNoByte;
		}

		if (!shpcnt) {
			error("No shapes - %s", fname);
		}
	} else // No sprite description: mono-shaped sprite with only .BMP file.
		++shpcnt;

	// Make sprite of choosen type:
	char c = *fname | 0x20;
	if (c >= 'a' && c <= 'z' && fname[1] == '0' && fname[2] == '\0') {
		h = new Hero(this);
		if (h) {
			h->gotoxyz(pos);
			_sprite = h;
		}
	} else {
		if (_sprite)
			delete _sprite;
		_sprite = new Sprite(this);
		if (_sprite)
			_sprite->gotoxyz(pos);
	}

	if (_sprite) {
		_sprite->_ref = ref;
		_sprite->_scene = scene;

		_sprite->_flags._frnt = frnt;
		_sprite->_flags._east = east;
		_sprite->_flags._port = port;
		_sprite->_flags._tran = tran;
		_sprite->_flags._kill = true;

		// Extract the filename, without the extension
		Common::strlcpy(_sprite->_file, fname, sizeof(_sprite->_file));
		char *p = strchr(_sprite->_file, '.');
		if (p)
			*p = '\0';

		_sprite->_shpCnt = shpcnt;
		_sprite->_seqCnt = seqcnt;

		for (int i = 0; i < kActions; i++)
			_sprite->_actionCtrl[i]._cnt = cnt[i];
	}
}

void CGE2Engine::loadScript(const char *fname) {
	EncryptedStream scrf(this, fname);

	if (scrf.err())
		return;

	bool ok = true;
	int lcnt = 0;

	char tmpStr[kLineMax + 1];
	Common::String line;

	for (line = scrf.readLine(); !scrf.eos(); line = scrf.readLine()) {
		if (line.size() == 0)
			continue;

		char *p;

		lcnt++;
		Common::strlcpy(tmpStr, line.c_str(), sizeof(tmpStr));
		
		ok = false; // not OK if break

		V3D P;

		// sprite ident number
		if ((p = token(tmpStr)) == NULL)
			break;
		int SpI = number(p);

		// sprite file name
		char *SpN;
		if ((SpN = token(nullptr)) == NULL)
			break;

		// sprite scene
		if ((p = token(nullptr)) == NULL)
			break;
		int SpA = number(p);

		// sprite column
		if ((p = token(nullptr)) == NULL)
			break;
		P._x = number(p);

		// sprite row
		if ((p = token(nullptr)) == NULL)
			break;
		P._y = number(p);

		// sprite Z pos
		if ((p = token(nullptr)) == NULL)
			break;
		P._z = number(p);

		// sprite life
		if ((p = token(nullptr)) == NULL)
			break;
		bool BkG = number(p) == 0;

		ok = true; // no break: OK

		_sprite = NULL;
		loadSprite(SpN, SpI, SpA, P);
		if (_sprite) {
			if (BkG)
				_sprite->_flags._back = true;

			int n = _spare->count();
			if (_spare->locate(_sprite->_ref) == nullptr)
				_spare->store(_sprite);
			_sprite = nullptr;
			if (_spare->count() == n)
				error("Durplicated reference! %s", SpN);
		}
	}

	if (!ok)
		error("Bad INI line %d [%s]", scrf.getLineCount(), fname);
}

void CGE2Engine::movie(const char *ext) {
	assert(ext);

	if (_quitFlag)
		return;

	char fn[12];
	sprintf(fn, "CGE.%s", (*ext == '.') ? ext + 1 : ext);

	if (_resman->exist(fn)) {
		int now = _now;
		_now = atoi(ext + 2);
		loadScript(fn);
		caveUp(_now);

		while (!_commandHandler->idle() && !_quitFlag)
			mainLoop();

		warning("STUB: CGE2Engine::movie()");

		_commandHandler->addCommand(kCmdClear, -1, 0, nullptr);
		_commandHandlerTurbo->addCommand(kCmdClear, -1, 0, nullptr);
		_vga->_showQ->clear();
		_spare->clear();
		_now = now;
	}
}

void CGE2Engine::caveUp(int cav) {
	_now = cav;
	int bakRef = _now << 8;
	if (_music)
		_midiPlayer->loadMidi(bakRef);
	showBak(bakRef);
	*_eye = *(_eyeTab[_now]);
	_mouseTop = V2D(this, V3D(0, 1, kScrDepth)).y;
	_spare->takeCave(_now);
	openPocket();
	
	warning("STUB: CGE2Engine::caveUp()");
	// TODO: Implement "Hero" things here!

	_sound->stop();
	_fx->clear();

	selectPocket(-1);
	_infoLine->setText(nullptr);
	busy(false);

	if (!_dark)
		_vga->sunset();
	_vga->show();
	_vga->copyPage(1, 0);
	_vga->show();

	_sprite = _vga->_showQ->first();
	_vga->sunrise(_vga->_sysPal);

	_dark = false;

	if (!_startupMode)
		_mouse->on();

	feedSnail(_vga->_showQ->locate(bakRef + 255), kNear, _heroTab[_sex]->_ptr);
	//setDrawColors(); - It's only for debugging purposes. Can be left out for now.
}

void CGE2Engine::switchCave(int cav) {
	warning("STUB: CGE2Engine::switchCave()");
}

void CGE2Engine::showBak(int ref) {
	Sprite *spr = _spare->take(ref);
	if (spr != nullptr) {
		_bitmapPalette = _vga->_sysPal;
		spr->expand();
		_bitmapPalette = NULL;
		spr->show(2);
		_vga->copyPage(1, 2);
		_spare->dispose(spr);
	}
}

void CGE2Engine::mainLoop() {
	_vga->show();
	_commandHandlerTurbo->runCommand();
	_commandHandler->runCommand();

	// Handle a delay between game frames
	handleFrame();

	// Handle any pending events
	_eventManager->poll();

	// Check shouldQuit()
	_quitFlag = shouldQuit();
}

void CGE2Engine::handleFrame() {
	// Game frame delay
	uint32 millis = g_system->getMillis();
	while (!_quitFlag && (millis < (_lastFrame + kGameFrameDelay))) {
		// Handle any pending events
		_eventManager->poll();

		if (millis >= (_lastTick + kGameTickDelay)) {
			// Dispatch the tick to any active objects
			tick();
			_lastTick = millis;
		}

		// Slight delay
		g_system->delayMillis(5);
		millis = g_system->getMillis();
	}
	_lastFrame = millis;

	if (millis >= (_lastTick + kGameTickDelay)) {
		// Dispatch the tick to any active objects
		tick();
		_lastTick = millis;
	}
}

Sprite *CGE2Engine::locate(int ref) {
	_taken = false;
	Sprite *spr = _vga->_showQ->locate(ref);
	if (!spr) {
		spr = _spare->locate(ref);
		if (spr)
			_taken = true;
	}
	return spr;
}

bool CGE2Engine::isHero(Sprite *spr) {
	return spr && spr->_ref / 10 == 14;
}

void CGE2Engine::tick() {
	for (Sprite *spr = _vga->_showQ->first(); spr; spr = spr->_next) {
		if (spr->_time) {
			if (--spr->_time == 0)
				spr->tick();
		}
		if (_waitRef) {
			if (_waitRef == _sprite->_ref)
				if (spr->seqTest(_waitSeq))
					_waitRef = 0;
		}
	}

	_mouse->tick();
}

void CGE2Engine::loadMap(int cav) {
	warning("STUB: CGE2Engine::loadMap()");
}

void CGE2Engine::openPocket() {
	warning("STUB: CGE2Engine::openPocket()");
}

void CGE2Engine::selectPocket(int n) {
	warning("STUB: CGE2Engine::selectPocket()");
}

void CGE2Engine::busy(bool on) {
	warning("STUB: CGE2Engine::selectPocket()");
}

void CGE2Engine::runGame() {
	if (_quitFlag)
		return;

	selectPocket(-1);

	loadUser();

	_commandHandlerTurbo->addCommand(kCmdSeq, kMusicRef, _music, nullptr);
	if (!_music)
		_midiPlayer->killMidi();

	checkSaySwitch();
		
	_infoLine->gotoxyz(V3D(kInfoX, kInfoY, 0));
	_infoLine->setText(nullptr);
	//_vga->_showQ->insert(_infoLine);
	warning("STUB: CGE2Engine::runGame() - Info Line is missing!");

	caveUp(_now);
	_startupMode = 0;
	_mouse->center();
	_mouse->off();
	_mouse->on();

	_keyboard->setClient(_sys);
	_commandHandler->addCommand(kCmdSeq, kPowerRef, 1, nullptr);

	_busyPtr = _vga->_showQ->locate(kBusyRef);

	_vol[0] = _vga->_showQ->locate(kDvolRef);
	_vol[1] = _vga->_showQ->locate(kMvolRef);

	// these sprites are loaded with SeqPtr==0 (why?!)
	if (_vol[0])
		_vol[0]->step((/*(int)SNDDrvInfo.VOL4.DL * */ _vol[0]->_seqCnt + _vol[0]->_seqCnt / 2) >> 4);
	if (_vol[1])
		_vol[1]->step((/*(int)SNDDrvInfo.VOL4.ML * */ _vol[1]->_seqCnt + _vol[1]->_seqCnt / 2) >> 4);
	// TODO: Recheck these! ^

	// main loop
	while (!_endGame && !_quitFlag) {
		if (_flag[3]) // Flag FINIS
			_commandHandler->addCallback(kCmdExec, -1, 0, kQGame);
		mainLoop();
	}

	// If finishing game due to closing ScummVM window, explicitly save the game
	if (!_endGame && canSaveGameStateCurrently())
		qGame();

	_keyboard->setClient(nullptr);
	_commandHandler->addCommand(kCmdClear, -1, 0, nullptr);
	_commandHandlerTurbo->addCommand(kCmdClear, -1, 0, nullptr);
	_mouse->off();
	_vga->_showQ->clear();
}

void CGE2Engine::loadUser() {
	warning("STUB: CGE2Engine::loadUser()");
	// Missing loading from file. TODO: Implement it with the saving/loading!
	loadScript("CGE.INI");
	loadGame();
	loadPos();
}

void CGE2Engine::loadGame() {
	warning("STUB: CGE2Engine::loadGame()");

	// load sprites & pocket
	
	Sprite *s;
	Hero *h = nullptr;
	
	// initialize Andzia/Anna
	s = _spare->take(142);
	if (s) {
		h = new Hero(this);
		*(Sprite*)h = *s;
		delete s;
		s = nullptr;
		h->expand();
		_spare->update(h);
	}
	_heroTab[0]->_ptr = h;
	s = _spare->take(152);
	_vga->_showQ->insert(s);
	_heroTab[0]->_face = s;

	// initialize Wacek/Vincent
	s = _spare->take(141);
	if (s) {
		h = new Hero(this);
		*(Sprite*)h = *s;
		delete s;
		s = nullptr;
		h->expand();
		_spare->update(h);
	}
	_heroTab[1]->_ptr = h;
	s = _spare->take(151);
	_vga->_showQ->insert(s);
	_heroTab[1]->_face = s;

	//--- start!
	switchHero(_sex);
}

void CGE2Engine::loadPos() {
	if (_resman->exist("CGE.HXY")) {
		for (int cav = 0; cav < kCaveMax; cav++)
			_heroTab[1]->_posTab[cav] = new V2D(this, 180, 10);
		
		EncryptedStream file(this, "CGE.HXY");

		for (int cav = 0; cav < kCaveMax; cav++) {
			_heroTab[0]->_posTab[cav]->x = file.readSint16LE();
			_heroTab[0]->_posTab[cav]->y = file.readSint16LE();
		}

		for (int cav = 0; cav < 41; cav++) { // (564 - 400) / 4 = 41
			_heroTab[1]->_posTab[cav]->x = file.readSint16LE();
			_heroTab[1]->_posTab[cav]->y = file.readSint16LE();
		}
	} else
		error("Missing file: CGE.HXY");
}

void CGE2Engine::releasePocket(Sprite *spr) {
	warning("STUB: CGE2Engine::releasePocket()");
}

void CGE2Engine::checkSaySwitch() {
	warning("STUB: CGE2Engine::checkSaySwitch()");
}

void CGE2Engine::qGame() {
	warning("STUB: CGE2Engine::qGame()");
	_endGame = true;
}

void CGE2Engine::loadTab() {
	setEye(_text->getText(240));
	for (int i = 0; i < kCaveMax; i++)
		*(_eyeTab[i]) = *_eye;

	/*
	if (_resman->exist(kTabName)) {
		EncryptedStream f(this, kTabName);
		for (int i = 0; i < kCaveMax; i++) {
			for (int j = 0; j < 3; j++) {
				signed b = f.readSint16BE();
				unsigned a = f.readUint16BE();
				uint16 round = uint16((long(a) << 16) / 100);
				
				if (round > 0x7FFF)
					b++;
			
				switch (j) {
				case 0:
					_eyeTab[i]->_x = b;
					break;
				case 1:
					_eyeTab[i]->_y = b;
					break;
				case 2:
					_eyeTab[i]->_z = b;
					break;
				}
				
			}
		}
	}
	*/
	warning("STUB: CGE2Engine::loadTab()");
}

void CGE2Engine::cge2_main() {
	warning("STUB: CGE2Engine::cge2_main()");

	loadTab();

	_mode++;

	if (showTitle("WELCOME")) {
#if 0
		if (_mode == 1)
			movie(kIntroExt);
#endif
		if (_text->getText(255) != NULL) {
			runGame();
			_startupMode = 2;
		} else
			_vga->sunset();
	} else
		_vga->sunset();
}

char *CGE2Engine::mergeExt(char *buf, const char *name, const char *ext) {
	strcpy(buf, name);
	char *dot = strrchr(buf, '.');
	if (!dot)
		strcat(buf, ext);

	return buf;
}

void CGE2Engine::setEye(const V3D &e) { 
	*_eye = e;
}

void CGE2Engine::setEye(const V2D& e2, int z) {
	_eye->_x = e2.x;
	_eye->_y = e2.y;
	_eye->_z = z;
}

void CGE2Engine::setEye(const char *s) {
	char tempStr[kLineMax];
	strcpy(tempStr, s);
	_eye->_x = atoi(token(tempStr));
	_eye->_y = atoi(token(NULL));
	_eye->_z = atoi(token(NULL));
}

int CGE2Engine::newRandom(int range) {
	if (!range)
		return 0;

	return _randomSource.getRandomNumber(range - 1);
}

bool CGE2Engine::showTitle(const char *name) {
	if (_quitFlag)
		return false;

	_bitmapPalette = _vga->_sysPal;
	BitmapPtr *LB = new BitmapPtr[2];
	LB[0] = new Bitmap(this, name);
	LB[1] = NULL;
	_bitmapPalette = NULL;

	Sprite D(this, LB, 1);
	D._flags._kill = true;
	warning("STUB: Sprite::showTitle() - Flags changed compared to CGE1's Sprite type.");
	D.gotoxyz(kScrWidth >> 1, -(kPanHeight >> 1));
	_vga->sunset();

	D.show(2);

	_vga->copyPage(1, 2);
	_vga->copyPage(0, 1);

	_vga->sunrise(_vga->_sysPal);

	_vga->update();

	warning("STUB: CGE2Engine::showTitle()");

	return true;
}

int CGE2Engine::freePockets(int sx) {
	int n = 0;
	for (int i = 0; i < kPocketMax; i++){
		if (_heroTab[sx]->_pocket[i] == nullptr)
			++n;
	}
	return n;
}

int CGE2Engine::findActivePocket(int ref) {
	for (int i = 0; i < kPocketMax; i++) {
		Sprite *spr = _heroTab[_sex]->_pocket[i];
		if (ref >= 0) {
			if (spr && spr->_ref == ref)
				return i;
		} else if (!spr)
			return i;
	}
	return -1;
}

void CGE2Engine::pocFul() {
	Hero *h = _heroTab[_sex]->_ptr;
	h->park();
	_commandHandler->addCommand(kCmdWait, -1, -1, h);
	_commandHandler->addCommand(kCmdSound, -1, 2, h);
	_commandHandler->addCommand(kCmdSay, -1, kPocketFull + _sex, h);
}

void CGE2Engine::killText() {
	if (!_talk)
		return;

	_commandHandlerTurbo->addCommand(kCmdKill, -1, 0, _talk);
	_talk = NULL;
}

void CGE2Engine::switchHero(int sex) {
	if (sex != _sex) {
		int scene = _heroTab[sex]->_ptr->_scene;
		if (_blinkSprite) {
			_blinkSprite->_flags._hide = false;
			_blinkSprite = nullptr;
		}
		if (scene >= 0) {
			_commandHandler->addCommand(kCmdSeq, -1, 2, _heroTab[_sex]->_face);
			_sex ^= 1;
			switchCave(scene);
		}
	}
	Sprite *face = _heroTab[_sex]->_face;
	if (face->_seqPtr == 0)
		_commandHandler->addCommand(kCmdSeq, -1, 1, face);
}

Sprite *CGE2Engine::spriteAt(int x, int y) {
	Sprite *spr = NULL, *queueTail = _vga->_showQ->last();
	if (queueTail) {
		for (spr = queueTail->_prev; spr; spr = spr->_prev) {
			if (!spr->_flags._hide && !spr->_flags._tran && spr->getShp()->solidAt(x - spr->_pos2D.x, y - spr->_pos2D.y))
				break;
		}
	}
	return spr;
}

#pragma argsused
void Sprite::touch(uint16 mask, int x, int y, Common::KeyCode keyCode) {
	if ((mask & kEventAttn) != 0)
		return;

	if (!_vm->_startupMode)
		_vm->_infoLine->setText(name());

	if (_ref < 0)
		return; // cannot access system sprites

	if (_ref / 10 == 12) {
		_vm->optionTouch(_ref % 10, mask);
		return;
	}

	if (_vm->isHero(this) && !_vm->_blinkSprite) {
		_vm->switchHero((this == _vm->_heroTab[1]->_ptr) ? 1 : 0);
	} else if (_flags._kept) { // sprite in pocket
		for (int sex = 0; sex < 2; ++sex) {
			for (int p = 0; p < kPocketMax; ++p) {
				if (_vm->_heroTab[sex]->_pocket[p] == this) {
					_vm->switchHero(sex);
					if (_vm->_sex == sex) {
						if (_vm->_blinkSprite)
							_vm->_blinkSprite->_flags._hide = false;
						if (_vm->_blinkSprite == this)
							_vm->_blinkSprite = nullptr;
						else
							_vm->_blinkSprite = this;
					}
				}
			}
		}
	} else { // sprite NOT in pocket
		Hero *h = _vm->_heroTab[_vm->_sex]->_ptr;
		if (!_vm->_talk) {
			if ((_ref & 0xFF) < 200 && h->distance(this) > (h->_maxDist << 1))
				h->walkTo(this);
			else if (_vm->_blinkSprite) {
				if (works(_vm->_blinkSprite)) {
					_vm->feedSnail(_vm->_blinkSprite, (_vm->_sex) ? kMTake : kFTake, _vm->_heroTab[_vm->_sex]->_ptr);
					_vm->_blinkSprite->_flags._hide = false;
					_vm->_blinkSprite = nullptr;
				} else
					_vm->offUse();

				_vm->selectPocket(-1);
			// else, no pocket sprite selected
			} else if (_flags._port) { // portable
				if (_vm->findActivePocket(-1) < 0)
					_vm->pocFul();
				else {
					_vm->_commandHandler->addCommand(kCmdReach, -2, _ref, nullptr);
					_vm->_commandHandler->addCommand(kCmdKeep, -1, -1, this);
					_flags._port = false;
				}
			} else { // non-portable
				Action a = h->action();
				if (_actionCtrl[a]._cnt) {
					CommandHandler::Command *cmdList = snList(a);
					if (cmdList[_actionCtrl[a]._ptr]._commandType == kCmdNext)
						_vm->offUse();
					else
						_vm->feedSnail(this, a, h);
				} else
					_vm->offUse();
			}
		}
	}
}

void CGE2Engine::optionTouch(int opt, uint16 mask) {
	warning("STUB: CGE2Engine::optionTouch()");
}

void CGE2Engine::offUse() {
	warning("STUB: CGE2Engine::offUse()");
}


} // End of namespace CGE2
