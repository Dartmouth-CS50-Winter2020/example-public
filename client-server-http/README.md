# Simple HTTP server and client

David Kotz, May 2016

### To build
`make all`

### Local testing

You can run both the client and server on the same machine, very easily.

Start the server in one window:

```
./httpserver
Listening at port 52222
```

Run the client in another window, using the 'loopback' address `127.0.0.1` and the port number provided above:

```
$ ./httpclient 127.0.0.1 52222 /ffff
HTTP/1.1 404 Not Found
Server: CS50/1.0 (Kotz)
Connection: close

```

### Remote testing

You can run the client and server on separate machines.

Start the server on a well-known machine like `flume`:

```
./httpserver
Listening at port 52222
```

On any other Internet-connected machine, give the server's hostname and the port provided above.

```
$ ./httpclient flume.cs.dartmouth.edu 52222 /ffff
HTTP/1.1 404 Not Found
Server: CS50/1.0 (Kotz)
Connection: close

```

### To run the server on your laptop

If you run the server on a host that does not have a hostname, you need to find its IP address.

On a Mac,
```ifconfig | grep 'inet '```
to find your IP address.
For example,

```
$ ifconfig | grep 'inet '
	inet 127.0.0.1 netmask 0xff000000
	inet 10.1.10.163 netmask 0xffffff00 broadcast 10.1.10.255
```

Ignore the first line - that's the loopback address.
The second line provides our current IP address.
Some addresses are 'private' to the local network, and can only be reached by other clients on the same network.
(This is common on home networks, Wi-Fi hotspots, and on campus.)  You can recognize these addresses because they look like `10.*.*.*`, `172.16.*`-`172.31.*.*`, or `192.168.*.*`.

See [Wikipedia](https://en.wikipedia.org/wiki/Private_network) for more information.

### HTTP info

We can see how HTTP works by using `telnet` to connect to a real web server, and typing a simple HTTP `GET` request by hand:

```
[cs50@flume ~]$ telnet www.cs.dartmouth.edu 80
Trying 129.170.213.101...
Connected to www.cs.dartmouth.edu.
Escape character is '^]'.
GET /~cs50/index.html HTTP/1.1           <== I typed this
HOST: www.cs.dartmouth.edu               <== and this
                                         <== and a blank line
HTTP/1.1 200 OK
Date: Wed, 20 Apr 2016 12:39:57 GMT
Server: Apache/2.4.10 (Fedora)
Last-Modified: Wed, 20 Apr 2016 02:56:05 GMT
ETag: "c7a-530e1bc17bb40"
Accept-Ranges: bytes
Content-Length: 3194
Connection: close
Content-Type: text/html; charset=UTF-8

<!DOCTYPE html>
<html>

...
</html>
```

Our client only sends those two lines - `GET` and `HOST` - and our server only pays attention to the `GET` line.
