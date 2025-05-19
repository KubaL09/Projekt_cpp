#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <functional>
#include <limits>
#include <iomanip>
#include "calculator.h"

int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "");

    bool verbose = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-v") {
            verbose = true;
        }
        else if (arg == "-h") {
            std::cout << "Prosty Kalkulator - Instrukcja:\n"
                << "  -v : Wyświetlaj szczegółowe informacje o operacjach\n"
                << "  -h : Wyświetl tę instrukcję\n";
            return 0;
        }
    }

    Math::Calculator calc;

    if (verbose) {
        std::cout << "Tryb szczegółowy: włączony\n";
    }

    int choice;
    Math::Operation operation;
    double firstNumber, secondNumber;
    bool needSecondNumber = true;
    bool isNewCalculation = true;

    do {
        std::cout << "\n=== PROSTY KALKULATOR ===\n";
        std::cout << "Wybierz operację:\n";
        std::cout << "1. Dodawanie\n";
        std::cout << "2. Odejmowanie\n";
        std::cout << "3. Mnożenie\n";
        std::cout << "4. Dzielenie\n";
        std::cout << "5. Potęgowanie\n";
        std::cout << "6. Pierwiastek kwadratowy\n";
        std::cout << "7. Historia operacji\n";
        std::cout << "8. Sortuj historię\n";
        std::cout << "9. Wyczyść\n";
        std::cout << "0. Wyjście\n";
        std::cout << "Wybierz: ";

        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Błędne dane wejściowe. Podaj liczbę: ";
        }

        if (choice == 0) {
            std::cout << "Dziękujemy za skorzystanie z kalkulatora!\n";
            break;
        }
        else if (choice == 7) {
            Math::displayHistory(calc.getHistory());
            continue;
        }
        else if (choice == 8) {
            Math::sortAndDisplayHistory(calc.getHistory());
            continue;
        }
        else if (choice == 9) {
            calc.clear();
            std::cout << "Kalkulator został wyczyszczony.\n";
            isNewCalculation = true;
            continue;
        }
        else if (choice < 1 || choice > 9) {
            std::cout << "Nieprawidłowy wybór. Spróbuj ponownie.\n";
            continue;
        }

        operation = static_cast<Math::Operation>(choice);

        needSecondNumber = (operation != Math::Operation::SQRT);

        if (isNewCalculation) {
            std::cout << "Podaj pierwszą liczbę: ";
            std::cin >> firstNumber;
            calc.setFirstNumber(firstNumber);
        }

        if (needSecondNumber) {
            std::cout << "Podaj drugą liczbę: ";
            std::cin >> secondNumber;
            calc.setSecondNumber(secondNumber);
        }

        calc.setOperation(operation);

        switch (operation) {
        case Math::Operation::ADD:
            calc.add(secondNumber);
            break;

        case Math::Operation::SUBTRACT:
            calc.subtract(secondNumber);
            break;

        case Math::Operation::MULTIPLY:
            calc.multiply(secondNumber);
            break;

        case Math::Operation::DIVIDE:
            if (secondNumber == 0) {
                std::cout << "Błąd: Nie można dzielić przez zero!\n";
            }
            else {
                calc.divide(secondNumber);
            }
            break;

        case Math::Operation::POWER:
            calc.power(secondNumber);
            break;

        case Math::Operation::SQRT:
            if (calc.getCurrentValue() < 0) {
                std::cout << "Błąd: Nie można obliczyć pierwiastka z liczby ujemnej!\n";
            }
            else {
                calc.squareRoot();
            }
            break;

        default:
            std::cout << "Nieprawidłowy wybór. Spróbuj ponownie.\n";
        }

        isNewCalculation = false;

        if (verbose) {
            std::cout << "Wykonano operację: "
                << Math::getOperationName(operation)
                << "\nWynik: " << calc.getCurrentValue() << "\n";
        }
        else {
            std::cout << "Wynik: " << calc.getCurrentValue() << "\n";
        }

        char continueChoice;
        std::cout << "Kontynuować obliczenia z tym wynikiem? (t/n): ";
        std::cin >> continueChoice;

        if (continueChoice == 'n' || continueChoice == 'N') {
            isNewCalculation = true;
        }

    } while (true);

    return 0;
}