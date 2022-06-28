#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <vector>
#include <utility>
#include <time.h>
#include <map>
#include <queue>
#include<direct.h>
#include<filesystem>
#include <string.h>
#include"JSON/json-develop/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
using namespace sf;
using namespace std;

const int FAVORITE_LIST = 2;
const int SEARCH_HISTORY = 1;
const string original_data_path = "ENLIGHTEN_DATA//ORIGINAL_DATA";
const string use_data = "ENLIGHTEN_DATA//DATA";
const string USERS = "ENLIGHTEN_DATA//USERS_INFORMATIONS//users.csv";
const string ADMIN = "ENLIGHTEN_DATA//USERS_INFORMATIONS//admins.csv";
const string JSONPATH = "ENLIGHTEN_DATA//DATA//ENGLISH_DEFINITIONS//English_Definitions.json";
const string USEJSONPATH = "ENLIGHTEN_DATA//DATA//ENGLISH_DEFINITIONS//English_Definitions.json"; // Use this to test the user definitions
const double TOTAL = 5.88124e+11;

const int TRIE_LIMIT = 95;
const int DEC = 32;

enum Status{ResetDict = 1, ResetAllDict = 2, ChangePw = 3, ChangeData = 4, ImportNew = 5, RemDict = 6};

struct Object
{
	Sprite draw;
	Texture txt;
	FloatRect bound;
};

struct Info
{
	Font font;
	Text text;
	FloatRect bound;
	bool check = false;
	string s = "";
};

struct Confirmation;

struct Vocabulary;

struct SearchBar;

struct LeftRight;

struct Dictionary;

struct UserDef {
	string username;
	string definition;
	int like;
	int dislike;
	vector<pair<string, bool>> list;
	UserDef() {}
	
	UserDef(string __username, string __definition, int __like, int __dislike, vector <pair<string, bool>> __list) {
		username = __username;
		definition = __definition;
		like = __like;
		dislike = __dislike;
		list = __list;
	}
	UserDef(string __username, string __definition){
		username = __username;
		definition = __definition;
		like = 0;
		dislike = 0;
		list.clear();
	}
};

struct Node
{
	//English-Vietnamese
	vector<string> def;

	//English-English
	string word;
	vector<pair<pair<string, string>, vector<string>>> definitions; // { { kind_of_word , definition } , examples }
	vector<UserDef> user_definitions;
	vector<string> antonyms;
	vector<string> synonyms;
	
	//For recommendations
	double freq = 0;

	Node *child[TRIE_LIMIT];
	Node()
	{
		for (int i = 0; i < TRIE_LIMIT; i++)
			child[i] = NULL;
	}
};

struct Edit;

struct Trie
{
	Node *root = new Node();
};

struct Enlighten
{
	// 0. Trie envie_Trie;
	// 1. Trie def_envie_Trie;
	// 2. Trie enen_Trie;
	// 3. Trie def_enen_Trie;
	int cur_id;
	string username;
	bool is_admin;
	vector<Trie> user_Trie;
	vector<string> favorite;
	vector<string> history;
	vector<string> dictionary_name;

	Enlighten() {
		is_admin = false;
		cur_id = 0;
		user_Trie.clear();
	}
};

struct AdminButton;