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
#include <string.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "ws2812.h"
#include "ws2812_ll.h"
#include "hal.h"
#include "delay.h"

static struct color_t led_colors[LEDCOUNT];
staticassert(sizeof(led_colors) == LEDCOUNT * sizeof(struct color_t));

void ws2812_update(void) {
	cli();
	for (uint8_t i = 0; i < 3 * LEDCOUNT; i++) {
		ws2812_sendbyte(((uint8_t*)led_colors)[i]);
	}
	sei();
}

void ws2812_rotate(void) {
	struct color_t temp = led_colors[0];
	for (uint8_t i = 0; i < LEDCOUNT - 1; i++) {
		led_colors[i] = led_colors[i + 1];
	}
	led_colors[LEDCOUNT - 1] = temp;
}

void ws2812_set(uint8_t led_index, const struct color_t *color) {
	led_colors[led_index] = *color;
}

void ws2812_set_all(const struct color_t *color) {
	for (uint8_t i = 0; i < LEDCOUNT; i++) {
		ws2812_set(i, color);
	}
}

void ws2812_clr_all(void) {
	memset(led_colors, 0, sizeof(led_colors));
}

void ws2812_init(void) {
	ws2812_clr_all();
	LEDOutput_SetInactive();
}
