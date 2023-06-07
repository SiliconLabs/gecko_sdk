/***************************************************************************//**
 * @file
 * @brief File Transfer Portocol Client header file
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __SL_FTP_CLIENT_H__
#define __SL_FTP_CLIENT_H__

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include <stdint.h>
#include <stddef.h>

#include "sl_status.h"
#include "sl_ftp.h"
#include "sl_ftp_config.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

#if SL_FTP_ENABLE_FTP_PROTOCOL
// Control Commands
///	Abort an active file transfer.
#define SL_FTP_CTRL_CMD_ABOR "ABOR"
///	Account information.
#define SL_FTP_CTRL_CMD_ACCT "ACCT"
///	RFC 2228	Authentication/Security Data
#define SL_FTP_CTRL_CMD_ADAT "ADAT"
///	Allocate sufficient disk space to receive a file.
#define SL_FTP_CTRL_CMD_ALLO "ALLO"
///	Append (with create)
#define SL_FTP_CTRL_CMD_APPE "APPE"
///	RFC 2228	Authentication/Security Mechanism
#define SL_FTP_CTRL_CMD_AUTH "AUTH"
///	Streamlined FTP Command Extensions	Get the available space
#define SL_FTP_CTRL_CMD_AVBL "AVBL"
///	RFC 2228	Clear Command Channel
#define SL_FTP_CTRL_CMD_CCC  "CCC"
///	Change to Parent Directory.
#define SL_FTP_CTRL_CMD_CDUP "CDUP"
///	RFC 2228	Confidentiality Protection Command
#define SL_FTP_CTRL_CMD_CONF "CONF"
///	Streamlined FTP Command Extensions	Client / Server Identification
#define SL_FTP_CTRL_CMD_CSID "CSID"
///	RFC 697	Change working directory.
#define SL_FTP_CTRL_CMD_CWD  "CWD"
///	Delete file.
#define SL_FTP_CTRL_CMD_DELE "DELE"
///	Streamlined FTP Command Extensions	Get the directory size
#define SL_FTP_CTRL_CMD_DSIZ "DSIZ"
///	RFC 2228	Privacy Protected Channel
#define SL_FTP_CTRL_CMD_ENC  "ENC"
///	RFC 2428	Specifies an extended address and port to which the server should connect.
#define SL_FTP_CTRL_CMD_EPRT "EPRT"
///	RFC 2428	Enter extended passive mode.
#define SL_FTP_CTRL_CMD_EPSV "EPSV"
///	RFC 2389	Get the feature list implemented by the server.
#define SL_FTP_CTRL_CMD_FEAT "FEAT"
///	Returns usage documentation on a command if specified, else a general help document is returned.
#define SL_FTP_CTRL_CMD_HELP "HELP"
///	RFC 7151	Identify desired virtual host on server, by name.
#define SL_FTP_CTRL_CMD_HOST "HOST"
///	RFC 2640	Language Negotiation
#define SL_FTP_CTRL_CMD_LANG "LANG"
///	Returns information of a file or directory if specified, else information of the current working directory is returned.
#define SL_FTP_CTRL_CMD_LIST "LIST"
///	RFC 1639	Specifies a long address and port to which the server should connect.
#define SL_FTP_CTRL_CMD_LPRT "LPRT"
///	RFC 1639	Enter long passive mode.
#define SL_FTP_CTRL_CMD_LPSV "LPSV"
///	RFC 3659	Return the last-modified time of a specified file.
#define SL_FTP_CTRL_CMD_MDTM "MDTM"
///	The 'MFMT', 'MFCT', and 'MFF' Command Extensions for FTP	Modify the creation time of a file.
#define SL_FTP_CTRL_CMD_MFCT "MFCT"
///	The 'MFMT', 'MFCT', and 'MFF' Command Extensions for FTP	Modify fact (the last modification time, creation time, UNIX group/owner/mode of a file).
#define SL_FTP_CTRL_CMD_MFF  "MFF"
///	The 'MFMT', 'MFCT', and 'MFF' Command Extensions for FTP	Modify the last modification time of a file.
#define SL_FTP_CTRL_CMD_MFMT "MFMT"
///	RFC 2228	Integrity Protected Command
#define SL_FTP_CTRL_CMD_MIC  "MIC"
///	Make directory.
#define SL_FTP_CTRL_CMD_MKD  "MKD"
///	RFC 3659	Lists the contents of a directory in a standardized machine-readable format.
#define SL_FTP_CTRL_CMD_MLSD "MLSD"
///	RFC 3659	Provides data about exactly the object named on its command line in a standardized machine-readable format.
#define SL_FTP_CTRL_CMD_MLST "MLST"
///	Sets the transfer mode (Stream, Block, or Compressed).
#define SL_FTP_CTRL_CMD_MODE "MODE"
///	Returns a list of file names in a specified directory.
#define SL_FTP_CTRL_CMD_NLST "NLST"
///	No operation (dummy packet; used mostly on keepalives).
#define SL_FTP_CTRL_CMD_NOOP "NOOP"
///	RFC 2389	Select options for a feature (for example OPTS UTF8 ON).
#define SL_FTP_CTRL_CMD_OPTS "OPTS"
///	Authentication password.
#define SL_FTP_CTRL_CMD_PASS "PASS"
///	Enter passive mode.
#define SL_FTP_CTRL_CMD_PASV "PASV"
///	RFC 2228	Protection Buffer Size
#define SL_FTP_CTRL_CMD_PBSZ "PBSZ"
///	Specifies an address and port to which the server should connect.
#define SL_FTP_CTRL_CMD_PORT "PORT"
///	RFC 2228	Data Channel Protection Level.
#define SL_FTP_CTRL_CMD_PROT "PROT"
///	Print working directory. Returns the current directory of the host.
#define SL_FTP_CTRL_CMD_PWD  "PWD"
///	Disconnect.
#define SL_FTP_CTRL_CMD_QUIT "QUIT"
///	Re initializes the connection.
#define SL_FTP_CTRL_CMD_REIN "REIN"
///	RFC 3659	Restart transfer from the specified point.
#define SL_FTP_CTRL_CMD_REST "REST"
///	Retrieve a copy of the file
#define SL_FTP_CTRL_CMD_RETR "RETR"
///	Remove a directory.
#define SL_FTP_CTRL_CMD_RMD  "RMD"
///	Streamlined FTP Command Extensions	Remove a directory tree
#define SL_FTP_CTRL_CMD_RMDA "RMDA"
///	Rename from.
#define SL_FTP_CTRL_CMD_RNFR "RNFR"
///	Rename to.
#define SL_FTP_CTRL_CMD_RNTO "RNTO"
///	Sends site specific commands to remote server (like SITE IDLE 60 or SITE UMASK 002). Inspect SITE HELP output for complete list of supported commands.
#define SL_FTP_CTRL_CMD_SITE "SITE"
///	RFC 3659	Return the size of a file.
#define SL_FTP_CTRL_CMD_SIZE "SIZE"
///	Mount file structure.
#define SL_FTP_CTRL_CMD_SMNT "SMNT"
///	FTP Extension Allowing IP Forwarding (NATs)	Use single port passive mode (only one TCP port number for both control connections and passive-mode data connections)
#define SL_FTP_CTRL_CMD_SPSV "SPSV"
///	Returns information on the server status, including the status of the current connection
#define SL_FTP_CTRL_CMD_STAT "STAT"
///	Accept the data and to store the data as a file at the server site
#define SL_FTP_CTRL_CMD_STOR "STOR"
///	Store file uniquely.
#define SL_FTP_CTRL_CMD_STOU "STOU"
///	Set file transfer structure.
#define SL_FTP_CTRL_CMD_STRU "STRU"
///	Return system type.
#define SL_FTP_CTRL_CMD_SYST "SYST"
///	Streamlined FTP Command Extensions	Get a thumbnail of a remote image file
#define SL_FTP_CTRL_CMD_THMB "THMB"
///	Sets the transfer mode (ASCII/Binary).
#define SL_FTP_CTRL_CMD_TYPE "TYPE"
///	Authentication username.
#define SL_FTP_CTRL_CMD_USER "USER"
///	RFC 775	Change to the parent of the current working directory
#define SL_FTP_CTRL_CMD_XCUP "XCUP"
///	RFC 775	Make a directory
#define SL_FTP_CTRL_CMD_XMKD "XMKD"
///	RFC 775	Print the current working directory
#define SL_FTP_CTRL_CMD_XPWD "XPWD"
///	RFC 743
#define SL_FTP_CTRL_CMD_XRCP "XRCP"
///	RFC 775	Remove the directory
#define SL_FTP_CTRL_CMD_XRMD "XRMD"
///	RFC 743
#define SL_FTP_CTRL_CMD_XRSQ "XRSQ"
///	RFC 737	Send, mail if cannot
#define SL_FTP_CTRL_CMD_XSEM "XSEM"
///	RFC 737	Send to terminal
#define SL_FTP_CTRL_CMD_XSEN "XSEN"

// Server Return Codes
// 100 Series: The requested action is being initiated, expect another reply before proceeding with a new command.
///	Restart marker replay . In this case, the text is exact and not left to the particular implementation; it must read: MARK yyyy = mmmm where yyyy is User-process data stream marker, and mmmm server's equivalent marker (note the spaces between markers and "=").
#define SL_FTP_SRV_RET_CODE_1XX_RMP         110U
///	Service ready in nnn minutes.
#define SL_FTP_SRV_RET_CODE_1XX_SREADY      120U
///	Data connection already open; transfer starting.
#define SL_FTP_SRV_RET_CODE_1XX_DATACON     125U
///	File status okay; about to open data connection.
#define SL_FTP_SRV_RET_CODE_1XX_FILESTAT    150U

// 200 Series: The requested action has been successfully completed.
#define SL_FTP_SRV_RET_CODE_2XX_REQACTOK    200U
///	Command not implemented, superfluous at this site.
#define SL_FTP_SRV_RET_CODE_2XX_CMDNOTIMP   202U
///	System status, or system help reply.
#define SL_FTP_SRV_RET_CODE_2XX_SYSSTAT     211U
///	Directory status.
#define SL_FTP_SRV_RET_CODE_2XX_DIRSTAT     212U
///	File status.
#define SL_FTP_SRV_RET_CODE_2XX_FILESTAT    213U
///	Help message. Explains how to use the server or the meaning of a particular non-standard command. This reply is useful only to the human user.
#define SL_FTP_SRV_RET_CODE_2XX_HELPMSG     214U
///	NAME system type. Where NAME is an official system name from the registry kept by IANA.
#define SL_FTP_SRV_RET_CODE_2XX_NAMESYST    215U
///	Service ready for new user.
#define SL_FTP_SRV_RET_CODE_2XX_SREADY      220U
///	Service closing control connection.
#define SL_FTP_SRV_RET_CODE_2XX_SCLOSE      221U
///	Data connection open; no transfer in progress.
#define SL_FTP_SRV_RET_CODE_2XX_DATACON     225U
///	Closing data connection. Requested file action successful (for example, file transfer or file abort).
#define SL_FTP_SRV_RET_CODE_2XX_CLOSEDATAC  226U
///	Entering Passive Mode (h1,h2,h3,h4,p1,p2).
#define SL_FTP_SRV_RET_CODE_2XX_PSVMODE     227U
///	Entering Long Passive Mode (long address, port).
#define SL_FTP_SRV_RET_CODE_2XX_LPSVMODE    228U
///	Entering Extended Passive Mode (|||port|).
#define SL_FTP_SRV_RET_CODE_2XX_EPSVMODE    229U
///	User logged in, proceed. Logged out if appropriate.
#define SL_FTP_SRV_RET_CODE_2XX_USRLOGI     230U
///	User logged out; service terminated.
#define SL_FTP_SRV_RET_CODE_2XX_USRLOGO     231U
///	Logout command noted, will complete when transfer done. Alternatively: User logged in, authorized by security data exchange.
#define SL_FTP_SRV_RET_CODE_2XX_LOGOCNOTE   232U
///	Specifies that the server accepts the authentication mechanism specified by the client, and no security data needs to be exchanged.
#define SL_FTP_SRV_RET_CODE_2XX_ACAUTH      234U
///	Specifies that the server accepts the security data given by the client, and no further security data needs to be exchanged.
#define SL_FTP_SRV_RET_CODE_2XX_ACSEC       235U
///	Requested file action okay, completed.
#define SL_FTP_SRV_RET_CODE_2XX_FILEACTOK   250U
///	"PATHNAME" created.
#define SL_FTP_SRV_RET_CODE_2XX_PNAMCREATE  257U

// 300 Series: The command has been accepted, but the requested action is on hold, pending receipt of further information.
///	User name okay, need password.
#define SL_FTP_SRV_RET_CODE_3XX_USRNAMEOK   331U
///	Need account for login.
#define SL_FTP_SRV_RET_CODE_3XX_NEEDACOUNT  332U
///	Specifies that the server accepts the authentication mechanism specified by the client, but some security data needs to be exchanged.
#define SL_FTP_SRV_RET_CODE_3XX_NEEDSECD    334U
///	Specifies that the server accepts the security data given by the client, but further security data needs to be exchanged.
#define SL_FTP_SRV_RET_CODE_3XX_NEEDSECDF   335U
///	Requested file action pending further information
#define SL_FTP_SRV_RET_CODE_3XX_PENDFINF    350U

// 400 Series: The command was not accepted and the requested action did not take place, but the error condition is temporary and the action may be requested again.
///	Service not available, closing control connection. This may be a reply to any command if the service knows it must shut down.
#define SL_FTP_SRV_RET_CODE_4XX_SERVNOTAV   421U
///	Can't open data connection.
#define SL_FTP_SRV_RET_CODE_4XX_NODCON      425U
///	Connection closed; transfer aborted.
#define SL_FTP_SRV_RET_CODE_4XX_CONCLOSED   426U
///	Invalid username or password
#define SL_FTP_SRV_RET_CODE_4XX_INVUSRPWD   430U
///	Requested host unavailable.
#define SL_FTP_SRV_RET_CODE_4XX_HOSTUNAV    434U
///	Requested file action not taken.
#define SL_FTP_SRV_RET_CODE_4XX_REQFILNOT   450U
///	Requested action aborted. Local error in processing.
#define SL_FTP_SRV_RET_CODE_4XX_REQACABORT  451U
///	Requested action not taken. Insufficient storage space in system. File unavailable (e.g., file busy).
#define SL_FTP_SRV_RET_CODE_4XX_REQACTNOT   452U

// 500 Series: Syntax error, command unrecognized and the requested action did not take place. This may include errors such as command line too long.
///	Syntax error in parameters or arguments.
#define SL_FTP_SRV_RET_CODE_5XX_SYNTAXERR   501U
///	Command not implemented.
#define SL_FTP_SRV_RET_CODE_5XX_CMDNOTIMP   502U
///	Bad sequence of commands.
#define SL_FTP_SRV_RET_CODE_5XX_BADSEQCMD   503U
///	Command not implemented for that parameter.
#define SL_FTP_SRV_RET_CODE_5XX_CMDPARNIMP  504U
///	Not logged in.
#define SL_FTP_SRV_RET_CODE_5XX_NOTLOGI     530U
///	Need account for storing files.
#define SL_FTP_SRV_RET_CODE_5XX_NEEDACSF    532U
///	Request denied for policy reasons.
#define SL_FTP_SRV_RET_CODE_5XX_REQDPOL     534U
///	Requested action not taken. File unavailable (e.g., file not found, no access).
#define SL_FTP_SRV_RET_CODE_5XX_REQACTNT    550U
///	Requested action aborted. Page type unknown.
#define SL_FTP_SRV_RET_CODE_5XX_REQACABORT  551U
///	Requested file action aborted. Exceeded storage allocation (for current directory or dataset).
#define SL_FTP_SRV_RET_CODE_5XX_REQFAABORT  552U
///	Requested action not taken. File name not allowed.
#define SL_FTP_SRV_RET_CODE_5XX_REQACTNOT   553U

// 600 Series: Replies regarding confidentiality and integrity
///	Integrity protected reply.
#define SL_FTP_SRV_RET_CODE_6XX_INTPROREP   631U
///	Confidentiality and integrity protected reply.
#define SL_FTP_SRV_RET_CODE_6XX_CONINTPREP  632U
///	Confidentiality protected reply.
#define SL_FTP_SRV_RET_CODE_6XX_CONFPROREP  633U

// 10000 Series: Common Winsock Error Codes[2] (These are not FTP return codes)
///	Connection reset by peer. The connection was forcibly closed by the remote host.
#define SL_FTP_SRV_RET_CODE_100XX_CONRST    10054U
///	Cannot connect to remote server.
#define SL_FTP_SRV_RET_CODE_100XX_NOCONSRV  10060U
///	Cannot connect to remote server. The connection is actively refused by the server.
#define SL_FTP_SRV_RET_CODE_100XX_REFCONS   10061U
///	No route to host / DNS cannot be resolved.
#define SL_FTP_SRV_RET_CODE_100XX_NORHOST   10065U
///	Directory not empty.
#define SL_FTP_SRV_RET_CODE_100XX_DIRNOTE   10066U
///	Too many users, server is full.
#define SL_FTP_SRV_RET_CODE_100XX_SRVFULL   10068U

/// FTP default port of control channel
#define SL_FTP_SRV_DEFAULT_CTRL_PORT        21U

/// FTP default port of data channel
#define SL_FTP_SRV_DEFAULT_DATA_PORT        20U

#if  defined(SL_WISUN_UNIT_TEST)
#warning Unit test enabled
/// FTP Service loop for unit tests
#define SL_FTP_SERVICE_LOOP()       for (uint8_t i = 0U; i < SL_FTP_SERVICE_LOOP_EXPECTED_CNT; ++i)
#else
/// FTP Service loop
#define SL_FTP_SERVICE_LOOP()       while (1)
#endif

/// FTP Client channel
typedef struct sl_ftp_clnt_ch {
  /// Socket ID
  int32_t sock_id;
  /// Host address string
  const char *host;
  /// Remote Port
  uint16_t port;
  /// Buffer pointer
  uint8_t *buff_ptr;
  /// Buffer size
  size_t buff_size;
  /// Data handler
  void (*data_hnd)(struct  sl_ftp_clnt_ch* const, const size_t);
} sl_ftp_clnt_ch_t;

/// FTP Client data handler callback type definition
typedef void (*sl_ftp_clnt_ch_data_hnd_t)(sl_ftp_clnt_ch_t * const clnt_ch, const size_t rcv_data_size);

/// FTP Client modes
typedef enum sl_ftp_clnt_mode {
  /// FTP Client passive mode
  FTP_CLNT_MODE_PASSIVE = 0,
  /// FTP Client extended passive mode
  FTP_CLNT_MODE_EXT_PASSIVE,
} sl_ftp_clnt_mode_t;

/// FTP server return code type definition
typedef int32_t sl_ftp_srv_ret_code_t;

/// FTP Client
typedef struct sl_ftp_clnt {
  /// Control channel
  sl_ftp_clnt_ch_t ctrl_ch;
  /// Data channel
  sl_ftp_clnt_ch_t data_ch;
  /// Mode
  sl_ftp_clnt_mode_t mode;
  /// Server return code
  sl_ftp_srv_ret_code_t srv_ret_code;
  /// Event flags
  osEventFlagsId_t evt_flags;
} sl_ftp_clnt_t;

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * @brief Init FTP service
 * @details Initialize OS objects
 ******************************************************************************/
