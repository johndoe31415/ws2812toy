/* Automatically generated HAL from hal.xml */
/* NEVER EDIT MANUALLY */

/* Generated on: 2019-07-09 22:23:58 */

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

/* PowerLED -> PC4 (Output, Initially Inactive) */
#define PowerLED_BIT                             4
#define PowerLED_PIN                             PINC
#define PowerLED_PORT                            PORTC
#define PowerLED_DDR                             DDRC
#define PowerLED_ModeOutput()                    PowerLED_DDR |= _BV(PowerLED_BIT)
#define PowerLED_IsOutput()                      ((PowerLED_DDR & _BV(PowerLED_BIT)) != 0)
#define PowerLED_SetHIGH()                       PowerLED_PORT |= _BV(PowerLED_BIT)
#define PowerLED_SetLOW()                        PowerLED_PORT &= ~_BV(PowerLED_BIT)
#define PowerLED_Get()                           (PowerLED_PIN & _BV(PowerLED_BIT))
#define PowerLED_SetInactive()                   PowerLED_SetLOW()
#define PowerLED_SetActive()                     PowerLED_SetHIGH()
#define PowerLED_Toggle()                        PowerLED_PORT ^= _BV(PowerLED_BIT)
#define PowerLED_SetConditional(condition)       if (condition) PowerLED_SetActive(); else PowerLED_SetInactive()
#define PowerLED_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { PowerLED_SetActive(); } else if (conditionoff) { PowerLED_SetInactive(); } else if (conditiontoggle) { PowerLED_Toggle(); }
#define PowerLED_Pulse()                         { PowerLED_SetActive(); PowerLED_SetInactive(); }
#define PowerLED_PulseNop()                      { PowerLED_SetActive(); nop(); PowerLED_SetInactive(); }
#define PowerLED_IsInactive()                    (PowerLED_Get() == 0)
#define PowerLED_IsActive()                      (PowerLED_Get() != 0)
#define PowerLED_Init()                          { PowerLED_SetInactive(); PowerLED_ModeOutput(); }

/* Switch -> PC3 (Input, Initially Pullup On, Active-Low) */
#define Switch_BIT                               3
#define Switch_PIN                               PINC
#define Switch_PORT                              PORTC
#define Switch_DDR                               DDRC
#define Switch_SetPullupActive()                 Switch_PORT |= _BV(Switch_BIT)
#define Switch_SetPullupInactive()               Switch_PORT &= ~_BV(Switch_BIT)
#define Switch_ModeInput()                       Switch_DDR &= ~_BV(Switch_BIT)
#define Switch_IsInput()                         ((Switch_DDR & _BV(Switch_BIT)) == 0)
#define Switch_Get()                             (Switch_PIN & _BV(Switch_BIT))
#define Switch_GetBit()                          (Switch_Get() >> Switch_BIT)
#define Switch_IsInactive()                      (Switch_Get() != 0)
#define Switch_IsActive()                        (Switch_Get() == 0)
#define Switch_Init()                            { Switch_SetPullupActive(); Switch_ModeInput(); }

#define initHAL() {\
		LEDOutput_Init();\
		PowerLED_Init();\
		Switch_Init();\
}

#endif
