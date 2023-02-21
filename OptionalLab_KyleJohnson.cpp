#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> department_preferences = {
    {1, 5, 3, 2, 4},
    {1, 3, 4, 2, 5},
    {3, 4, 2, 5, 1},
    {3, 1, 2, 4, 5},
    {4, 3, 1, 2, 5}
}; 
vector<vector<int>> programmer_preferences = {
    {3, 1, 2, 5, 4},
    {4, 3, 1, 5, 2},
    {2, 5, 4, 1, 3},
    {4, 5, 2, 1, 3},
    {3, 2, 1, 5, 4}
};

vector<int> department_matched; // stores which programmer each department is matched to
vector<bool> programmer_matched; // stores whether a programmer is matched to a department or not

bool is_preferred_by_department(int programmer, int dept1, int dept2) {
    for (int i = 0; i < programmer_preferences[programmer].size(); i++) {
        int pref_dept = programmer_preferences[programmer][i];
        if (pref_dept == dept1) {
            return true;
        }
        if (pref_dept == dept2) {
            return false;
        }
    }
    return false;
}

void matching() {
    // Initialize all departments and programmers as unmatched
    department_matched.assign(department_preferences.size(), -1);
    programmer_matched.assign(programmer_preferences.size(), false);

    int free_count = department_preferences.size(); // Number of free departments

    while (free_count > 0) {
        // Find a free department
        int dept;
        for (dept = 0; dept < department_preferences.size(); dept++) {
            if (department_matched[dept] == -1) {
                break;
            }
        }

        // Find the first programmer in the department's preference list
        for (int i = 0; i < department_preferences[dept].size(); i++) {
            int programmer = department_preferences[dept][i] - 1; 
            if (!programmer_matched[programmer]) { 
                department_matched[dept] = programmer;
                programmer_matched[programmer] = true;
                free_count--;
                break;
            }
            else {
                int current_dept = -1;
                // Find the current department that the programmer is matched to
                for (int j = 0; j < department_matched.size(); j++) {
                    if (department_matched[j] == programmer) {
                        current_dept = j;
                        break;
                    }
                }
                // Check if the new department is preferred by the programmer over the current department
                if (is_preferred_by_department(programmer, dept+1, current_dept+1)) {
                    department_matched[dept] = programmer;
                    programmer_matched[programmer] = true;
                    department_matched[current_dept] = -1;
                    break;
                }
            }
        }
    }
}

int main() {
    matching();
    for (int i = 0; i < department_matched.size(); i++) {
        cout << "Department #" << i+1 << " will get Programmer #" << department_matched[i]+1 << endl;
    }
    return 0;
}