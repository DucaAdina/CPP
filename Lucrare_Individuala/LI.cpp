#include <iostream>
#include <algorithm>
#include <random>
#include <vector>

struct CountryCapital
{
    std::string country;
    std::string capital;
};

class CountryGame {
private:
    inline static const int NUM_COUNTRIES = 10;
    std::vector<CountryCapital> countryCapitalPairs;
    int score;
    int chances;

public:
    CountryGame() : score(0), chances(3) {
     
        std::vector<std::string> countriesArray = {"Bulgaria", "Belgium", "Serbia", "Luxembourg", "Romania", "Sweden", "Denmark", "Moldova", "Slovenia", "Ukraine"};
        std::vector<std::string> capitalsArray = {"Sofia", "Brussels", "Belgrade", "Luxembourg", "Bucharest", "Stockholm", "Copenhagen", "Chisinau", "Ljubljana", "Kiev"};

        for (size_t i = 0; i < NUM_COUNTRIES; i++) {
            countryCapitalPairs.push_back({countriesArray[i], capitalsArray[i]});
        }
        shuffleVector(countryCapitalPairs);
    }

    template <typename T>
    void shuffleVector(std::vector<T>& array) {
        std::random_device rd;
        std::default_random_engine rng(rd());
        std::shuffle(array.begin(), array.end(), rng);
    }

    void displayMenu() const {
        std::cout << "==== Country Capital Quiz ====\n";
        std::cout << "1. Play Game\n";
        std::cout << "2. Instructions\n";
        std::cout << "3. Exit\n";
        std::cout << "=============================\n";
    }

    void displayInstructions() const {
        std::cout << "==== Instructions ====\n";
        std::cout << "You will be given the name of a country, and you have to guess its capital.\n";
        std::cout << "Make sure to capitalize the first letter of the capital.\n";
        std::cout << "You have 3 chances for each question. If you run out of chances, your score will be penalized.\n";
        std::cout << "Try to score 7 or more to win!\n";
        std::cout << "=======================\n";
    }

    void playGame() {
        do {
            displayMenu();
            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                    playRound();
                    break;
                case 2:
                    displayInstructions();
                    break;
                case 3:
                    std::cout << "Exit!\n";
                    return;
                default:
                    std::cout << "Invalid choice. Please enter a valid option.\n";
                    break;
            }
        } while (true);
    }

    void playRound() {
        chances = 3; 
        std::cout << "Your score: " << score << "\n";
        std::cout << "=======================\n";
        std::cout << "Number of chances: " << chances << "\n";
        std::cout << "=======================\n";
        
        displayAvailableCapitals();

        int i = 0;
        while (i < NUM_COUNTRIES && chances > 0) {
            std::string userGuess;
            std::cout << "Enter the capital of " << countryCapitalPairs[i].country << ": ";
            std::cin >> userGuess;

            if (!isupper(userGuess[0])) {
                std::cout << "Incorrect! Please start the capital with an uppercase letter.\n";
                chances--;  
                std::cout << "Number of chances: " << chances << "\n";
            } else {
                if (userGuess == countryCapitalPairs[i].capital) {
                    std::cout << "Correct!\n";
                    score++;
                    std::cout << "Your score: " << score << "\n";
                    ++i;
                } else {
                    std::cout << "Incorrect! " << userGuess << " is not the capital of " << countryCapitalPairs[i].country << ".\n";
                    std::cout << "Try again for " << countryCapitalPairs[i].country << "!\n";
                    chances--;
                    std::cout << "Number of chances: " << chances << "\n";
                }

                if (chances == 0)
                    score--;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Your score: " << score << "\n";
    }

    void displayAvailableCapitals() const {
        std::cout << "Available capitals:\n";
        for (const auto& pair : countryCapitalPairs) {
            std::cout << pair.capital << "\n";
        }
        std::cout << "\n";
    }

    bool isGameOver() {
        if (score >= 7) {
            std::cout << "You won!\n";
            return true;
        } else {
            std::cout << "You lost. Try again? (yes/no): ";
            std::string answer;
            std::cin >> answer;
            return (answer == "no");
        }
    }
};

int main() {
    CountryGame game;
    game.playGame();

    return 0;
}
