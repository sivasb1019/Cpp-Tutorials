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