					/* SPDX-License-Identifier: BSL-1.0 OR BSD-3-Clause */
					
					#ifndef MPT_IO_READ_FILEREADER_HPP
					#define MPT_IO_READ_FILEREADER_HPP
					
					
					
					#include "mpt/base/alloc.hpp"
					#include "mpt/base/bit.hpp"
					#include "mpt/base/integer.hpp"
					#include "mpt/base/memory.hpp"
					#include "mpt/base/namespace.hpp"
					#include "mpt/base/span.hpp"
					#include "mpt/base/utility.hpp"
					#include "mpt/io/base.hpp"
					#include "mpt/endian/floatingpoint.hpp"
					#include "mpt/endian/integer.hpp"
					#include "mpt/string/utility.hpp"
					
					#include <algorithm>
					#include <array>
					#include <limits>
					#include <string>
					#include <vector>
					
					#include <cassert>
					#include <cstddef>
					#include <cstring>
					
					
					
					namespace mpt {
					inline namespace MPT_INLINE_NS {
					
					
					
					namespace IO {
					
					
					
					namespace FileReader {
					
					// Read a "T" object from the stream.
					// If not enough bytes can be read, false is returned.
					// If successful, the file cursor is advanced by the size of "T".
					template <typename T, typename TFileCursor>
					bool Read(TFileCursor & f, T & target) {
				// cppcheck false-positive
				// cppcheck-suppress uninitvar
				mpt::byte_span dst = mpt::as_raw_memory(target);
				if (dst.size() != f.GetRaw(dst).size()) {
			return false;
				}
				f.Skip(dst.size());
				return true;
					}
					
					// Read an array of binary-safe T values.
					// If successful, the file cursor is advanced by the size of the array.
					// Otherwise, the target is zeroed.
					template <typename T, std::size_t destSize, typename TFileCursor>
					bool ReadArray(TFileCursor & f, T (&destArray)[destSize]) {
				static_assert(mpt::is_binary_safe<T>::value);
				if (!f.CanRead(sizeof(destArray))) {
			mpt::reset(destArray);
			return false;
				}
				f.ReadRaw(mpt::as_raw_memory(destArray));
				return true;
					}
					
					// Read an array of binary-safe T values.
					// If successful, the file cursor is advanced by the size of the array.
					// Otherwise, the target is zeroed.
					template <typename T, std::size_t destSize, typename TFileCursor>
					bool ReadArray(TFileCursor & f, std::array<T, destSize> & destArray) {
				static_assert(mpt::is_binary_safe<T>::value);
				if (!f.CanRead(sizeof(destArray))) {
			destArray.fill(T{});
			return false;
				}
				f.ReadRaw(mpt::as_raw_memory(destArray));
				return true;
					}
					
					// Read destSize elements of binary-safe type T into a vector.
					// If successful, the file cursor is advanced by the size of the vector.
					// Otherwise, the vector is resized to destSize, but possibly existing contents are not cleared.
					template <typename T, typename TFileCursor>
					bool ReadVector(TFileCursor & f, std::vector<T> & destVector, size_t destSize) {
				static_assert(mpt::is_binary_safe<T>::value);
				destVector.resize(destSize);
				if (!f.CanRead(sizeof(T) * destSize)) {
			return false;
				}
				f.ReadRaw(mpt::as_raw_memory(destVector));
				return true;
					}
					
					template <typename T, std::size_t destSize, typename TFileCursor>
					std::array<T, destSize> ReadArray(TFileCursor & f) {
				std::array<T, destSize> destArray;
				ReadArray(f, destArray);
				return destArray;
					}
					
					// Read some kind of integer in little-endian format.
					// If successful, the file cursor is advanced by the size of the integer.
					template <typename T, typename TFileCursor>
					T ReadIntLE(TFileCursor & f) {
				static_assert(std::numeric_limits<T>::is_integer == true, "Target type is a not an integer");
				typename mpt::make_le<T>::type target;
				if (!FileReader::Read(f, target)) {
			return 0;
				}
				return target;
					}
					
					// Read some kind of integer in big-endian format.
					// If successful, the file cursor is advanced by the size of the integer.
					template <typename T, typename TFileCursor>
					T ReadIntBE(TFileCursor & f) {
				static_assert(std::numeric_limits<T>::is_integer == true, "Target type is a not an integer");
				typename mpt::make_be<T>::type target;
				if (!FileReader::Read(f, target)) {
			return 0;
				}
				return target;
					}
					
					// Read a integer in little-endian format which has some of its higher bytes not stored in file.
					// If successful, the file cursor is advanced by the given size.
					template <typename T, typename TFileCursor>
					T ReadTruncatedIntLE(TFileCursor & f, typename TFileCursor::pos_type size) {
				static_assert(std::numeric_limits<T>::is_integer == true, "Target type is a not an integer");
				assert(sizeof(T) >= size);
				if (size == 0) {
			return 0;
				}
				if (!f.CanRead(size)) {
			return 0;
				}
				uint8 buf[sizeof(T)];
				bool negative = false;
				for (std::size_t i = 0; i < sizeof(T); ++i) {
			uint8 byte = 0;
			if (i < size) {
		FileReader::Read(f, byte);
		negative = std::numeric_limits<T>::is_signed && ((byte & 0x80) != 0x00);
			} else {
		// sign or zero extend
		byte = negative ? 0xff : 0x00;
			}
			buf[i] = byte;
				}
				return mpt::bit_cast<typename mpt::make_le<T>::type>(buf);
					}
					
					// Read a supplied-size little endian integer to a fixed size variable.
					// The data is properly sign-extended when fewer bytes are stored.
					// If more bytes are stored, higher order bytes are silently ignored.
					// If successful, the file cursor is advanced by the given size.
					template <typename T, typename TFileCursor>
					T ReadSizedIntLE(TFileCursor & f, typename TFileCursor::pos_type size) {
				static_assert(std::numeric_limits<T>::is_integer == true, "Target type is a not an integer");
				if (size == 0) {
			return 0;
				}
				if (!f.CanRead(size)) {
			return 0;
				}
				if (size < sizeof(T)) {
			return FileReader::ReadTruncatedIntLE<T>(f, size);
				}
				T retval = FileReader::ReadIntLE<T>(f);
				f.Skip(size - sizeof(T));
				return retval;
					}
					
					// Read unsigned 32-Bit integer in little-endian format.
					// If successful, the file cursor is advanced by the size of the integer.
					template <typename TFileCursor>
					uint32 ReadUint32LE(TFileCursor & f) {
				return FileReader::ReadIntLE<uint32>(f);
					}
					
					// Read unsigned 32-Bit integer in big-endian format.
					// If successful, the file cursor is advanced by the size of the integer.
					template <typename TFileCursor>
					uint32 ReadUint32BE(TFileCursor & f) {
				return FileReader::ReadIntBE<uint32>(f);
					}
					
					// Read signed 32-Bit integer in little-endian format.
					// If successful, the file cursor is advanced by the size of the integer.
					template <typename TFileCursor>
					int32 ReadInt32LE(TFileCursor & f) {
				return FileReader::ReadIntLE<int32>(f);
					}
					
					// Read signed 32-Bit integer in big-endian format.
					// If successful, the file cursor is advanced by the size of the integer.
					template <typename TFileCursor>
					int32 ReadInt32BE(TFileCursor & f) {
				return FileReader::ReadIntBE<int32>(f);
					}
					
					// Read unsigned 24-Bit integer in little-endian format.
					// If successful, the file cursor is advanced by the size of the integer.
					template <typename TFileCursor>
					uint32 ReadUint24LE(TFileCursor & f) {
				const auto arr = FileReader::ReadArray<uint8, 3>(f);
				return arr[0] | (arr[1] << 8) | (arr[2] << 16);
					}
					
					// Read unsigned 24-Bit integer in big-endian format.
					// If successful, the file cursor is advanced by the size of the integer.
					template <typename TFileCursor>
					uint32 ReadUint24BE(TFileCursor & f) {
				const auto arr = FileReader::ReadArray<uint8, 3>(f);
				return (arr[0] << 16) | (arr[1] << 8) | arr[2];
					}
					
					// Read unsigned 16-Bit integer in little-endian format.
					// If successful, the file cursor is advanced by the size of the integer.
					template <typename TFileCursor>
					uint16 ReadUint16LE(TFileCursor & f) {
				return FileReader::ReadIntLE<uint16>(f);
					}
					
					// Read unsigned 16-Bit integer in big-endian format.
					// If successful, the file cursor is advanced by the size of the integer.
					template <typename TFileCursor>
					uint16 ReadUint16BE(TFileCursor & f) {
				return FileReader::ReadIntBE<uint16>(f);
					}
					
					// Read signed 16-Bit integer in little-endian format.
					// If successful, the file cursor is advanced by the size of the integer.
					template <typename TFileCursor>
					int16 ReadInt16LE(TFileCursor & f) {
				return FileReader::ReadIntLE<int16>(f);
					}
					
					// Read signed 16-Bit integer in big-endian format.
					// If successful, the file cursor is advanced by the size of the integer.
					template <typename TFileCursor>
					int16 ReadInt16BE(TFileCursor & f) {
				return FileReader::ReadIntBE<int16>(f);
					}
					
					// Read a single 8bit character.
					// If successful, the file cursor is advanced by the size of the integer.
					template <typename TFileCursor>
					char ReadChar(TFileCursor & f) {
				char target;
				if (!FileReader::Read(f, target)) {
			return 0;
				}
				return target;
					}
					
					// Read unsigned 8-Bit integer.
					// If successful, the file cursor is advanced by the size of the integer.
					template <typename TFileCursor>
					uint8 ReadUint8(TFileCursor & f) {
				uint8 target;
				if (!FileReader::Read(f, target)) {
			return 0;
				}
				return target;
					}
					
					// Read signed 8-Bit integer. If successful, the file cursor is advanced by the size of the integer.
					template <typename TFileCursor>
					int8 ReadInt8(TFileCursor & f) {
				int8 target;
				if (!FileReader::Read(f, target)) {
			return 0;
				}
				return target;
					}
					
					// Read 32-Bit float in little-endian format.
					// If successful, the file cursor is advanced by the size of the float.
					template <typename TFileCursor>
					float ReadFloatLE(TFileCursor & f) {
				IEEE754binary32LE target;
				if (!FileReader::Read(f, target)) {
			return 0.0f;
				}
				return target;
					}
					
					// Read 32-Bit float in big-endian format.
					// If successful, the file cursor is advanced by the size of the float.
					template <typename TFileCursor>
					float ReadFloatBE(TFileCursor & f) {
				IEEE754binary32BE target;
				if (!FileReader::Read(f, target)) {
			return 0.0f;
				}
				return target;
					}
					
					// Read 64-Bit float in little-endian format.
					// If successful, the file cursor is advanced by the size of the float.
					template <typename TFileCursor>
					double ReadDoubleLE(TFileCursor & f) {
				IEEE754binary64LE target;
				if (!FileReader::Read(f, target)) {
			return 0.0;
				}
				return target;
					}
					
					// Read 64-Bit float in big-endian format.
					// If successful, the file cursor is advanced by the size of the float.
					template <typename TFileCursor>
					double ReadDoubleBE(TFileCursor & f) {
				IEEE754binary64BE target;
				if (!FileReader::Read(f, target)) {
			return 0.0;
				}
				return target;
					}
					
					// Read a struct.
					// If successful, the file cursor is advanced by the size of the struct. Otherwise, the target is zeroed.
					template <typename T, typename TFileCursor>
					bool ReadStruct(TFileCursor & f, T & target) {
				static_assert(mpt::is_binary_safe<T>::value);
				if (!FileReader::Read(f, target)) {
			mpt::reset(target);
			return false;
				}
				return true;
					}
					
					// Allow to read a struct partially (if there's less memory available than the struct's size, fill it up with zeros).
					// The file cursor is advanced by "partialSize" bytes.
					template <typename T, typename TFileCursor>
					typename TFileCursor::pos_type ReadStructPartial(TFileCursor & f, T & target, typename TFileCursor::pos_type partialSize = sizeof(T)) {
				static_assert(mpt::is_binary_safe<T>::value);
				typename TFileCursor::pos_type copyBytes = std::min(partialSize, sizeof(T));
				if (!f.CanRead(copyBytes)) {
			copyBytes = f.BytesLeft();
				}
				f.GetRaw(mpt::span(mpt::as_raw_memory(target).data(), copyBytes));
				std::memset(mpt::as_raw_memory(target).data() + copyBytes, 0, sizeof(target) - copyBytes);
				f.Skip(partialSize);
				return copyBytes;
					}
					
					// Read a null-terminated string into a std::string
					template <typename TFileCursor>
					bool ReadNullString(TFileCursor & f, std::string & dest, const typename TFileCursor::pos_type maxLength = std::numeric_limits<typename TFileCursor::pos_type>::max()) {
				dest.clear();
				if (!f.CanRead(1)) {
			return false;
				}
				char buffer[mpt::IO::BUFFERSIZE_MINUSCULE];
				typename TFileCursor::pos_type avail = 0;
				while ((avail = std::min(f.GetRaw(mpt::as_span(buffer)).size(), maxLength - dest.length())) != 0) {
			auto end = std::find(buffer, buffer + avail, '\0');
			dest.insert(dest.end(), buffer, end);
			f.Skip(end - buffer);
			if (end < buffer + avail) {
		// Found null char
		f.Skip(1);
		break;
			}
				}
				return dest.length() != 0;
					}
					
					// Read a string up to the next line terminator into a std::string
					template <typename TFileCursor>
					bool ReadLine(TFileCursor & f, std::string & dest, const typename TFileCursor::pos_type maxLength = std::numeric_limits<typename TFileCursor::pos_type>::max()) {
				dest.clear();
				if (!f.CanRead(1)) {
			return false;
				}
				char buffer[mpt::IO::BUFFERSIZE_MINUSCULE];
				char c = '\0';
				typename TFileCursor::pos_type avail = 0;
				while ((avail = std::min(f.GetRaw(mpt::as_span(buffer)).size(), maxLength - dest.length())) != 0) {
			auto end = std::find_if(buffer, buffer + avail, mpt::is_any_line_ending<char>);
			dest.insert(dest.end(), buffer, end);
			f.Skip(end - buffer);
			if (end < buffer + avail) {
		// Found line ending
		f.Skip(1);
		// Handle CRLF line ending
		if (*end == '\r') {
	if (FileReader::Read(f, c) && c != '\n') {
f.SkipBack(1);
	}
		}
		break;
			}
				}
				return true;
					}
					
					// Compare a magic string with the current stream position.
					// Returns true if they are identical and advances the file cursor by the the length of the "magic" string.
					// Returns false if the string could not be found. The file cursor is not advanced in this case.
					template <size_t N, typename TFileCursor>
					bool ReadMagic(TFileCursor & f, const char (&magic)[N]) {
				assert(magic[N - 1] == '\0');
				for (std::size_t i = 0; i < N - 1; ++i) {
			assert(magic[i] != '\0');
				}
				constexpr typename TFileCursor::pos_type magicLength = N - 1;
				std::byte buffer[magicLength] = {};
				if (f.GetRaw(mpt::span(buffer, magicLength)).size() != magicLength) {
			return false;
				}
				if (std::memcmp(buffer, magic, magicLength)) {
			return false;
				}
				f.Skip(magicLength);
				return true;
					}
					
					// Read variable-length unsigned integer (as found in MIDI files).
					// If successful, the file cursor is advanced by the size of the integer and true is returned.
					// False is returned if not enough bytes were left to finish reading of the integer or if an overflow happened (source doesn't fit into target integer).
					// In case of an overflow, the target is also set to the maximum value supported by its data type.
					template <typename T, typename TFileCursor>
					bool ReadVarInt(TFileCursor & f, T & target) {
				static_assert(std::numeric_limits<T>::is_integer == true && std::numeric_limits<T>::is_signed == false, "Target type is not an unsigned integer");
					
				if (f.NoBytesLeft()) {
			target = 0;
			return false;
				}
					
				std::byte bytes[16]; // More than enough for any valid VarInt
				typename TFileCursor::pos_type avail = f.GetRaw(mpt::as_span(bytes)).size();
				typename TFileCursor::pos_type readPos = 1;
					
				uint8 b = mpt::byte_cast<uint8>(bytes[0]);
				target = (b & 0x7F);
				std::size_t writtenBits = static_cast<std::size_t>(mpt::bit_width(target)); // Bits used in the most significant byte
					
				while (readPos < avail && (b & 0x80) != 0) {
			b = mpt::byte_cast<uint8>(bytes[readPos++]);
			target <<= 7;
			target |= (b & 0x7F);
			writtenBits += 7;
			if (readPos == avail) {
		f.Skip(readPos);
		avail = f.GetRaw(mpt::as_span(bytes)).size();
		readPos = 0;
			}
				}
				f.Skip(readPos);
					
				if (writtenBits > sizeof(target) * 8u) {
			// Overflow
			target = std::numeric_limits<T>::max();
			return false;
				} else if ((b & 0x80) != 0) {
			// Reached EOF
			return false;
				}
				return true;
					}
					
					template <typename Tid, typename Tsize>
					struct ChunkHeader {
				using id_type = Tid;
				using size_type = Tsize;
				friend constexpr bool declare_binary_safe(const ChunkHeader &) noexcept {
			return true;
				}
				id_type id{};
				size_type size{};
				id_type GetID() const {
			return id;
				}
				size_type GetLength() const {
			return size;
				}
					};
					
					template <typename TChunkHeader, typename TFileCursor>
					struct Chunk {
				TChunkHeader header;
				TFileCursor data;
				TChunkHeader GetHeader() const {
			return header;
				}
				TFileCursor GetData() const {
			return data;
				}
					};
					
					template <typename TChunkHeader, typename TFileCursor>
					struct ChunkList {
					
				using id_type = decltype(TChunkHeader().GetID());
				using size_type = decltype(TChunkHeader().GetLength());
					
				std::vector<Chunk<TChunkHeader, TFileCursor>> chunks;
					
				// Check if the list contains a given chunk.
				bool ChunkExists(id_type id) const {
			return std::find_if(chunks.begin(), chunks.end(), [id](const Chunk<TChunkHeader, TFileCursor> & chunk) { return chunk.GetHeader().GetID() == id; }) != chunks.end();
				}
					
				// Retrieve the first chunk with a given ID.
				TFileCursor GetChunk(id_type id) const {
			auto chunk = std::find_if(chunks.begin(), chunks.end(), [id](const Chunk<TChunkHeader, TFileCursor> & chunk) { return chunk.GetHeader().GetID() == id; });
			if (chunk == chunks.end()) {
		return TFileCursor();
			}
			return chunk->GetData();
				}
					
				// Retrieve all chunks with a given ID.
				std::vector<TFileCursor> GetAllChunks(id_type id) const {
			std::vector<TFileCursor> result;
			for (const auto & chunk : chunks) {
		if (chunk.GetHeader().GetID() == id) {
	result.push_back(chunk.GetData());
		}
			}
			return result;
				}
					};
					
					// Read a single "TChunkHeader" chunk.
					// T is required to have the methods GetID() and GetLength().
					// GetLength() must return the chunk size in bytes, and GetID() the chunk ID.
					template <typename TChunkHeader, typename TFileCursor>
					Chunk<TChunkHeader, TFileCursor> ReadNextChunk(TFileCursor & f, typename TFileCursor::pos_type alignment) {
				Chunk<TChunkHeader, TFileCursor> result;
				if (!FileReader::Read(f, result.header)) {
			return Chunk<TChunkHeader, TFileCursor>();
				}
				typename TFileCursor::pos_type dataSize = result.header.GetLength();
				result.data = f.ReadChunk(dataSize);
				if (alignment > 1) {
			if ((dataSize % alignment) != 0) {
		f.Skip(alignment - (dataSize % alignment));
			}
				}
				return result;
					}
					
					// Read a series of "TChunkHeader" chunks until the end of file is reached.
					// T is required to have the methods GetID() and GetLength().
					// GetLength() must return the chunk size in bytes, and GetID() the chunk ID.
					template <typename TChunkHeader, typename TFileCursor>
					ChunkList<TChunkHeader, TFileCursor> ReadChunks(TFileCursor & f, typename TFileCursor::pos_type alignment) {
				ChunkList<TChunkHeader, TFileCursor> result;
				while (f.CanRead(sizeof(TChunkHeader))) {
			result.chunks.push_back(FileReader::ReadNextChunk<TChunkHeader, TFileCursor>(f, alignment));
				}
				return result;
					}
					
					// Read a series of "TChunkHeader" chunks until a given chunk ID is found.
					// T is required to have the methods GetID() and GetLength().
					// GetLength() must return the chunk size in bytes, and GetID() the chunk ID.
					template <typename TChunkHeader, typename TFileCursor>
					ChunkList<TChunkHeader, TFileCursor> ReadChunksUntil(TFileCursor & f, typename TFileCursor::pos_type alignment, decltype(TChunkHeader().GetID()) lastID) {
				ChunkList<TChunkHeader, TFileCursor> result;
				while (f.CanRead(sizeof(TChunkHeader))) {
			result.chunks.push_back(FileReader::ReadNextChunk<TChunkHeader, TFileCursor>(f, alignment));
			if (result.chunks.back().GetHeader().GetID() == lastID) {
		break;
			}
				}
				return result;
					}
					
					} // namespace FileReader
					
					
					
					} // namespace IO
					
					
					
					} // namespace MPT_INLINE_NS
					} // namespace mpt
					
					
					
					#endif // MPT_IO_READ_FILEREADER_HPP
					