#ifndef as5048_h
#define as5048_h
#define LIBRARY_VERSION 1.0.0

#include <libmaple/libmaple_types.h>
#include <libmaple/timer.h>

#include <stdint.h>
#include <wirish/HardwareSPI.h>
#include <wirish/wirish_types.h>

#define AS5048A_CLEAR_ERROR_FLAG 0x0001
#define AS5048A_PROGRAMMING_CONTROL 0x0003
#define AS5048A_OTP_REGISTER_ZERO_POS_HIGH 0x0016
#define AS5048A_OTP_REGISTER_ZERO_POS_LOW 0x0017
#define AS5048A_DIAG_AGC 0x3FFD
#define AS5048A_MAGNITUDE 0x3FFE
#define AS5048A_ANGLE 0x3FFF

class AS5048A{

	bool errorFlag;
	byte _cs;
	byte cs;
	byte dout;
	byte din;
	byte clk;
	uint32 position;
	uint32 transaction(uint32 data);

	public:

	/**
	 *	Constructor
	 */
	AS5048A(byte arg_cs);

	/**
	 * Initialiser
	 * Sets up the SPI interface
	 */
	void init();

	/**
	 * Closes the SPI connection
	 */
	void close();

	/*
	 * Read a register from the sensor
	 * Takes the address of the register as a 16 bit uint32
	 * Returns the value of the register
	 */
	uint32 read(uint32 registerAddress);

	/*
	 * Write to a register
	 * Takes the 16-bit  address of the target register and the 16 bit uint32 of data
	 * to be written to that register
	 * Returns the value of the register after the write has been performed. This
	 * is read back from the sensor to ensure a sucessful write.
	 */
	uint32 write(uint32 registerAddress, uint32 data);

	/**
	 * Get the rotation of the sensor relative to the zero position.
	 *
	 * @return {int} between -2^13 and 2^13
	 */
	int getRotation();

	/**
	 * Returns the raw angle directly from the sensor
	 */
	uint32 getRawRotation();


	/**
	 * returns the value of the state register
	 * @return 16 bit uint32 containing flags
	 */
	uint32 getState();

	/**
	 * Print the diagnostic register of the sensor
	 */
	void printState();

	/**
	 * Returns the value used for Automatic Gain Control (Part of diagnostic
	 * register)
	 */
	byte getGain();

	/*
	 * Get and clear the error register by reading it
	 */
	uint32 getErrors();

	/*
	 * Set the zero position
	 */
	void setZeroPosition(uint32 arg_position);

	/*
	 * Returns the current zero position
	 */
	uint32 getZeroPosition();

	/*
	 * Check if an error has been encountered.
	 */
	bool error();

	private:

	byte spiCalcEvenParity(uint32);
};
#endif
