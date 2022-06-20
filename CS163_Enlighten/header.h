#pragma once

#include "struct_and_dependencies.h"

//------------------Login Functions---------------------
bool login(string username, string password, string path, vector<string> &search_history, vector<string> &favorite_list);
void changePassword(string username, string new_pass, string path);
bool createNewAccount(string username, string password, string path);
void update(string username, int CASE, vector<string>& list, string path);

//------------------Trie for English Definitions-----------
void clear(MEANINGS& m);
MEANINGS* search(AVD_TRIE T, string word);
bool insert(AVD_TRIE& T, string word, const MEANINGS& current);
bool remove(AVD_TRIE& T, string word);
void convert(json data, AVD_TRIE& root);

//--------------Autocomplete Word Functions-------------
void fillCompleteList(Node* cur, string word, vector<string>& completeList, int limit);
vector<string> autocomplete(Trie T, string word, int limit);

//-------------------Objects/Text to draw---------------
Object createObject(string s, float x, float y);
Object *createObjectTest(string s, float x, float y);
Object createObject(string s);
Object *createObjectTest(string s);
Info createInfo(string s, float x, float y, unsigned int size);
Info createInfo(string s, string info, float x, float y, unsigned int size);
Info *createInfoTest(string s, string info, float x, float y, unsigned int size);
pair<Object *, Object *> createElement(string s, float x, float y);
Confirmation create();
Confirmation create(string b1, string o1, string o2, string o3);
void deallocate(Confirmation& p);
void deallocate(SearchBar& p);
void deallocate(pair<Object *, Object *> &p);
//-------------------Features--------------------------
bool isHere(FloatRect &bound, Vector2f &mouse);
bool isHere(const pair<Object *, Object *> &a, Vector2f &mouse);
bool drawWhich(RenderWindow &window, const pair<Object *, Object *> &a, Vector2f &mouse);
bool drawWhich(RenderWindow &window, Object a, Object b, Vector2f &mouse);
bool drawWhich(RenderWindow &window, Object *a, Object *b, Vector2f &mouse);
bool switchPage(FloatRect &bound, Vector2f &mouse, int k, int &page);
void changePos(Object *a, Object *b, float x, float y);
void changePos(Object *a, float x, float y);
void changePos(Info *a, float x, float y);
void texting(Info &text, Uint32 unicode, unsigned int limit);
void texting(Info *&text, Uint32 unicode, unsigned int limit);
void checkConfirmation(RenderWindow& window, int& check, const Confirmation& element, Vector2f& mouse);
void searching(RenderWindow& window, int& status, const SearchBar& s, Vector2f& mouse, int& add_status);
//---------------------Scene--------------------------
void Scene1(RenderWindow &window, int &page);
void setRole(RenderWindow &window, int &page, bool &is_admin);
void logIn(RenderWindow &window, int &page, bool is_admin);
void home(RenderWindow &window, int &page, bool &is_admin);
void wordDisplay(RenderWindow &window, int &page, const bool &is_admin);
void myList(RenderWindow &window, int &page, bool is_fav);
void revision(RenderWindow &window, int &page);
void settings(RenderWindow& window, int& page, const bool& is_admin);


//------------------Struct(cont)-------------------------
struct SearchBar
{
	Info* search_info = createInfoTest("Graphic/Oswald-Regular.ttf", "search", 393.0f, 36.0f, 20);
	Object board = createObject("Graphic/p0_board.png", 330.0f, 22.0f);
	pair<Object*, Object*> change = createElement("switch", 810.0f, 26.0f);
	pair<Object*, Object*> search = createElement("search_bar", 360.0f, 26.0f);
	pair<Object*, Object*> add = createElement("add", 308.0f, 26.0f);
	pair<Object*, Object*> search_history = createElement("p4_sh", 658.0f, 211.0f);
	Confirmation new_word = create("p0_nw", "p0_cancel", "p0_ok", "p0_return");
	Info enter_word = createInfo("Graphic/Oswald-Light.ttf", "Enter word", 345.0f, 330.0f, 30);
	Info enter_defi = createInfo("Graphic/Oswald-Light.ttf", "Enter definition", 345.0f, 412.0f, 30);
	SearchBar()
	{
		changePos(add.second, 260.0f, 26.0f);
	}
};