//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/HIDDeviceInfo.h"
#include "ofUtils.h"


namespace ofx {
namespace IO {


const uint16_t HIDDeviceInfo::UNDEFINED_VENDOR_ID = 0x00;
const uint16_t HIDDeviceInfo::UNDEFINED_PRODUCT_ID = 0x00;
const uint16_t HIDDeviceInfo::UNDEFINED_USAGE_PAGE = std::numeric_limits<uint16_t>::max();
const uint16_t HIDDeviceInfo::UNDEFINED_USAGE = std::numeric_limits<uint16_t>::max();
const std::string HIDDeviceInfo::UNDEFINED_SERIAL_NUMBER = "UNDEFINED_SERIAL_NUMBER";
const std::string HIDDeviceInfo::UNDEFINED_MANUFACTURER = "UNDEFINED_MANUFACTURER";
const std::string HIDDeviceInfo::UNDEFINED_PRODUCT = "UNDEFINED_PRODUCT";
const std::string HIDDeviceInfo::UNDEFINED_PATH = "UNDEFINED_PATH";
const int HIDDeviceInfo::UNDEFINED_INTERFACE_NUMBER = -1;


HIDDeviceInfo::HIDDeviceInfo(uint16_t vendorId,
                             uint16_t productId,
                             const std::string serialNumber):
    HIDDeviceInfo(vendorId,
                  productId,
                  UNDEFINED_USAGE_PAGE,
                  UNDEFINED_USAGE,
                  serialNumber)
{
}


HIDDeviceInfo::HIDDeviceInfo(uint16_t vendorId,
                             uint16_t productId,
                             uint16_t usagePage,
                             uint16_t usage,
                             const std::string serialNumber):
    HIDDeviceInfo(vendorId,
                  productId,
                  serialNumber,
                  usagePage,
                  usage,
                  UNDEFINED_MANUFACTURER,
                  UNDEFINED_PRODUCT,
                  UNDEFINED_PATH,
                  UNDEFINED_INTERFACE_NUMBER)
{
}


HIDDeviceInfo::HIDDeviceInfo(uint16_t vendorId,
                             uint16_t productId,
                             const std::string serialNumber,
                             uint16_t usagePage,
                             uint16_t usage,
                             const std::string& manufacturer,
                             const std::string& product,
                             const std::string& path,
                             int interfaceNumber):
    _vendorId(vendorId),
    _productId(productId),
    _serialNumber(serialNumber),
    _usagePage(usagePage),
    _usage(usage),
    _manufacturer(manufacturer),
    _product(product),
    _path(path),
    _interfaceNumber(interfaceNumber)
{
}


HIDDeviceInfo::~HIDDeviceInfo()
{
}


uint16_t HIDDeviceInfo::vendorId() const
{
    return _vendorId;
}


uint16_t HIDDeviceInfo::productId() const
{
    return _productId;
}


std::string HIDDeviceInfo::serialNumber() const
{
    return _serialNumber;
}


uint16_t HIDDeviceInfo::usagePage() const
{
    return _usagePage;
}


uint16_t HIDDeviceInfo::usage() const
{
    return _usage;
}


std::string HIDDeviceInfo::manufacturer() const
{
    return _manufacturer;
}


std::string HIDDeviceInfo::product() const
{
    return _product;
}


std::string HIDDeviceInfo::path() const
{
    return _path;
}


int HIDDeviceInfo::interfaceNumber() const
{
    return _interfaceNumber;
}


ofJson HIDDeviceInfo::toJSON() const
{
    ofJson json;
    json["vendor_id"] = _vendorId;
    json["product_id"] = _productId;
    json["serial_number"] = _serialNumber;
    json["usage_page"] = _usagePage;
    json["usage"] = _usage;
    json["manufacturer"] = _manufacturer;
    json["product"] = _product;
    json["path"] = _path;
    json["interface_number"] = _interfaceNumber;
    return json;
}


HIDDeviceInfo HIDDeviceInfo::fromJSON(const ofJson& json)
{
    return HIDDeviceInfo(json.value("vendor_id", UNDEFINED_VENDOR_ID),
                         json.value("product_id", UNDEFINED_PRODUCT_ID),
                         json.value("serial_number", UNDEFINED_SERIAL_NUMBER),
                         json.value("usage_page", UNDEFINED_USAGE_PAGE),
                         json.value("usage", UNDEFINED_USAGE),
                         json.value("manufacturer", UNDEFINED_MANUFACTURER),
                         json.value("product", UNDEFINED_PRODUCT),
                         json.value("path", UNDEFINED_PATH),
                         json.value("interface_number", UNDEFINED_INTERFACE_NUMBER));
}


} } // namespace ofx::IO
