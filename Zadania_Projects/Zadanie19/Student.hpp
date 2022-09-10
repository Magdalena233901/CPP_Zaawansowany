#pragma once
#pragma once
#include <string>
#include "json/json.hpp"

namespace Zad
{
    using json = nlohmann::json;

    struct Student
    {
        Student(std::string newFirstName, std::string newLastName, int newStudentId);

        std::string firstName;
        std::string lastName;
        int studentId;
    };

    void to_json(json& j, const Student& s);

}