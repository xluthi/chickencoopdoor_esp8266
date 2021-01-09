# Automatic chicken coop door controlled by an ESP8266 #

The purpose of this project is to control a chicken coop door with an ESP8266.  The main features are:
  - It should open and close the door based on the time of the day (thanks to a real-time clock module) and a predefined pattern.
  - It should open and close the door based on the sunrise/sunset.
  - it supports MQTT to report status, update its configuration, or manually controlling the door.

Technically, it uses a DS1307 RTC module, a stepper motor, some stop contacts, saving of configuration in EEPROM...


The initial code is based on https://github.com/xluthi/pulse_counter_esp8266.


## MQTT ##

The following topics are defined (*my_hostname* is the ESP chipID (aka serial number) of the ESP8266):

1. house/hardware/ping_all
  * *Direction*: get
  * *answer*: house/hardware/ping_all/result: hostname of the ESP.
  * *Usage*:

    Specific topic that all hardware on the network must listen to and answer.
    It's a kind of discovery topic to have a view on active hardware.


2. house/hardware/my_hostname/do_reboot
  * *Direction*: set
  * *answer*: none
  * *payload*: none
  * *Usage*:

    Restart the ESP. It does not work after the first restart after serial flashing.
    However it works after manual reboot by power of RST switch.


3. house/hardware/my_hostname/do_upgrade
  * *direction*: set
  * *answer*: none
  * *payload*: the URL to download the firmware.
  * *Usage*:

     Launch firmware upgrade via HTTP download.  The payload is the HTTP URL to download the firmware.
     ! A priori, only HTTP works (no HTTPS)!


4. house/hardware/my_hostname/enable_mqtt_logs
  * *direction*: set
  * *answer*: none
  * *payload*: 0 --> disable log. Any other char --> enable logs
  * *usage*: Enable of disable MQTT verbose logs. Those are sent on house/hardware/my_hostname/log


5. house/hardware/my_hostname/get_config
  * *direction*: get
  * *answer*: Send on the log topic the following info: sensor topic, file compilation date and time, Wifi ssid
  * *payload*: none
  * *usage*: return some configuration and state information's


6. house/hardware/my_hostname/ctrl_led
    * *direction*: set
    * *answer*: none
    * *payload*: 0 -->Turn LED off.  Any other char --> turn the LED on.
    * *usage*: Test MQTT messaging by controlling builtin LED.

7. house/hardware/my_hostname/get_rtc
    * *direction*: get
    * *answer*: date&time,  e.g.: 2021-01-09 17:35:11
    * *payload*: none
    * *usage*: returns the current date & time from the RTC module.

8. house/hardware/my_hostname/set_rtc
    * *direction*: set
    * *answer*: none
    * *payload*: the date and time in the iso8601 format (e.g. 2020-06-25T15:29:37), without timezone info
    * *usage*: update the RTC module date and time.  On Linux, an easy way to generate the date & time with the correct format is `date +%Y-%m-%dT%T`.


## Compilation ##

In order to compile this sketch, you need a specific version of the PubSubClient: please download it on GitHub: https://github.com/xluthi/pubsubclient.

Before compiling, create a `private.h` file based on the provided `private_example.h` file: it should contain your Wifi settings, as well as the MQTT broker parameters.

The code contains a lot of debug statements. If those are not required, comment the `#define DEBUG` at the beginning of the main file.
