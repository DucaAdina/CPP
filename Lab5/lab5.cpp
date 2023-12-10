#include <iostream>
#include <fstream>
#include <vector>
#include <optional>
#include <ostream>
#include <array>
#include <span>

// #include "nlohmann/json.hpp"

using json = nlohmann::json;

enum class Gender
{
    Male,
    Female
};
// Можете сигнализировать ошибку возвратом false функцией сериализации, или определите enum class с возможными ошибками сериализации, и возвращайте значения из этого enum-а.
enum class SerializationError
{
    NoError,
    InvalidName,
    InvalidLegs,
    InvalidGender
};

// Распишите код для структуры данных, с которой будете впоследствие работать. Структура должна иметь как минимум 3 поля:
struct Animal
{
    std::array<char, 6> nameLetters; // Строковое поле (C-string, т.е. char массив с максимальной фиксированной длиной, и нулевым символом на конце; можете использовать std::array).
    std::string name;
    int legs;      // Целочисленное поле (int)
    Gender gender; // enum class поле (например, Gender с возможными значениями Male и Female)

    Animal(const char *initialName, int initialLegs, Gender initialGender)
        : legs(initialLegs), gender(initialGender)
    {
        std::strncpy(nameLetters.data(), initialName, 5);
        nameLetters[5] = '\0';
        name = nameLetters.data();
    }
};

// Распишите по функции для каждого поля, которая принимает параметром std::ostream& и вписывает в него сериализованное значение поля:

void serializeNameLetters(std::ostream &os, const std::array<char, 5> &nameLetters)
{
    os.write(nameLetters.data(), nameLetters.size());
}

void serializeName(std::ostream &os, std::string name)
{
    os << name.c_str();
}
void serializeLegs(std::ostream &os, int legs)
{
    os << legs;
}

void serializeGender(std::ostream &os, Gender gender)
{
    if (gender == Gender::Male)
    {
        os << "Male";
    }
    else
    {
        os << "Female";
    }
}
/*  Распишите функцию, которая принимает параметром std::ostream& и ссылку на ваш объект, и сериализует весь объект.

Сериализуйте каждое поле, используя функции, расписанные ранее.

Разделите значения полей запятыми.

Этот формат называется CSV -- comma separated values*/

void serializeAnimalCSV(const Animal &animal, std::ostream &os)
{
    serializeNameLetters(animal.nameLetters, os);
    os << ",";
    serializeName(animal.name, os);
    os << ",";
    serializeLegs(animal.legs, os);
    os << ",";
    serializeGender(animal.gender, os);
}

/*Распишите по функции, которая парсит каждое поле структуры, из заданного std::istream&:

Для функции считывающую строку, пускай принимает параметром std::span буфера, копирует туда строку, и вписывает нулевой байт после. Можете сделать чтобы фукнция возвращала std::array со строкой вместо игр с указателем.

Для функции считывающую целое число, напишите свою функцию конвертирования, или импортируйте boost::try_lexical_cast, или используйте std::stoi, используя exception handling. Смотри некоторые объяснения.

Для функции считывающую enum, логика будет зависеть от того, какое представление вы выбрали для сериализации enum в предыдущем задании:

Если храните числом, используйте std::stoi, проверьте если входит в диапазон значений, и переконвертируйте в нужный тип (через static_cast или просто C каст).

Если сериализуете как строку, можете считать в локальный буфер и использовать std::strcmp чтобы сравнить с каждым возможным значением.

Если храните как символ, считайте как char, и сделайте switch чтобы выбрать нужное значение enum.*/

std::array<char, 6> parseNameLetters(std::istream &is)
{
    std::array<char, 6> result;
    is.read(result.data(), 5);
    result[5] = '\0';
    return result;
}
std::string parseName(std::istream &is)
{
    std::string result;

    while (true)
    {
        char ch;
        is.get(ch);

        if (ch == ',')
        {
            break;
        }
        else if (is.eof())
        {
            std::cerr << "Eroare la citirea numelui: lipsește virgula\n";
            return "";
        }

        result.push_back(ch);
    }

    return result;
}

