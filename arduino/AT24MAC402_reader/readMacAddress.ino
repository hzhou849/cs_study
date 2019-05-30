/*
  Arduino Sketch that demonstrates reading the factory-programmed
  EUI-48 MAC Address from a AT24MAC402 / AT24MAC602 Serial EEPROM
  over TWI / I2C.
 
  Product page: http://www.atmel.com/devices/AT24MAC402.aspx
  Datasheet: http://www.atmel.com/images/atmel-8807-seeprom-at24mac402-602-datasheet.pdf
 */

#include <Wire.h>

// This will be filled in with the actual MAC address
static byte mymac[] = { 0x00,0x00,0x00,0x00,0x00,0x00 };



void setup() {
  // Start serial communication
  Serial.begin(9600);
  Serial.println("Going to read MAC...");

  // Start I2C com54munication
  Wire.begin();

  // Read the MAC address parts from the EEPROM into mymac
  readMacAddress(0x0, mymac);

  // Display the result
  Serial.print("MAC: ");
  for (byte i = 0; i < 6; ++i) {
    Serial.print(mymac[i], HEX);
    if (i < 5)
      Serial.print(':');
  }
  Serial.println();
}


void loop() {
}


// Function to read the MAC address from a AT24MAC402 EEPROM
//
// address: the 3-bit address assinged to the EEPROM (using the A0 A1 A2 pins)
// macaddr: a pointer to 6 bytes of memory
//
/* The Slave address is 3 bits form a0 a1 a2 
 * by or masking the last three bits we can address the slave devices
 * ie 0x58 (is device address)
 * 0x58 =    0101 1000
 * OR last 3 bits  000 ---> 0101 1000 (no change)
 * OR last 3 bits  001 ---> 0101 1001 == 0x59
 * */


void readMacAddress(byte address, byte macaddr[]) {
  int i2c_address = 0x58 | address;
	Serial.print(address); // see that the value of address is.
  // Tell the EEPROM where we would like to read from
  Wire.beginTransmission(i2c_address);
  Wire.write(0x9A); // Location of the EUI-48
  Wire.endTransmission();

  // Now read 6 bytes from that memory address
  Wire.requestFrom(i2c_address, 6);
  for(byte i=0; i<6; i++) {
    macaddr[i] = Wire.read();
  }
}
