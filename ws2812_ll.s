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

.file	"ws2812_ll.s"

/* PB0 */
__PORT = 0x05
__PIN = 0


.text
.global	ws2812_sendbyte
	.type	ws2812_sendbyte, @function
ws2812_sendbyte:
	ldi r25, 8
	send_next_bit:
		sbi __PORT, __PIN
		lsl r24
		nop
		nop
		
		brcs bit_is_one
			cbi __PORT, __PIN
		bit_is_one:

		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop

		cbi __PORT, __PIN
		nop
	
	dec r25
	brne send_next_bit
	ret
