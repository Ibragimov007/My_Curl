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

#include "../headers/main.h"

// Opens and closes the TCP socket, prepares the request and
// receives the response.
int main(int argc, char* argv[])
{
    char* hostname = check_arguments(argc, argv);
    if (!hostname) return 1;
    int tcp_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (tcp_socket == -1)
    {
        my_perror("Could not create TCP socket\n");
        return 1;
    }
    char* request = prepare_http_request(hostname);
    if (!request)
    {
        free(hostname);
        return 1;
    }
    int connected = socket_connect(tcp_socket, hostname);
    free(hostname);
    if (connected)
    {
        socket_write(tcp_socket, request);
        socket_read(tcp_socket);
    }
    close(tcp_socket);
    free(request);
    return 0;
}

char* check_arguments(int argc, char** argv)
{
    if (argc != 2)
    {
        my_printf("Format: my_curl <URL>\n");
        my_printf("Try one of the following:\n");
        my_printf("example.com \nhttpbin.org \nhttp.badssl.com \n");
        my_printf("httpforever.com \ncaptive.apple.com \ngoogle.com\n");
        return NULL;
    }
    char* hostname = http_remove(argv[1]);
    return hostname;
}
