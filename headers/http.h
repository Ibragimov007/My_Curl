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

#ifndef MY_CURL_HEADERS_HTTP_H_
#define MY_CURL_HEADERS_HTTP_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../headers/my_lib/my_string.h"
#include "../headers/my_lib/my_stdio.h"

// Removes the leading http:// scheme from URL.
char* http_remove(char* url);

// Strips the path off URL.
char* get_domain_name(char* url);

// Gets the path part of an URL.
char* get_path(char* url);

// Prepares a GET request.
char* prepare_http_request(char* hostname);

#endif  // MY_CURL_HEADERS_HTTP_H_
