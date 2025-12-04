#include "StudentManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

bool StudentManager::loadFromCSV(const std::string &filePath, PerfStats &stats) {
    Timer t;
    std::ifstream in(filePath);
    if (!in.is_open()) {
        std::cerr << "Failed to open " << filePath << "\n";
        return false;
    }

    students.clear();
    std::string line;

    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        Student s;

        std::getline(ss, token, ',');
        s.id = std::stoi(token);

        std::getline(ss, token, ',');
        s.name = token;

        std::getline(ss, token, ',');
        s.age = std::stoi(token);

        std::getline(ss, token, ',');
        s.grade = std::stod(token);

        students.push_back(s);
    }

    stats.recordsProcessed = students.size();
    stats.loadMs = t.elapsedMs();
    return true;
}

bool StudentManager::saveToCSV(const std::string &filePath, PerfStats &stats) const {
    Timer t;
    std::ofstream out(filePath);
    if (!out.is_open()) {
        std::cerr << "Failed to save to " << filePath << "\n";
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
        std::cout << s.id << " | " << s.name
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

std::vector<Student> StudentManager::searchByName(const std::string &name) const {
    std::vector<Student> result;
    for (const auto &s : students) {
        if (s.name == name) result.push_back(s);
    }
    return result;
}

void StudentManager::sortById(PerfStats &stats) {
    Timer t;
    std::sort(students.begin(), students.end(),
        [](const Student &a, const Student &b) {
            return a.id < b.id;
        });
    stats.sortMs = t.elapsedMs();
}

void StudentManager::sortByGrade(PerfStats &stats) {
    Timer t;
    std::sort(students.begin(), students.end(),
        [](const Student &a, const Student &b) {
            return a.grade > b.grade;
        });
    stats.sortMs = t.elapsedMs();
}

void StudentManager::sortByName(PerfStats &stats) {
    Timer t;
    std::sort(students.begin(), students.end(),
        [](const Student &a, const Student &b) {
            return a.name < b.name;
        });
    stats.sortMs = t.elapsedMs();
}

