
#include <iostream>
#include <iomanip>
#include <string>
#include <locale>
using namespace std;

// Перелік для спеціальностей
enum Specialization {
    COMPUTER_SCIENCE,
    INFORMATICS,
    MATH_ECONOMICS,
    PHYSICS_INFORMATICS,
    LABOR_EDUCATION
};

// Структура для зберігання даних про студента
struct Student {
    string surname;
    int course;
    Specialization spec;
    double physics;
    double math;

    union {
        double programming;
        double numericalMethods;
        double pedagogy;
    } thirdGrade;
};

// Функція для виведення назви спеціальності
string getSpecializationName(Specialization spec) {
    switch (spec) {
    case COMPUTER_SCIENCE: return "Computer Science";
    case INFORMATICS: return "Informatics";
    case MATH_ECONOMICS: return "Math & Economics";
    case PHYSICS_INFORMATICS: return "Physics & Informatics";
    case LABOR_EDUCATION: return "Labor Education";
    default: return "Unknown";
    }
}

// Функція для введення даних студента
void inputStudentData(Student& student) {
    cout << "Введiть прiзвище студента: ";
    cin >> student.surname;
    cout << "Введiть курс (цiле число): ";
    cin >> student.course;

    int specChoice;
    cout << "Оберiть спецiальнiсть (0 - Computer Science, 1 - Informatics, 2 - Math & Economics, 3 - Physics & Informatics, 4 - Labor Education): ";
    cin >> specChoice;
    student.spec = static_cast<Specialization>(specChoice);

    cout << "Введiть оцiнку з фiзики: ";
    cin >> student.physics;
    cout << "Введiть оцiнку з математики: ";
    cin >> student.math;

    // Введення третьої оцінки залежно від спеціальності
    if (student.spec == COMPUTER_SCIENCE) {
        cout << "Введiть оцiнку з програмування: ";
        cin >> student.thirdGrade.programming;
    }
    else if (student.spec == INFORMATICS) {
        cout << "Введiть оцiнку з чисельних методiв: ";
        cin >> student.thirdGrade.numericalMethods;
    }
    else {
        cout << "Введiть оцiнку з педагогiки: ";
        cin >> student.thirdGrade.pedagogy;
    }
    cout << endl;
}

// Функція для створення масиву студентів
void createStudentsArray(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Студент №" << i + 1 << ":\n";
        inputStudentData(students[i]);
    }
}

// Функція для виведення таблиці з даними студентів
void printStudentsTable(const Student students[], int n) {
    cout << left << setw(5) << "№"
        << setw(15) << "Прiзвище"
        << setw(10) << "Курс"
        << setw(20) << "Спецiальнiсть"
        << setw(10) << "Фiзика"
        << setw(10) << "Математика"
        << setw(15) << "Програмування"
        << setw(15) << "Чисел. мет."
        << setw(10) << "Педагогiка" << endl;

    cout << string(110, '-') << endl;

    for (int i = 0; i < n; i++) {
        cout << left << setw(5) << (i + 1)
            << setw(15) << students[i].surname
            << setw(10) << students[i].course
            << setw(20) << getSpecializationName(students[i].spec)
            << setw(10) << students[i].physics
            << setw(10) << students[i].math;

        // Виведення третьої оцінки залежно від спеціальності
        if (students[i].spec == COMPUTER_SCIENCE) {
            cout << setw(15) << students[i].thirdGrade.programming
                << setw(15) << "-"
                << setw(10) << "-";
        }
        else if (students[i].spec == INFORMATICS) {
            cout << setw(15) << "-"
                << setw(15) << students[i].thirdGrade.numericalMethods
                << setw(10) << "-";
        }
        else {
            cout << setw(15) << "-"
                << setw(15) << "-"
                << setw(10) << students[i].thirdGrade.pedagogy;
        }
        cout << endl;
    }
}
double countExcellentGrades(const Student students[], int n) {
    double exellentCount = 0, percent;

    for (int i = 0; i < n; i++) {
        if (students[i].physics == 5
            && students[i].math == 5 &&
            ((students[i].spec == COMPUTER_SCIENCE && students[i].thirdGrade.programming == 5)|| (students[i].spec == INFORMATICS && students[i].thirdGrade.numericalMethods == 5)|| (students[i].spec != COMPUTER_SCIENCE && students[i].spec != INFORMATICS && students[i].thirdGrade.pedagogy == 5)))
            exellentCount++;
    }
    percent = exellentCount / n;
    return percent;
}

void Surnames(Student students[], int n) {

    for (int i = 0; i < n; i++) {
        if (students[i].physics == 5) {
            cout << students[i].surname << endl;
        }
    }
}


int main() {
    setlocale(LC_CTYPE, "ukr");
    int n;
    cout << "Введiть кiлькiсть студентiв: ";
    cin >> n;

    Student* students = new Student[n];

    createStudentsArray(students, n);


    cout << "\nТаблиця студентiв:\n";
    printStudentsTable(students, n);

    cout << "\nвiдсоток вiдмiнникiв: " << countExcellentGrades(students, n) * 100 << "%" << endl;
    cout << "Прiзвища студентiв, що отримали 5 з фiзики:" << endl;
    Surnames(students, n);


    delete[] students;
    return 0;
}