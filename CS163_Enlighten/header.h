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
bool changeDataset(string folderpath, string destination);
string findFolder(string name, string dictionary_link);

//------------------Login Functions---------------------
bool login(string username, string password, string path, vector<string> &search_history, vector<string> &favorite_list);
bool changePassword(string username, string old_pass, string new_pass,string path);
bool createNewAccount(string username, string password, string path);
void update(string username, int CASE, vector<string> &list, string path);
void modify_csv(string username, int CASE, vector<string>& list, string path);

//-------------------Profile Functions-----------------
bool readUserProfile(string path, string username, Profile& profile);
bool readAllUserProfile(string path, vector<Profile>& profiles);
bool writeUserProfile(string path, string username, const Profile& profile);
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
int checkConfirmation(RenderWindow& window, Event& event, int& check, const Confirmation& element, Vector2f& mouse);
int searching(int is_okay, RenderWindow& window, int& status, SearchBar& s, Vector2f& mouse, int& add_status, Enlighten& dataset, Event& event, int count, Vocabulary& new_word);
int searching(RenderWindow& window, int& status, SearchBar& s, Vector2f& mouse, int& add_status, Enlighten& dataset, Event& event, int count, Vocabulary& new_word);
void resetInfo(Info*& a, string s);
void resetInfo(Info& a, string s);
int checkString(Info a);
void changeInfo(Info& a, Info& b, string name_a, string name_b);

//---------------------Scene--------------------------
void Scene1(RenderWindow& window, int& page, Enlighten& dataset);
void setRole(RenderWindow &window, int &page, Enlighten &dataset);
void logIn(RenderWindow &window, int &page, string &user_name, Enlighten &dataset);
void home(RenderWindow &window, int &page, const string &user_name, bool &is_fav, Enlighten &dataset);
void wordDisplay(RenderWindow &window, int &page, bool &is_fav, Enlighten &dataset, string word_here);
void myList(RenderWindow &window, int &page, Enlighten &dataset);
void revision(RenderWindow &window, int &page, Enlighten &dataset, int& level, bool difficulty);
void settings(RenderWindow &window, int &page, const bool &is_admin, Enlighten &dataset);
void testQA(RenderWindow &window, int &page, Enlighten& dataset, int level, bool& difficulty);
void wordDisplayAdmin(RenderWindow& window, int& page, bool& is_fav, Enlighten& dataset, string word_here);
void searchResult(RenderWindow& window, int& page, string word, Enlighten& dataset, bool& is_fav, bool right_word, bool is_normal);
void profile(RenderWindow& window, int& page, Enlighten& dataset, bool& is_admin);

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
Node *search(Trie &T, string keyword); // return all definitions
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
vector<string> correct_words(Trie &T, string word, int nums);
bool insert(Trie &T, string word, double freq);
vector<string> EV(string path, vector<string> v);
void getTree(string path, Trie &root);

//--------------Autocomplete Word Functions-------------
void fillCompleteList(Node *cur, string word, vector<string> &completeList, int limit);
vector<string> autocomplete(Trie T, string word, int limit);

//-----------------------Revision-----------------------------
bool randomWord(Trie T, pair<string, string>& ques);
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

//--------------------Play Sound-------------------------
bool playSound(string fileName);


//-------------------Deallocate data---------------------
void saveDatasets(RenderWindow& window, Enlighten dataset);
void deallocateDataset(Enlighten& dataset);


struct Confirmation
{
	pair<Object*, Object*> board;
	pair<Object*, Object*> nah;
	pair<Object*, Object*> of_course;
	pair<Object*, Object*> out;
	Object invalid = createObject("Graphic/invalid.png", 200.0f, 271.0f);
};

struct Vocabulary {
	string word;
	string type;
	vector<string> definitions;

	void resetWord(bool include_word)
	{
		if (include_word)
		{
			word = "";
		}
		type = "";
		definitions.clear();
	}

	void read(string s)
	{
		/*stringstream readMe(s);
		string res;
		definitions.clear();
		while (getline(readMe, res, ';' ))
		{
			definitions.push_back(res);
		}*/

		definitions.clear();
		unsigned int i = 0;
		while (i < s.size()) {
			string res;
			for (; i < s.size(); i++)
			{
				if (s[i] == '\n') res.push_back(' ');
				else if (s[i] == ';')
				{
					i++;
					break;
				}
				else res.push_back(s[i]);
			}
			definitions.push_back(res);
		}
	}
};

struct Dictionary
{
	Object board = createObject("Graphic/p0_choose.png", 200.0f, 270.0f);
	pair<Object*, Object*> button[6];
	pair<Object*, Object*> left = createElement("left", 530.0f, 510.0f);
	pair<Object*, Object*> right = createElement("right", 560.0f, 510.0f);
	Info* name[6];

