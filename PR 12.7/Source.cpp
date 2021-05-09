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
    SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
    SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������

    srand((unsigned)time(NULL));
    Elem* L = NULL;
    Elem* T = NULL; // ������ ��� ������ � �����

    read_file(L);
    cout << "����������� ������: ";

    print(L);
    cout << endl;

    cout << "����� � ������: " << count_elem(L) << endl << endl;

    Info num;
    Info fib[100]; // ��������� ������ ��� ��������� � ����� ����� Գ�������
    cout << "����� Գ�������: ";
    for (Info i = 0; i < 20; i++) // ����������� ������ 20 ����� Գ������� � ��������� �� � �������� ����� 
    {
        num = Fib(i);
        fib[i] = num;
        cout << fib[i] << " ";
        if (Fib(i + 1) == num) { // ������� ��������� ����
            i++;
        }
    }
    cout << endl << endl;
    Info k = 0;
    cout << "�����, �� ��������� � ������� Գ�������: ";
    for (Info i = 0; i < 20; i++) {
        check(L, fib[i]);
    }
    cout << endl << endl;

    process(L, T); // ������� ������

    cout << "������������ ������: ";
    while (T != NULL) {
        cout << remove(T) << " ";
    }
    cout << endl;
}

void insert(Elem*& L, Info value) // ��������� �������� � ������
{
    Elem* tmp = new Elem; // ��������� ���������� �������� 
    tmp->info = value;
    if (L != NULL) // ���� ������ �� �������
    {
        Elem* T = L; // �� ���� ���������� �������
        while (T->link != L) // ���������� �� ���������� �������� 
            T = T->link; // ������� ���
        T->link = tmp;
    }
    else // ���� ������ �������
    {
        L = tmp;
    }
    tmp->link = L;
}

Info remove(Elem*& L) // ��������� �������� � ������ 
{
    Elem* T = L; // ��������� �������
    while (T->link != L) // ���������� �� ���� ������
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

Info Fib(Info i) // ���������� ����������� ����� Գ������

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
    Info k = 1; // ���������� ��������� 
    while (L->link != first) // �������� �� ����������
    {
        k++; // �������� ������� ��������
        L = L->link; // ������� ���
    }
    L = first; // ��������� �� �������
    Info value;
    for (Info j = 0; j < k; j++) {
        Info l = k - j - 1; // ���������� �������� 
        for (Info temp = 0; temp < l; temp++) {
            L = L->link; // ����������� �������
        }
        value = L->info;
        L = first; // ���������� �� �������
        insert(T, value);
    }
}

bool check(Elem* L, Info value) {
    Elem* start = L;
    if (value < 0) { // ������ �� �������
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
    ifstream f("numbers.txt"); // �������� ������ ���������� �����
    Info number;
    while (!f.eof()) { // �� ���� �����
        f >> number;
        insert(L, number);
    }
}

Info count_elem(Elem* L) { // ������� ������� �������� � ������
    Info k = 1;
    Elem* start = L;
    L = L->link;
    while (L != start) {
        k++;
        L = L->link;
    }
    return k;
}