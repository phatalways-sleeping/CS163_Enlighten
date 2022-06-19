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
using std::string;
using namespace sf;
using namespace std;

const int FAVORITE_LIST = 2;
const int SEARCH_HISTORY = 1;
const string USERS = "Data//USERS INFORMATIONS//users.csv";
const string ADMIN = "Data//USERS INFORMATIONS//admins.csv";

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