// server/server.cpp (Winsock server)
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "../client/Performance.h"
#include "../client/student.h"

using namespace std;

int main() {
    PerfStats stats;
    Timer tReceive;

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        cerr << "WSAStartup failed\n";
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        cerr << "Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9002);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "Bind failed, err=" << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        cerr << "Listen failed, err=" << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Server listening on port 9002...\n";

    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "Accept failed, err=" << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    uint32_t countNet = 0;
    int rec = recv(clientSocket, reinterpret_cast<char*>(&countNet), sizeof(countNet), MSG_WAITALL);
    if (rec != sizeof(countNet)) {
        cerr << "Failed to read count\n";
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    uint32_t count = ntohl(countNet);

    vector<Student> students;
    students.reserve(count);

    string line;
    char ch;
    while (recv(clientSocket, &ch, 1, 0) > 0) {
        if (ch == '\n') {
            if (!line.empty()) {
                Student s;
                stringstream ss(line);
                string tok;
                getline(ss, tok, ','); s.id = stoi(tok);
                getline(ss, tok, ','); s.name = tok;
                getline(ss, tok, ','); s.age = stoi(tok);
                getline(ss, tok, ','); s.grade = stod(tok);
                students.push_back(s);
                line.clear();
            }
        } else {
            line.push_back(ch);
        }
    }

    stats.recordsProcessed = students.size();
    stats.transmitMs = tReceive.elapsedMs();

    Timer tSave;
    ofstream out("data/output.csv");
    if (!out.is_open()) {
        cerr << "Failed to open data/output.csv for writing\n";
    } else {
        for (const auto &s : students) out << s.toCSV() << "\n";
    }
    stats.saveMs = tSave.elapsedMs();

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    cout << "\n=== Server Perf ===\n";
    cout << "Records received: " << stats.recordsProcessed << "\n";
    cout << "Receive time: " << stats.transmitMs << " ms\n";
    cout << "Save time: " << stats.saveMs << " ms\n";

    return 0;
}

