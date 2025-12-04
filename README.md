# Student Record Management System (C++)

##### 

##### A mini system demonstrating object-oriented programming, file handling, data processing, TCP networking (Winsock), and performance monitoring.

##### 

##### This student record management system includes:

##### \- Reading student data from CSV

##### \- Listing, searching, and sorting records

##### \- Sending data via TCP client (Winsock)

##### \- Receiving data via TCP server (Winsock)

##### \- Saving received data to output CSV

##### \- Tracking and reporting performance metrics

##### 

##### 

##### 

### \# How to Run the Project

##### 

* #### Requirements

##### \- MinGW (g++)

##### \- Windows terminal (Git Bash)

##### \- Winsock

##### 

##### 

* #### Steps to run the project:

##### 

1. open two terminals
    one runs the server and other for the client.
   
   ---
2. ##### start the server terminal

##### &nbsp;  go to the project folder and run server

##### &nbsp;  Run server: ./server\_app.exe



##### 3\. start the client terminal 

##### &nbsp;  go to the project folder and run client

##### &nbsp;  Run client: ./client\_app.exe

##### 



* #### output: 



##### Loads students from data/students.txt



##### Sorts them



##### Sends them to the server



##### Shows performance stats

##### 

##### 

### \# Build Commands

##### 

* #### &nbsp;Compile the Server



##### g++ -std=c++17 -Iclient -o server\_app.exe server/server.cpp client/StudentManager.cpp -lws2\_32 -mconsole

#### 

#### 

* #### Compile the Client



##### g++ -std=c++17 -Iclient -o client\_app.exe client/main\_client.cpp client/StudentManager.cpp -lws2\_32 -mconsole



##### 

### \# Performance Metrics

##### 

##### The system reports basic performance statistics on both client and server sides.

##### 

##### 

* #### Client Performance

##### 

##### === Client Perf ===

##### records: 5

##### load ms: 0.3046

##### sort ms: 0.0138

##### transmit ms: 3.4218

##### 

* #### Server Performance



##### === Server Perf ===

##### Records received: 5

##### Receive time: 34420.4 ms

##### Save time: 1.0134 ms

##### 

##### 

### \# Observed Bottlenecks \& Trade-offs

##### 

##### CSV parsing time increases linearly with input size

##### 

##### Sorting time depends on record count (O(n log n))

##### 

##### Transmission time depends on network overhead and number of records

##### 

##### Server currently handles one client at a time (no concurrency)

##### 

