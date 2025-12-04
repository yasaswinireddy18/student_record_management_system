Student Record Management System (C++)

A mini system demonstrating object-oriented programming, file handling, data processing, TCP networking (Winsock), and performance monitoring.

Features:
• Load student data from CSV
• List all students
• Search by ID, name
• Sort by grade (descending), name (ascending)
• Interactive client menu
• Send data to server via TCP
• Server receives data and saves to output CSV
• Performance tracking


PROJECT FOLDER STRUCTURE
![Project Folder](https://github.com/yasaswinireddy18/student_record_management_system/blob/main/screenshots/Project%20folder.png?raw=1)

STUDENT DATA:
Student Data (students.txt)
![Student Data](https://raw.githubusercontent.com/yasaswinireddy18/student_record_management_system/refs/heads/main/screenshots/student_data.png)

HOW TO RUN THE PROJECT

Requirements:
• MinGW (g++)
• Git Bash / Windows Terminal
• Winsock (built into Windows)

Steps:

1. Open two terminals
    One for server, one for client.
2. Run the server
   ./server_app.exe

Expected output:
Server listening on port 9002...

3. Run the client
  ./client_app.exe

Client shows the menu:

1. List all students

2. Search by ID

3. Search by name

4. Sort by grade (descending)

5. Sort by name (ascending)

6. Send data to server and exit

7. Exit without sending

SEARCHING FOR STUDENT DETAILS

Search by ID:
• Choose option 2
• Enter numeric ID
• System prints matching student or “not found”

Search by Name:
• Choose option 3
• Enter full name (case-sensitive)
• Prints all matching students or “not found”

SENDING DATA TO SERVER

Choose option 6 in the client.
Client will sort the data, send it to the server, and show performance stats.

Server will receive data and save it to:
data/output.csv

## Client Menu and Initial Output
![Menu and Output](https://raw.githubusercontent.com/yasaswinireddy18/student_record_management_system/refs/heads/main/screenshots/output1.png)

## Continued Output
![Output Continuation](https://raw.githubusercontent.com/yasaswinireddy18/student_record_management_system/refs/heads/main/screenshots/output2.png)




BUILD COMMANDS (LOCAL COMPILATION)

Build Server:

g++ -std=c++17 -Iclient -o server_app.exe server/server.cpp client/StudentManager.cpp -lws2_32 -mconsole


Build Client:

g++ -std=c++17 -Iclient -o client_app.exe client/main_client.cpp client/StudentManager.cpp -lws2_32 -mconsole


PERFORMANCE METRICS (EXAMPLE)

Client:
• Records processed: 5
• Load time: ~0.30 ms
• Sort time: ~0.01 ms
• Transmit time: ~3.42 ms
## Client Performance Output
![Client Performance](https://raw.githubusercontent.com/yasaswinireddy18/student_record_management_system/refs/heads/main/screenshots/client_performance.png)


Server:
• Records received: 5
• Receive time: ~34420 ms (local TCP overhead)
• Save time: ~1.01 ms

## Server Performance Output
![Server Performance](https://raw.githubusercontent.com/yasaswinireddy18/student_record_management_system/refs/heads/main/screenshots/server%20performance.png)

OBSERVED BOTTLENECKS & TRADE-OFFS

• CSV parsing grows linearly with file size
• Sorting is O(n log n)
• Network transmission time varies with Windows TCP buffer behavior
• Server is single-threaded (handles one client at a time)
• No concurrency or async implemented