meta:
	ADDON_NAME = ofxHID
	ADDON_DESCRIPTION = An openFrameworks addon for direct HID access to USB devices.
	ADDON_AUTHOR = bakercp
	ADDON_MAINTAINER = bakercp
	ADDON_TAGS = "hid" "usb"
	ADDON_URL = http://github.com/bakercp/ofxHID
common:
	ADDON_DEPENDENCIES = ofxIO

linux64:
	# linux only, any library that should be included in the project using
	# pkg-config
	ADDON_PKG_CONFIG_LIBRARIES = libusb-1.0

linux:
	# linux only, any library that should be included in the project using
	# pkg-config
	ADDON_PKG_CONFIG_LIBRARIES = libusb-1.0

msys2:
	# any library that should be included in the project using pkg-config
	ADDON_PKG_CONFIG_LIBRARIES = libusb-1.0

linuxarmv6l:
	# linux only, any library that should be included in the project using
	# pkg-config
	ADDON_PKG_CONFIG_LIBRARIES = libusb-1.0

linuxarmv7l:
	# linux only, any library that should be included in the project using
	# pkg-config
	ADDON_PKG_CONFIG_LIBRARIES = libusb-1.0
	