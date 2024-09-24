#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

/*
 * Пол (перечисление)
 */
enum class Gender {
    Male,   ///< Мужской пол
    Female  ///< Женский пол
};

/*
 * Дата рождения (структура)
 */
struct Date {
    int day;    ///< День
    int month;  ///< Месяц
    int year;   ///< Год
};

/*
 * Работник (структура)
 */
struct Worker {
    std::string fullName;  ///< Полное имя
    Gender gender;         ///< Пол
    Date birthDate;        ///< Дата рождения
};

/*
 * Генерация случайного ФИО с учетом пола
 *
 * @param gender пол работника (мужской или женский).
 * @return возвращает случайное ФИО.
 */
std::string generateRandomName(Gender gender) {
    const std::vector<std::string> maleNames = {"Ivan Ivanov", "Petr Petrov", "Sidor Sidorov", "Alexey Smirnov", "Nikolay Kuznetsov"};
    const std::vector<std::string> femaleNames = {"Anna Ivanova", "Olga Petrova", "Maria Sidorova", "Elena Smirnova", "Natalia Kuznetsova"};

    if (gender == Gender::Male) {
        return maleNames[rand() % maleNames.size()];
    } else {
        return femaleNames[rand() % femaleNames.size()];
    }
}

/*
 * Генерация случайного пола
 *
 * @return возвращает случайное значение пола (мужской или женский).
 */
Gender generateRandomGender() {
    return rand() % 2 == 0 ? Gender::Male : Gender::Female;
}

/*
 * Генерация случайной даты рождения.
 *
 * @return возвращает случайную дату рождения, возраст не более 70 лет.
 */
Date generateRandomBirthDate() {
    Date birthDate;
    birthDate.day = rand() % 28 + 1;
    birthDate.month = rand() % 12 + 1;
    birthDate.year = 1954 + rand() % 70;  // Возраст не более 70 лет
    return birthDate;
}

/*
 * Генерация массива работников
 *
 * @param n количество работников.
 * @return возвращает вектор работников.
 */
std::vector<Worker> generateWorkers(int n) {
    std::vector<Worker> workers;
    for (int i = 0; i < n; ++i) {
        Worker worker;
        worker.gender = generateRandomGender();
        worker.fullName = generateRandomName(worker.gender);
        worker.birthDate = generateRandomBirthDate();
        workers.push_back(worker);
    }
    return workers;
}

/*
 * Вывод информации о работнике
 *
 * @param worker структура с данными о работнике.
 */
void printWorker(const Worker& worker) {
    std::cout << "ФИО: " << worker.fullName << ", Пол: " 
              << (worker.gender == Gender::Male ? "Мужской" : "Женский")
              << ", Дата рождения: " << worker.birthDate.day << "/"
              << worker.birthDate.month << "/" << worker.birthDate.year << "\n";
}

/*
 * Поиск работника по частичному совпадению ФИО
 *
 * @param workers вектор работников.
 * @param query строка для поиска (часть ФИО).
 */
void searchByFullName(const std::vector<Worker>& workers, const std::string& query) {
    bool found = false;
    for (const auto& worker : workers) {
        if (worker.fullName.find(query) == 0) {
            printWorker(worker);
            found = true;
        }
    }
    if (!found) {
        std::cout << "Работники с таким ФИО не найдены.\n";
    }
}

/*
 * Фильтрация работников по году рождения
 *
 * @param workers вектор работников.
 * @param year год для фильтрации.
 * @param isGreater если true - фильтруются работники, родившиеся позже указанного года; если false - раньше.
 */
void filterByBirthYear(const std::vector<Worker>& workers, int year, bool isGreater) {
    bool found = false;
    for (const auto& worker : workers) {
        if ((isGreater && worker.birthDate.year < year) || (!isGreater && worker.birthDate.year > year)) {
            printWorker(worker);
            found = true;
        }
    }
    if (!found) {
        std::cout << "Нет работников, соответствующих заданным условиям.\n";
    }
}

