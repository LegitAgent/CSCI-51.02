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

// function for incrementing letters
string increment_letters(string name){  
    int len = name.length();            // get length of name, put in variable 'len'
    char temp[len+1];                   // create char array 'temp' with len+1 spaces

    // for loop to increment each letter
    for(int i = 0; i < len; i++){
        char a = name[i];               // set a to be the ith char in name
        a++;                            // increment a (turns it to b)
        temp[i] = a;                    // set ith char in temp to be a
    }
    temp[len] = '\0';                   // adding null character at end of answer    
    string answer = temp;               // creating string object 'answer' with the chars of temp
    return answer;                      // return answer
}

int main(void) {
    string name;
    cin >> name;

    string increment = increment_letters(name);
    string hashed = hash_letters(name);
    cout << hashed << endl;
    cout << increment << endl;

    return 0;
}

