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

#include <avr/pgmspace.h>

#include "colors.h"

const struct color_t rainbow[60] PROGMEM = {
	{ .red = 0xfb, .green = 0x0c, .blue = 0x09 },
	{ .red = 0xfb, .green = 0x16, .blue = 0x0d },
	{ .red = 0xfb, .green = 0x20, .blue = 0x12 },
	{ .red = 0xfa, .green = 0x29, .blue = 0x16 },
	{ .red = 0xfa, .green = 0x33, .blue = 0x1a },
	{ .red = 0xfa, .green = 0x3d, .blue = 0x1f },
	{ .red = 0xfa, .green = 0x47, .blue = 0x23 },
	{ .red = 0xfa, .green = 0x50, .blue = 0x28 },
	{ .red = 0xf9, .green = 0x5a, .blue = 0x2c },
	{ .red = 0xf9, .green = 0x64, .blue = 0x30 },
	{ .red = 0xf9, .green = 0x6e, .blue = 0x34 },
	{ .red = 0xf9, .green = 0x7c, .blue = 0x31 },
	{ .red = 0xf9, .green = 0x8a, .blue = 0x2e },
	{ .red = 0xf8, .green = 0x98, .blue = 0x2c },
	{ .red = 0xf8, .green = 0xa6, .blue = 0x29 },
	{ .red = 0xf8, .green = 0xb3, .blue = 0x27 },
	{ .red = 0xf8, .green = 0xc1, .blue = 0x24 },
	{ .red = 0xf8, .green = 0xcf, .blue = 0x22 },
	{ .red = 0xf7, .green = 0xdd, .blue = 0x1f },
	{ .red = 0xf7, .green = 0xeb, .blue = 0x1d },
	{ .red = 0xf0, .green = 0xf1, .blue = 0x1c },
	{ .red = 0xdc, .green = 0xe8, .blue = 0x1d },
	{ .red = 0xc8, .green = 0xdf, .blue = 0x1f },
	{ .red = 0xb4, .green = 0xd6, .blue = 0x21 },
	{ .red = 0x9f, .green = 0xcd, .blue = 0x22 },
	{ .red = 0x8b, .green = 0xc4, .blue = 0x24 },
	{ .red = 0x77, .green = 0xbb, .blue = 0x26 },
	{ .red = 0x63, .green = 0xb2, .blue = 0x28 },
	{ .red = 0x4e, .green = 0xa9, .blue = 0x29 },
	{ .red = 0x3a, .green = 0xa0, .blue = 0x2b },
	{ .red = 0x2f, .green = 0x95, .blue = 0x30 },
	{ .red = 0x2d, .green = 0x86, .blue = 0x39 },
	{ .red = 0x2b, .green = 0x78, .blue = 0x41 },
	{ .red = 0x29, .green = 0x69, .blue = 0x4a },
	{ .red = 0x27, .green = 0x5b, .blue = 0x52 },
	{ .red = 0x25, .green = 0x4d, .blue = 0x5b },
	{ .red = 0x23, .green = 0x3e, .blue = 0x64 },
	{ .red = 0x21, .green = 0x30, .blue = 0x6c },
	{ .red = 0x1f, .green = 0x21, .blue = 0x75 },
	{ .red = 0x1d, .green = 0x13, .blue = 0x7d },
	{ .red = 0x24, .green = 0x0e, .blue = 0x80 },
	{ .red = 0x31, .green = 0x0d, .blue = 0x80 },
	{ .red = 0x3d, .green = 0x0c, .blue = 0x80 },
	{ .red = 0x49, .green = 0x0b, .blue = 0x80 },
	{ .red = 0x55, .green = 0x0b, .blue = 0x80 },
	{ .red = 0x62, .green = 0x0a, .blue = 0x81 },
	{ .red = 0x6e, .green = 0x09, .blue = 0x81 },
	{ .red = 0x7a, .green = 0x09, .blue = 0x81 },
	{ .red = 0x87, .green = 0x08, .blue = 0x81 },
	{ .red = 0x93, .green = 0x07, .blue = 0x81 },
	{ .red = 0x90, .green = 0x07, .blue = 0x81 },
	{ .red = 0x8b, .green = 0x08, .blue = 0x81 },
	{ .red = 0x85, .green = 0x08, .blue = 0x81 },
	{ .red = 0x80, .green = 0x09, .blue = 0x81 },
	{ .red = 0x7a, .green = 0x09, .blue = 0x81 },
	{ .red = 0x75, .green = 0x0a, .blue = 0x82 },
	{ .red = 0x6f, .green = 0x0a, .blue = 0x82 },
	{ .red = 0x6a, .green = 0x0b, .blue = 0x82 },
	{ .red = 0x64, .green = 0x0b, .blue = 0x82 },
	{ .red = 0x5f, .green = 0x0c, .blue = 0x82 }
};

void color_dim(struct color_t *color, uint8_t shift_bits) {
	color->red >>= shift_bits;
	color->green >>= shift_bits;
	color->blue >>= shift_bits;
}

void color_lookup(struct color_t *color, const struct color_t *lookup_table, uint8_t index) {
	if (index < 60) {
		memcpy_P(color, lookup_table + index, sizeof(struct color_t));
	} else {
		/* Undefined! */
		color->red = 0xff;
		color->green = 0;
		color->blue = 0;
	}
}

void color_lookup_cyclic(struct color_t *color, const struct color_t *lookup_table, uint8_t index, uint8_t total_colors) {
	index *= 2;
	if (index < total_colors) {
		color_lookup(color, lookup_table, index);
	} else {
		color_lookup(color, lookup_table, (2 * total_colors) - index - 1);
	}
}
