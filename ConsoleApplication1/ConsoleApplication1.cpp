#include <locale.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int Kolvo_Comb()
{
    string komb = "komb.txt";
    string str;
    ifstream comb;
    comb.open(komb);
    int kolvo_comb = 0;
    while (!comb.eof())
    {
        getline(comb, str);
        kolvo_comb++;
    }
    comb.close();
    return kolvo_comb;
}

float Kolvo_Res()
{
    string test = "test.txt";
    string str;
    ifstream Res;
    Res.open(test);
    int stroki = 0;
    while (!Res.eof())
    {
        getline(Res, str);
        stroki++;
    }
    Res.close();
    return stroki;
}


int main()
{

    setlocale(LC_ALL, "Russian");

    int kolvo_comb = Kolvo_Comb();
    double kolvo_res = Kolvo_Res();

    int* max_new_res = new int[kolvo_comb];
    int* first_work = new int[kolvo_comb];
    int* second_work = new int[kolvo_comb];
    int** resource = new int* [kolvo_comb];
    for (int i = 0; i < kolvo_comb; i++)
        resource[i] = new int[kolvo_comb];
    int* x = new int[kolvo_comb];
    double* y = new double[kolvo_comb];

    for (int i = 0; i < kolvo_comb; i++)
    {
        x[i] = 0;
        y[i] = 0;
        first_work[i] = 0;
        second_work[i] = 0;
        max_new_res[i] = 0;
    }



    const int  alfa = 1, gamma = 1;      //штрафы для критериев
    double sumUnStock = 0, sumRatedTime = 0;         //критерии эффективности 

    int** max_intensive = new int* [kolvo_comb];
    for (int i = 0; i < kolvo_comb; i++)
        max_intensive[i] = new int[kolvo_comb];

    int** min_intensive = new int* [kolvo_comb];
    for (int i = 0; i < kolvo_comb; i++)
        min_intensive[i] = new int[kolvo_comb];

    int** new_resource = new int* [kolvo_comb];
    for (int i = 0; i < kolvo_comb; i++)
        new_resource[i] = new int[kolvo_res];

    int count_work = 0;
    string nameF = "komb.txt"; // Считывание комбинаций
    ifstream comb;
    comb.open(nameF);
    while (!comb.eof())
    {
        for (int i = 0; i < kolvo_comb; i++)
        {
            comb >> first_work[i] >> second_work[i];
            if (second_work[i] > count_work)
                count_work = second_work[i];
        }
    }
    comb.close();

    string name = "test.txt"; // Первая таблица
    ifstream myfile;
    myfile.open(name);
    while (!myfile.eof())
    {
        for (int i = 0; i < kolvo_res; i++)
        {
            for (int j = 0; j < kolvo_comb; j++)
            {
                myfile >> resource[i][j];
            }
        }
    }
    myfile.close();
   
    cout << "\n\nВходные параметры задачи \n";
    cout << "\nКоличество ресурса k, необходимого для выполнения работы j: \n";
    cout << "-------";
    for (int i = 0; i < kolvo_comb; i++)
        cout << "--------";
    cout << "\n|     |";
    for (int i = 0; i < kolvo_comb; i++)
    {
        if (first_work[i] < 10)
            cout << " <" << first_work[i];
        else
            cout << "<" << first_work[i];
        if (first_work[i] < 10)
            cout << ", " << second_work[i] << ">|";
        else
            cout << "," << second_work[i] << ">|";
    }
    cout << "\n-------";
    for (int i = 0; i < kolvo_comb; i++)
        cout << "--------";
    for (int i = 0; i < kolvo_res; i++)
    {
        cout << "\n| k=" << i + 1 << " |";
        for (int j = 0; j < kolvo_comb; j++)
        {
            if (resource[i][j] < 10)
                cout << "   " << resource[i][j] << "   |";
            else
                cout << "  " << resource[i][j] << "   |";
        }
    }
    cout << "\n-------";
    for (int i = 0; i < kolvo_comb; i++)
        cout << "--------";

    string max_name = "max.txt"; // Таблица максимальных
    ifstream max;
    max.open(max_name);
    while (!max.eof())
    {
        for (int i = 0; i < kolvo_res; i++)
        {
            for (int j = 0; j < kolvo_comb; j++)
            {
                max >> max_intensive[i][j];
            }
        }
    }
    max.close();

    string min_name = "min.txt"; // Таблица минимальных
    ifstream min;
    min.open(min_name);
    while (!min.eof())
    {
        for (int i = 0; i < kolvo_res; i++)
        {
            for (int j = 0; j < kolvo_comb; j++)
            {
                min >> min_intensive[i][j];
            }
        }
    }
    min.close();
    cout << "\n\nМаксимальная и минимальная интенсивность потребления k ресурса работой j: \n";
    cout << "-------";
    for (int i = 0; i < kolvo_comb; i++)
        cout << "--------";
    cout << "\n|     |";
    for (int i = 0; i < kolvo_comb; i++)
    {
        if (first_work[i] < 10)
            cout << " <" << first_work[i];
        else
            cout << "<" << first_work[i];
        if (first_work[i] < 10)
            cout << ", " << second_work[i] << ">|";
        else
            cout << "," << second_work[i] << ">|";
    }
    cout << "\n-------";
    for (int i = 0; i < kolvo_comb; i++)
        cout << "--------";
    for (int i = 0; i < kolvo_res; i++)
    {
        cout << "\n| k=" << i + 1 << " |";
        for (int j = 0; j < kolvo_comb; j++)
        {
            if (max_intensive[i][j] < 10)
                cout << "  " << max_intensive[i][j] << "/";
            else
                cout << " " << max_intensive[i][j] << "/";
            if (min_intensive[i][j] < 10)
                cout << min_intensive[i][j] << "  |";
            else
                cout << min_intensive[i][j] << " |";
        }
    }
    cout << "\n-------";
    for (int i = 0; i < kolvo_comb; i++)
        cout << "--------";


    cout << "\nОрганичения, описывающие сетевую модель: \n";
    for (int k = 0; k < kolvo_comb; k++)
    {
        int flag = 0;
        for (int l = 0; l < kolvo_comb; l++)
        {
            if (first_work[k] == second_work[l])
                flag++;
        }
        if (flag == 0)
            cout << "x<" << first_work[k] << "," << second_work[k] << "> >= 0;\n";

        else
        {
            cout << "x<" << first_work[k] << "," << second_work[k] << "> >= max( ";
            for (int l = 0; l < kolvo_comb; l++)
            {
                if (first_work[k] == second_work[l])
                    cout << "y<" << first_work[l] << "," << second_work[l] << "> ";
            }
            cout << ") + 1;\n";
        }

    }

    for (int i = 0; i < kolvo_res; i++)
    {
        for (int j = 0; j < kolvo_comb; j++)
        {
            if (resource[i][j] == 0)
                new_resource[i][j] = 0;
            else
            {
                float res;
                res = (float)resource[i][j] / max_intensive[i][j];
                if ((float)((int)res) == res)
                    new_resource[i][j] = res;
                else
                    new_resource[i][j] = (float)((int)res) + 1;
            }
        }
    }

    for (int i = 0; i < kolvo_comb; i++)
    {
        max_new_res[i] = 0;
        for (int j = 0; j < kolvo_res; j++)
        {
            if (new_resource[j][i] > max_new_res[i])
                max_new_res[i] = new_resource[j][i];
        }
    }


    cout << "\nТаблица потребления ресурсов: \n";
    cout << "-------";
    for (int i = 0; i < kolvo_comb; i++)
        cout << "--------";
    cout << "\n|     |";
    for (int i = 0; i < kolvo_comb; i++)
    {
        if (first_work[i] < 10)
            cout << " <" << first_work[i];
        else
            cout << "<" << first_work[i];
        if (first_work[i] < 10)
            cout << ", " << second_work[i] << ">|";
        else
            cout << "," << second_work[i] << ">|";
    }
    cout << "\n-------";
    for (int i = 0; i < kolvo_comb; i++)
        cout << "--------";
    for (int i = 0; i < kolvo_res; i++)
    {
        cout << "\n| k=" << i + 1 << " |";
        for (int j = 0; j < kolvo_comb; j++)
        {
            if (new_resource[j][i] < 10)
                cout << "   " << new_resource[i][j] << "   |";
            else
                cout << "  " << new_resource[i][j] << "   |";
        }
    }
    cout << "\n-------";
    for (int i = 0; i < kolvo_comb; i++)
        cout << "--------";
    cout << "\n| max |";
    for (int j = 0; j < kolvo_comb; j++)
    {
        if (max_new_res[j] < 10)
            cout << "   " << max_new_res[j] << "   |";
        else
            cout << "  " << max_new_res[j] << "   |";
    }
    cout << "\n-------";
    for (int i = 0; i < kolvo_comb; i++)
        cout << "--------";
    int kolvo_dir_work;
    cout << "\nВведите количество работ, имеющих директивные сроки: ";
    cin >> kolvo_dir_work;
    while (kolvo_dir_work < 1)
    {
        cout << "\nКоличество работ должно быть > 0, повторите ввод: ";           // возможность сделать 0 и проверка
        cin >> kolvo_dir_work;
    }
    cout << "\nВведите работу и ее директивный срок(начальная работа, пробел, конечная работа, пробел, директивный срок): ";
    int* direct_time = new int[kolvo_dir_work];
    int* direct_first_work = new int[kolvo_dir_work];
    int* direct_second_work = new int[kolvo_dir_work];
    int* direct_index = new int[kolvo_dir_work];
    bool b = true;

    for (int i = 0; i < kolvo_comb; i++)
    {
        direct_time[i] = 0;
        direct_first_work[i] = 0;
        direct_second_work[i] = 0;
        direct_index[i] = 0;
    }

    for (int i = 0; i < kolvo_dir_work; i++)
    {
        b = false;
        cin >> direct_first_work[i] >> direct_second_work[i] >> direct_time[i];
        for (int j = 0; j < kolvo_comb; j++)
        {
            if ((first_work[j] == direct_first_work[i]) && (second_work[j] == direct_second_work[i]))
            {
                direct_index[i] = j;
                b = true;
                break;
            }
        }
        if (b == true)
            break;
        while (b == false)
        {
            cout << "\nНекорректно заданы работы, повторите ввод: ";
            cin >> direct_first_work[i] >> direct_second_work[i] >> direct_time[i];
            for (int k = 0; k < kolvo_comb; k++)
            {
                if ((first_work[k] == direct_first_work[k]) && (second_work[k] == direct_second_work[k]))
                {
                    direct_index[i] = k;
                    b = true;
                }
            }
        }
    }
    int max_way = 0;
    int before_work;
    int* precursor = new int[count_work];        //предшественник
    int* tek_lenght = new int[count_work];
    int* max_tek_length = new int[count_work];
    for (int i = 0; i < count_work; i++)
    {
        max_tek_length[i] = 0;
        precursor[i] = 0;
        tek_lenght[i] = 0;
    }
    for (int l = 0; l < count_work; l++)
    {
        for (int k = 0; k < kolvo_comb; k++)
        {
            if ((second_work[k] == (l + 1)))
            {
                before_work = first_work[k];
                tek_lenght[l] = max_new_res[k] + max_tek_length[before_work - 1];
                if (tek_lenght[l] > max_tek_length[l])
                {
                    max_tek_length[l] = tek_lenght[l];
                    precursor[l] = before_work;
                    max_way = max_tek_length[l];
                }
            }
        }
    }

    for (int l = 0; l < count_work; l++)
    {
        for (int k = 0; k < kolvo_comb; k++)
        {
            x[k] = max_tek_length[first_work[k] - 1] + 1;
            tek_lenght[l] = max_new_res[k] + max_tek_length[before_work - 1];
            y[k] = x[k] + max_new_res[k] - 1;
        }
    }
    cout << "\nТаблица тактов выполнения работ: \n";
    cout << "-------";
    for (int i = 0; i < kolvo_comb; i++)
        cout << "--------";
    cout << "\n|     |";
    for (int i = 0; i < kolvo_comb; i++)
    {
        if (first_work[i] < 10)
            cout << " <" << first_work[i];
        else
            cout << "<" << first_work[i];
        if (first_work[i] < 10)
            cout << ", " << second_work[i] << ">|";
        else
            cout << "," << second_work[i] << ">|";
    }
    cout << "\n-------";
    for (int i = 0; i < kolvo_comb; i++)
        cout << "--------";
    cout << "\n|  х  |";
    for (int j = 0; j < kolvo_comb; j++)
    {
        if (x[j] < 10)
            cout << "   " << x[j] << "   |";
        else
            cout << "  " << x[j] << "   |";
    }
    cout << "\n|  y  |";
    for (int j = 0; j < kolvo_comb; j++)
    {
        if (y[j] < 10)
            cout << "   " << y[j] << "   |";
        else
            cout << "  " << y[j] << "   |";
    }
    cout << "\n-------";
    for (int i = 0; i < kolvo_comb; i++)
        cout << "--------";

    cout << "\nгде х-номер такта начала работы j, y-номер такта окончания работы j;\n";
    //необходимые и достаточные условия
    bool sost = true;
    for (int i = 0; i < kolvo_dir_work; i++)
    {
        sumRatedTime = 0;
        if (y[direct_index[i]] <= direct_time[i])
            sost = true;
        else
        {
            sost = false;
            sumRatedTime = sumRatedTime + gamma * 100 * (float)((y[direct_index[i]] - direct_time[i]) / direct_time[i]);
            break;
        }
        if (sost == false)
            break;
    }
    if (sost == true)
    {
        for (int j = 0; j < kolvo_res; j++)
        {
            for (int i = 0; i < kolvo_comb; i++)
            {
                if ((max_new_res[i] * min_intensive[j][i]) <= resource[j][i])
                    sost = true;
                else
                {
                    sost = false;
                    break;
                }
                if (sost == false)
                    break;
            }
        }
    }
    double** z = new double* [kolvo_comb];
    double* kritRes = new double[kolvo_res];
    for (int i = 0; i < kolvo_comb; i++)
        z[i] = new double[kolvo_comb];
    if (sost == true)
    {
        cout << "\nНеобходимые и достаточные условия выполняются, система ограничений совместна. Тогда:";
        for (int i = 0; i < kolvo_res; i++)
        {
            sumUnStock = 0;
            for (int j = 0; j < kolvo_comb; j++)
            {
                if (resource[i][j] == 0)
                    z[i][j] = 0;
                else
                    z[i][j] = (double)(resource[i][j]) / (double)(y[j] - x[j] + 1);
                sumUnStock += alfa * ((((y[j] - x[j] + 1) * z[i][j]) - resource[i][j]) / resource[i][j]) * 100;
            }
           
            kritRes[i] = sumUnStock;
        }


        cout << "\nКоличество k ресурса, которое будет выделено работе j в такте t: ";
        cout << "\n-------";
        for (int i = 0; i < kolvo_comb; i++)
            cout << "--------";
        cout << "\n|     |";
        for (int i = 0; i < kolvo_comb; i++)
        {
            if (first_work[i] < 10)
                cout << " <" << first_work[i];
            else
                cout << "<" << first_work[i];
            if (first_work[i] < 10)
                cout << ", " << second_work[i] << ">|";
            else
                cout << "," << second_work[i] << ">|";
        }
        cout << "\n-------";
        for (int i = 0; i < kolvo_comb; i++)
            cout << "--------";
        for (int i = 0; i < kolvo_res; i++)
        {
            cout << "\n| k=" << i + 1 << " |";
            for (int j = 0; j < kolvo_comb; j++)
            {

                cout << setw(5) << z[i][j] << "  |";
            }
        }
        cout << "\n-------";
        for (int i = 0; i < kolvo_comb; i++)
            cout << "--------";
        cout << "\nномера|";
        for (int i = 0; i < kolvo_comb; i++)
            cout << "       |";
        cout << "\nтактов|";
        for (int i = 0; i < kolvo_comb; i++)
        {
            if (x[i] == y[i])
            {
                if (x[i] < 10)
                    cout << "   " << x[i] << "   |";
                else
                    cout << "  " << x[i] << "   |";
            }
            else
            {
                if (x[i] < 10)
                    cout << "  " << x[i] << "-";
                else
                    cout << " " << x[i] << "-";
                if (y[i] < 10)
                    cout << y[i] << "  |";
                else
                    cout << y[i] << " |";
            }
        }
        cout << "\nпотр. |";
        for (int i = 0; i < kolvo_comb; i++)
            cout << "       |";
        cout << "\nресур.|";
        for (int i = 0; i < kolvo_comb; i++)
            cout << "       |";
        cout << "\n-------";
        for (int i = 0; i < kolvo_comb; i++)
            cout << "--------";

        bool itogKrit = true;
        for (int p = 0; p < kolvo_res; p++)
        {
            if (kritRes[p] > 0)
            {
                cout << "\nКритерий оптимальности, связанный с обеспеченностью системы ресурсом" << p + 1 << "нарушен. Задача может быть решина с применением метода штрафов";
                itogKrit = false;
            }
        }
        
        if (itogKrit == true)
            cout << "\n\nКритерии эффективности и качества в задаче не нарушены! ";
    }
    else
    {
        cout << "\nСистема ограничений не совместна. Необходимые критерии эффективности и качества не выполняются.";
        if (sumRatedTime > 0)
            cout << "\nДиррективные сроки работ будут нарушены. Задача может быть решена с применением метода штрафов.";
        cout << "\nПопробуйте изменить параметры задачи!\n";
    }
    delete[] first_work;
    delete[] second_work;
    delete[] resource;
    delete[] max_intensive;
    delete[] min_intensive;
    delete[] max_new_res;
    delete[] new_resource;
    delete[] x;
    delete[] y;
    delete[] precursor;
    delete[] tek_lenght;
    delete[] max_tek_length;
    delete[] z;
    delete[] direct_index;
    delete[] direct_time;
    delete[] direct_first_work;
    delete[] direct_second_work;
}