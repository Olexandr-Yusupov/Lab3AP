#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include <bitset>
#include "analize.h"
#include "pages.h"
#include "test_module.h"
using namespace std;
void test1()
{
 string test = "1A 0c 0f\n0D 0f 0d 02 38 68 03\n1B 0f FF FF EE EE\n23 0f 0d 00 
00 28 03\n80 02 0f";
 vector<string> words = read_words(test);
 printf("\nString[1]:\n");
 cout<<test<<endl;
 printf("\n");
 code_analize(words);
}
void test2()
{
 string test = "1A 0c 0f 0D 0f 0d 02 38 68 03 1B 0f DD FC\nEE 0E 23 0f 0d 00 00 
28 03 80\n02 0f";
 vector<string> words = read_words(test);
 printf("\nString[2]:\n");
 cout<<test<<endl;
 printf("\n");
 code_analize(words);
}
void test3()
{
 string test = "1A 0c 0f\n0D 0f 0d 02 38 68 03\n1B 0f 00 00 08 03\n23 0f 0d 00 
00 68 03\n80 02 0f";
 vector<string> words = read_words(test);
 printf("\nString[3]:\n");
 cout<<test<<endl;
 printf("\n");
 code_analize(words);
}
void read_form_file()
{
 ifstream infile("input.txt");
 string line;
 vector<string> words;
 printf("\n\nReading from file:\n------------------\n");
 while (getline(infile, line))
 {
 words.clear();
 words = read_words(line);
 code_analize(words);
 }
}
void menu()
{
 bool exit_flag = false;
 int choice;
 page_table_init();
 while (exit_flag == false)
 {
 printf("---MENU---\n");
 printf("1 - read from file\n2 - read from str1\n3 - read from str2\n4 - 
read from str3\n0 - exit\n\nenter: ");
 cin>>choice;
 switch(choice)
 {
 case 1:
 read_form_file();
 break;
 case 2:
 test1();
 break;
 case 3:
 test2();
 break;
 case 4:
 test3();
 break;
 case 0:
 exit_flag = true;
 break;
 default:
 exit_flag = true;
 break;
 }
 }
}