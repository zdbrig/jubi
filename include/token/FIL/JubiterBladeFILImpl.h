#pragma once
#include <memory>

#include "token/JubiterBlade/JubiterBladeToken.h"
#include "token/ETH/JubiterBladeETHImpl.h"
#include "token/FIL/JubiterBaseFILImpl.h"


namespace jub {
namespace token {


class JubiterBladeFILImpl :
        public JubiterBladeToken,
virtual public JubiterBaseFILImpl {

public:
    //for Factory
    static std::shared_ptr<BaseToken> Create(JUB_UINT16 deviceID) {
        return std::make_shared<JubiterBladeFILImpl>(deviceID);
    }

    JubiterBladeFILImpl(JUB_UINT16 deviceID) :
        JubiterBladeToken(deviceID) {}
    ~JubiterBladeFILImpl() {}


    //FIL functions
    virtual JUB_RV SelectApplet() override;
    virtual JUB_RV SetCoin() override;
    virtual JUB_RV GetAddress(const std::string& path, const JUB_UINT16 tag, std::string& address) override;
    virtual JUB_RV GetHDNode(const JUB_BYTE format, const std::string& path, std::string& pubkey) override;
    virtual JUB_RV SignTX(const uint64_t& nonce,
                          const  int64_t& glimit,
                          const uint256_t& gfeeCap,
                          const uint256_t& gpremium,
                          const std::string& to,
                          const uint256_t& value,
                          const std::string& input,
                          const std::string& path,
                          std::vector<uchar_vector>& vSignatureRaw) override;
}; // class JubiterBladeFILImpl end


} // namespace token end
} // namespace jub end
