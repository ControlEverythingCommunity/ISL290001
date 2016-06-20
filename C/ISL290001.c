// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ISL290001
// This code is designed to work with the ISL290001_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, ISL290001 I2C address is 0x44(68)
	ioctl(file, I2C_SLAVE, 0x44);

	// Select command register
	// ADC converts IDIODE1-IDIODE2 into 2’s-complement 16-bit data, 200ms per integration(0x08)
	char config[1] = {0x08};
	write(file, config, 1);
	sleep(1);

	// Read data back, 2 bytes
	// luminance LSB, luminance MSB
	char data[2] = {0};
	if(read(file, data, 2) != 2)
	{
		printf("Erorr : Input/output Erorr \n");
		exit(1);
	}
	else
	{
		// Convert the data
		int luminance = ((data[1] * 256 + data[0]) * 10000) / 32768;

		// Output data to screen
		printf("Ambient Light luminance : %d lux \n", luminance);
	}
}
