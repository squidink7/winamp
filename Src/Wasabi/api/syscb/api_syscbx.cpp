// ----------------------------------------------------------------------------
// Generated by InterfaceFactory [Wed May 07 00:58:14 2003]
// 
// File        : api_syscbx.cpp
// Class       : api_syscb
// class layer : Dispatchable Receiver
// ----------------------------------------------------------------------------
#include <precomp.h>

#include "api_syscbx.h"

#ifdef CBCLASS
#undef CBCLASS
#endif

#define CBCLASS api_syscbX
START_DISPATCH;
CB(API_SYSCB_SYSCB_REGISTERCALLBACK, syscb_registerCallback);
CB(API_SYSCB_SYSCB_DEREGISTERCALLBACK, syscb_deregisterCallback);
CB(API_SYSCB_SYSCB_ISSUECALLBACK, syscb_issueCallback);
END_DISPATCH;
#undef CBCLASS
