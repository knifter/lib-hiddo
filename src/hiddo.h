#ifndef __HIDDO_H
#define __HIDDO_H

#include <Arduino.h>
#include <TwoWireDevice.h>

#define HIDDO_ADDRESS_DEFAULT              (0x44)

class Hiddo: public TwoWireDevice {
    public:    
        // typedef enum
        // {
        //     PINMODE_INPUT = 0x01,
        //     PINMODE_OUTPUT = 0x02,
        //     PINMODE_INPUT_PULLUP = 0x05,
        // } PinMode_t;

        Hiddo(TwoWire& wire, const uint8_t addr = HIDDO_ADDRESS_DEFAULT) : TwoWireDevice(wire, addr) {};
        Hiddo(const uint8_t addr = HIDDO_ADDRESS_DEFAULT) : TwoWireDevice(addr) {};

        bool 	begin();
		void 	reset();
		void    clear();
		void 	read();
		void 	turn_off();
		void 	turn_on();
		void 	setLED(uint8_t idx, uint8_t r, uint8_t g, uint8_t b);

		uint8_t _intstat;
		int8_t _rotval;
		uint16_t _ircmd;

    protected:

    private:
        Hiddo(const Hiddo&);
        Hiddo& operator=(const Hiddo&);

};

#endif // __HIDDO_H
