#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string.h>
#include <string>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <vector>
#include"JSON/json-develop/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
using std::string;
using namespace sf;
using namespace std;

const int FAVORITE_LIST = 2;
const int SEARCH_HISTORY = 1;
const string USERS = "Data//USERS INFORMATIONS//users.csv";
const string ADMIN = "Data//USERS INFORMATIONS//admins.csv";
string links[] = { "DA.json", "DB.json", "DC.json", "DD.json" , "DE.json", "DF.json", "DG.json",
						"DH.json", "DI.json", "DJ.json", "DK.json", "DL.json", "DM.json", "DN.json", "DO.json", "DP.json",
									"DQ.json", "DR.json", "DS.json", "DT.json", "DU.json", "DV.json", "DW.json", "DX.json", "DY.json", "DZ.json" }; //26 elements
const string JSONPATH = "Data//ENGLISH DEFINITIONS//";
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

struct Node 
{
	vector <string> def;
	Node* child[256];
	Node() {
		for (int i = 0; i < 256; i++) child[i] = NULL;
	}
};

struct Trie 
{
	Node* root = new Node();
};

struct MEANINGS {
	string word;
	vector<pair<pair<string, string>, vector<string>>> definitions;
	vector<string> examples;
	vector<string> antonyms;
	vector<string> synonyms;
	MEANINGS* child[256];
	MEANINGS() { for (int i = 0; i < 256; i++) child[i] = nullptr; }
};

struct TRIE {
	MEANINGS* root = new MEANINGS();
};