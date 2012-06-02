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

/*
 * This file is based on WME Lite.
 * http://dead-code.org/redir.php?target=wmelite
 * Copyright (c) 2011 Jan Nedoma
 */

#include "engines/wintermute/dcgf.h"
#include "engines/wintermute/Base/BSoundMgr.h"
#include "engines/wintermute/Base/BRegistry.h"
#include "engines/wintermute/utils/PathUtil.h"
#include "engines/wintermute/utils/StringUtil.h"
#include "engines/wintermute/Base/BGame.h"
#include "engines/wintermute/Base/BFileManager.h"

namespace WinterMute {

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//IMPLEMENT_PERSISTENT(CBSoundMgr, true);

//////////////////////////////////////////////////////////////////////////
CBSoundMgr::CBSoundMgr(CBGame *inGame): CBBase(inGame) {
	_soundAvailable = false;

	_volumeSFX = _volumeSpeech = _volumeMusic = _volumeMaster = 100;
}


//////////////////////////////////////////////////////////////////////////
CBSoundMgr::~CBSoundMgr() {
	saveSettings();
	cleanup();
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundMgr::cleanup() {
	for (int i = 0; i < _sounds.GetSize(); i++) delete _sounds[i];
	_sounds.RemoveAll();
#if 0
	BASS_Free();
#endif
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
void CBSoundMgr::saveSettings() {
	if (_soundAvailable) {
		Game->_registry->WriteInt("Audio", "MasterVolume", _volumeMaster);

		Game->_registry->WriteInt("Audio", "SFXVolume",    _volumeSFX);
		Game->_registry->WriteInt("Audio", "SpeechVolume", _volumeSpeech);
		Game->_registry->WriteInt("Audio", "MusicVolume",  _volumeMusic);
	}
}

//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundMgr::initialize() {
	_soundAvailable = false;
#if 0

#ifdef __IPHONEOS__
#define BASS_CONFIG_IOS_MIXAUDIO 34
	BASS_SetConfig(BASS_CONFIG_IOS_MIXAUDIO, 0);
#endif


	if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
		Game->LOG(0, "An incorrect version of BASS was loaded");
		return E_FAIL;
	}

	if (!BASS_Init(-1, 44100, 0, 0, NULL)) {
		Game->LOG(0, "Can't initialize sound device");
		return E_FAIL;
	}
#endif

	_volumeMaster = Game->_registry->ReadInt("Audio", "MasterVolume", 100);

	_volumeSFX    = Game->_registry->ReadInt("Audio", "SFXVolume",    100);
	_volumeSpeech = Game->_registry->ReadInt("Audio", "SpeechVolume", 100);
	_volumeMusic  = Game->_registry->ReadInt("Audio", "MusicVolume",  100);

	_soundAvailable = true;
	setMasterVolumePercent(_volumeMaster);

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundMgr::initLoop() {
	if (!_soundAvailable) return S_OK;
#if 0

	BASS_Update(500);
#endif
	return S_OK;
}


//////////////////////////////////////////////////////////////////////////
CBSoundBuffer *CBSoundMgr::addSound(const char *Filename, TSoundType Type, bool Streamed) {
	if (!_soundAvailable) return NULL;

	CBSoundBuffer *sound;

	// try to switch WAV to OGG file (if available)
	AnsiString ext = PathUtil::GetExtension(Filename);
	if (StringUtil::CompareNoCase(ext, "wav")) {
		AnsiString path = PathUtil::GetDirectoryName(Filename);
		AnsiString name = PathUtil::GetFileNameWithoutExtension(Filename);

		AnsiString newFile = PathUtil::Combine(path, name + "ogg");
		CBFile *file = Game->_fileManager->OpenFile(newFile.c_str());
		if (file) {
			Filename = newFile.c_str();
			Game->_fileManager->CloseFile(file);
		}
	}

	sound = new CBSoundBuffer(Game);
	if (!sound) return NULL;

	sound->SetStreaming(Streamed);
	sound->SetType(Type);


	HRESULT res = sound->LoadFromFile(Filename);
	if (FAILED(res)) {
		Game->LOG(res, "Error loading sound '%s'", Filename);
		delete sound;
		return NULL;
	}

	// set volume appropriately
	switch (Type) {
	case SOUND_SFX:
		sound->SetVolume(_volumeSFX);
		break;
	case SOUND_SPEECH:
		sound->SetVolume(_volumeSpeech);
		break;
	case SOUND_MUSIC:
		sound->SetVolume(_volumeMusic);
		break;
	}

	// register sound
	_sounds.Add(sound);

	return sound;

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundMgr::addSound(CBSoundBuffer *Sound, TSoundType Type) {
	if (!Sound) return E_FAIL;

	// set volume appropriately
	switch (Type) {
	case SOUND_SFX:
		Sound->SetVolume(_volumeSFX);
		break;
	case SOUND_SPEECH:
		Sound->SetVolume(_volumeSpeech);
		break;
	case SOUND_MUSIC:
		Sound->SetVolume(_volumeMusic);
		break;
	}

	// register sound
	_sounds.Add(Sound);

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundMgr::removeSound(CBSoundBuffer *Sound) {

	for (int i = 0; i < _sounds.GetSize(); i++) {
		if (_sounds[i] == Sound) {
			delete _sounds[i];
			_sounds.RemoveAt(i);
			return S_OK;
		}
	}

	return E_FAIL;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundMgr::setVolume(TSoundType Type, int Volume) {
	if (!_soundAvailable) return S_OK;

	switch (Type) {
	case SOUND_SFX:
		_volumeSFX = Volume;
		break;
	case SOUND_SPEECH:
		_volumeSpeech = Volume;
		break;
	case SOUND_MUSIC:
		_volumeMusic  = Volume;
		break;
	}

	for (int i = 0; i < _sounds.GetSize(); i++) {
		if (_sounds[i]->_type == Type) _sounds[i]->SetVolume(Volume);
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundMgr::setVolumePercent(TSoundType Type, byte Percent) {
	return setVolume(Type, Percent);
}


//////////////////////////////////////////////////////////////////////////
byte CBSoundMgr::getVolumePercent(TSoundType Type) {
	int Volume;
	switch (Type) {
	case SOUND_SFX:
		Volume = _volumeSFX;
		break;
	case SOUND_SPEECH:
		Volume = _volumeSpeech;
		break;
	case SOUND_MUSIC:
		Volume = _volumeMusic;
		break;
	}

	return (byte)Volume;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundMgr::setMasterVolumePercent(byte  Percent) {
	_volumeMaster = Percent;
#if 0
	BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, (uint32)(10000.0f / 100.0f * (float)Percent));
#endif
	return S_OK;
}


//////////////////////////////////////////////////////////////////////////
byte CBSoundMgr::getMasterVolumePercent() {
#if 0
	uint32 val = BASS_GetConfig(BASS_CONFIG_GVOL_STREAM);
	return (float)val / 10000.0f * 100.0f;
#endif
	return 0;
}



//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundMgr::pauseAll(bool IncludingMusic) {

	for (int i = 0; i < _sounds.GetSize(); i++) {
		if (_sounds[i]->IsPlaying() && (_sounds[i]->_type != SOUND_MUSIC || IncludingMusic)) {
			_sounds[i]->Pause();
			_sounds[i]->_freezePaused = true;
		}
	}

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////
HRESULT CBSoundMgr::resumeAll() {

	for (int i = 0; i < _sounds.GetSize(); i++) {
		if (_sounds[i]->_freezePaused) {
			_sounds[i]->Resume();
			_sounds[i]->_freezePaused = false;
		}
	}

	return S_OK;
}


//////////////////////////////////////////////////////////////////////////
float CBSoundMgr::posToPan(int X, int Y) {
	float relPos = (float)X / ((float)Game->_renderer->_width);

	float minPan = -0.7f;
	float maxPan = 0.7f;

	return minPan + relPos * (maxPan - minPan);
}

} // end of namespace WinterMute
