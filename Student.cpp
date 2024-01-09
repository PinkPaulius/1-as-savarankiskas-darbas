#include "Student.h"

// Konstruktorius
Student::Student(const std::string& n, const std::string& s) : vardas(n), pavarde(s), galutinisBalas(0.0), galutineMediana(0.0) {}

// Destruktorius
Student::~Student() {}

// Kopijavimo konstruktorius
Student::Student(const Student& other) : vardas(other.vardas), pavarde(other.pavarde),
ndRezultatai(other.ndRezultatai),
egzaminoRezultatas(other.egzaminoRezultatas),
galutinisBalas(other.galutinisBalas),
galutineMediana(other.galutineMediana) {}

// Priskyrimo operatorius
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        vardas = other.vardas;
        pavarde = other.pavarde;
        ndRezultatai = other.ndRezultatai;
        egzaminoRezultatas = other.egzaminoRezultatas;
        galutinisBalas = other.galutinisBalas;
        galutineMediana = other.galutineMediana;
    }
    return *this;
}

// Metodas duomenims priskirti
void Student::inputDuom() {
    std::cout << "Ar norite sugeneruoti atsitiktinius balus? (t/n): ";
    char choice;
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cerr << "Neteisinga ivestis. Iveskite 't' arba 'n'." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (choice == 't' || choice == 'T') {
        generateRandomPazymius();
    }
    else {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Iveskite sio studento namu darbo ivertinima: " << vardas << " " << pavarde << " (Jei baigete vesti namu darbu ivertinimus, spauskite Enter):\n";

        double result;
        while (true) {
            std::cout << "Namu darbas " << (ndRezultatai.size() + 1) << ": ";
            std::string input;
            std::getline(std::cin, input);

            if (input.empty() || std::all_of(input.begin(), input.end(), ::isspace)) {
                break;
            }

            try {
                size_t pos;
                result = std::stod(input, &pos);

                if (pos != input.size()) {
                    throw std::invalid_argument("Neteisinga ivestis. Iveskite tinkama numeri.");
                }

                if (result < 1.0 || result > 10.0) {
                    std::cerr << "Neteisinga ivestis. Namu darbu balas turi buti nuo 1 iki 10." << std::endl;
                    continue;
                }
            }
            catch (const std::invalid_argument& e) {
                std::cerr << e.what() << std::endl;
                continue;
            }

            ndRezultatai.push_back(result);
        }

        std::cout << "Iveskite sio studento egzamino ivertinima: " << vardas << " " << pavarde << ": ";
        std::cin >> egzaminoRezultatas;

        if (std::cin.fail()) {
            std::cerr << "Neteisinga ivestis. Iveskite tinkam? numeri." << std::endl;
            std::exit(EXIT_FAILURE);
        }

        if (egzaminoRezultatas < 1.0 || egzaminoRezultatas > 10.0) {
            std::cerr << "Neteisinga ivestis. Egzamino balas turi buti nuo 1 iki 10." << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

// Metodas sugeneruoti atsitiktinius pazymius nuo 1 iki 10
void Student::generateRandomPazymius() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> homeworkDist(1.0, 10.0);
    std::uniform_real_distribution<double> examDist(1.0, 10.0);

    std::cout << "Generuojami atsitiktiniai ivertinimai siam mokiniui: " << vardas << " " << pavarde << "...\n";

    // Generuojami atsitiktiniai rezultatai
    const int numHomeworks = 5; // Siuo atveju generuojami 5 atsitiktiniai ivertinimai
    for (int i = 0; i < numHomeworks; ++i) {
        ndRezultatai.push_back(homeworkDist(gen));
    }

    // Atsitiktinis egzamino ivertinimas
    egzaminoRezultatas = examDist(gen);
}
// Metodas apskaiciuoti galutiniam balui ir medianai
void Student::calculateGaltuniusBalus() {
    double homeworkAverage = 0.0;
    for (double result : ndRezultatai) {
        homeworkAverage += result;
    }
    homeworkAverage /= ndRezultatai.size();
    galutinisBalas = 0.4 * homeworkAverage + 0.6 * egzaminoRezultatas;

    std::vector<double> sortedHomework = ndRezultatai;
    std::sort(sortedHomework.begin(), sortedHomework.end());

    if (sortedHomework.size() % 2 == 0) {
        galutineMediana = 0.4 * (sortedHomework[sortedHomework.size() / 2 - 1] + sortedHomework[sortedHomework.size() / 2])
            + 0.6 * egzaminoRezultatas;
    }
    else {
        galutineMediana = 0.4 * sortedHomework[sortedHomework.size() / 2] + 0.6 * egzaminoRezultatas;
    }
}

// Metodas duomenu spausdinimui
void Student::outputDuom() const {
    std::cout << std::left << std::setw(15) << std::setw(15) << pavarde << std::setw(15) << vardas
        << std::fixed << std::setprecision(2) << std::setw(15) << galutinisBalas << std::right << std::setw(7) << galutineMediana << std::endl;
}

void Student::inputDuomIsTextFailo(double hw1, double hw2, double hw3, double hw4, double hw5, double exam) {
    ndRezultatai = { hw1, hw2, hw3, hw4, hw5 };
    egzaminoRezultatas = exam;
}
// Getteriai
std::string Student::getPavarde() const {
    return pavarde;
}

std::string Student::getVardas() const {
    return vardas;
}

double Student::getGalutinisBalas() const {
    return galutinisBalas;
}