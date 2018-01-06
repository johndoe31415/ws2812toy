/* Automatically generated HAL from HAL.xml */
/* NEVER EDIT MANUALLY */

/* Generated on: 2015-09-23 23:50:46 */

#ifndef __HAL_H__
#define __HAL_H__

#include <avr/io.h>

#define nop()                                    __asm__ __volatile__("nop")

/* LEDOutput -> PB0 (Output, Initially Inactive) */
#define LEDOutput_BIT                            0
#define LEDOutput_PIN                            PINB
#define LEDOutput_PORT                           PORTB
#define LEDOutput_DDR                            DDRB
#define LEDOutput_ModeOutput()                   LEDOutput_DDR |= _BV(LEDOutput_BIT)
#define LEDOutput_IsOutput()                     ((LEDOutput_DDR & _BV(LEDOutput_BIT)) != 0)
#define LEDOutput_SetHIGH()                      LEDOutput_PORT |= _BV(LEDOutput_BIT)
#define LEDOutput_SetLOW()                       LEDOutput_PORT &= ~_BV(LEDOutput_BIT)
#define LEDOutput_Get()                          (LEDOutput_PIN & _BV(LEDOutput_BIT))
#define LEDOutput_SetInactive()                  LEDOutput_SetLOW()
#define LEDOutput_SetActive()                    LEDOutput_SetHIGH()
#define LEDOutput_Toggle()                       LEDOutput_PORT ^= _BV(LEDOutput_BIT)
#define LEDOutput_SetConditional(condition)      if (condition) LEDOutput_SetActive(); else LEDOutput_SetInactive()
#define LEDOutput_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { LEDOutput_SetActive(); } else if (conditionoff) { LEDOutput_SetInactive(); } else if (conditiontoggle) { LEDOutput_Toggle(); }
#define LEDOutput_Pulse()                        { LEDOutput_SetActive(); LEDOutput_SetInactive(); }
#define LEDOutput_PulseNop()                     { LEDOutput_SetActive(); nop(); LEDOutput_SetInactive(); }
#define LEDOutput_IsInactive()                   (LEDOutput_Get() == 0)
#define LEDOutput_IsActive()                     (LEDOutput_Get() != 0)
#define LEDOutput_Init()                         { LEDOutput_SetInactive(); LEDOutput_ModeOutput(); }

#define initHAL() {\
		LEDOutput_Init();\
}

#endif
