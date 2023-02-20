#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    // Department preferences
    vector<vector<int>> department_preferences = {
        {1, 5, 3, 2, 4},
        {1, 3, 4, 2, 5},
        {3, 4, 2, 5, 1},
        {3, 1, 2, 4, 5},
        {4, 3, 1, 2, 5}
    };
    
    // Programmer preferences
    vector<vector<int>> programmer_preferences = {
        {3, 1, 2, 5, 4},
        {4, 3, 1, 5, 2},
        {2, 5, 4, 1, 3},
        {4, 5, 2, 1, 3},
        {3, 2, 1, 5, 4}
    };

    int n = department_preferences.size(); // number of departments and programmers

    vector<int> department_match(n, -1); // department i is matched to programmer department_match[i]
    vector<int> programmer_match(n, -1); // programmer i is matched to department programmer_match[i]

    queue<int> free_departments; // queue of departments that haven't yet found a programmer

    for (int i = 0; i < n; i++) {
        free_departments.push(i);
    }

    while (!free_departments.empty()) {
        int department = free_departments.front();
        free_departments.pop();
        for (int j = 0; j < n; j++) {
            int programmer = department_preferences[department][j] - 1; // programmer preference index starts from 1, subtract 1 to get the actual index
            if (programmer_match[programmer] == -1) { // programmer is free
                department_match[department] = programmer;
                programmer_match[programmer] = department;
                break;
            } else { // programmer is already matched with another department
                int current_department = programmer_match[programmer];
                int current_preference = 0, new_preference = 0;
                for (int k = 0; k < n; k++) {
                    if (programmer_preferences[programmer][k] == department) {
                        new_preference = k;
                    }
                    if (programmer_preferences[programmer][k] == current_department) {
                        current_preference = k;
                    }
                }
                if (new_preference < current_preference) { // programmer prefers new department
                    department_match[department] = programmer;
                    programmer_match[programmer] = department;
                    free_departments.push(current_department);
                    break;
                }
            }
        }
    }

    // print results
    for (int i = 0; i < n; i++) {
        cout << "Department #" << i+1 << " will get Programmer #" << department_match[i]+1 << endl;
    }

    return 0;
}
