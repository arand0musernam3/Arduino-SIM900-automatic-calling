# Automatic calling with Arduino + SIM900
This is a small script that has a simple objective:

Given a normally closed switch, when it is opened it will call three designated numbers under the `calls()` function.

It loads the necessary libraries and outputs lots of information via the serial port.

This might be useful for other projects where such information might be necessary.

**IMPORTANT**: The SIM attached to the SIM900 **must be** unlocked, IE. there must be no PIN locking.

The connections on the board are done as seen in the code. For the switch, digital pin 2 is used. It can be easily changed by changing the global variable.
