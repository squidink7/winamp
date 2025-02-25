	/*
	** JNetLib
	** Copyright (C) 2000-2007 Nullsoft, Inc.
	** Author: Justin Frankel
	** File: util.h - JNL interface for basic network utilities
	** License: see jnetlib.h
	**
	** routines you may be interested in:
	**   JNL::open_socketlib();
	**    opens the socket library. Call this once before using any network
	**    code. If you create a new thread, call this again. Only really an
	**    issue for Win32 support, but use it anyway for portability/
	**
	**   JNL::close_Socketlib();
	**    closes the socketlib. Call this when you're done with the network,
	**    after all your JNetLib objects have been destroyed.
	**
	**   unsigned long JNL::ipstr_to_addr(const char *cp);
	**    gives you the integer representation of a ip address in dotted
	**    decimal form.
	**
	**  JNL::addr_to_ipstr(unsigned long addr, char *host, int maxhostlen);
	**    gives you the dotted decimal notation of an integer ip address.
	**
	*/
	
	#ifndef NULLSOFT_WAC_NETWORK_UTIL_H
	#define NULLSOFT_WAC_NETWORK_UTIL_H
	
	class JNL
	{
public:
static int           open_socketlib();
static void          close_socketlib();
	
static unsigned long ipstr_to_addr( const char *cp );
static void          addr_to_ipstr( unsigned long addr, char *host, int maxhostlen );
	
static int           parse_url( const char *url, char **prot, char **host, unsigned short *port, char **req, char **lp );
	};
	
	#endif //!NULLSOFT_WAC_NETWORK_UTIL_H
	