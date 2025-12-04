#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include "student.h"
#include "Performance.h"
#include <vector>
#include <string>

class StudentManager {
public:
    bool loadFromCSV(const std::string &filePath, PerfStats &stats);
    bool saveToCSV(const std::string &filePath, PerfStats &stats) const;

    void listAll() const;
    const Student* searchById(int id) const;
    std::vector<Student> searchByName(const std::string &name) const;

    void sortById(PerfStats &stats);
    void sortByGrade(PerfStats &stats);
    void sortByName(PerfStats &stats);

    const std::vector<Student>& getAll() const { return students; }
    size_t size() const { return students.size(); }

private:
    std::vector<Student> students;
};

#endif
