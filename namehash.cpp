#include <iostream>
using namespace std;

string hash_letters(string name) {
    int len = name.length();
    char temp[len + 1];
    temp[0] = name[0];

    for (int i = 1; i < len; i++) {
        char a = '#';
        temp[i] = a;
    }
    temp[len] = '\0';
    
    return string(temp);
}

int main(void) {
    string name;
    cin >> name;

    string hashed = hash_letters(name);
    cout <<hashed << endl;

    return 0;
}