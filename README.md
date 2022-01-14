

 
 
#PROJECT REPORT

CS2001- Data Structures
Semester Project

Group Members:
Muhammad Hatif Mujahid(20K-0218)
Wahaj Javed Alam (20K-0208)
Minhal Irfan (20K-0316)
Section : BCS-3E

Submitted to: Dr. Ali raza

Department of Computer Science BS(CS)
FAST-NUCES Karachi

INTRODUCTION 
Pwned Passwords are 517,238,891 real world passwords previously exposed in data breaches. This exposure makes them unsuitable for ongoing use as they're at much greater risk of being used to take over other accounts. They're searchable online below as well as being downloadable for use in other online systems.
The entire set of passwords is downloadable for free  with each password being represented as a SHA-1 hash to protect the original value (some passwords contain personally identifiable information) followed by a count of how many times that password had been seen in the source data.
HYPOTHESIS 
The security of an account is critical to the successful operation of a system. The following data collection contains passwords along with the number of times they were encountered in common data breaches, making them potentially dangerous. As a result, our project examines the dataset in real time and notifies the user about the password's security.
MATERIALS
Visual studio Code
Github
Pwned password dataset 
Mingw GNU compiler (very imp)
Functions
loading _screen_start()
loading_screen_search()
createFileNames()
startFromStart(string F_name)
startFromHalf(string F_name)
createTree(string name)
searchFile(vector<string> fileNames, string data)
sha1func(const string input)
searching(string hash)
searching(string hash)
searchResults(string hash)
PROCEDURE
Downloaded the dataset from url. 
The 25GB dataset was too big to handle so we parsed the data using python.
Data was parsed into 10000000 lines and 48 files. In total the dataset is now 19.6gb.
After parsing the file, to improve file reading we implemented threading to achieve optimal file reading time and divided our file into two AVL trees to reduce balancing time complexity.
SInce the dataset is sorted:	
We have read and stored the first lines of every file.
Then a function decides which file to choose based on the hash value by simple comparison technique.
We decided on making an AVL which is a self-balancing tree. This has reduced the search time from seconds to microseconds.
The menu driven program ensures readability of the program.
FEATURES
Multithreading
Sha-1 encryption
AVL tree searching 
Shows the pwned passwords as well the number of times they have been detected.
It is easily adaptable to any other program. We can use any banking system etc where the user has to choose passwords to sign up.
Data parsing using python.
RESULTS
Time achieved: 24 seconds on average for file reading, 0.000045 seconds average for searching value.
REFERENCES
Multithreading in C++ - GeeksforGeeks 
Pwned Passwords 
