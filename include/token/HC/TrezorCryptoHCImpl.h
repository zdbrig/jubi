#pragma once
#include <token/BTC/TrezorCryptoBTCImpl.h>
#include <token/HC/JubiterBaseHCImpl.h>

namespace jub {
namespace token {


class TrezorCryptoHCImpl :
        public TrezorCryptoBTCImpl,
virtual public JubiterBaseHCImpl {

public:
    TrezorCryptoHCImpl(const std::string& xprv) :
        TrezorCryptoBTCImpl(xprv) {
        _hashType = SigHashAll;
    };
    ~TrezorCryptoHCImpl() {};

    virtual JUB_RV SignTX(const JUB_BYTE addrFmt,
                          const JUB_ENUM_BTC_TRANS_TYPE& type,
                          const JUB_UINT16 inputCount,
                          const std::vector<JUB_UINT64>& vInputAmount,
                          const std::vector<std::string>& vInputPath,
                          const std::vector<JUB_UINT16>& vChangeIndex,
                          const std::vector<std::string>& vChangePath,
                          const std::vector<JUB_BYTE>& vUnsigedTrans,
                          std::vector<JUB_BYTE>& vRaw) override;

protected:
    virtual JUB_RV _HdnodePrivCkd(std::string path, HDNode* node, JUB_UINT32* parentFingerprint) override;
}; // class TrezorCryptoHCImpl end


} // namespace token end
} // namespace jub end
