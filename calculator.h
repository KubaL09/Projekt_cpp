#pragma once
#include <vector>
#include <string>
#include <functional>
namespace Math {
    typedef double Number;
    typedef std::string OperationName;
    typedef std::vector<double> Nums;
#define MAX_HISTORY_SIZE 100
#define DEFAULT_PRECISION 4
#define CALCULATOR_VERSION "1.0"
    enum Operation {
        ADD = 1,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        POWER,
        SQRT
    };
    struct History {
        Operation op;
        Number previousValue;
        Number operand;
        Number resultValue;
    };
    OperationName getOperationName(Operation op);
    void displayHistory(const std::vector<History>& history);
    bool compareHistoryEntries(const History& a, const History& b);
    void sortAndDisplayHistory(std::vector<History> history);
    class Calculator {
    private:
        Number currentValue;
        Number pendingValue;
        Operation pendingOp;
        bool newCalculation;
        std::vector<History> history;
        void addToHistory(Operation op, Number firstValue, Number secondValue);
    public:
        Calculator();
        void setFirstNumber(Number value);
        void setSecondNumber(Number value);
        void setOperation(Operation op);
        Number calculate();
        void add(Number value);
        void subtract(Number value);
        void multiply(Number value);
        void divide(Number value);
        void power(Number exponent);
        void squareRoot();
        void clear();
        Number getCurrentValue() const;
        const std::vector<History>& getHistory() const;
    };
}