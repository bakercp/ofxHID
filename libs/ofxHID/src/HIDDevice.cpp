//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofx/IO/HIDDevice.h"
#include "ofx/IO/HIDDeviceUtils.h"
#include "ofUtils.h"


namespace ofx {
namespace IO {


const uint64_t HIDDevice::INFINITE_TIMEOUT = std::numeric_limits<uint64_t>::max();
const uint64_t HIDDevice::DEFAULT_READ_TIMEOUT = 200;
const std::size_t HIDDevice::DEFAULT_READ_BUFFER_SIZE = 1024;


HIDDevice::HIDDevice()
{
    hid_init();
}


HIDDevice::~HIDDevice()
{
    close();
    hid_exit();
}


bool HIDDevice::setup(const HIDDeviceInfo& descriptor)
{
    close();

    auto devices = HIDDeviceUtils::listDevicesWithInfo(descriptor);

    if (!devices.empty())
    {
        std::string path = devices[0].path();

        ofLogVerbose("HIDDevice::setup") << "Attempting to open: " << path;

        _deviceHandle = hid_open_path(path.data());

        if (_deviceHandle != nullptr)
        {
            _deviceInfo = std::make_unique<HIDDeviceInfo>(devices[0]);
            return true;
        }

        ofLogError("HIDDevice::setup") << "Unable to open: " << path;
    }

    return false;
}


void HIDDevice::close()
{
    if (_deviceHandle)
    {
        hid_close(_deviceHandle);
        _deviceHandle = nullptr;
    }
}


bool HIDDevice::isOpen() const
{
    return _deviceHandle != nullptr;
}


std::streamsize HIDDevice::writeReport(uint8_t reportId,
                                       const std::vector<uint8_t>& reportData)
{
    if (isOpen())
    {
        std::vector<uint8_t> data;
        data.reserve(reportData.size() + 1);
        data.insert(data.end(), reportId);
        data.insert(data.end(), reportData.begin(), reportData.end());
        return hid_write(_deviceHandle, data.data(), data.size());
    }

    ofLogError("HIDDevice::writeReport") << "No device is open.";
    return -1;

}


std::streamsize HIDDevice::writeReport(const std::vector<uint8_t>& reportData)
{
    return writeReport(0x00, reportData);
}


std::streamsize HIDDevice::writeFeatureReport(uint8_t reportId,
                                              const std::vector<uint8_t>& reportData)
{
    if (isOpen())
    {
        std::vector<uint8_t> data;
        data.reserve(reportData.size() + 1);
        data.insert(data.end(), reportId);
        data.insert(data.end(), reportData.begin(), reportData.end());
        return hid_send_feature_report(_deviceHandle, data.data(), data.size());
    }

    ofLogError("HIDDevice::writeFeatureReport") << "No device is open.";
    return -1;
}


std::streamsize HIDDevice::writeFeatureReport(const std::vector<uint8_t>& reportData)
{
    return writeFeatureReport(0x00, reportData);
}


std::streamsize HIDDevice::readFeatureReport(uint8_t reportId,
                                             std::vector<uint8_t>& reportData,
                                             std::size_t readBufferSize)
{
    if (isOpen())
    {
        // Clear the report data.
        reportData.clear();

        std::vector<uint8_t> data(readBufferSize);

        // Set the 0th element to the report id.
        data[0] = reportId;

        // Get the feature report.
        std::streamsize result = hid_get_feature_report(_deviceHandle,
                                                        data.data(),
                                                        data.size());

        if (result > -1)
        {
            // The hid api says this should be true.
            assert(result >= 1);

            std::streamsize reportLength = result - 1;

            if (reportLength > 0)
            {
                reportData.reserve(reportLength);
                reportData.insert(reportData.end(),
                                  data.begin() + 1,
                                  data.begin() + 1 + reportLength);
            }

            return reportLength;

        }

        return result;

    }

    ofLogError("HIDDevice::readFeatureReport") << "No device is open.";
    return -1;
}


std::streamsize HIDDevice::readFeatureReport(std::vector<uint8_t>& reportData,
                                             std::size_t readBufferSize)
{
    return readFeatureReport(0x00, reportData, readBufferSize);
}


std::streamsize HIDDevice::read(std::vector<uint8_t>& buffer,
                                std::size_t readBufferSize)
{
    if (isOpen())
    {
        buffer.resize(readBufferSize);

        std::streamsize result = hid_read_timeout(_deviceHandle,
                                                  buffer.data(),
                                                  buffer.size(),
                                                  int(_readTimeoutMillis == INFINITE_TIMEOUT ? -1 : _readTimeoutMillis));

        if (result > -1)
            buffer.resize(result);
        else
            buffer.clear();

        return result;
    }

    ofLogError("HIDDevice::read") << "No device is open.";
    return -1;
}


std::streamsize HIDDevice::write(uint8_t reportId,
                                 const std::vector<uint8_t>& reportData)
{
    if (isOpen())
    {
        std::vector<uint8_t> data;
        data.reserve(reportData.size() + 1);
        data.insert(data.end(), reportId);
        data.insert(data.end(), reportData.begin(), reportData.end());

        std::streamsize result = hid_write(_deviceHandle, data.data(), data.size());
        
        if (result > -1)
        {
            // The hid api says this should be true.
            assert(result >= 1);

            std::streamsize reportLength = result - 1;

            return reportLength;
            
        }

        return result;
    }
    
    ofLogError("HIDDevice::write") << "No device is open.";
    return -1;
}

    
void HIDDevice::setReadTimeoutMillis(uint64_t readTimeoutMillis)
{
    _readTimeoutMillis = readTimeoutMillis;
}


uint64_t HIDDevice::getReadTimeoutMillis() const
{
    return _readTimeoutMillis;
}


hid_device* HIDDevice::device()
{
    return _deviceHandle;
}


const hid_device* HIDDevice::device() const
{
    return _deviceHandle;
}


} } // namespace ofx::IO
