#include <iostream>
using namespace std;


// function for hashing letters
string hash_letters(string name) {
    int len = name.length();            // variable 'len' carries the length of 'name'
    char temp[len + 1];                 // create char array 'temp' with len+1 spaces
    temp[0] = name[0];                  // set first character of temp to be first char of name
    
    // for loop to increment each character, starting with 1 to preserve the first character
    for (int i = 1; i < len; i++) {
        temp[i] = '#';                  // set ith character in temp to be '#'
    }
    temp[len] = '\0';                   // adds a null character at the end of temp
    
    return string(temp);                // returns a string that was created from character array 'temp'
}

// #4: function for incrementing letters
string increment_letters(string name){  
    int len = name.length();            // get length of name, put in variable 'len'
    char temp[len+1];                   // create char array 'temp' with len+1 spaces

    // for loop to increment each letter
    for(int i = 0; i < len; i++){       // loops len times
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

