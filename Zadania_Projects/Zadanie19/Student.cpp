#include "Student.hpp"

namespace Zad {

    Student::Student(std::string newFirstName, std::string newLastName, int newStudentId)
        : firstName(newFirstName), lastName(newLastName), studentId(newStudentId)
    {};

    void to_json(json& j, const Student& s)
    {
        j = json{ {"firstName", s.getFirstName()} , {"lastName" , s.getLastName()}, {"studentId" , s.getStudentId()}};
    }

    void from_json( const json& j, Student& s)
    {
        s.setFirstName(j["firstName"].get<std::string>());
        s.setLastName(j["lastName"]);

        int studentId;
        j["studentId"].get_to(studentId); //get_to sluzy do porowniania zmiennej
        s.setStudentId(studentId);
    }

}