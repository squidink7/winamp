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

#ifndef prerr_h___
#define prerr_h___

/*
*
* prerr.h
* This file is automatically generated; please do not edit it.
*/

/* Memory allocation attempt failed */
#define PR_OUT_OF_MEMORY_ERROR                   (-6000L)

/* Invalid file descriptor */
#define PR_BAD_DESCRIPTOR_ERROR                  (-5999L)

/* The operation would have blocked */
#define PR_WOULD_BLOCK_ERROR                     (-5998L)

/* Invalid memory address argument */
#define PR_ACCESS_FAULT_ERROR                    (-5997L)

/* Invalid function for file type */
#define PR_INVALID_METHOD_ERROR                  (-5996L)

/* Invalid memory address argument */
#define PR_ILLEGAL_ACCESS_ERROR                  (-5995L)

/* Some unknown error has occurred */
#define PR_UNKNOWN_ERROR                         (-5994L)

/* Operation interrupted by another thread */
#define PR_PENDING_INTERRUPT_ERROR               (-5993L)

/* function not implemented */
#define PR_NOT_IMPLEMENTED_ERROR                 (-5992L)

/* I/O function error */
#define PR_IO_ERROR                              (-5991L)

/* I/O operation timed out */
#define PR_IO_TIMEOUT_ERROR                      (-5990L)

/* I/O operation on busy file descriptor */
#define PR_IO_PENDING_ERROR                      (-5989L)

/* The directory could not be opened */
#define PR_DIRECTORY_OPEN_ERROR                  (-5988L)

/* Invalid function argument */
#define PR_INVALID_ARGUMENT_ERROR                (-5987L)

/* Network address not available (in use?) */
#define PR_ADDRESS_NOT_AVAILABLE_ERROR           (-5986L)

/* Network address type not supported */
#define PR_ADDRESS_NOT_SUPPORTED_ERROR           (-5985L)

/* Already connected */
#define PR_IS_CONNECTED_ERROR                    (-5984L)

/* Network address is invalid */
#define PR_BAD_ADDRESS_ERROR                     (-5983L)

/* Local Network address is in use */
#define PR_ADDRESS_IN_USE_ERROR                  (-5982L)

/* Connection refused by peer */
#define PR_CONNECT_REFUSED_ERROR                 (-5981L)

/* Network address is presently unreachable */
#define PR_NETWORK_UNREACHABLE_ERROR             (-5980L)

/* Connection attempt timed out */
#define PR_CONNECT_TIMEOUT_ERROR                 (-5979L)

/* Network file descriptor is not connected */
#define PR_NOT_CONNECTED_ERROR                   (-5978L)

/* Failure to load dynamic library */
#define PR_LOAD_LIBRARY_ERROR                    (-5977L)

/* Failure to unload dynamic library */
#define PR_UNLOAD_LIBRARY_ERROR                  (-5976L)

/* Symbol not found in any of the loaded dynamic libraries */
#define PR_FIND_SYMBOL_ERROR                     (-5975L)

/* Insufficient system resources */
#define PR_INSUFFICIENT_RESOURCES_ERROR          (-5974L)

/* A directory lookup on a network address has failed */
#define PR_DIRECTORY_LOOKUP_ERROR                (-5973L)

/* Attempt to access a TPD key that is out of range */
#define PR_TPD_RANGE_ERROR                       (-5972L)

/* Process open FD table is full */
#define PR_PROC_DESC_TABLE_FULL_ERROR            (-5971L)

/* System open FD table is full */
#define PR_SYS_DESC_TABLE_FULL_ERROR             (-5970L)

/* Network operation attempted on non-network file descriptor */
#define PR_NOT_SOCKET_ERROR                      (-5969L)

/* TCP-specific function attempted on a non-TCP file descriptor */
#define PR_NOT_TCP_SOCKET_ERROR                  (-5968L)

/* TCP file descriptor is already bound */
#define PR_SOCKET_ADDRESS_IS_BOUND_ERROR         (-5967L)

/* Access Denied */
#define PR_NO_ACCESS_RIGHTS_ERROR                (-5966L)

/* The requested operation is not supported by the platform */
#define PR_OPERATION_NOT_SUPPORTED_ERROR         (-5965L)

/* The host operating system does not support the protocol requested */
#define PR_PROTOCOL_NOT_SUPPORTED_ERROR          (-5964L)

