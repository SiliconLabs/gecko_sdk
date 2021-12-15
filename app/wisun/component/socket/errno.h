/***************************************************************************//**
 * @file
 * @brief Errno implementation
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef _ERRNO_H_
#define _ERRNO_H_
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @defgroup SL_WISUN_SOCKET_ERRNO Errno
 * @ingroup SL_WISUN_SOCKET
 * @{
 *****************************************************************************/

/**************************************************************************//**
 * @brief Public get errno value
 *****************************************************************************/
#define errno (__get_errno())

/**************************************************************************//**
 * @defgroup SL_WISUN_SOCKET_ERRNO_TYPES Errno type definitions
 * @ingroup SL_WISUN_SOCKET_ERRNO
 * @{
 *****************************************************************************/
/**************************************************************************//**
 * @brief Errno type implementation (POSIX)
 *****************************************************************************/
typedef enum {
  /// ENOERROR (not standard errno value)
  ENOERROR = 0,
  /// Argument list too long (POSIX.1-2001).
  E2BIG,
  /// Permission denied (POSIX.1-2001).
  EACCES,
  /// Address already in use (POSIX.1-2001).
  EADDRINUSE,
  /// Address not available (POSIX.1-2001).
  EADDRNOTAVAIL,
  /// Address family not supported (POSIX.1-2001).
  EAFNOSUPPORT,
  /// Resource temporarily unavailable
  EAGAIN,
  /// Connection already in progress (POSIX.1-2001).
  EALREADY,
  /// Invalid exchange.
  EBADE,
  /// Bad file descriptor (POSIX.1-2001).
  EBADF,
  /// File descriptor in bad state.
  EBADFD,
  /// Bad message (POSIX.1-2001).
  EBADMSG,
  /// Invalid request descriptor.
  EBADR,
  /// Invalid request code.
  EBADRQC,
  /// Invalid slot.
  EBADSLT,
  /// Device or resource busy (POSIX.1-2001).
  EBUSY,
  /// Operation canceled (POSIX.1-2001).
  ECANCELED,
  /// No child processes (POSIX.1-2001).
  ECHILD,
  /// Channel number out of range.
  ECHRNG,
  /// Communication error on send.
  ECOMM,
  /// Connection aborted (POSIX.1-2001).
  ECONNABORTED,
  /// Connection refused (POSIX.1-2001).
  ECONNREFUSED,
  /// Connection reset (POSIX.1-2001).
  ECONNRESET,
  /// Resource deadlock avoided (POSIX.1-2001).
  EDEADLK,
  /// On most architectures, a synonym for EDEADLK.
  EDEADLOCK,
  /// Destination address required (POSIX.1-2001).
  EDESTADDRREQ,
  /// Mathematics argument out of domain of function
  EDOM,
  /// Disk quota exceeded (POSIX.1-2001).
  EDQUOT,
  /// File exists (POSIX.1-2001).
  EEXIST,
  /// Bad address (POSIX.1-2001).
  EFAULT,
  /// File too large (POSIX.1-2001).
  EFBIG,
  /// Host is down.
  EHOSTDOWN,
  /// Host is unreachable (POSIX.1-2001).
  EHOSTUNREACH,
  /// Memory page has hardware error.
  EHWPOISON,
  /// Identifier removed (POSIX.1-2001).
  EIDRM,
  /// Invalid or incomplete multibyte or wide character
  EILSEQ,
  /// Operation in progress (POSIX.1-2001).
  EINPROGRESS,
  /// Interrupted function call (POSIX.1-2001); see signal(7).
  EINTR,
  /// Invalid argument (POSIX.1-2001).
  EINVAL,
  /// Input/output error (POSIX.1-2001).
  EIO,
  /// Socket is connected (POSIX.1-2001).
  EISCONN,
  /// Is a directory (POSIX.1-2001).
  EISDIR,
  /// Is a named type file.
  EISNAM,
  /// Key has expired.
  EKEYEXPIRED,
  /// Key was rejected by service.
  EKEYREJECTED,
  /// Key has been revoked.
  EKEYREVOKED,
  /// Level 2 halted.
  EL2HLT,
  /// Level 2 not synchronized.
  EL2NSYNC,
  /// Level 3 halted.
  EL3HLT,
  /// Level 3 reset.
  EL3RST,
  /// Cannot access a needed shared library.
  ELIBACC,
  /// Accessing a corrupted shared library.
  ELIBBAD,
  /// Attempting to link in too many shared libraries.
  ELIBMAX,
  /// .lib section in a.out corrupted
  ELIBSCN,
  /// Cannot exec a shared library directly.
  ELIBEXEC,
  /// Link number out of range.
  ELNRANGE,
  /// Too many levels of symbolic links (POSIX.1-2001).
  ELOOP,
  /// Wrong medium type.
  EMEDIUMTYPE,
  /// Too many open files (POSIX.1-2001).
  EMFILE,
  /// Too many links (POSIX.1-2001).
  EMLINK,
  /// Message too long (POSIX.1-2001).
  EMSGSIZE,
  /// Multihop attempted (POSIX.1-2001).
  EMULTIHOP,
  /// Filename too long (POSIX.1-2001).
  ENAMETOOLONG,
  /// Network is down (POSIX.1-2001).
  ENETDOWN,
  /// Connection aborted by network (POSIX.1-2001).
  ENETRESET,
  /// Network unreachable (POSIX.1-2001).
  ENETUNREACH,
  /// Too many open files in system (POSIX.1-2001).
  ENFILE,
  /// No anode.
  ENOANO,
  /// No buffer space available (POSIX.1 (XSI STREAMS option)).
  ENOBUFS,
  /// No message is available on the STREAM head read queue
  ENODATA,
  /// No such device (POSIX.1-2001).
  ENODEV,
  /// No such file or directory (POSIX.1-2001).
  ENOENT,
  /// Exec format error (POSIX.1-2001).
  ENOEXEC,
  /// Required key not available.
  ENOKEY,
  /// No locks available (POSIX.1-2001).
  ENOLCK,
  /// Link has been severed (POSIX.1-2001).
  ENOLINK,
  /// No medium found.
  ENOMEDIUM,
  /// Not enough space/cannot allocate memory (POSIX.1-2001).
  ENOMEM,
  /// No message of the desired type (POSIX.1-2001).
  ENOMSG,
  /// Machine is not on the network.
  ENONET,
  /// Package not installed.
  ENOPKG,
  /// Protocol not available (POSIX.1-2001).
  ENOPROTOOPT,
  /// No space left on device (POSIX.1-2001).
  ENOSPC,
  /// No STREAM resources (POSIX.1 (XSI STREAMS option)).
  ENOSR,
  /// Not a STREAM (POSIX.1 (XSI STREAMS option)).
  ENOSTR,
  /// Function not implemented (POSIX.1-2001).
  ENOSYS,
  /// Block device required.
  ENOTBLK,
  /// The socket is not connected (POSIX.1-2001).
  ENOTCONN,
  /// Not a directory (POSIX.1-2001).
  ENOTDIR,
  /// Directory not empty (POSIX.1-2001).
  ENOTEMPTY,
  /// State not recoverable (POSIX.1-2008).
  ENOTRECOVERABLE,
  /// Not a socket (POSIX.1-2001).
  ENOTSOCK,
  /// Operation not supported (POSIX.1-2001).
  ENOTSUP,
  /// Inappropriate I/O control operation (POSIX.1-2001).
  ENOTTY,
  /// Name not unique on network.
  ENOTUNIQ,
  /// No such device or address (POSIX.1-2001).
  ENXIO,
  /// Operation not supported on socket (POSIX.1-2001).
  EOPNOTSUPP,
  /// Value too large to be stored in data type (POSIX.1-2001).
  EOVERFLOW,
  /// Owner died (POSIX.1-2008).
  EOWNERDEAD,
  /// Operation not permitted (POSIX.1-2001).
  EPERM,
  /// Protocol family not supported.
  EPFNOSUPPORT,
  /// Broken pipe (POSIX.1-2001).
  EPIPE,
  /// Protocol error (POSIX.1-2001).
  EPROTO,
  /// Protocol not supported (POSIX.1-2001).
  EPROTONOSUPPORT,
  /// Protocol wrong type for socket (POSIX.1-2001).
  EPROTOTYPE,
  /// Result too large (POSIX.1, C99).
  ERANGE,
  /// Remote address changed.
  EREMCHG,
  /// Object is remote.
  EREMOTE,
  /// Remote I/O error.
  EREMOTEIO,
  /// Interrupted system call should be restarted.
  ERESTART,
  /// Operation not possible due to RF-kill.
  ERFKILL,
  /// Read-only file system (POSIX.1-2001).
  EROFS,
  /// Cannot send after transport endpoint shutdown.
  ESHUTDOWN,
  /// Invalid seek (POSIX.1-2001).
  ESPIPE,
  /// Socket type not supported.
  ESOCKTNOSUPPORT,
  /// No such process (POSIX.1-2001).
  ESRCH,
  /// Stale file handle (POSIX.1-2001).
  ESTALE,
  /// Streams pipe error.
  ESTRPIPE,
  /// Timer expired (POSIX.1 (XSI STREAMS option)).
  ETIME,
  /// Connection timed out (POSIX.1-2001).
  ETIMEDOUT,
  /// Too many references: cannot splice.
  ETOOMANYREFS,
  /// Text file busy (POSIX.1-2001).
  ETXTBSY,
  /// Structure needs cleaning.
  EUCLEAN,
  /// Protocol driver not attached.
  EUNATCH,
  /// Too many users.
  EUSERS,
  /// Operation would block (may be same value as EAGAIN)
  EWOULDBLOCK,
  /// Improper link (POSIX.1-2001).
  EXDEV,
  /// Exchange full.
  EXFULL
} errno_t;
/** @} (end SL_WISUN_SOCKET_ERRNO_TYPES) */
// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Init errno
 * @details For internal usage in socket modules
 *****************************************************************************/
void __init_errno(void);

/**************************************************************************//**
 * @brief Get errno number
 * @details Thread safe get errno. For internal usage in socket modules
 * @return errno current value
 *****************************************************************************/
errno_t __get_errno(void);

/**************************************************************************//**
 * @brief Set errno
 * @details For internal usage in socket modules
 * @param[in] errcode errno value to set
 *****************************************************************************/
void __set_errno(const errno_t errcode);

/** @}*/

#ifdef __cplusplus
}
#endif
#endif /*EOF*/
