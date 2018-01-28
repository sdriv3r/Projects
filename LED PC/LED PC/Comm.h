/*
 * Comm.h
 *
 * Created: 2017-11-22 8:37:23 PM
 *  Author: Fluffy
 */ 


#ifndef COMM_H_
#define COMM_H_

// Init Serial communication. Baud rate of 2400.
void initSerial();

// Read a full line. Reads until '\r'. 
void readLine();

// Sets the correct value. The format is "r=cs\r" where 'r' is the color between r,g,b 'c' is the color value in byte and 's' is the checksum.
void setValue();

// Check if the 3 first char of the buffer match the checksum (4th char).
uint8_t checksumValid();

// Request a resend of the last line.
void requestResend();

// Transmit a single character.
void transmit (unsigned char data);

// Receive a single character.
unsigned char receive();

#endif /* COMM_H_ */