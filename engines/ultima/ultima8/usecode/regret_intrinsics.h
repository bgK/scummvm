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

#ifndef ULTIMA8_USECODE_REGRETINTRINSICS_H
#define ULTIMA8_USECODE_REGRETINTRINSICS_H

#include "ultima/ultima8/usecode/intrinsics.h"
#include "ultima/ultima8/world/item.h"

namespace Ultima {
namespace Ultima8 {

// Crusader: No Regret Intrinsics
Intrinsic RegretIntrinsics[] = {
	0, // Intrinsic000()
	Item::I_getFrame, // Intrinsic001()
	Item::I_setFrame, // Intrinsic002()
	Item::I_getMapArray, // Intrinsic003()
	Item::I_getStatus, // Intrinsic004()
	Item::I_orStatus, // Intrinsic005()
	Item::I_equip, // Intrinsic006()
	Item::I_isOnScreen, // Intrinsic007()
	Actor::I_isNPC, // Intrinsic008()
	Item::I_getZ, // Intrinsic009()
	0, // Intrinsic00A()
	Item::I_getQLo, // Intrinsic00B()
	Item::I_destroy, // Intrinsic00C()
	0, // Intrinsic00D()
	Item::I_getX, // Intrinsic00E()
	Item::I_getY, // Intrinsic00F()
	// 0010
	AudioProcess::I_playSFXCru, // Intrinsic010()
	Item::I_getShape, // Intrinsic011()
	0, // Intrinsic012()
	0, // Intrinsic013()
	Item::I_legalCreateAtCoords, // Intrinsic014()
	Item::I_andStatus, // Intrinsic015()
	0, // Intrinsic016()
	0, // Intrinsic017()
	0, // Intrinsic018()
	0, // Intrinsic019()
	Item::I_create, // Intrinsic01A()
	Item::I_popToCoords, // Intrinsic01B()
	0, // Intrinsic01C()
	Item::I_push, // Intrinsic01D()
	0, // Intrinsic01E()
	Item::I_getQLo, // Intrinsic01F()
	// 0020
	Item::I_setQLo, // Intrinsic020()
	Item::I_getQHi, // Intrinsic021()
	Item::I_setQHi, // Intrinsic022()
	0, // Intrinsic023()
	0, // Intrinsic024()
	Item::I_getCY, // Intrinsic025()
	Item::I_getCX, // Intrinsic026()
	0, // Intrinsic027()
	Item::I_setNpcNum, // Intrinsic028()
	0, // Intrinsic029()
	Item::I_setShape, // Intrinsic02A()
	Item::I_pop, // Intrinsic02B()
	0, // Intrinsic02C()
	Item::I_isCompletelyOn, // Intrinsic02D()
	Item::I_popToContainer, // Intrinsic02E()
	0, // Intrinsic02F()
	// 0030
	0, // Intrinsic030()
	Item::I_getFamily, // Intrinsic031()
	Actor::I_destroyContents, // Intrinsic032()
	0, // Intrinsic033()
	Item::I_getDirToItem, // Intrinsic034()
	0, // Intrinsic035()
	0, // Intrinsic036()
	0, // Intrinsic037()
	Item::I_andStatus, // Intrinsic038()
	Kernel::I_resetRef, // Intrinsic039()
	Item::I_touch, // Intrinsic03A()
	Egg::I_getEggId, // Intrinsic03B()
	0, // Intrinsic03C()
	0, // Intrinsic03D()
	0, // Intrinsic03E()
	0, // Intrinsic03F()
	// 0040
	0, // Intrinsic040()
	Item::I_isOn, // Intrinsic041()
	Item::I_getQHi, // Intrinsic042()
	Item::I_isOn, // Intrinsic043()
	Item::I_getQHi, // Intrinsic044()
	Item::I_isOn, // Intrinsic045()
	Item::I_getQHi, // Intrinsic046()
	Item::I_isOn, // Intrinsic047()
	Item::I_getQHi, // Intrinsic048()
	Item::I_isOn, // Intrinsic049()
	Item::I_getQHi, // Intrinsic04A()
	Item::I_isOn, // Intrinsic04B()
	Item::I_getQHi, // Intrinsic04C()
	0, // Intrinsic04D()
	Actor::I_isDead, // Intrinsic04E()
	0, // Intrinsic04F()
	// 0050
	0, // Intrinsic050()
	0, // Intrinsic051()
	0, // Intrinsic052()
	0, // Intrinsic053()
	0, // Intrinsic054()
	0, // Intrinsic055()
	0, // Intrinsic056()
	0, // Intrinsic057()
	Item::I_use, // Intrinsic058()
	0, // Intrinsic059()
	0, // Intrinsic05A()
	Item::I_getSurfaceWeight, // Intrinsic05B()
	0, // Intrinsic05C()
	Item::I_setFrame, // Intrinsic05D()
	0, // Intrinsic05E()
	0, // Intrinsic05F()
	// 0060
	0, // Intrinsic060()
	0, // Intrinsic061()
	0, // Intrinsic062()
	Item::I_legalCreateAtPoint, // Intrinsic063()
	Item::I_getPoint, // Intrinsic064()
	Item::I_legalMoveToPoint, // Intrinsic065()
	Item::I_fall, // Intrinsic066()
	0, // Intrinsic067()
	Kernel::I_getNumProcesses, // Intrinsic068()
	Item::I_getCY, // Intrinsic069()
	0, // Intrinsic06A()
	0, // Intrinsic06B()
	0, // Intrinsic06C()
	0, // Intrinsic06D()
	0, // Intrinsic06E()
	Item::I_isInNpc, // Intrinsic06F()
	// 0070
	0, // Intrinsic070()
	0, // Intrinsic071()
	0, // Intrinsic072()
	0, // Intrinsic073()
	Actor::I_isDead, // Intrinsic074()
	Actor::I_getNpcNum, // Intrinsic075()
	0, // Intrinsic076()
	0, // Intrinsic077()
	Item::I_unequip, // Intrinsic078()
	Item::I_andStatus, // Intrinsic079()
	Item::I_move, // Intrinsic07A()
	0, // Intrinsic07B()
	0, // Intrinsic07C()
	0, // Intrinsic07D()
	0, // Intrinsic07E()
	0, // Intrinsic07F()
	// 0080
	0, // Intrinsic080()
	0, // Intrinsic081()
	0, // Intrinsic082()
	0, // Intrinsic083()
	0, // Intrinsic084()
	0, // Intrinsic085()
	0, // Intrinsic086()
	0, // Intrinsic087()
	0, // Intrinsic088()
	0, // Intrinsic089()
	Item::I_getQuality, // Intrinsic08A()
	Item::I_setQuality, // Intrinsic08B()
	0, // Intrinsic08C()
	0, // Intrinsic08D()
	0, // Intrinsic08E()
	CameraProcess::I_getCameraX, // Intrinsic08F()
	// 0090
	CameraProcess::I_getCameraY, // Intrinsic090()
	Item::I_setMapArray, // Intrinsic091()
	Actor::I_getNpcNum, // Intrinsic092()
	0, // Intrinsic093()
	0, // Intrinsic094()
	Item::I_enterFastArea, // Intrinsic095()
	Item::I_setBroken, // Intrinsic096()
	0, // Intrinsic097()
	Actor::I_getNpcNum, // Intrinsic098()
	0, // Intrinsic099()
	0, // Intrinsic09A()
	0, // Intrinsic09B()
	0, // Intrinsic09C()
	0, // Intrinsic09D()
	0, // Intrinsic09E()
	0, // Intrinsic09F()
	// 00A0
	Item::I_andStatus, // Intrinsic0A0()
	Egg::I_getUnkEggType, // Intrinsic0A1()
	Egg::I_setEggXRange, // Intrinsic0A2()
	Item::I_setFrame, // Intrinsic0A3()
	Item::I_overlaps, // Intrinsic0A4()
	Item::I_isOn, // Intrinsic0A5()
	Item::I_getQHi, // Intrinsic0A6()
	0, // Intrinsic0A7()
	Item::I_getCY, // Intrinsic0A8()
	0, // Intrinsic0A9()
	Item::I_isOn, // Intrinsic0AA()
	Actor::I_isDead, // Intrinsic0AB()
	0, // Intrinsic0AC()
	0, // Intrinsic0AD()
	Item::I_getQHi, // Intrinsic0AE()
	Item::I_andStatus, // Intrinsic0AF()
	// 00B0
	0, // Intrinsic0B0()
	Item::I_andStatus, // Intrinsic0B1()
	0, // Intrinsic0B2()
	Item::I_andStatus, // Intrinsic0B3()
	0, // Intrinsic0B4()
	0, // Intrinsic0B5()
	0, // Intrinsic0B6()
	Actor::I_getNpcNum, // Intrinsic0B7()
	Item::I_getCY, // Intrinsic0B8()
	Item::I_isOn, // Intrinsic0B9()
	Item::I_getFootpadData, // Intrinsic0BA()
	Actor::I_isDead, // Intrinsic0BB()
	Actor::I_createActorCru, // Intrinsic0BC()
	0, // Intrinsic0BD()
	0, // Intrinsic0BE()
	Item::I_andStatus, // Intrinsic0BF()
	// 00C0
	0, // Intrinsic0C0()
	0, // Intrinsic0C1()
	0, // Intrinsic0C2()
	0, // Intrinsic0C3()
	Item::I_getQHi, // Intrinsic0C4()
	Item::I_setQuality, // Intrinsic0C5()
	0, // Intrinsic0C6()
	0, // Intrinsic0C7()
	0, // Intrinsic0C8()
	Item::I_equip, // Intrinsic0C9()
	Item::I_setBroken, // Intrinsic0CA()
	Item::I_isOn, // Intrinsic0CB()
	0, // Intrinsic0CC()
	0, // Intrinsic0CD()
	Item::I_getQHi, // Intrinsic0CE()
	Item::I_isOn, // Intrinsic0CF()
	// 00D0
	0, // Intrinsic0D0()
	0, // Intrinsic0D1()
	0, // Intrinsic0D2()
	0, // Intrinsic0D3()
	CameraProcess::I_getCameraY, // Intrinsic0D4()
	0, // Intrinsic0D5()
	0, // Intrinsic0D6()
	0, // Intrinsic0D7()
	0, // Intrinsic0D8()
	0, // Intrinsic0D9()
	0, // Intrinsic0DA()
	0, // Intrinsic0DB()
	Item::I_getQLo, // Intrinsic0DC()
	Item::I_getQHi, // Intrinsic0DD()
	Actor::I_getNpcNum, // Intrinsic0DE()
	0, // Intrinsic0DF()
	// 00E0
	0, // Intrinsic0E0()
	0, // Intrinsic0E1()
	Item::I_getQLo, // Intrinsic0E2()
	Item::I_getCY, // Intrinsic0E3()
	Actor::I_getNpcNum, // Intrinsic0E4()
	0, // Intrinsic0E5()
	Actor::I_getNpcNum, // Intrinsic0E6()
	0, // Intrinsic0E7()
	Actor::I_getNpcNum, // Intrinsic0E8()
	0, // Intrinsic0E9()
	Actor::I_getNpcNum, // Intrinsic0EA()
	0, // Intrinsic0EB()
	Actor::I_getNpcNum, // Intrinsic0EC()
	0, // Intrinsic0ED()
	Actor::I_getNpcNum, // Intrinsic0EE()
	0, // Intrinsic0EF()
	// 00F0
	Actor::I_getNpcNum, // Intrinsic0F0()
	0, // Intrinsic0F1()
	Actor::I_getNpcNum, // Intrinsic0F2()
	0, // Intrinsic0F3()
	Actor::I_getNpcNum, // Intrinsic0F4()
	0, // Intrinsic0F5()
	Actor::I_getNpcNum, // Intrinsic0F6()
	Item::I_andStatus, // Intrinsic0F7()
	0, // Intrinsic0F8()
	Item::I_getQLo, // Intrinsic0F9()
	0, // Intrinsic0FA()
	0, // Intrinsic0FB()
	0, // Intrinsic0FC()
	Item::I_getQLo, // Intrinsic0FD()
	0, // Intrinsic0FE()
	0, // Intrinsic0FF()
	// 0100
	Item::I_andStatus, // Intrinsic100()
	Item::I_isOn, // Intrinsic101()
	Actor::I_isDead, // Intrinsic102()
	0, // Intrinsic103()
	Item::I_getQHi, // Intrinsic104()
	0, // Intrinsic105()
	0, // Intrinsic106()
	Item::I_getQLo, // Intrinsic107()
	Item::I_isOn, // Intrinsic108()
	Item::I_getQHi, // Intrinsic109()
	Item::I_isOn, // Intrinsic10A()
	Item::I_getQHi, // Intrinsic10B()
	0, // Intrinsic10C()
	Actor::I_getNpcNum, // Intrinsic10D()
	Item::I_getCY, // Intrinsic10E()
	0, // Intrinsic10F()
	// 0110
	Item::I_isOn, // Intrinsic110()
	0, // Intrinsic111()
	0, // Intrinsic112()
	Actor::I_isDead, // Intrinsic113()
	0, // Intrinsic114()
	0, // Intrinsic115()
	Item::I_getQHi, // Intrinsic116()
	0, // Intrinsic117()
	Item::I_andStatus, // Intrinsic118()
	Actor::I_getNpcNum, // Intrinsic119()
	Item::I_andStatus, // Intrinsic11A()
	Actor::I_getNpcNum, // Intrinsic11B()
	0, // Intrinsic11C()
	Item::I_andStatus, // Intrinsic11D()
	Actor::I_getNpcNum, // Intrinsic11E()
	0, // Intrinsic11F()
	// 0120
	Item::I_andStatus, // Intrinsic120()
	Actor::I_getNpcNum, // Intrinsic121()
	Item::I_getQ, // Intrinsic122()
	Item::I_setQ, // Intrinsic123()
	Item::I_andStatus, // Intrinsic124()
	Actor::I_getNpcNum, // Intrinsic125()
	Item::I_andStatus, // Intrinsic126()
	Actor::I_getNpcNum, // Intrinsic127()
	Item::I_andStatus, // Intrinsic128()
	Actor::I_getNpcNum, // Intrinsic129()
	Item::I_andStatus, // Intrinsic12A()
	Actor::I_getNpcNum, // Intrinsic12B()
	Item::I_andStatus, // Intrinsic12C()
	Actor::I_getNpcNum, // Intrinsic12D()
	0, // Intrinsic12E()
	Item::I_andStatus, // Intrinsic12F()
	// 0130
	Actor::I_getNpcNum, // Intrinsic130()
	0, // Intrinsic131()
	Item::I_andStatus, // Intrinsic132()
	0, // Intrinsic133()
	Item::I_andStatus, // Intrinsic134()
	CameraProcess::I_getCameraY, // Intrinsic135()
	CameraProcess::I_getCameraZ, // Intrinsic136()
	0, // Intrinsic137()
	0, // Intrinsic138()
	0, // Intrinsic139()
	Actor::I_getNpcNum, // Intrinsic13A()
	0, // Intrinsic13B()
	Item::I_getCY, // Intrinsic13C()
	Item::I_getCZ, // Intrinsic13D()
	Item::I_setFrame, // Intrinsic13E()
	0, // Intrinsic13F()
	// 0140
	0, // Intrinsic140()
	0, // Intrinsic141()
	0, // Intrinsic142()
	Actor::I_isDead, // Intrinsic143()
	0, // Intrinsic144()
	0, // Intrinsic145()
	0, // Intrinsic146()
	0, // Intrinsic147()
	Actor::I_getNpcNum, // Intrinsic148()
	Item::I_getQLo, // Intrinsic149()
	Item::I_andStatus, // Intrinsic14A()
	Ultima8Engine::I_getCurrentTimerTick, // Intrinsic14B()
	0, // Intrinsic14C()
	0, // Intrinsic14D()
	0, // Intrinsic14E()
	Egg::I_getEggXRange, // Intrinsic14F()
	// 0150
	0, // Intrinsic150()
	0, // Intrinsic151()
	Item::I_setFrame, // Intrinsic152()
	0, // Intrinsic153()
	0, // Intrinsic154()
	0, // Intrinsic155()
	Item::I_isOn, // Intrinsic156()
	0, // Intrinsic157()
	0, // Intrinsic158()
	Item::I_getQHi, // Intrinsic159()
	Item::I_getQLo, // Intrinsic15A()
	0, // Intrinsic15B()
	0, // Intrinsic15C()
	0  // Intrinsic15D()
};

} // End of namespace Ultima8
} // End of namespace Ultima

#endif