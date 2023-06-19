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

#ifndef MY_CURL_HEADERS_MY_INET_H_
#define MY_CURL_HEADERS_MY_INET_H_

#include <netinet/in.h>
#include <stdlib.h>

#include "../../headers/my_lib/my_stdlib.h"

// Converts the hostshort from host byte order to network byte order.
uint16_t my_htons(uint16_t hostshort);

// Converts the hostshort from newtwork byte order to host byte order.
uint16_t my_ntohs(uint16_t netshort);

// Converts the Internet host address in string from the IPv4
// numbers-and-dots notation into binary form (in network byte order)
// and stores it in the structure that int32_struct points to.
int my_inet_aton(char* string, struct in_addr* int32_struct);

// Converts the Internet host address int32_struct, given in network byte
// order, to a string in IPv4 dotted-decimal notation.
// Don't forget to free the returned string.
char* my_inet_ntoa(struct in_addr int32_struct);

// Returns 1 if the architecture is big-endian and 0 otherwise.
int check_endiannes();

#endif  // MY_CURL_HEADERS_MY_INET_H_
