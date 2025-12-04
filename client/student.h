#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <sstream>

struct Student {
    int id{};
    std::string name;
    int age{};
    double grade{};

    std::string toCSV() const {
        std::ostringstream oss;
        oss << id << "," << name << "," << age << "," << grade;
        return oss.str();
    }
};

#endif 
