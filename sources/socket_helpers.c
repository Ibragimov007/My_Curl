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

#include "../headers/socket_helpers.h"

// Shows off my_gethostbyname on only two example it works reliably.
// Calls now standard getaddrinfo otherwise.
int fill_sockaddr(struct sockaddr_in* server, char* domain_name)
{
    char* address = my_gethostbyname(domain_name);
    if (!address)
    {
        resolve_error(domain_name);
        return 1;
    }
    my_inet_aton(address, &server->sin_addr);
    free(address);
    /*  We used getaddrinfo during development.
        struct addrinfo* res = NULL;
        int gai_error = getaddrinfo(domain_name, "80", 0, &res);
        if (gai_error)
        {
            resolve_error(domain_name);
            return 1;
        }
        // Skips the address family and copies ipv4 address.
        memcpy(&server->sin_addr, res->ai_addr->sa_data + 2, 4);
        freeaddrinfo(res);
    */
    return 0;
}

// Writes to standard error output.
int resolve_error(char* domain_name)
{
    char* s1 = "could not resolve host: ";
    write(2, s1, my_strlen(s1));
    write(2, domain_name, my_strlen(domain_name));
    write(2, "\n", 1);
    free(domain_name);
    return 0;
}

// Iterates over buffer to find the matching string.
int skip_header(char* buffer, int size)
{
    int flag = 0;
    int i = 0;
    while (!flag && i + 3 < size)
    {
        if (my_strncmp(buffer + i, "\r\n\r\n", 4) == 0)
        {
            flag = 1;
            i += 3;
        }
        i++;
    }
    return i;
}

// Looks up the match, allocates a string, copies the number
// to it, converts to numeric and returns the result.
int find_length(char* buffer, int size)
{
    char* string_1 = "Content-Length: ";
    int length_1 = my_strlen(string_1);
    int i = 0;
    while (i + length_1 < size)
    {
        if (my_strncmp(buffer + i, string_1, length_1) == 0)
        {
            i += length_1;
            break;
        }
        i++;
    }
    char* string_2 = malloc(sizeof(char) * 20);
    int j = 0;
    while (buffer[i + j] != '\r')
    {
        string_2[j] = buffer[i + j];
        j++;
    }
    string_2[j] = '\0';
    int length_2 = my_atoi(string_2);
    free(string_2);
    return length_2;
}
