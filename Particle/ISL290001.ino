// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ISL290001
// This code is designed to work with the ISL290001_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <application.h>
#include <spark_wiring_i2c.h>

// ISL290001 I2C address is 0x44(68)
#define Addr 0x44

int luminance;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "ISL290001");
  Particle.variable("luminance", luminance);

  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select command register
  // ADC converts IDIODE1-IDIODE2 into 2’s-complement 16-bit data, 200ms per integration
  Wire.write(0x08);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data[2];

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // luminance lsb, luminance msb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data
  luminance = (((data[1] * 256) + data[0]) * 10000) / 32768;

  // Output data to dashboard
  Particle.publish("Ambient Light luminance :", String(luminance));
  delay(300);
}

