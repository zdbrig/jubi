#pragma once
#include "token/JubiterBIO/JubiterBIOToken.h"
#include "token/EOS/JubiterBladeEOSImpl.h"

#include <memory>

namespace jub {
namespace token {


class JubiterBIOEOSImpl :
        public JubiterBIOToken,
virtual public JubiterBladeEOSImpl {
public:
    //for Factory
    static std::shared_ptr<BaseToken> Create(const JUB_UINT16 deviceID) {
        return std::make_shared<JubiterBIOEOSImpl>(deviceID);
    }

public:
    JubiterBIOEOSImpl(const JUB_UINT16 deviceID) :
        JubiterBIOToken(deviceID),
        JubiterBladeEOSImpl(deviceID) {}
    virtual ~JubiterBIOEOSImpl() = default;

    virtual JUB_RV GetHDNode(const JUB_BYTE format, const std::string& path, std::string& pubkey) override;
}; // class JubiterBIOEOSImpl end


} // namespace token end
} // namespace jub end
