#include "calculator.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

Math::OperationName Math::getOperationName(Math::Operation op) {
    switch (op) {
    case Operation::ADD:
        return "Dodawanie";
    case Operation::SUBTRACT:
        return "Odejmowanie";
    case Operation::MULTIPLY:
        return "Mno¿enie";
    case Operation::DIVIDE:
        return "Dzielenie";
    case Operation::POWER:
        return "Potêgowanie";
    case Operation::SQRT:
        return "Pierwiastek kwadratowy";
    default:
        return "Nieznana operacja";
    }
}

void Math::displayHistory(const std::vector<Math::History>& history) {
    if (history.empty()) {
        std::cout << "Historia jest pusta.\n";
        return;
    }

    std::cout << "\n=== HISTORIA OPERACJI ===\n";
    std::cout << std::setw(5) << "Nr" << " | "
        << std::setw(20) << "Operacja" << " | "
        << std::setw(10) << "Liczba 1" << " | "
        << std::setw(10) << "Liczba 2" << " | "
        << std::setw(10) << "Wynik" << "\n";
    std::cout << std::string(65, '-') << "\n";

    for (size_t i = 0; i < history.size(); ++i) {
        const auto& entry = history[i];

        std::cout << std::setw(5) << (i + 1) << " | "
            << std::setw(20) << getOperationName(entry.op) << " | ";

        if (entry.op != Operation::SQRT) {
            std::cout << std::setw(10) << entry.previousValue << " | "
                << std::setw(10) << entry.operand << " | ";
        }
        else {
            std::cout << std::setw(10) << entry.previousValue << " | "
                << std::setw(10) << "---" << " | ";
        }

        std::cout << std::setw(10) << entry.resultValue << "\n";
    }
}

bool Math::compareHistoryEntries(const Math::History& a, const Math::History& b) {
    return a.resultValue < b.resultValue;
}

void Math::sortAndDisplayHistory(std::vector<Math::History> history) {
    if (history.empty()) {
        std::cout << "Historia jest pusta.\n";
        return;
    }

    for (size_t i = 0; i < history.size() - 1; ++i) {
        for (size_t j = 0; j < history.size() - i - 1; ++j) {
            if (history[j].resultValue > history[j + 1].resultValue) {
                History temp = history[j];
                history[j] = history[j + 1];
                history[j + 1] = temp;
            }
        }
    }

    std::cout << "\n=== HISTORIA OPERACJI (POSORTOWANA) ===\n";
    std::cout << std::setw(5) << "Nr" << " | "
        << std::setw(20) << "Operacja" << " | "
        << std::setw(10) << "Liczba 1" << " | "
        << std::setw(10) << "Liczba 2" << " | "
        << std::setw(10) << "Wynik" << "\n";
    std::cout << std::string(65, '-') << "\n";

    int counter = 1;
    for (const auto& entry : history) {
        std::cout << std::setw(5) << counter++ << " | "
            << std::setw(20) << getOperationName(entry.op) << " | ";

        if (entry.op != Operation::SQRT) {
            std::cout << std::setw(10) << entry.previousValue << " | "
                << std::setw(10) << entry.operand << " | ";
        }
        else {
            std::cout << std::setw(10) << entry.previousValue << " | "
                << std::setw(10) << "---" << " | ";
        }

        std::cout << std::setw(10) << entry.resultValue << "\n";
    }
}

Math::Calculator::Calculator()
    : currentValue(0), pendingValue(0), pendingOp(Operation::ADD), newCalculation(true) {
    history.reserve(MAX_HISTORY_SIZE);
}

void Math::Calculator::addToHistory(Math::Operation op, Math::Number firstValue, Math::Number secondValue) {
    History entry;
    entry.op = op;
    entry.previousValue = firstValue;
    entry.operand = secondValue;
    entry.resultValue = currentValue;

    if (history.size() >= MAX_HISTORY_SIZE) {
        history.erase(history.begin());
    }

    history.push_back(entry);
}

void Math::Calculator::setFirstNumber(Math::Number value) {
    currentValue = value;
    newCalculation = true;
}

void Math::Calculator::setSecondNumber(Math::Number value) {
    pendingValue = value;
}

void Math::Calculator::setOperation(Math::Operation op) {
    pendingOp = op;
}

Math::Number Math::Calculator::calculate() {
    Number firstValue = currentValue;
    Number secondValue = pendingValue;

    switch (pendingOp) {
    case Operation::ADD:
        currentValue = firstValue + secondValue;
        break;
    case Operation::SUBTRACT:
        currentValue = firstValue - secondValue;
        break;
    case Operation::MULTIPLY:
        currentValue = firstValue * secondValue;
        break;
    case Operation::DIVIDE:
        if (secondValue == 0) {
            std::cout << "B³¹d: Nie mo¿na dzieliæ przez zero!\n";
            return currentValue;
        }
        currentValue = firstValue / secondValue;
        break;
    case Operation::POWER:
        currentValue = std::pow(firstValue, secondValue);
        break;
    case Operation::SQRT:
        if (firstValue < 0) {
            std::cout << "B³¹d: Nie mo¿na obliczyæ pierwiastka z liczby ujemnej!\n";
            return currentValue;
        }
        currentValue = std::sqrt(firstValue);
        break;
    }

    addToHistory(pendingOp, firstValue, secondValue);
    newCalculation = false;
    return currentValue;
}

void Math::Calculator::add(Math::Number value) {
    pendingOp = Operation::ADD;
    pendingValue = value;
    calculate();
}

void Math::Calculator::subtract(Math::Number value) {
    pendingOp = Operation::SUBTRACT;
    pendingValue = value;
    calculate();
}

void Math::Calculator::multiply(Math::Number value) {
    pendingOp = Operation::MULTIPLY;
    pendingValue = value;
    calculate();
}

void Math::Calculator::divide(Math::Number value) {
    if (value == 0) {
        std::cout << "B³¹d: Nie mo¿na dzieliæ przez zero!\n";
        return;
    }
    pendingOp = Operation::DIVIDE;
    pendingValue = value;
    calculate();
}

void Math::Calculator::power(Math::Number exponent) {
    pendingOp = Operation::POWER;
    pendingValue = exponent;
    calculate();
}

void Math::Calculator::squareRoot() {
    if (currentValue < 0) {
        std::cout << "B³¹d: Nie mo¿na obliczyæ pierwiastka z liczby ujemnej!\n";
        return;
    }
    pendingOp = Operation::SQRT;
    calculate();
}

void Math::Calculator::clear() {
    currentValue = 0;
    pendingValue = 0;
    pendingOp = Operation::ADD;
    newCalculation = true;
}

Math::Number Math::Calculator::getCurrentValue() const {
    return currentValue;
}

const std::vector<Math::History>& Math::Calculator::getHistory() const {
    return history;
}