	Dictionary()
	{
		for (int i = 0; i < 6; i++)
		{
			button[i] = createElement("p0_button", 230.0f + 220.0f * (i % 3), 360.0f + 80.0f * (int)(i / 3));
			name[i] = createInfoTest("Graphic/Oswald-Regular.ttf", "", 230.0f + 220.0f * (i % 3), 360.0f + 80.0f * (int)(i / 3), 30);
		}
	}

	void deallocateDic()
	{
		for (int i = 0; i < 6; i++)
		{
			deallocate(button[i]);
			delete name[i];
		}
		deallocate(left);
		deallocate(right);
	}
	void draw(RenderWindow& window, int flag, Vector2f& mouse, bool check)
	{
		window.draw(board.draw);
		for (int i = 0; i < flag; i++)
		{
			drawWhich(window, button[i], mouse);
			window.draw(name[i]->text);
		}
		if (check)
		{
			drawWhich(window, left, mouse);
			drawWhich(window, right, mouse);
		}
	}
	int assign(vector<Trie>& dict, int begin, bool& check)
	{
		int res = dict.size();
		int k = res < (begin + 6) ? res : (begin + 6);
		for (int i = begin; i < k; i++)
		{
			name[i]->s = dict[i].name;
			name[i]->text.setString(dict[i].name);
			name[i]->text.setFillColor(Color::White);
			changePos(name[i], 332.0f + 220.0f * (i % 3) - round(name[i]->bound.width / 2), 370.0f + 80.0f * (int)(i / 3));
		}
		if (begin) check = true;
		else check = false;
		return k - begin;
	}
};

struct SearchBar
{
	Info* search_info = createInfoTest("Graphic/Oswald-Regular.ttf", "type anything you want to search", 393.0f, 36.0f, 20);
	Object board = createObject("Graphic/p0_board.png", 330.0f, 22.0f);
	pair<Object*, Object*> change = createElement("switch", 810.0f, 26.0f);
	pair<Object*, Object*> search = createElement("search_bar", 360.0f, 26.0f);
	pair<Object*, Object*> add = createElement("add", 308.0f, 26.0f);
	pair<Object*, Object*> search_history = createElement("p4_sh", 658.0f, 211.0f);
	pair<Object*, Object*> SE[3];
	Confirmation new_word = create("p0_nw", "p0_cancel", "p0_ok", "p0_return", 0);
	Dictionary switch_dict;
	Info enter_word = createInfo("Graphic/Oswald-Light.ttf", "Enter word", 345.0f, 210.0f, 30);
	Info enter_type = createInfo("Graphic/Oswald-Light.ttf", "Enter type of word", 345.0f, 280.0f, 30);
	Info enter_defi = createInfo("Graphic/Oswald-Light.ttf", "Enter definition", 345.0f, 358.0f, 30);
	Info* result[3];
	Object search_normal = createObject("Graphic/d_search.png", 391.0f, 207.0f);
	Object search_defi = createObject("Graphic/d_search_here.png", 391.0f, 207.0f);
	bool is_normal = true;
	SearchBar()
	{
		for (int i = 0; i < 3; i++)
		{
			result[i] = createInfoTest("Graphic/Oswald-Regular.ttf", "", 393.0f, 78.0f + 44.0f * i, 20);
			SE[i] = createElement("p0_SE", 360.0f, 66.0f + 42.0f * i);
		}
		changePos(add.second, 260.0f, 26.0f);
	}
};

struct LeftRight
{
	pair<Object*, Object*> left[3], right[3];
	void draw(RenderWindow& window, Vector2f& mouse);
	void draw(RenderWindow& window, Vector2f& mouse, int x);
	void deleteLR();
	LeftRight();
	LeftRight(int x);
};

struct Edit
{
	pair<Object*, Object*> edit = createElement("edit", 1058.0f, 340.0f);
	Confirmation new_word = create("p0_nw", "p0_cancel", "p0_ok", "p0_return", 0);
	Info enter_word = createInfo("Graphic/Oswald-Light.ttf", "Enter word", 345.0f, 210.0f, 30);
	Info enter_type = createInfo("Graphic/Oswald-Light.ttf", "Enter type of word", 345.0f, 280.0f, 30);
	Info enter_defi = createInfo("Graphic/Oswald-Light.ttf", "Enter definition", 345.0f, 358.0f, 30);
	Object fixed = createObject("Graphic/p0_fixed.png", 837.0f, 196.0f);
	Object unfixed = createObject("Graphic/p0_unfixed.png", 837.0f, 196.0f);

	Edit(string word, string type)
	{
		enter_word.s = word;
		enter_type.s = type;
		enter_word.text.setString(word);
		enter_type.text.setString(type);
	}

	void reset(Vocabulary& word)
	{
		word.resetWord(false);
		enter_type.s = "";
		enter_type.check = false;
		enter_type.text.setString("Enter type of word");
		enter_defi.s = "";
		enter_defi.text.setString("Enter definition");
		enter_defi.check = false;
	}

