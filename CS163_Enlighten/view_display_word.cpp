#include "header.h"


// admin only
void wordDisplayAdmin(RenderWindow& window, int& page, bool& is_fav, Enlighten& dataset, string word_here)
{
	Admin admin;
	Object screen = createObject("Graphic/p5_border.png");
	int cur_id = dataset.cur_id;
	Node* word_info = search(dataset.user_Trie[cur_id], word_here);
	if (!word_info) {
		page = 4;
		return;
	}
	//vector<string> &all_defi = search_result(dataset.user_Trie[cur_id], word_here);
	vector<string>& all_defi = word_info->def;
	vector<UserDef>& user_defi = word_info->user_definitions;
	int defi_id = -1;
	int user_defi_id = -1;
	int user_cur_page = 0;
	string path;
	path = ADMIN;
	string cur_defi = "";
	if (all_defi.size())
	{
		cur_defi = all_defi[0];
		defi_id = 0;
	}
	int id_fav_word = -1;
	bool is_fav_word = inVector(word_here, dataset.favorite, id_fav_word);
	Info word = createInfo("Graphic/Roboto-Regular.ttf", word_here, 380.0f, 180.0f, 64);
	Info definition = createInfo("Graphic/Roboto-Regular.ttf", cur_defi, 380.0f, 264.0f, 26);
	Info word_type = createInfo("Graphic/Roboto-Regular.ttf", "(" /*+ "word type" +*/, 390.0f + word.bound.width, 210.0f, 30);
	Object home1 = createObject("Graphic/home1.png", 0.0f, 168.0f);
	Object search_bar = createObject("Graphic/search_bar.png", 360.0f, 26.0f);
	pair<Object*, Object*> home = createElement("home", 0.0f, 168.0f);
	pair<Object*, Object*> settings = createElement("settings", 0.0f, 448.0f);
	pair<Object*, Object*> revision = createElement("revision", 0.0f, 308.0f);
	pair<Object*, Object*> fav = createElement("p4_fav", 963.0f, 31.0f);
	pair<Object*, Object*> user = createElement("p4_user", 1010.0f, 30.0f);
	pair<Object*, Object*> del = createElement("p4_del", 1056.0f, 32.0f);
	pair<Object*, Object*> add = createElement("add", 308.0f, 26.0f);
	pair<Object*, Object*> change = createElement("switch", 810.0f, 26.0f);
	pair<Object*, Object*> add_to_fav = createElement("p5_add_fav", 886.0f, 115.0f);
	pair<Object*, Object*> rem_fav = createElement("p5_rem_fav", 886.0f, 115.0f);
	Object w = createObject("Graphic/w.png", 317.0f, 196.0f);
	Object t = createObject("Graphic/t.png", 317.0f, 272.0f);
	Object d = createObject("Graphic/d.png", 317.0f, 348.0f);
	Edit edit_word(word_here, word_type.text.getString());
	Vocabulary existed_word;
	Object* border[3];
	LeftRight left_right;
	Info* name[3], * defi[3];
	int index = 0;
	for (int i = 0; i < 3; i++)
	{
		border[i] = createObjectTest("Graphic/p5_info_bar.png", 397.0f, 378.0f + 110.0f * i);
		name[i] = createInfoTest("Graphic/Roboto-Regular.ttf", "demo username", 426.0f, 396.0f + 110.0f * i, 18);
		defi[i] = createInfoTest("Graphic/RobotoCondensed-Bold.ttf", "demo definition here", 426.0f, 420.0f + 110.0f * i, 25);
	}
	Event event;
	changePos(add.second, 260.0f, 26.0f);

	bool flag = false, is_fixed = false;
	definition.s = cur_defi;
	definition.text.setString(definition.s);

	int check = 0;
	while (page == 5)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				page = 0;
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(fav.first->bound, mouse, 6, page, is_fav, true);
					switchPage(del.first->bound, mouse, 1, page);
					// switchPage(search_history.first->bound, mouse, x, page);
					switchPage(revision.first->bound, mouse, 7, page);
					if (isHere(edit_word.fixed.bound, mouse))
						is_fixed ^= 1;
				}
				if (!flag)
				{
					if (!is_fav_word && isHere(add_to_fav.first->bound, mouse))
					{
						is_fav_word ^= 1;
						dataset.favorite.push_back(word_here);
						id_fav_word = dataset.favorite.size() - 1;
						update(dataset.username, FAVORITE_LIST, dataset.favorite, path);
					}
					else if (is_fav_word && isHere(rem_fav.first->bound, mouse))
					{
						is_fav_word ^= 1;
						dataset.favorite.erase(dataset.favorite.begin() + id_fav_word);
						update(dataset.username, FAVORITE_LIST, dataset.favorite, path);
					}
					if (isHere(left_right.left[1], mouse) && defi_id > 0)
					{
						defi_id--;
						cur_defi = all_defi[defi_id];
						definition.s = cur_defi;
						definition.text.setString(definition.s);
					}
					else if (isHere(left_right.right[1], mouse) && defi_id + 1 < all_defi.size())
					{
						defi_id++;
						cur_defi = all_defi[defi_id];
						definition.s = cur_defi;
						definition.text.setString(definition.s);
					}
					if (admin.status == Admin::State::Open)
					{
						admin.status = Admin::State::DoSth;
						if (isHere(admin.add, mouse))
						{
							admin.button = Admin::AButton::Add;
						}
						else if (isHere(admin.edit, mouse))
						{
							admin.button = Admin::AButton::Edit;
							flag = true;
							edit_word.reset(existed_word);
							check = -1;
						}
						else if (isHere(admin.rem, mouse))
						{
							admin.button = Admin::AButton::Rem;
						}
						else if (isHere(admin.del, mouse))
						{
							admin.button = Admin::AButton::Del;
						}
						else
						{
							admin.status = Admin::State::Open;
						}
					}
					else if (admin.status == Admin::State::DoSth && isHere(admin.choose, mouse))
					{
						admin.status = Admin::State::Open;
					}
						//for (int i = 0; i < 3; i++)
						//{
						//	int id = i + user_cur_page * 3;
						//	if (id >= user_defi.size())
						//		break;
						//	if (isHere(deleteB[i], mouse))
						//	{
						//		// delete user_definition
						//		user_defi.erase(user_defi.begin() + id);
						//	}
						//}
					if (isHere(left_right.left[2], mouse) && user_cur_page > 0)
					{
						user_cur_page--;
					}
					else if (isHere(left_right.right[2], mouse) && (user_cur_page + 1) * 3 < user_defi.size())
					{
						user_cur_page++;
					}
				}
				else
				{
					typingWhat(d, w, t, mouse, edit_word);
				}
				break;
			}
			case Event::TextEntered:
			{
				if (flag)
				{
					texting(edit_word.enter_type, event.text.unicode, 30);
					texting_endl(edit_word.enter_defi, event.text.unicode, 36);
				}
				break;
			}
			default:
				break;
			}
		}
		window.clear();
		window.draw(screen.draw);
		window.draw(home1.draw);
		drawWhich(window, settings, mouse);
		drawWhich(window, revision, mouse);
		drawWhich(window, fav, mouse);
		drawWhich(window, change, mouse);
		drawWhich(window, add, mouse);
		drawWhich(window, user, mouse);
		drawWhich(window, del, mouse);
		left_right.draw(window, mouse);
		if (!is_fav_word)
		{
			drawWhich(window, add_to_fav, mouse);
		}
		else
		{
			drawWhich(window, rem_fav, mouse);
		}
		window.draw(search_bar.draw);
		window.draw(word.text);
		drawLongText(window, definition, true, 50);
		// window.draw(definition.text);
		for (int i = 0; i < 3; i++)
		{
			int id = i + user_cur_page * 3;
			if (id >= user_defi.size())
				break;
			name[i]->s = user_defi[id].username;
			name[i]->text.setString(name[i]->s);
			defi[i]->s = user_defi[id].definition;
			defi[i]->text.setString(defi[i]->s);
			window.draw(border[i]->draw);
			window.draw(name[i]->text);
			window.draw(defi[i]->text);
		}
		int check_me = edit_word.draw(window, mouse, flag, check, existed_word, true, is_fixed);

		if (check_me == 1)
		{
			if (!edit_word.enter_type.s.empty() && edit_word.enter_type.s[0] != '(')
				edit_word.enter_type.s = '(' + edit_word.enter_type.s + ") ";
			user_defi.push_back(UserDef(dataset.username, edit_word.enter_type.s + edit_word.enter_defi.s));
			// them dinh nghia cua nguoi dung
			// sua file data ?
			if (!writeJson(dataset.user_Trie[cur_id], JSONPATH))
				cout << "Can't write file " << JSONPATH << endl;
			else {
				cout << "Update " << JSONPATH << ": OK\n";
			}
		}
		else if (check_me == 2)
		{
			// change the word directly
			// sua file data ?
			string insert_word = word_here;
			string insert_type = "";
			if (!edit_word.enter_type.s.empty() && edit_word.enter_type.s[0] != '(')
				edit_word.enter_type.s = '(' + edit_word.enter_type.s + ") ";
			insert_type = edit_word.enter_type.s;
			string insert_defi = edit_word.enter_defi.s;
			insert(dataset.user_Trie[cur_id], insert_word, insert_type, insert_defi);
			all_defi.push_back(edit_word.enter_defi.s);
			word_type.s = existed_word.type;
			definition.text.setString(definition.s);
			word_type.text.setString(word_type.s);
			if (!writeJson(dataset.user_Trie[cur_id], JSONPATH))
				cout << "Can't write file " << JSONPATH << endl;
			else {
				cout << "Update " << JSONPATH << ": OK\n";
			}
		}
		bool done = admin.draw(window, mouse, check, (int)user_defi.size(), user_cur_page, index, flag);
		if (done)
		{
			// index: index cua user_def can thao tac
			switch (admin.button)
			{
			case Admin::AButton::Add:
				break;
			case Admin::AButton::Del:
				break;
			case Admin::AButton::Rem:
				break;
			default:
				break;
			}
		}
		window.display();
	}
	deallocate(home);
	deallocate(settings);
	deallocate(revision);
	deallocate(fav);
	deallocate(user);
	deallocate(del);
	deallocate(add);
	deallocate(change);
	left_right.deleteLR();
	deallocate(add_to_fav);
	deallocate(rem_fav);
	admin.deleteButton();
	for (int i = 0; i < 3; i++)
	{
		delete border[i], name[i], defi[i];
	}
	edit_word.deleteEdit();
}