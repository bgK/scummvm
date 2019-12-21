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

#ifndef ULTIMA6_SOUND_MIXER_DECODER_PC_SPEAKER_STREAM_H
#define ULTIMA6_SOUND_MIXER_DECODER_PC_SPEAKER_STREAM_H

#include "ultima/shared/std/string.h"
#include "ultima/ultima6/sound/mixer/decoder/pc_speaker.h"
#include "audio/audiostream.h"

namespace Ultima {
namespace Ultima6 {

class PCSpeakerStream : public Audio::RewindableAudioStream {
public:
	PCSpeakerStream() {
		pcspkr = new PCSpeaker(SPKR_OUTPUT_RATE);
		finished = false;
	}

	~PCSpeakerStream() {
		delete pcspkr;
	}

	/** Is this a stereo stream? */
	bool isStereo() const {
		return false;
	}

	/** Sample rate of the stream. */
	int getRate() const {
		return SPKR_OUTPUT_RATE;
	}

	/**
	 * End of data reached? If this returns true, it means that at this
	 * time there is no data available in the stream. However there may be
	 * more data in the future.
	 * This is used by e.g. a rate converter to decide whether to keep on
	 * converting data or stop.
	 */
	bool endOfData() const {
		return finished;
	}

	bool rewind() {
		return false;
	}

protected:
	PCSpeaker *pcspkr;
	bool finished;
};


class PCSpeakerFreqStream : public PCSpeakerStream {
public:
	PCSpeakerFreqStream() {

	}

	PCSpeakerFreqStream(uint32 start, uint16 d);
	~PCSpeakerFreqStream();
	uint32 getLengthInMsec();
	int readBuffer(sint16 *buffer, const int numSamples);

protected:

	uint32 frequency;
	uint32 duration;
	uint32 total_samples_played;

};

class PCSpeakerSweepFreqStream : public PCSpeakerStream {
public:
	PCSpeakerSweepFreqStream() {

	}

	PCSpeakerSweepFreqStream(uint32 start, uint32 end, uint16 d, uint16 s);
	~PCSpeakerSweepFreqStream();
	uint32 getLengthInMsec();
	int readBuffer(sint16 *buffer, const int numSamples);

protected:

	uint32 start_freq;
	uint32 finish_freq;
	uint32 cur_freq;
	uint16 duration;
	uint16 stepping;

	uint32 freq_step;
	float samples_per_step;
	float sample_pos;
	uint32 total_samples_played;
	uint32 num_steps;
	uint32 cur_step;

};

class PCSpeakerRandomStream : public PCSpeakerStream {
public:
	PCSpeakerRandomStream() {

	}

	PCSpeakerRandomStream(uint32 start, uint16 d, uint16 s);
	~PCSpeakerRandomStream();
	uint32 getLengthInMsec();
	uint16 getNextFreqValue();
	int readBuffer(sint16 *buffer, const int numSamples);

protected:

	uint16 base_val;
	uint16 duration;
	uint16 stepping;

	uint32 rand_value;
	uint32 sample_pos;
	uint32 total_samples_played;
	uint32 samples_per_step;
	uint32 num_steps;
	uint32 cur_step;

};

class PCSpeakerStutterStream : public PCSpeakerStream {
public:
	PCSpeakerStutterStream() {

	}

	PCSpeakerStutterStream(sint16 a0, uint16 a2, uint16 a4, uint16 a6, uint16 a8);
	~PCSpeakerStutterStream();
	uint32 getLengthInMsec();
	int readBuffer(sint16 *buffer, const int numSamples);

protected:

	sint16 arg_0;
	uint16 arg_2;
	uint16 arg_4;
	uint16 arg_6;
	uint16 arg_8;

	uint16 dx;
	uint16 cx;
	float delay;
	float delay_remaining;

};

Audio::AudioStream *makePCSpeakerSlugDissolveSfxStream(uint32 rate);
Audio::AudioStream *makePCSpeakerGlassSfxStream(uint32 rate);
Audio::AudioStream *makePCSpeakerMagicCastingP1SfxStream(uint32 rate, uint8 magic_circle);
Audio::AudioStream *makePCSpeakerMagicCastingP2SfxStream(uint32 rate, uint8 magic_circle);
Audio::AudioStream *makePCSpeakerAvatarDeathSfxStream(uint32 rate);
Audio::AudioStream *makePCSpeakerKalLorSfxStream(uint32 rate);
Audio::AudioStream *makePCSpeakerHailStoneSfxStream(uint32 rate);
Audio::AudioStream *makePCSpeakerEarthQuakeSfxStream(uint32 rate);

} // End of namespace Ultima6
} // End of namespace Ultima

#endif
