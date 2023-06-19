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

#ifndef MY_CURL_HEADERS_DNS_STRUCTURES_H_
#define MY_CURL_HEADERS_DNS_STRUCTURES_H_

// DNS header structure. After the colons are the sizes of the bit fields.
typedef struct dns_header
{
    unsigned short id;          // identification number
    unsigned char qr : 1;       // query/response flag
    unsigned char opcode : 4;   // purpose of the message
    unsigned char aa : 1;       // authoritative answer
    unsigned char tc : 1;       // truncated message
    unsigned char rd : 1;       // recursion desired
    unsigned char ra : 1;       // recursion available
    unsigned char z : 3;        // reserved for future use
    unsigned char rcode : 4;    // response code
    unsigned short q_count;     // number of question entries
    unsigned short ans_count;   // number of answer entries
    unsigned short auth_count;  // number of authority entries
    unsigned short add_count;   // number of resource entries
} header_type;

// Constant sized fields of DNS query structure.
typedef struct question
{
    unsigned short qtype;
    unsigned short qclass;
} query_type;

// Constant sized fields of the resource record structure.
#pragma pack(push, 1)  // Avoiding structure padding.
typedef struct resource_record
{
    unsigned short type;
    unsigned short _class;
    unsigned int ttl;
    unsigned short data_len;
} rr_header;
#pragma pack(pop)

#endif  // MY_CURL_HEADERS_DNS_STRUCTURES_H_
