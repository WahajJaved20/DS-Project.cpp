#include "sha1.hpp"
#include <string>
#include<iostream>

using namespace std;
const string sha1func(const string input){
    SHA1 checksum;
    checksum.update(input);
    const string hash = checksum.final();
    return hash;
}
int main()
{
    string str;
    cout<<"Enter password: ";
    getline(cin, str);
    string hash = sha1func(str);
    
    cout << "The SHA-1 of \"" << str << "\" is: " << hash << endl;

    return 0;
}