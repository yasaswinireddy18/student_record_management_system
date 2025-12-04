# \# Student Record Management System (C++ / Winsock)

# 

# A mini system demonstrating object-oriented programming, file handling, data processing, TCP networking (Winsock), and performance monitoring.

# 

# This project includes:

# \- Reading student data from CSV

# \- Listing, searching, and sorting records

# \- Sending data via TCP client (Winsock)

# \- Receiving data via TCP server (Winsock)

# \- Saving received data to output CSV

# \- Tracking and reporting performance metrics

# 

# ---

# 

# \## 🚀 How to Run the Project (Windows)

# 

# \### Requirements

# \- MinGW (g++)

# \- Windows terminal (MSYS2 / Git Bash)

# \- Winsock (comes with Windows)

# 

# ---

# 

# \## 🛠️ Build Commands

# 

# \### Compile the Server

# ```bash

# g++ -std=c++17 -Iclient -o server\_app.exe server/server.cpp client/StudentManager.cpp -lws2\_32 -mconsole



