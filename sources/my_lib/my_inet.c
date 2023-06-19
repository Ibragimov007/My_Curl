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

#include "../../headers/my_lib/my_inet.h"

uint16_t my_htons(uint16_t hostshort)
{
    if (check_endiannes()) return hostshort;
    char array[2] = {0};
    // Reimagines hostshort as a char array and fills the local array
    // with its bytes in reverse order.
    array[0] = *((char*)&hostshort + 1);
    array[1] = *(char*)&hostshort;
    // Casts char pointer to int pointer.
    uint16_t netshort = *(uint16_t*)array;
    return netshort;
}

uint16_t my_ntohs(uint16_t netshort)
{
    if (check_endiannes()) return netshort;
    // Bitwise OR of netshort divided by 2 to the power of 8 and
    // netshort multiplied by the same number.
    uint16_t hostshort = (netshort >> 8) | (netshort << 8);
    return hostshort;
}

int my_inet_aton(char* string, struct in_addr* int32_struct)
{
    char array[4] = {0};
    char** tokens = my_strtok(string, ".");
    int i = 0;
    char** tokens_head = tokens;
    while (*tokens)
    {
        array[i] = my_atoi(*tokens);
        tokens++;
        i++;
    }
    free(tokens_head);
    int32_struct->s_addr = *(uint32_t*)array;
    return 1;
}

char* my_inet_ntoa(struct in_addr int32_struct)
{
    int i = 0;
    unsigned char* pointer = (unsigned char*)(&int32_struct.s_addr);
    char* string = malloc(sizeof(char) * 16);
    my_memset(string, '\0', 16);
    char* string_new = NULL;
    while (i < 4)
    {
        string_new = my_itoa(pointer[i]);
        string = my_strcat(string, string_new);
        free(string_new);
        if (i != 3)
        {
            string = my_strcat(string, ".");
        }
        i++;
    }
    return string;
}

int check_endiannes()
{
    int x = 1;
    if (*(char*)&x)
    {
        return 0;  // The processor is little endian.
    }
    return 1;  // The processor is big endian.
}
