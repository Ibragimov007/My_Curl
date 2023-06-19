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

#ifndef MY_CURL_HEADERS_DNS_SEND_H_
#define MY_CURL_HEADERS_DNS_SEND_H_

#include "dns_structures.h"
#include "../headers/dns_prepare.h"
#include "../headers/my_lib/my_inet.h"

// Sends the dns query. Returns the offset for read_address() .
int send_query(char* host, int dns_socket);

// Sets the parameters of dns query header.
int initialize_header(header_type* header);

#endif  // MY_CURL_HEADERS_DNS_SEND_H_
