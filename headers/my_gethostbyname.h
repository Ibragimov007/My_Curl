/*Copyright (C) 2023 Timur Timak

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public
License along with this program. If not, see
<https://www.gnu.org/licenses/>. */

#ifndef MY_CURL_HEADERS_MY_GETHOSTBYNAME_H_
#define MY_CURL_HEADERS_MY_GETHOSTBYNAME_H_

#include <stdlib.h>
#include <sys/socket.h>
#include <stdint.h>

#include "../headers/dns_send.h"
#include "../headers/my_lib/my_stdio.h"
#include "../headers/my_lib/my_string.h"

// Returns the ip address of a host.
char* my_gethostbyname(char* host);

// Returns address from dns response.
char* read_address(char* buffer, int offset);

// Waits until DNS responds or picks another one.
int wait_dns(int dns_socket, char* buffer, int buffer_size,
             struct sockaddr_in* destination, char* host);

// Contains the select function for non-blocking read.
int timer(int socket);

#endif  // MY_CURL_HEADERS_MY_GETHOSTBYNAME_H_
