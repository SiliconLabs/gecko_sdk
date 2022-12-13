/***************************************************************************//**
 * @file
 * @brief Implementation of safe string functions.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_string.h"
#include <stdint.h>
#include <ctype.h>

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * Copy a string into a buffer.
 ******************************************************************************/
void sl_strcpy_s(char *dst, size_t dst_size, const char *src)
{
  size_t len_copy = 0;

  if (dst == NULL) {
    return;
  }
  if (src == NULL) {
    return;
  }
  if (dst_size == 0) {
    return;
  }
  while ((*src != '\0') && (len_copy < (dst_size - 1))) {
    *dst = *src;
    dst++;
    src++;
    len_copy++;
  }
  *dst = '\0';
}

/***************************************************************************//**
 * Append the source string to the end of destination string
 ******************************************************************************/
void sl_strcat_s(char *dst, size_t dst_size, const char *src)
{
  size_t ofs;

  if (dst == NULL) {
    return;
  }
  if (src == NULL) {
    return;
  }
  if (dst_size == 0) {
    return;
  }
  ofs = sl_strlen(dst);
  if (ofs < dst_size) {
    sl_strcpy_s(&dst[ofs], dst_size - ofs, src);
  }
}

/***************************************************************************//**
 * Get the string length
 ******************************************************************************/
size_t sl_strlen(char *str)
{
  return sl_strnlen(str, SIZE_MAX);
}

/***************************************************************************//**
 * Get the string length, limited to a given length
 ******************************************************************************/
size_t sl_strnlen(char *str, size_t max_len)
{
  size_t len = 0;

  if (str == NULL) {
    return len;
  }
  while ((*str != '\0') && (len < max_len)) {
    str++;
    len++;
  }

  return len;
}

/***************************************************************************//**
 * Check if string is empty.
 ******************************************************************************/
bool sl_str_is_empty(const char *str)
{
  return (str == NULL || *str == '\0');
}

/***************************************************************************//**
 * Compare two strings, ignoring case.
 ******************************************************************************/
int sl_strcasecmp(char const *a, char const *b)
{
  int d = 0;

  if ((a == NULL) || (b == NULL)) {
    return 1;
  }
  for (;; a++, b++) {
    d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
    if ((d != 0) || (!*a)) {
      break;
    }
  }
  return d;
}

/***************************************************************************//**
 * Search for a character in memory, in reverse order.
 * Inspired from the GNU implementation of memchr and memrchr.
 ******************************************************************************/
void* sl_memrchr(void const *buff, char c, size_t buffer_len)
{
  // Go to the end of the buffer
  char* buffer;

  if (buff == NULL || buffer_len == 0) {
    return NULL;
  }

  // Check unaligned chars
  for (buffer = (char*)((uintptr_t)buff + buffer_len); buffer_len > 0 && ((unsigned long)buffer % sizeof(unsigned long)) != 0; buffer_len--) {
    if (*--buffer == c) {
      return buffer;
    }
  }

  // Check aligned buffers
  /**
   * Instead of checking byte per byte, we check an
   * entire word at a time to see if the target byte is present.
   * Algorithm goes as follows:
   * 1) Compute the xor of the current 32bit buffer with a buffer
   *    containing only the target char, this way, we get a 0 byte
   *    iif the byte is the same as the char.
   * 2) We substract 1 to all bytes, and then check if the MSb
   *    is 1. If so, then the byte was 0, and so the character was there.
   * 3) We return the address of the character.
   **/
  unsigned long *word_pointer = (unsigned long *) buffer - 1;
  unsigned long c_mask = c << 24 | c << 16 | c << 8 | c;
  unsigned long one_mask = 0x01010101;
  if (sizeof(unsigned long) >  4) {
    // 64 bit system support
    c_mask |= c_mask << 31 << 1;
    one_mask |= one_mask << 31 << 1;
  }
  while (buffer_len >= sizeof(uintptr_t)) {
    uint32_t char_xor = c_mask ^ (*word_pointer);
    if (((char_xor - one_mask) & (one_mask << 7)) != 0) {
      // Character in the word
      if (sizeof(unsigned long) >  4) {
        if (((char*)word_pointer)[7] == c) {
          return &((char*)word_pointer)[7];
        }
        if (((char*)word_pointer)[6] == c) {
          return &((char*)word_pointer)[6];
        }
        if (((char*)word_pointer)[5] == c) {
          return &((char*)word_pointer)[5];
        }
        if (((char*)word_pointer)[4] == c) {
          return &((char*)word_pointer)[4];
        }
      }
      if (((char*)word_pointer)[3] == c) {
        return &((char*)word_pointer)[3];
      }
      if (((char*)word_pointer)[2] == c) {
        return &((char*)word_pointer)[2];
      }
      if (((char*)word_pointer)[1] == c) {
        return &((char*)word_pointer)[1];
      }
      if (((char*)word_pointer)[0] == c) {
        return &((char*)word_pointer)[0];
      }
    }
    buffer--;
    buffer_len -= sizeof(uintptr_t);
  }

  // Check the rest of the unaligned bytes, if any
  for (; buffer_len > 0; buffer_len--) {
    if (*--buffer == c) {
      return buffer;
    }
  }
  return NULL;
}
