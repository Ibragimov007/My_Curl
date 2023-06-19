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

#include "../headers/dns_prepare.h"

// Gets the DNS server from /etc/resolv.conf file on Linux.
char* get_dns_server()
{
    int fd = open("/etc/resolv.conf", O_RDONLY);
    if (fd < 0) my_perror("Failed opening /etc/resolv.conf file.\n");
    char* string = NULL;
    char* nameserver = "nameserver";
    char** pointer = NULL;
    while ((string = my_readline(fd)) != NULL)
    {
        if (my_strncmp(string, nameserver, my_strlen(nameserver)) == 0)
        {
            pointer = my_strtok(string, " ");
            break;
        }
        free(string);
    }
    close(fd);
    char* return_string = malloc(sizeof(char) * 17);
    my_strcpy(return_string, pointer[1]);  // Copies the dns ip.
    free(string);
    free(pointer);
    return return_string;
}

// Converts www.example.com to 3www7example3com0 .
void change_to_dns_name_format(char* qname, char* host)
{
    int log = 0;
    int length = my_strlen(host) + 1;
    for (int i = 0; i < length; i++)
    {
        if (host[i] == '.' || i + 1 == length)
        {
            *qname++ = i - log;  // Saves the character count.
            for (; log < i; log++)
            {
                *qname++ = host[log];
            }
            log++;
        }
    }
    *qname++ = '\0';
}
