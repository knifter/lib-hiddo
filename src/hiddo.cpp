#include "hiddo.h"

#ifndef ERROR
#define ERROR(x)		Serial.println(x);
#endif

bool Hiddo::begin()
{
	// reset();
	if(!TwoWireDevice::begin())
		return false;

	// Clear all interrupts (and checks device is there)
	readreg8(REG_INTSTAT);
	return last_error() == 0;
}

void Hiddo::reset()
{
	// TODO: call this REG_RESET then..
	writereg8(REG_RESERVED1, 0x00);
}

void Hiddo::clear()
{
	// Clear remote int
	readreg8(REG_INTSTAT);

	// and our 'cache'
	_intstat = 0x00;
}

void Hiddo::setLED(uint8_t idx, uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t reg = REG_LEDS_START + idx*3;
	writereg8(reg++, r);
	writereg8(reg++, g);
	writereg8(reg, b);
}

void Hiddo::read()
{
	_intstat = readreg8(REG_INTSTAT);

	if(last_error())
	{
		ERROR("hiddo.read() failed");
		_intstat = 0x00;
		_rotval = 0x00;
		_ircmd = 0x0000;
		return;
	};

	_rotval = 0;
	_ircmd = 0x0000;
	if(_intstat & INT_ROTARY)
	{
		_rotval = readreg8(REG_ROTVAL);
		if(last_error())
			_rotval = 0;
	};
	if(_intstat & INT_IR)
	{
		_ircmd = readreg16_LM(REG_IR_LSB);
		if(last_error())
			_ircmd = 0x0000;
	};
}

void Hiddo::turn_off()
{
	uint8_t config1 = readreg8(REG_CONFIG1);
	config1 |= CONFIG1_POWERDOWN;
	clear();
	writereg8(REG_CONFIG1, config1);
}

void Hiddo::turn_on()
{
	uint8_t tmp = readreg8(REG_CONFIG1);
	tmp &= ~CONFIG1_POWERDOWN;
	writereg8(REG_CONFIG1, tmp);

	// Send again: Workaround hiddo not waking up for some reason
	delay(5);
	writereg8(REG_CONFIG1, tmp);
}

