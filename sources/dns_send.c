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

#include "../headers/dns_send.h"

// Composes the message and writes it to the socket.
int send_query(char* host, int dns_socket)
{
    char buffer[512] = {0};
    // Prepares header.
    int header_length = sizeof(header_type);
    header_type* header = malloc(sizeof(char) * header_length);
    initialize_header(header);
    my_memcpy(buffer, (char*)header, header_length);
    free(header);
    int offset = header_length;
    // Prepares body.
    char* qname = &buffer[offset];
    change_to_dns_name_format(qname, host);
    offset += my_strlen(qname) + 1;
    query_type* qinfo = (query_type*)&buffer[offset];
    qinfo->qtype = my_htons(1);   // Type A - we need an ip address.
    qinfo->qclass = my_htons(1);  // IN - the internet.
    offset += sizeof(query_type);
    // Actually sends.
    int bytes_total = 0;
    int bytes_last = 0;
    int request_length = offset;
    while (bytes_total < request_length)
    {
        bytes_last = write(dns_socket, buffer + bytes_total,
                           request_length - bytes_total);
        if (bytes_last == -1)
        {
            my_perror("UDP write failed.");
            exit(EXIT_FAILURE);
        }
        bytes_total += bytes_last;
    }
    return offset;
}

int initialize_header(header_type* header)
{
    header->id = 3;
    header->qr = 0;            // This is a query.
    header->opcode = 0;        // This is a standard query.
    header->aa = 0;            // Not authoritative.
    header->tc = 0;            // This message is not truncated.
    header->rd = my_htons(1);  // Recursion desired.
    header->ra = 0;            // Recursion not available.
    header->z = 0;
    header->rcode = 0;
    header->q_count = my_htons(1);  // We have only 1 question.
    header->ans_count = 0;
    header->auth_count = 0;
    header->add_count = 0;
    return 0;
}
