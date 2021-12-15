/**
 * @file
 * @brief Defines NVM3 file system for application.
 *
 * @details The module contains a nvm3_Handle_t that defines the NVM3 file system
 * for the application. A pointer to the handle is passed as output parameter
 * from ApplicationFileSystemInit(). There are also functions for verifying
 * that the file system contains the files that are expected.
 *
 * @copyright 2019 Silicon Laboratories Inc.
 */

#ifndef ZAF_APPLICATIONUTILITIES_ZAF_NVM3_APP_H_
#define ZAF_APPLICATIONUTILITIES_ZAF_NVM3_APP_H_

#include "nvm3.h"

// Description of an NVM3 file for the caretaker.
typedef struct SFileDescriptor
{
  nvm3_ObjectKey_t ObjectKey;
  size_t   iDataSize;
} SFileDescriptor;

// Set of file descriptors
typedef struct SFileSet
{
  nvm3_Handle_t *         pFileSystem;
  uint32_t                iFileCount;
  const SFileDescriptor*  pFileDescriptors;
} SFileSet;


// Error codes returned from FileSystemVerify Interface
typedef enum EFileSysVerifyStatus
{
  EFSV_STATUS_SUCCESS = 0,
  EFSV_STATUS_FILESYS_MISMATCH,

  // Object errors
  EFSV_STATUS_UNABLE_TO_AQUIRE_HANDLE,  // Most likely caused by file not existing
  EFSV_STATUS_SIZE_MISMATCH,            // Current file size does not match size specified

  // Could not create or modify misfit files
  EFSV_STATUS_WRITE_ERROR

} EFileSysVerifyStatus;


/**
* @brief Opens file system for application and passes a handle to it as output pointer.
*
* @param[out] pFileSystemApplication Handle to file system passed to application.
* @return bool true if nvm3_open() succeeded else false.
*/
bool ApplicationFileSystemInit(nvm3_Handle_t** pFileSystemApplication);

/**
 * Returns the application file system handle.
 * @return The application file system handle.
 */
nvm3_Handle_t * ZAF_GetFileSystemHandle(void);

#endif /* ZAF_APPLICATIONUTILITIES_ZAF_NVM3_APP_H_ */
