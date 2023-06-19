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

#include "../headers/my_gethostbyname.h"

// Creates and connects the socket, sends DNS query and returns the
// address from the response.
char* my_gethostbyname(char* host)
{
    struct sockaddr_in destination;
    destination.sin_family = AF_INET;
    destination.sin_port = my_htons(53);
    char* dns_server = get_dns_server();
    my_inet_aton(dns_server, &destination.sin_addr);
    free(dns_server);
    // UDP socket for DNS queries.
    int dns_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (dns_socket == -1)
    {
        my_perror("Could not create DNS socket\n");
        exit(EXIT_FAILURE);
    }
    connect(dns_socket, (struct sockaddr*)&destination, sizeof(destination));
    int offset = send_query(host, dns_socket);
    int buffer_size = 512;
    char* buffer = malloc(sizeof(char) * (buffer_size + 1));
    my_memset(buffer, 0, buffer_size + 1);
    int new_offset =
        wait_dns(dns_socket, buffer, buffer_size, &destination, host);
    if (new_offset) offset = new_offset;
    unsigned char rcode = (unsigned char)buffer[3] << 4;
    if (rcode != 0) return NULL;
    char* returned_address = read_address(buffer, offset);
    free(buffer);
    return returned_address;
}

// Finds address in buffer with offset, and returns it in a new string.
char* read_address(char* buffer, int offset)
{
    // Skips the dns header and query fields.
    char* reader = &buffer[offset];
    reader += sizeof(short);  // Skips the compressed name field.
    // Skips the resource record header.
    reader = reader + sizeof(rr_header);
    struct sockaddr_in address;
    // Working without ntohl.
    address.sin_addr.s_addr = *((uint32_t*)reader);
    char* returned_address = my_inet_ntoa(address.sin_addr);
    return returned_address;
}

// Tries to read from socket until timer expires. Connects to Cloudflare
// in case it fails.
int wait_dns(int dns_socket, char* buffer, int buffer_size,
             struct sockaddr_in* destination, char* host)
{
    int bytes_total = 0;
    int bytes_new = 0;
    int offset = 0;
    if (timer(dns_socket))
    {
        // We could have read in a loop until we read a certain length,
        // but the packet is usually so small it comes in one piece.
        if ((bytes_new = read(dns_socket, buffer + bytes_total,
                              buffer_size - bytes_total)) <
            0)  // Receive the answer.
        {
            my_perror("Read from DNS socket failed.");
        }
    }
    else
    {
        char* dns_server = malloc(sizeof(char) * 8);
        my_strcpy(dns_server, "1.1.1.1");
        my_inet_aton(dns_server, &destination->sin_addr);
        free(dns_server);
        connect(dns_socket, (struct sockaddr*)destination,
                sizeof(*destination));
        offset = send_query(host, dns_socket);  // Sends query.
        if ((bytes_new = read(dns_socket, buffer + bytes_total,
                              buffer_size - bytes_total)) <
            0)  // Receives the answer.
        {
            my_perror("Read from DNS socket failed.");
        }
    }
    close(dns_socket);
    return offset;
}

// Prepares the input set and timer, calls for select().
int timer(int socket)
{
    fd_set input_set;
    struct timeval timeout;
    int ready_for_reading = 0;
    // Initializes the set.
    FD_ZERO(&input_set);
    // Listens to the input descriptor.
    FD_SET(socket, &input_set);
    timeout.tv_sec = 3;   // Waits for 3 seconds.
    timeout.tv_usec = 0;  // and 0 microseconds.
    ready_for_reading = select(socket + 1, &input_set, NULL, NULL, &timeout);
    return ready_for_reading;
}