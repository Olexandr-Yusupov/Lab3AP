#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <bitset>
#include "pages.h"
struct page_table
{
 unsigned int vr_page;
 int flag;
 unsigned int phys_page;
};
vector<page_table> table;
void page_table_init()
{
 ifstream tbl("page_table.csv");
 string vr_page;
 string flag;
 string phys_page;
 unsigned int vp, pp;
 while(tbl.good())
 {
 getline(tbl, vr_page, ',');
 getline(tbl, flag, ',');
 getline(tbl, phys_page, '\n');
 vp = bitset<21>(vr_page).to_ulong();
 pp = bitset<5>(phys_page).to_ulong();
 table.push_back({vp, stoi(flag), pp});
 }
}
string aligment(string adr)
{
 if (adr.size()<4)
 {
 adr.insert(0, 4-adr.size(), '0');
 }
 return adr;
}
string find_page(string adr)
{
 stringstream ss;
 unsigned int vr_adr;
 unsigned int res;
 string rs;
 ss<<adr;
 ss>>hex>>vr_adr;
 unsigned int vp_num = vr_adr>>11;
 unsigned int offset = (vr_adr & 2047);
 for (int i=0; i<table.size(); i++)
 {
 if (table[i].vr_page == vp_num)
 {
 if (table[i].flag != 0)
 {
 res = table[i].phys_page<<11;
 res += offset;
 ss.clear();
 ss<<hex<<res;
 ss>>rs;
 return aligment(rs);
 }
 return "load_error";
 }
 }
 return "null";
}
