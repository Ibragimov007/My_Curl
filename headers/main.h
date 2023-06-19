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

#ifndef MY_CURL_HEADERS_MAIN_H_
#define MY_CURL_HEADERS_MAIN_H_

#include "../headers/http.h"
#include "../headers/tcp_socket.h"

#include "../headers/my_lib/my_stdio.h"
#include "../headers/my_lib/my_printf.h"

// Calls the http and socket functions.
int main(int argc, char* argv[]);

// Expects an URL as argument.
char* check_arguments(int argc, char** argv);

#endif  // MY_CURL_HEADERS_MAIN_H_
