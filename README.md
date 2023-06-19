# Welcome to My Curl
***

## Task
We had to replicate a simple behavior of the curl app that was initiated by\
Daniel Stenberg.

## Description
The hardest part was the resolution of names to IP addresses.

Callgraph in graph.png and graph.svg .

We used the stock getaddrinfo() during development as even curl.se\
uses it and man pages tell us that gethostbyname() is obsolete.\
We made a bleak imitation of gethostbyname to understand how it works.\
It doesn't handle recursions, it reads only the first response from the\
server.

There aren't that many http sites that don't redirect you to https,\
we test with what we could find:\
example.com\
httpbin.org\
http.badssl.com\
httpforever.com\
captive.apple.com\
google.com

my_gethostbyname() looks up the DNS address in /etc/resolv.conf,\
asks it, if it doesn't respond in 3 seconds it asks Cloudflare's DNS.

A better but slower solution would be make iterative requests to the root\
servers, then to TLD servers and the to the authoritative ones.

After that we just send a GET http request, strip the header off of it\
save the response into a large buffer for Gandalf and write it to stdout.

## Installation
Get yourself a copy and run make in the root folder of the project.

## Usage
Give an URL as argument and expect to see HTML page printed out.

```
$>./my_curl google.com
<HTML><HEAD><meta http-equiv="content-type" content="text/html;charset=utf-8">
<TITLE>301 Moved</TITLE></HEAD><BODY>
<H1>301 Moved</H1>
The document has moved
<A HREF="http://www.google.com/">here</A>.
</BODY></HTML>
$>
```

### The Core Team
Timur Timak\
Zafarbek Ibragimov

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
