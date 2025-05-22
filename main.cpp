#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <iomanip>

using namespace std;

int randomInt(int min, int max) 
{
    random_device rd;
    knuth_b gen(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

ostream& operator<< (ostream& os, const vector<int>& v) 
{
    for (int num : v)
    {
        os << num << ' ';
    }
    return os;
}

bool isPrime(int n) 
{
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) 
    {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() 
{
    int n;
    cout << "Введите кол-во элементов: ";
    cin >> n;
    vector<int> arr1(n);
    for (int i = 0; i < n; ++i) 
    {
        arr1[i] = randomInt(10, 30);
    }
    
    vector<int> arr2(5);
    for (int i = 0; i < 5; ++i) 
    {
        arr2[i] = randomInt(10, 30);
    }
    
    cout << "1. Инициализированные массивы:" << endl;
    cout << "arr1 (" << n << " элементов): ";
    cout << arr1 << "\n";
    cout << "arr2 (5 элементов): ";
    cout << arr2 << "\n";
    cout << endl;
    
    // 2. Четные элементы arr1 на нечетных местах
    cout << "2. Четные элементы arr1 на нечетных местах:" << endl;
    int count_even = 0;
    vector<int> even_elements;
    for (int i = 1; i < n; i += 2) 
    {
        if (arr1[i] % 2 == 0) 
        {
            count_even++;
            even_elements.push_back(arr1[i]);
        }
    }
    cout << "Элементы: ";
    cout << even_elements << "\n";
    cout << "Количество: " << count_even << endl;
    
    // 3. Какие числа из arr2 встречаются в arr1
    cout << "3. Числа из arr2, встречающиеся в arr1:" << endl;
    unordered_map<int, int> frequency;
    for (int num : arr1) 
    {
        frequency[num]++;
    }
    
    bool found = false;
    for (int num : arr2) 
    {
        if (frequency.count(num)) 
        {
            found = true;
            cout << "Число " << num << " встречается " << frequency[num] << " раз(а)" << endl;
        }
    }
    
    if (!found) 
    {
        cout << "Ни одно число из arr2 не встречается в arr1" << endl;
    }
    cout << endl;
    
    // 4. Модификация массива случайных символов
    cout << "4. Модификация массива символов:" << endl;
    int m;
    cout << "Введите кол-во элементов: ";
    cin >> m;
    vector<char> char_arr(m);
    for (int i = 0; i < m; ++i) 
    {
    // Генерация случайного печатного символа
    char_arr[i] = randomInt(32, 126);
    }
    cout << "Исходный массив (" << m << " элементов): ";
    for (char c : char_arr) cout << c << " ";
    cout << endl;

    if (m > 0) 
    {
        char last = char_arr.back();
        for (int i = m - 1; i > 0; --i) 
        {
            char_arr[i] = char_arr[i - 1];
        }
        char_arr[0] = last;
    }
    
    cout << "После циклического сдвига вправо: ";
    for (char c : char_arr) cout << c << " ";
    cout << endl << endl;
    
    // 5. Работа с числами 1000-9000
    cout << "5. Работа с числами 1000-9000:" << endl;
    int p;
    cout << "Введите кол-во элементов: ";
    cin >> p;
    vector<int> numbers(p);
    int original_sum = 0;
    
    for (int i = 0; i < p; ++i) 
    {
        numbers[i] = randomInt(1000, 9000);
        original_sum += numbers[i];
    }
    
    cout << "Исходный массив (" << p << " элементов): ";
    cout << numbers << "\n";
    cout << "Сумма элементов: " << original_sum << endl;
    
    // Меняем цифры в порядке возрастания
    for (int& num : numbers) 
    {
        string s = to_string(num);
        sort(s.begin(), s.end());
        // Удаляем ведущие нули, если они появились
        while (s.size() > 1 && s[0] == '0') 
        {
            s.erase(0, 1);
        }
        num = s.empty() ? 0 : stoi(s);
    }
    
    cout << "После сортировки цифр в каждом числе: ";
    cout << numbers << "\n";
    
    // Сортировка массива по возрастанию
    sort(numbers.begin(), numbers.end());
    cout << "После сортировки всего массива: ";
    cout << numbers << "\n";
    
    int new_sum = 0;
    for (int num : numbers) 
    {
        new_sum += num;
    }
    cout << "Сумма после преобразований: " << new_sum << endl;
    cout << "Разница с исходной суммой: " << abs(original_sum - new_sum) << endl;
    
    return 0;
}