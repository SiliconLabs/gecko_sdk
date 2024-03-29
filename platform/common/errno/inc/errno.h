/***************************************************************************//**
 * @file errno.h
 * @brief errno standard header
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef ERRNO_H
#define ERRNO_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * @addtogroup errno Errno
 * @details Errno contains the definition for errno and the defines for
 * the errno values.
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * Macro for errno usage.
 * Can be used to retrieve errno value and to assign errno value since function
 * returns address of variable used to store errno value.
 ******************************************************************************/
#define errno (*sl_errno())

/***************************************************************************//**
 * Errno function used with macro errno.
 *
 * @return  Address of global variable used to store errno value
 ******************************************************************************/
int *sl_errno(void);

// -----------------------------------------------------------------------------
// Errno Define Values

#define EPERM           1   ///< Not owner
#define ENOENT          2   ///< No such file or directory
#define ESRCH           3   ///< No such process
#define EINTR           4   ///< Interrupted system call
#define EIO             5   ///< I/O error
#define ENXIO           6   ///< No such device or address
#define E2BIG           7   ///< Arguments list too long
#define ENOEXEC         8   ///< Exec format error
#define EBADF           9   ///< Bad file number
#define ECHILD          10  ///< No children
#define EAGAIN          11  ///< No more processes
#define ENOMEM          12  ///< Not enough space
#define EACCES          13  ///< Permission denied
#define EFAULT          14  ///< Bad address
#define ENOTBLK         15  ///< Block device required
#define EBUSY           16  ///< Device or resource busy
#define EEXIST          17  ///< File exists
#define EXDEV           18  ///< Cross-device link
#define ENODEV          19  ///< No such device
#define ENOTDIR         20  ///< Not a directory
#define EISDIR          21  ///< Is a directory
#define EINVAL          22  ///< Invalid argument
#define ENFILE          23  ///< Too many open files in system
#define EMFILE          24  ///< File descriptor value too large
#define ENOTTY          25  ///< Not a character device
#define ETXTBSY         26  ///< Text file busy
#define EFBIG           27  ///< File too large
#define ENOSPC          28  ///< No space left on device
#define ESPIPE          29  ///< Illegal seek
#define EROFS           30  ///< Read-only file system
#define EMLINK          31  ///< Too many links
#define EPIPE           32  ///< Broken pipe
#define EDOM            33  ///< Mathematics argument out of domain of function
#define ERANGE          34  ///< Result too large
#define ENOMSG          35  ///< No message of desired type
#define EIDRM           36  ///< Identifier removed

#define EDEADLK         45  ///< Deadlock
#define ENOLCK          46  ///< No lock

#define ENOSTR          60  ///< Not a stream
#define ENODATA         61  ///< No data (for no delay io)
#define ETIME           62  ///< Stream ioctl timeout
#define ENOSR           63  ///< No stream resources

#define ENOLINK         67  ///< Virtual circuit is gone

#define EPROTO          71  ///< Protocol error
#define EMULTIHOP       74  ///< Multihop attempted

#define EBADMSG         77  ///< Bad message
#define EFTYPE          79  ///< Inappropriate file type or format

#define ENOSYS          88  ///< Function not implemented

#define ENOTEMPTY       90  ///< Directory not empty
#define ENAMETOOLONG    91  ///< File or path name too long
#define ELOOP           92  ///< Too many symbolic links
#define EOPNOTSUPP      95  ///< Operation not supported on socket
#define EPFNOSUPPORT    96  ///< Protocol family not supported
#define ECONNRESET      104 ///< Connection reset by peer
#define ENOBUFS         105 ///< No buffer space available
#define EAFNOSUPPORT    106 ///< Address family not supported by protocol family
#define EPROTOTYPE      107 ///< Protocol wrong type for socket
#define ENOTSOCK        108 ///< Socket operation on non-socket
#define ENOPROTOOPT     109 ///< Protocol not available
#define ESHUTDOWN       110 ///< Can't send after socket shutdown
#define ECONNREFUSED    111 ///< Connection refused
#define EADDRINUSE      112 ///< Address already in use
#define ECONNABORTED    113 ///< Software caused connection abort
#define ENETUNREACH     114 ///< Network is unreachable
#define ENETDOWN        115 ///< Network interface is not configured
#define ETIMEDOUT       116 ///< Connection timed out
#define EHOSTDOWN       117 ///< Host is down
#define EHOSTUNREACH    118 ///< Host is unreachable
#define EINPROGRESS     119 ///< Connection already in progress
#define EALREADY        120 ///< Socket already connected
#define EDESTADDRREQ    121 ///< Destination address required
#define EMSGSIZE        122 ///< Message too long
#define EPROTONOSUPPORT 123 ///< Unknown protocol
#define ESOCKTNOSUPPORT 124 ///< Socket type not supported
#define EADDRNOTAVAIL   125 ///< Address not available
#define ENETRESET       126 ///< Connection aborted by network
#define EISCONN         127 ///< Socket is already connected
#define ENOTCONN        128 ///< Socket is not connected
#define ETOOMANYREFS    129 ///< Too many references: can't splice

#define ENOTSUP         134 ///< Not supported

#define EILSEQ          138 ///< Illegal byte sequence
#define EOVERFLOW       139 ///< Value too large for defined data type
#define ECANCELED       140 ///< Operation canceled
#define ENOTRECOVERABLE 141 ///< State not recoverable
#define EOWNERDEAD      142 ///< Previous owner died

#define EWOULDBLOCK     EAGAIN  ///< Operation would block

/** @} (end addtogroup errno) */

#ifdef __cplusplus
}
#endif

#endif // ERRNO_H
