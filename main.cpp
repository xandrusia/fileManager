#include <iostream>
#include <filesystem>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <string>
#include <list>
#include "menu.h"
#include <fstream>


using namespace std;
namespace fs = std::filesystem;

enum choice
{
    deleteTheFile = 1,
    createAFile = 2,
    fileContent = 3
};

struct basicInfo
{
    string nameOfApp;
    string greeting;

    showInfo()
    {
         cout<<greeting<<endl;
         cout<<nameOfApp<<endl;
    }

};
    //storage = stores directories
    vector <fs::path> storage;
    //fileStorage = stores files
    vector <fs :: path> fileStorage;
    int j=0;


void listDirectory( fs:: path userPath ) {

    for (auto file : fs::directory_iterator(userPath)) {

        if (fs::is_directory(file)== 1) {
                cout << j << ": "<< file << endl;
                storage.push_back(file);
                j++;
            listDirectory(file);

        }
        else {
            cout << file<<endl;
        }
    }
}

void showDirectory ()
{

       fs::path myPath("C:\\Users\\sandr\\Desktop\\bzdety");

   cout<<"your path is : " << myPath<<endl;
   cout<<"name of this directory is : "<< myPath.filename()<<endl;
   cout<<"Address of our path : "<<&myPath<<endl;                                           //extracting the name of directory
   //cout<<fs::is_directory(myPath)<<endl;                                                 //tells us if is it a file or directory, 1- a directory
   cout<<"extracted extension is : "<<myPath.extension()<<endl;                                                      //extracting the extension of my file, what the file contains
   cout<<"we are on disc : " <<myPath.root_name()<<endl;                               //extracting the disc on which I'm working on
   cout<<"this is my path to parent dir : " <<myPath.parent_path()<<endl;             //path to my parent

   cout<<"listing files in current directory : "<<endl;
   cout << j << ": "<< myPath << endl;
    storage.push_back(myPath);
    j++;

    listDirectory(myPath);
}

void dir (int inputs)
{
    int x = 0;
    for (auto file : fs::directory_iterator(storage[inputs])) {

                cout << x << "= "<< file << endl;
                fileStorage.push_back(file);
               x++;
    }
}


void deleteFile(int fileNo)
{
remove(fileStorage[fileNo]);
cout<<"file deleted"<<endl;
}

int userInput()
{
    cout << "choose file Number " << endl;
    int fileNoo;
    cin >> fileNoo;

    return fileNoo;
}

void createFile(int dirNoo)
{
    string name;
     fs::path  fullPath;
    cout << "what do you want to name this file" << endl;
    cin>>name;
    name = name +".txt";
    fullPath = storage[dirNoo]/name;

    ofstream file(fullPath);
    cout<<"file created" << endl;
}

void seeContent(int fileNo)
{
ifstream file(fileStorage[fileNo]);
if (file.is_open())
{
cout<<"Here is the content of a file : "<<endl;
cout<<file.rdbuf()<<endl;
file.close();

} else cout << "file did not open properly" << endl;
}


int main()

{
menu pass;
pass.password();

//belongs to struct
    basicInfo myApp;
    myApp.greeting = "Welcome to my file handler, program which lists and change directories";
    myApp.nameOfApp = "Sandra's file handler";
    myApp.showInfo();

   showDirectory();

cout<<"What is the number of the directory you want to change?"<< endl;
int dirNo;
cin>>dirNo;
dir(dirNo);


pass.menuStart();

int input;
cin>>input;

switch(input)
{
case deleteTheFile:
    deleteFile(userInput());
    break;
case createAFile:
    createFile(dirNo);
    break;
case fileContent:
    seeContent(userInput());
    break;
default:
    cout<<"No such option in menu"<<endl;
}

 return 0;

}
