/*
	ws2812toy - Control a ring of WS2812 RGB LEDs from an ATmega88.
	Copyright (C) 2015-2019 Johannes Bauer

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

int main() {
	initHAL();
	ws2812_init();

	uint8_t color_index_chg = 0;
	uint8_t color_index = 0;
	uint8_t led_index = 0;
	while (true) {
		struct color_t color;
		color_lookup_cyclic(&color, rainbow, color_index, 60);
		color_dim(&color, 2);
		ws2812_clr_all();
		ws2812_set(led_index, &color);

		color_index_chg++;
		if (color_index_chg >= 7) {
			color_index_chg = 0;
			color_index++;
			if (color_index >= 60) {
				color_index = 0;
			}
		}

		led_index++;
		if (led_index >= LEDCOUNT) {
			led_index = 0;
		}

		ws2812_update();
		delay_millis(45);
	}

	return 0;
}
