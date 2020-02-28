#include <token/BTC/JubiterBaseBTCImpl.h>
#include <TrezorCrypto/base58.h>
#include <TrezorCrypto/bip32.h>
#include <Bitcoin/Address.h>
#include <Bitcoin/SegwitAddress.h>


namespace jub {
namespace token {


JUB_RV JubiterBaseBTCImpl::_getPubkeyFromXpub(const std::string& xpub, TW::Data& publicKey,
                                              uint32_t hdVersionPub, uint32_t hdVersionPrv) {

    try {
        HDNode hdkey;
        uint32_t fingerprint = 0;
        if (0 != hdnode_deserialize(xpub.c_str(),
                                    hdVersionPub, hdVersionPrv,
                                    _curve_name, &hdkey, &fingerprint)) {
            return JUBR_ARGUMENTS_BAD;
        }

        uchar_vector vPublicKey(hdkey.public_key, sizeof(hdkey.public_key)/sizeof(uint8_t));
        publicKey = TW::Data(vPublicKey);
    }
    catch (...) {
        return JUBR_ARGUMENTS_BAD;
    }

    return JUBR_OK;
}


JUB_RV JubiterBaseBTCImpl::_getAddress(const TW::Data publicKey, std::string& address) {

    try {
        TW::Bitcoin::Address addr(TW::PublicKey(publicKey, _publicKeyType), TWCoinTypeP2pkhPrefix(_coin));
        address = addr.string();
    }
    catch (...) {
        return JUBR_ARGUMENTS_BAD;
    }

    return JUBR_OK;
}


JUB_RV JubiterBaseBTCImpl::_getSegwitAddress(const TW::Data publicKey, std::string& address) {

    try {
        // keyhash
        TW::Bitcoin::SegwitAddress segwitAddr(TW::PublicKey(publicKey, _publicKeyType), OpCode::OP_0, std::string(stringForHRP(TWCoinTypeHRP(_coin))));

        // redeemScript
        TW::Bitcoin::Script redeemScript = TW::Bitcoin::Script::buildPayToWitnessProgram(segwitAddr.witnessProgram);
        TW::Data hRedeemScript = TW::Hash::sha256ripemd(&redeemScript.bytes[0], &redeemScript.bytes[0]+redeemScript.bytes.size());

        // address
        TW::Data bytes;
        bytes.insert(bytes.end(), TWCoinTypeP2shPrefix(_coin));
        bytes.insert(bytes.end(), hRedeemScript.begin(), hRedeemScript.end());

        address = TW::Base58::bitcoin.encodeCheck(bytes);
    }
    catch (...) {
        return JUBR_ARGUMENTS_BAD;
    }

    return JUBR_OK;
}


JUB_RV JubiterBaseBTCImpl::_serializeUnsignedTx(const uint32_t coin,
                                                const std::vector<INPUT_BTC>& vInputs,
                                                const std::vector<OUTPUT_BTC>& vOutputs,
                                                TW::Bitcoin::Transaction& tx) {

    // inputs
    for (const auto& input:vInputs) {
        uchar_vector preHash(input.preHash);
        preHash.reverse();
        TW::Bitcoin::OutPoint outpoint(preHash, input.preIndex);
        TW::Bitcoin::TransactionInput *txInput = new TW::Bitcoin::TransactionInput();
        txInput->previousOutput = outpoint;
        txInput->script = TW::Bitcoin::Script();// null
        txInput->sequence = input.nSequence;
        tx.inputs.push_back(txInput);
    }

    // outputs
    for (const auto& output:vOutputs) {
        TW::Bitcoin::Script scriptPubkey;
        JUB_UINT64 amount = 0;
        switch (output.type) {
            case JUB_ENUM_SCRIPT_BTC_TYPE::RETURN0:
            {
                TW::Data return0(output.return0.dataLen);
                std::memcpy(&return0[0], output.return0.data, output.return0.dataLen);

                scriptPubkey = TW::Bitcoin::Script::buildReturn0(return0);
                amount = output.return0.amount;
                break;
            }
            case JUB_ENUM_SCRIPT_BTC_TYPE::QRC20:
            {
                TW::Data qrc20(output.qrc20.dataLen);
                std::memcpy(&qrc20[0], output.qrc20.data, output.qrc20.dataLen);

                scriptPubkey = TW::Bitcoin::Script(qrc20.begin(), qrc20.end());
                break;
            }
            default:
            {
                scriptPubkey = TW::Bitcoin::Script::buildForAddress(std::string(output.stdOutput.address), (TWCoinType)coin);
                amount = output.stdOutput.amount;
                break;
            }
        }
        TW::Bitcoin::TransactionOutput *ptxOutput = new TW::Bitcoin::TransactionOutput();
        ptxOutput->value = TW::Bitcoin::Amount(amount);
        ptxOutput->script = scriptPubkey;
        tx.outputs.push_back(ptxOutput);
    }

    return JUBR_OK;
}


JUB_RV JubiterBaseBTCImpl::SerializeUnsignedTx(const JUB_ENUM_BTC_TRANS_TYPE& type,
                                               const std::vector<INPUT_BTC>& vInputs,
                                               const std::vector<OUTPUT_BTC>& vOutputs,
                                               const JUB_UINT32 lockTime,
                                               uchar_vector& unsignedRaw) {

    bool witness = false;
    if (p2sh_p2wpkh == type) {
        witness = true;
    }

    TW::Bitcoin::Transaction tx(lockTime);
    JUB_VERIFY_RV(_serializeUnsignedTx(_coin,
                                       vInputs,
                                       vOutputs,
                                       tx));

    tx.encode(witness, unsignedRaw);

    return JUBR_OK;
}


JUB_RV JubiterBaseBTCImpl::_verifyPayToPublicKeyHashScriptSig(const TWCoinType& coin,
                                                              const TW::Bitcoin::Transaction& tx,
                                                              const size_t index, const uint32_t& hashType, const uint64_t amount,
                                                              const TW::Data& signature,
                                                              const TW::PublicKey publicKey,
                                                              bool witness) {

    JUB_RV rv = JUBR_OK;

    // script code - scriptPubKey
    uint8_t prefix = TWCoinTypeP2pkhPrefix(coin);
    TW::Bitcoin::Address addr(publicKey, prefix);
    TW::Bitcoin::Script scriptCode = TW::Bitcoin::Script::buildForAddress(addr.string(), coin);
    if (0 == scriptCode.size()) {
        return JUBR_ARGUMENTS_BAD;
    }

    TW::Data preImage;
    if (!witness) {
        preImage = tx.getPreImage(scriptCode, index, hashType);
    }
    else {
        preImage = tx.getPreImage(scriptCode, index, hashType, amount);
    }
    const auto begin = reinterpret_cast<const uint8_t*>(preImage.data());
    TW::Data digest = tx.hasher(begin, begin+preImage.size());
    if (!publicKey.verifyAsDER(signature, digest)) {
        rv = JUBR_ERROR;
    }

    return rv;
}


JUB_RV JubiterBaseBTCImpl::_verifyTx(const TWCoinType& coin,
                                     const TW::Bitcoin::Transaction* tx,
                                     const uint32_t& hashType,
                                     const std::vector<JUB_UINT64>& vInputAmount,
                                     const std::vector<TW::PublicKey>& vInputPublicKey) {

    JUB_RV rv = JUBR_OK;

    for (size_t index=0; index<tx->inputs.size(); ++index) {
        rv = JUBR_ERROR;

        TW::Bitcoin::Script witnessProgram;
        if (!witnessProgram.decode(tx->inputs[index]->script.bytes)) {
            rv = JUBR_ERROR;
            break;
        }

        if (witnessProgram.isWitnessProgram()) {
            TW::Data signature;
            TW::Data publicKey;
            // P2WPKH
            if (witnessProgram.isPayToWitnessScriptHash()) {
                if (!TW::Bitcoin::Script::parseWitnessStackToPayToWitnessScriptHash(tx->inputs[index]->scriptWitness,
                                                                                    signature, publicKey)) {
                    rv = JUBR_ERROR;
                    break;
                }
                
                if (vInputPublicKey[index].bytes != publicKey) {
                    continue;
                }

                rv = _verifyPayToPublicKeyHashScriptSig(coin,
                                                        *tx,
                                                        index, hashType, vInputAmount[index],
                                                        signature,
                                                        vInputPublicKey[index],
                                                        true);
                if (JUBR_OK != rv) {
                    break;
                }
                else {
                    rv = JUBR_OK;
                }
            }
//            else if (witnessProgram.isPayToWitnessxxx) {
//
//            }
            else {
                rv = JUBR_ERROR;
                continue;
            }
        }
        else {
            TW::Data signature;
            TW::Data publicKey;
            TW::Bitcoin::Script script = tx->inputs[index]->script;
            // P2PKH
            if (script.matchPayToPublicKeyHashScriptSig(signature, publicKey)) {
                if (vInputPublicKey[index].bytes != publicKey) {
                    continue;
                }

                rv = _verifyPayToPublicKeyHashScriptSig(coin,
                                                        *tx,
                                                        index, hashType, vInputAmount[index],
                                                        signature,
                                                        vInputPublicKey[index]);
                if (JUBR_OK != rv) {
                    break;
                }
                else {
                    rv = JUBR_OK;
                }
            }
//            else if (signedTx.inputs[index].script.matchxxx) {
//
//            }
            else {
                rv = JUBR_ERROR;
                continue;
            }
        }
    }

    return rv;
}


JUB_RV JubiterBaseBTCImpl::VerifyTx(const bool witness,
                                    const uchar_vector& signedRaw,
                                    const std::vector<JUB_UINT64>& vInputAmount,
                                    const std::vector<TW::Data>& vInputPublicKey) {

    JUB_RV rv = JUBR_ARGUMENTS_BAD;

    try {
        TW::Bitcoin::Transaction tx;
        if (!tx.decode(witness, signedRaw)) {
            return rv;
        }

        std::vector<TW::PublicKey> vInputPubkey;
        for(const auto& inputPublicKey:vInputPublicKey) {
            vInputPubkey.push_back(TW::PublicKey(TW::Data(inputPublicKey), _publicKeyType));
        }

        return _verifyTx(_coin,
                         &tx,
                         _hashType,
                         vInputAmount,
                         vInputPubkey);
    }
    catch (...) {
        rv = JUBR_ERROR;
    }

    return rv;
}


JUB_RV JubiterBaseBTCImpl::_serializeTx(bool witness,
                                        const std::vector<JUB_UINT64>& vInputAmount,
                                        const std::vector<TW::Data>& vInputPublicKey,
                                        const std::vector<uchar_vector>& vSignatureRaw,
                                        TW::Bitcoin::Transaction* tx,
                                        uchar_vector& signedRaw) {

    for (size_t index=0; index<tx->inputs.size(); ++index) {
        TW::Bitcoin::Script script;
        if (!witness) {
            // P2PKH
            tx->inputs[index]->script = TW::Bitcoin::Script::buildPayToPublicKeyHashScriptSig(vSignatureRaw[index], vInputPublicKey[index]);
        }
        else {
            // P2WPKH
            TW::PublicKey twpk = TW::PublicKey(vInputPublicKey[index], _publicKeyType);

            TW::Data scriptPubkey;
            TW::Bitcoin::Script::buildPayToWitnessPubkeyHash(twpk.hash(TW::Data())).encode(scriptPubkey);
            tx->inputs[index]->script.bytes = scriptPubkey;

            tx->inputs[index]->scriptWitness = TW::Bitcoin::Script::buildPayToPublicKeyHashScriptSigWitness(vSignatureRaw[index], vInputPublicKey[index]);
        }
    }

    tx->encode(witness, signedRaw);
    if (0 >= signedRaw.size()) {
        return JUBR_ERROR;
    }

    return JUBR_OK;
}


} // namespace token end
} // namespace jub end
