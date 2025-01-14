[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/YLTza_-c)
# <p align="center">PA5: The Server Moved Out!<p>

**Introduction**

In this programming assignment, you will be adding a class called TCPRequestChannel to extend the IPC capabilities of the client-server implementation in PA3 using the TCP/IP protocol. The client-side and server-side ends of a TCPRequestChannel will reside on different machines.

Since the communication API (not just the underlying functionality and features) through TCP/IP is different from FIFO, you will also need to restructure the server.cpp and client.cpp as part of this programming assignment:

- The server program must be modified to handle incoming requests across the network request channels using the TCP/IP protocol. Specifically, the server must be able to handle multiple request channels from the client residing on a different machine. 

- You must also modify the client to send requests across the network request channels using the TCP/IP protocol.


**Tasks**

- [ ] Implement the TCPRequestChannel class
  - [ ] write the TCPRequestChannel(string, string) and TCPRequestChannel(int) constructors
  - [ ] write the destructor
  - [ ] write accept_conn() so the server can accept client connections
  - [ ] write cread(void*, int) and cwrite(void*, int) methods
- [ ] Modify client
  - [ ] add a and r options
  - [ ] change request channel instances to TCPRequestChannel
- [ ] Modify server
  - [ ] add r option
  - [ ] implement server's primary channel
  - [ ] implement server's accept loop

See the PA5 module on Canvas for further details and assistance.
