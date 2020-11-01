///
/// \file SoapySDR/Registry.h
///
/// Device factory registration API for C vendor drivers.
///
/// \copyright
/// Copyright (c) 2020 Nicholas Corgan
/// SPDX-License-Identifier: BSL-1.0
///

#pragma once
#include <SoapySDR/Config.h>
#include <SoapySDR/Types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef SoapySDRKwargs*(*SoapySDRCDeviceFindFunc)(SoapySDRKwargs*, size_t*);
typedef void*(*SoapySDRCDeviceMakeFunc)(SoapySDRKwargs*);
typedef void(*SoapySDRCDeviceUnmakeFunc)(void*);

typedef char*(*SoapySDRCDeviceGetDriverKeyFunc)(void*);
typedef char*(*SoapySDRCDeviceGetHardwareKeyFunc)(void*);
typedef SoapySDRKwargs(*SoapySDRCDeviceGetHardwareInfoFunc)(void*);

typedef struct
{
    const char* driverName;

    SoapySDRCDeviceFindFunc find;
    SoapySDRCDeviceMakeFunc make;
    SoapySDRCDeviceUnmakeFunc unmake;

    SoapySDRCDeviceGetDriverKeyFunc getDriverKey;
    SoapySDRCDeviceGetHardwareKeyFunc getHardwareKey;
    SoapySDRCDeviceGetHardwareInfoFunc getHardwareInfo;
} SoapySDRDevice_CFunctions;

#define SOAPY_SDR_GET_DEVICE_FUNCTIONS SoapySDRRegistry_getDeviceFunctions

typedef SoapySDRDevice_CFunctions(*SoapySDRGetCDeviceFunctions)();

#ifdef __cplusplus
}
#endif
