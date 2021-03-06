#pragma once
#include <memory>

#include "token/BTC/JubiterLiteBTCImpl.h"


namespace jub {
namespace token {


class JubiterLiteLTCImpl :
    public JubiterLiteBTCImpl {
public:
    //for Factory
    static std::shared_ptr<BaseToken> Create(const JUB_UINT16 deviceID) {
        return std::make_shared<JubiterLiteLTCImpl>(deviceID);
    }

public:
    JubiterLiteLTCImpl(const JUB_UINT16 deviceID) :
        JubiterLiteBTCImpl(deviceID) {
            _coin = TWCoinType::TWCoinTypeLitecoin;
    }
    ~JubiterLiteLTCImpl() {}
}; // class JubiterLiteLTCImpl end


} // namespace token end
} // namespace jub end
