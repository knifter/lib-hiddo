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
        // } pinmode_t;

        // REG_INTSTAT, REG_INTMASK and REG_SLEEPMASK bits (same layout)
        typedef enum
        {
            INT_SW1             = 0x01,     // SLEEPMASK: no effect, polled only while hiddo awake
            INT_SW2             = 0x02,     // SLEEPMASK: no effect, polled only while hiddo awake
            INT_SW3             = 0x04,
            INT_SW4             = 0x08,
            INT_PUSH            = 0x10,
            INT_IR              = 0x20,
            INT_ROTARY          = 0x40,
            INT_IRWAKE          = 0x80
        } regs_int_t; // For INSTAT, INTMASK, SLEEPMASK

        Hiddo(TwoWire& wire, const uint8_t addr = HIDDO_ADDRESS_DEFAULT) : TwoWireDevice(wire, addr) {};
        Hiddo(const uint8_t addr = HIDDO_ADDRESS_DEFAULT) : TwoWireDevice(addr) {};

        bool 	begin();
		void 	reset();
		void    clear();
		void 	read();
		void 	turn_off();
		void 	turn_on();
		void 	setLED(uint8_t idx, uint8_t r, uint8_t g, uint8_t b);

		uint8_t     _intstat;
		int8_t      _rotval;
		uint16_t    _ircmd;

    protected:

    private:
        // Register map, Version 20190929
        typedef enum
        {
            REG_CONFIG1         = 0x01,
            REG_NOTIFY          = 0x02,
            REG_RESERVED1       = 0x03,
            REG_SLEEPMASK       = 0x04,
            REG_INTMASK         = 0x05,
            REG_INTSTAT         = 0x06,
            REG_ROTVAL          = 0x07,
            REG_IR_MSB          = 0x08,
            REG_IR_LSB          = 0x09,
            REG_IR_WAKE_LSB     = 0x10,
            REG_IR_WAKE_MSB     = 0x11,
            REG_IR_MASK_LSB     = 0x12,
            REG_IR_MASK_MSB     = 0x13,
            REG_LEDC_R          = 0xA0,
            REG_LEDC_G          = 0xA1,
            REG_LEDC_B          = 0xA2,
            REG_LEDS_START      = 0xA3,
            REG_LED0_R          = 0xA3,
            REG_LED0_G          = 0xA4,
            REG_LED0_B          = 0xA5,
            REG_LED1_R          = 0xA6,
            REG_LED1_G          = 0xA7,
            REG_LED1_B          = 0xA8,
            REG_LED2_R          = 0xA9,
            REG_LED2_G          = 0xAA,
            REG_LED2_B          = 0xAB,
            REG_LED3_R          = 0xAC,
            REG_LED3_G          = 0xAD,
            REG_LED3_B          = 0xAE,
            REG_LEDS_END        = 0xAE,
            REG_VFD_DATA        = 0xFA,
            REG_VFD_COMMAND     = 0xF8
        } regaddr_t;

        // REG_CONFIG1 bits
        typedef enum
        {
            CONFIG1_SLEEP_ENBL  = 0x01,     // Allow MCU sleep, 0 = never-ever sleep the MCU
            CONFIG1_POWERDOWN   = 0x02,     // power down 5V_SW and sleep mcu
            CONFIG1_DFLT        = 0x01
        } reg_config1_t;

        // REG_NOTIFY bits
        typedef enum
        {
            NOTIFY_INTSTAT      = 0x01,     // TwoWire master send INTSTAT on change
            NOTIFY_IR           = 0x20,     // TwoWire master send IRCMD on change
            NOTIFY_ROTARY       = 0x40,     // TwoWire master send RORVAL on change
            NOTIFY_IRWAKE       = 0x80,     // TwoWire master send IRCMD when IRCMD==IRWAKE
            NOTIFY_DFLT         = 0x00
        } reg_notify_t;

        // Defaults, set by hiddo fw (not written from here):
        // INTMASK      0xFF
        // SLEEPMASK    0x90    INT_PUSH | INT_IRWAKE, enable interrupts during power-down
        // IRWAKE       0xF900  PWR
        // IRMASK       0xFFFF

        Hiddo(const Hiddo&);
        Hiddo& operator=(const Hiddo&);

};

#endif // __HIDDO_H
