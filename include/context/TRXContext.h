//
//  TRXContext.h
//  JubSDK
//
//  Created by Pan Min on 2020/09/10.
//  Copyright © 2020 JuBiter. All rights reserved.
//

#pragma once
#ifndef __ContextTRX__
#define __ContextTRX__

#include "JUB_SDK_TRX.h"

#include <string>
#include <vector>

#include "utility/Singleton.h"
#include "utility/xManager.hpp"

#include "context/BaseContext.h"
#include "token/interface/BaseToken.h"


namespace jub {
namespace context {


class TRXContext :
    public BaseContext {
public:
    //for Factory
    static TRXContext* Create(const CONTEXT_CONFIG_TRX& cfg,
                              std::shared_ptr<token::BaseToken> tokenPtr) {
        return new TRXContext(cfg, tokenPtr);
    }

    TRXContext(CONTEXT_CONFIG_TRX cfg, std::shared_ptr<token::BaseToken> tokenPtr) :
        BaseContext(tokenPtr) {
            _mainPath = cfg.mainPath;
            _timeout = 120 * 2;
            _appletVersion = "";
    }
    ~TRXContext() {}

    virtual JUB_RV GetAddress(const BIP44_Path& path, const JUB_UINT16 tag, std::string& address);
    virtual JUB_RV SetMyAddress(const BIP44_Path& path, std::string& address);
    virtual JUB_RV GetHDNode(const JUB_BYTE format, const BIP44_Path& path, std::string& pubkey);
    virtual JUB_RV GetAddress(const BIP48_Path& path, const JUB_UINT16 tag, std::string& address);
    virtual JUB_RV SetMyAddress(const BIP48_Path& path, std::string& address);
    virtual JUB_RV GetHDNode(const JUB_BYTE format, const BIP48_Path& path, std::string& pubkey);
    virtual JUB_RV GetMainHDNode(const JUB_BYTE format, std::string& xpub);

    virtual JUB_RV SignTransaction(const BIP44_Path& path,
                                   JUB_CHAR_CPTR packedContractInPb,
                                   std::string& rawInJSON);

    virtual JUB_RV BuildTRC20Abi(JUB_CHAR_CPTR to, JUB_CHAR_CPTR value, std::string& abi);
    virtual JUB_RV SetTRC20Token(JUB_CHAR_CPTR pTokenName,
                                 JUB_UINT16 unitDP,
                                 JUB_CHAR_CPTR pContractAddress);

    virtual JUB_RV PackTransactionRaw(const JUB_TX_TRX& tx,
                                      std::string& packedContractInPB);

    virtual JUB_RV ActiveSelf() override;
}; // class TRXContext end


} // namespace context end
} // namespace jub end

#endif // #pragma once
