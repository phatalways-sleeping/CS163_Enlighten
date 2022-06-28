#pragma once
#include "header.h"
#include "test_function.h"

void wordDisplay(RenderWindow &window, int &page, const bool &is_admin, bool &is_fav, Enlighten &dataset, string word_here)
{
	pair<Object*, Object*> like = createElement("like", 873.0f, 412.0f);
	pair<Object*, Object*> dislike = createElement("dislike", 926.0f, 417.0f);
	Info like_count = createInfo("Graphic/VNI-Vari.TTF", "0", 900.0f, 415.0f, 17);
	Info like_count_here = createInfo("Graphic/VNI-Vari.TTF", "0", 900.0f, 415.0f, 17);
	like_count.text.setFillColor(Color(113, 171, 177, 255));
	like_count_here.text.setFillColor(Color(73, 101, 104, 255));
	Info dislike_count = createInfo("Graphic/VNI-Vari.TTF", "0", 952.0f, 415.0f, 17);
	Info dislike_count_here = createInfo("Graphic/VNI-Vari.TTF", "0", 952.0f, 415.0f, 17);
	dislike_count.text.setFillColor(Color(113, 171, 177, 255));
	dislike_count.text.setFillColor(Color(73, 101, 104, 255));
	// 1:like, 0: none, -1: dislike - check xem user da like/dislike chua
	int like_status = 0;
	Object screen = createObject("Graphic/p5_border.png");
	// Object settings1 = createObject("Graphic/settings1.png", 0.0f, 448.0f);
	// Object revision1 = createObject("Graphic/revision1.png", 0.0f, 308.0f);
	int cur_id = dataset.cur_id;
	Node* word_info = search(dataset.user_Trie[cur_id], word_here);
	if (!word_info) insert(dataset.user_Trie[cur_id], word_here, "");
	word_info = search(dataset.user_Trie[cur_id], word_here);
	//vector<string> &all_defi = search_result(dataset.user_Trie[cur_id], word_here);
	vector<string> &all_defi = word_info->def;
	vector<UserDef>& user_defi = word_info->user_definitions;
	int defi_id = -1;
	int user_defi_id = -1;
	int user_cur_page = 0;
	string path;
	if (dataset.is_admin)
		path = ADMIN;
	else
		path = USERS;
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
	pair<Object *, Object *> home = createElement("home", 0.0f, 168.0f);
	pair<Object *, Object *> settings = createElement("settings", 0.0f, 448.0f);
	pair<Object *, Object *> revision = createElement("revision", 0.0f, 308.0f);
	pair<Object *, Object *> fav = createElement("p4_fav", 963.0f, 31.0f);
	pair<Object *, Object *> user = createElement("p4_user", 1010.0f, 30.0f);
	pair<Object *, Object *> del = createElement("p4_del", 1056.0f, 32.0f);
	pair<Object *, Object *> add = createElement("add", 308.0f, 26.0f);
	pair<Object *, Object *> change = createElement("switch", 810.0f, 26.0f);
	pair<Object *, Object *> add_to_fav = createElement("p5_add_fav", 886.0f, 115.0f);
	pair<Object *, Object *> rem_fav = createElement("p5_rem_fav", 886.0f, 115.0f);
	pair<Object *, Object *> deleteB[3];
	Object w = createObject("Graphic/w.png", 317.0f, 196.0f);
	Object t = createObject("Graphic/t.png", 317.0f, 272.0f);
	Object d = createObject("Graphic/d.png", 317.0f, 348.0f);
	Edit edit_word(word_here, word_type.text.getString());
	Vocabulary existed_word;
	Object *border[3];
	LeftRight left_right;
	Info *name[3], *defi[3];
	for (int i = 0; i < 3; i++)
	{
		deleteB[i] = createElement("del", 980.0f, 410.0f + 110.0f * i);
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
					if (isHere(edit_word.edit, mouse))
					{
						flag = true;
						edit_word.reset(existed_word);
						check = -1;
					}
					else if (is_admin)
					{
						for (int i = 0; i < 3; i++)
						{
							int id = i + user_cur_page * 3;
							if (id >= user_defi.size())
								break;
							if (isHere(deleteB[i], mouse))
							{
								// delete user_definition
								user_defi.erase(user_defi.begin() + id);
							}
						}
					}
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
			if (is_admin)
				drawWhich(window, deleteB[i], mouse);
		}
		int check_me = edit_word.draw(window, mouse, flag, check, existed_word, is_admin, is_fixed);
		
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
		if (like_status == 0)
		{
			if (isHere(like, mouse) || isHere(like_count.bound, mouse))
			{
				window.draw(like.second->draw);
				window.draw(like_count_here.text);
			}
			else
			{
				window.draw(like.first->draw);
				window.draw(like_count.text);
			}
			if (isHere(dislike, mouse) || isHere(dislike_count.bound, mouse))
			{
				window.draw(dislike.second->draw);
				window.draw(dislike_count_here.text);
			}
			else
			{
				window.draw(dislike.first->draw);
				window.draw(dislike_count.text);
			}
		}
		else if (like_status == -1)
		{
			if (isHere(like, mouse) || isHere(like_count.bound, mouse))
			{
				window.draw(like.second->draw);
				window.draw(like_count_here.text);
			}
			else
			{
				window.draw(like.first->draw);
				window.draw(like_count.text);
			}
			window.draw(dislike.first->draw);
			window.draw(dislike_count.text);
		}
		else
		{
			if (isHere(dislike, mouse) || isHere(dislike_count.bound, mouse))
			{
				window.draw(dislike.second->draw);
				window.draw(dislike_count_here.text);
			}
			else
			{
				window.draw(dislike.first->draw);
				window.draw(dislike_count.text);
			}
			window.draw(like.first->draw);
			window.draw(like_count.text);
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
	for (int i = 0; i < 3; i++)
	{
		delete border[i], name[i], defi[i];
		deallocate(deleteB[i]);
	}
	deallocate(like);
	deallocate(dislike);
	edit_word.deleteEdit();
}

// page 12
void searchResult(RenderWindow& window, int& page, string result_word, Enlighten& dataset, bool right_word)
{
	Object screen = createObject("Graphic/border.png");
	Info* word;
	if(right_word)
		word = createInfoTest("Graphic/bahnschrift.ttf", "Search result for " + result_word, 402.0f, 127.0f, 21);
	else 
		word = createInfoTest("Graphic/bahnschrift.ttf", "Do you mean " + result_word, 402.0f, 127.0f, 21);
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
	pair<Object*, Object*> clear = createElement("clear", 886.0f, 120.0f);
	pair<Object*, Object*> rem_fav = createElement("p5_rem_fav", 886.0f, 115.0f);
	Object* border[5];
	pair<Object*, Object*> rem[5];
	Info* name[5], * defi[5];
	LeftRight left_right(1);

	/*int cur_page = 0;
	bool check = true;
	string path;
	if (dataset.is_admin)
		path = ADMIN;
	else
		path = USERS;
	int WHAT_LIST;
	if (is_fav)
		WHAT_LIST = FAVORITE_LIST;
	else
		WHAT_LIST = SEARCH_HISTORY;
	int cur_id = dataset.cur_id;
	int size = 100;
	vector<string>& cur_list = is_fav ? dataset.favorite : dataset.history;
	size = min(size, (int)cur_list.size());*/
	//-------------------------------------------------------------------
	for (int i = 0; i < 5; i++)
	{
		rem[i] = createElement("del", 980.0f, 210.0f + 110.0f * i);
		border[i] = createObjectTest("Graphic/bar.png", 360.0f, 178.0f + 110.0f * i);
		name[i] = createInfoTest("Graphic/Roboto-Medium.ttf", "", 390.0f, 190.0f + 110.0f * i, 23);
		defi[i] = createInfoTest("Graphic/RobotoCondensed-Regular.ttf", "", 390.0f, 225.0f + 110.0f * i, 17);
	}

	Event event;
	changePos(add.second, 260.0f, 26.0f);

	while (page == 12)
	{
		/*if (check)
		{

			for (int i = 0; i < 5; i++)
			{
				if (i + cur_page * 5 >= size)
					break;
				name[i]->s = cur_list[i + cur_page * 5];
				cerr << i << ": " << name[i]->s << endl;
				name[i]->text.setString(name[i]->s);
			}

			for (int i = 0; i < 5; i++)
			{
				if (i + cur_page * 5 >= size)
					break;
				Node* defi_search = search(dataset.user_Trie[cur_id], name[i]->s);
				if (defi_search && defi_search->def.size())
				{
					defi[i]->s = defi_search->def[0];
					defi[i]->text.setString(defi[i]->s);
				}
			}
		}
		check = false;*/
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
				//if (event.mouseButton.button == Mouse::Left)
				//{
				//	switchPage(del.first->bound, mouse, 1, page);
				//	switchPage(revision.first->bound, mouse, 7, page);
				//	switchPage(home1.bound, mouse, 4, page);
				//	for (int i = 0; i < 5; i++)
				//	{
				//		if (i + cur_page * 5 >= size)
				//			break;
				//		if (isHere(border[i], mouse) && !name[i]->s.empty())
				//		{ // word display
				//			page = 5;
				//			wordDisplay(window, page, dataset.is_admin, is_fav, dataset, name[i]->s);
				//			return;
				//		}
				//		if (isHere(rem[i], mouse)) // del 1 defi
				//		{
				//			size--;
				//			if (size % 5 == 0 && cur_page > 0)
				//			{
				//				cur_page--;
				//			}
				//			check = true;
				//			cur_list.erase(cur_list.begin() + i + cur_page * 5);
				//			// update(dataset.username, WHAT_LIST, cur_list, path);
				//		}
				//	}
				//	if (isHere(clear, mouse))
				//	{ // clear all
				//		cur_list.clear();
				//		check = true;
				//		size = 0;
				//		cur_page = 0;
				//		// update(dataset.username, WHAT_LIST, cur_list, path);
				//	}
				//	else if (isHere(left_right.left[2], mouse) && cur_page > 0)
				//	{
				//		cur_page--;
				//		check = true;
				//	}
				//	else if (isHere(left_right.right[2], mouse) && (cur_page + 1) * 5 < size)
				//	{
				//		cur_page++;
				//		check = true;
				//	}
				//}
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
		left_right.draw(window, mouse, 0);
		left_right.draw(window, mouse, 2);
		drawWhich(window, clear, mouse);
		window.draw(search_bar.draw);
		//for (int i = 0; i < 5; i++)
		//{
		//	int id = i + cur_page * 5;
		//	if (id >= size)
		//		break;
		//	window.draw(border[i]->draw);
		//	window.draw(name[i]->text);
		//	// window.draw(defi[i]->text);
		//	drawLongText(window, defi[i]);
		//	drawWhich(window, rem[i], mouse);
		//}
		window.draw(word->text);
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
	deallocate(clear);
	deallocate(rem_fav);
	delete word;
	for (int i = 0; i < 5; i++)
	{
		delete border[i], name[i], defi[i], rem[i];
	}
}

void myList(RenderWindow &window, int &page, bool &is_fav, Enlighten &dataset)
{
	Object screen = createObject("Graphic/border.png");
	Info *word;
	if (is_fav)
		word = createInfoTest("Graphic/bahnschrift.ttf", "Favorite", 402.0f, 127.0f, 21);
	else
		word = createInfoTest("Graphic/bahnschrift.ttf", "Search History", 402.0f, 127.0f, 21);
	Object home1 = createObject("Graphic/home1.png", 0.0f, 168.0f);
	Object search_bar = createObject("Graphic/search_bar.png", 360.0f, 26.0f);
	pair<Object *, Object *> home = createElement("home", 0.0f, 168.0f);
	pair<Object *, Object *> settings = createElement("settings", 0.0f, 448.0f);
	pair<Object *, Object *> revision = createElement("revision", 0.0f, 308.0f);
	pair<Object *, Object *> fav = createElement("p4_fav", 963.0f, 31.0f);
	pair<Object *, Object *> user = createElement("p4_user", 1010.0f, 30.0f);
	pair<Object *, Object *> del = createElement("p4_del", 1056.0f, 32.0f);
	pair<Object *, Object *> add = createElement("add", 308.0f, 26.0f);
	pair<Object *, Object *> change = createElement("switch", 810.0f, 26.0f);
	pair<Object *, Object *> clear = createElement("clear", 886.0f, 120.0f);
	pair<Object *, Object *> rem_fav = createElement("p5_rem_fav", 886.0f, 115.0f);
	Object *border[5];
	pair<Object *, Object *> rem[5];
	Info *name[5], *defi[5];
	LeftRight left_right(1);

	int cur_page = 0;
	bool check = true;
	string path;
	if (dataset.is_admin)
		path = ADMIN;
	else
		path = USERS;
	int WHAT_LIST;
	if (is_fav)
		WHAT_LIST = FAVORITE_LIST;
	else
		WHAT_LIST = SEARCH_HISTORY;
	int cur_id = dataset.cur_id;
	int size = 100;
	vector<string> &cur_list = is_fav ? dataset.favorite : dataset.history;
	size = min(size, (int)cur_list.size());
	//-------------------------------------------------------------------
	for (int i = 0; i < 5; i++)
	{
		rem[i] = createElement("del", 980.0f, 210.0f + 110.0f * i);
		border[i] = createObjectTest("Graphic/bar.png", 360.0f, 178.0f + 110.0f * i);
		name[i] = createInfoTest("Graphic/Roboto-Medium.ttf", "", 390.0f, 190.0f + 110.0f * i, 23);
		defi[i] = createInfoTest("Graphic/RobotoCondensed-Regular.ttf", "", 390.0f, 225.0f + 110.0f * i, 17);
	}

	Event event;
	changePos(add.second, 260.0f, 26.0f);

	while (page == 6)
	{
		if (check)
		{

			for (int i = 0; i < 5; i++)
			{
				if (i + cur_page * 5 >= size)
					break;
				name[i]->s = cur_list[i + cur_page * 5];
				cerr << i << ": " << name[i]->s << endl;
				name[i]->text.setString(name[i]->s);
			}

			for (int i = 0; i < 5; i++)
			{
				if (i + cur_page * 5 >= size)
					break;
				Node *defi_search = search(dataset.user_Trie[cur_id], name[i]->s);
				if (defi_search && defi_search->def.size())
				{
					defi[i]->s = defi_search->def[0];
					defi[i]->text.setString(defi[i]->s);
				}
			}
		}
		check = false;
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
					switchPage(del.first->bound, mouse, 1, page);
					switchPage(revision.first->bound, mouse, 7, page);
					switchPage(home1.bound, mouse, 4, page);
					for (int i = 0; i < 5; i++)
					{
						if (i + cur_page * 5 >= size)
							break;
						if (isHere(border[i], mouse) && !name[i]->s.empty())
						{ // word display
							page = 5;
							wordDisplay(window, page, dataset.is_admin, is_fav, dataset, name[i]->s);
							return;
						}
						if (isHere(rem[i], mouse)) // del 1 defi
						{
							size--;
							if (size % 5 == 0 && cur_page > 0)
							{
								cur_page--;
							}
							check = true;
							cur_list.erase(cur_list.begin() + i + cur_page * 5);
							// update(dataset.username, WHAT_LIST, cur_list, path);
						}
					}
					if (isHere(clear, mouse))
					{ // clear all
						cur_list.clear();
						check = true;
						size = 0;
						cur_page = 0;
						// update(dataset.username, WHAT_LIST, cur_list, path);
					}
					else if (isHere(left_right.left[2], mouse) && cur_page > 0)
					{
						cur_page--;
						check = true;
					}
					else if (isHere(left_right.right[2], mouse) && (cur_page + 1) * 5 < size)
					{
						cur_page++;
						check = true;
					}
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
		left_right.draw(window, mouse, 0);
		left_right.draw(window, mouse, 2);
		drawWhich(window, clear, mouse);
		window.draw(search_bar.draw);
		for (int i = 0; i < 5; i++)
		{
			int id = i + cur_page * 5;
			if (id >= size)
				break;
			window.draw(border[i]->draw);
			window.draw(name[i]->text);
			// window.draw(defi[i]->text);
			drawLongText(window, defi[i]);
			drawWhich(window, rem[i], mouse);
		}
		window.draw(word->text);
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
	deallocate(clear);
	deallocate(rem_fav);
	delete word;
	for (int i = 0; i < 5; i++)
	{
		delete border[i], name[i], defi[i], rem[i];
	}
}
