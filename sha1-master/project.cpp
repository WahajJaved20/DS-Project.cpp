#include "sha1.hpp"
#include <string>
#include<iostream>

using namespace std;
int main()
{
    string str;
    cout<<"Enter password: ";
    getline(cin, str);

    SHA1 checksum;
    checksum.update(str);
    const string hash = checksum.final();

    cout << "The SHA-1 of \"" << str << "\" is: " << hash << endl;

    return 0;
}