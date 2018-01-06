/*
	ws2812toy - Control a ring of WS2812 RGB LEDs from an ATmega88.
	Copyright (C) 2011-2015 Johannes Bauer

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
#include <util/delay.h>
#include "hal.h"
#include "delay.h"
#include "colors.h"
#include "ws2812.h"

static void ledring_load_rainbow(void) {
	for (int i = 0; i < LEDCOUNT; i++) {
		struct color_t color;
		color_lookup_cyclic(&color, rainbow, i, LEDCOUNT);
		color_dim(&color, 2);
		ws2812_set(i, &color);
	}
}

static void ledring_rotate_full(uint16_t millis) {
	for (int i = 0; i < LEDCOUNT; i++) {
		ws2812_rotate();
		ws2812_update();
		delay_millis(millis);
	}
}

static void ledring_rotate_rainbow(uint8_t rotation_cnt, uint16_t millis) {
	ledring_load_rainbow();
	for (uint8_t i = 0; i < rotation_cnt; i++) {
		ledring_rotate_full(millis);
	}
}

static void ledring_all_rainbow(uint8_t cycle_cnt, uint16_t millis) {
	for (uint8_t j = 0; j < cycle_cnt; j++) {
		for (uint8_t i = 0; i < LEDCOUNT; i++) {
			struct color_t color;
			color_lookup_cyclic(&color, rainbow, i, LEDCOUNT);
			color_dim(&color, 2);
			ws2812_set_all(&color);
			ws2812_update();
			delay_millis(millis);
		}
	}
}

static void ledring_set_tail(uint8_t center_index, const struct color_t *center_color, uint8_t tail_length) {
	ws2812_clr_all();
	ws2812_set(center_index, center_color);

	struct color_t tail_color = *center_color;
	for (uint8_t i = 0; i < 4; i++) {
		color_dim(&tail_color, 1);

		for (uint8_t j = 0; j < tail_length; j++) {
			ws2812_set((center_index + (tail_length * i) + j) % LEDCOUNT, &tail_color);
			ws2812_set((center_index - (tail_length * i) + j + LEDCOUNT) % LEDCOUNT, &tail_color);
		}
	}
}

static void ledring_rainbow_tail(uint8_t cycle_cnt, uint8_t colorchg, uint8_t tail_length, uint16_t millis) {
	uint8_t center = 0;
	for (uint8_t coloridx = 0; coloridx < LEDCOUNT; coloridx ++) {
		struct color_t color;
		color_lookup_cyclic(&color, rainbow, coloridx, LEDCOUNT);
		ledring_set_tail(center, &color, tail_length);
		for (uint8_t j = 0; j < colorchg; j++) {
			ws2812_rotate();
			ws2812_update();
			delay_millis(millis);
		}
		center = (center - colorchg + LEDCOUNT) % LEDCOUNT;
	}
}

int main() {
	initHAL();
	ws2812_init();

	while (true) {
		ledring_rotate_rainbow(5, 25);
		ledring_all_rainbow(3, 50);
		ledring_rainbow_tail(3, 15, 2, 25);
	}

	return 0;
}
