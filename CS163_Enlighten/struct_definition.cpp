#include "header.h"

//------------------Struct(cont)-------------------------
struct AdminButton
{
	enum class AButton {Add = 1, Rem = 2, Edit = 3, Del = 4};
	enum class State { Close = 0, Open = 1, DoSth = 2};
	AButton button = AButton::Add;
	State status = State::Close;
	pair<Object*, Object*> choose = createElement("b_burger", 1058.0f, 340.0f);
	pair<Object*, Object*> add = createElement("b_add", 1070.0f, 295.0f);
	pair<Object*, Object*> rem = createElement("b_rem", 1021.0f, 314.0f);
	pair<Object*, Object*> edit = createElement("b_edit", 1021.0f, 367.0f);
	pair<Object*, Object*> del = createElement("b_del", 1070.0f, 384.0f);
	pair<Object*, Object*> p_add[3], p_del[3], p_push[3], p_rem = createElement("p_del", 1040.0f, 243.0f);
	Object border = createObject("Graphic/b_border.png", 1021.0f, 295.0f);
	Confirmation confirm[2];
	AdminButton()
	{
		for (int i = 0; i < 3; i++)
		{
			// create p_...
			p_add[i] = createElement("p_add", 980.0f, 410.0f + i * 110.0f);
			p_del[i] = createElement("p_del", 980.0f, 410.0f + i * 110.0f);
			p_push[i] = createElement("p_push", 980.0f, 410.0f + i * 110.0f);
		}
	}

	bool draw(RenderWindow& window, Vector2f& mouse, int& check, int count, int& index)
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
			if (!isHere(border.bound, mouse))
			{
				status = State::Close;
			}
			return false;
		case State::DoSth:
			int res = 0;
			if (button == AButton::Add)
			{
				window.draw(add.second->draw);
				window.draw(edit.first->draw);
				window.draw(rem.first->draw);
				window.draw(del.first->draw);
				for (int i = 0; i < count; i++)
				{
					drawWhich(window, p_add[i], mouse);
					if (isHere(p_add[i], mouse))
					{
						check = -1;
						index = i;
					}
				}
				res = checkConfirmation(window, check, confirm[0], mouse);
			}
			else if (button == AButton::Del)
			{
				window.draw(del.second->draw);
				window.draw(add.first->draw);
				window.draw(rem.first->draw);
				window.draw(edit.first->draw);
				for (int i = 0; i < count; i++)
				{
					drawWhich(window, p_del[i], mouse);
					if (isHere(p_del[i], mouse))
					{
						check = -1;
						index = i;
					}
				}
				res = checkConfirmation(window, check, confirm[0], mouse);
			}
			else if (button == AButton::Edit)
			{
				window.draw(edit.second->draw);
				window.draw(add.first->draw);
				window.draw(rem.first->draw);
				window.draw(del.first->draw);
				res = checkConfirmation(window, check, confirm[1], mouse);
			}
			else
			{
				window.draw(rem.second->draw);
				window.draw(add.first->draw);
				window.draw(del.first->draw);
				window.draw(edit.first->draw);
				if (isHere(p_rem, mouse))
				{
					check = -1;
					index = -1;
					//index = i;
				}
				res = checkConfirmation(window, check, confirm[0], mouse);
			}
			if (res == -1)
				return true;
			break;
			return false;
		}
	}
	void deleteButton()
	{
		deallocate(add);
		deallocate(rem);
		deallocate(edit);
		deallocate(del);
		deallocate(confirm[0]);
		deallocate(confirm[1]);
	}
};

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
	int assign(vector<string>& dict_name, int begin, bool& check)
	{
		int res = dict_name.size();
		int k = res < (begin + 6) ? res : (begin + 6);
		for (int i = begin; i < k; i++)
		{
			name[i]->s = dict_name[i];
			name[i]->text.setString(dict_name[i]);
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