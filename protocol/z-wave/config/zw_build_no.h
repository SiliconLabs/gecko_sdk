/**
 * @file
 * @copyright 2021 Silicon Laboratories Inc.
 */

#ifndef _ZW_BUILD_NO_H_
#define _ZW_BUILD_NO_H_


// Can be changed with command line argument.
#ifndef ZW_BUILD_NO
#define ZW_BUILD_NO 0xABCD
#endif

#ifndef ZAF_BUILD_NO
#define ZAF_BUILD_NO  ZW_BUILD_NO
#endif

#endif /* _ZW_BUILD_NO_H_ */