void sl_ftp_clnt_service_init(void);

/***************************************************************************//**
 * @brief Init FTP Client instance
 * @details Initialize buffer and connection parameters
 * @param[in,out] clnt FTP Client to initialize
 * @param[in] host Remote host address string
 * @return sl_status_t SL_STATUS_OK on succes, otherwise SL_STATUS_FAIL
 ******************************************************************************/
sl_status_t sl_ftp_clnt_init(sl_ftp_clnt_t * const clnt,
                             const char *host);

/***************************************************************************//**
 * @brief Initializ FTP client with default settings
 * @details Settings are included in configuration
 * @param[in,out] clnt FTP Client to initialize
 * @return sl_status_t SL_STATUS_OK on succes, otherwise SL_STATUS_FAIL
 ******************************************************************************/
__STATIC_INLINE sl_status_t sl_ftp_clnt_default_init(sl_ftp_clnt_t * const clnt)
{
  return sl_ftp_clnt_init(clnt, SL_FTP_CLNT_AUTH_DEFAUL_HOST);
}

/***************************************************************************//**
 * @brief FTP client connects to server
 * @details Using portable socket connect implementation
 * @param[in,out] clnt FTP Client to connect
 * @return sl_status_t SL_STATUS_OK on succes, otherwise SL_STATUS_FAIL
 ******************************************************************************/
