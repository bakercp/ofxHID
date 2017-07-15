//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofx/IO/HIDDeviceInfo.h"


namespace ofx {
namespace IO {


/// \brief A collection of utilities for interacting with HID devices.
class HIDDeviceUtils
{
public:
    /// \brief List all available HID devices.
    /// \returns a list of matching devices.
    static HIDDeviceInfo::DeviceList listDevices();

    /// \brief List all available HID devices matching a vendor id.
    /// \param vendorId The vendor identification number.
    /// \returns a list of matching devices.
    static HIDDeviceInfo::DeviceList listDevicesWithVendorId(uint16_t vendorId);

    /// \brief List all available HID devices matching a product id.
    /// \param productId The product identification number.
    /// \returns a list of matching devices.
    static HIDDeviceInfo::DeviceList listDevicesWithProductId(uint16_t productId);

    /// \brief List all available HID devices matching vendor and product ids.
    /// \param productId The product identification number.
    /// \param vendorId The vendor identification number.
    /// \returns a list of matching devices.
    static HIDDeviceInfo::DeviceList listDevicesWithVendorAndProductIds(uint16_t vendorId,
                                                                        uint16_t productId);
    
    /// \brief List all available HID devices matching the given HIDDeviceInfo.
    ///
    /// Will match all set elements of the HIDDeviceInfo, with the exception of
    /// the platform specific path.
    ///
    /// \returns a list of matching devices, or none if matching failed.
    static HIDDeviceInfo::DeviceList listDevicesWithInfo(const HIDDeviceInfo& info);

    /// \brief Convert a wchar_t string to a multi-byte string.
    ///
    /// This will typically result in a UTF8-encoded string if the user's locale
    /// is set to use UTF-8.
    ///
    /// \param input The wchar_t string input.
    static std::string toMultiByteString(const wchar_t* input);

};


} } // namespace ofx::IO
