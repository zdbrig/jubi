/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   JUB_core.h
 * Author: zxc
 *
 * Created on 2019年7月18日, 上午10:58
 */


#ifndef JUB_CORE_H
#define JUB_CORE_H

#include "JUB_SDK.h"

typedef enum {
    STRENGTH128 = 128,
    STRENGTH192 = 192,
    STRENGTH256 = 256
} JUB_MNEMONIC_STRENGTH;

typedef enum{
    secp256k1 = 0,
    ed25519,
    nist256p1      
}JUB_CURVES;

JUB_RV JUB_GenerateMnemonic(IN JUB_MNEMONIC_STRENGTH strength, OUT JUB_CHAR_PTR_PTR mnemonic);

JUB_RV JUB_CheckMnemonic(IN JUB_CHAR_CPTR mnemonic);

JUB_RV JUB_GenerateSeed(IN JUB_CHAR_CPTR mnemonic, IN JUB_CHAR_CPTR passphrase, OUT JUB_BYTE seed[64], void (*progress_callback)(JUB_UINT32 current, JUB_UINT32 total));

JUB_RV JUB_SeedToMasterPrivateKey(IN JUB_BYTE_PTR seed, IN JUB_UINT16 seed_len, IN JUB_CURVES curve, OUT JUB_CHAR_PTR_PTR prikeyInXPRI);

#endif /* JUB_CORE_H */
