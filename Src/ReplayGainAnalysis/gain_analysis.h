	/*
	*  ReplayGainAnalysis - analyzes input samples and give the recommended dB change
	*  Copyright (C) 2001 David Robinson and Glen Sawyer
	*
	*  This library is free software; you can redistribute it and/or
	*  modify it under the terms of the GNU Lesser General Public
	*  License as published by the Free Software Foundation; either
	*  version 2.1 of the License, or (at your option) any later version.
	*
	*  This library is distributed in the hope that it will be useful,
	*  but WITHOUT ANY WARRANTY; without even the implied warranty of
	*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	*  Lesser General Public License for more details.
	*
	*  You should have received a copy of the GNU Lesser General Public
	*  License along with this library; if not, write to the Free Software
	*  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
	*
	*  concept and filter values by David Robinson (David@Robinson.org)
	*    -- blame him if you think the idea is flawed
	*  coding by Glen Sawyer (mp3gain@hotmail.com) 735 W 255 N, Orem, UT 84057-4505 USA
	*    -- blame him if you think this runs too slowly, or the coding is otherwise flawed
	*
	*  For an explanation of the concepts and the basic algorithms involved, go to:
	*    http://www.replaygain.org/
	*/
	
	#ifndef GAIN_ANALYSIS_H
	#define GAIN_ANALYSIS_H
	
	#include <stddef.h>
	#include <bfc/platform/export.h>
	
	#define GAIN_NOT_ENOUGH_SAMPLES  -24601
	#define GAIN_ANALYSIS_ERROR           0
	#define GAIN_ANALYSIS_OK              1
	
	#define INIT_GAIN_ANALYSIS_ERROR      0
	#define INIT_GAIN_ANALYSIS_OK         1
	
	#ifdef __cplusplus
	extern "C"
	{
	#endif
	
typedef float Float_t;         // Type used for filtering
	
DLLEXPORT void * WACreateRGContext();
DLLEXPORT void WAFreeRGContext(void *context);
	
int DLLEXPORT WAInitGainAnalysis(void *context, long samplefreq);
int DLLEXPORT WAAnalyzeSamples(void *context, const Float_t* left_samples, const Float_t* right_samples, size_t num_samples, int num_channels);
int	DLLEXPORT WAResetSampleFrequency ( void *context, long samplefreq );
Float_t DLLEXPORT WAGetTitleGain(void *context);
Float_t DLLEXPORT WAGetAlbumGain(void *context);
	
	#ifdef __cplusplus
	}
	#endif
	
	#endif /* GAIN_ANALYSIS_H */
	