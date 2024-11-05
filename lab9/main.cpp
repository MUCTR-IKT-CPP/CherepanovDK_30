#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include <numeric>

class QuadraticEquation {
public:
    // Конструктор класса, принимает комплексные коэффициенты уравнения и находит корни
    QuadraticEquation(std::complex<double> a, std::complex<double> b, std::complex<double> c)
        : a_(a), b_(b), c_(c) {
        solve();
    }

    // Дружественная функция для вывода объекта QuadraticEquation в поток
    friend std::ostream& operator<<(std::ostream& os, const QuadraticEquation& eq) {
        os << "Equation: " << eq.a_ << " * x^2 + " << eq.b_ << " * x + " << eq.c_ << " = 0\n";
        os << "Roots: " << eq.root1_ << ", " << eq.root2_ << "\n";
        return os;
    }

    // Метод для проверки, есть ли среди корней введенное пользователем число
    bool hasRoot(const std::complex<double>& number) const {
        return std::any_of(roots_.begin(), roots_.end(), [&number](const auto& root) {
            return root == number;
        });
    }

    // Метод для проверки количества корней, которые меньше заданного пользователем числа
    int countRootsLessThan(const std::complex<double>& number) const {
        return std::count_if(roots_.begin(), roots_.end(), [&number](const auto& root) {
            return std::abs(root) < std::abs(number);
        });
    }

    // Получить корни уравнения
    const std::vector<std::complex<double>>& getRoots() const { return roots_; }

    // Получить сумму корней
    std::complex<double> sumOfRoots() const { return root1_ + root2_; }

private:
    std::complex<double> a_, b_, c_;
    std::complex<double> root1_, root2_;
    std::vector<std::complex<double>> roots_;

    // Решение уравнения
    void solve() {
        std::complex<double> discriminant = std::sqrt(b_ * b_ - 4.0 * a_ * c_);
        root1_ = (-b_ + discriminant) / (2.0 * a_);
        root2_ = (-b_ - discriminant) / (2.0 * a_);
        roots_ = {root1_, root2_};
    }
};

// Функция для генерации уникальных корней из всех уравнений в контейнере
std::vector<std::complex<double>> getUniqueRoots(const std::vector<QuadraticEquation>& equations) {
    std::set<std::complex<double>> uniqueRoots;
    for (const auto& eq : equations) {
        uniqueRoots.insert(eq.getRoots().begin(), eq.getRoots().end());
    }
    return std::vector<std::complex<double>>(uniqueRoots.begin(), uniqueRoots.end());
}

// Функция для сортировки уравнений по возрастанию модуля суммы корней
void sortEquationsBySumOfRoots(std::vector<QuadraticEquation>& equations) {
    std::sort(equations.begin(), equations.end(), [](const QuadraticEquation& eq1, const QuadraticEquation& eq2) {
        return std::abs(eq1.sumOfRoots()) < std::abs(eq2.sumOfRoots());
    });
}

int main() {
    // Генерация N объектов QuadraticEquation и запись их в контейнер
    std::vector<QuadraticEquation> equations = {
        {std::complex<double>(1, 0), std::complex<double>(-3, 0), std::complex<double>(2, 0)},
        {std::complex<double>(1, 0), std::complex<double>(0, 0), std::complex<double>(-4, 0)},
        {std::complex<double>(1, 1), std::complex<double>(-5, 0), std::complex<double>(6, 1)}
    };

    // Вывод всех объектов в контейнере
    for (const auto& eq : equations) {
        std::cout << eq << "\n";
    }

    // Ввод числа и проверка его наличия среди корней
    std::complex<double> userRoot(2, 0);
    for (const auto& eq : equations) {
        if (eq.hasRoot(userRoot)) {
            std::cout << "Equation has root " << userRoot << "\n";
        }
    }

    // Ввод числа и подсчет количества корней, меньших заданного числа
    std::complex<double> threshold(3, 0);
    for (const auto& eq : equations) {
        int count = eq.countRootsLessThan(threshold);
        std::cout << "Number of roots less than " << threshold << ": " << count << "\n";
    }

    // Формирование вектора уникальных корней
    std::vector<std::complex<double>> uniqueRoots = getUniqueRoots(equations);
    std::cout << "Unique roots:\n";
    for (const auto& root : uniqueRoots) {
        std::cout << root << "\n";
    }

    // Сортировка уравнений по возрастанию модуля суммы корней
    sortEquationsBySumOfRoots(equations);
    std::cout << "\nEquations sorted by the sum of roots:\n";
    for (const auto& eq : equations) {
        std::cout << eq << "\n";
    }

    return 0;
}
