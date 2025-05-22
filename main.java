package first.fisrt_java;

import java.util.ArrayList;
import java.util.List;

public class main {
    private static final double E = 0.0001;

    private static double f(double x) {
        return x * Math.log(x + 1) - 1;
    }

    private static double f1(double x) {
        return Math.log(x + 1) + x / (x + 1);
    }

    private static double phi(double x) throws RuntimeException {
        double denominator = Math.log(x + 1);
        if (denominator == 0 || x + 1 <= 0) throw new RuntimeException("Недопустимое значение в phi(x)");
        return 1.0 / denominator;
    }

    private static int halfDivision(double a, double b, List<Double> roots) {
        if (f(a) * f(b) >= 0.0) {
            System.out.println("Неверный интервал для метода половинного деления");
            return 0;
        }
        int k = 0;
        double c = 0;
        System.out.println("ПРОГРАММА УТОЧНЕНИЯ КОРНЯ МЕТОДОМ ПОЛОВИННОГО ДЕЛЕНИЯ С ТОЧНОСТЬЮ ДО E");
        System.out.printf("%2s | %7s | %9s | %s%n", "N", "an", "bn", "bn - an");
        while (Math.abs(b - a) >= E) {
            c = (a + b) / 2;
            System.out.printf("%2d | %7.4f | %9.4f | %.4f%n", k, a, b, Math.abs(b - a));
            if (f(c) == 0.0) break;
            if (f(c) * f(a) < 0) b = c;
            else a = c;
            k++;
        }
        roots.add(c);
        System.out.printf("КОРЕНЬ %.4f С %d ИТЕРАЦИЯМИ%n", c, k);
        return k;
    }

    // Метод Ньютона
    private static int newtonMethod(double x0, List<Double> roots) {
        int k = 0;
        double x1 = x0 - f(x0) / f1(x0);
        System.out.println("\nПРОГРАММА УТОЧНЕНИЯ КОРНЯ МЕТОДОМ НЬЮТОНА С ТОЧНОСТЬЮ ДО E");
        System.out.printf("%2s | %7s | %9s | %s%n", "N", "xn", "xn+1", "xn+1 - xn");
        while (Math.abs(x1 - x0) > E) {
            System.out.printf("%2d | %7.4f | %9.4f | %.4f%n", k, x0, x1, Math.abs(x1 - x0));
            x0 = x1;
            x1 = x0 - f(x0) / f1(x0);
            k++;
        }
        roots.add(x1);
        System.out.printf("КОРЕНЬ %.4f С %d ИТЕРАЦИЯМИ%n", x1, k);
        return k;
    }

    // Метод простых итераций
    private static int simpleIterations(double x0, List<Double> roots) {
        try {
            int k = 0;
            double x1 = phi(x0);
            System.out.println("\nМЕТОД ПРОСТЫХ ИТЕРАЦИЙ");
            System.out.printf("%2s | %7s | %9s | %s%n", "N", "xn", "xn+1", "xn+1 - xn");
            while (Math.abs(x1 - x0) > E) {
                System.out.printf("%2d | %7.4f | %9.4f | %.4f%n", k, x0, x1, Math.abs(x1 - x0));
                x0 = x1;
                x1 = phi(x0);
                k++;
            }
            roots.add(x1);
            System.out.printf("КОРЕНЬ %.4f С %d ИТЕРАЦИЯМИ%n", x1, k);
            return k;
        } catch (RuntimeException e) {
            System.out.println("Ошибка в методе простых итераций: " + e.getMessage());
            return 0;
        }
    }

    public static void main(String[] args) {
        List<Double> roots = new ArrayList<>();
        int s1, s2, s3;

        s1 = halfDivision(1, 2, roots);

        s2 = newtonMethod(1.5, roots);

        s3 = simpleIterations(1.5, roots);

        System.out.println("\nВСЕ КОРНИ УРАВНЕНИЯ");
        for (double root : roots) {
            System.out.printf("%.4f ", root);
        }
        System.out.println();

        System.out.println("\nСКОРОСТЬ СХОДИМОСТИ:");
        System.out.println("У НЬЮТОНА " + s2 + " ИТЕРАЦИЙ");
        System.out.println("У МЕТОДА ПРОСТЫХ ИТЕРАЦИЙ " + s3 + " ИТЕРАЦИЙ");
        System.out.println("У МЕТОДА ПОЛОВИННОГО ДЕЛЕНИЯ " + s1 + " ИТЕРАЦИЙ");

        if (s1 < s2 && s1 < s3) {
            System.out.println("МЕТОД ПОЛОВИННОГО ДЕЛЕНИЯ НАИБОЛЕЕ ЭФФЕКТИВЕН ПО СКОРОСТИ СХОДИМОСТИ.");
        } else if (s2 < s1 && s2 < s3) {
            System.out.println("МЕТОД НЬЮТОНА НАИБОЛЕЕ ЭФФЕКТИВЕН ПО СКОРОСТИ СХОДИМОСТИ.");
        } else {
            System.out.println("МЕТОД ПРОСТЫХ ИТЕРАЦИЙ НАИБОЛЕЕ ЭФФЕКТИВЕН ПО СКОРОСТИ СХОДИМОСТИ.");
        }
    }
}