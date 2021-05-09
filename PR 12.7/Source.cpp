#include <iostream>
#include <Windows.h>
#include <fstream>
#include <time.h>

using namespace std;

typedef int Info;

struct Elem
{
    Elem* link;
    Info info;
};

void insert(Elem*& L, Info value);
Info remove(Elem*& L);
void print(Elem* L);
void process(Elem* L, Elem*& T);
Info Fib(Info i);
bool check(Elem* L, Info value);
void read_file(Elem*& L);
Info count_elem(Elem* L);

int main()
{
    SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
    SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

    srand((unsigned)time(NULL));
    Elem* L = NULL;
    Elem* T = NULL; // список для інверсії в нього

    read_file(L);
    cout << "Оригінальний список: ";

    print(L);
    cout << endl;

    cout << "Чисел в списку: " << count_elem(L) << endl << endl;

    Info num;
    Info fib[100]; // створення масиву для занесення в нього чисел Фібоначчі
    cout << "Числа Фібоначчі: ";
    for (Info i = 0; i < 20; i++) // знаходження перших 20 чисел Фібоначчі і занесення їх у числовий масив 
    {
        num = Fib(i);
        fib[i] = num;
        cout << fib[i] << " ";
        if (Fib(i + 1) == num) { // пропуск однакових цифр
            i++;
        }
    }
    cout << endl << endl;
    Info k = 0;
    cout << "Числа, які збігаються з числами Фібоначчі: ";
    for (Info i = 0; i < 20; i++) {
        check(L, fib[i]);
    }
    cout << endl << endl;

    process(L, T); // інверсія списку

    cout << "Інвертований список: ";
    while (T != NULL) {
        cout << remove(T) << " ";
    }
    cout << endl;
}

void insert(Elem*& L, Info value) // додавання елементу у список
{
    Elem* tmp = new Elem; // створення допоміжного елемента 
    tmp->info = value;
    if (L != NULL) // Якщо список не порожній
    {
        Elem* T = L; // ще один допомоміжий елемент
        while (T->link != L) // сканування до останнього елементу 
            T = T->link; // перехід далі
        T->link = tmp;
    }
    else // Якщо список порожній
    {
        L = tmp;
    }
    tmp->link = L;
}

Info remove(Elem*& L) // видалення елементу зі списку 
{
    Elem* T = L; // допоміжний елемент
    while (T->link != L) // сканування до кінця списку
        T = T->link;
    Info value = L->info;
    if (T != L)
    {
        Elem* tmp = L->link;
        delete L;
        L = tmp;
        T->link = L;
    }
    else
    {
        delete L;
        L = NULL;
    }
    return value;
}

void print(Elem* L) {
    if (L == NULL)
        return;
    Elem* first = L;
    cout << L->info << " ";
    while (L->link != first)
    {
        L = L->link;
        cout << L->info << " ";
    }
    cout << endl;
}

Info Fib(Info i) // рекурсивне знаходження чисел Фібоначі

{
    Info value = 0;
    if (i < 1) return 0;
    if (i == 1) return 1;
    return Fib(i - 1) + Fib(i - 2);
}

void process(Elem* L, Elem*& T)
{
    if (L == NULL)
        return;
    Elem* first = L;
    Info k = 1; // оголошення лічильника 
    while (L->link != first) // перевірка до останнього
    {
        k++; // лічильник кількості елементів
        L = L->link; // перехід далі
    }
    L = first; // поврнення на початок
    Info value;
    for (Info j = 0; j < k; j++) {
        Info l = k - j - 1; // визначення елементу 
        for (Info temp = 0; temp < l; temp++) {
            L = L->link; // знаходиться елемент
        }
        value = L->info;
        L = first; // повернення на початок
        insert(T, value);
    }
}

bool check(Elem* L, Info value) {
    Elem* start = L;
    if (value < 0) { // захист від помилок
        return false;
    }
    if (L->info == value) {
        cout << value << " ";
        return true;
    }
    L = L->link;
    while (L != start) {
        if (L->info == value) {
            cout << value << " ";
            return true;
        }
        else {
            L = L->link;
        }
    }
    return false;
}

void read_file(Elem*& L)
{
    ifstream f("numbers.txt"); // відкриття потоку зчитування файла
    Info number;
    while (!f.eof()) { // всі інші цифри
        f >> number;
        insert(L, number);
    }
}

Info count_elem(Elem* L) { // рахунок кількості елементів у списку
    Info k = 1;
    Elem* start = L;
    L = L->link;
    while (L != start) {
        k++;
        L = L->link;
    }
    return k;
}