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

#ifndef MY_CURL_HEADERS_DNS_PREPARE_H_
#define MY_CURL_HEADERS_DNS_PREPARE_H_

#include <stdio.h>

#include "../headers/my_lib/my_printf.h"
#include "../headers/my_lib/my_string.h"
#include "../headers/my_lib/my_readline.h"
#include "../headers/my_lib/my_stdio.h"

// Returns the address of dns server.
char* get_dns_server();

// Conforms hostname for dns query.
void change_to_dns_name_format(char* qname, char* host);

#endif  // MY_CURL_HEADERS_DNS_PREPARE_H_
