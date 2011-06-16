// Copyright 2011 Juri Glass, Mathias Runge, Nadim El Sayed 
// DAI-Labor, TU-Berlin
// 
// This file is part of libSML.
// 
// libSML is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// libSML is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with libSML.  If not, see <http://www.gnu.org/licenses/>.


#ifndef _SML_NUMBER_H
#define	_SML_NUMBER_H

#include "sml_shared.h"

#ifdef __cplusplus
extern "C" {
#endif


// Parses a number. Identified by type (SML_TYPE_INTEGER or SML_TYPE_UNSIGNED) 
// and maximal number of bytes (SML_TYPE_NUMBER_8, SML_TYPE_NUMBER_16, 
// SML_TYPE_NUMBER_32, SML_TYPE_NUMBER_64)
u64 sml_number_parse(sml_buffer *buf, unsigned char type, int max_size);

#define sml_u8_parse(buf) (u8) sml_number_parse(buf, SML_TYPE_UNSIGNED, SML_TYPE_NUMBER_8)
#define sml_u16_parse(buf) (u16) sml_number_parse(buf, SML_TYPE_UNSIGNED, SML_TYPE_NUMBER_16)
#define sml_u32_parse(buf) (u32) sml_number_parse(buf, SML_TYPE_UNSIGNED, SML_TYPE_NUMBER_32)
#define sml_u64_parse(buf) (u64) sml_number_parse(buf, SML_TYPE_UNSIGNED, SML_TYPE_NUMBER_64)
#define sml_i8_parse(buf) (i8) sml_number_parse(buf, SML_TYPE_INTEGER, SML_TYPE_NUMBER_8)
#define sml_i16_parse(buf) (i16) sml_number_parse(buf, SML_TYPE_INTEGER, SML_TYPE_NUMBER_16)
#define sml_i32_parse(buf) (i32) sml_number_parse(buf, SML_TYPE_INTEGER, SML_TYPE_NUMBER_32)
#define sml_i64_parse(buf) (i64) sml_number_parse(buf, SML_TYPE_INTEGER, SML_TYPE_NUMBER_64)

void sml_number_write(unsigned char type, int size, u64 value, sml_buffer *buf);

typedef u8 sml_unit;

#ifdef __cplusplus
}
#endif


#endif
