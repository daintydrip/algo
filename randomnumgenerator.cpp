#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    int n;
    cout << "Enter the number of random numbers to generate: ";
    cin >> n;

    cout << "Random numbers: ";
    for (int i = 0; i < n; ++i) {
        int random_number = rand() % 999 + 1;
        cout << random_number << " ";
    }
    cout << endl;

    return 0;
}
