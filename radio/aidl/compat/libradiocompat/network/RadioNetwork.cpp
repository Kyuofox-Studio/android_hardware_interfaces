/*
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <libradiocompat/RadioNetwork.h>

#include "commonStructs.h"
#include "debug.h"
#include "structs.h"
#include "utils.h"

#include "collections.h"

#define RADIO_MODULE "Network"

namespace android::hardware::radio::compat {

using ::aidl::android::hardware::radio::AccessNetwork;
using ::aidl::android::hardware::radio::RadioAccessFamily;
using ::ndk::ScopedAStatus;
namespace aidl = ::aidl::android::hardware::radio::network;
constexpr auto ok = &ScopedAStatus::ok;

ScopedAStatus RadioNetwork::getAllowedNetworkTypesBitmap(int32_t serial) {
    LOG_CALL << serial;
    if (mHal1_6) {
        mHal1_6->getAllowedNetworkTypesBitmap(serial);
    } else {
        mHal1_5->getPreferredNetworkType(serial);
    }
    return ok();
}

ScopedAStatus RadioNetwork::getAvailableBandModes(int32_t serial) {
    LOG_CALL << serial;
    mHal1_5->getAvailableBandModes(serial);
    return ok();
}

ScopedAStatus RadioNetwork::getAvailableNetworks(int32_t serial) {
    LOG_CALL << serial;
    mHal1_5->getAvailableNetworks(serial);
    return ok();
}

ScopedAStatus RadioNetwork::getBarringInfo(int32_t serial) {
    LOG_CALL << serial;
    mHal1_5->getBarringInfo(serial);
    return ok();
}

ScopedAStatus RadioNetwork::getCdmaRoamingPreference(int32_t serial) {
    LOG_CALL << serial;
    mHal1_5->getCdmaRoamingPreference(serial);
    return ok();
}

ScopedAStatus RadioNetwork::getCellInfoList(int32_t serial) {
    LOG_CALL << serial;
    mHal1_5->getCellInfoList(serial);
    return ok();
}

ScopedAStatus RadioNetwork::getDataRegistrationState(int32_t serial) {
    LOG_CALL << serial;
    mHal1_5->getDataRegistrationState(serial);
    return ok();
}

ScopedAStatus RadioNetwork::getImsRegistrationState(int32_t serial) {
    LOG_CALL << serial;
    mHal1_5->getImsRegistrationState(serial);
    return ok();
}

ScopedAStatus RadioNetwork::getNetworkSelectionMode(int32_t serial) {
    LOG_CALL << serial;
    mHal1_5->getNetworkSelectionMode(serial);
    return ok();
}

ScopedAStatus RadioNetwork::getOperator(int32_t serial) {
    LOG_CALL << serial;
    mHal1_5->getOperator(serial);
    return ok();
}

ScopedAStatus RadioNetwork::getSignalStrength(int32_t serial) {
    LOG_CALL << serial;
    mHal1_5->getSignalStrength(serial);
    return ok();
}

ScopedAStatus RadioNetwork::getSystemSelectionChannels(int32_t serial) {
    LOG_CALL << serial;
    if (mHal1_6) {
        mHal1_6->getSystemSelectionChannels(serial);
    } else {
        respond().getSystemSelectionChannelsResponse(notSupported(serial), {});
    }
    return ok();
}

ScopedAStatus RadioNetwork::getVoiceRadioTechnology(int32_t serial) {
    LOG_CALL << serial;
    mHal1_5->getVoiceRadioTechnology(serial);
    return ok();
}

ScopedAStatus RadioNetwork::getVoiceRegistrationState(int32_t serial) {
    LOG_CALL << serial;
    mHal1_5->getVoiceRegistrationState(serial);
    return ok();
}

ScopedAStatus RadioNetwork::isNrDualConnectivityEnabled(int32_t serial) {
    LOG_CALL << serial;
    if (mHal1_6) {
        mHal1_6->isNrDualConnectivityEnabled(serial);
    } else {
        respond().isNrDualConnectivityEnabledResponse(notSupported(serial), false);
    }
    return ok();
}

ScopedAStatus RadioNetwork::responseAcknowledgement() {
    LOG_CALL;
    mHal1_5->responseAcknowledgement();
    return ok();
}

ScopedAStatus RadioNetwork::setAllowedNetworkTypesBitmap(int32_t serial, RadioAccessFamily ntype) {
    LOG_CALL << serial;
    const auto raf = toHidlBitfield<V1_4::RadioAccessFamily>(ntype);
    if (mHal1_6) {
        mHal1_6->setAllowedNetworkTypesBitmap(serial, raf);
    } else {
        mHal1_5->setPreferredNetworkType(serial, getNetworkTypeFromRaf(raf));
    }
    return ok();
}

ScopedAStatus RadioNetwork::setBandMode(int32_t serial, aidl::RadioBandMode mode) {
    LOG_CALL << serial;
    mHal1_5->setBandMode(serial, V1_0::RadioBandMode(mode));
    return ok();
}

ScopedAStatus RadioNetwork::setBarringPassword(int32_t serial, const std::string& facility,
                                               const std::string& oldPw, const std::string& newPw) {
    LOG_CALL << serial;
    mHal1_5->setBarringPassword(serial, facility, oldPw, newPw);
    return ok();
}

ScopedAStatus RadioNetwork::setCdmaRoamingPreference(int32_t serial, aidl::CdmaRoamingType type) {
    LOG_CALL << serial;
    mHal1_5->setCdmaRoamingPreference(serial, V1_0::CdmaRoamingType(type));
    return ok();
}

ScopedAStatus RadioNetwork::setCellInfoListRate(int32_t serial, int32_t rate) {
    LOG_CALL << serial;
    mHal1_5->setCellInfoListRate(serial, rate);
    return ok();
}

ScopedAStatus RadioNetwork::setIndicationFilter(int32_t serial, aidl::IndicationFilter indFilter) {
    LOG_CALL << serial;
    mHal1_5->setIndicationFilter(serial, toHidlBitfield<V1_0::IndicationFilter>(indFilter));
    return ok();
}

ScopedAStatus RadioNetwork::setLinkCapacityReportingCriteria(  //
        int32_t serial, int32_t hysteresisMs, int32_t hysteresisDlKbps, int32_t hysteresisUlKbps,
        const std::vector<int32_t>& thrDownlinkKbps, const std::vector<int32_t>& thrUplinkKbps,
        AccessNetwork accessNetwork) {
    LOG_CALL << serial;
    mHal1_5->setLinkCapacityReportingCriteria(  //
            serial, hysteresisMs, hysteresisDlKbps, hysteresisUlKbps, thrDownlinkKbps,
            thrUplinkKbps, V1_2::AccessNetwork(accessNetwork));
    return ok();
}

ScopedAStatus RadioNetwork::setLocationUpdates(int32_t serial, bool enable) {
    LOG_CALL << serial;
    mHal1_5->setLocationUpdates(serial, enable);
    return ok();
}

ScopedAStatus RadioNetwork::setNetworkSelectionModeAutomatic(int32_t serial) {
    LOG_CALL << serial;
    mHal1_5->setNetworkSelectionModeAutomatic(serial);
    return ok();
}

ScopedAStatus RadioNetwork::setNetworkSelectionModeManual(  //
        int32_t serial, const std::string& opNumeric, AccessNetwork ran) {
    LOG_CALL << serial;
    mHal1_5->setNetworkSelectionModeManual_1_5(serial, opNumeric, V1_5::RadioAccessNetworks(ran));
    return ok();
}

ScopedAStatus RadioNetwork::setNrDualConnectivityState(int32_t serial,
                                                       aidl::NrDualConnectivityState st) {
    LOG_CALL << serial;
    if (mHal1_6) {
        mHal1_6->setNrDualConnectivityState(serial, V1_6::NrDualConnectivityState(st));
    } else {
        respond().setNrDualConnectivityStateResponse(notSupported(serial));
    }
    return ok();
}

ScopedAStatus RadioNetwork::setResponseFunctions(
        const std::shared_ptr<aidl::IRadioNetworkResponse>& networkResponse,
        const std::shared_ptr<aidl::IRadioNetworkIndication>& networkIndication) {
    LOG_CALL << networkResponse << ' ' << networkIndication;

    CHECK(networkResponse);
    CHECK(networkIndication);

    mRadioResponse->setResponseFunction(networkResponse);
    mRadioIndication->setResponseFunction(networkIndication);

    return ok();
}

ScopedAStatus RadioNetwork::setSignalStrengthReportingCriteria(
        int32_t serial, const std::vector<aidl::SignalThresholdInfo>& infos) {
    LOG_CALL << serial;
    // TODO(b/203699028): how about other infos?
    mHal1_5->setSignalStrengthReportingCriteria_1_5(serial, toHidl(infos[0]),
                                                    V1_5::AccessNetwork(infos[0].ran));
    return ok();
}

ScopedAStatus RadioNetwork::setSuppServiceNotifications(int32_t serial, bool enable) {
    LOG_CALL << serial;
    mHal1_5->setSuppServiceNotifications(serial, enable);
    return ok();
}

ScopedAStatus RadioNetwork::setSystemSelectionChannels(  //
        int32_t serial, bool specifyCh, const std::vector<aidl::RadioAccessSpecifier>& specifiers) {
    LOG_CALL << serial;
    mHal1_5->setSystemSelectionChannels_1_5(serial, specifyCh, toHidl(specifiers));
    return ok();
}

ScopedAStatus RadioNetwork::startNetworkScan(int32_t serial, const aidl::NetworkScanRequest& req) {
    LOG_CALL << serial;
    mHal1_5->startNetworkScan_1_5(serial, toHidl(req));
    return ok();
}

ScopedAStatus RadioNetwork::stopNetworkScan(int32_t serial) {
    LOG_CALL << serial;
    mHal1_5->stopNetworkScan(serial);
    return ok();
}

ScopedAStatus RadioNetwork::supplyNetworkDepersonalization(int32_t ser, const std::string& nPin) {
    LOG_CALL << ser;
    mHal1_5->supplyNetworkDepersonalization(ser, nPin);
    return ok();
}

// TODO(b/210498497): is there a cleaner way to send a response back to Android, even though these
// methods must never be called?
ScopedAStatus RadioNetwork::setUsageSetting(
        int32_t ser, ::aidl::android::hardware::radio::network::UsageSetting) {
    LOG_CALL << ser;
    LOG(ERROR) << "setUsageSetting is unsupported by HIDL HALs";
    return ok();
}

ScopedAStatus RadioNetwork::getUsageSetting(int32_t ser) {
    LOG_CALL << ser;
    LOG(ERROR) << "getUsageSetting is unsupported by HIDL HALs";
    return ok();
}

}  // namespace android::hardware::radio::compat