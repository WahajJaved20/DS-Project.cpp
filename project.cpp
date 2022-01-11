#include "sha1.hpp"
#include <string>
#include<ctype.h>
#include<iostream>

using namespace std;
const string sha1func(const string input){
    SHA1 checksum;
    checksum.update(input);
    string hash = checksum.final();
    for (int i = 0; i < hash.size(); i++)
    {
        if(isalpha(hash[i])){
            hash[i]-=32;
        }
    }
    return hash;
}
int main()
{
    string str;
    cout<<"Enter password: ";
    getline(cin, str);
    string hash = sha1func(str);
    cout << "The SHA-1 of " << str << " is: " << hash << endl;

    return 0;
}