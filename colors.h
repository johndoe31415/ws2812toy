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

#ifndef __COLORS_H__
#define __COLORS_H__

#include <avr/pgmspace.h>
#include "staticassert.h"

struct color_t {
	uint8_t green, red, blue;
} __attribute__ ((packed));
staticassert(sizeof(struct color_t) == 3);

extern const struct color_t rainbow[60] PROGMEM;

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
void color_dim(struct color_t *color, uint8_t shift_bits);
void color_lookup(struct color_t *color, const struct color_t *lookup_table, uint8_t index);
void color_lookup_cyclic(struct color_t *color, const struct color_t *lookup_table, uint8_t index, uint8_t total_colors);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
