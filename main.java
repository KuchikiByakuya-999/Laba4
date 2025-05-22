package fourth.fourth_java;

import java.util.*;

class Candidate {
    String name;
    int bordaScore;
    Map<String, Integer> condorcetWins;

    public Candidate(String name) {
        this.name = name;
        this.bordaScore = 0;
        this.condorcetWins = new HashMap<>();
    }
}

public class main {
    public static String findBordaWinner(List<Candidate> candidates) {
        int maxScore = -1;
        String winner = "";
        
        for (Candidate candidate : candidates) {
            if (candidate.bordaScore > maxScore) {
                maxScore = candidate.bordaScore;
                winner = candidate.name;
            }
        }
        
        return winner;
    }

    public static String findCondorcetWinner(List<Candidate> candidates, int numVoters) {
        for (Candidate candidate : candidates) {
            boolean isCondorcetWinner = true;
            
            for (Candidate other : candidates) {
                if (!candidate.name.equals(other.name)) {
                    if (candidate.condorcetWins.getOrDefault(other.name, 0) <= numVoters / 2) {
                        isCondorcetWinner = false;
                        break;
                    }
                }
            }
            
            if (isCondorcetWinner) {
                return candidate.name;
            }
        }
        
        return "No Condorcet winner";
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int numCandidates, numVoters;
        
        System.out.print("Введите количество кандидатов: ");
        numCandidates = scanner.nextInt();
        System.out.print("Введите количество избирателей: ");
        numVoters = scanner.nextInt();
        scanner.nextLine(); // Очистка буфера
        
        List<Candidate> candidates = new ArrayList<>();
        Map<String, Integer> nameToIndex = new HashMap<>();
        
        System.out.println("Введите имена кандидатов (по одному в строке):");
        for (int i = 0; i < numCandidates; ++i) {
            String name = scanner.nextLine().trim();
            if (name.isEmpty()) {
                System.out.println("Имя кандидата не может быть пустым. Пожалуйста, введите снова.");
                i--;
                continue;
            }
            Candidate candidate = new Candidate(name);
            candidates.add(candidate);
            nameToIndex.put(name, i);
        }
        
        // Инициализация карты побед для Кондорсе
        for (Candidate candidate : candidates) {
            for (Candidate other : candidates) {
                if (!candidate.name.equals(other.name)) {
                    candidate.condorcetWins.put(other.name, 0);
                }
            }
        }
        
        System.out.println("Введите голоса (по одному в строке, кандидаты в порядке предпочтения, разделенные пробелами):");
        for (int i = 0; i < numVoters; ++i) {
            String vote = scanner.nextLine().trim();
            if (vote.isEmpty()) {
                System.out.println("Голос не может быть пустым. Пожалуйста, введите снова.");
                i--;
                continue;
            }
            
            String[] preferences = vote.split("\\s+"); // Разделение по одному или нескольким пробелам
            
            if (preferences.length != numCandidates) {
                System.out.println("Недействительный голос! Ожидается " + numCandidates + 
                                 " кандидатов, а получено " + preferences.length + 
                                 ". Пожалуйста, введите снова.");
                i--;
                continue;
            }
            
            // Проверка, что все кандидаты в голосе существуют
            boolean validVote = true;
            for (String name : preferences) {
                if (!nameToIndex.containsKey(name)) {
                    System.out.println("Кандидат '" + name + "' не существует. Пожалуйста, введите снова.");
                    validVote = false;
                    break;
                }
            }
            if (!validVote) {
                i--;
                continue;
            }
            
            // Начисление баллов по методу Борда
            for (int j = 0; j < numCandidates; ++j) {
                String candidateName = preferences[j];
                candidates.get(nameToIndex.get(candidateName)).bordaScore += (numCandidates - j - 1);
            }
            
            // Обновление парных сравнений для метода Кондорсе
            for (int j = 0; j < numCandidates; ++j) {
                for (int k = j + 1; k < numCandidates; ++k) {
                    String higher = preferences[j];
                    String lower = preferences[k];
                    Candidate higherCandidate = candidates.get(nameToIndex.get(higher));
                    higherCandidate.condorcetWins.put(lower, higherCandidate.condorcetWins.getOrDefault(lower, 0) + 1);
                }
            }
        }
        
        String bordaWinner = findBordaWinner(candidates);
        String condorcetWinner = findCondorcetWinner(candidates, numVoters);
        
        System.out.println("\nРезультаты:");
        System.out.println("Баллы по методу Борда:");
        for (Candidate candidate : candidates) {
            System.out.println(candidate.name + ": " + candidate.bordaScore);
        }
        
        System.out.println("\nПарные сравнения по Кондорсе:");
        for (Candidate candidate : candidates) {
            System.out.println(candidate.name + " wins against:");
            for (Candidate opponent : candidates) {
                if (!candidate.name.equals(opponent.name)) {
                    int wins = candidate.condorcetWins.getOrDefault(opponent.name, 0);
                    System.out.println("  " + opponent.name + ": " + wins + 
                                     " (" + (wins > numVoters / 2 ? "побеждает" : "проигрывает") + 
                                     ")");
                }
            }
        }
        
        System.out.println("\nПобедитель по методу Борда: " + bordaWinner);
        System.out.println("Победитель по методу Кондорсе: " + condorcetWinner);
        
        if (!bordaWinner.equals(condorcetWinner) && !condorcetWinner.equals("No Condorcet winner")) {
            System.out.println("\nПримечание: Разные методы голосования дали разных победителей. Это известно " +
                             "как парадокс голосования и демонстрирует, что разные системы голосования могут " +
                             "давать разные результаты при одинаковых предпочтениях избирателей.");
        }
        
        scanner.close();
    }
}