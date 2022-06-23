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
 const string USERS = "Data//USERS INFORMATIONS//users.csv";
 const string ADMIN = "Data//USERS INFORMATIONS//admins.csv";
 const string links[] = { "DA.json", "DB.json", "DC.json", "DD.json" , "DE.json", "DF.json", "DG.json",
						"DH.json", "DI.json", "DJ.json", "DK.json", "DL.json", "DM.json", "DN.json", "DO.json", "DP.json",
								"DQ.json", "DR.json", "DS.json", "DT.json", "DU.json", "DV.json", "DW.json", "DX.json", "DY.json", "DZ.json" }; //26 elements
 const string JSONPATH = "Data//ENGLISH DEFINITIONS//";
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

struct SearchBar;

struct LeftRight;

struct Node
{
	//English-Vietnamese
	vector<string> def;

	//English-English
	string word;
	vector<pair<pair<string, string>, vector<string>>> definitions;
	vector<string> examples;
	vector<string> antonyms;
	vector<string> synonyms;

	//For recommendations
	double freq;

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
	Trie envie_Trie;
	Trie def_envie_Trie;
	Trie enen_Trie;
	Trie def_enen_Trie;
	vector<Trie> user_Trie;

	vector<string> favorite;
	vector<string> history;
};