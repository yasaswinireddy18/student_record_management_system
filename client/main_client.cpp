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

    uint32_t cnt = htonl(static_cast<uint32_t>(students.size()));
    if (send(sock, reinterpret_cast<const char*>(&cnt), sizeof(cnt), 0) == SOCKET_ERROR) {
        cerr << "send count failed\n";
        closesocket(sock);
        WSACleanup();
        return false;
    }

    for (const auto &s : students) {
        string line = s.toCSV() + "\n";
        if (send(sock, line.c_str(), static_cast<int>(line.size()), 0) == SOCKET_ERROR) {
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
        cerr << "Failed to load students. Exiting.\n";
        return 1;
    }

    cout << "Loaded " << mgr.size() << " students\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. List all students\n";
        cout << "2. Search by ID\n";
        cout << "3. Search by name\n";
        cout << "4. Sort by grade (descending)\n";
        cout << "5. Sort by name (asc)\n";
        cout << "6. Send data to server and exit\n";
        cout << "7. Exit without sending\n";
        cout << "Choose an option: ";
        int opt;
        if (!(cin >> opt)) {
            cin.clear();
            string dummy;
            getline(cin, dummy);
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (opt == 1) {
            mgr.listAll();
        } else if (opt == 2) {
            cout << "Enter ID: ";
            int id; cin >> id;
            const Student* s = mgr.searchById(id);
            if (s) {
                cout << s->id << " | " << s->name << " | age: " << s->age << " | grade: " << s->grade << "\n";
            } else {
                cout << "No student found with ID " << id << "\n";
            }
        } else if (opt == 3) {
            cout << "Enter full name to search (case-sensitive): ";
            string name;
            // consume leftover newline
            getline(cin, name);
            if (name.empty()) getline(cin, name);
            vector<Student> res = mgr.searchByName(name);
            if (res.empty()) {
                cout << "No students found with name: " << name << "\n";
            } else {
                for (const auto &st : res) {
                    cout << st.id << " | " << st.name << " | age: " << st.age << " | grade: " << st.grade << "\n";
                }
            }
        } else if (opt == 4) {
            mgr.sortByGrade(stats);
            cout << "Sorted by grade (desc).\n";
        } else if (opt == 5) {
            mgr.sortByName(stats);
            cout << "Sorted by name (asc).\n";
        } else if (opt == 6) {
            // before sending, show a brief summary
            cout << "\nPreparing to send " << mgr.size() << " records to server...\n";
            if (!sendStudentsTCP(mgr.getAll(), "127.0.0.1", 9002, stats)) {
                cerr << "Failed to send data to server.\n";
                return 1;
            }
            cout << "\n=== Client Perf ===\n";
            cout << "records: " << stats.recordsProcessed << "\n";
            cout << "load ms: " << stats.loadMs << "\n";
            cout << "sort ms: " << stats.sortMs << "\n";
            cout << "transmit ms: " << stats.transmitMs << "\n";
            break;
        } else if (opt == 7) {
            cout << "Exiting without sending.\n";
            break;
        } else {
            cout << "Unknown option. Try again.\n";
        }
    }

    return 0;
}

