#pragma once
#include <string>
#include "json/json.hpp"

namespace Zad
{
    using json = nlohmann::json;

    class Student
    {
    public:
        Student(std::string newFirstName, std::string newLastName, int newStudentId);

        Student()
        {};

        std::string getFirstName() const
        {
            return firstName;
        }

        std::string getLastName() const
        {
            return lastName;
        }

        int getStudentId() const
        {
            return studentId;
        }

        void setFirstName(std::string newFirstName)
        {
            firstName = newFirstName;
        }

        void setLastName(std::string newLastName)
        {
            lastName = newLastName;
        }

        void setStudentId(int newStudentId)
        {
            studentId = newStudentId;
        }

    private:
        std::string firstName;
        std::string lastName;
        int studentId;
    };

    void to_json(json& j, const Student& s);
    void from_json(const json& j, Student& s);

}