#include "StudentManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

bool StudentManager::loadFromCSV(const string &filePath, PerfStats &stats) {
    Timer t;
    ifstream in(filePath);
    if (!in.is_open()) {
        cerr << "Failed to open " << filePath << "\n";
        return false;
    }

    students.clear();
    string line;

    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string token;
        Student s;

        getline(ss, token, ',');
        s.id = stoi(token);

        getline(ss, token, ',');
        s.name = token;

        getline(ss, token, ',');
        s.age = stoi(token);

        getline(ss, token, ',');
        s.grade = stod(token);

        students.push_back(s);
    }

    stats.recordsProcessed = students.size();
    stats.loadMs = t.elapsedMs();
    return true;
}

bool StudentManager::saveToCSV(const string &filePath, PerfStats &stats) const {
    Timer t;
    ofstream out(filePath);
    if (!out.is_open()) {
        cerr << "Failed to save to " << filePath << "\n";
        return false;
    }

    for (const auto &s : students) {
        out << s.toCSV() << "\n";
    }

    stats.saveMs = t.elapsedMs();
    return true;
}

void StudentManager::listAll() const {
    for (const auto &s : students) {
        cout << s.id << " | " << s.name
             << " | age: " << s.age
             << " | grade: " << s.grade << "\n";
    }
}

const Student* StudentManager::searchById(int id) const {
    for (const auto &s : students) {
        if (s.id == id) return &s;
    }
    return nullptr;
}

vector<Student> StudentManager::searchByName(const string &name) const {
    vector<Student> result;
    for (const auto &s : students) {
        if (s.name == name) result.push_back(s);
    }
    return result;
}

void StudentManager::sortById(PerfStats &stats) {
    Timer t;
    sort(students.begin(), students.end(),
        [](const Student &a, const Student &b) {
            return a.id < b.id;
        });
    stats.sortMs = t.elapsedMs();
}

void StudentManager::sortByGrade(PerfStats &stats) {
    Timer t;
    sort(students.begin(), students.end(),
        [](const Student &a, const Student &b) {
            return a.grade > b.grade;
        });
    stats.sortMs = t.elapsedMs();
}

void StudentManager::sortByName(PerfStats &stats) {
    Timer t;
    sort(students.begin(), students.end(),
        [](const Student &a, const Student &b) {
            return a.name < b.name;
        });
    stats.sortMs = t.elapsedMs();
}