/* Access to the remote file has been severed */
#define PR_REMOTE_FILE_ERROR                     (-5963L)

/* The value requested is too large to be stored in the data buffer provided */
#define PR_BUFFER_OVERFLOW_ERROR                 (-5962L)

/* TCP connection reset by peer */
#define PR_CONNECT_RESET_ERROR                   (-5961L)

/* Unused */
#define PR_RANGE_ERROR                           (-5960L)

/* The operation would have deadlocked */
#define PR_DEADLOCK_ERROR                        (-5959L)

/* The file is already locked */
#define PR_FILE_IS_LOCKED_ERROR                  (-5958L)

/* Write would result in file larger than the system allows */
#define PR_FILE_TOO_BIG_ERROR                    (-5957L)

/* The device for storing the file is full */
#define PR_NO_DEVICE_SPACE_ERROR                 (-5956L)

/* Unused */
#define PR_PIPE_ERROR                            (-5955L)

/* Unused */
#define PR_NO_SEEK_DEVICE_ERROR                  (-5954L)

/* Cannot perform a normal file operation on a directory */
#define PR_IS_DIRECTORY_ERROR                    (-5953L)

/* Symbolic link loop */
#define PR_LOOP_ERROR                            (-5952L)

/* File name is too long */
#define PR_NAME_TOO_LONG_ERROR                   (-5951L)

/* File not found */
#define PR_FILE_NOT_FOUND_ERROR                  (-5950L)

/* Cannot perform directory operation on a normal file */
#define PR_NOT_DIRECTORY_ERROR                   (-5949L)

/* Cannot write to a read-only file system */
#define PR_READ_ONLY_FILESYSTEM_ERROR            (-5948L)

/* Cannot delete a directory that is not empty */
#define PR_DIRECTORY_NOT_EMPTY_ERROR             (-5947L)

/* Cannot delete or rename a file object while the file system is busy */
#define PR_FILESYSTEM_MOUNTED_ERROR              (-5946L)

/* Cannot rename a file to a file system on another device */
#define PR_NOT_SAME_DEVICE_ERROR                 (-5945L)

/* The directory object in the file system is corrupted */
#define PR_DIRECTORY_CORRUPTED_ERROR             (-5944L)

/* Cannot create or rename a filename that already exists */
#define PR_FILE_EXISTS_ERROR                     (-5943L)

/* Directory is full.  No additional filenames may be added */
#define PR_MAX_DIRECTORY_ENTRIES_ERROR           (-5942L)

/* The required device was in an invalid state */
#define PR_INVALID_DEVICE_STATE_ERROR            (-5941L)

/* The device is locked */
#define PR_DEVICE_IS_LOCKED_ERROR                (-5940L)

/* No more entries in the directory */
#define PR_NO_MORE_FILES_ERROR                   (-5939L)

/* Encountered end of file */
#define PR_END_OF_FILE_ERROR                     (-5938L)

/* Seek error */
#define PR_FILE_SEEK_ERROR                       (-5937L)

/* The file is busy */
#define PR_FILE_IS_BUSY_ERROR                    (-5936L)

/* The I/O operation was aborted */
#define PR_OPERATION_ABORTED_ERROR               (-5935L)

/* Operation is still in progress (probably a non-blocking connect) */
#define PR_IN_PROGRESS_ERROR                     (-5934L)

/* Operation has already been initiated (probably a non-blocking connect) */
#define PR_ALREADY_INITIATED_ERROR               (-5933L)

/* The wait group is empty */
#define PR_GROUP_EMPTY_ERROR                     (-5932L)

/* Object state improper for request */
#define PR_INVALID_STATE_ERROR                   (-5931L)

/* Network is down */
#define PR_NETWORK_DOWN_ERROR                    (-5930L)

/* Socket shutdown */
#define PR_SOCKET_SHUTDOWN_ERROR                 (-5929L)

/* Connection aborted */
#define PR_CONNECT_ABORTED_ERROR                 (-5928L)

/* Host is unreachable */
#define PR_HOST_UNREACHABLE_ERROR                (-5927L)

/* The library is not loaded */
#define PR_LIBRARY_NOT_LOADED_ERROR              (-5926L)

/* Placeholder for the end of the list */
#define PR_MAX_ERROR                             (-5925L)

extern void nspr_InitializePRErrorTable(void);
#define ERROR_TABLE_BASE_nspr (-6000L)

#endif /* prerr_h___ */
