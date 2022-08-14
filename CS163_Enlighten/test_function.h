#pragma once
#include <string>


const int special_value = 2;
const string dict_name_path = "ENLIGHTEN_DATA/DATA/DICTIONARY.TXT";
const string origin_dict_name_path = "ENLIGHTEN_DATA/ORIGINAL_DATA/DICTIONARY.TXT";
vector <pair<string, bool>> nullvector();
int likeStatus(string user, vector <pair<string, bool>> list, int& cur_id);
bool like_compare(UserDef x, UserDef y);

string cutWordtype(string x);
string cutDefinition(string x);

bool visitAllNode(Node* root, vector <pair<string, string>>& word_def);

bool build_definition_trie(Trie& T_def, Trie T);