sl_status_t sl_wiusn_ftp_clnt_connect(sl_ftp_clnt_t * const clnt);

/***************************************************************************//**
 * @brief FTP Client connect with authentication
 * @details Connect client control channel with authentication data
 * @param[in,out] clnt FTP Client
 * @param[in] user User name
 * @param[in] password Password
 * @return sl_status_t SL_STATUS_OK on succes, otherwise SL_STATUS_FAIL
 ******************************************************************************/
sl_status_t sl_ftp_clnt_connect_auth(sl_ftp_clnt_t * const clnt,
                                     const char *user,
                                     const char *password);

/***************************************************************************//**
 * @brief FTP Client connect with default authentication
 * @details Default authentication data is defined in config file
 * @param[in,out] clnt
 * @return sl_status_t SL_STATUS_OK on succes, otherwise SL_STATUS_FAIL
 ******************************************************************************/
__STATIC_INLINE sl_status_t sl_ftp_clnt_connect_default_auth(sl_ftp_clnt_t * const clnt)
{
  return sl_ftp_clnt_connect_auth(clnt, SL_FTP_CLNT_AUTH_DEFAULT_USER, SL_FTP_CLNT_AUTH_DEFAULT_PASSWORD);
}

/***************************************************************************//**
 * @brief FTP Client send command
 * @details Send FTP Client commands on control channel
 * @param[in,out] clnt FTP client
 * @param[in] cmd Command string
 * @param[in] content Content of command
 * @return sl_status_t SL_STATUS_OK on succes, otherwise SL_STATUS_FAIL
 ******************************************************************************/
