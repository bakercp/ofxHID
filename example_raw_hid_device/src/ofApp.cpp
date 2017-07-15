//
// Copyright (c) 2017 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#include "ofApp.h"


void ofApp::setup()
{
    auto devices = ofxIO::HIDDeviceUtils::listDevices();
//    auto devices = ofxIO::HIDDeviceUtils::listDevicesWithVendorAndProductIds(1266, 2361);
//    auto devices = ofxIO::HIDDeviceUtils::listDevicesWithVendorAndProductIds(1478, 61446);

    for (const auto& device: devices)
    {
        std::cout << device.toJSON().dump(4) << std::endl;

        ofxIO::HIDDevice _device;

        if (_device.setup(device))
        {
            std::cout << "Success." << std::endl;
        }
        else
        {
            std::cout << "Failed." << std::endl;
        }
    }



//    ofxIO::HIDDevice device;
//
//    if (device.setup(devices[2]))
//    {
//        std::cout << "Success." << std::endl;
//
//    }
//    else
//    {
//        std::cout << "Failed." << std::endl;
//    }

//    else



//
//    {
//        ofxIO::HIDDeviceInfo rawHID(0x16C0,
//                                    0x0486,
//                                    0xFFAB,
//                                    0x0200);
//
//        auto devices = ofxIO::HIDDeviceUtils::listDevicesWithInfo(rawHID);
//
//        for (const auto& device: devices)
//        {
//            std::cout << device.toJSON().dump(4) << std::endl;
//        }
//
//    }
//
//    std::cout << "--------------------------------" << std::endl;
//    {
//        ofxIO::HIDDeviceInfo rawHIDDebug(0x16C0,
//                                         0x0486,
//                                         0xFFC9,
//                                         0x0004);
//
//        ofxIO::HIDDevice device;
//
//    if (device.setup(rawHIDDebug))
//    {
//        std::cout << "Success." << std::endl;
//
//    }

//        auto devices = ofxIO::HIDDeviceUtils::listDevicesWithInfo(rawHIDDebug);
//
//        for (const auto& device: devices)
//        {
//            std::cout << device.toJSON().dump(4) << std::endl;
//        }
//    }
//

//    ofxIO::HIDDevice device;
//    device.setLogLevel(OF_LOG_VERBOSE);

//    ofxIO::HIDDevice::Settings settings;
//
//    settings.vendorId = 0x16C0;
//    settings.productId = 0x0486;
//    settings.serialNumber = "1735860";

//    settings.usagePage = 

    // Teensyduino RawHID
//    settings.usagePage = 0xFFAB;
//    settings.usage = 0x0200;

    // Teensyduino Debug RawHID
//    settings.usagePage = 0xFFC9;
//    settings.usage = 0x0004;

//    bool result = device.open(settings);


}

void ofApp::exit()
{
}


void ofApp::draw()
{

}
