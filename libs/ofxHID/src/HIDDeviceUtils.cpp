//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/HIDDeviceUtils.h"
#include "hidapi/hidapi.h"


namespace ofx {
namespace IO {


HIDDeviceInfo::DeviceList HIDDeviceUtils::listDevices()
{
    return listDevicesWithVendorAndProductIds(HIDDeviceInfo::UNDEFINED_VENDOR_ID,
                                              HIDDeviceInfo::UNDEFINED_PRODUCT_ID);
}


HIDDeviceInfo::DeviceList HIDDeviceUtils::listDevicesWithVendorId(uint16_t vendorId)
{
    return listDevicesWithVendorAndProductIds(vendorId,
                                              HIDDeviceInfo::UNDEFINED_PRODUCT_ID);
}


HIDDeviceInfo::DeviceList HIDDeviceUtils::listDevicesWithProductId(uint16_t productId)
{
    return listDevicesWithVendorAndProductIds(HIDDeviceInfo::UNDEFINED_VENDOR_ID,
                                              productId);
}


HIDDeviceInfo::DeviceList HIDDeviceUtils::listDevicesWithVendorAndProductIds(uint16_t vendorId,
                                                                             uint16_t productId)
{
    return HIDDeviceUtils::listDevicesWithInfo(HIDDeviceInfo(vendorId, productId));
}


HIDDeviceInfo::DeviceList HIDDeviceUtils::listDevicesWithInfo(const HIDDeviceInfo& info)
{
    HIDDeviceInfo::DeviceList deviceList;

    struct hid_device_info* devices = nullptr;
    struct hid_device_info* currentDevice = nullptr;

    // Enumerate matching devices.
    devices = hid_enumerate(info.vendorId(), info.productId());

    currentDevice = devices;

    while (currentDevice)
    {
#if defined(TARGET_OSX)
        // This is a hack for this issue https://github.com/signal11/hidapi/issues/326.
        if (currentDevice->interface_number == -1)
        {
            std::string _path = currentDevice->path;
            std::string _key = "IOUSBHostInterface@";
            std::size_t _n = _path.find(_key);
            if (_n != std::string::npos)
            {
                std::size_t _start = _n + _key.size();
                _n = _path.find("/", _start);
                if (_n != std::string::npos)
                {
                    currentDevice->interface_number = std::stoi(_path.substr(_start, _n - _start));
                }
            }
        }
#endif

        auto device = HIDDeviceInfo(currentDevice->vendor_id,
                                    currentDevice->product_id,
                                    toMultiByteString(currentDevice->serial_number),
                                    currentDevice->usage_page,
                                    currentDevice->usage,
                                    toMultiByteString(currentDevice->manufacturer_string),
                                    toMultiByteString(currentDevice->product_string),
                                    currentDevice->path,
                                    currentDevice->interface_number);

        if ((info.vendorId()     != HIDDeviceInfo::UNDEFINED_VENDOR_ID     && info.vendorId()     != device.vendorId())
        ||  (info.productId()    != HIDDeviceInfo::UNDEFINED_PRODUCT_ID    && info.productId()    != device.productId())
        ||  (info.serialNumber() != HIDDeviceInfo::UNDEFINED_SERIAL_NUMBER && info.serialNumber() != device.serialNumber())
        ||  (info.usagePage()    != HIDDeviceInfo::UNDEFINED_USAGE_PAGE    && info.usagePage()    != device.usagePage())
        ||  (info.usage()        != HIDDeviceInfo::UNDEFINED_USAGE         && info.usage()        != device.usage())
        ||  (info.manufacturer() != HIDDeviceInfo::UNDEFINED_MANUFACTURER  && info.manufacturer() != device.manufacturer())
        ||  (info.product()      != HIDDeviceInfo::UNDEFINED_PRODUCT       && info.product()      != device.product())
        ||  (info.interfaceNumber() != HIDDeviceInfo::UNDEFINED_INTERFACE_NUMBER && info.interfaceNumber() != device.interfaceNumber()))
        // Ignore the path, as it is platform-specific.
        {
            // Skip it.
        }
        else
        {
            deviceList.push_back(device);
        }

        currentDevice = currentDevice->next;
    }

    hid_free_enumeration(devices);
    
    return deviceList;
}


std::string HIDDeviceUtils::toMultiByteString(const wchar_t* input)
{
    if (input)
    {
        std::size_t inputSize = std::wcslen(input);

        if (inputSize > 0)
        {
            std::vector<char> output;
            output.resize(inputSize * 4);
            std::size_t size = std::wcstombs(output.data(), input, output.size());

            // Add zero termination in case our buffer wasn't long enough.
            if (size >= output.size())
            {
                ofLogError("HIDDeviceUtils::toMultiByteString") << "The converted size was >= to the buffer size, clamping.";
                output[output.size() - 1] = '\0';
            }

            return std::string(output.data(), size);
        }

        return std::string();

    }

    return std::string();
}


} } // namespace ofx::IO
