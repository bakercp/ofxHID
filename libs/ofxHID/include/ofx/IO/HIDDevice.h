//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "hidapi/hidapi.h"
#include "ofConstants.h"
#include "ofLog.h"
#include "ofx/IO/HIDDeviceInfo.h"


namespace ofx {
namespace IO {


class HIDDevice
{
public:
    /// \brief Create a default HIDDevice.
    HIDDevice();

    /// \brief Create a HIDDevice with the given settings.
    ///
    /// If multiple matching devices are found, the first one will be chosen.
    ///
    /// An error will be logged on failure and the user can check to see if the
    /// device is open by calling isOpen().
    ///
    /// \param descriptor The descriptor to open.
    /// \param readTimeoutMillis The number of read timeout millis.
    HIDDevice(const HIDDeviceInfo& descriptor,
              uint64_t readTimeoutMillis);

    /// \brief Destroy the HIDDevice.
    virtual ~HIDDevice();

    /// \brief Open a new connection with the given settings.
    ///
    /// If multiple matching devices are found, the first one will be chosen.
    ///
    /// \param descriptor The descriptor to open.
    /// \returns true if successfully opened.
    bool setup(const HIDDeviceInfo& descriptor);

    /// \brief Close any open connection.
    void close();

    /// \returns true if a device is connected.
    bool isOpen() const;

    /// \brief Write an output report to the device using a report ID.
    ///
    /// Will send via the first OUT endpoint if it exists, otherwise it will use
    /// the first CONTROL endpoint (endpoint 0).
    ///
    /// \param reportId The numbered report id.
    /// \param reportData The report data to write.
    /// \returns the number of data bytes written, or -1 on error.
    std::streamsize writeReport(uint8_t reportId,
                                const std::vector<uint8_t>& reportData);

    /// \brief Write an output report using the default 0x00 report ID.
    ///
    /// Will send via the first OUT endpoint if it exists, otherwise it will use
    /// the first CONTROL endpoint (endpoint 0).
    ///
    /// \param reportData The report data to write.
    /// \returns the number of data bytes written, or -1 on error.
    std::streamsize writeReport(const std::vector<uint8_t>& reportData);

    /// \brief Write a feature report with the given report id.
    /// \param reportData The report data to write.
    /// \returns the number of data bytes written, equal to reportData.size() on success.
    std::streamsize writeFeatureReport(uint8_t reportId,
                                       const std::vector<uint8_t>& reportData);

    /// \brief Write a feature report with the default report id (0x00).
    /// \param reportData The report data to write.
    /// \returns the number of data bytes written, equal to reportData.size() on success.
    std::streamsize writeFeatureReport(const std::vector<uint8_t>& reportData);

    /// \brief Read the feature report for the given report id.
    ///
    /// On success, the reportData will be filled with the feature report data.
    /// On failure, an empty reportData vector will be presented and -1 will be
    /// Returned. In some cases the read will not fail, but no data will be
    /// returned. Failure is indicated by a return value of -1.
    ///
    /// \param reportId The report id to query.
    /// \param reportData A vector of data to be filled.
    /// \param readBufferSize The read buffer size.
    /// \returns the number of report data bytes read, or -1 on failure.
    std::streamsize readFeatureReport(uint8_t reportId,
                                      std::vector<uint8_t>& reportData,
                                      std::size_t readBufferSize = DEFAULT_READ_BUFFER_SIZE);

    /// \brief Read the default feature report.
    ///
    /// This queries the reportId == 0x00.
    ///
    /// On success, the reportData will be filled with the feature report data.
    /// On failure, an empty reportData vector will be presented and -1 will be
    /// Returned. In some cases the read will not fail, but no data will be
    /// returned. Failure is indicated by a return value of -1.
    ///
    /// \param reportData A vector of data to be filled.
    /// \param readBufferSize The read buffer size.
    /// \returns the number of report data bytes read, or -1 on failure.
    std::streamsize readFeatureReport(std::vector<uint8_t>& reportData,
                                      std::size_t readBufferSize = DEFAULT_READ_BUFFER_SIZE);


    /// \brief Read data from the HID device.
    ///
    /// Input reports are returned to the host through the INTERRUPT IN
    /// endpoint. The first byte will contain the Report number if the device
    /// uses numbered reports.
    ///
    /// \param buffer The buffer to fill.
    /// \param readBufferSize The read buffer size.
    /// \returns the number of bytes read.
    std::streamsize read(std::vector<uint8_t>& buffer,
                         std::size_t readBufferSize = DEFAULT_READ_BUFFER_SIZE);


    /// \brief Write data to the HID device.
    ///
    /// This will send the data on the first OUT endpoint, if one exists. If it
    /// does not, it will send the data through the Control Endpoint
    /// (Endpoint 0).
    ///
    /// \param reportId The report id to write.
    /// \param reportData The data to write.
    /// \returns the number of report data bytes written.
    std::streamsize write(uint8_t reportId, const std::vector<uint8_t>& reportData);

    /// \brief Set the read timeout in milliseconds.
    ///
    /// INIFINITE_TIMEOUT causes reads to block.
    ///
    /// \param readTimeoutMillis The number of read timeout millis.
    void setReadTimeoutMillis(uint64_t readTimeoutMillis);

    /// \returns the read timeout in milliseconds.
    uint64_t getReadTimeoutMillis() const;

    /// \brief Set the read packet size in number of bytes.
    /// \param size The packet size in number of bytes.
    void setReadPacketSize(std::size_t size);

    /// \returns the read packet size in number of bytes.
    std::size_t getReadPacketSize() const;

    /// \brief Set the write packet size in number of bytes.
    /// \param size The packet size in number of bytes.
    void setWritePacketSize(std::size_t size);

    /// \returns the write packet size in number of bytes.
    std::size_t getWritePacketSize() const;

    /// \brief The value for a blocking timeout.
    static const uint64_t INFINITE_TIMEOUT;

    /// \brief The default value for read timeout in milliseconds.
    static const uint64_t DEFAULT_READ_TIMEOUT;

    /// \brief The default read buffer size in bytes.
    static const std::size_t DEFAULT_READ_BUFFER_SIZE;

protected:
    /// \returns a pointer to the underlying HID device handle or nullptr if not connected.
    hid_device* device();

    /// \returns a const pointer to the underlying HID device handle or nullptr if not connected.
    const hid_device* device() const;

private:
    /// \brief The read timeout in milliseconds
    uint64_t _readTimeoutMillis = DEFAULT_READ_TIMEOUT;

//    /// \brief The write buffer, used for write operations.
//    std::vector<uint8_t> _writeBuffer;
//
//    /// \brief The read buffer, used for read operations.
//    std::vector<uint8_t> _readBuffer;

    /// \brief The HID device handle.
    hid_device* _deviceHandle = nullptr;

    /// \brief The HID device info.
    std::unique_ptr<HIDDeviceInfo> _deviceInfo = nullptr;

};


} } // namespace ofx::IO
