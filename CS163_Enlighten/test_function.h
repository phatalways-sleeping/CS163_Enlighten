#pragma once
#include <string>


const int special_value = 1;
const string dict_name_path = "ENLIGHTEN_DATA/DATA/DATASETSNAMES.TXT";
vector <pair<string, bool>> nullvector();
int likeStatus(string user, vector <pair<string, bool>> list, int& cur_id);
bool like_compare(UserDef x, UserDef y);

string cutWordtype(string x);
string cutDefinition(string x);

