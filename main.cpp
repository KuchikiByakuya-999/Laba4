#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

struct Candidate 
{
    string name;
    int bordaScore;
    map<string, int> condorcetWins;
};

// Функция для определения победителя по методу Борда
string findBordaWinner(const vector<Candidate>& candidates) 
{
    int maxScore = -1;
    string winner;
    
    for (const auto& candidate : candidates) 
    {
        if (candidate.bordaScore > maxScore) 
        {
            maxScore = candidate.bordaScore;
            winner = candidate.name;
        }
    }
    
    return winner;
}

// Функция для определения победителя по методу Кондорсе
string findCondorcetWinner(const vector<Candidate>& candidates, int numVoters) 
{
    for (const auto& candidate : candidates) 
    {
        bool isCondorcetWinner = true;
        
        for (const auto& other : candidates) 
        {
            if (candidate.name != other.name) 
            {
                if (candidate.condorcetWins.at(other.name) <= numVoters / 2) 
                {
                    isCondorcetWinner = false;
                    break;
                }
            }
        }
        
        if (isCondorcetWinner) 
        {
            return candidate.name;
        }
    }
    
    return "No Condorcet winner";
}

int main() {
    int numCandidates, numVoters;
    
    cout << "Введите количество кандидатов: ";
    cin >> numCandidates;
    cout << "Введите количество избирателей: ";
    cin >> numVoters;
    cin.ignore(); // Очистка буфера
    
    vector<Candidate> candidates(numCandidates);
    map<string, int> nameToIndex;
    
    // Ввод имен кандидатов
    cout << "Введите имена кандидатов (по одному в строке):" << endl;
    for (int i = 0; i < numCandidates; ++i) 
    {
        getline(cin, candidates[i].name);
        nameToIndex[candidates[i].name] = i;
        candidates[i].bordaScore = 0;
        
        // Инициализация карты побед для Кондорсе
        for (int j = 0; j < numCandidates; ++j) 
        {
            if (i != j) 
            {
                candidates[i].condorcetWins[candidates[j].name] = 0;
            }
        }
    }
    
    // Ввод голосов избирателей
    cout << "Введите голоса (по одному в строке, кандидаты в порядке предпочтения):" << endl;
    for (int i = 0; i < numVoters; ++i) 
    {
        string vote;
        getline(cin, vote);
        
        // Разбиваем голос на отдельные кандидаты
        vector<string> preferences;
        size_t pos = 0;
        string delimiter = " ";
        while ((pos = vote.find(delimiter)) != string::npos) 
        {
            preferences.push_back(vote.substr(0, pos));
            vote.erase(0, pos + delimiter.length());
        }
        preferences.push_back(vote);
        
        // Проверка корректности ввода
        if (preferences.size() != numCandidates) 
        {
            cout << "Недействительный голос! Пожалуйста, введите точно " << numCandidates 
                 << " кандидаты, разделенные пробелами." << endl;
            --i; // Повторяем ввод для этого избирателя
            continue;
        }
        
        // Начисление баллов по методу Борда
        for (int j = 0; j < numCandidates; ++j) 
        {
            string candidateName = preferences[j];
            candidates[nameToIndex[candidateName]].bordaScore += (numCandidates - j - 1);
        }
        
        // Обновление парных сравнений для метода Кондорсе
        for (int j = 0; j < numCandidates; ++j) 
        {
            for (int k = j + 1; k < numCandidates; ++k) 
            {
                string higher = preferences[j];
                string lower = preferences[k];
                candidates[nameToIndex[higher]].condorcetWins[lower]++;
            }
        }
    }
    
    // Определение победителей
    string bordaWinner = findBordaWinner(candidates);
    string condorcetWinner = findCondorcetWinner(candidates, numVoters);
    
    // Вывод результатов
    cout << "\nРезультаты:" << endl;
    cout << "Баллы по методу Борда:" << endl;
    for (const auto& candidate : candidates) 
    {
        cout << candidate.name << ": " << candidate.bordaScore << endl;
    }
    
    cout << "\nПарные сравнения по Кондорсе:" << endl;
    for (const auto& candidate : candidates) 
    {
        cout << candidate.name << " wins against:" << endl;
        for (const auto& opponent : candidates) 
        {
            if (candidate.name != opponent.name) 
            {
                cout << "  " << opponent.name << ": " << candidate.condorcetWins.at(opponent.name) 
                     << " (" << (candidate.condorcetWins.at(opponent.name) > numVoters / 2 ? "побеждает" : "проигрывает") 
                     << ")" << endl;
            }
        }
    }
    
    cout << "\nПобедитель по методу Борда: " << bordaWinner << endl;
    cout << "Победитель по методу Кондорсе: " << condorcetWinner << endl;
    
    if (bordaWinner != condorcetWinner && condorcetWinner != "No Condorcet winner") 
    {
        cout << "\nПримечание: Разные методы голосования дали разных победителей. Это известно "
             << "как парадокс голосования и демонстрирует, что разные системы голосования могут "
             << "давать разные результаты при одинаковых предпочтениях избирателей." << endl;
    }
    
    return 0;
}