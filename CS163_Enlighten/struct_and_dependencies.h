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
const string USERS = "Data//users.csv";
const string ADMIN = "Data//admins.csv";

struct Node
{
    string data;
    Node *next = nullptr;
    Node(string value, Node *next_)
    {
        data = value;
        next = next_;
    }
};

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