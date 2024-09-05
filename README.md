# Interpolation_Mapper
This is a value interpolation algorithm, it is made for Arduino Nano because it supports 5V, but you can use any other board. It is important to respect the bit depth of the input and output signal, or you need to add a conversion factor to the algorithm if the bit depth does not match.

And I used it to make the throttle control curve on the electric scooter smoother, it uses an analog throttle control signal with a maximum level of 5V, but you can apply it for any other purpose.

The project is made in CLion and Platformio, but you can copy the code to any other development environment.