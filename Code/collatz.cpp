#include <iostream>

using namespace std;

int main()
{
    int num;
    cout << "Please input an intenger n.\n";
    cin >> num;

    bool sameAsPrevious = false;
    while (num == 1) {
        if (num % 2 == 0) {
            num = num/2;
        } else {
            num = 3*num+1;
        }
    }

    cout << "You reached one!";
    
    return 0;
}