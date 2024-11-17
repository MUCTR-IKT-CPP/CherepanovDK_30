#include <iostream>
#include <complex>
#include <optional>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <set>
#include <cmath>

// Компаратор для комплексных чисел с округлением до 2 знаков после запятой
struct ComplexComparator {
    bool operator()(const std::complex<double>& a, const std::complex<double>& b) const {
        if (std::abs(a) < std::abs(b)) {
            return true;
        } else if (std::abs(a) > std::abs(b)) {
            return false;
        }
        return a.real() < b.real();
    }
};

// Функция для округления комплексного числа до 2 знаков после запятой
std::complex<double> roundToTwoDecimalPlaces(const std::complex<double>& number) {
    double realPart = std::round(number.real() * 100.0) / 100.0;
    double imagPart = std::round(number.imag() * 100.0) / 100.0;
    return {realPart, imagPart};
}

class QuadraticEquation {
private:
    std::complex<double> a, b, c;
    std::optional<std::complex<double>> root1, root2;

public:
    // Конструктор, принимающий коэффициенты типа complex<double> и сразу находящий корни
    QuadraticEquation(std::complex<double> a, std::complex<double> b, std::complex<double> c) 
        : a(roundToTwoDecimalPlaces(a)), b(roundToTwoDecimalPlaces(b)), c(roundToTwoDecimalPlaces(c)) {

        if (a != std::complex<double>(0.0, 0.0)) {
            std::complex<double> discriminant = b * b - std::complex<double>(4.0) * a * c;
            root1 = roundToTwoDecimalPlaces((-b + std::sqrt(discriminant)) / (std::complex<double>(2.0) * a));
            root2 = roundToTwoDecimalPlaces((-b - std::sqrt(discriminant)) / (std::complex<double>(2.0) * a));
        } else if (b != std::complex<double>(0.0, 0.0)) {
            root1 = roundToTwoDecimalPlaces(-c / b);
            root2 = std::nullopt;
        } else {
            if (c == std::complex<double>(0.0, 0.0)) {
                std::cout << "Уравнение имеет бесконечное множество решений." << std::endl;
            } else {
                std::cout << "Уравнение не имеет решений." << std::endl;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const QuadraticEquation& eq) {
        os << "Уравнение: (" << eq.a << ")x^2 + (" << eq.b << ")x + (" << eq.c << ") = 0\n";
        
        if (eq.root1 && eq.root2) {
            os << "Корни уравнения: x1 = " << *eq.root1 << ", x2 = " << *eq.root2;
        } else if (eq.root1) {
            os << "Корень уравнения: x = " << *eq.root1;
        } else {
            os << "Нет действительных корней";
        }
        os << std::endl;
        return os;
    }

    bool containsRoot(const std::complex<double>& number) const {
        return (root1 && *root1 == number) || (root2 && *root2 == number);
    }

    // Новый метод для получения суммы корней
    std::optional<std::complex<double>> sumOfRoots() const {
        if (root1 && root2) {
            return *root1 + *root2;
        } else if (root1) {
            return *root1;
        }
        return std::nullopt;
    }

    static bool hasRoot(const std::vector<QuadraticEquation>& equations, const std::complex<double>& number) {
        return std::any_of(equations.begin(), equations.end(), [&](const QuadraticEquation& eq) {
            return eq.containsRoot(number);
        });
    }

    static int countRootsLessThan(const std::vector<QuadraticEquation>& equations, const std::complex<double>& number) {
        return std::count_if(equations.begin(), equations.end(), [&](const QuadraticEquation& eq) {
            return (eq.root1 && std::abs(*eq.root1) < std::abs(number)) +
                   (eq.root2 && std::abs(*eq.root2) < std::abs(number));
        });
    }

    static std::vector<std::complex<double>> uniqueRoots(const std::vector<QuadraticEquation>& equations) {
        std::set<std::complex<double>, ComplexComparator> uniqueRootsSet;

        for (const auto& eq : equations) {
            if (eq.root1) {
                uniqueRootsSet.insert(*eq.root1);
            }
            if (eq.root2) {
                uniqueRootsSet.insert(*eq.root2);
            }
        }

        return std::vector<std::complex<double>>(uniqueRootsSet.begin(), uniqueRootsSet.end());
    }

    // Новый статический метод для сортировки по сумме корней
    static void sortBySumOfRoots(std::vector<QuadraticEquation>& equations) {
        std::sort(equations.begin(), equations.end(), [](const QuadraticEquation& eq1, const QuadraticEquation& eq2) {
            auto sum1 = eq1.sumOfRoots();
            auto sum2 = eq2.sumOfRoots();

            if (!sum1) return false;  // Если у первого уравнения нет корней, оно считается больше
            if (!sum2) return true;   // Если у второго нет корней, первое идет раньше

            return std::abs(*sum1) < std::abs(*sum2);
        });
    }
};

// Функция для генерации случайных дробных комплексных чисел
std::complex<double> generateRandomComplex() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(-10.0, 10.0);
    return roundToTwoDecimalPlaces({dis(gen), dis(gen)});
}

double getDouble(const std::string &message) {
    double number;
    std::cout << message;
    std::cin >> number;
    return number;
}

int main() {
    int N;
    std::cout << "Введите количество уравнений: ";
    std::cin >> N;
    
    std::vector<QuadraticEquation> equations;

    for (int i = 0; i < N; ++i) {
        std::complex<double> a = generateRandomComplex();
        std::complex<double> b = generateRandomComplex();
        std::complex<double> c = generateRandomComplex();
        equations.emplace_back(a, b, c);
    }

    std::cout << "\nСписок уравнений до сортировки:\n";
    std::copy(equations.begin(), equations.end(), std::ostream_iterator<QuadraticEquation>(std::cout, "\n"));

    // Сортировка уравнений по возрастанию суммы корней
    QuadraticEquation::sortBySumOfRoots(equations);

    std::cout << "\nСписок уравнений после сортировки по возрастанию суммы корней:\n";
    std::copy(equations.begin(), equations.end(), std::ostream_iterator<QuadraticEquation>(std::cout, "\n"));

    // Пример работы с остальными методами, оставленными без изменений
    std::cout << "\nВведите комплексное число для поиска корня (формат: a + bi):" << std::endl;
    double realPart = getDouble("Введите вещественную часть: "); 
    double imaginaryPart = getDouble("Введите мнимую часть: ");
    std::complex<double> userInput(realPart, imaginaryPart);

    if (QuadraticEquation::hasRoot(equations, userInput)) {
        std::cout << "Данное комплексное число является корнем хотя бы одного уравнения." << std::endl;
    } else {
        std::cout << "Данное комплексное число не является корнем ни одного уравнения." << std::endl;
    }

    std::cout << "\nВведите комплексное число для сравнения корней (формат: a + bi):" << std::endl;
    realPart = getDouble("Введите вещественную часть: ");
    imaginaryPart = getDouble("Введите мнимую часть: "); 
    std::complex<double> threshold(realPart, imaginaryPart);

    int count = QuadraticEquation::countRootsLessThan(equations, threshold);
    std::cout << "Количество корней, модуль которых меньше заданного числа: " << count << std::endl;

    std::vector<std::complex<double>> uniqueRoots = QuadraticEquation::uniqueRoots(equations);
    std::cout << "\nУникальные корни уравнений:" << std::endl;
    for (const auto& root : uniqueRoots) {
        std::cout << root << std::endl;
    }

    return 0;
}