//
//  JUB_SDK_main.cpp
//  JubSDKTest
//
//  Created by panmin on 2019/9/17.
//  Copyright © 2019 JuBiter. All rights reserved.
//

#include "JUB_SDK_test.h"
#include "JUB_SDK_main.h"
#if SW
#include "JUB_SDK_software_test_btc.hpp"
#include "JUB_SDK_software_test_eth.hpp"
#include "JUB_SDK_software_test_hcash.hpp"
#include "JUB_SDK_software_test_eos.hpp"
#include "JUB_SDK_software_test_xrp.hpp"
#include "JUB_SDK_software_test_trx.hpp"
#include "JUB_SDK_software_test_fil.hpp"
#include "JUB_SDK_test_scp11.h"
#endif
using namespace std;

std::string GetErrMsg(JUB_RV rv) {

    std::string errMsg;
    switch (rv) {
    case JUBR_OK:                   { errMsg = "JUBR_OK"; break; }
    case JUBR_ERROR:                { errMsg = "JUBR_ERROR"; break; }
    case JUBR_HOST_MEMORY:          { errMsg = "JUBR_HOST_MEMORY"; break; }
    case JUBR_ARGUMENTS_BAD:        { errMsg = "JUBR_ARGUMENTS_BAD"; break; }
    case JUBR_IMPL_NOT_SUPPORT:     { errMsg = "JUBR_IMPL_NOT_SUPPORT"; break; }
    case JUBR_MEMORY_NULL_PTR:      { errMsg = "JUBR_MEMORY_NULL_PTR"; break; }
    case JUBR_CONTEXT_NOT_SATISFIED:{ errMsg = "JUBR_CONTEXT_NOT_SATISFIED"; break; }
    case JUBR_INVALID_MEMORY_PTR:   { errMsg = "JUBR_INVALID_MEMORY_PTR"; break; }
    case JUBR_REPEAT_MEMORY_PTR:    { errMsg = "JUBR_REPEAT_MEMORY_PTR"; break; }
    case JUBR_BUFFER_TOO_SMALL:     { errMsg = "JUBR_BUFFER_TOO_SMALL"; break; }
    case JUBR_MULTISIG_OK:          { errMsg = "JUBR_MULTISIG_OK"; break; }
    case JUBR_QRC20_WRONG_FORMAT:   { errMsg = "JUBR_QRC20_WRONG_FORMAT"; break; }

    case JUBR_INIT_DEVICE_LIB_ERROR:{ errMsg = "JUBR_INIT_DEVICE_LIB_ERROR"; break; }
    case JUBR_CONNECT_DEVICE_ERROR: { errMsg = "JUBR_CONNECT_DEVICE_ERROR"; break; }
    case JUBR_TRANSMIT_DEVICE_ERROR:{ errMsg = "JUBR_TRANSMIT_DEVICE_ERROR"; break; }
    case JUBR_NOT_CONNECT_DEVICE:   { errMsg = "JUBR_NOT_CONNECT_DEVICE"; break; }
    case JUBR_DEVICE_PIN_ERROR:     { errMsg = "JUBR_DEVICE_PIN_ERROR"; break; }
    case JUBR_USER_CANCEL:          { errMsg = "JUBR_USER_CANCEL"; break; }
    case JUBR_ERROR_ARGS:           { errMsg = "JUBR_ERROR_ARGS"; break; }
    case JUBR_PIN_LOCKED:           { errMsg = "JUBR_PIN_LOCKED"; break; }

    case JUBR_DEVICE_BUSY:          { errMsg = "JUBR_DEVICE_BUSY"; break; }
    case JUBR_TRANSACT_TIMEOUT:     { errMsg = "JUBR_TRANSACT_TIMEOUT"; break; }
    case JUBR_OTHER_ERROR:          { errMsg = "JUBR_OTHER_ERROR"; break; }
    case JUBR_CMD_ERROR:            { errMsg = "JUBR_CMD_ERROR"; break; }
    case JUBR_BT_BOND_FAILED:       { errMsg = "JUBR_BT_BOND_FAILED"; break; }

    //token errors
    case JUBR_UNKNOWN_COS_ERROR:        { errMsg = "JUBR_UNKNOWN_COS_ERROR"; break; }
    case JUBR_NOT_FOUND_MASTER_KEY_TYPE:{ errMsg = "JUBR_NOT_FOUND_MASTER_KEY_TYPE"; break; }
    case JUBR_NOT_FOUND_ECC_KEY_TYPE:   { errMsg = "JUBR_NOT_FOUND_ECC_KEY_TYPE"; break; }
    case JUBR_NOT_FOUND_ENTROPY_SIZE:   { errMsg = "JUBR_NOT_FOUND_ENTROPY_SIZE"; break; }
    case JUBR_WRONG_ENTROPY_SIZE:       { errMsg = "JUBR_WRONG_ENTROPY_SIZE"; break; }
    case JUBR_NOT_FOUND_MASTER_KEY_SIZE:{ errMsg = "JUBR_NOT_FOUND_MASTER_KEY_SIZE"; break; }
    case JUBR_WRONG_MASTER_KEY_SIZE:    { errMsg = "JUBR_WRONG_MASTER_KEY_SIZE"; break; }

    case JUBR_NOT_FOUND_PASS_PHRASE:     { errMsg = "JUBR_NOT_FOUND_PASS_PHRASE"; break; }
    case JUBR_NOT_FOUND_MNEMONICS:       { errMsg = "JUBR_NOT_FOUND_MNEMONICS"; break; }
    case JUBR_NOT_FOUND_MNMONICE_IN_DICT:{ errMsg = "JUBR_NOT_FOUND_MNMONICE_IN_DICT"; break; }
    case JUBR_MNOMENIC_LEN_OUT_OF_LIMIT: { errMsg = "JUBR_MNOMENIC_LEN_OUT_OF_LIMIT"; break; }
    case JUBR_ENTROPY_BITS_SIZE_MUST_BE_THE_TIMES_OF_EIGHT:{ errMsg = "JUBR_ENTROPY_BITS_SIZE_MUST_BE_THE_TIMES_OF_EIGHT"; break; }
    case JUBR_MNMONIC_WORD_COUNT_MUST_BE_TIMES_OF_THREE:   { errMsg = "JUBR_MNMONIC_WORD_COUNT_MUST_BE_TIMES_OF_THREE"; break; }
    case JUBR_NEED_TO_GENERATE_MNOMENIC_FIRST:{ errMsg = "JUBR_NEED_TO_GENERATE_MNOMENIC_FIRST"; break; }

    case JUBR_CLA_NOT_SUPPORTED:         { errMsg = "JUBR_CLA_NOT_SUPPORTED"; break; }
    case JUBR_WRONG_LENGTH:              { errMsg = "JUBR_WRONG_LENGTH"; break; }
    case JUBR_WRONG_OFFSET:              { errMsg = "JUBR_WRONG_OFFSET"; break; }
    case JUBR_INS_NOT_SUPPORTED:         { errMsg = "JUBR_INS_NOT_SUPPORTED"; break; }
    case JUBR_WRONG_P1P2:                { errMsg = "JUBR_WRONG_P1P2"; break; }
    case JUBR_WRONG_P3:                  { errMsg = "JUBR_WRONG_P3"; break; }

    case JUBR_FILE_INVALID:              { errMsg = "JUBR_FILE_INVALID"; break; }
    case JUBR_AUTHENTICATION_FAILED:     { errMsg = "JUBR_AUTHENTICATION_FAILED"; break; }
    case JUBR_NO_MESSAGE_SENT:           { errMsg = "JUBR_NO_MESSAGE_SENT"; break; }
    case JUBR_WRITE_NVM_FAILED:          { errMsg = "JUBR_WRITE_NVM_FAILED"; break; }
    case JUBR_COMMUNICATION_FAILED:      { errMsg = "JUBR_COMMUNICATION_FAILED"; break; }
    case JUBR_REFERENCE_KEY_NOT_FOUND:   { errMsg = "JUBR_REFERENCE_KEY_NOT_FOUND"; break; }
    case JUBR_FILE_TYPE_INCORRECT:       { errMsg = "JUBR_FILE_TYPE_INCORRECT"; break; }
    case JUBR_SECURITY_STATUS_NOT_SATIFIED:{ errMsg = "JUBR_SECURITY_STATUS_NOT_SATIFIED"; break; }
    case JUBR_AUTHENTICATION_BLOCK:      { errMsg = "JUBR_AUTHENTICATION_BLOCK"; break; }
    case JUBR_DATA_INVALID:              { errMsg = "JUBR_DATA_INVALID"; break; }
    case JUBR_CONDITIONS_NOT_SATISFIED:  { errMsg = "JUBR_CONDITIONS_NOT_SATISFIED"; break; }
    case JUBR_COMMAND_NOT_ALLOWED:       { errMsg = "JUBR_COMMAND_NOT_ALLOWED"; break; }
    case JUBR_MAC_INVALID:               { errMsg = "JUBR_MAC_INVALID"; break; }
    case JUBR_DATA_PARAMETER_INCORRECT:  { errMsg = "JUBR_DATA_PARAMETER_INCORRECT"; break; }

    case JUBR_FUNC_NOT_SUPPORTED:        { errMsg = "JUBR_FUNC_NOT_SUPPORTED"; break; }
    case JUBR_FILE_NOT_FOUND:            { errMsg = "JUBR_FILE_NOT_FOUND"; break; }
    case JUBR_RECORD_NOT_FOUNT:          { errMsg = "JUBR_RECORD_NOT_FOUNT"; break; }
    case JUBR_FILE_FULL:                 { errMsg = "JUBR_FILE_FULL"; break; }
    case JUBR_REFERENCE_DATA_NOT_FOUND:  { errMsg = "JUBR_REFERENCE_DATA_NOT_FOUND"; break; }
    case JUBR_FID_EXIST_ALREADY:         { errMsg = "JUBR_FID_EXIST_ALREADY"; break; }
    case JUBR_DFNAME_EXIST_ALREADY:      { errMsg = "JUBR_DFNAME_EXIST_ALREADY"; break; }
    case JUBR_KEY_INVALID:               { errMsg = "JUBR_KEY_INVALID"; break; }

    case JUBR_CUSTOM_DEFINED:            { errMsg = "JUBR_CUSTOM_DEFINED"; break; }
    case JUBR_EOS_APP_INDEP_OK:          { errMsg = "JUBR_EOS_APP_INDEP_OK"; break; }
    case JUBR_VERIFY_SIGN_FAILED:        { errMsg = "JUBR_VERIFY_SIGN_FAILED"; break; }
    case JUBR_BIO_FINGERPRINT_MODALITY_ERROR:{ errMsg = "JUBR_BIO_TIMEOUT"; break; }
    case JUBR_BIO_SPACE_LIMITATION:      { errMsg = "JUBR_BIO_SPACE_LIMITATION"; break; }
    case JUBR_BIO_TIMEOUT:               { errMsg = "JUBR_BIO_TIMEOUT"; break; }

    default:                        { errMsg = "UNKNOWN ERROR."; break; }
    }   // switch (rv) end

    return errMsg;
}

