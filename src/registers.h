#ifndef __REGISTERS_H
#define __REGISTERS_H

// Version 20190929

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
	REG_IR_WAKE_LSB		= 0x10,
	REG_IR_WAKE_MSB		= 0x11,
	REG_IR_MASK_LSB		= 0x12,
	REG_IR_MASK_MSB		= 0x13,
	REG_LEDC_R			= 0xA0,
	REG_LEDC_G			= 0xA1,
	REG_LEDC_B			= 0xA2,
	REG_LEDS_START		= 0xA3,
	REG_LED0_R			= 0xA3,
	REG_LED0_G			= 0xA4,
	REG_LED0_B			= 0xA5,
	REG_LED1_R			= 0xA6,
	REG_LED1_G			= 0xA7,
	REG_LED1_B			= 0xA8,
	REG_LED2_R			= 0xA9,
	REG_LED2_G			= 0xAA,
	REG_LED2_B			= 0xAB,
	REG_LED3_R			= 0xAC,
	REG_LED3_G			= 0xAD,
	REG_LED3_B			= 0xAE,
	REG_LEDS_END		= 0xAE,
    REG_VFD_DATA        = 0xFA,
    REG_VFD_COMMAND     = 0xF8
} reg_addr_t;

#define        CONFIG1_SLEEP_ENBL   0x01        // Allow MCU sleep, 0 = never-ever sleep the MCU
#define		   CONFIG1_POWERDOWN	0x02        // power down 5V_SW and sleep mcu, optionally enable:
//#define     CONFIG_PD_SW34          0x04        // Poll SW3&SW4 during PowerDown with timer
//#define     CONFIG_AUTOSLEEP_ENBL   0x08        // Always sleep at end of loop, with PD_SW34 behaviour
#define CONFIG1_DFLT                0x01

#define        NOTIFY_INTSTAT  		0x01        // TwoWire master send INTSTAT on change
#define        NOTIFY_IR       		0x20        // TwoWire master send IRCMD on change
#define        NOTIFY_ROTARY   		0x40        // TwoWire master send RORVAL on change
#define		   NOTIFY_IRWAKE		0x80		// TwoWire master send IRCMD when IRCMD==IRWAKE
#define NOTIFY_DFLT                0x00

#define     SLEEPMASK_SW1           0x01        
#define     SLEEPMASK_SW2           0x02
#define     SLEEPMASK_SW3           0x04        // Requires CONFIG_PD_SW34
#define     SLEEPMASK_SW4           0x08        // Requires CONFIG_PD_SW34
#define     SLEEPMASK_PUSH          0x10
#define     SLEEPMASK_IR            0x20
#define     SLEEPMASK_ROTARY        0x40
#define		SLEEPMASK_IRWAKE		0x80
#define SLEEPMASK_DFLT              0x90        // Enable interrupts during power-down
	
#define     INTMASK_SW1             0x01
#define     INTMASK_SW2             0x02
#define     INTMASK_SW3             0x04
#define     INTMASK_SW4             0x08
#define     INTMASK_PUSH            0x10
#define     INTMASK_IR              0x20
#define     INTMASK_ROTARY          0x40
#define		INTMASK_IRWAKE			0x80
#define INTMASK_DFLT                0xFF

#define     INTSTAT_SW1             0x01
#define     INTSTAT_SW2             0x02
#define     INTSTAT_SW3             0x04
#define     INTSTAT_SW4             0x08
#define     INTSTAT_PUSH            0x10
#define     INTSTAT_IR              0x20
#define     INTSTAT_ROTARY          0x40
#define		INTSTAT_IRWAKE			0x80

#define IRWAKE_DFLT					0xF938	// DISPLAY

// extern uint16_t IRMASK;

#endif // __REGISTERS_H