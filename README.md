rahhid
======

Radioactive@Home HID driver based on `libhidapi` (with simple [ThingSpeak](https://thingspeak.com/) support).

[![Travis-CI](https://travis-ci.org/burghardt/rahhid.svg?branch=master)](https://travis-ci.org/burghardt/rahhid/)
[![CircleCI](https://circleci.com/gh/burghardt/rahhid/tree/master.svg?style=svg)](https://circleci.com/gh/burghardt/rahhid)
[![Drone.IO](https://drone.io/github.com/burghardt/rahhid/status.png)](https://drone.io/github.com/burghardt/rahhid)
[![Coverity](https://scan.coverity.com/projects/6133/badge.svg)](https://scan.coverity.com/projects/6133)
[![CodeCov](http://codecov.io/github/burghardt/rahhid/coverage.svg?branch=master)](http://codecov.io/github/burghardt/rahhid/)

Live ThingSpeak demo
--------------------

[Skierniewice Geiger counter](https://thingspeak.com/channels/52967) channels is updated using `rahhid`.

How to build this program?
------------------------

Install `libhidapi-dev` (Debian/Ubuntu) or equivalent:
```
# apt-get update -qq
# apt-get install libhidapi-dev
```

Compile `rahhid` with:
```
# make
```

Sensor test
-----------
Run `rahid` without any arguments to measure for 30 seconds:
```
# ./rahhid
Switched LCD backlight off
Switched buzzer off
Reset counters... counting...
Clock: 29930, counts: 8
16.0374 CPM
0.0936765 microSv/h
16.0383 corrected CPM
0.0936815+-0.0331197 microSv/h
```

Uploading data to ThingSpeak
----------------------------
Supply API key as only argument to upload data to associated channel:

```
# ./rahhid "TS_API_KEY_HERE"
```

Use `cron` to upload data periodically:
```
# crontab -l
#m  h dom mon dow cmd
*/5 *  *   *   *  /usr/local/bin/rahhid "TS_API_KEY_HERE"
```

Building for OpenWRT
--------------------
Download [SDK package](http://wiki.openwrt.org/doc/howto/obtain.firmware.sdk) for your OpenWRT version. Download [hidapi package](https://github.com/openwrt/packages/tree/master/libs/hidapi) and put into
`package/hidapi`. Install `hidapi` library and headers into SDK with `make` command.

Now put `Makefile.openwrt` into `package/rahhid` directory and build `rahhid` with `make` command.

Install libusb (from OpenWRT repository) on target device with opkg:
```
# opkg install libusb-1.0
```

Finally install `hidapi_<version>_<arch>.ipk` and `rahhid_<version>_<arch>.ipk` on your OpenWRT device.
