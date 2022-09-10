#include "Student.hpp"

namespace Zad {

    Student::Student(std::string newFirstName, std::string newLastName, int newStudentId)
        : firstName(newFirstName), lastName(newLastName), studentId(newStudentId)
    {};

    void to_json(json& j, const Student& s)
    {
        j = json{ {"firstName", s.firstName} , {"lastName" , s.lastName}, {"studentId" , s.studentId} };
    }

}