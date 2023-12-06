#include <iostream>
#include <fstream>
#include <vector>
#include <optional>

class Animal {
    
public:
    Animal() = default;

    Animal(const std::string& initialName, int initialLegs, Gender initialGender) 
        : name(initialName), legs(initialLegs), gender(initialGender) {
        if (initialName.size() < 6) {
            nameLetters = initialName;
        } else {
            nameLetters = initialName.substr(0, 5);
        }
    }


    friend std::ostream& operator<<(std::ostream& os, const Animal& animal) {
        os << animal.nameLetters << ',' << animal.name << ',' << animal.legs << ',';
        if (animal.gender == Gender::Male) {
            os << "Male";
        } else {
            os << "Female";
        }
        return os;
    }


    friend std::istream& operator>>(std::istream& is, Animal& animal) {
        // Citim direct în membrii clasei
        std::getline(is, animal.nameLetters, ',');
        std::getline(is, animal.name, ',');
        is >> animal.legs;

        std::string genderStr;
        is >> genderStr;

        if (genderStr == "Male") {
            animal.gender = Gender::Male;
        } else if (genderStr == "Female") {
            animal.gender = Gender::Female;
        } else {
            std::cerr << "Eroare de gen\n";
            throw std::invalid_argument("Eroare de gen");
        }

        return is;
    }

private:
    std::string nameLetters; 
    std::string name;
    int legs;
    Gender gender;
};


void modifyAndSerialize(std::vector<Animal>& animals, const std::string& outputFileName) {
  
    if (!animals.empty()) {
        animals[0] = {"ModifiedName", 4, Gender::Male};
    }

    
    animals.push_back({"NewAnimal", 4, Gender::Male});

  
    std::ofstream outputFile(outputFileName);
    if (outputFile.is_open()) {
        for (const auto& animal : animals) {
            outputFile << animal << '\n';
        }
        outputFile.close();
    } else {
        std::cerr << "Eroare la deschiderea fișierului pentru scriere\n";
    }
}


std::vector<Animal> readAndDeserialize(const std::string& inputFileName) {
    std::vector<Animal> animals;


    std::ifstream inputFile(inputFileName);
    if (inputFile.is_open()) {
        Animal animal;
        while (inputFile >> animal) {
            animals.push_back(animal);
        }
        inputFile.close();
    } else {
        std::cerr << "Eroare la deschiderea fișierului pentru citire\n";
    }

    return animals;
}

int main() {
    
    std::vector<Animal> animals = readAndDeserialize("animal.json");

  
    modifyAndSerialize(animals, "animal.json");

    std::cout << "Procesul de modificare și serializare a fost completat cu succes.\n";

    return 0;
}
