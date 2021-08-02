//
// Created by ZhouP on 3/3/2019.
//

#ifndef UNTITLED_LAMBDA_H
#define UNTITLED_LAMBDA_H

#include <vector>
#include <iostream>

class Student
{
public:
    int m_id;
    int m_age;
public:
    Student (int id, int age): m_id(id), m_age(age)
    {

    }

    void printMe () const {
        std::cout << "I am " << m_age << " years old and my Id is " << m_id << std::endl;
    }

//    Student(Student& s) = default;
//    Student& operator=(Student& s) = default;

//    constexpr Student& operator=(const Student&) = default;
//    constexpr Student(const Student&) = default;

    Student& operator=(const Student& s)
    {
        this->m_age = s.m_age;
        this->m_id = s.m_id;

        return *this;
    }
    Student(const Student& s)
    {
        this->m_age = s.m_age;
        this->m_id = s.m_id;
    }

    Student(Student&& s)
    {
        this->m_age = s.m_age;
        this->m_id = s.m_id;
    }

    Student& operator=(Student&& s)
    {
        return *this;
    }


//    virtual ~Student() {}


};


std::vector<Student> prepareTestData()
{
    std::vector<Student> students;
    students.reserve(3);
    students.push_back (Student (1, 19));
    students.push_back (Student (4, 21));
//    students.push_back (Student (3, 20));
    students.emplace_back(3, 20);
    return students;
}

void printResults(const std::vector<Student>& students) {
    for (const Student &student : students) {
        student.printMe();
    }
}

void test_lambda()
{
    Student s1(1, 19);
    s1.printMe();
    Student s2 = s1;
    s2.m_age = 10;
    Student s3 = std::move(s1);
    s2 = std::move(s1);
    s3.printMe();
    s2.printMe();
    s1.printMe();

//    std::vector<Student> students = prepareTestData();
//    printResults (students);
//    std::sort(students.begin(), students.end(), [&](const Student s1, const Student s2) {return s1.m_id < s2.m_id;});
//    std::cout << "after sorting:" << std::endl;
//    printResults (students);
}

#endif //UNTITLED_LAMBDA_H
