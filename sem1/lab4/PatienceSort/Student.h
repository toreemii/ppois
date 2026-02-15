#pragma once
#include <iostream>
#include <string>

class Student
{
private:
    std::string name;
    int age;
    double grade;

public:
    Student() : name(""), age(0), grade(0.0) {}
    Student(const std::string &name, int age, double grade) : name(name), age(age), grade(grade) {}
    Student(const std::string &name, double grade) : name(name), age(0), grade(grade) {}

    bool operator<(const Student &other) const
    {
        return name < other.name;
    }

    friend std::ostream &operator<<(std::ostream &os, const Student &student)
    {
        os << student.name << "(" << student.age << ", " << student.grade << ")";
        return os;
    }

    std::string getName() const
    {
        return name;
    }
    int getAge() const
    {
        return age;
    }
    double getGrade() const
    {
        return grade;
    }

    bool operator==(const Student &other) const
    {
        return name == other.name && age == other.age && grade == other.grade;
    }

    bool operator>(const Student &other) const
    {
        return grade > other.grade;
    }
};