// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <SoapySDR/Device.hpp>

#include <SoapySDR/Registry.h>

namespace SoapySDR
{

class DeviceCVendorAPI: public Device
{
public:
    DeviceCVendorAPI(void* device, const SoapySDRDevice_CFunctions& driverFunctions);
    virtual ~DeviceCVendorAPI();

    std::string getDriverKey(void) const override;

    std::string getHardwareKey(void) const override;

    Kwargs getHardwareInfo(void) const override;

private:
    void* _device;
    SoapySDRDevice_CFunctions _driverFunctions;
};

}
