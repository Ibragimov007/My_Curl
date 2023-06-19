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

#include "../headers/http.h"

// Removes the leading http:// scheme if there is one and returns a copy
// of the rest of the string.
char* http_remove(char* url)
{
    char* result = NULL;
    char* http = "http://";
    int size_of_http = my_strlen(http);
    int size_of_url = my_strlen(url);
    if (my_strncmp(url, http, size_of_http) == 0)
    {
        int result_size = size_of_url - size_of_http + 1;
        result = malloc(sizeof(char) * result_size);
        my_memset(result, '\0', result_size);
        my_strncpy(result, url + size_of_http, result_size - 1);
        result[result_size - 1] = '\0';
    }
    else
    {
        result = (char*)malloc(size_of_url + 1);
        my_memset(result, '\0', size_of_url + 1);
        my_strcpy(result, url);
    }
    return result;
}

// Looks for the first slash, copies everything before that.
char* get_domain_name(char* url)
{
    char* path_start = my_strchr(url, '/');
    char* domain_name = NULL;
    if (path_start == NULL)
    {
        int domain_name_length = my_strlen(url) + 1;
        domain_name = malloc(sizeof(char) * domain_name_length);
        my_strcpy(domain_name, url);
        domain_name[domain_name_length - 1] = '\0';
        return domain_name;
    }
    else
    {
        int domain_name_length = path_start - url;
        // Allocate a buffer for the domain name.
        domain_name = malloc(domain_name_length + 1);
        my_strncpy(domain_name, url, domain_name_length);
        domain_name[domain_name_length] = '\0';
    }
    return domain_name;
}

// Returns pointer to the first slash.
char* get_path(char* url)
{
    char* path_start = my_strchr(url, '/');
    if (path_start == NULL)
    {
        return NULL;
    }
    else
    {
        return path_start;
    }
}

// Adds the desired path to the request and asks to close the connection
// after response.
char* prepare_http_request(char* hostname)
{
    int max_length = 1024;
    char* request = malloc(sizeof(char) * max_length);
    my_memset(request, '\0', max_length);
    char request_template[] = "GET %s HTTP/1.1\r\nHost: %s\r\n%s\r\n";
    char* connection_close = "";//Connection: close";
    char* domain_name = get_domain_name(hostname);
    char* path = get_path(hostname);
    if (path == NULL) path = "/";
    int request_length = snprintf(request, max_length, request_template, path,
                                  domain_name, connection_close);
    free(domain_name);
    if (request_length >= max_length)
    {
        my_perror("Request is too long.");
        free(request);
        return NULL;
    }
    return request;
}
