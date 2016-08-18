# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# ISL290001
# This code is designed to work with the ISL290001_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# ISL290001 address, 0x44(68)
# Select command register
#		0x08(08)	ADC converts IDIODE1-IDIODE2 into 2’s-complement 16-bit data, 200ms per integration
data = [0x08]
i2c.write(0x44, data)

time.sleep(0.5)

# ISL290001 address, 0x44(68)
# Read data back from, 2 bytes
# luminance LSB, luminance MSB
data = i2c.readBytes(0x44, 0x00, 2)

# Convert the data
luminance = (((data[1] * 256) + data[0]) * 10000) / 32768

# Output data to screen
print "Ambient Light Luminance : %d lux" %luminance