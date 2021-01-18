# Slowpoke

Firmware for little 2 wheels robocar

For now, it is heavily inspired by the work of Miguel Grinberg [robot](https://blog.miguelgrinberg.com/post/building-an-arduino-robot-part-i-hardware-components)

### TODO:
 - [ ] stabilize HC-SR04 values - both HW & SW side (advanced filtering)
 - [ ] better power source (LiPO)
   - [ ] power distribution
 - [ ] smoother movement in environment (if possible with single ultrasonic)
   - [ ] optionaly add more sensors for sides readings
 - [ ] optical RPM measuring on motors
 - [ ] better DC motors
 - [ ] more customized chassis (3D printed)
 - [ ] continuously document (probably on wiki)
 
### Used HW:
- Arduino Duemilanove (older UNO) [info](https://www.arduino.cc/en/Main/arduinoBoardDuemilanove)
- HC-SR04 ultra sonic sensor [datasheet](https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)
- Motor driver shield L293D (clone of adafruit version) + screw shield (too access pins taken by the motor driver board)
- cheap DC motors(TT) with plastic gearing