/*
 * Подсчет распределения работников по полу
 *
 * @param workers вектор работников.
 */
void genderDistribution(const std::vector<Worker>& workers) {
    int maleCount = 0, femaleCount = 0;
    for (const auto& worker : workers) {
        if (worker.gender == Gender::Male) {
            ++maleCount;
        } else {
            ++femaleCount;
        }
    }
    std::cout << "Мужчин: " << maleCount << ", Женщин: " << femaleCount << "\n";
}

/*
 * Распределение работников по возрастным группам
 *
 * @param workers вектор работников.
 * @param groupStep шаг возрастной группы (по умолчанию 5 лет).
 */
void ageGroupDistribution(const std::vector<Worker>& workers, int groupStep = 5) {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    int currentYear = now->tm_year + 1900;

    std::vector<int> ageGroups(70 / groupStep + 1, 0);

    for (const auto& worker : workers) {
        int age = currentYear - worker.birthDate.year;
        int groupIndex = age / groupStep;
        if (groupIndex < ageGroups.size()) {
            ++ageGroups[groupIndex];
        }
    }

    for (int i = 0; i < ageGroups.size(); ++i) {
        std::cout << "Группа " << i * groupStep << "-" << (i + 1) * groupStep - 1 << " лет: " << ageGroups[i] << "\n";
    }
}

/*
 * Сортировка работников по возрасту
 *
 * @param a первый работник для сравнения.
 * @param b второй работник для сравнения.
 * @return возвращает true, если первый работник старше второго.
 */
bool compareByAge(const Worker& a, const Worker& b) {
    if (a.birthDate.year != b.birthDate.year) {
        return a.birthDate.year < b.birthDate.year;
    }
    if (a.birthDate.month != b.birthDate.month) {
        return a.birthDate.month < b.birthDate.month;
    }
    return a.birthDate.day < b.birthDate.day;
}

/*
 * Сортировка массива работников по возрасту
 *
 * @param workers вектор работников.
 */
void sortWorkersByAge(std::vector<Worker>& workers) {
    std::sort(workers.begin(), workers.end(), compareByAge);
}

/*
 * Отображение меню с доступными операциями
 */
void showMenu() {
    std::cout << "\nМеню:\n";
    std::cout << "1. Показать всех работников\n";
    std::cout << "2. Найти работника по ФИО\n";
    std::cout << "3. Отфильтровать работников по году рождения\n";
    std::cout << "4. Показать распределение по полу\n";
    std::cout << "5. Показать распределение по возрастным группам\n";
    std::cout << "6. Отсортировать работников по возрасту\n";
    std::cout << "0. Выход\n";
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    int n;
    std::cout << "Введите количество работников: ";
    std::cin >> n;

    std::vector<Worker> workers = generateWorkers(n);

    bool running = true;
    while (running) {
        showMenu();
        int choice;
        std::cout << "Введите номер операции: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "\nСписок всех работников:\n";
                for (const auto& worker : workers) {
                    printWorker(worker);
                }
                break;

            case 2: {
                std::string query;
                std::cout << "Введите начало ФИО для поиска: ";
                std::cin >> query;
                searchByFullName(workers, query);
                break;
            }

            case 3: {
                int year;
                bool isGreater;
                std::cout << "Введите год для фильтрации: ";
                std::cin >> year;
                std::cout << "Искать работников старше указанного года? (1 - Да, 0 - Нет): ";
                std::cin >> isGreater;
                filterByBirthYear(workers, year, isGreater);
                break;
            }

            case 4:
                genderDistribution(workers);
                break;

            case 5:
                ageGroupDistribution(workers);
                break;

            case 6:
                sortWorkersByAge(workers);
                std::cout << "\nСписок работников, отсортированный по возрасту:\n";
                for (const auto& worker : workers) {
                    printWorker(worker);
                }
                break;

            case 0:
                running = false;
                std::cout << "Выход из программы.\n";
                break;

            default:
                std::cout << "Неверный выбор, попробуйте снова.\n";
        }
    }

    return 0;
}
