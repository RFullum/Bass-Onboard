# Bass-Onboard
A standalone plugin that will be used as onboard audio processing for my bass guitar on a Raspberry Pi.

A work in progress. The current idea is to feed the signal from the bass pickups directly into the 
Raspberry Pi via a ADC. The signal will be processed digitally within this app. Then out via stereo DAC.


## Probable/Possible Onboard Processing:

* Input Gain
* Noise Gate
* Compressor
* Waveshaper Distortion
* Foldback Distortion
* Bitcrush/Sample & Hold distortion
* Resonant Filtering
* Haas Widening
* Phaser
* Chorus
* Flanger
* Delay
* Hopefully some really bizarre shit, because there area already enough Phaser/Chorus/Flanger/Delay plugins in the world.


## Physical Interface Ideas

* bno055 Absolute Orientation sensor
  - Euler Orientation
  - Quaterion Orientation
  - Angular Velocity
  - Acceleration
  - Magnetic Field Strenght
  - Linear Acceleration
  - Gravity Vector
  - Temperature
* Touchscreen overlay XY positioning mounted on the bass
* Buttons & Knobs
  - Buttons or master knob choose active process
  - Knobs change color via LED based on active process and control parameters accordingly (e.g. Gain amount, dry/wet, cutoff, resonance, etc.)


## Audio Interface Ideas

* Basic HiFiBerry DAC + ADC Pro
  - Convert signal to digital and back to analog in one device, on bass
  - Stereo Output RCA (Unbalanced)
  - Easily recognized as audio card on the RasPi (Makes Input/Output in JUCE easy)
* USB 3 audio interface
  - Requires RasPi 4 (RasPi 3 is only USB 2. Not fast enough. Don't care what anyone says.)
  - Frees up GPIO pins for breakout interfacing (bno055, touchscreen, knobs and LEDs, etc)
  - Takes devices out of the "maker space" to consumer products. (Not that the HiFiBerry isn't already made by a company.)
  - Will probably be over-featured, over-priced, and too large for the application
  - Cheap & small interfaces usually sound and behave like they're cheap & smaell
* Create my own ADC input & separate analog or digital output
  - More work
  - More flexible
  - More Difficult to program for
  - Will OS recognize as Sound Card?
  - Getting the audio in and out of the Juce App if it doesn't recognize as sound card?
  - Having different sound card devices for input and output always gave me a hard time in Linux
* Wireless
  - RasPi already has wireless abilities. 
  - DAC into onboard Pi. Process. WiFi to another Pi with ADC.
  - Less cables in the studio or on stage.
  - Possible latency issues
* Ethernet
  - Audio over ethernet: fast audio data
  - Can only play into devices that have an ethernet system (i.e. Dante)
  - Possible power over ethernet for powering Pi + devices?
  - Ethernet jack will probably wear out too quickly
* HDMI
  - There are 1 or 2 HDMI ports depending on RasPi model
  - They're easily recognized by OS
  - That makes them easier to work with in JUCE
  - They're out-only. Having different in/out audio devices always gives me a hard time in Linux.


## Powering the rig

* Will need some sort of battery with enough juice to power the Pi plus breakouts, boards, devices, and LEDs for several hours.
* Will need a battery monitor script that will properly shut the RasPi down when battery is low
* Running a power cable along the audio cables would be a bad idea for a lot of reasons.


## Mounting, Routing, & Ports

* RasPi 
  - w/stacked audio card (HiFiBerry?) 
  - mounted in cutout inside body of bass
  - Cutout has clear panels so you can see through both sides
* bno055
  - Mounted inside body of bass
  - Covered cutout on back of bass
  - Wires drilled from cutout to RasPi cutout
* Touchscreen
  - Mounted on front of bass, above pickups where thumb can easily operate while still finger picking
  - Connector strip drilled into front of bass, with breakout inside cutout on back
  - Wires drilled from cutout to RasPi cutout
* Buttons and Knobs
  - Replace standard instrument pot knobs
  - Wires drilled from cavity cutout to RasPi cavity
* RasPi & Audio Ports
  - Stereo Output RCA jumper from RasPi to panel on bass.
  - HDMI port access from outside bass.
  - USB port access from outside bass.
  - Battery Charger port.
  
  
## This will all change many times as i come up with new ideas and run into roadblocks and limitations.
