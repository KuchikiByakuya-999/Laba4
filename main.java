package second.second_java;

import java.util.*;

public class main {
    public static int randomInt(int min, int max) {
        Random random = new Random();
        return random.nextInt(max - min + 1) + min;
    }

    public static boolean isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Введите кол-во элементов: ");
        int n = scanner.nextInt();
        List<Integer> arr1 = new ArrayList<>();
        for (int i = 0; i < n; ++i) {
            arr1.add(randomInt(10, 30));
        }

        List<Integer> arr2 = new ArrayList<>();
        for (int i = 0; i < 5; ++i) {
            arr2.add(randomInt(10, 30));
        }

        System.out.println("1. Инициализированные массивы:");
        System.out.print("arr1 (" + n + " элементов): ");
        printListWithSpace(arr1);
        System.out.print("arr2 (5 элементов): ");
        printListWithSpace(arr2);
        System.out.println();

        // 2. Четные элементы arr1 на нечетных местах
        System.out.println("2. Четные элементы arr1 на нечетных местах:");
        int count_even = 0;
        List<Integer> even_elements = new ArrayList<>();
        for (int i = 1; i < n; i += 2) {
            if (arr1.get(i) % 2 == 0) {
                count_even++;
                even_elements.add(arr1.get(i));
            }
        }
        System.out.print("Элементы: ");
        printListWithSpace(even_elements);
        System.out.println("Количество: " + count_even + "\n");

        // 3. Какие числа из arr2 встречаются в arr1
        System.out.println("3. Числа из arr2, встречающиеся в arr1:");
        Map<Integer, Integer> frequency = new HashMap<>();
        for (int num : arr1) {
            frequency.put(num, frequency.getOrDefault(num, 0) + 1);
        }

        boolean found = false;
        for (int num : arr2) {
            if (frequency.containsKey(num)) {
                found = true;
                System.out.println("Число " + num + " встречается " + frequency.get(num) + " раз(а)");
            }
        }

        if (!found) {
            System.out.println("Ни одно число из arr2 не встречается в arr1");
        }
        System.out.println();

        // 4. Модификация массива случайных символов
        System.out.println("4. Модификация массива символов:");
        System.out.print("Введите кол-во элементов: ");
        int m = scanner.nextInt();
        List<Character> charArr = new ArrayList<>();
        for (int i = 0; i < m; ++i) {
            charArr.add((char) randomInt(32, 126));
        }

        System.out.print("Исходный массив (" + m + " элементов): ");
        printCharListWithSpace(charArr);

        if (m > 0) {
            char last = charArr.get(charArr.size() - 1);
            for (int i = m - 1; i > 0; --i) {
                charArr.set(i, charArr.get(i - 1));
            }
            charArr.set(0, last);
        }

        System.out.print("После циклического сдвига вправо: ");
        printCharListWithSpace(charArr);
        System.out.println();

        // 5. Работа с числами 1000-9000
        System.out.println("5. Работа с числами 1000-9000:");
        System.out.print("Введите кол-во элементов: ");
        int p = scanner.nextInt();
        List<Integer> numbers = new ArrayList<>();
        int original_sum = 0;

        for (int i = 0; i < p; ++i) {
            int num = randomInt(1000, 9000);
            numbers.add(num);
            original_sum += num;
        }

        System.out.print("Исходный массив (" + p + " элементов): ");
        printListWithSpace(numbers);
        System.out.println("Сумма элементов: " + original_sum);

        for (int i = 0; i < numbers.size(); ++i) {
            String s = numbers.get(i).toString();
            char[] chars = s.toCharArray();
            Arrays.sort(chars);
            s = new String(chars);
            while (s.length() > 1 && s.charAt(0) == '0') {
                s = s.substring(1);
            }
            numbers.set(i, s.isEmpty() ? 0 : Integer.parseInt(s));
        }

        System.out.print("После сортировки цифр в каждом числе: ");
        printListWithSpace(numbers);

        // Сортировка массива по возрастанию
        Collections.sort(numbers);
        System.out.print("После сортировки всего массива: ");
        printListWithSpace(numbers);

        int new_sum = 0;
        for (int num : numbers) {
            new_sum += num;
        }
        System.out.println("Сумма после преобразований: " + new_sum);
        System.out.println("Разница с исходной суммой: " + Math.abs(original_sum - new_sum));
    }

    private static void printListWithSpace(List<Integer> list) {
        for (int i = 0; i < list.size(); i++) {
            if (i > 0) System.out.print(" ");
            System.out.print(list.get(i));
        }
        System.out.println();
    }

    private static void printCharListWithSpace(List<Character> list) {
        for (int i = 0; i < list.size(); i++) {
            if (i > 0) System.out.print(" ");
            System.out.print(list.get(i));
        }
        System.out.println();
    }
}