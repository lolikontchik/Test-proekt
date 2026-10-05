#include <iostream>
#include <locale.h>

using namespace std;

struct Anketa {
    char fam[25];
    char name[25];
    int year;
};

struct Stud {
    Anketa person;
    int group;
    int exam[4];
};

int main() {
    setlocale(LC_ALL, "RUS");
    Stud kurs[10] =
    {
        {{"Иванов", "Иван", 2006}, 1161, {5, 4, 2, 2}},
        {{"Петров", "Пётр", 2002}, 1145, {3, 5, 5, 3}},
        {{"Морозов", "Олег", 2005}, 1123, {2, 3, 2, 4}},
        {{"Сидоров", "Алексей", 2004}, 1159, {5, 4, 4, 4}},
        {{"Семёнов", "Семён", 2004}, 1201, {5, 4, 5, 4}},
        {{"Фёдоров", "Леонид", 2001}, 1161, {2, 5, 5, 3}},
        {{"Орлов", "Дмитрий", 2005}, 1099, {5, 3, 3, 5}},
        {{"Пушкин", "Александр", 2006}, 1122, {5, 5, 2, 4}},
        {{"Мамонов", "Иван", 2004}, 1171, {3, 5, 3, 4}},
        {{"Степанов", "Степан", 2003}, 1153, {5, 4, 5, 4}}
    };
    cout << "Список студентов и сумма баллов за аттестацию:\n\n";

    for (int i = 0; i < 10; i++) {
        int sum = 0;

        for (int j = 0; j < 4; j++) {
            sum += kurs[i].exam[j];
        }

        cout << "Фамилия: " << kurs[i].person.fam << endl;
        cout << "Имя: " << kurs[i].person.name << endl;
        cout << "Год рождения: " << kurs[i].person.year << endl;
        cout << "Группа: " << kurs[i].group << endl;

        cout << "Оценки: ";
        for (int j = 0; j < 4; j++) {
            cout << kurs[i].exam[j] << " ";
        }
        cout << endl;
        cout << "Сумма баллов: " << sum << endl;
        cout << "-----------------------------" << endl;
    }
    return 0;
}