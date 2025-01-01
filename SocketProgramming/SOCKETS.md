Stream Socket (SOCK_STREAM):
Connection Oriented, uses TCP/IP. IP is responsible for data routing and not for data
Integrity. Ensures the data sent to be error free and complete and in same order as it
was sent!!
Telnet uses the Stream Sockets.
Datagram Socket (SOCK_DGRAM):
Connectionless sockets. Uses UDP. Not reliable. Packet May/May does not reach but if
reached, will be error free. Uses IP for routing.
Used when TCP stack is either not available or few dropped packets doesn't harm (like
Video conferencing, Movies etc.)
Few applications like tfpt (trivial file transfer protocol uses the UDP, but on top of that
they have their own protocols to ensure the data integrity. File transfer doesn't need an
open connection every time and when the connection is available, next packet can Full screen (f
sent.


Big Endian (Network Byte Order) and Littel Endian
Big Endian Byte Order: The most significant byte (the "big end") of the data
is placed at the byte with the lowest address. The rest of the data is placed in
order in the next three bytes in memory.
Little Endian Byte Order: The least significant byte (the "little end") of the
data is placed at the byte with the lowest address. The rest of the data is
placed in order in the next three bytes in memory.
In these definitions, the data, a 32-bit pattern, is regarded as a 32-bit unsigned
integer. The "most significant" byte is the one for the largest powers of two:
231, ..., 224. The "least significant" byte is the one for the smallest powers of
two: 27, ..., 20.
For example, say that the 32-bit pattern 0x12345678 is stored at address
Ox00400000. The most significant byte is 0x12; the least significant is 0x78.
K
Apis (htons, nighs available for conversion to and from network to host byte.
Big Endian
12
34
56
0x00400002
78
Little Endian
78
56
34
0x00400002
0*00400001
0x00400000
12
Full screen (f)




