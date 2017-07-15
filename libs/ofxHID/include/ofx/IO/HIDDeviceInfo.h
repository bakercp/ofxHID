//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofJson.h"
#include "ofTypes.h"


namespace ofx {
namespace IO {


/// \brief A class representing an HID device.
///
/// The class can be used a fully-defined descriptor or can be partially defined
/// in order to search for matching devices. Typically the HIDDeviceInfo will be
/// used for HIDDeviceUtils::listDevices*() functions.
class HIDDeviceInfo
{
public:
    /// \brief A typedef for a collection of HIDDeviceInfo objects.
    typedef std::vector<HIDDeviceInfo> DeviceList;

    /// \brief Create a partially defined HIDDeviceInfo with the given parameters.
    ///
    /// Partially defined HIDDeviceInfo object can be used to search for mathing
    /// devices.
    ///
    /// \param vendorId The Vendor ID, assigned by USB organization.
    /// \param productId The product ID, assigned by the manufactuer.
    /// \param serialNumber The product serial number.
    HIDDeviceInfo(uint16_t vendorId,
                  uint16_t productId,
                  const std::string serialNumber = UNDEFINED_SERIAL_NUMBER);

    /// \brief Create a partially defined HIDDeviceInfo with the given parameters.
    ///
    /// Partially defined HIDDeviceInfo object can be used to search for mathing
    /// devices.
    ///
    /// \param vendorId The Vendor ID, assigned by USB organization.
    /// \param productId The product ID, assigned by the manufactuer.
    /// \param usagePage The top level usage page.
    /// \param usage The top level usage.
    /// \param serialNumber The product serial number.
    HIDDeviceInfo(uint16_t vendorId,
                  uint16_t productId,
                  uint16_t usagePage,
                  uint16_t usage,
                  const std::string serialNumber = UNDEFINED_SERIAL_NUMBER);

    /// \brief Create a fully-defined HIDDeviceInfo with the given parameters.
    /// \param vendorId The Vendor ID, assigned by USB organization.
    /// \param productId The product ID, assigned by the manufactuer.
    /// \param serialNumber The product serial number.
    /// \param usagePage The top level usage page.
    /// \param usage The top level usage.
    /// \param manufacturer The manufacturer string.
    /// \param product The product string.
    /// \param path The platform-specific device path.
    /// \param interfaceNumber The interface number for composite devices.
    HIDDeviceInfo(uint16_t vendorId,
                  uint16_t productId,
                  const std::string serialNumber,
                  uint16_t usagePage,
                  uint16_t usage,
                  const std::string& manufacturer,
                  const std::string& product,
                  const std::string& path,
                  int interfaceNumber);

    /// \brief Destroy the HIDDeviceInfo.
    ~HIDDeviceInfo();

    /// \returns the Vendor ID, assigned by USB organization.
    uint16_t vendorId() const;

    /// \returns the product ID, assigned by the manufactuer.
    uint16_t productId() const;

    /// \returns the product serial number.
    std::string serialNumber() const;

    /// \returns the top level usage page.
    uint16_t usagePage() const;

    /// \brief returns the top level usage.
    uint16_t usage() const;

    /// \returns the manufacturer string.
    std::string manufacturer() const;

    /// \returns the product string.
    std::string product() const;

    /// \returns the platform-specific device path.
    std::string path() const;

    /// \returns the interface number for composite devices.
    int interfaceNumber() const;

    /// \returns the JSON representation of this object.
    ofJson toJSON() const;

    /// \returns the JSON representation of this object.
    static HIDDeviceInfo fromJSON(const ofJson& json);

    /// \brief Undefined vendor id value.
    static const uint16_t UNDEFINED_VENDOR_ID;

    /// \brief Undefined product id value.
    static const uint16_t UNDEFINED_PRODUCT_ID;

    /// \brief Undefined usage page value.
    static const uint16_t UNDEFINED_USAGE_PAGE;

    /// \brief Undefined usage value.
    static const uint16_t UNDEFINED_USAGE;

    /// \brief Undefined serial number value.
    static const std::string UNDEFINED_SERIAL_NUMBER;

    /// \brief Undefined manufacturer value.
    static const std::string UNDEFINED_MANUFACTURER;

    /// \brief Undefined product value.
    static const std::string UNDEFINED_PRODUCT;

    /// \brief Undefined path value.
    static const std::string UNDEFINED_PATH;

    /// \brief Undefined interface number.
    static const int UNDEFINED_INTERFACE_NUMBER;

private:
    /// \brief Vendor ID, assigned by USB organization.
    uint16_t _vendorId = UNDEFINED_VENDOR_ID;

    /// \brief Product ID, assigned by the manufactuer.
    uint16_t _productId = UNDEFINED_PRODUCT_ID;

    /// \brief Product serial number.
    std::string _serialNumber;

    /// \brief Top level usage page.
    uint16_t _usagePage = UNDEFINED_USAGE_PAGE;

    /// \brief Top level usage number.
    uint16_t _usage = UNDEFINED_USAGE;

    /// \brief The manufacturer.
    std::string _manufacturer;

    /// \brief Product string.
    std::string _product;

    /// \brief The platform-specific device path.
    std::string _path;

    /// \brief The interface number for composite devices.
    int _interfaceNumber = UNDEFINED_INTERFACE_NUMBER;

};


} } // namespace ofx::IO
