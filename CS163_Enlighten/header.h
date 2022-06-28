#pragma once

#include "struct_and_dependencies.h"

//------------------Functions with Data--------------------------
void duplicateOriginalData(const string original_data_path, const string use_data);
bool deallocateDuplicatedData(const string use_data);
bool removeDatasets(string source);
bool resetCurrentDataset(string path, string name, string original_path);
bool addNewDataSets(string path, string destination);
bool addToUseData(string path, string destination);
string upper(string s);
//------------------Login Functions---------------------
bool login(string username, string password, string path, vector<string> &search_history, vector<string> &favorite_list);
bool changePassword(string username, string old_pass, string new_pass,string path);
bool createNewAccount(string username, string password, string path);
void update(string username, int CASE, vector<string> &list, string path);
void modify_csv(string username, int CASE, vector<string>& list, string path);

//------------------Trie for English Definitions-----------
void clear(Node &m);
bool insert(Trie &T, string word, const Node &current);
bool remove_eng(Trie &T, string word);
void convert(json data, Trie &root);
void convert(Node *T, vector<Node> &v);
bool edit_eng(Trie &T, string word, string kind_word, string new_definition);
json writeToJSON(Node* root);
bool writeJson(const Trie& T, string path);
bool readJson(Trie& T, string path);
string normalize(string s);

//--------------Autocomplete Word Functions-------------
void fillCompleteList(Node *cur, string word, vector<string> &completeList, int limit);
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
Confirmation create(string b1, string o1, string o2, string o3, int x);
void deallocate(Confirmation &p);
void deallocate(SearchBar &p);
void deallocate(pair<Object *, Object *> &p);

//-------------------Features--------------------------
bool isHere(FloatRect &bound, Vector2f &mouse);
bool isHere(const pair<Object *, Object *> &a, Vector2f &mouse);
bool isHere(const Object*& a, Vector2f& mouse);
bool isHere(Object* a, Vector2f& mouse);
bool drawWhich(RenderWindow &window, const pair<Object *, Object *> &a, Vector2f &mouse);
bool drawWhich(RenderWindow &window, Object a, Object b, Vector2f &mouse);
bool drawWhich(RenderWindow &window, Object *a, Object *b, Vector2f &mouse);
void drawText(RenderWindow &window, Info a);
void drawText(RenderWindow &window, Info *a);
void drawLongText(RenderWindow& window, Info a);
void drawLongText(RenderWindow& window, Info a, int max_size);
void drawLongText(RenderWindow& window, Info a, bool show_full, int max_size);
void drawLongText(RenderWindow& window, Info *a);
void drawLongText(RenderWindow& window, Info *a, int max_size);
bool switchPage(FloatRect &bound, Vector2f &mouse, int k, int &page);
bool switchPage(FloatRect &bound, Vector2f &mouse, int k, int &page, bool &change, bool true_or_false);
void changePos(Object *a, Object *b, float x, float y);
void changePos(Info& a, float x, float y);
void changePos(Object *a, float x, float y);
void changePos(Info *a, float x, float y);
void texting(Info& text, Uint32 unicode, unsigned int limit);
void texting(Info*& text, Uint32 unicode, unsigned int limit);
void texting_endl(Info &text, Uint32 unicode, unsigned int limit);
void texting_endl(Info *&text, Uint32 unicode, unsigned int limit);
// 0: nothing - nodraw, -1: confirm something, 1: nothing still draw
int checkConfirmation(RenderWindow &window, int &check, const Confirmation &element, Vector2f &mouse);
int searching(RenderWindow &window, int &status, SearchBar &s, Vector2f &mouse, int &add_status, Enlighten &dataset, Event &event, int count, Vocabulary& new_word);
void resetInfo(Info*& a, string s);
void resetInfo(Info& a, string s);
int checkString(Info a);
void changeInfo(Info& a, Info& b, string name_a, string name_b);

