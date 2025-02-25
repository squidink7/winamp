			/*
            * SampleFormatOpus.cpp
            * --------------------
            * Purpose: Opus sample import.
            * Notes  :
            * Authors: OpenMPT Devs
            * The OpenMPT source code is released under the BSD license. Read LICENSE for more details.
            */
			
			
			#include "stdafx.h"
			#include "Sndfile.h"
			#ifndef MODPLUG_NO_FILESAVE
			#include "../common/mptFileIO.h"
			#endif
			#include "../common/misc_util.h"
			#include "Tagging.h"
			#include "Loaders.h"
			#include "../common/FileReader.h"
			#include "modsmp_ctrl.h"
			#include "openmpt/soundbase/Copy.hpp"
			#include "../soundlib/ModSampleCopy.h"
			//#include "mpt/crc/crc.hpp"
			#include "OggStream.h"
			#ifdef MPT_WITH_OGG
			#if MPT_COMPILER_CLANG
			#pragma clang diagnostic push
			#pragma clang diagnostic ignored "-Wreserved-id-macro"
			#endif // MPT_COMPILER_CLANG
			#include <ogg/ogg.h>
			#if MPT_COMPILER_CLANG
			#pragma clang diagnostic pop
			#endif // MPT_COMPILER_CLANG
			#endif // MPT_WITH_OGG
			#if defined(MPT_WITH_OPUSFILE)
			#include <opusfile.h>
			#endif // MPT_WITH_OPUSFILE
			
			
			OPENMPT_NAMESPACE_BEGIN
			
			
			////////////////////////////////////////////////////////////////////////////////
			// Opus
			
			#if defined(MPT_WITH_OPUSFILE)
			
			static mpt::ustring UStringFromOpus(const char *str)
			{
		return str ? mpt::ToUnicode(mpt::Charset::UTF8, str) : mpt::ustring();
			}
			
			static FileTags GetOpusFileTags(OggOpusFile *of)
			{
		FileTags tags;
		const OpusTags *ot = op_tags(of, -1);
		if(!ot)
		{
	return tags;
		}
		tags.encoder = UStringFromOpus(opus_tags_query(ot, "ENCODER", 0));
		tags.title = UStringFromOpus(opus_tags_query(ot, "TITLE", 0));
		tags.comments = UStringFromOpus(opus_tags_query(ot, "DESCRIPTION", 0));
		tags.bpm = UStringFromOpus(opus_tags_query(ot, "BPM", 0)); // non-standard
		tags.artist = UStringFromOpus(opus_tags_query(ot, "ARTIST", 0));
		tags.album = UStringFromOpus(opus_tags_query(ot, "ALBUM", 0));
		tags.trackno = UStringFromOpus(opus_tags_query(ot, "TRACKNUMBER", 0));
		tags.year = UStringFromOpus(opus_tags_query(ot, "DATE", 0));
		tags.url = UStringFromOpus(opus_tags_query(ot, "CONTACT", 0));
		tags.genre = UStringFromOpus(opus_tags_query(ot, "GENRE", 0));
		return tags;
			}
			
			#endif // MPT_WITH_OPUSFILE
			
			bool CSoundFile::ReadOpusSample(SAMPLEINDEX sample, FileReader &file)
			{
		file.Rewind();
			
			#if defined(MPT_WITH_OPUSFILE)
			
		int rate = 0;
		int channels = 0;
		std::vector<int16> raw_sample_data;
			
		std::string sampleName;
			
		FileReader initial = file.GetChunk(65536); // 512 is recommended by libopusfile
		if(op_test(NULL, initial.GetRawData<unsigned char>().data(), initial.GetLength()) != 0)
		{
	return false;
		}
			
		OggOpusFile *of = op_open_memory(file.GetRawData<unsigned char>().data(), file.GetLength(), NULL);
		if(!of)
		{
	return false;
		}
			
		rate = 48000;
		channels = op_channel_count(of, -1);
		if(rate <= 0 || channels <= 0)
		{
	op_free(of);
	of = NULL;
	return false;
		}
		if(channels > 2 || op_link_count(of) != 1)
		{
	// We downmix multichannel to stereo as recommended by Opus specification in
	// case we are not able to handle > 2 channels.
	// We also decode chained files as stereo even if they start with a mono
	// stream, which simplifies handling of link boundaries for us.
	channels = 2;
		}
			
		sampleName = mpt::ToCharset(GetCharsetInternal(), GetSampleNameFromTags(GetOpusFileTags(of)));
			
		if(auto length = op_pcm_total(of, 0); length != OP_EINVAL)
	raw_sample_data.reserve(std::min(MAX_SAMPLE_LENGTH, mpt::saturate_cast<SmpLength>(length)) * channels);
			
		std::vector<int16> decodeBuf(120 * 48000 / 1000); // 120ms (max Opus packet), 48kHz
		bool eof = false;
		while(!eof)
		{
	int framesRead = 0;
	if(channels == 2)
	{
framesRead = op_read_stereo(of, &(decodeBuf[0]), static_cast<int>(decodeBuf.size()));
	} else if(channels == 1)
	{
framesRead = op_read(of, &(decodeBuf[0]), static_cast<int>(decodeBuf.size()), NULL);
	}
	if(framesRead > 0)
	{
mpt::append(raw_sample_data, decodeBuf.begin(), decodeBuf.begin() + (framesRead * channels));
	} else if(framesRead == 0)
	{
eof = true;
	} else if(framesRead == OP_HOLE)
	{
// continue
	} else
	{
// other errors are fatal, stop decoding
eof = true;
	}
	if((raw_sample_data.size() / channels) > MAX_SAMPLE_LENGTH)
	{
break;
	}
		}
			
		op_free(of);
		of = NULL;
			
		if(raw_sample_data.empty())
		{
	return false;
		}
			
		DestroySampleThreadsafe(sample);
		ModSample &mptSample = Samples[sample];
		mptSample.Initialize();
		mptSample.nC5Speed = rate;
		mptSample.nLength = std::min(MAX_SAMPLE_LENGTH, mpt::saturate_cast<SmpLength>(raw_sample_data.size() / channels));
			
		mptSample.uFlags.set(CHN_16BIT);
		mptSample.uFlags.set(CHN_STEREO, channels == 2);
			
		if(!mptSample.AllocateSample())
		{
	return false;
		}
			
		if(raw_sample_data.size() / channels > MAX_SAMPLE_LENGTH)
		{
	AddToLog(LogWarning, U_("Sample has been truncated!"));
		}
			
		std::copy(raw_sample_data.begin(), raw_sample_data.begin() + mptSample.nLength * channels, mptSample.sample16());
			
		mptSample.Convert(MOD_TYPE_IT, GetType());
		mptSample.PrecomputeLoops(*this, false);
		m_szNames[sample] = sampleName;
			
		return true;
			
			#else // !MPT_WITH_OPUSFILE
			
		MPT_UNREFERENCED_PARAMETER(sample);
		MPT_UNREFERENCED_PARAMETER(file);
			
		return false;
			
			#endif // MPT_WITH_OPUSFILE
			
			}
			
			
			OPENMPT_NAMESPACE_END
			