sl_status_t sl_ftp_clnt_send_cmd(sl_ftp_clnt_t * const clnt,
                                 const char *cmd,
                                 const char *content);

/***************************************************************************//**
 * @brief FTP Client receive on control channel
 * @details Receiving control command responses
 * @param[in,out] clnt FTP Client
 * @return sl_status_t SL_STATUS_OK on succes, otherwise SL_STATUS_FAIL
 ******************************************************************************/
sl_status_t  sl_ftp_clnt_recv_ctrl(sl_ftp_clnt_t * const clnt);

/***************************************************************************//**
 * @brief FTP Client receive until return code detected
 * @details Receiving on control channel until detect the expected return code, or timeout
 * @param[in,out] clnt FTP Client
 * @param[in] ret_code Expected return code
 * @return sl_status_t SL_STATUS_OK on succes, otherwise SL_STATUS_FAIL
 ******************************************************************************/
sl_status_t sl_ftp_clnt_recv_ctrl_until_ret_code(sl_ftp_clnt_t * const clnt,
                                                 sl_ftp_srv_ret_code_t ret_code);

/***************************************************************************//**
 * @brief FTP Client close
 * @details Close connection on control and data channal too
 * @param[in,out] clnt FTP Client
 * @return sl_status_t SL_STATUS_OK on succes, otherwise SL_STATUS_FAIL
 ******************************************************************************/
