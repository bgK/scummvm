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

#ifndef HUGO_H
#define HUGO_H

#include "engines/engine.h"
#include "common/file.h"
#include "hugo/console.h"
#include "hugo/dialogs.h"

// This include is here temporarily while the engine is being refactored.
#include "hugo/game.h"
#include "hugo/file.h"

#define HUGO_DAT_VER_MAJ 0                          // 1 byte
#define HUGO_DAT_VER_MIN 42                         // 1 byte
#define DATAALIGNMENT    4

namespace Common {
class RandomSource;
}

/**
 * This is the namespace of the Hugo engine.
 *
 * Status of this engine: ???
 *
 * Games using this engine:
 * - Hugo's House of Horror
 * - Whodunit?
 * - Jungle of Doom
 * - Hugo's Horrific Adventure
 * - Hugo's Mystery Adventure
 * - Hugo's Amazon Adventure
 */
namespace Hugo {

static const int kSavegameVersion = 6;
static const int kInvDx = 32;                       // Width of an inventory icon
static const int kInvDy = 32;                       // Height of inventory icon
static const int kMaxTunes = 16;                    // Max number of tunes
static const int kStepDx = 5;                       // Num pixels moved in x by HERO per step
static const int kStepDy = 4;                       // Num pixels moved in y by HERO per step
static const int kXPix = 320;                       // Width of pcx background file
static const int kYPix = 200;                       // Height of pcx background file
static const int kViewSizeX = kXPix;                // Width of window view
static const int kViewSizeY = 192;                  // Height of window view. In original game: 184
static const int kDibOffY = 0;                      // Offset into dib SrcY (old status line area). In original game: 8
static const int kCompLineSize = 40;                // number of bytes in a compressed line
static const int kMaxLineSize = kCompLineSize - 2;  // Max length of user input line
static const int kMaxTextRows = 25;                 // Number of text lines in display
static const int kMaxBoxChar = kMaxLineSize * kMaxTextRows; // Max chars on screen
static const int kOvlSize = kCompLineSize * kYPix;  // Size of an overlay file
static const int kStateDontCare = 0xFF;             // Any state allowed in command verb
static const int kHeroIndex = 0;                    // In all enums, HERO is the first element
static const int kArrowNumb = 2;                    // Number of arrows (left/right)
static const int kLeftArrow = -2;                   // Cursor over Left arrow in inventory icon bar
static const int kRightArrow = -3;                  // Cursor over Right arrow in inventory icon bar
static const int kMaxPath = 256;                    // Max length of a full path name
static const int kHeroMaxWidth = 24;                // Maximum width of hero
static const int kHeroMinWidth = 16;                // Minimum width of hero

typedef char command_t[kMaxLineSize + 8];           // Command line (+spare for prompt,cursor)

struct config_t {                                   // User's config (saved)
	bool musicFl;                                   // State of Music button/menu item
	bool soundFl;                                   // State of Sound button/menu item
	bool turboFl;                                   // State of Turbo button/menu item
	bool playlist[kMaxTunes];                       // Tune playlist
};

typedef byte icondib_t[kXPix * kInvDy];             // Icon bar dib
typedef byte viewdib_t[(long)kXPix * kYPix];        // Viewport dib
typedef byte overlay_t[kOvlSize];                   // Overlay file

enum GameType {
	kGameTypeNone  = 0,
	kGameTypeHugo1,
	kGameTypeHugo2,
	kGameTypeHugo3
};

enum GameVariant {
	kGameVariantH1Win = 0,
	kGameVariantH2Win,
	kGameVariantH3Win,
	kGameVariantH1Dos,
	kGameVariantH2Dos,
	kGameVariantH3Dos
};

enum HugoDebugChannels {
	kDebugSchedule  = 1 <<  0,
	kDebugEngine    = 1 <<  1,
	kDebugDisplay   = 1 <<  2,
	kDebugMouse     = 1 <<  3,
	kDebugParser    = 1 <<  4,
	kDebugFile      = 1 <<  5,
	kDebugRoute     = 1 <<  6,
	kDebugInventory = 1 <<  7,
	kDebugObject    = 1 <<  8,
	kDebugMusic     = 1 <<  9
};

enum HugoRegistered {
	kRegShareware = 0,
	kRegRegistered,
	kRegFreeware
};

/**
 * Inventory icon bar states
 */
enum istate_t {kInventoryOff, kInventoryUp, kInventoryDown, kInventoryActive};

/**
 * Game view state machine
 */
enum vstate_t {kViewIdle, kViewIntroInit, kViewIntro, kViewPlay, kViewInvent, kViewExit};

/**
 * Enumerate whether object is foreground, background or 'floating'
 * If floating, HERO can collide with it and fore/back ground is determined
 * by relative y-coord of object base.  This is the general case.
 * If fore or background, no collisions can take place and object is either
 * behind or in front of all others, although can still be hidden by the
 * the overlay plane.  OVEROVL means the object is FLOATING (to other
 * objects) but is never hidden by the overlay plane
 */
enum {kPriorityForeground, kPriorityBackground, kPriorityFloating, kPriorityOverOverlay};

/**
 * Display list functions
 */
enum dupdate_t {kDisplayInit, kDisplayAdd, kDisplayDisplay, kDisplayRestore};

/**
 * Priority for sound effect
 */
enum priority_t {kSoundPriorityLow, kSoundPriorityMedium, kSoundPriorityHigh};

enum HugoGameFeatures {
	GF_PACKED = (1 << 0) // Database
};

// Strings used by the engine
enum seqTextEngine {
	kEsAdvertise = 0
};

struct HugoGameDescription;

struct status_t {                                   // Game status (not saved)
	bool     storyModeFl;                           // Game is telling story - no commands
	bool     gameOverFl;                            // Game is over - hero knobbled
	bool     lookFl;                                // Toolbar "look" button pressed
	bool     recallFl;                              // Toolbar "recall" button pressed
	bool     newScreenFl;                           // New screen just loaded in dib_a
	bool     godModeFl;                             // Allow DEBUG features in live version
	bool     showBoundariesFl;                      // Flag used to show and hide boundaries, 
	                                                // used by the console
	bool     doQuitFl;
	bool     skipIntroFl;
	bool     helpFl;
	uint32   tick;                                  // Current time in ticks
	vstate_t viewState;                             // View state machine
	int16    song;                                  // Current song

// Strangerke - Suppress as related to playback
//	bool     playbackFl;                            // Game is in playback mode
//	bool     recordFl;                              // Game is in record mode
// Strangerke - Not used ?
//	bool     helpFl;                                // Calling WinHelp (don't disable music)
//	bool     mmtimeFl;                              // Multimedia timer supported
//	bool     demoFl;                                // Game is in demo mode
//	bool     textBoxFl;                             // Game is (halted) in text box
//	int16    screenWidth;                           // Desktop screen width
//	int16    saveSlot;                              // Current slot to save/restore game
//	int16    cx, cy;                                // Cursor position (dib coords)
//	uint32   saveTick;                              // Time of last save in ticks
//
//	typedef char fpath_t[kMaxPath];                 // File path
//	fpath_t  path;                                  // Alternate path for saved files
};

/**
 * Structure to define an EXIT or other collision-activated hotspot
 */
struct hotspot_t {
	int        screenIndex;                         // Screen in which hotspot appears
	int        x1, y1, x2, y2;                      // Bounding box of hotspot
	uint16     actIndex;                            // Actions to carry out if a 'hit'
	int16      viewx, viewy, direction;             // Used in auto-route mode
};

class FileManager;
class Scheduler;
class Screen;
class MouseHandler;
class InventoryHandler;
class Parser;
class Route;
class SoundHandler;
class IntroHandler;
class ObjectHandler;
class TextHandler;

class HugoEngine : public Engine {
public:
	HugoEngine(OSystem *syst, const HugoGameDescription *gd);
	~HugoEngine();

