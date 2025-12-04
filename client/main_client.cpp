#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include "StudentManager.h"
#include "student.h"
#include "Performance.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

bool sendStudentsTCP(const vector<Student>& students, const string& host, int port, PerfStats &stats) {
    Timer t;
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        cerr << "WSAStartup failed\n";
        return false;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        cerr << "socket failed\n";
        WSACleanup();
        return false;
    }

    sockaddr_in serv{};
    serv.sin_family = AF_INET;
    serv.sin_port = htons(port);

    if (inet_pton(AF_INET, host.c_str(), &serv.sin_addr) != 1) {
        serv.sin_addr.s_addr = inet_addr(host.c_str());
    }

    if (connect(sock, (sockaddr*)&serv, sizeof(serv)) == SOCKET_ERROR) {
        cerr << "connect failed, err=" << WSAGetLastError() << "\n";
        closesocket(sock);
        WSACleanup();
        return false;
    }

    uint32_t cnt = htonl((uint32_t)students.size());
    if (send(sock, (const char*)&cnt, sizeof(cnt), 0) == SOCKET_ERROR) {
        cerr << "send count failed\n";
        closesocket(sock);
        WSACleanup();
        return false;
    }

    for (const auto &s : students) {
        string line = s.toCSV() + "\n";
        if (send(sock, line.c_str(), (int)line.size(), 0) == SOCKET_ERROR) {
            cerr << "send line failed\n";
            closesocket(sock);
            WSACleanup();
            return false;
        }
    }

    stats.transmitMs = t.elapsedMs();

    closesocket(sock);
    WSACleanup();
    return true;
}

int main() {
    PerfStats stats;
    StudentManager mgr;

    if (!mgr.loadFromCSV("data\\students.txt", stats)) {
        cerr << "load failed\n";
        return 1;
    }

    cout << "Loaded " << mgr.size() << " students\n";
    mgr.sortByGrade(stats);
    cout << "After sort by grade:\n";
    mgr.listAll();

    if (!sendStudentsTCP(mgr.getAll(), "127.0.0.1", 9002, stats)) {
        cerr << "send failed\n";
        return 1;
    }

    cout << "\n=== Client Perf ===\n";
    cout << "records: " << stats.recordsProcessed << "\n";
    cout << "load ms: " << stats.loadMs << "\n";
    cout << "sort ms: " << stats.sortMs << "\n";
    cout << "transmit ms: " << stats.transmitMs << "\n";

    return 0;
}

