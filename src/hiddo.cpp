#include "hiddo.h"

#include "registers.h"

#ifndef ERROR
#define ERROR(x)		Serial.println(x);
#endif

bool Hiddo::begin()
{
	// reset();
	// Clear all interrupts
	return readreg8(REG_INTSTAT) == -1 ? false : true;
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

	// Bad read workaround
	if(_intstat == 0xFF)
	{
		ERROR("hiddo.read() failed (FF)");
		_intstat = 0x00;
		_rotval = 0x00;
		_ircmd = 0x0000;
		return;
	};

	_rotval = 0;
	_ircmd = 0x0000;
	if(_intstat & INTSTAT_ROTARY)
		_rotval = readreg8(REG_ROTVAL);	
	if(_intstat & INTSTAT_IR)
		_ircmd = readreg16_LE(REG_IR_LSB);
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
}

