// Copyright 2022 Neo Trinity
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

// Used to create a keymap using only KC_ prefixed keys

#define LAYOUT( \
	K00, K01, K02, K03, K04, K05, K06,  \
	K10, K11, K12, K13, K14, K15, K16,  \
	K20, K21, K22, K23, K24, K25, K26,  \
	K30, K31, K32, K33, K34,      K38,  \
	                         K35, K37,  \
	                              K36   \
	) \
	{ \
	{ K00, K01, K02, K03, K04, K05, K06, KC_NO, KC_NO }, \
	{ K10, K11, K12, K13, K14, K15, K16, KC_NO, KC_NO }, \
	{ K20, K21, K22, K23, K24, K25, K26, KC_NO, KC_NO }, \
	{ K30, K31, K32, K33, K34, K35, K36, K37,   K38   } \
	}





static const char PROGMEM lhp_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
};


