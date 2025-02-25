	/*
    * mptRandom.cpp
    * -------------
    * Purpose: PRNG
    * Notes  : (currently none)
    * Authors: OpenMPT Devs
    * The OpenMPT source code is released under the BSD license. Read LICENSE for more details.
    */
	
	#include "stdafx.h"
	
	#include "mptRandom.h"
	
	OPENMPT_NAMESPACE_BEGIN
	
	namespace mpt
	{
	
	#if defined(MODPLUG_TRACKER) && !defined(MPT_BUILD_WINESUPPORT)
	
	static mpt::random_device *g_rd = nullptr;
	static mpt::thread_safe_prng<mpt::default_prng> *g_global_prng = nullptr;
	
	void set_global_random_device(mpt::random_device *rd)
	{
g_rd = rd;
	}
	
	void set_global_prng(mpt::thread_safe_prng<mpt::default_prng> *prng)
	{
g_global_prng = prng;
	}
	
	mpt::random_device & global_random_device()
	{
return *g_rd;
	}
	
	mpt::thread_safe_prng<mpt::default_prng> & global_prng()
	{
return *g_global_prng;
	}
	
	#else
	
	mpt::random_device & global_random_device()
	{
static mpt::random_device g_rd;
return g_rd;
	}
	
	mpt::thread_safe_prng<mpt::default_prng> & global_prng()
	{
static mpt::thread_safe_prng<mpt::default_prng> g_global_prng(mpt::make_prng<mpt::default_prng>(global_random_device()));
return g_global_prng;
	}
	
	#endif // MODPLUG_TRACKER && !MPT_BUILD_WINESUPPORT
	
	} // namespace mpt
	
	OPENMPT_NAMESPACE_END
	