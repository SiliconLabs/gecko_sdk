"""
ESL Encrypted Advertising Data Module.
"""

# Copyright 2023 Silicon Laboratories Inc. www.silabs.com
#
# SPDX-License-Identifier: Zlib
#
# The licensor of this software is Silicon Laboratories Inc.
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

import secrets
from cryptography.hazmat.primitives.ciphers.aead import AESCCM
from ap_constants import *
from ap_logger import getLogger

### Configuration values

# B1 block, octet 2 (header) for EAD encryption, CSS d11, Part A, 1.23.3
ENCRYPTED_DATA_B1_HEADER = 0xEA

class KeyMaterial():
    """ Encrypted Advertising Data Key Material """
    def __init__(self, keymat):
        self.key = keymat[0:16][::-1] # Reverse byteorder to big-endian for the key
        self.iv = keymat[16:24]


class EAD():
    """ Encrypted Advertising Data handling class """
    def __init__(self):
        self.log = getLogger()

    def encrypt(self, data, key_material, random=None):
        """ Encrypt PA data and assemble the ESL payload """
        ead_ad_type = EAD_AD_TYPE.to_bytes(1, byteorder='little')
        esl_ad_type = ESL_AD_TYPE.to_bytes(1, byteorder='little')
        if random is not None:
            randomizer = random
        else:
            randomizer = secrets.token_bytes(EAD_RANDOMIZER_SIZE)
        add_data = (ENCRYPTED_DATA_B1_HEADER).to_bytes(1, byteorder='little')
        nonce = randomizer + key_material.iv

        aes_ccm = AESCCM(key_material.key, 4)
        payload_length = len(esl_ad_type) + len(data)
        data = payload_length.to_bytes(1, byteorder='little') + esl_ad_type + data
        ad_data = aes_ccm.encrypt(nonce, data, add_data)

        length = len(ead_ad_type) + len(randomizer) + len(ad_data)
        ret = length.to_bytes(1, byteorder='little') + ead_ad_type + randomizer + ad_data
        return ret

    def decrypt(self, data, key_material):
        """ Decrypt encrypted PA data """
        ad_data = b""
        add_data = (ENCRYPTED_DATA_B1_HEADER).to_bytes(1, byteorder='little')
        randomizer, enc_data = self.unpack(data)

        if randomizer is not None:
            nonce = randomizer + key_material.iv
            aes_ccm = AESCCM(key_material.key, 4)
            try:
                ad_data = aes_ccm.decrypt(nonce, enc_data, add_data)
            except:
                self.log.error("AEAD decryption failed.")

        return ad_data

    def unpack(self, data):
        """ Unpack fields from PA data """
        randomizer = None
        enc_data = None
        if (data[0] > EAD_PACKET_OVERHEAD) and data[1] == EAD_AD_TYPE:
            randomizer = data[2:7]
            enc_data = data[7:]
        else:
            self.log.error("Wrong encrypted PA payload size!")

        return randomizer, enc_data

    def generate_key(self, bitlen=128):
        """ Generate AES key """
        return AESCCM.generate_key(bit_length=bitlen)
