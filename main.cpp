#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

const double E = 0.0001;

double f(double x) 
{
    return x * log(x + 1) - 1;
}


double f1(double x) 
{
    return log(x + 1) + x / (x + 1);
}

double phi(double x) 
{
    double den = log(x + 1); 
    if (den == 0 || x + 1 <= 0) throw runtime_error("Недопустимое значение в phi(x)");
    return 1.0 / den;
}

int halfDivision(double a, double b, vector<double>& roots) 
{
    if (f(a) * f(b) >= 0.0) 
    {
        cout << "Неверный интервал для метода половинного деления" << endl;
        return 0;
    }
    int k = 0;
    double c;
    cout << "ПРОГРАММА УТОЧНЕНИЯ КОРНЯ МЕТОДОМ ПОЛОВИННОГО ДЕЛЕНИЯ С ТОЧНОСТЬЮ ДО E" << endl;
    cout << setw(2) << "N" << " | " << setw(7) << "an" << " | " << setw(9) << "bn" << " | " << "bn - an" << endl;
    while (abs(b - a) >= E) 
    {
        c = (a + b) / 2;
        cout << setw(2) << k << " | " << fixed << setprecision(4) << setw(7) << a 
             << " | " << setw(9) << b << " | " << abs(b - a) << endl;
        if (f(c) == 0.0) break;
        if (f(c) * f(a) < 0) b = c;
        else a = c;
        k++;
    }
    roots.push_back(c);
    cout << "КОРЕНЬ " << fixed << setprecision(4) << c << " С " << k << " ИТЕРАЦИЯМИ" << endl;
    return k;
}

// Метод Ньютона
int newtonMethod(double x0, vector<double>& roots) 
{
    int k = 0;
    double x1 = x0 - f(x0) / f1(x0);
    cout << endl << "ПРОГРАММА УТОЧНЕНИЯ КОРНЯ МЕТОДОМ НЬЮТОНА С ТОЧНОСТЬЮ ДО E" << endl;
    cout << setw(2) << "N" << " | " << setw(7) << "xn" << " | " << setw(9) << "xn+1" << " | " << "xn+1 - xn" << endl;
    while (abs(x1 - x0) > E) {
        cout << setw(2) << k << " | " << fixed << setprecision(4) << setw(7) << x0 
             << " | " << setw(9) << x1 << " | " << abs(x1 - x0) << endl;
        x0 = x1;
        x1 = x0 - f(x0) / f1(x0);
        k++;
    }
    roots.push_back(x1);
    cout << "КОРЕНЬ " << fixed << setprecision(4) << x1 << " С " << k << " ИТЕРАЦИЯМИ" << endl;
    return k;
}

// Метод простых итераций
int simpleIterations(double x0, vector<double>& roots) 
{
    try 
    {
        int k = 0;
        double x1 = phi(x0);
        cout << endl << "МЕТОД ПРОСТЫХ ИТЕРАЦИЙ" << endl;
        cout << setw(2) << "N" << " | " << setw(7) << "xn" << " | " << setw(9) << "xn+1" << " | " << "xn+1 - xn" << endl;
        while (abs(x1 - x0) > E) 
        {
            cout << setw(2) << k << " | " << fixed << setprecision(4) << setw(7) << x0 
                 << " | " << setw(9) << x1 << " | " << abs(x1 - x0) << endl;
            x0 = x1;
            x1 = phi(x0);
            k++;
        }
        roots.push_back(x1);
        cout << "КОРЕНЬ " << fixed << setprecision(4) << x1 << " С " << k << " ИТЕРАЦИЯМИ" << endl;
        return k;
    } catch (const runtime_error& e) 
    {
        cout << "Ошибка в методе простых итераций: " << e.what() << endl;
        return 0;
    }
}

int main() 
{
    vector<double> roots;
    int s1, s2, s3;

    s1 = halfDivision(1, 2, roots);

    s2 = newtonMethod(1.5, roots);

    s3 = simpleIterations(1.5, roots);

    cout << endl << "ВСЕ КОРНИ УРАВНЕНИЯ" << endl;
    for (double root : roots) 
    {
        cout << fixed << setprecision(4) << root << " ";
    }
    cout << endl;

    cout << endl << "СКОРОСТЬ СХОДИМОСТИ:" << endl;
    cout << "У НЬЮТОНА " << s2 << " ИТЕРАЦИЙ" << endl;
    cout << "У МЕТОДА ПРОСТЫХ ИТЕРАЦИЙ " << s3 << " ИТЕРАЦИЙ" << endl;
    cout << "У МЕТОДА ПОЛОВИННОГО ДЕЛЕНИЯ " << s1 << " ИТЕРАЦИЙ" << endl;
    
    cout << "МЕТОД НЬЮТОНА НАИБОЛЕЕ ЭФФЕКТИВЕН ПО СКОРОСТИ СХОДИМОСТИ." << endl;
    
    return 0;
}