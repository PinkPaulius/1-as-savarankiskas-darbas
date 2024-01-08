#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

class Student {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<double> ndRezultatai;
    double egzaminoRezultatas;
    double galutinisBalas;
    double galutineMediana;
    friend bool compareStudents(const Student& a, const Student& b);

public:
    // Konstruktorius
    Student(const std::string& n, const std::string& s);

    // Destruktorius
    ~Student();

    // Kopijavimo operatorius
    Student(const Student& other);

    // Priskyrimo operatorius
    Student& operator=(const Student& other);

    // Metodas duomenims priskirti
    void inputDuom();

    // Metodas priskirti atsitiktinai sugeneruotiems pazymiams nuo 1 iki 10
    void generateRandomPazymius();

    // Metodas suskaiciuoti galutini ivertinima ir mediana
    void calculateGaltuniusBalus();

    // Metodas parodyti rezultata
    void outputDuom() const;

    // Metodas gauti duomenis is tekstinio failo
    void inputDuomIsTextFailo(double hw1, double hw2, double hw3, double hw4, double hw5, double exam);
};

#endif