	// 1: dinh nghia nguoi dung, 2: dinh nghia admin
	int draw(RenderWindow& window, Vector2f& mouse, bool& flag, int& check, Vocabulary& existed_word, const bool& is_admin, bool& is_fixed)
	{
		if (flag)
		{
			if (check == 0)
			{
				flag = false;
				return 0;
			}
			int res = checkConfirmation(window, check, new_word, mouse);
			if (is_admin && check == -1)
			{
				window.draw((is_fixed ? fixed.draw : unfixed.draw));
			}
			if (res == -1)
			{
				existed_word.read(enter_defi.s);
				existed_word.type = enter_type.s;
				if (is_admin && is_fixed) return 2;
				return 1;
			}
			else if (res == 0)
			{
				flag = false;
			}
			else if (check == -1)
			{
				window.draw(enter_word.text);
				window.draw(enter_defi.text);
				window.draw(enter_type.text);
				drawText(window, enter_word);
				drawText(window, enter_type);
				drawText(window, enter_defi);
			}
			window.draw(edit.first->draw);
		}
		else
		{
			drawWhich(window, edit, mouse);
		}
		return 0;
	}

	void deleteEdit()
	{
		deallocate(new_word);
		deallocate(edit);
	}
};

struct Admin
{
	enum class AButton { Add = 1, Rem = 2, Edit = 3, Del = 4 };
	enum class State { Close = 0, Open = 1, DoSth = 2 };
	AButton button = AButton::Add;
	State status = State::Close;
	pair<Object*, Object*> choose = createElement("b_burger", 1058.0f, 340.0f);
	pair<Object*, Object*> add = createElement("b_add", 1070.0f, 295.0f);
	pair<Object*, Object*> rem = createElement("b_rem", 1021.0f, 314.0f);
	pair<Object*, Object*> edit = createElement("b_edit", 1021.0f, 367.0f);
	pair<Object*, Object*> del = createElement("b_del", 1070.0f, 384.0f);
	pair<Object*, Object*> p_add[3], p_del[3], p_push[3], p_rem = createElement("p_del", 1040.0f, 243.0f);
	Object border = createObject("Graphic/b_border.png", 1021.0f, 295.0f);
	Confirmation confirm = create();


	bool draw(bool& is_okay, RenderWindow& window, Vector2f& mouse, int& check, int max_size, int id, int& index, bool& flag)
	{
		switch (status)
		{
		default:
			drawWhich(window, choose, mouse);
			if (isHere(choose, mouse))
			{
				status = State::Open;
			}
			return false;
		case State::Open:
			window.draw(choose.second->draw);
			drawWhich(window, add, mouse);
			drawWhich(window, edit, mouse);
			drawWhich(window, rem, mouse);
			drawWhich(window, del, mouse);
			if (!isHere(border.bound, mouse) && !is_okay)
			{
				status = State::Close;
			}
			return false;
		case State::DoSth:
			int res = 0;
			window.draw(choose.first->draw);
			if (button == AButton::Add)
			{
				window.draw(add.second->draw);
				window.draw(edit.first->draw);
				window.draw(rem.first->draw);
				window.draw(del.first->draw);
				for (int i = 0; i < 3; i++)
				{
					int id_c = i + id * 3;
					if (id_c >= max_size)
						break;
					drawWhich(window, p_add[i], mouse);
				}
				res = checkConfirmation(window, check, confirm, mouse);
			}
			else if (button == AButton::Del)
			{
				window.draw(del.second->draw);
				window.draw(add.first->draw);
				window.draw(rem.first->draw);
				window.draw(edit.first->draw);
				for (int i = 0; i < 3; i++)
				{
					int id_c = i + id * 3;
					if (id_c >= max_size)
						break;
					drawWhich(window, p_del[i], mouse);
				}
				res = checkConfirmation(window, check, confirm, mouse);
			}
			else if (button == AButton::Edit)
			{
				window.draw(edit.second->draw);
				window.draw(add.first->draw);
				window.draw(rem.first->draw);
				window.draw(del.first->draw);
				if (flag) res = 1;
				else
				{
					status = State::Close;
					return false;
				}
			}
			else
			{
				window.draw(rem.second->draw);
				window.draw(add.first->draw);
				window.draw(del.first->draw);
				window.draw(edit.first->draw);
				drawWhich(window, p_rem, mouse);
				res = checkConfirmation(window, check, confirm, mouse);
			}
			if (res == -1)
				return true;
			break;
			return false;
		}
		return false;
	}
	void deleteButton()
	{
		deallocate(add);
		deallocate(rem);
		deallocate(edit);
		deallocate(del);
		deallocate(confirm);
	}

	Admin()
	{
		for (int i = 0; i < 3; i++)
		{
			// create p_...
			p_add[i] = createElement("p_add", 980.0f, 410.0f + i * 110.0f);
			p_del[i] = createElement("p_del", 980.0f, 410.0f + i * 110.0f);
			p_push[i] = createElement("p_push", 980.0f, 410.0f + i * 110.0f);
		}
	}
};


