#include <iostream>
#include <vector>
#include <string>
using namespace std;
int Hrazr(int number, int rank)
{
    while (rank > 1)
    {
        number /= 10;
        rank--;
    }
    return number % 10;
}
void digitalSort(std::vector <int>& mas, int rank) {
    //для удобства создадим двумерный массив нулей
    //позже в одномерных массивах будут цифры, в двумерном - числа из этих цифр
    vector <int> mas1;
    vector <vector <int>> mas2;
    int i, j, temp = 0;
    mas2.resize(mas.size());
    for (i = 0; i < mas.size(); i++) {
        mas1.push_back(0);
        for (j = 0; j < mas.size(); j++)
            mas2[i].push_back(0);
    }

    //cтавим элемент в нужное место двумерного массива по цифре разряда
    for (i = 0; i < mas.size(); i++)
    {
        int a = Hrazr(mas[i], rank);
        mas2[mas1[a]][a] = mas[i];
        mas1[a]++;
    }
    //обратно заполняем массив
    for (i = 0; i < mas.size(); i++)
    {
        for (j = 0; j < mas1[i]; j++)
        {
            mas[temp] = mas2[j][i];
            temp++;
        }
    }
}


void digitalSortAssistant(int maxrazr, vector<int>& mas) {
    for (int razr = 1; razr < maxrazr + 1; razr++)
        digitalSort(mas, razr);
}

int main() {
    //максимальная разрядность числа
    int maxrazr = 4;
    vector <int> mas = { 1234, 543, 1260, 235, 827, 1234, 85, 1245, 2917, 7492, 2718, 2193, 2874, 184, 35, 4827, 2947 };
    digitalSortAssistant(maxrazr, mas);

    for (int i = 0; i < mas.size(); i++)
        cout << mas[i] << endl;
    return 0;
}