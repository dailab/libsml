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

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sml/sml.h>
#include <sml/sml_transport.h>

void transport_receiver(unsigned char *buffer, size_t buffer_len) {
    // the buffer contains the whole message, with transport escape sequences.
    // these escape sequences are stripped here. 
    sml_file *file = sml_file_parse(buffer + 8, buffer_len - 16);
    
    // the sml file is parsed
    sml_file_print(file);
    
    // all elements returned by parsing functions must be free'd
    sml_file_free(file);
}

int main(int argc, char **argv) {
    char *device = "your device here";
    
    // this depends on your device (serial port, ip)
    int fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0) {
        printf("error: %s - %s\n", device, strerror(errno));
        return -1;
    }
    
    // this is a blocking call
    sml_transport_listen(fd, &transport_receiver);
    
    close(fd);
    return 0;
}