//---------------------Scene--------------------------
void Scene1(RenderWindow &window, int &page, Enlighten &dataset);
void setRole(RenderWindow &window, int &page, bool &is_admin, Enlighten &dataset);
void logIn(RenderWindow &window, int &page, const bool &is_admin, string &user_name, vector<string> &history, vector<string> &favourite, Enlighten &dataset);
void home(RenderWindow &window, int &page, bool &is_admin, const string &user_name, bool &is_fav, vector<string> history, Enlighten &dataset);
void wordDisplay(RenderWindow &window, int &page, const bool &is_admin, bool &is_fav, Enlighten &dataset, string word_here);
void myList(RenderWindow &window, int &page, bool &is_fav, Enlighten &dataset);
void revision(RenderWindow &window, int &page, Enlighten &dataset, int& level, bool difficulty);
void settings(RenderWindow &window, int &page, const bool &is_admin, Enlighten &dataset);
void testQA(RenderWindow &window, int &page, Enlighten& dataset, int level, bool& difficulty);

//------------------check word/definition in fav/his list---------
bool inVector(string str, vector <string> list, int& cur_id);

//------------------ timing---------------------------------
double getTime(auto start, auto end)
{
	double time = (double)(end - start) / CLOCKS_PER_SEC * 1000.0;
	return time;
}
//------------------ Data Structures------------------------
//-------------------Basic Trie-----------------------------
bool inputTxtFile(Trie &T, string fileName);
void writeBinaryFile(ofstream &f, Node *node);
bool outputBinaryFile(Trie T, string fileName);
void readBinaryFile(ifstream &f, Node *&node);
bool inputBinaryFile(Trie &T, string fileName);
bool getstr(string s, string &word, string &def);
Node *search(Trie T, string keyword); // return all definitions
bool insert(Trie &T, string word, string def);
bool edit(Trie &T, string word, int id, string def); // edit the id-th definition of word
bool remove(Trie &T, string word);
void deallocateNode(Node *&node);
void reset(Trie &T);

//-------------------Search---------------------------------
vector<string> search_result(Trie T, string keyword, int nums);
vector<string> &search_result(Trie &T, string keyword);
bool search_result(Trie T, string keyword, int nums, vector <string>& res);
//-------------------Search for definition------------------
vector<string> splitword(string str);
vector<string> search_def(Trie &T, string def, int nums);
bool build_definition_trie_TxtFile(Trie &T_def, string fileName);
bool cmp(pair<int, string> x, pair<int, string> y);
//-------------------Auto correct---------------------------
vector<string> correct_words(const Trie &T, string word, int nums);
bool insert(Trie &T, string word, double freq);
vector<string> EV(string path, vector<string> v);
void getTree(string path, Trie &root);

//--------------Autocomplete Word Functions-------------
void fillCompleteList(Node *cur, string word, vector<string> &completeList, int limit);
vector<string> autocomplete(Trie T, string word, int limit);

//-----------------------Revision-----------------------------
pair<string, string> randomWord(Trie T);
vector<vector<string>> revisionWord(Trie T, int level, vector<string> searchHistory, vector<string> favoriteList);

//-------------------Demo trie function------------------------
long long Rand(long long l, long long r);
void genWords(int nums_word, int len_def, string fileName);
void trie_testing(string fileName);
void trie_definition_testing(string fileName);
void trie_autocorrect(string fileName);
void trie_revision_testing(string fileName, vector<string> searchHistory, vector<string> favoriteList);

//------------------Draw Elements-----------------------
void loadingDataset(RenderWindow &window, Enlighten &p, int &page, int number_of_dataset);
void sleepHere(double s);
void typingWhat(Object& d, Object& w, Object&t, Vector2f& mouse, SearchBar& do_search);
void typingWhat(Object& d, Object& w, Object& t, Vector2f& mouse, Edit& do_search);
bool insert(Trie& T, string word, string type, string def);