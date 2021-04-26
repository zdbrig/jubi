#pragma once
#include "token/JubiterBIO/JubiterBIOToken.h"
#include "token/TRX/JubiterBladeTRXImpl.h"

#include <memory>

namespace jub {
namespace token {


class JubiterBIOTRXImpl :
        public JubiterBIOToken,
virtual public JubiterBladeTRXImpl {
public:
    //for Factory
    static std::shared_ptr<BaseToken> Create(JUB_UINT16 deviceID) {
        return std::make_shared<JubiterBIOTRXImpl>(deviceID);
    }

public:
    JubiterBIOTRXImpl(JUB_UINT16 deviceID) :
        JubiterBIOToken(deviceID),
        JubiterBladeTRXImpl(deviceID) {}
    virtual ~JubiterBIOTRXImpl() = default;

    virtual JUB_RV SetTRC20Token(const std::string& tokenName,
                                 const JUB_UINT16 unitDP,
                                 const std::string& contractAddress) override;
    virtual JUB_RV GetHDNode(const JUB_BYTE format, const std::string& path, std::string& pubkey) override;

}; // class JubiterBIOTRXImpl end


} // namespace token end
} // namespace jub end
