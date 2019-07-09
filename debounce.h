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

#ifndef __DEBOUNCE_H__
#define __DEBOUNCE_H__

#include <stdint.h>
#include <stdbool.h>

#define DEBOUNCE_THRESHOLD		50

enum debounce_action_t {
	NOACTION = 0,
	ACTION_PRESSED = 1,
	ACTION_RELEASED = 2,
};

struct debounce_t {
	uint8_t counter;
	bool last_state;
};

/*************** AUTO GENERATED SECTION FOLLOWS ***************/
uint8_t debounce(struct debounce_t *button, bool state);
/***************  AUTO GENERATED SECTION ENDS   ***************/

#endif
