#include <iostream>
#include <string>
#include <algorithm>
#include <Windows.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define OS_WINDOWS
#endif

#define CONSOLE_YELLOW 14
#define CONSOLE_DEFAULT 7

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::sort;
const int N = 5001;

struct student {
    string name;
    double scores[N];
    double sum = 0;
};

int studentsCnt, examsCnt, sortType;
int examMax[N];
double examSum[N];
double allSum = 0;
student students[N];

int main()
{
#ifdef OS_WINDOWS
    HANDLE coutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(coutHandle, CONSOLE_DEFAULT);
#endif // OS_WINDOWS
    cout << "Input students count & exams count: ";
    cin >> studentsCnt >> examsCnt;
    cout << "Input exams maximum score: ";
    for (int i = 0; i < examsCnt; i++)
        cin >> examMax[i];
    cout << "Input each student\'s name & scores:" << endl;
    for (int i = 0; i < studentsCnt; i++)
    {
        cin >> students[i].name;
        for (int j = 0; j < examsCnt; j++) {
            cin >> students[i].scores[j];
            examSum[j] += students[i].scores[j];
            students[i].sum += students[i].scores[j];
        }
        allSum += students[i].sum;
    }
    cout << "Sorting type (1 for sum, 0 for average): ";
    cin >> sortType;
    if (sortType)
        sort(students, students + studentsCnt, [](student a, student b) {
            return a.sum > b.sum;
        });
    else
        sort(students, students + studentsCnt, [](student a, student b) {
            return a.sum / examsCnt < b.sum / examsCnt;
        });
    
    cout << "Ranking :: Name :: Sum :: Average :: Exams" << endl;
    for (int i = 0; i < studentsCnt; i++)
    {
#ifdef OS_WINDOWS
        if (i == 0) SetConsoleTextAttribute(coutHandle, CONSOLE_YELLOW);
#endif // OS_WINDOWS
        cout << i+1 << ". " << students[i].name << '\t' << students[i].sum << '\t' << students[i].sum / examsCnt;
        for (int j = 0; j < examsCnt; j++)
        {
            cout << '\t' << students[i].scores[j] << '/' << examMax[j];
        }
        cout << endl;
#ifdef OS_WINDOWS
        if (i == 0) SetConsoleTextAttribute(coutHandle, CONSOLE_DEFAULT);
#endif // OS_WINDOWS
    }

    for (int i = 0; i < examsCnt; i++)
        cout << "Exam " << i + 1 << " average: " << examSum[i] / studentsCnt << endl;
    cout << "Total average: " << allSum / studentsCnt << endl;
}
