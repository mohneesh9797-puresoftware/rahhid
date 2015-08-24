rahhid
======

Radioactive@Home HID driver based on `libhidapi` (with simple [ThingSpeak](https://thingspeak.com/) support).

Live ThingSpeak demo
--------------------

[Skierniewice Geiger counter](https://thingspeak.com/channels/52967) channels is updated using `rahhid`.

How to build this program?
------------------------

1. Install `libhidapi-dev` (Debian/Ubuntu) or equivalent:
```
# apt-get update -qq
# apt-get install libhidapi-dev
```

2. Compile `rahhid` with:
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
