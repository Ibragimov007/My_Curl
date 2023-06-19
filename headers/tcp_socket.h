/*Copyright (C) 2023 Timur Timak, Zafarbek Ibragimov

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

#ifndef MY_CURL_HEADERS_TCP_SOCKET_H_
#define MY_CURL_HEADERS_TCP_SOCKET_H_

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>

#include "../headers/http.h"
#include "../headers/my_lib/my_stdio.h"
#include "../headers/socket_helpers.h"

// Calls the connect function on our TCP socket.
int socket_connect(int our_socket, char* hostname);

// Writes to the socket.
int socket_write(int our_socket, char* request);

// Reads from the socket.
int socket_read(int our_socket);

#endif  // MY_CURL_HEADERS_TCP_SOCKET_H_
