			/* SPDX-License-Identifier: BSL-1.0 OR BSD-3-Clause */
			
			#ifndef MPT_IO_READ_FILEDATA_HPP
			#define MPT_IO_READ_FILEDATA_HPP
			
			
			
			#include "mpt/base/memory.hpp"
			#include "mpt/base/namespace.hpp"
			
			#include <algorithm>
			
			#include <cstddef>
			
			
			
			namespace mpt {
			inline namespace MPT_INLINE_NS {
			
			
			
			namespace IO {
			
			
			
			class IFileData {
			public:
		typedef std::size_t pos_type;
			
			protected:
		IFileData() = default;
			
			public:
		IFileData(const IFileData &) = default;
		IFileData & operator=(const IFileData &) = default;
		virtual ~IFileData() = default;
			
			public:
		virtual bool IsValid() const = 0;
		virtual bool HasFastGetLength() const = 0;
		virtual bool HasPinnedView() const = 0;
		virtual const std::byte * GetRawData() const = 0;
		virtual pos_type GetLength() const = 0;
		virtual mpt::byte_span Read(pos_type pos, mpt::byte_span dst) const = 0;
			
		virtual bool CanRead(pos_type pos, std::size_t length) const {
	pos_type dataLength = GetLength();
	if ((pos == dataLength) && (length == 0)) {
return true;
	}
	if (pos >= dataLength) {
return false;
	}
	return length <= dataLength - pos;
		}
			
		virtual std::size_t GetReadableLength(pos_type pos, std::size_t length) const {
	pos_type dataLength = GetLength();
	if (pos >= dataLength) {
return 0;
	}
	return std::min(length, dataLength - pos);
		}
			};
			
			
			
			} // namespace IO
			
			
			
			} // namespace MPT_INLINE_NS
			} // namespace mpt
			
			
			
			#endif // MPT_IO_READ_FILEDATA_HPP
			