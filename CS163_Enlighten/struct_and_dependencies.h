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
/*
#include "DataStructure/demo.h"
#include "DataStructure/clock.h"
#include "DataStructure/trie.h"
#include "DataStructure/trie_autocorrect.h"
#include "DataStructure/trie_definition.h"
*/
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
 const string JSONPATH = "ENLIGHTEN_DATA//ORIGINAL_DATA//ENGLISH_DEFINITIONS//English_Definitions.json";
 const double TOTAL = 5.88124e+11;

 
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

struct Confirmation
{
	pair<Object *, Object *> board;
	pair<Object *, Object *> nah;
	pair<Object *, Object *> of_course;
	pair<Object *, Object *> out;
};

struct Vocabulary;

struct SearchBar;

struct LeftRight;

struct Dictionary;

struct Node
{
	//English-Vietnamese
	vector<string> def;

	//English-English
	string word;
	vector<pair<pair<string, string>, vector<string>>> definitions; // { { kind_of_word , definition } , examples }
	vector<pair<string, string>> user_definitions;  // { username, definition }
	vector<string> antonyms;
	vector<string> synonyms;

	//For recommendations
	double freq = 0;

	Node *child[256];
	Node()
	{
		for (int i = 0; i < 256; i++)
			child[i] = NULL;
	}
};

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