#include <iostream>
#include <vector>
#include <tuple> 
using namespace std;

void MN(int n) {
    // Объявление вектора целых чисел R для хранения сопротивлений
    vector<int> R;
    // Цикл считывания сопротивлений R и добавления их в вектор R
    for (int num = 0; num < n; ++num) {
        int r;
        cout << "Введите R" << num+1 << ": ";
        cin >> r;
        R.push_back(r);
    }

    // Объявление вектора кортежей для хранения тройки значений (e, r, vect)
    vector<tuple<int, int, int>> E;
    // Два дополнительных вектора для хранения отдельных значений r и vect
    vector<int> r_list;
    vector<int> vect_list;
    // Цикл для считывания e, r, vect и добавления в соответствующие структуры
    for (int num = 0; num < n; ++num) {
        int e, r, vect;
        cout << "Введите e" << num+1 << ": ";
        cin >> e;
        cout << "Введите r" << num+1 << ": ";
        cin >> r;
        cout << "Введите vect" << num+1 << ": ";
        cin >> vect;
        E.emplace_back(e, r, vect);
        r_list.push_back(r);
        vect_list.push_back(vect);
    }

    // Создание двумерного вектора для хранения токов I
    vector<vector<double>> I_list(n, vector<double>(n, 0));
    // Вектор для хранения итоговых направлений
    vector<vector<int>> vect_list_final;
    // Цикл для расчёта токов и напряжений в цепи
    for (int num = 1; num <= n; ++num) {
        vector<double> I(n, 0);

        vector<int> R_copy = R;
        vector<int> r_list_copy = r_list;
        // Удаление элементов из копий векторов, чтобы смоделировать изменение схемы
        R_copy.erase(R_copy.begin() + num - 1);
        r_list_copy.erase(r_list_copy.begin() + num - 1);
        vector<int> vect_list_copy = vect_list;

        // Расчёт параллельного соединения сопротивлений
        double R_parall = (R_copy[0] + r_list_copy[0]) * (R_copy[1] + r_list_copy[1]) / ((R_copy[0] + r_list_copy[0]) + (R_copy[1] + r_list_copy[1]));
        cout << "Rперв.нетронут. = " << R_copy[0] << " Ом" << endl;
        cout << "Rвтор.нетронут. = " << R_copy[1] << " Ом" << endl;
        cout << "Rпаралл-" << num << " = " << R_parall << " Ом" << endl;
        // Расчёт эквивалентного сопротивления цепи
        double R_ekv = R_parall + R[num-1];
        cout << "Rэкв-" << num << " = " << R_ekv << " Ом" << endl;
        // Расчёт тока через эквивалентное сопротивление
        I[num-1] = get<0>(E[num-1]) / (R_ekv + get<1>(E[num-1]));
        cout << "I" << num << " = " << I[num-1] << " А" << endl;
        // Расчёт напряжения U на участке ab
        double U = R_parall * I[num-1];
        cout << "Uab-" << num << " = " << U << " В" << endl;

        // Корректировка токов и направлений для остальных элементов схемы
        for (int i = 0; i < n; ++i) {
            if (I[i] == 0) {
                I[i] = U / (R[num-1] + r_list[num-1]);
                cout << "I" << i << " = " << I[i] << " А" << endl;
            }
            if (i != num - 1) {
                vect_list_copy[i] = -1 * vect_list_copy[i];
            }
        }
        vect_list_final.push_back(vect_list_copy);
        I_list[num-1] = I;
    }

    // Вывод изначальных направлений тока
    cout << "Изначальные направления: ";
    for (int vect : vect_list) {
        cout << vect << " ";
    }
    cout << endl;

    // Вывод значений токов
    cout << "Токи: ";
    for (const auto& I : I_list) {
        for (double current_I : I) {
            cout << current_I << " ";
        }
    }
    cout << endl;

    // Вывод итоговых направлений тока
    cout << "Направления: ";
    for (const auto& vect : vect_list_final) {
        for (int current_vect : vect) {
            cout << current_vect << " ";
        }
    }
    cout << endl;

    // Объявление вектора для хранения итоговых значений токов (не используется далее в коде)
    vector<double> I_last(n, 0);
}

// Основная функция main
int main() {
    // Вызов функции MN с аргументом 3
    MN(3);
    return 0;
}