sl_status_t sl_ftp_clnt_close(sl_ftp_clnt_t * const clnt);

/***************************************************************************//**
 * @brief Get file content from Server
 * @details Data channel received content is handled in client data channel data handler callback
 * @param[in,out] clnt FTP Client
 * @param[in] file File name string
 * @return sl_status_t SL_STATUS_OK on succes, otherwise SL_STATUS_FAIL
 ******************************************************************************/
sl_status_t sl_ftp_clnt_get(sl_ftp_clnt_t * const clnt,
                            const char *file);
/***************************************************************************//**
 * @brief Put content to Server file system
 * @details Send data channel buffer to server file system.
 * @param[in,out] clnt FTP Client
 * @param[in] file File name to store data
 * @return sl_status_t SL_STATUS_OK on succes, otherwise SL_STATUS_FAIL
 ******************************************************************************/
sl_status_t sl_ftp_clnt_put(sl_ftp_clnt_t * const clnt,
                            const char *file);

/***************************************************************************//**
 * @brief Delte file on Server file system
 * @details Send request to delete file on Server file system
 * @param[in,out] clnt FTP Client
 * @param[in] file File name to delete
 * @return sl_status_t SL_STATUS_OK on succes, otherwise SL_STATUS_FAIL
 ******************************************************************************/
sl_status_t sl_ftp_clnt_delete_file(sl_ftp_clnt_t * const clnt,
                                    const char *file);

#endif

#ifdef __cplusplus
}
#endif
#endif
