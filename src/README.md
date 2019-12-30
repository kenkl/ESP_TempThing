# ESP_TempThing

An ESP8266 with a Dallas DS18B20 digital temperature sensor, providing the reading over a simple RESTful (JSON) web call. This is the ESP1 temperature source seen in [gettemp](https://github.com/kenkl/gettemp) and [gettemp2](https://github.com/kenkl/gettemp). 

29-Dec-2019: This is my initial publishing (to GitHub) of years-old code, originally constructed in the Arduino IDE (don't judge me). It was later moved over to PlatformIO (the standalone Atom IDE). Now, some more years later, it lives in VSC (still using PlatformIO), and is finally (as hinted at in the gettemp projects) published to GitHub.  

 I was keeping a kind of changelog at the top of the main sourcefile, and it doesn't really belong there any more. Until I decide whether I care enough to keep any of its history (probably not), I'll keep it here...

```
// v1.0.0 - Initial play with the HelloServer sample. Add a handleToggle to control an LED with RESTful calls
// v1.0.0 - Forking off HelloServer to create an ESP8266-based thermometer thing to send JSON data from DS18B20
//           Initial steps - ensure that OneWire and DallasTemperature are usable on the ESP
//           and simply return a number that makes sense.
// v1.0.1 - JSON was *too* simple to wire up. Let's double-tap the sensor. I remember that being A Thing at one point.
//           todo: not much... clean up the cruft -serial jabber and strip comments that don't mean much in a functional
//           bit of code. Wire up a watchdog/periodic reboot, maybe.
// v1.0.2 - Let's add handlers for discrete LEDon and LEDoff so it can be more intellegently toggled from a
//           remote entity (initially Raspi running navi_pilot.py)
// v1.0.3 - Very similar to 102 - changing the mDNS name (esp3)
// v1.0.4 - Just getting Curie (new MacBook Air) to understand the Huzzah module. Let's change the personality to esp4
// v1.0.5 - Actully, let's not change the personality. Going back to esp1. Also, adding some things for the serial monitor to see.
```

I'm planning to build a couple more of these, and I'll be adding a Fritzing file to describe the hookup of this thing (it's actually pretty simple, really), and cleaning up the code a little. For now, I was so happy to have (finally) found this code (squirreled away on an old laptop), I figured I should post it before it got more permanently lost. 

