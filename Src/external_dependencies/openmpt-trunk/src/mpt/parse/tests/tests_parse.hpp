	/* SPDX-License-Identifier: BSL-1.0 OR BSD-3-Clause */
	
	#ifndef MPT_PARSE_TESTS_PARSE_HPP
	#define MPT_PARSE_TESTS_PARSE_HPP
	
	
	
	#include "mpt/base/detect.hpp"
	#include "mpt/base/integer.hpp"
	#include "mpt/base/namespace.hpp"
	#include "mpt/format/simple.hpp"
	#include "mpt/parse/parse.hpp"
	#include "mpt/string/types.hpp"
	#include "mpt/test/test.hpp"
	#include "mpt/test/test_macros.hpp"
	
	#include <limits>
	
	
	
	namespace mpt {
	inline namespace MPT_INLINE_NS {
	
	
	
	namespace tests {
	namespace parse {
	
	#if MPT_COMPILER_CLANG
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wglobal-constructors"
	#endif
	MPT_TEST_GROUP_INLINE("mpt/parse")
	#if MPT_COMPILER_CLANG
	#pragma clang diagnostic pop
	#endif
	{
MPT_TEST_EXPECT_EQUAL(mpt::ConvertStringTo<uint32>("586"), 586u);
MPT_TEST_EXPECT_EQUAL(mpt::ConvertStringTo<uint32>("2147483647"), (uint32)std::numeric_limits<int32>::max());
MPT_TEST_EXPECT_EQUAL(mpt::ConvertStringTo<uint32>("4294967295"), std::numeric_limits<uint32>::max());
	
MPT_TEST_EXPECT_EQUAL(mpt::ConvertStringTo<int64>("-9223372036854775808"), std::numeric_limits<int64>::min());
MPT_TEST_EXPECT_EQUAL(mpt::ConvertStringTo<int64>("-159"), -159);
MPT_TEST_EXPECT_EQUAL(mpt::ConvertStringTo<int64>("9223372036854775807"), std::numeric_limits<int64>::max());
	
MPT_TEST_EXPECT_EQUAL(mpt::ConvertStringTo<uint64>("85059"), 85059u);
MPT_TEST_EXPECT_EQUAL(mpt::ConvertStringTo<uint64>("9223372036854775807"), (uint64)std::numeric_limits<int64>::max());
MPT_TEST_EXPECT_EQUAL(mpt::ConvertStringTo<uint64>("18446744073709551615"), std::numeric_limits<uint64>::max());
	
MPT_TEST_EXPECT_EQUAL(mpt::ConvertStringTo<float>("-87.0"), -87.0f);
	#if !MPT_OS_DJGPP
MPT_TEST_EXPECT_EQUAL(mpt::ConvertStringTo<double>("-0.5e-6"), -0.5e-6);
	#endif
	#if !MPT_OS_DJGPP
MPT_TEST_EXPECT_EQUAL(mpt::ConvertStringTo<double>("58.65403492763"), 58.65403492763);
	#else
MPT_TEST_EXPECT_EQUAL(std::abs(mpt::ConvertStringTo<double>("58.65403492763") - 58.65403492763) <= 0.0001, true);
	#endif
	
MPT_TEST_EXPECT_EQUAL(mpt::ConvertStringTo<float>(mpt::format<std::string>::val(-87.0)), -87.0f);
	#if !MPT_OS_DJGPP
MPT_TEST_EXPECT_EQUAL(mpt::ConvertStringTo<double>(mpt::format<std::string>::val(-0.5e-6)), -0.5e-6);
	#endif
	
MPT_TEST_EXPECT_EQUAL(mpt::ConvertHexStringTo<unsigned char>("fe"), 254);
	#if !defined(MPT_COMPILER_QUIRK_NO_WCHAR)
MPT_TEST_EXPECT_EQUAL(mpt::ConvertHexStringTo<unsigned char>(L"fe"), 254);
	#endif // !MPT_COMPILER_QUIRK_NO_WCHAR
MPT_TEST_EXPECT_EQUAL(mpt::ConvertHexStringTo<unsigned int>(MPT_USTRING("ffff")), 65535u);
	}
	
	} // namespace parse
	} // namespace tests
	
	
	
	} // namespace MPT_INLINE_NS
	} // namespace mpt
	
	
	
	#endif // MPT_PARSE_TESTS_PARSE_HPP
	