#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define HIGH 1
#define LOW 0

#define IN 1
#define OUT 0

#define GPIOPIN14 14
#define GPIOPIN18 18
#define GPIOPIN23 23
#define GPIOPIN24 24


static int sysfs_gpio_get(int pin) {
	char buffer[3];
	char path[50];
	int fd;
	snprintf(path,50,"/sys/class/gpio/gpio%d/value",pin);
	fd = open(path,O_RDONLY);
	if(fd==-1) {
		printf("Could not open gpio value file");
	}
	read(fd,buffer,3);
	close(fd);
	return atoi(buffer);
}

static int sysfs_gpio_export(int pin) {
	char buffer[3];
	int length_written=0;
	int fd = open("/sys/class/gpio/export",O_WRONLY);
	if(fd==-1) {
		printf("Could not open gpio export file");
	}
	length_written=snprintf(buffer,3,"%d",pin);
	write(fd,buffer,length_written);
	close(fd);
	return 0;
}

static int sysfs_gpio_unexport(int pin) {
	char buffer[3];
	int length_written=0;
	int fd = open("/sys/class/gpio/unexport",O_WRONLY);
	if(fd==-1) {
		printf("Could not open gpio unexport file");
	}
	length_written=snprintf(buffer,3,"%d",pin);
	write(fd,buffer,length_written);
	close(fd);
	return 0;
}

static int sysfs_gpio_set_direction(int pin, int direction) {
	char path[50];
	int fd;
	snprintf(path,50,"/sys/class/gpio/gpio%d/direction",pin);
	// printf("%s\n",path);
	fd = open(path,O_WRONLY);
	if(fd==-1) {
		printf("Could not open gpio direction file");
	}
	if(direction==IN) {
		write(fd,"in\0",2);
	}
	if(direction==OUT) {
		write(fd,"out\0",3);
	}
	close(fd);
	return 0;
}

int match_states(int state_gpiopins[4],int temp_state_gpiopins[4]) {
	if(state_gpiopins[0]!=temp_state_gpiopins[0]) {
		return 0;
	}
	if(state_gpiopins[1]!=temp_state_gpiopins[1]) {
		return 0;
	}
	if(state_gpiopins[2]!=temp_state_gpiopins[2]) {
		return 0;
	}
	if(state_gpiopins[3]!=temp_state_gpiopins[3]) {
		return 0;
	}
	return 1;
}

int main() {
	// to store state of pins
	int state_gpiopins[4];
	int i=0;
	// gpio pins export
	sysfs_gpio_export(GPIOPIN14);
	sysfs_gpio_export(GPIOPIN24);
	sysfs_gpio_export(GPIOPIN18);
	sysfs_gpio_export(GPIOPIN23);
	usleep(5*100000);
	sysfs_gpio_set_direction(GPIOPIN14,IN);
	sysfs_gpio_set_direction(GPIOPIN24,IN);
	sysfs_gpio_set_direction(GPIOPIN18,IN);
	sysfs_gpio_set_direction(GPIOPIN23,IN);
	state_gpiopins[0]=sysfs_gpio_get(GPIOPIN14);
	state_gpiopins[1]=sysfs_gpio_get(GPIOPIN24);
	state_gpiopins[2]=sysfs_gpio_get(GPIOPIN18);
	state_gpiopins[3]=sysfs_gpio_get(GPIOPIN23);
	while(1) {
		int temp_state_gpiopins[4];
		temp_state_gpiopins[0]=sysfs_gpio_get(GPIOPIN14);
		temp_state_gpiopins[1]=sysfs_gpio_get(GPIOPIN24);
		temp_state_gpiopins[2]=sysfs_gpio_get(GPIOPIN18);
		temp_state_gpiopins[3]=sysfs_gpio_get(GPIOPIN23);
		if(!match_states(state_gpiopins,temp_state_gpiopins)) {
			printf("GPIOPIN14 state previous %d ",state_gpiopins[0]);
			state_gpiopins[0]=temp_state_gpiopins[0];
			printf("current %d\n",state_gpiopins[0]);
			printf("GPIOPIN24 state previous %d ",state_gpiopins[1]);
			state_gpiopins[1]=temp_state_gpiopins[1];
			printf("current %d\n",state_gpiopins[1]);
			printf("GPIOPIN18 state previous %d ",state_gpiopins[2]);
			state_gpiopins[2]=temp_state_gpiopins[2];
			printf("current %d\n",state_gpiopins[2]);
			printf("GPIOPIN23 state previous %d ",state_gpiopins[3]);
			state_gpiopins[3]=temp_state_gpiopins[3];
			printf("current %d\n",state_gpiopins[3]);
			// printf("state previous: ");
			// printf("GPIOPIN14 state previous %d current %d\n",temp_state_gpiopins[0],state_gpiopins[0]);
			// printf("GPIOPIN24 state previous %d current %d\n",temp_state_gpiopins[1],state_gpiopins[1]);
			// printf("GPIOPIN18 state previous %d current %d\n",temp_state_gpiopins[2],state_gpiopins[2]);
			// printf("GPIOPIN23 state previous %d current %d\n",temp_state_gpiopins[3],state_gpiopins[3]);
		}
		usleep(5*100000);	
	}
	return 0;
}
