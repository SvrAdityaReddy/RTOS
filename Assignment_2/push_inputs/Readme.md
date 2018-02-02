# Push Inputs

Here Raspberry PI 2 B is used. GPIO pins used are GPIO 14, GPIO 18, GPIO 23, GPIO 24, GPIO 25. wiringPi library has been used to set direction to GPIO pins, detect interrupts through GPIO pins and to read data from GPIO pins. Arduino is made to act as a sensor and it's digital pins 2, 3, 4, 5, 6 to GPIO 14, GPIO 18, GPIO 23, GPIO 24, GPIO 25 respectively. Code of arduino to act as sensor is available in [arduino_push](https://github.com/SvrAdityaReddy/RTOS/tree/master/Assignment_2/push_inputs/arduino_push) directory. <br>
Below are the api's of wiringPi library used.

```{C}

void pinMode(int pin, int mode);
int digitalRead(int pin);
int wiringPiISR (int pin, int edgeType,  void (*function)(void)) ;

```

To compile the program do the following

```{sh}

$ gcc push_input.c -o push_input -lwiringPi

```

# Pin Layout with wiringPi mappings

![image](https://user-images.githubusercontent.com/19650574/35741154-0ed1d122-085d-11e8-9d10-140f14769e17.png)

# References

[1] [Core Functions](http://wiringpi.com/reference/core-functions/) <br>
[2] [Priority, Interrupts and Threads](http://wiringpi.com/reference/priority-interrupts-and-threads/) <br>
[3] [RPi GPIO Code Samples](https://elinux.org/RPi_GPIO_Code_Samples) <br>
[4] [Pins](http://wiringpi.com/pins/)
