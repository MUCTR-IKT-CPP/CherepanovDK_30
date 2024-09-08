#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

/**
 * @brief Генерирует строку заданной длины, состоящую из случайных символов английского алфавита.
 * 
 * @param length Длина генерируемой строки.
 * @return std::string Строка, состоящая из случайных символов.
 */
std::string generateRandomString(size_t length) {
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result;
    result.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        char randomChar = characters[rand() % characters.size()];
        result += randomChar;
    }

    return result;
}

/**
 * @brief Подсчитывает количество вхождений каждой буквы в строке.
 * 
 * @param str Строка, в которой производится подсчет вхождений.
 * @return std::unordered_map<char, size_t> Карта, где ключом является символ, а значением — количество его вхождений.
 */
std::unordered_map<char, size_t> countCharacterOccurrences(const std::string& str) {
    std::unordered_map<char, size_t> occurrences;

    for (char ch : str) {
        if (isalpha(ch)) {
            occurrences[ch]++;
        }
    }

    return occurrences;
}

/**
 * @brief Выводит количество вхождений каждой буквы на экран.
 * 
 * @param occurrences Карта с количеством вхождений каждой буквы.
 */
void printCharacterOccurrences(const std::unordered_map<char, size_t>& occurrences) {
    for (const auto& pair : occurrences) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

int main() {
    // Установка случайного начального значения
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Генерация строки из 10000 случайных символов
    const size_t stringLength = 10000;
    std::string randomString = generateRandomString(stringLength);

    // Подсчет вхождений каждой буквы
    std::unordered_map<char, size_t> occurrences = countCharacterOccurrences(randomString);

    // Вывод результатов
    printCharacterOccurrences(occurrences);

    return 0;
}