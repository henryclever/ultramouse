ultramouse
==========

This is the code for the Ultramouse device as seen on youtube. It is currently used on the Arduino platform. 
Total length: 268 lines.
Here is the youtube video describing what it does:
https://www.youtube.com/watch?v=2kRi1g88mWI

The display is multiplexed: so be careful if you are going to modify anything if you build this because it has 
to run on a loop with continuous and fast timing to run the BCD decoder to keep the digital display lit properly. 
Always note the delays!

Be careful not to connect anything to pins 0 or 1 on the arduino because it uses them for a serial connection with
the Ultrasonic sensors.

Any questions? Let me know!