int parseLegs(std::istream &is)
{
    int result = 0;
    char ch;

    while (is.get(ch))
    {
        if (ch == ',')
        {
            is.unget();
            break;
        }
        else if (!std::isdigit(ch))
        {
            std::cerr << "Eroare la citirea numărului de picioare: caracter nevalid\n";
            return 0;
        }

        result = result * 10 + (ch - '0'); // Construim numărul
    }

    return result;
}

Gender parseGender(std::istream &is)
{
    std::string genderStr;
    char delimiter;

    if (std::getline(is, genderStr, ',') && is.get(delimiter))
    {

        is.unget();
        if (genderStr == "Male")
        {
            return Gender::Male;
        }
        else if (genderStr == "Female")
        {
            return Gender::Female;
        }
    }

    std::cerr << "Eroare la citirea genului\n";
}

// Распишите функцию, которая принимает параметром std::istream&, и десериализует весь объект, возвращая его, и true, если десериализация прошла успешно.

std::optional<Animal> deserializeAnimalCSV(std::istream &is)
{
    std::array<char, 6> nameLetters;
    std::string name;
    int legs;
    Gender gender;

    nameLetters = parseNameLetters(is);

    if (is.peek() == ',')
    {
        is.ignore();
    }
    else
    {
        return std::nullopt;
    }

    name = parseName(is);

    if (is.peek() == ',')
    {
        is.ignore();
    }
    else
    {
        return std::nullopt;
    }

    legs = parseLegs(is);

    if (is.peek() == ',')
    {
        is.ignore();
    }
    else
    {
        return std::nullopt;
    }

    gender = parseGender(is);

    return Animal{nameLetters.data(), legs, gender};
}

// Распишите функцию, которая сериализует std::span из объектов вашей структуры, который приходит параметром, в std::ostream&, который тоже передавайте параметром.

// Сериализуйте каждый объект, используя функцию сериализации, расписанную ранее.

// Разделите объекты переходом на новую строку.

void serializeAnimalsSpan(std::ostream &os, std::span<Animal> animals)
{
    for (const auto &animal : animals)
    {
        serializeAnimalCSV(animal, os);
        os << '\n'; // Trecem la o nouă linie după fiecare obiect
    }
}

// Сделайте подобную функцию, которая считывает из заданного параметром std::iostream&, и десериализует каждую строку в std::vector, или в переменную типа вашего динамического массива из лабы 4, из объектов вашей структуры.

std::vector<Animal> deserializeAnimalsVector(std::istream &is)
{
    std::vector<Animal> animals;

    while (true)
    {
        auto optionalAnimal = deserializeAnimalCSV(is);

        if (optionalAnimal.has_value())
        {
            animals.push_back(optionalAnimal.value());
        }
        else
        {
            break;
        }
    }

    return animals;
}

void modifyAndSerialize(std::vector<Animal> &animals, const std::string &outputFileName)
{
    // Modificați câmpurile elementului 0 după cum doriți
    if (!animals.empty())
    {
        animals[0].name = "ModifiedName";
    }

    // Adăugați un nou element la sfârșit
    animals.push_back({"NewAnimal", 4, Gender::Male});

    // Deschideți fișierul pentru scriere și serializați datele
    std::ofstream outputFile(outputFileName);
    if (outputFile.is_open())
    {
        for (const auto &animal : animals)
        {
            serializeAnimal(outputFile, animal);
        }
        outputFile.close();
    }
    else
    {
        std::cerr << "Eroare la deschiderea fișierului pentru scriere\n";
    }
}
int main()
{
    std::vector<Animal> animals;

    std::ifstream inputFile("animal.json");
    if (inputFile.is_open())
    {
        json jsonData;
        inputFile >> jsonData;
        inputFile.close();
    }
    else
    {
        std::cerr << "Eroare la deschiderea fișierului pentru citire\n";
        return 1;
    }

    modifyAndSerialize(animals, "animal.json");

    std::cout << "Procesul de modificare și serializare a fost completat cu succes.\n";

    return 0;
}
