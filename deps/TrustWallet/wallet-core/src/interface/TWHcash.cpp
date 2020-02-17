// Copyright © 2017-2019 JuBiter.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <TrustWalletCore/TWHcash.h>

// JuBiter-defined
bool SigHashIsAll(uint32_t type) {
    return (type & 0x1f) == SigHashAll;
}
