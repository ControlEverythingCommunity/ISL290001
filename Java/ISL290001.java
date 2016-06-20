// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ISL290001
// This code is designed to work with the ISL290001_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;
import java.text.DecimalFormat;
import java.text.NumberFormat;

public class ISL290001
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, ISL290001 I2C address is 0x44(68)
		I2CDevice device = Bus.getDevice(0x44);

		// Select command register
		// ADC converts IDIODE1-IDIODE2 into 2’s-complement 16-bit data, 200ms per integration
		device.write((byte)0x08);
		Thread.sleep(500);

		// Read data back, 2 bytes
		// luminance LSB, luminance MSB
		byte[] data=new byte[2];
		device.read(data, 0, 2);

		// Convert the data
		int luminance = ((((data[1] & 0xFF) * 256) + (data[0] & 0xFF)) * 10000) / 32768;

		// Output data to screen
		System.out.printf("Ambient Light luminance : %d lux %n", luminance);
	}
}
	