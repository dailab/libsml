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


#include <sml/sml_transport.h>

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <sml/sml_shared.h>
#include <sml/sml_crc16.h>

#define MC_SML_BUFFER_LEN 8096

size_t sml_transport_read(int fd, unsigned char *buffer, size_t max_len) {

	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(fd, &readfds);

	unsigned char byte;
	unsigned char buf[max_len];
	int esc = 0, start = 0, i = 0, end = 0, r;

	while (i < max_len) {
		select(fd + 1, &readfds, 0, 0, 0);
		if (FD_ISSET(fd, &readfds)) {

			if (!i) { // read until escaped start sequence;
				r = read(fd, &byte, 1);
				if (r <= 0) continue;

				if (esc == 4) {
					if (byte == 0x01) {
						buf[esc + start++] = byte;
						if (start == 4) {
							i = esc + start;
							esc = 0;
							start = 0;
						}
					}
					else {
						// no start sequence
						esc = 0;
					}
				}
				else {
					if (byte == 0x1b) {
						buf[esc++] = byte;
					}
					else {
						// no escape sequence
						esc = 0;
					}
				}
			}
			else { // read the message
				r = read(fd, (void *)(&(buf[i])), 1);
				if (r <= 0) continue;

				if (esc == 4) {
					if (end) {
						end++;
						if (end == 5) {
							memcpy(buffer, &(buf[0]), i);
							return i;
						}
					}
					else {
						if (buf[i] == 0x1a) {
							end++;
						}
						else {
							// dont read other escaped sequences yet
							printf("error: unrecognized sequence");
							esc = 0;
						}
					}
				}
				else {
					if (buf[i] == 0x1b) {
						esc++;
					}
					else {
						esc = 0;
					}
				}
				i++;
			}
		}
	}

	return -1;
}

void sml_transport_listen(int fd, void (*sml_transport_receiver)(unsigned char *buffer, size_t buffer_len)) {
	unsigned char buffer[MC_SML_BUFFER_LEN];
	size_t bytes;

	while (1) {
		bytes = sml_transport_read(fd, buffer, MC_SML_BUFFER_LEN);

		if (bytes > 0) {
			sml_transport_receiver(buffer, bytes);
		}
	}
}

int sml_transport_write(int fd, sml_file *file) {

	unsigned char start_seq[] = {0x1b, 0x1b, 0x1b, 0x1b, 0x01, 0x01, 0x01, 0x01};
	unsigned char end_seq[] = {0x1b, 0x1b, 0x1b, 0x1b, 0x1a};
	sml_buffer *buf = file->buf;
	buf->cursor = 0;

	// add start sequence
	memcpy(sml_buf_get_current_buf(buf), start_seq, 8);
	buf->cursor += 8;

	// add file
	sml_file_write(file);

	// add padding bytes
	int padding = (buf->cursor % 4) ? (4 - buf->cursor % 4) : 0;
	if (padding) {
		// write zeroed bytes
		memset(sml_buf_get_current_buf(buf), 0, padding);
		buf->cursor += padding;
	}

	// begin end sequence
	memcpy(sml_buf_get_current_buf(buf), end_seq, 5);
	buf->cursor += 5;

	// add padding info
	buf->buffer[buf->cursor++] = (unsigned char) padding;

	// add crc checksum
	u16 crc = sml_crc16_calculate(buf->buffer, buf->cursor);
	buf->buffer[buf->cursor++] = (unsigned char) ((crc & 0xFF00) >> 8);
	buf->buffer[buf->cursor++] = (unsigned char) (crc & 0x00FF);

	size_t wr = write(fd, buf->buffer, buf->cursor);
	if (wr == buf->cursor) {
		return wr;
	}
	return 0;
}

