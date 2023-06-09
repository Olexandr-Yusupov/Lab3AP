#include <iostream>
#include <stdio.h>
#include <sstream>
#include <bitset>
#include "analize.h"
#include "pages.h"
using namespace std;
string error_ = "none";
vector<string> read_words(string line)
{
 int i;
 vector<string> words;
 string word = "";
 bool word_start = false;
 for (i=0; i<line.size(); i++)
 {
 if (word_start == false && line[i] != ' ' && line[i] != ',' && line[i] !=
'\0' && line[i] != '\n')
 {
 word_start = true;
 }
 if (word_start == true)
 {
 if ( line[i] == ' ' || line[i] == ',' || line[i] == '\0' || line[i] ==
'\n')
 {
 words.push_back(word);
 word.clear();
 word_start = false;
 }
 else
 {
 word += line[i];
 }
 }
 }
 if (word != "")
 {
 words.push_back(word);
 }
 return words;
}
void del_test (vector<string> *vec, int k)
{
 for (int i=0; i<vec->size() - k; i++)
 {
 (*vec)[i] = (*vec)[i+k];
 }
 for (int i=0; i<k; i++)
 vec->pop_back();
}
void print_code(vector<string> *vec, int k)
{
 for (int i=0; i<k; i++)
 {
 cout<<(*vec)[i]<<" ";
 }
 cout<<endl;
}
int hex_to_int(string hex_n = "null", char chr = 'n')
{
 int num;
 stringstream ss;
 if (chr == 'n')
 {
 ss<<hex_n;
 ss>>hex>>num;
 }
 else
 {
 ss<<chr;
 ss>>hex>>num;
 }
 //cout<<"NUM: "<<num<<"; hex: "<<chr<<endl;
 return num;
}
string convert_adr(string adr)
{
 string phys_adr;
 phys_adr = find_page(adr);
 if (phys_adr != "null" && phys_adr != "load_error")
 {
 return phys_adr;
 }
 error_ = phys_adr;
 return adr;
}
void print_error()
{
 if (error_ == "null")
 cout<<"failed to convert adress: there is no such page in the table"<<endl;
 else if (error_ == "load_error")
 cout<<"failed to convert adress: current page isn't loaded to physical 
memory"<<endl;
 error_ = "none";
}
int mov_analizer(vector<string> *word)
{
 string res = "MOV ";
 string adr = "";
 int del_num = 0;
 if ((*word)[0] == "1A")
 {
 res += "R";
 res += to_string(hex_to_int("null", (*word)[1][1]));
 res += ", ";
 res += "R";
 res += to_string(hex_to_int("null", (*word)[2][1]));
 del_num = 3;
 }
 else if ((*word)[0] == "1B")
 {
 res += "[0x";
 for (int i=2; i<6; i++)
 {
 adr += (*word)[i];
 }
 adr = convert_adr(adr);
 res += adr;
 res += "], ";
 res += "R";
 res += to_string(hex_to_int("null", (*word)[1][1]));
 del_num = 6;
 }
 else if ((*word)[0] == "1C")
 {
 if ((*word)[1][0] == '0')
 {
 res += "R";
 res += to_string(hex_to_int("null", (*word)[1][1]));
 res += ", ";
 res += to_string(hex_to_int((*word)[2]));
 del_num = 3;
 }
 else if ((*word)[1][0] == '1')
 {
 res += "R";
 res += to_string(hex_to_int("null", (*word)[1][1]));
 res += ", ";
 res += to_string(hex_to_int((*word)[2] + (*word)[3]));
 del_num = 4;
 }
 else
 {
 cout<<"error: unknown code\n"<<endl;
 return 0;
 }
 }
 print_code(word, del_num);
 del_test(word, del_num);
 cout<<res<<endl;
 print_error();
 return 1;
}
int sub_analizer(vector<string> *word)
{
 string res = "SUB ";
 string adr = "";
 int del_num = 0;
 if ((*word)[0] == "0C")
 {
 if ((*word)[1][0] != '0')
 {
 cout<<"error: syntax error \n"<<endl;
 return 0;
 }
 res += "R";
 res += to_string(hex_to_int("null", (*word)[1][1]));
 res += ", ";
 res += "R";
 res += to_string(hex_to_int("null", (*word)[2][1]));
 res += ", ";
 res += "R";
 res += to_string(hex_to_int("null", (*word)[3][1]));
 del_num = 4;
 }
 else if ((*word)[0] == "0D")
 {
 res += "R";
 res += to_string(hex_to_int("null", (*word)[1][1]));
 res += ", ";
 res += "R";
 res += to_string(hex_to_int("null", (*word)[2][1]));
 res += ", ";
 res += "[0x";
 for (int i=3; i<7; i++)
 {
 adr += (*word)[i];
 }
 res += convert_adr(adr);
 res += "]";
 del_num = 7;
 }
 print_code(word, del_num);
 del_test(word, del_num);
 cout<<res<<endl;
 print_error();
 return 1;
}
int mul_analizer(vector<string> *word)
{
 string res = "MUL ";
 string adr = "";
 int del_num;
 if ((*word)[0] == "21")
 {
 if ((*word)[1][0] != '0')
 {
 cout<<"error: unknown code\n"<<endl;
 return 0;
 }
 res += "R";
 res += to_string(hex_to_int("null", (*word)[1][1]));
 res += ", ";
 res += "R";
 res += to_string(hex_to_int("null", (*word)[2][1]));
 res += ", ";
 res += "R";
 res += to_string(hex_to_int("null", (*word)[3][1]));
 del_num = 4;
 }
 if ((*word)[0] == "23")
 {
 res += "R";
 res += to_string(hex_to_int("null", (*word)[1][1]));
 res += ", ";
 res += "R";
 res += to_string(hex_to_int("null", (*word)[2][1]));
 res += ", ";
 res += "[0x";
 for (int i=3; i<7; i++)
 {
 adr += (*word)[i];
 }
 res += convert_adr(adr);
 res += "]";
 del_num = 7;
 }
 print_code(word, del_num);
 del_test(word, del_num);
 cout<<res<<endl;
 print_error();
 return 1;
}
int cmp_analizer(vector<string> *word)
{
 string res = "CMP ";
 string adr = "";
 int del_num;
 res += "R";
 res += to_string(hex_to_int("null", (*word)[1][1]));
 res += ", ";
 res += "R";
 res += to_string(hex_to_int("null", (*word)[1][1]));
 del_num = 3;
 print_code(word, del_num);
 del_test(word, del_num);
 cout<<res<<endl;
 return 1;
}
void code_analize(vector<string> word)
{
 while(word.size() != 0)
 {
 if (word[0] == "1A" || word[0] == "1B" || word[0] == "1C")
 {
 if (mov_analizer(&word) == 0)
 break;
 printf("\n");
 }
 else if (word[0] == "0C" || word[0] == "0D")
 {
 if (sub_analizer(&word) == 0)
 break;
 printf("\n");
 }
 else if (word[0] == "21" || word[0] == "23")
 {
 if (mul_analizer(&word) == 0)
 break;
 printf("\n");
 }
 else if (word[0] == "80")
 {
 if (cmp_analizer(&word) == 0)
 break;
 printf("\n");
 }
 else
 {
 cout<<"syntax error"<<endl;
 break;
 }
 }
}
