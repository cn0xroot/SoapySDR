// Copyright (c) 2020 Nicholas Corgan
// SPDX-License-Identifier: BSL-1.0

#include <SoapySDR/Registry.hpp>

#include "DeviceCVendorAPI.hpp"
#include "TypeHelpers.hpp"

SoapySDR::DeviceCVendorAPI::DeviceCVendorAPI(void* device, const SoapySDRDevice_CFunctions& driverFunctions):
    _device(device),
    _driverFunctions(driverFunctions)
{
}

SoapySDR::DeviceCVendorAPI::~DeviceCVendorAPI()
{
    _driverFunctions.unmake(_device);
}

std::string SoapySDR::DeviceCVendorAPI::getDriverKey(void) const
{
    if(_driverFunctions.getDriverKey) return _driverFunctions.getDriverKey(_device);
    return SoapySDR::Device::getDriverKey();
}

std::string SoapySDR::DeviceCVendorAPI::getHardwareKey(void) const
{
    if(_driverFunctions.getHardwareKey) return _driverFunctions.getHardwareKey(_device);
    return SoapySDR::Device::getHardwareKey();
}

SoapySDR::Kwargs SoapySDR::DeviceCVendorAPI::getHardwareInfo(void) const
{
    if(_driverFunctions.getHardwareInfo)
    {
        auto hardwareInfoC = _driverFunctions.getHardwareInfo(_device);
        auto hardwareInfoCpp = toKwargs(&hardwareInfoC);
        SoapySDRKwargs_clear(&hardwareInfoC);

        return hardwareInfoCpp;
    }

    return SoapySDR::Device::getHardwareInfo();
}

//
// Registration
//

std::vector<SoapySDR::Kwargs> find_driverCVendorAPI(const SoapySDR::Kwargs& kwargs, const SoapySDRDevice_CFunctions& cFunctions)
{
    auto kwargsC = toKwargs(kwargs);

    size_t numDevices;
    auto* devsC = cFunctions.find(&kwargsC, &numDevices);
    auto devsCpp = toKwargsList(devsC, numDevices);

    SoapySDRKwargsList_clear(devsC, numDevices);
    SoapySDRKwargs_clear(&kwargsC);

    return devsCpp;
}

SoapySDR::Device* make_driverCVendorAPI(const SoapySDR::Kwargs& kwargs, const SoapySDRDevice_CFunctions& cFunctions)
{
    auto kwargsC = toKwargs(kwargs);
    auto* devC = cFunctions.make(&kwargsC);

    SoapySDRKwargs_clear(&kwargsC);

    return new SoapySDR::DeviceCVendorAPI(devC, cFunctions);
}
