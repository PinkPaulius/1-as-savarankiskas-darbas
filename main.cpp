#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream> 
#include <algorithm> 
#include "Student.h"

// Funkcija studentu rusiavimui pagal pavardes pirma raide
bool compareStudents(const Student& a, const Student& b) {
    return a.pavarde.front() < b.pavarde.front();
}

int main() {
    const int numStudents = 2; // Galima pakeisti i norima kieki studentu
    std::vector<Student> students;

    std::cout << "Ar norite ivesti duomenis rankiniu budu ar is tekstinio failo? (paspauskite r rankiniui, t tekstiniam failui): ";
    char inputChoice;
    std::cin >> inputChoice;

    if (inputChoice == 'r' || inputChoice == 'R') {
        // Rankinis ivedimas
        for (int i = 0; i < numStudents; ++i) {
            std::string name, surname;
            std::cout << "Iveskite studento varda ir pavarde. Studentas Nr: " << (i + 1) << ":\n";
            std::cin >> name >> surname;
            std::cin.ignore();

            Student student(name, surname);
            student.inputDuom();
            student.calculateGaltuniusBalus();

            students.push_back(student);
        }
    }
    else if (inputChoice == 't' || inputChoice == 'T') {
        // Skaitymas is tekstinio failo
        std::string fileName;
        std::cout << "Iveskite tekstinio failo pavadinima (pvz., pavyzdys.txt): ";
        std::cin >> fileName;

        std::ifstream inputFile(fileName);
        if (!inputFile) {
            std::cerr << "Klaida atidarant faila. Programa isjungiama..." << std::endl;
            return 1;
        }

        std::string header;
        std::getline(inputFile, header);
        std::string surname, name;
        double hw1, hw2, hw3, hw4, hw5, exam;
        while (inputFile >> surname >> name >> hw1 >> hw2 >> hw3 >> hw4 >> hw5 >> exam) {
            Student student(name, surname);

            if (inputFile.fail()) {
                std::cerr << "Klaida nuskaitant duomenis is failo. Programa isjungiama..." << std::endl;
                return 1; 
            }

            student.inputDuomIsTextFailo(hw1, hw2, hw3, hw4, hw5, exam);
            student.calculateGaltuniusBalus();
            students.push_back(student);
        }

        inputFile.close();
    }
    else {
        std::cerr << "Netinkamas pasirinkimas. Programa isjungiama..." << std::endl;
        return 1; 
    }

    std::sort(students.begin(), students.end(), compareStudents);

    std::cout << std::setw(0) << "Pavarde" << std::setw(15) << "Vardas" << std::setw(20) << "Galutinis balas" << std::right << std::setw(13) << "Mediana\n";
    std::cout << "-----------------------------------------------------------\n";

    for (const Student& student : students) {
        student.outputDuom();
    }

    return 0;
}
