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

#ifndef MY_CURL_HEADERS_SOCKET_HELPERS_H_
#define MY_CURL_HEADERS_SOCKET_HELPERS_H_

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "../headers/http.h"
#include "../headers/my_gethostbyname.h"
#include "../headers/my_lib/my_stdio.h"

// Calls either my_gethostbyname or getaddrinfo.
int fill_sockaddr(struct sockaddr_in* server, char* domain_name);

// Prints error message.
int resolve_error(char* domain_name);

// Searches for the double new line after header in HTTP response.
int skip_header(char* buffer, int size);

// Looks up "content length" field in an http header.
int find_length(char* buffer, int size);

#endif  // MY_CURL_HEADERS_SOCKET_HELPERS_H_
