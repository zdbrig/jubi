#include "JUB_SDK_Hcash.h"
#include "context/ContextHC.h"
#include "utility/util.h"
#include "token/interface/TokenInterface.hpp"
#include "token/interface/HCTokenInterface.hpp"
#include "mSIGNA/stdutils/uchar_vector.h"
#include <TrezorCrypto/ecdsa.h>
#include <TrezorCrypto/secp256k1.h>

namespace jub {

JUB_RV ContextHC::ActiveSelf() {

    auto token = dynamic_cast<HCTokenInterface*>(jub::TokenManager::GetInstance()->GetOne(_deviceID));
    auto ctoken = dynamic_cast<CommonTokenInterface*>(jub::TokenManager::GetInstance()->GetOne(_deviceID));
    JUB_CHECK_NULL(token);
    JUB_CHECK_NULL(ctoken);
    JUB_VERIFY_RV(token->selectApplet_HC());
    JUB_VERIFY_RV(ctoken->SetTimeout(_timeout));

    return JUBR_OK;
}

JUB_RV ContextHC::signTX(std::vector<INPUT_HC> vInputs, std::vector<OUTPUT_HC> vOutputs, std::string unsignedTrans, std::string& raw) {

    auto token = dynamic_cast<HCTokenInterface*>(jub::TokenManager::GetInstance()->GetOne(_deviceID));
    JUB_CHECK_NULL(token);

    //deal inputs
    std::vector<JUB_UINT64> vInputAmount;
    std::vector<std::string> vInputPath;
    for (auto input : vInputs) {
        vInputAmount.push_back(input.amount);
        vInputPath.push_back(_FullBip44Path(input.path));
    }

    //deal outputs
    std::vector<JUB_UINT16> vChangeIndex;
    std::vector<std::string> vChangePath;
    for (std::size_t i = 0, e = vOutputs.size(); i != e; ++i) {
        if (vOutputs[i].changeAddress) {
            vChangeIndex.push_back((JUB_UINT16)i);
            vChangePath.push_back(_FullBip44Path(vOutputs[i].path));
        }
    }

    uchar_vector vUnsignedTrans(unsignedTrans);

    uchar_vector vRaw;
    JUB_VERIFY_RV(token->SignTXBTC(p2pkh,
                                   (JUB_UINT16)vInputs.size(),
                                   vInputAmount,
                                   vInputPath,
                                   vChangeIndex,
                                   vChangePath,
                                   vUnsignedTrans,
                                   vRaw));

    raw = vRaw.getHex();

    return JUBR_OK;
}

} // namespace jub end