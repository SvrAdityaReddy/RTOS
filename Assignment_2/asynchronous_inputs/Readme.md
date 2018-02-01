# Asynchronous Inputs

Here Raspberry PI 2 B is used. GPIO pins used are GPIO 14, GPIO 18, GPIO 23, GPIO 24. The direction is set, values are read from these GPIO pins through sysfs interface. API's used are as follow

```{C}

int open(const char *pathname, int flags);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);

```

# PIN LAYOUT

![image](https://user-images.githubusercontent.com/19650574/35697066-2d0a1a9a-07af-11e8-92d8-2a4c6a2a4271.png)

# References

[1] [Man pages]() <br>
[2] [RPi GPIO Code Samples](https://elinux.org/RPi_GPIO_Code_Samples) <br>
[3] [Raspberry Pi GPIO Layout](https://www.raspberrypi-spy.co.uk/2012/06/simple-guide-to-the-rpi-gpio-header-and-pins/raspberry-pi-gpio-layout-model-b-plus-rotated-2700x900/#prettyPhoto/0/)
