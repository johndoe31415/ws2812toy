/*
	ws2812toy - Control a ring of WS2812 RGB LEDs from an ATmega88.
	Copyright (C) 2015-2018 Johannes Bauer

	This file is part of ws2812toy.

	ws2812toy is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; this program is ONLY licensed under
	version 3 of the License, later versions are explicitly excluded.

	ws2812toy is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with ws2812toy; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	Johannes Bauer <JohannesBauer@gmx.de>
*/

#include <stdint.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "hal.h"
#include "delay.h"
#include "colors.h"
#include "ws2812.h"
#include "debounce.h"

enum mode_t {
	MODE_OFF = 0,
	MODE_RAINBOW,
	MODE_WARMCOLORS,
	MODE_DIMWHITE,
	MODE_BRIGHTWHITE,
	MODE_LAST,
};

static struct debounce_t debouncer;
static volatile bool interrupt;
static uint8_t mode = MODE_OFF;
static const struct color_t dim_white = {
	.red = 100,
	.green = 100,
	.blue = 100,
};
static const struct color_t bright_white = {
	.red = 200,
	.green = 200,
	.blue = 200,
};


static void interruptible_sleep(uint16_t millis) {
	while (!interrupt && millis--) {
		delay_millis(1);
	}
}

static void interruptible_function_showfixedcolor(void) {
	struct color_t color = { 0 };
	if (mode == MODE_RAINBOW) {
		color.blue = 255;
		color_dim(&color, 3);
	} else if (mode == MODE_WARMCOLORS) {
		color.red = 255;
		color_dim(&color, 3);
	} else if (mode == MODE_DIMWHITE) {
		color = dim_white;
	} else if (mode == MODE_BRIGHTWHITE) {
		color = bright_white;
	}
	ws2812_set_all(&color);
	ws2812_update();
	interruptible_sleep(500);
}

static void interruptible_function(void) {
	if (mode == MODE_OFF) {
		ws2812_clr_all();
		ws2812_update();
		while (!interrupt) {
			interruptible_sleep(1000);
		}
	} else if ((mode == MODE_RAINBOW) || (mode == MODE_WARMCOLORS)) {
		uint8_t color_count;
		const struct color_t *colors;
		if (mode == MODE_RAINBOW) {
			color_count = RAINBOW_COLOR_COUNT;
			colors = rainbow;
		} else {
			color_count = RAINBOW_COLOR_COUNT;
			colors = warmcolors;
		}

		const uint8_t max_index = (2 * color_count) - 2;
		for (uint8_t color_index = 0; color_index < max_index; color_index++) {
			struct color_t color;
			color_lookup_cyclic(&color, colors, color_index, color_count);
			color_dim(&color, 2);

			if (color_index == 0) {
				ws2812_set_all(&color);
			}

			for (uint8_t led = 0; led < LEDCOUNT; led++) {
				ws2812_set(led, &color);
				ws2812_update();
				interruptible_sleep(100);
				if (interrupt) {
					break;
				}
			}
			if (interrupt) {
				break;
			}
		}
	} else if ((mode == MODE_DIMWHITE) || (mode == MODE_BRIGHTWHITE)) {
		struct color_t const_color;
		const_color = (mode == MODE_DIMWHITE) ? dim_white : bright_white;
		ws2812_set_all(&const_color);
		ws2812_update();
		while (true) {
			interruptible_sleep(1);
			if (interrupt) {
				break;
			}
		}
	}
}

ISR(TIMER0_OVF_vect) {
	TCNT0 = 0x70; 	/* 500 µs */
	if (debounce(&debouncer, Switch_IsActive()) == ACTION_PRESSED) {
		mode++;
		if (mode == MODE_LAST) {
			mode = MODE_OFF;
		}
		PowerLED_SetConditional(mode != MODE_OFF);
		interrupt = true;
	}
}

int main() {
	initHAL();
	ws2812_init();

	TCCR0B = _BV(CS01) | _BV(CS00);		/* CK / 64 */
	TIMSK0 = _BV(TOIE0);
	TCNT0 = 0x70; 	/* 500 µs */
	sei();

	while (true) {
		if (interrupt) {
			/* Show new mode */
			interrupt = false;
			interruptible_function_showfixedcolor();
			continue;
		}
		interruptible_function();
	}

	return 0;
}
