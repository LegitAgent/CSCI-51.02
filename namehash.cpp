#include <iostream>                     // include iostream header file
using namespace std;


// #3: function for hashing letters
string hash_letters(string name) {      // function with string parameter that returns a string
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
string increment_letters(string name){  // function with string parameter that returns a string
    int len = name.length();            // get length of name, put in variable 'len'
    char temp[len+1];                   // create char array 'temp' with len+1 spaces

    // for loop to increment each letter
    for(int i = 0; i < len; i++){       // loops len times
        bool is_not_letter;             // bool to store if character is a letter
        char a = name[i];
        is_not_letter = (a < 65 || (a > 90 && a < 97)); // these values are the non-letters in cpp ASCII

        if(is_not_letter){              // if 'a' is not a letter
            temp[i] = a;                // set temp at ith position to a (not changing anything)
            continue;                   // continue to next loop
        }
        if(a == 90 || a == 122){        // if a is 90 (Z) or 122 (z)
            a -= 26;                    // decrement by 26 (turns into character before a/A)
        }
        a++;                            // increment by 1 ()
        temp[i] = a;                    // set ith char in temp to be a
    }
    temp[len] = '\0';                   // adding null character at end of temp    
    string answer = temp;               // creating string object 'answer' with the chars of temp
    return answer;                      // return answer
}

// #5: function for incrementing letters, pointer manipulation
char hash_letter_pointer(char *p) {     // function with char pointer parameter that returns a char
    char character = *p;                // dereference the pointer p into its character form
    int ascii = int(character);         // turn the character to its ascii format
    if(ascii == 122 || ascii == 90) {   // if the ascii is a 'z' or 'Z' 
        ascii -= 25;                    // then - 25 to turn it into an 'a' or 'A'
    } else if((ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122)) {  // if it is any other letter
        ascii++;                        // increment by 1
    }
    return char(ascii);                 // return the ascii into its character form
}

// main function
int main(void) {
    string name;                        // create string object 'name'
    cin >> name;                        // set name to user's input in console
    cout << name << endl;               // output value of name to console

    string increment = increment_letters(name);         // 'increment' holds name replaced with next letter
    string hashed = hash_letters(name);                 // 'hashed' holds name replaced with # after first letter
    
    // implementation of pointer based function seen in specs
    for (int i = 0; i < name.length(); i++) {
        char edited = hash_letter_pointer(&name[i]);    // char edited holds next letter of value held at name[i]'s address 
        name[i] = edited;               // set ith letter of name to next letter
    }
    cout << hashed << endl;             // output value of hashed to console
    cout << increment << endl;          // output value of increment to console
    cout << name << endl;               // output new value of name to console

    return 0;                           // here for good practice
}