	OSystem *_system;

	byte   _numVariant;
	byte   _gameVariant;
	int8   _soundSilence;
	int8   _soundTest;
	int8   _tunesNbr;
	uint16 _numScreens;
	uint16 _numStates;
	int8   _normalTPS;                              // Number of ticks (frames) per second.
	                                                // 8 for Win versions, 9 for DOS versions
	object_t *_hero;
	byte  *_screen_p;
	byte  _heroImage;
	byte  *_screenStates;
	command_t _line;                                // Line of user text input
	config_t  _config;                              // User's config
	int16     *_defltTunes;
	uint16    _look;
	uint16    _take;
	uint16    _drop;

	maze_t      _maze;                              // Maze control structure
	hugo_boot_t _boot;                              // Boot info structure

	GUI::Debugger *getDebugger();

	Common::RandomSource *_rnd;

	const char *_episode;
	Common::String _picDir;

	command_t _statusLine;
	command_t _scoreLine;

	const HugoGameDescription *_gameDescription;
	uint32 getFeatures() const;
	const char *getGameId() const;

	GameType getGameType() const;
	Common::Platform getPlatform() const;
	bool isPacked() const;

	// Used by the qsort function
	static HugoEngine &get() {
		assert(s_Engine != 0);
		return *s_Engine;
	}

	virtual bool canLoadGameStateCurrently();
	virtual bool canSaveGameStateCurrently();
	bool loadHugoDat();

	int8 getTPS() const;

	void initGame(const HugoGameDescription *gd);
	void initGamePart(const HugoGameDescription *gd);
	void endGame();
	void gameOverMsg();
	void initStatus();
	void readScreenFiles(const int screen);
	void setNewScreen(const int screen);
	void shutdown();
	void syncSoundSettings();

	status_t &getGameStatus();
	int getScore() const;
	void setScore(const int newScore);
	void adjustScore(const int adjustment);
	int getMaxScore() const;
	void setMaxScore(const int newScore);
	Common::Error saveGameState(int slot, const char *desc);
	Common::Error loadGameState(int slot);
	bool hasFeature(EngineFeature f) const;
	const char *getCopyrightString() const;

	Common::String getSavegameFilename(int slot);
	uint16 **loadLongArray(Common::SeekableReadStream &in);

	FileManager *_file;
	Scheduler *_scheduler;
	Screen *_screen;
	MouseHandler *_mouse;
	InventoryHandler *_inventory;
	Parser *_parser;
	Route *_route;
	SoundHandler *_sound;
	IntroHandler *_intro;
	ObjectHandler *_object;
	TextHandler *_text;
	TopMenu *_topMenu;

protected:

	// Engine APIs
	Common::Error run();

private:
	static const int kTurboTps = 16;                // This many in turbo mode

	status_t _status;                               // Game status structure
	uint32 _lastTime;
	uint32 _curTime;

	static HugoEngine *s_Engine;

	HugoConsole *_console;

	GameType _gameType;
	Common::Platform _platform;
	bool _packedFl;

	int _score;                                     // Holds current score
	int _maxscore;                                  // Holds maximum score

	void initPlaylist(bool playlist[kMaxTunes]);
	void initConfig();
	void initialize();
	void initMachine();
	void calcMaxScore();
	void resetConfig();
	void runMachine();

};

} // End of namespace Hugo

#endif // Hugo_H
