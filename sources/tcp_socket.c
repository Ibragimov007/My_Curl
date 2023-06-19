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

#include "../headers/tcp_socket.h"

#define PORT 80
#define buffer_size 1024

// Strips the hostname, get the ip, connects to it.
int socket_connect(int tcp_socket, char* hostname)
{
    char* domain_name = get_domain_name(hostname);
    struct sockaddr_in server;
    if (fill_sockaddr(&server, domain_name)) return 0;
    server.sin_family = AF_INET;
    server.sin_port = my_htons(PORT);
    // Actually connect.
    if (connect(tcp_socket, (struct sockaddr*)&server, sizeof(server)) == -1)
    {
        my_perror("TCP connect failed.");
        free(domain_name);
        return 0;
    }
    free(domain_name);
    return 1;
}

// Non-blockingly writes the request to the socket.
int socket_write(int tcp_socket, char* request)
{
    int request_length = my_strlen(request);
    write(tcp_socket, request, request_length);
    int bytes_total = 0;
    int bytes_last = 0;
    while (bytes_total < request_length)
    {
        bytes_last = write(tcp_socket, request + bytes_total,
                           request_length - bytes_total);
        if (bytes_last == -1)
        {
            my_perror("TCP write failed.");
            exit(EXIT_FAILURE);
        }
        bytes_total += bytes_last;
    }
    return 0;
}

// Reads the response until it has the full length.
// Allocates large buffer for Gandalf.
int socket_read(int tcp_socket)
{
    char* buffer = malloc(sizeof(char) * (buffer_size * 1));
    my_memset(buffer, 0, buffer_size * 1);
    char* buffer_2 = malloc(sizeof(char) * (buffer_size * 50));
    my_memset(buffer_2, 0, buffer_size * 50);
    int bytes_read = read(tcp_socket, buffer, buffer_size);
    int length = find_length(buffer, bytes_read);
    int header = skip_header(buffer, buffer_size);
    int bytes_total = bytes_read - header;
    my_strncpy(buffer_2, buffer + header, bytes_read - header);
    while (bytes_total < length)
    {
        bytes_read = read(tcp_socket, buffer, buffer_size);
        my_strncpy(buffer_2 + bytes_total, buffer, bytes_read);
        bytes_total += bytes_read;
    }
    write(1, buffer_2, length);
    free(buffer);
    free(buffer_2);
    return 0;
}
