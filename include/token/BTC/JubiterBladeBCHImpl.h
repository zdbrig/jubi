#pragma once
#include <memory>

#include "token/BTC/JubiterBladeBTCImpl.h"
#include "token/BTC/JubiterBaseBCHImpl.h"


namespace jub {
namespace token {


class JubiterBladeBCHImpl :
        public JubiterBladeBTCImpl,
virtual public JubiterBaseBCHImpl {
public:
    //for Factory
    static std::shared_ptr<BaseToken> Create(const JUB_UINT16 deviceID) {
        return std::make_shared<JubiterBladeBCHImpl>(deviceID);
    }

public:
    JubiterBladeBCHImpl(const JUB_UINT16 deviceID) :
        JubiterBladeBTCImpl(deviceID) {
            _hashType = TWBitcoinSigHashTypeForkBCH;
	}
    ~JubiterBladeBCHImpl() {}
}; // class JubiterBladeBCHImpl end


} // namespace token end
} // namespace jub end