void error_exit(const char* message) {

    cout << message << endl;
    cout << "press any key to exit" << endl;
    char str[9] = { 0, };
    cin >> str;
    exit(0);
}

Json::Value readJSON(const char* json_file) {
    Json::CharReaderBuilder builder;
    Json::Value root;
    ifstream in(json_file, ios::binary);
    if (!in.is_open()) {
        error_exit("Error opening json file\n");
    }
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, in, &root, &errs)) {
        error_exit("Error parse json file\n");
    }

    return root;
}

int main() {

    while(true) {
        cout << "--------------------------------------" << endl;
        cout << "|******* Jubiter Wallet Test ********|" << endl;
        cout << "|  1. hardware_test.                 |" << endl;
#if SW
        cout << "|  2. software_test_btc.             |" << endl;
        cout << "| 60. software_test_eth.             |" << endl;
        cout << "|144. software_test_xrp.             |" << endl;
        cout << "|171. software_test_hcash.           |" << endl;
        cout << "|194. software_test_eos.             |" << endl;
        cout << "|195. software_test_trx.             |" << endl;
        cout << "|461. software_test_fil.             |" << endl;
#endif
        cout << "| 99. scp_test.                      |" << endl;
        cout << "|  0. exit.                          |" << endl;
        cout << "--------------------------------------" << endl;
        cout << "* Please enter your choice:" << endl;

        int choice = 0;
        cin >> choice;
        switch (choice) {
        case 1:
            main_test();
            break;
#if SW
        case 2:
            software_test_btc("json/testSoftware.json");
            break;
        case 60:
            software_test_eth("json/testSoftware.json", "json/testETH.json");
            break;
        case 144:
            software_test_xrp("json/testSoftware.json", "json/testXRP.json");
            break;
        case 171:
            software_test_hcash("json/testSoftware.json", "json/testHCash.json");
            break;
        case 194:
            software_test_eos("json/testSoftware.json", "json/testEOS.json");
            break;
        case 195:
            software_test_trx("json/testSoftware.json", "json/testTRX.json");
            break;
        case 461:
            software_test_fil("json/testFIL.json");
            break;
        case 99:
            scp11_test("settings/42584E46433230303532353030303031_apk.settings");
//            scp11_test("settings/42584E46433230303532353030303032_apk.settings");
            break;
#endif
        case 0:
            exit(0);
        default:
            continue;
        }   // switch (choice) end
    }   // while(true) end

    return 0;
}
