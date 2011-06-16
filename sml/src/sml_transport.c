
#include <sml/sml_transport.h>

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define MC_SML_BUFFER_LEN 8096

// Invokes on every incoming SML message the given method. The buffer is freed afterwards.
void mc_sml_transport_listen(int fd, void (*mc_sml_transport_receiver)(unsigned char *buffer, size_t buffer_len)) {

	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(fd, &readfds);
	
	unsigned char byte;
	unsigned char buf[MC_SML_BUFFER_LEN];
	int esc = 0, start = 0, i, end = 0, r;
	
	for (i = 0; i < MC_SML_BUFFER_LEN;) {
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
							char *sml_file = (char *) malloc(i);
							memcpy(sml_file, &(buf[0]), i);
							// without the SML transport stuff
							mc_sml_transport_receiver((unsigned char *)(sml_file ), i);
							free(sml_file);
							i = -1;
							esc = 0;
							end = 0;
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
	printf("error: no end sequence found, buffer full.");
}




