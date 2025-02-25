	/*
    * SampleEdit.h
    * ------------
    * Purpose: Basic sample editing code (resizing, adding silence, normalizing, ...).
    * Notes  : (currently none)
    * Authors: OpenMPT Devs
    * The OpenMPT source code is released under the BSD license. Read LICENSE for more details.
    */
	
	
	#pragma once
	
	#include "openmpt/all/BuildSettings.hpp"
	
	#include "FadeLaws.h"
	#include "../soundlib/Snd_defs.h"
	
	OPENMPT_NAMESPACE_BEGIN
	
	class CSoundFile;
	struct ModSample;
	struct ModChannel;
	
	namespace SampleEdit
	{
	
	enum ResetFlag
	{
SmpResetCompo,
SmpResetInit,
SmpResetVibrato,
	};
	
	// Get a reference to all cue and loop points of the sample
	std::vector<std::reference_wrapper<SmpLength>> GetCuesAndLoops(ModSample &smp);
	
	
	// Insert silence to given location.
	// Note: Is currently implemented only for inserting silence to the beginning and to the end of the sample.
	// Return: Length of the new sample.
	SmpLength InsertSilence(ModSample &smp, const SmpLength silenceLength, const SmpLength startFrom, CSoundFile &sndFile);
	
	// Remove part of a sample [selStart, selEnd[.
	// Note: Removed memory is not freed.
	// Return: Length of the new sample.
	SmpLength RemoveRange(ModSample &smp, SmpLength selStart, SmpLength selEnd, CSoundFile &sndFile);
	
	// Change sample size.
	// Note: If resized sample is bigger, silence will be added to the sample's tail.
	// Return: Length of the new sample.
	SmpLength ResizeSample(ModSample &smp, const SmpLength newLength, CSoundFile &sndFile);
	
	// Resets samples.
	void ResetSamples(CSoundFile &sndFile, ResetFlag resetflag, SAMPLEINDEX minSample = SAMPLEINDEX_INVALID, SAMPLEINDEX maxSample = SAMPLEINDEX_INVALID);
	
	// Remove DC offset and normalize.
	// Return: If DC offset was removed, returns original offset value, zero otherwise.
	double RemoveDCOffset(ModSample &smp, SmpLength start, SmpLength end, CSoundFile &sndFile);
	
	// Amplify / fade  sample data
	bool AmplifySample(ModSample &smp, SmpLength start, SmpLength end, double amplifyStart, double amplifyEnd, bool isFadeIn, Fade::Law fadeLaw, CSoundFile &sndFile);
	
	// Reverse sample data
	bool ReverseSample(ModSample &smp, SmpLength start, SmpLength end, CSoundFile &sndFile);
	
	// Virtually unsign sample data
	bool UnsignSample(ModSample &smp, SmpLength start, SmpLength end, CSoundFile &sndFile);
	
	// Invert sample data (flip by 180 degrees)
	bool InvertSample(ModSample &smp, SmpLength start, SmpLength end, CSoundFile &sndFile);
	
	// Crossfade sample data to create smooth loops
	bool XFadeSample(ModSample &smp, SmpLength fadeLength, int fadeLaw, bool afterloopFade, bool useSustainLoop, CSoundFile &sndFile);
	
	// Silence parts of the sample data
	bool SilenceSample(ModSample &smp, SmpLength start, SmpLength end, CSoundFile &sndFile);
	
	// Modify stereo separation of the sample data. separation is in range [-200, 200]
	bool StereoSepSample(ModSample &smp, SmpLength start, SmpLength end, double separation, CSoundFile &sndFile);
	
	// Convert 16-bit sample to 8-bit
	bool ConvertTo8Bit(ModSample &smp, CSoundFile &sndFile);
	
	// Convert 8-bit sample to 16-bit
	bool ConvertTo16Bit(ModSample &smp, CSoundFile &sndFile);
	
	// Convert ping-pong loops to regular loops
	bool ConvertPingPongLoop(ModSample &smp, CSoundFile &sndFile, bool sustainLoop);
	
	} // namespace SampleEdit
	
	OPENMPT_NAMESPACE_END
	