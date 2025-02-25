				/*
                * StreamEncoder.cpp
                * -----------------
                * Purpose: Exporting streamed music files.
                * Notes  : none
                * Authors: Joern Heusipp
                *          OpenMPT Devs
                * The OpenMPT source code is released under the BSD license. Read LICENSE for more details.
                */
				
				#include "stdafx.h"
				
				#include "StreamEncoder.h"
				#include "StreamEncoderWAV.h"
				
				#include "mpt/io/io.hpp"
				#include "mpt/io/io_stdstream.hpp"
				
				#include "Mptrack.h"
				#include "TrackerSettings.h"
				
				#include "../soundlib/Sndfile.h"
				#include "../soundlib/WAVTools.h"
				
				
				OPENMPT_NAMESPACE_BEGIN
				
				
				class WavStreamWriter : public IAudioStreamEncoder
				{
				private:
				
			const WAVEncoder &enc;
			std::ostream &f;
			mpt::IO::OFile<std::ostream> ff;
			std::unique_ptr<WAVWriter> fileWAV;
			Encoder::Settings settings;
				
				public:
			WavStreamWriter(const WAVEncoder &enc_, std::ostream &file, const Encoder::Settings &settings_, const FileTags &tags)
		: enc(enc_)
		, f(file)
		, ff(f)
		, fileWAV(nullptr)
		, settings(settings_)
			{
				
		MPT_ASSERT(settings.Format.GetSampleFormat().IsValid());
		MPT_ASSERT(settings.Samplerate > 0);
		MPT_ASSERT(settings.Channels > 0);
				
		fileWAV = std::make_unique<WAVWriter>(ff);
		fileWAV->WriteFormat(settings.Samplerate, settings.Format.GetSampleFormat().GetBitsPerSample(), settings.Channels, settings.Format.GetSampleFormat().IsFloat() ? WAVFormatChunk::fmtFloat : WAVFormatChunk::fmtPCM);
				
		if(settings.Tags)
		{
	fileWAV->WriteMetatags(tags);
		}
				
		fileWAV->StartChunk(RIFFChunk::iddata);
				
			}
			SampleFormat GetSampleFormat() const override
			{
		return settings.Format.GetSampleFormat();
			}
			void WriteInterleaved(std::size_t frameCount, const double *interleaved) override
			{
		fileWAV->WriteBeforeDirect();
		auto result = WriteInterleavedLE(f, settings.Channels, settings.Format, frameCount, interleaved);
		fileWAV->WriteAfterDirect(result.first, result.second);
			}
			void WriteInterleaved(std::size_t frameCount, const float *interleaved) override
			{
		fileWAV->WriteBeforeDirect();
		auto result = WriteInterleavedLE(f, settings.Channels, settings.Format, frameCount, interleaved);
		fileWAV->WriteAfterDirect(result.first, result.second);
			}
			void WriteInterleaved(std::size_t frameCount, const int32 *interleaved) override
			{
		fileWAV->WriteBeforeDirect();
		auto result = WriteInterleavedLE(f, settings.Channels, settings.Format, frameCount, interleaved);
		fileWAV->WriteAfterDirect(result.first, result.second);
			}
			void WriteInterleaved(std::size_t frameCount, const int24 *interleaved) override
			{
		fileWAV->WriteBeforeDirect();
		auto result = WriteInterleavedLE(f, settings.Channels, settings.Format, frameCount, interleaved);
		fileWAV->WriteAfterDirect(result.first, result.second);
			}
			void WriteInterleaved(std::size_t frameCount, const int16 *interleaved) override
			{
		fileWAV->WriteBeforeDirect();
		auto result = WriteInterleavedLE(f, settings.Channels, settings.Format, frameCount, interleaved);
		fileWAV->WriteAfterDirect(result.first, result.second);
			}
			void WriteInterleaved(std::size_t frameCount, const int8 *interleaved) override
			{
		fileWAV->WriteBeforeDirect();
		auto result = WriteInterleavedLE(f, settings.Channels, settings.Format, frameCount, interleaved);
		fileWAV->WriteAfterDirect(result.first, result.second);
			}
			void WriteInterleaved(std::size_t frameCount, const uint8 *interleaved) override
			{
		fileWAV->WriteBeforeDirect();
		auto result = WriteInterleavedLE(f, settings.Channels, settings.Format, frameCount, interleaved);
		fileWAV->WriteAfterDirect(result.first, result.second);
			}
			void WriteCues(const std::vector<uint64> &cues) override
			{
		if(!cues.empty())
		{
	// Cue point header
	fileWAV->StartChunk(RIFFChunk::idcue_);
	uint32le numPoints;
	numPoints = mpt::saturate_cast<uint32>(cues.size());
	fileWAV->Write(numPoints);
				
	// Write all cue points
	uint32 index = 0;
	for(auto cue : cues)
	{
WAVCuePoint cuePoint{};
cuePoint.id = index++;
cuePoint.position = static_cast<uint32>(cue);
cuePoint.riffChunkID = static_cast<uint32>(RIFFChunk::iddata);
cuePoint.chunkStart = 0;	// we use no Wave List Chunk (wavl) as we have only one data block, so this should be 0.
cuePoint.blockStart = 0;	// ditto
cuePoint.offset = cuePoint.position;
fileWAV->Write(cuePoint);
	}
		}
			}
			void WriteFinalize() override
			{
		fileWAV->Finalize();
			}
			virtual ~WavStreamWriter()
			{
		fileWAV = nullptr;
			}
				};
				
				
				
				WAVEncoder::WAVEncoder()
				{
			Encoder::Traits traits;
			traits.fileExtension = P_("wav");
			traits.fileShortDescription = U_("Wave");
			traits.fileDescription = U_("Microsoft RIFF Wave");
			traits.encoderSettingsName = U_("Wave");
			traits.canTags = true;
			traits.canCues = true;
			traits.maxChannels = 4;
			traits.samplerates = TrackerSettings::Instance().GetSampleRates();
			traits.modes = Encoder::ModeLossless;
			traits.formats.push_back({ Encoder::Format::Encoding::Float, 64, mpt::endian::little });
			traits.formats.push_back({ Encoder::Format::Encoding::Float, 32, mpt::endian::little });
			traits.formats.push_back({ Encoder::Format::Encoding::Integer, 32, mpt::endian::little });
			traits.formats.push_back({ Encoder::Format::Encoding::Integer, 24, mpt::endian::little });
			traits.formats.push_back({ Encoder::Format::Encoding::Integer, 16, mpt::endian::little });
			traits.formats.push_back({ Encoder::Format::Encoding::Unsigned, 8, mpt::endian::little });
			traits.defaultSamplerate = 48000;
			traits.defaultChannels = 2;
			traits.defaultMode = Encoder::ModeLossless;
			traits.defaultFormat = { Encoder::Format::Encoding::Float, 32, mpt::endian::little };
			SetTraits(traits);
				}
				
				
				bool WAVEncoder::IsAvailable() const
				{
			return true;
				}
				
				
				std::unique_ptr<IAudioStreamEncoder> WAVEncoder::ConstructStreamEncoder(std::ostream &file, const Encoder::Settings &settings, const FileTags &tags) const
				{
			if(!IsAvailable())
			{
		return nullptr;
			}
			return std::make_unique<WavStreamWriter>(*this, file, settings, tags);
				}
				
				
				OPENMPT_NAMESPACE_END
				