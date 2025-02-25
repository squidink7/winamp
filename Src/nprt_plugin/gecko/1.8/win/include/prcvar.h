/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
* Version: MPL 1.1/GPL 2.0/LGPL 2.1
*
* The contents of this file are subject to the Mozilla Public License Version
* 1.1 (the "License"); you may not use this file except in compliance with
* the License. You may obtain a copy of the License at
* http://www.mozilla.org/MPL/
*
* Software distributed under the License is distributed on an "AS IS" basis,
* WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
* for the specific language governing rights and limitations under the
* License.
*
* The Original Code is the Netscape Portable Runtime (NSPR).
*
* The Initial Developer of the Original Code is
* Netscape Communications Corporation.
* Portions created by the Initial Developer are Copyright (C) 1998-2000
* the Initial Developer. All Rights Reserved.
*
* Contributor(s):
*
* Alternatively, the contents of this file may be used under the terms of
* either the GNU General Public License Version 2 or later (the "GPL"), or
* the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
* in which case the provisions of the GPL or the LGPL are applicable instead
* of those above. If you wish to allow use of your version of this file only
* under the terms of either the GPL or the LGPL, and not to allow others to
* use your version of this file under the terms of the MPL, indicate your
* decision by deleting the provisions above and replace them with the notice
* and other provisions required by the GPL or the LGPL. If you do not delete
* the provisions above, a recipient may use your version of this file under
* the terms of any one of the MPL, the GPL or the LGPL.
*
* ***** END LICENSE BLOCK ***** */

#ifndef prcvar_h___
#define prcvar_h___

#include "prlock.h"
#include "prinrval.h"

PR_BEGIN_EXTERN_C

typedef struct PRCondVar PRCondVar;

/*
** Create a new condition variable.
**
** 	"lock" is the lock used to protect the condition variable.
**
** Condition variables are synchronization objects that threads can use
** to wait for some condition to occur.
**
** This may fail if memory is tight or if some operating system resource
** is low. In such cases, a NULL will be returned.
*/
NSPR_API(PRCondVar*) PR_NewCondVar(PRLock *lock);

/*
** Destroy a condition variable. There must be no thread
** waiting on the condvar. The caller is responsible for guaranteeing
** that the condvar is no longer in use.
**
*/
NSPR_API(void) PR_DestroyCondVar(PRCondVar *cvar);

/*
** The thread that waits on a condition is blocked in a "waiting on
** condition" state until another thread notifies the condition or a
** caller specified amount of time expires. The lock associated with
** the condition variable will be released, which must have be held
** prior to the call to wait.
**
** Logically a notified thread is moved from the "waiting on condition"
** state and made "ready." When scheduled, it will attempt to reacquire
** the lock that it held when wait was called.
**
** The timeout has two well known values, PR_INTERVAL_NO_TIMEOUT and
** PR_INTERVAL_NO_WAIT. The former value requires that a condition be
** notified (or the thread interrupted) before it will resume from the
** wait. If the timeout has a value of PR_INTERVAL_NO_WAIT, the effect
** is to release the lock, possibly causing a rescheduling within the
** runtime, then immediately attempting to reacquire the lock and resume.
**
** Any other value for timeout will cause the thread to be rescheduled
** either due to explicit notification or an expired interval. The latter
** must be determined by treating time as one part of the monitored data
** being protected by the lock and tested explicitly for an expired
** interval.
**
** Returns PR_FAILURE if the caller has not locked the lock associated
** with the condition variable or the thread was interrupted (PR_Interrupt()).
** The particular reason can be extracted with PR_GetError().
*/
NSPR_API(PRStatus) PR_WaitCondVar(PRCondVar *cvar, PRIntervalTime timeout);

/*
** Notify ONE thread that is currently waiting on 'cvar'. Which thread is
** dependent on the implementation of the runtime. Common sense would dictate
** that all threads waiting on a single condition have identical semantics,
** therefore which one gets notified is not significant. 
**
** The calling thead must hold the lock that protects the condition, as
** well as the invariants that are tightly bound to the condition, when
** notify is called.
**
** Returns PR_FAILURE if the caller has not locked the lock associated
** with the condition variable.
*/
NSPR_API(PRStatus) PR_NotifyCondVar(PRCondVar *cvar);

/*
** Notify all of the threads waiting on the condition variable. The order
** that the threads are notified is indeterminant. The lock that protects
** the condition must be held.
**
** Returns PR_FAILURE if the caller has not locked the lock associated
** with the condition variable.
*/
NSPR_API(PRStatus) PR_NotifyAllCondVar(PRCondVar *cvar);

PR_END_EXTERN_C

#endif /* prcvar_h___ */
