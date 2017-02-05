#include <wirish/wirish.h>
#include <wirish/boards.h>

#include "AS5048A.h"
#include <wirish/boards.h>




//#define AS5048A_DEBUG

/**
 * Constructor
 */
AS5048A::AS5048A(byte arg_cs){
	_cs = arg_cs;
	errorFlag = false;
	position = 0;

	//setup pins
	pinMode(_cs,OUTPUT);

}


/**
 * Initialiser
 * Sets up the SPI interface
 */
void AS5048A::init()
{
		
		spi.begin(SPI_18MHZ, MSBFIRST, 0);
	// SPI.setDataMode(SPI_MODE1);
	// SPI.setClockDivider(SPI_CLOCK_DIV32); //64);
	// SPI.setBitOrder(MSBFIRST);
	// SPI.begin();
}

/**
 * Closes the SPI connection
 */
void AS5048A::close()
{
	spi.end();
}

/**
 * Utility function used to calculate even parity of uint32
 */
byte AS5048A::spiCalcEvenParity(uint32 value)
{
	byte cnt = 0;
	byte i;

	for (i = 0; i < 16; i++)
	{
		if (value & 0x1)
		{
			cnt++;
		}
		value >>= 1;
	}
	return cnt & 0x1;
}



/**
 * Get the rotation of the sensor relative to the zero position.
 *
 * @return {int} between -2^13 and 2^13
 */
int AS5048A::getRotation(){
	uint32 data;
	int rotation;

	data = AS5048A::getRawRotation();
	rotation = (int)data - (int)position;
	if(rotation > 8191) rotation = -((0x3FFF)-rotation); //more than -180
	//if(rotation < -0x1FFF) rotation = rotation+0x3FFF;

	return rotation;
}

/**
 * Returns the raw angle directly from the sensor
 */
uint32 AS5048A::getRawRotation(){
	return AS5048A::read(AS5048A_ANGLE);
}

/**
 * returns the value of the state register
 * @return 16 bit uint32 containing flags
 */
uint32 AS5048A::getState(){
	return AS5048A::read(AS5048A_DIAG_AGC);
}

/**
 * Returns the value used for Automatic Gain Control (Part of diagnostic
 * register)
 */
byte AS5048A::getGain(){
	uint32 data = AS5048A::getState();
	return (byte) data & 0xFF;
}

/*
 * Get and clear the error register by reading it
 */
uint32 AS5048A::getErrors(){
	return AS5048A::read(AS5048A_CLEAR_ERROR_FLAG);
}

/*
 * Set the zero position
 */
void AS5048A::setZeroPosition(uint32 arg_position){
	position = arg_position % 0x3FFF;
}

/*
 * Returns the current zero position
 */
uint32 AS5048A::getZeroPosition(){
	return position;
}

/*
 * Check if an error has been encountered.
 */
bool AS5048A::error(){
	return errorFlag;
}

/*
 * Read a register from the sensor
 * Takes the address of the register as a 16 bit uint32
 * Returns the value of the register
 */
uint32 AS5048A::read(uint32 registerAddress){
	uint32 command = 0b0100000000000000; // PAR=0 R/W=R
	command = command | registerAddress;

	//Add a parity bit on the the MSB
	command |= ((uint32)spiCalcEvenParity(command)<<15);

	//Split the command into two bytes
	byte right_byte = command & 0xFF;
	byte left_byte = ( command >> 8 ) & 0xFF;

	//Send the command
	digitalWrite(_cs, LOW);
	// SPI.transfer(left_byte);
	// SPI.transfer(right_byte);
	digitalWrite(_cs,HIGH);

	//Now read the response
	digitalWrite(_cs, LOW);
	// left_byte = SPI.transfer(0x00);
	// right_byte = SPI.transfer(0x00);
	digitalWrite(_cs, HIGH);

	//Check if the error bit is set
	if (left_byte & 0x40) {
		errorFlag = true;
	}
	else {
		errorFlag = false;
	}

	//Return the data, stripping the parity and error bits
	return (( ( left_byte & 0xFF ) << 8 ) | ( right_byte & 0xFF )) & ~0xC000;
}


/*
 * Write to a register
 * Takes the 16-bit  address of the target register and the 16 bit uint32 of data
 * to be written to that register
 * Returns the value of the register after the write has been performed. This
 * is read back from the sensor to ensure a sucessful write.
 */
uint32 AS5048A::write(uint32 registerAddress, uint32 data) {

	uint32 command = 0b0000000000000000; // PAR=0 R/W=W
	command |= registerAddress;

	//Add a parity bit on the the MSB
	command |= ((uint32)spiCalcEvenParity(command)<<15);

	//Split the command into two bytes
	byte right_byte = command & 0xFF;
	byte left_byte = ( command >> 8 ) & 0xFF;

	//Start the write command with the target address
	digitalWrite(_cs, LOW);
	// SPI.transfer(left_byte);
	// SPI.transfer(right_byte);
	digitalWrite(_cs,HIGH);

	uint32 dataToSend = 0b0000000000000000;
	dataToSend |= data;

	//Craft another packet including the data and parity
	dataToSend |= ((uint32)spiCalcEvenParity(dataToSend)<<15);
	right_byte = dataToSend & 0xFF;
	left_byte = ( dataToSend >> 8 ) & 0xFF;

	//Now send the data packet
	digitalWrite(_cs,LOW);
	// SPI.transfer(left_byte);
	// SPI.transfer(right_byte);
	digitalWrite(_cs,HIGH);

	//Send a NOP to get the new data in the register
	digitalWrite(_cs, LOW);
	// left_byte =-SPI.transfer(0x00);
	// right_byte = SPI.transfer(0x00);
	digitalWrite(_cs, HIGH);

	//Return the data, stripping the parity and error bits
	return (( ( left_byte & 0xFF ) << 8 ) | ( right_byte & 0xFF )) & ~0xC000;
}
