#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Student.h"
#include <chrono>

// Funkcija surusiuoti studentus abeceles tvarka pagal pirma pavardes raide
bool compareStudents(const Student& a, const Student& b) {
    return a.getPavarde().front() < b.getPavarde().front();
}

int main() {
    const int numStudents = 2; // Galima pakeisti i norima kieki studentu
    std::vector<Student> students;

    std::cout << "Pasirinkite 1, 2 arba 3:\n"
        << "1. Rasyti studentu duomenis rankiniu budu\n"
        << "2. Ikelti duomenis is tekstinio failo\n"
        << "3. Generuoti tekstini faila su studentais ir ju galutiniais balais\n"
        << "Irasykite savo pasirinkima (1, 2, or 3): ";

    char inputChoice;
    std::cin >> inputChoice;

    if (inputChoice == '1') {
        // Rankinis duomenu ivedimas
        for (int i = 0; i < numStudents; ++i) {
            std::string name, surname;
            std::cout << "Iveskite studento varda ir pavarde " << (i + 1) << ":\n";
            std::cin >> name >> surname;
            std::cin.ignore();

            Student student(name, surname);
            student.inputDuom();
            student.calculateGaltuniusBalus();

            students.push_back(student);
        }
    }
    else if (inputChoice == '2') {
        // Duomenu skaitymas is tekstinio failo
        std::string fileName;
        std::cout << "Iveskite tekstinio failo pavadinima (pvz. pavyzdys.txt): ";
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
                std::cerr << "Klaida skaitant duomenis is failo. Programa isjungiama..." << std::endl;
                return 1;
            }

            student.inputDuomIsTextFailo(hw1, hw2, hw3, hw4, hw5, exam);
            student.calculateGaltuniusBalus();
            students.push_back(student);
        }

        inputFile.close();
    }
    else if (inputChoice == '3') {
        // Generuoja tekstini faila su studentais
        std::cout << "Iveskite kiek studentu norite sugeneruoti: ";
        int num;
        std::cin >> num;

        std::string originalFileName;
        std::cout << "Iveskite norima tekstinio failo pavadinima: ";
        std::cin >> originalFileName;

        students.reserve(num);

        auto start = std::chrono::high_resolution_clock::now();

        // Generuojami vardai, pavardes, sugeneruojami atsitiktiniai namu darbu bei egzamino pazymiai
        for (int i = 0; i < num; ++i) {
            std::string name = "Vardas" + std::to_string(i + 1);
            std::string surname = "Pavarde" + std::to_string(i + 1);

            Student student(name, surname);
            student.generateRandomPazymius();
            student.calculateGaltuniusBalus();

            students.push_back(student);
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Sugeneruota: " << num << " studentu su namu darbu ir egzaminiu pazymiais bei ju galutiniais balais per " << duration.count() << " sekundziu.\n";

        

        std::sort(students.begin(), students.end(), compareStudents);

        std::string outputPath = "./";

        std::ofstream allStudentsFile(outputPath + originalFileName + "_" + std::to_string(num) + ".txt");
        std::ofstream highPerformingFile(outputPath + originalFileName + "_galvociai" + std::to_string(num) + ".txt");
        std::ofstream lowPerformingFile(outputPath + originalFileName + "_nuskriaustukai" + std::to_string(num) + ".txt");

        auto totalStart = std::chrono::high_resolution_clock::now();

        // Tekstiniu failu headeris
        allStudentsFile << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde" << std::setw(20) << "Galutinis balas" << "\n";
        highPerformingFile << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde" << std::setw(20) << "Galutinis balas" << "\n";
        lowPerformingFile << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde" << std::setw(20) << "Galutinis balas" << "\n";


        for (const Student& student : students) {
            allStudentsFile << std::setw(15) << student.getVardas() << std::setw(15) << student.getPavarde()
                << std::setw(20) << std::fixed << std::setprecision(2) << student.getGalutinisBalas() << "\n";
        }

        auto writePerformingStart = std::chrono::high_resolution_clock::now();
        // Surusiuojami nuskriaustukai ir galvociai ir sukuriami text failai jiems
        for (const Student& student : students) {
            if (student.getGalutinisBalas() >= 5.0) { 
                highPerformingFile << std::setw(15) << student.getVardas() << std::setw(15) << student.getPavarde()
                    << std::setw(20) << std::fixed << std::setprecision(2) << student.getGalutinisBalas() << "\n";
            }
            else {
                lowPerformingFile << std::setw(15) << student.getVardas() << std::setw(15) << student.getPavarde()
                    << std::setw(20) << std::fixed << std::setprecision(2) << student.getGalutinisBalas() << "\n";
            }
        }

        auto writePerformingEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> writePerformingDuration = writePerformingEnd - writePerformingStart;
        std::cout << num << " Studentu duomenu surusiuoti i galvociu ir nuskriaustuku grupes ir irasyti i faila per " << writePerformingDuration.count() << " sekundziu.\n";

        auto totalEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> totalDuration = totalEnd - totalStart;
        std::cout << num << " Studentu duomenys i visus tekstinius failus irasyti per " << totalDuration.count() << " sekundziu.\n";
        
    }
    else {
        std::cerr << "Klaida. Programa isjungiama..." << std::endl;
        return 1;
    }

    if (inputChoice != '3') {
        std::sort(students.begin(), students.end(), compareStudents);

        std::cout << std::setw(0) << "Pavarde" << std::setw(15) << "Vardas" << std::setw(20) << "Galutinis balas" << std::right << std::setw(13) << "Mediana\n";
        std::cout << "-----------------------------------------------------------\n";

        for (const Student& student : students) {
            student.outputDuom();
        }
    }
    return 0;
}
