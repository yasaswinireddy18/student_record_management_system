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

List all students

Search by ID

Search by name

Sort by grade (descending)

Sort by name (ascending)

Send data to server and exit

Exit without sending

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

Server:
• Records received: 5
• Receive time: ~34420 ms (local TCP overhead)
• Save time: ~1.01 ms

OBSERVED BOTTLENECKS & TRADE-OFFS

• CSV parsing grows linearly with file size
• Sorting is O(n log n)
• Network transmission time varies with Windows TCP buffer behavior
• Server is single-threaded (handles one client at a time)
• No concurrency or async implemented