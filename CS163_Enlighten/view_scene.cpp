#pragma once
#include "header.h"
#include "test_function.h"

void wordDisplay(RenderWindow &window, int &page, bool &is_fav, Enlighten &dataset, string word_here)
{
	if (dataset.is_admin) {
		wordDisplayAdmin(window, page, is_fav, dataset, word_here);
		return;
	}
	// Object settings1 = createObject("Graphic/settings1.png", 0.0f, 448.0f);
	// Object revision1 = createObject("Graphic/revision1.png", 0.0f, 308.0f);
	int cur_id = dataset.cur_id;
	Node* word_info = search(dataset.user_Trie[cur_id], word_here);
	if (!word_info) {
		page = 4;
		return;
	}
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
	pair<Object *, Object *> add_to_fav = createElement("p5_add_fav", 886.0f, 115.0f);
	pair<Object *, Object *> rem_fav = createElement("p5_rem_fav", 886.0f, 115.0f);
	pair<Object *, Object *> deleteB[3];
	pair<Object*, Object*> like[3];
	pair<Object*, Object*> dislike[3];
	/*
	pair<Object*, Object*> like[3] = createElement("like", 873.0f, 412.0f);
	pair<Object*, Object*> dislike[3] = createElement("dislike", 926.0f, 417.0f);
	Info* like_count[3] = createInfo("Graphic/VNI-Vari.TTF", "0", 900.0f, 415.0f, 17);
	Info* like_count_here[3] = createInfo("Graphic/VNI-Vari.TTF", "0", 900.0f, 415.0f, 17);
	like_count.text.setFillColor(Color(113, 171, 177, 255));
	like_count_here.text.setFillColor(Color(73, 101, 104, 255));
	Info* dislike_count[3] = createInfo("Graphic/VNI-Vari.TTF", "0", 952.0f, 415.0f, 17);
	Info* dislike_count_here[3] = createInfo("Graphic/VNI-Vari.TTF", "0", 952.0f, 415.0f, 17);
	dislike_count.text.setFillColor(Color(113, 171, 177, 255));
	dislike_count_here.text.setFillColor(Color(73, 101, 104, 255));*/
	// 1:like, 0: none, -1: dislike - check xem user da like/dislike chua
	int like_status[3] = { 0, 0, 0 };
	Object screen = createObject("Graphic/p5_border.png");
	Object w = createObject("Graphic/w.png", 317.0f, 196.0f);
	Object t = createObject("Graphic/t.png", 317.0f, 272.0f);
	Object d = createObject("Graphic/d.png", 317.0f, 348.0f);
	Edit edit_word(word_here, word_type.text.getString());
	Vocabulary existed_word;
	Object *border[3];
	LeftRight left_right;
	Info *name[3], *defi[3];
	Info* like_count[3];
	Info* like_count_here[3]; 
	Info* dislike_count[3]; 
	Info* dislike_count_here[3];
	Object* special[3];
	SearchBar do_search;
	Vocabulary new_word;
	for (int i = 0; i < 3; i++)
	{
		deleteB[i] = createElement("del", 980.0f, 410.0f + 110.0f * i);
		like[i] = createElement("like", 873.0f, 417.0f + 110.0f * i);
		dislike[i] = createElement("dislike", 926.0f, 417.0f + 110.0f * i);
		border[i] = createObjectTest("Graphic/p5_info_bar.png", 397.0f, 378.0f + 110.0f * i);
		like_count[i] = createInfoTest("Graphic/VNI-Vari.TTF", "0", 900.0f, 417.0f + 110.0f * i, 17);
		like_count_here[i] = createInfoTest("Graphic/VNI-Vari.TTF", "0", 900.0f, 417.0f + 110.0f * i, 17);
		dislike_count[i] = createInfoTest("Graphic/VNI-Vari.TTF", "0", 952.0f, 417.0f + 110.0f * i, 17);
		dislike_count_here[i] = createInfoTest("Graphic/VNI-Vari.TTF", "0", 952.0f, 417.0f + 110.0f * i, 17);
		name[i] = createInfoTest("Graphic/Roboto-Regular.ttf", "demo username", 426.0f, 396.0f + 110.0f * i, 18);
		defi[i] = createInfoTest("Graphic/RobotoCondensed-Bold.ttf", "demo definition here", 426.0f, 420.0f + 110.0f * i, 25);
		like_count[i]->text.setFillColor(Color(113, 171, 177, 255));
		like_count_here[i]->text.setFillColor(Color(73, 101, 104, 255));
		dislike_count[i]->text.setFillColor(Color(113, 171, 177, 255));
		dislike_count_here[i]->text.setFillColor(Color(73, 101, 104, 255));
		special[i] = createObjectTest("Graphic/p_top.png", 375.0f, 375.0f + 110.0f * i);
	}
	Event event;
	
	bool flag = false, is_fixed = false;
	definition.s = cur_defi;
	definition.text.setString(definition.s);
	int check = 0;
	bool sort_user_list = false;

	int size_searchBar = min(3, (int)dataset.history.size());
	int temp = 0;
	for (int i = 0; i < size_searchBar && temp < dataset.history.size(); ++i) {
		bool found = false;
		while (!found && temp < dataset.history.size()) {
			string w = dataset.history[temp];
			Node* info = search(dataset.user_Trie[cur_id], w);
			if (!info || info->definitions.empty()) {
				temp++;
			}
			else {
				do_search.result[i]->s = w;
				do_search.result[i]->text.setString(w);
				found = true;
				temp++;
			}
		}

	}
	int search_status = 0, add_status = 0, count = 0;
	bool isBreak = false;
	while (page == 5)
	{
		if (sort_user_list) {
			sort(user_defi.begin(), user_defi.end(), like_compare);
			sort_user_list = false;
		}
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				page = 0;
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(do_search.search_history.first->bound, mouse, 13, page);
					switchPage(fav.first->bound, mouse, 6, page);
					switchPage(del.first->bound, mouse, 1, page);
					switchPage(revision.first->bound, mouse, 7, page);
					switchPage(settings.first->bound, mouse, 8, page);
					switchPage(user.first->bound, mouse, 11, page);
					switchPage(home.first->bound, mouse, 4, page);
					if (search_status == 1) {
						for (int i = 0; i < size_searchBar; i++) {
							if (isHere(do_search.SE[i], mouse) && !do_search.result[i]->s.empty()) {
								search_status = 0;
								page = 5;
								if (dataset.is_admin)
									wordDisplayAdmin(window, page, is_fav, dataset, do_search.result[i]->s);
								else
									wordDisplay(window, page, is_fav, dataset, do_search.result[i]->s);
								isBreak = true;
								break;
							}
						}
						if (isBreak) break;
					}
					if (isHere(do_search.switch_dict.left, mouse))
					{
						count = (count == 0 ? 0 : count - 6);
					}
					else if (isHere(do_search.switch_dict.right, mouse))
					{
						count = (count < dataset.user_Trie.size() - 6 ? count + 6 : count);
					}
					else if (search_status == 2)
					{
						typingWhat(d, w, t, mouse, do_search);
					}
					else if (isHere(do_search.search_normal.bound, mouse))
					{
						do_search.is_normal ^= 1;
					}
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
					
					
					for (int i = 0; i < 3; i++)
					{
						int id = i + user_cur_page * 3;
						if (id >= user_defi.size())
							break;
						if (isHere(deleteB[i], mouse) && (dataset.is_admin || user_defi[id].username == dataset.username))
						{
							// delete user_definition
							sort_user_list = true;
							user_defi.erase(user_defi.begin() + id);
							if (!writeJson(dataset.user_Trie[cur_id], JSONPATH))
								cout << "Can't write file " << JSONPATH << endl;
							else {
								cout << "Update " << JSONPATH << ": OK\n";
							}
						}
						int like_id = -1;
						like_status[i] = likeStatus(dataset.username, user_defi[id].list, like_id); /// like / dislike
						if (like_status[i] == 0)
						{
							if (isHere(like[i], mouse) || isHere(like[i].first->bound, mouse))
							{
								sort_user_list = true;
								user_defi[id].like++;
								user_defi[id].list.push_back({ dataset.username, 1 });
								// update json tai day :(
								like_count[i]->s = to_string(user_defi[id].like);
								like_count[i]->text.setString(like_count[i]->s);
								like_count_here[i]->s = to_string(user_defi[id].like);
								like_count_here[i]->text.setString(like_count_here[i]->s);
							}
							if (isHere(dislike[i], mouse) || isHere(dislike_count[i]->bound, mouse))
							{
								sort_user_list = true;
								user_defi[id].dislike++;
								user_defi[id].list.push_back({ dataset.username, 0 });
								// update json tai day :(
								dislike_count[i]->s = to_string(user_defi[id].dislike);
								dislike_count[i]->text.setString(dislike_count[i]->s);
								dislike_count_here[i]->s = to_string(user_defi[id].dislike);
								dislike_count_here[i]->text.setString(dislike_count_here[i]->s);
							}
						}
						else if (like_status[i] == -1)
						{
							if (isHere(like[i], mouse) || isHere(like_count[i]->bound, mouse)) // dislike ma bam like
							{
								sort_user_list = true;
								user_defi[id].like++;
								user_defi[id].dislike--;
								user_defi[id].list[like_id].second ^= 1;
								// update json tai day :(
								like_count[i]->s = to_string(user_defi[id].like);
								like_count[i]->text.setString(like_count[i]->s);
								like_count_here[i]->s = to_string(user_defi[id].like);
								like_count_here[i]->text.setString(like_count_here[i]->s);
								dislike_count[i]->s = to_string(user_defi[id].dislike);
								dislike_count[i]->text.setString(dislike_count[i]->s);
								dislike_count_here[i]->s = to_string(user_defi[id].dislike);
								dislike_count_here[i]->text.setString(dislike_count_here[i]->s);
								
							}
							
							if (isHere(dislike[i], mouse) || isHere(dislike_count[i]->bound, mouse)) { // dislike ma huy dislike
								sort_user_list = true;
								user_defi[id].dislike--;
								user_defi[id].list.erase(user_defi[id].list.begin() + like_id);
								// update json tai day :(
								dislike_count[i]->s = to_string(user_defi[id].dislike);
								dislike_count[i]->text.setString(dislike_count[i]->s);
								dislike_count_here[i]->s = to_string(user_defi[id].dislike);
								dislike_count_here[i]->text.setString(dislike_count_here[i]->s);
								
							}

						}
						else
						{
							if (isHere(dislike[i], mouse) || isHere(dislike_count[i]->bound, mouse)) // like ma bam dislike
							{
								sort_user_list = true;
								user_defi[id].like--;
								user_defi[id].dislike++;
								user_defi[id].list[like_id].second ^= 1;
								// update json tai day :(
								like_count[i]->s = to_string(user_defi[id].like);
								like_count[i]->text.setString(like_count[i]->s);
								like_count_here[i]->s = to_string(user_defi[id].like);
								like_count_here[i]->text.setString(like_count_here[i]->s);
								dislike_count[i]->s = to_string(user_defi[id].dislike);
								dislike_count[i]->text.setString(dislike_count[i]->s);
								dislike_count_here[i]->s = to_string(user_defi[id].dislike);
								dislike_count_here[i]->text.setString(dislike_count_here[i]->s);
								
							}
						
							if (isHere(like[i], mouse) || isHere(like_count[i]->bound, mouse)) { // like ma huy like
								sort_user_list = true;
								user_defi[id].like--;
								user_defi[id].list.erase(user_defi[id].list.begin() + like_id);
								// update json tai day :(
								like_count[i]->s = to_string(user_defi[id].like);
								like_count[i]->text.setString(like_count[i]->s);
								like_count_here[i]->s = to_string(user_defi[id].like);
								like_count_here[i]->text.setString(like_count_here[i]->s);
								
							}
							
							/*window.draw(like[i].first->draw);
							window.draw(like_count[i]->text);*/
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
				if (search_status == 1)
				{
					if (event.text.unicode == 13) {
						if (do_search.is_normal) {
							if (do_search.result[0]->s == "") {
								page = 12;
								searchResult(window, page, do_search.search_info->s, dataset, is_fav, 0, 1);
							}
							else {
								page = 12;
								searchResult(window, page, do_search.result[0]->s, dataset, is_fav, do_search.result[0]->s == do_search.search_info->s, 1);
							}
						}
						else {
							page = 12;
							searchResult(window, page, do_search.search_info->s, dataset, is_fav, 0, 0);
						}
						isBreak = true;
						break;
					}
					texting(do_search.search_info, event.text.unicode, 30);
					vector<string> completeList;
					vector <string> correctList;
					if (do_search.is_normal) {
						completeList = autocomplete(dataset.user_Trie[dataset.cur_id], do_search.search_info->s, 3);
						correctList = correct_words(dataset.user_Trie[dataset.cur_id], do_search.search_info->s, 3);
						for (auto s : correctList)
						{
							bool isExist = false;
							for (auto t : completeList) {
								if (t == s) {
									isExist = true;
									break;
								}
							}
							if (!isExist) completeList.push_back(s);
						}
					}
					else {
						completeList = search_def(dataset.def_Trie[dataset.cur_id], do_search.search_info->s, 3);
					}
					for (int i = 0; i < 3; i++)
					{
						do_search.result[i]->s = "";
						do_search.result[i]->text.setString("");
					}

					if (do_search.search_info->s.empty()) {
						size_searchBar = min(3, (int)dataset.history.size());
						int temp = 0;
						for (int i = 0; i < size_searchBar && temp < dataset.history.size(); ++i) {
							bool found = false;
							while (!found && temp < dataset.history.size()) {
								string w = dataset.history[temp];
								Node* info = search(dataset.user_Trie[cur_id], w);
								if (!info || info->definitions.empty()) {
									temp++;
								}
								else {
									do_search.result[i]->s = w;
									do_search.result[i]->text.setString(w);
									found = true;
									temp++;
								}
							}

						}
					}
					else {
						size_searchBar = min(3, (int)completeList.size());
						for (int i = 0; i < size_searchBar; ++i) {
							do_search.result[i]->s = completeList[i];
							do_search.result[i]->text.setString(completeList[i]);
						}
					}


				}
				else if (search_status == 2)
				{
					texting_endl(do_search.enter_defi, event.text.unicode, 36);
					texting(do_search.enter_word, event.text.unicode, 30);
					texting(do_search.enter_type, event.text.unicode, 30);
				}
				else {

				}
				break;
			}
			case Event::KeyReleased:
				if (event.key.code == Keyboard::F && search_status < 1)
				{
					search_status = 1;
					do_search.search_info->check = true;
				}
				else if (event.key.code == Keyboard::Escape)
				{
					search_status = 0;
					do_search.search_info->s = "";
					do_search.search_info->text.setString("");
				}
				break;
			default:
				break;
			}
			if (isBreak) break;
		}
		if (isBreak) break;
		window.clear();
		window.draw(screen.draw);
		window.draw(home1.draw);
		drawWhich(window, settings, mouse);
		drawWhich(window, revision, mouse);
		drawWhich(window, fav, mouse);
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
			like_count[i]->s = to_string(user_defi[id].like);
			like_count_here[i]->s = to_string(user_defi[id].like);
			dislike_count[i]->s = to_string(user_defi[id].dislike);
			dislike_count_here[i]->s = to_string(user_defi[id].dislike);
			// show special
			if (user_defi[id].like - user_defi[id].dislike >= special_value) {
				window.draw(special[i]->draw);
			}
			//
			like_count[i]->text.setString(like_count[i]->s);
			like_count_here[i]->text.setString(like_count_here[i]->s);
			dislike_count[i]->text.setString(dislike_count[i]->s);
			dislike_count_here[i]->text.setString(dislike_count_here[i]->s);
			int like_id = -1;
			like_status[i] = likeStatus(dataset.username, user_defi[id].list, like_id); // show like, dislike
			window.draw(border[i]->draw);
			window.draw(name[i]->text);
			window.draw(defi[i]->text);
			if (dataset.is_admin || user_defi[id].username == dataset.username)
				drawWhich(window, deleteB[i], mouse);
			
			if (like_status[i] == 0)
			{
				if (isHere(like[i], mouse))
				{	
					window.draw(like[i].second->draw);
					window.draw(like_count_here[i]->text);
				}
				else
				{
					window.draw(like[i].first->draw);
					window.draw(like_count[i]->text);
				}
				if (isHere(dislike[i], mouse) || isHere(dislike_count[i]->bound, mouse))
				{
					
					window.draw(dislike[i].second->draw);
					window.draw(dislike_count_here[i]->text);
				}
				else
				{
					window.draw(dislike[i].first->draw);
					window.draw(dislike_count[i]->text);
				}
			}
			else if (like_status[i] == -1)
			{
				if (isHere(like[i], mouse) || isHere(like_count[i]->bound, mouse)) // dislike ma bam like
				{
					window.draw(like[i].second->draw);
					window.draw(like_count_here[i]->text);
					window.draw(dislike[i].first->draw);
					window.draw(dislike_count[i]->text);
				}
				else if (isHere(dislike[i], mouse) || isHere(dislike_count[i]->bound, mouse)) { // dislike ma huy dislike
					window.draw(like[i].first->draw);
					window.draw(like_count[i]->text);
					window.draw(dislike[i].second->draw);
					window.draw(dislike_count_here[i]->text);
				}
				else {
					window.draw(like[i].first->draw);
					window.draw(like_count[i]->text);
					window.draw(dislike[i].second->draw);
					window.draw(dislike_count_here[i]->text);
				}
			}
			else
			{
				if (isHere(dislike[i], mouse) || isHere(dislike_count[i]->bound, mouse)) // like ma bam dislike
				{
				
					window.draw(like[i].first->draw);
					window.draw(like_count[i]->text);
					window.draw(dislike[i].second->draw);
					window.draw(dislike_count_here[i]->text);
				}
				else if (isHere(like[i], mouse) || isHere(like_count[i]->bound, mouse)) { // like ma huy like
					
					window.draw(like[i].second->draw);
					window.draw(like_count_here[i]->text);
					window.draw(dislike[i].first->draw);
					window.draw(dislike_count[i]->text);
				}
				else {
					window.draw(like[i].second->draw);
					window.draw(like_count_here[i]->text);
					window.draw(dislike[i].first->draw);
					window.draw(dislike_count[i]->text);

				}
				/*window.draw(like[i].first->draw);
				window.draw(like_count[i]->text);*/
			}
		}
		int check_me = edit_word.draw(window, mouse, flag, check, existed_word, dataset.is_admin, is_fixed);
		
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
		int check_search = searching(window, search_status, do_search, mouse, add_status, dataset, event, count, new_word);
		if (check_search == 1)
		{
			// added new word
		}
		else if (check_search > 0)
		{
			// switch to other dictionary
		}
		
		window.display();
	}
	deallocate(home);
	deallocate(settings);
	deallocate(revision);
	deallocate(fav);
	deallocate(user);
	deallocate(del);
	left_right.deleteLR();
	deallocate(add_to_fav);
	deallocate(rem_fav);
	for (int i = 0; i < 3; i++)
	{
		delete border[i], name[i], defi[i], like_count[i], like_count_here[i], dislike_count[i], dislike_count_here[i];
		deallocate(deleteB[i]);
		deallocate(like[i]);
		deallocate(dislike[i]);
		delete(special[i]);
	}
	
	edit_word.deleteEdit();
}

// page 12
void searchResult(RenderWindow& window, int& page, string result_word, Enlighten& dataset, bool& is_fav, bool right_word, bool is_normal)
{
	Object screen = createObject("Graphic/border.png");
	Info* word;
	if(right_word)
		word = createInfoTest("Graphic/bahnschrift.ttf", "Search result for \"" + result_word + "\"", 402.0f, 127.0f, 21);
	else 
		word = createInfoTest("Graphic/bahnschrift.ttf", "Do you mean \"" + result_word + "\"", 402.0f, 127.0f, 21);
	Object home1 = createObject("Graphic/home1.png", 0.0f, 168.0f);
	Object search_bar = createObject("Graphic/search_bar.png", 360.0f, 26.0f);
	pair<Object*, Object*> home = createElement("home", 0.0f, 168.0f);
	pair<Object*, Object*> settings = createElement("settings", 0.0f, 448.0f);
	pair<Object*, Object*> revision = createElement("revision", 0.0f, 308.0f);
	pair<Object*, Object*> fav = createElement("p4_fav", 963.0f, 31.0f);
	pair<Object*, Object*> user = createElement("p4_user", 1010.0f, 30.0f);
	pair<Object*, Object*> del = createElement("p4_del", 1056.0f, 32.0f);
	pair<Object*, Object*> rem_fav = createElement("p5_rem_fav", 886.0f, 115.0f);
	Object w = createObject("Graphic/w.png", 317.0f, 196.0f);
	Object t = createObject("Graphic/t.png", 317.0f, 272.0f);
	Object d = createObject("Graphic/d.png", 317.0f, 348.0f);
	Object* border[5];
	Info* name[5], * defi[5];
	LeftRight left_right(1);
	SearchBar do_search;
	Vocabulary new_word;

	int cur_page = 0;
	bool check = true;
	int cur_id = dataset.cur_id;
	int size = 50;
	vector<string> cur_list;
	if (is_normal) {
		cur_list = autocomplete(dataset.user_Trie[cur_id], result_word, 50);
		vector<string> correct_list = correct_words(dataset.user_Trie[cur_id], result_word, 50);
		for (auto s1 : correct_list) {
			bool isExist = false;
			for (auto s2 : cur_list) {
				if (s1 == s2) {
					isExist = true;
					break;
				}
			}
			if (!isExist) cur_list.push_back(s1);
		}
	}
	else {
		cur_list = search_def(dataset.def_Trie[cur_id], result_word, 50);
	}
	size = min(size, (int)cur_list.size());
	//-------------------------------------------------------------------
	for (int i = 0; i < 5; i++)
	{
		border[i] = createObjectTest("Graphic/bar.png", 360.0f, 178.0f + 110.0f * i);
		name[i] = createInfoTest("Graphic/Roboto-Medium.ttf", "", 390.0f, 190.0f + 110.0f * i, 23);
		defi[i] = createInfoTest("Graphic/RobotoCondensed-Regular.ttf", "", 390.0f, 225.0f + 110.0f * i, 17);
	}
	int size_searchBar = min(3, (int)dataset.history.size());
	for (int i = 0; i < size_searchBar; ++i) {
		do_search.result[i]->s = dataset.history[i];
		do_search.result[i]->text.setString(dataset.history[i]);
	}
	int search_status = 0, add_status = 0, count = 0;
	bool isBreak = false;
	Event event;

	while (page == 12)
	{
		if (check)
		{

			for (int i = 0; i < 5; i++)
			{
				if (i + cur_page * 5 >= size)
					break;
				name[i]->s = cur_list[i + cur_page * 5];
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
		check = false;
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{

			switch (event.type)
			{
			case Event::Closed:
			{
				page = 0;
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(del.first->bound, mouse, 1, page);
					switchPage(revision.first->bound, mouse, 7, page);
					switchPage(fav.first->bound, mouse, 6, page);
					switchPage(home1.bound, mouse, 4, page);
					switchPage(do_search.search_history.first->bound, mouse, 13, page);
					switchPage(user.first->bound, mouse, 11, page);
					switchPage(settings.first->bound, mouse, 8, page);
					if (search_status == 1) {
						for (int i = 0; i < size_searchBar; i++) {
							if (isHere(do_search.SE[i], mouse) && !do_search.result[i]->s.empty()) {
								search_status = 0;
								page = 5;
								for (int j = 0; j < dataset.history.size(); j++) {
									if (dataset.history[j] == do_search.result[i]->s) {
										dataset.history.erase(dataset.history.begin() + j);
										break;
									}
								}
								dataset.history.insert(dataset.history.begin(), do_search.result[i]->s);
								//update(dataset.username, WHAT_LIST, dataset.history, path);
								if (dataset.is_admin)
									wordDisplayAdmin(window, page, is_fav, dataset, do_search.result[i]->s);
								else
									wordDisplay(window, page, is_fav, dataset, do_search.result[i]->s);
								isBreak = true;
								break;
							}
						}
					}
					if (isHere(left_right.left[2], mouse) && cur_page > 0)
					{
						cur_page--;
						check = true;
					}
					else if (isHere(left_right.right[2], mouse) && (cur_page + 1) * 5 < size)
					{
						cur_page++;
						check = true;
					}
					if (isHere(do_search.switch_dict.left, mouse))
					{
						count = (count == 0 ? 0 : count - 6);
					}
					else if (isHere(do_search.switch_dict.right, mouse))
					{
						count = (count < dataset.user_Trie.size() - 6 ? count + 6 : count);
					}
					else if (search_status == 2)
					{
						typingWhat(d, w, t, mouse, do_search);
					}
					else if (isHere(do_search.search_normal.bound, mouse))
					{
						do_search.is_normal ^= 1;
					}
					else if(search_status == 0) {
						for (int i = 0; i < 5; i++)
						{
							if (i + cur_page * 5 >= size)
								break;
							if (isHere(border[i], mouse) && !name[i]->s.empty())
							{ // word display
								for (int j = 0; j < dataset.history.size(); j++) {
									if (dataset.history[j] == name[i]->s) {
										dataset.history.erase(dataset.history.begin() + j);
										break;
									}
								}
								dataset.history.insert(dataset.history.begin(), name[i]->s);
								//update(dataset.username, WHAT_LIST, dataset.history, path);
								page = 5;
								wordDisplay(window, page, is_fav, dataset, name[i]->s);
								isBreak = true;
								break;
							}
						}
						if (isBreak) break;
					}
				}
				break;
			}
			case Event::TextEntered:
			{
				if (search_status == 1)
				{
					if (event.text.unicode == 13) {
						if (do_search.is_normal) {
							if (do_search.result[0]->s == "") {
								page = 12;
								searchResult(window, page, do_search.search_info->s, dataset, is_fav, 0, 1);
							}
							else {
								page = 12;
								searchResult(window, page, do_search.result[0]->s, dataset, is_fav, do_search.result[0]->s == do_search.search_info->s, 1);
							}
						}
						else {
							page = 12;
							searchResult(window, page, do_search.search_info->s, dataset, is_fav, 0, 0);
						}
						isBreak = true;
						break;
					}
					texting(do_search.search_info, event.text.unicode, 30);
					vector<string> completeList(0);
					vector<string> correctList(0);
					if (do_search.is_normal) {
						completeList = autocomplete(dataset.user_Trie[dataset.cur_id], do_search.search_info->s, 3);
						correctList = correct_words(dataset.user_Trie[dataset.cur_id], do_search.search_info->s, 3);
						for (auto s : correctList)
						{
							bool isExist = false;
							for (auto t : completeList) {
								if (t == s) {
									isExist = true;
									break;
								}
							}
							if (!isExist) completeList.push_back(s);
						}
					}
					else {
						completeList = search_def(dataset.def_Trie[dataset.cur_id], do_search.search_info->s, 3);
					}
					for (int i = 0; i < 3; i++)
					{
						do_search.result[i]->s = "";
						do_search.result[i]->text.setString("");
					}

					if (do_search.search_info->s.empty()) {
						size_searchBar = min(3, (int)dataset.history.size());
						int temp = 0;
						for (int i = 0; i < size_searchBar && temp < dataset.history.size(); ++i) {
							bool found = false;
							while (!found && temp < dataset.history.size()) {
								string w = dataset.history[temp];
								Node* info = search(dataset.user_Trie[cur_id], w);
								if (!info || info->definitions.empty()) {
									temp++;
								}
								else {
									do_search.result[i]->s = w;
									do_search.result[i]->text.setString(w);
									found = true;
									temp++;
								}
							}

						}
					}
					else {
						size_searchBar = min(3, (int)completeList.size());
						for (int i = 0; i < size_searchBar; ++i) {
							do_search.result[i]->s = completeList[i];
							do_search.result[i]->text.setString(completeList[i]);
						}
					}


				}
				else if (search_status == 2)
				{
					texting_endl(do_search.enter_defi, event.text.unicode, 36);
					texting(do_search.enter_word, event.text.unicode, 30);
					texting(do_search.enter_type, event.text.unicode, 30);
				}
				else {

				}
				break;
			}
			case Event::KeyReleased:
				if (event.key.code == Keyboard::F && search_status < 1)
				{
					search_status = 1;
					do_search.search_info->check = true;
				}
				else if (event.key.code == Keyboard::Escape)
				{
					search_status = 0;
					do_search.search_info->s = "";
					do_search.search_info->text.setString("");
				}
				break;
			default:
				break;
			}
			if (isBreak) break;
		}
		if (isBreak) break;
		window.clear();
		window.draw(screen.draw);
		window.draw(home1.draw);
		drawWhich(window, settings, mouse);
		drawWhich(window, revision, mouse);
		drawWhich(window, fav, mouse);
		drawWhich(window, user, mouse);
		drawWhich(window, del, mouse);
		left_right.draw(window, mouse, 0);
		left_right.draw(window, mouse, 2);
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
		}
		window.draw(word->text);
		int check_search = searching(window, search_status, do_search, mouse, add_status, dataset, event, count, new_word);
		if (check_search == 1)
		{
			// added new word
		}
		else if (check_search > 0)
		{
			// switch to other dictionary
		}
		window.display();
	}
	deallocate(home);
	deallocate(settings);
	deallocate(revision);
	deallocate(fav);
	deallocate(user);
	deallocate(del);
	left_right.deleteLR();
	deallocate(rem_fav);
	delete word;
	for (int i = 0; i < 5; i++)
	{
		delete border[i], name[i], defi[i];
	}
}

void myList(RenderWindow &window, int &page, Enlighten &dataset)
{
	// page = 6: favorite list
	// page = 13: history list
	bool is_fav = (page == 6);
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
	pair<Object *, Object *> clear = createElement("clear", 886.0f, 120.0f);
	pair<Object *, Object *> rem_fav = createElement("p5_rem_fav", 886.0f, 115.0f);
	Object w = createObject("Graphic/w.png", 317.0f, 196.0f);
	Object t = createObject("Graphic/t.png", 317.0f, 272.0f);
	Object d = createObject("Graphic/d.png", 317.0f, 348.0f);
	Object *border[5];
	pair<Object *, Object *> rem[5];
	Info *name[5], *defi[5];
	LeftRight left_right(1);
	SearchBar do_search;
	Vocabulary new_word;

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
	vector<pair<string, int>> show_list;
	for (int i = 0; i < cur_list.size(); i++) {
		string s = cur_list[i];
		Node* defi_search = search(dataset.user_Trie[cur_id], s);
		if (defi_search && defi_search->def.size())
			show_list.push_back({ s, i });
	}
	size = min(size, (int)show_list.size());
	//-------------------------------------------------------------------
	for (int i = 0; i < 5; i++)
	{
		rem[i] = createElement("del", 980.0f, 210.0f + 110.0f * i);
		border[i] = createObjectTest("Graphic/bar.png", 360.0f, 178.0f + 110.0f * i);
		name[i] = createInfoTest("Graphic/Roboto-Medium.ttf", "", 390.0f, 190.0f + 110.0f * i, 23);
		defi[i] = createInfoTest("Graphic/RobotoCondensed-Regular.ttf", "", 390.0f, 225.0f + 110.0f * i, 17);
	}

	Event event;
	int size_searchBar = min(3, (int)dataset.history.size());
	int temp = 0;
	for (int i = 0; i < size_searchBar && temp < dataset.history.size(); ++i) {
		bool found = false;
		while (!found && temp < dataset.history.size()){
			string w = dataset.history[temp];
			Node* info = search(dataset.user_Trie[cur_id], w);
			if (!info || info->user_definitions.empty()) {
				temp++;
			}
			else {
				do_search.result[i]->s = w;
				do_search.result[i]->text.setString(w);
				found = true;
				temp++;
			}
		}
		
	}
	int search_status = 0, add_status = 0, count = 0;
	bool isBreak = false;
	while (page == 6 || page == 13)
	{
		if (check)
		{
			for (int i = 0; i < 5; i++)
			{
				if (i + cur_page * 5 >= size)
					break;
				name[i]->s = show_list[i + cur_page * 5].first;
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
				page = 0;
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(del.first->bound, mouse, 1, page);
					switchPage(user.first->bound, mouse, 11, page);
					switchPage(home1.bound, mouse, 4, page);
					if (is_fav && switchPage(do_search.search_history.first->bound, mouse, 13, page)) {
						isBreak = true;
						break;
					}
					if (!is_fav && switchPage(fav.first->bound, mouse, 6, page)) {
						isBreak = true;
						break;
					}
					if (search_status == 1) {
						for (int i = 0; i < size_searchBar; i++) {
							if (isHere(do_search.SE[i], mouse) && !do_search.result[i]->s.empty()) {
								search_status = 0;
								page = 5;
								for (int j = 0; j < dataset.history.size(); j++) {
									if (dataset.history[j] == do_search.result[i]->s) {
										dataset.history.erase(dataset.history.begin() + j);
										break;
									}
								}
								
								dataset.history.insert(dataset.history.begin(), do_search.result[i]->s);
								if (dataset.is_admin)
									wordDisplayAdmin(window, page, is_fav, dataset, do_search.result[i]->s);
								else
									wordDisplay(window, page, is_fav, dataset, do_search.result[i]->s);
								isBreak = true;
								break;
							}
						}
						if (isBreak) break;
					}
					switchPage(settings.first->bound, mouse, 8, page);
					if (isHere(do_search.switch_dict.left, mouse))
					{
						count = (count == 0 ? 0 : count - 6);
					}
					else if (isHere(do_search.switch_dict.right, mouse))
					{
						count = (count < dataset.user_Trie.size() - 6 ? count + 6 : count);
					}
					else if (search_status == 2)
					{
						typingWhat(d, w, t, mouse, do_search);
					}
					else if (isHere(do_search.search_normal.bound, mouse))
					{
						do_search.is_normal ^= 1;
					}
					// switchPage(search_history.first->bound, mouse, x, page);
					switchPage(revision.first->bound, mouse, 7, page);
					if (search_status == 0) {
						for (int i = 0; i < 5; i++)
						{
							if (i + cur_page * 5 >= size)
								break;
							if (isHere(border[i], mouse) && !name[i]->s.empty())
							{ // word display
								page = 5;
								if (dataset.is_admin)
									wordDisplayAdmin(window, page, is_fav, dataset, name[i]->s);
								else
									wordDisplay(window, page, is_fav, dataset, name[i]->s);
								isBreak = true;
								break;
							}
							if (isHere(rem[i], mouse)) // del 1 defi
							{
								size--;
								if (size % 5 == 0 && cur_page > 0)
								{
									cur_page--;
								}
								check = true;
								cur_list.erase(cur_list.begin() + show_list[i + cur_page * 5].second);
								show_list.erase(show_list.begin() + i + cur_page * 5);
								// update(dataset.username, WHAT_LIST, cur_list, path);
							}
						}
					}
					if (isBreak) break;
					if (isHere(clear, mouse))
					{ // clear all
						cur_list.clear();
						show_list.clear();
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
			case Event::TextEntered:
			{
				if (search_status == 1)
				{
					if (event.text.unicode == 13) {
						if (do_search.is_normal) {
							if (do_search.result[0]->s == "") {
								page = 12;
								searchResult(window, page, do_search.search_info->s, dataset, is_fav, 0, 1);
							}
							else {
								page = 12;
								searchResult(window, page, do_search.result[0]->s, dataset, is_fav, do_search.result[0]->s == do_search.search_info->s, 1);
							}
						}
						else {
							page = 12;
							searchResult(window, page, do_search.search_info->s, dataset, is_fav, 0, 0);
						}
						isBreak = true;
						break;
					}
					texting(do_search.search_info, event.text.unicode, 30);
					vector<string> completeList;
					vector <string> correctList;
					if (do_search.is_normal) {
						completeList = autocomplete(dataset.user_Trie[dataset.cur_id], do_search.search_info->s, 3);
						correctList = correct_words(dataset.user_Trie[dataset.cur_id], do_search.search_info->s, 3);
						for (auto s : correctList)
						{
							bool isExist = false;
							for (auto t : completeList) {
								if (t == s) {
									isExist = true;
									break;
								}
							}
							if (!isExist) completeList.push_back(s);
						}
					}
					else {
						completeList = search_def(dataset.def_Trie[dataset.cur_id], do_search.search_info->s, 3);
					}
					for (int i = 0; i < 3; i++)
					{
						do_search.result[i]->s = "";
						do_search.result[i]->text.setString("");
					}

					if (do_search.search_info->s.empty()) {
						size_searchBar = min(3, (int)dataset.history.size());
						int temp = 0;
						for (int i = 0; i < size_searchBar && temp < dataset.history.size(); ++i) {
							bool found = false;
							while (!found && temp < dataset.history.size()) {
								string w = dataset.history[temp];
								Node* info = search(dataset.user_Trie[cur_id], w);
								if (!info || info->user_definitions.empty()) {
									temp++;
								}
								else {
									do_search.result[i]->s = w;
									do_search.result[i]->text.setString(w);
									found = true;
									temp++;
								}
							}

						}
					}
					else {
						size_searchBar = min(3, (int)completeList.size());
						for (int i = 0; i < size_searchBar; ++i) {
							do_search.result[i]->s = completeList[i];
							do_search.result[i]->text.setString(completeList[i]);
						}
					}


				}
				else if (search_status == 2)
				{
					texting_endl(do_search.enter_defi, event.text.unicode, 36);
					texting(do_search.enter_word, event.text.unicode, 30);
					texting(do_search.enter_type, event.text.unicode, 30);
				}
				else {

				}
				break;
			}
			case Event::KeyReleased:
				if (event.key.code == Keyboard::F && search_status < 1)
				{
					search_status = 1;
					do_search.search_info->check = true;
				}
				else if (event.key.code == Keyboard::Escape)
				{
					search_status = 0;
					do_search.search_info->s = "";
					do_search.search_info->text.setString("");
				}
				break;
			default:
				break;
			}
			if (isBreak) break;
		}
		if (isBreak) break;
		window.clear();
		window.draw(screen.draw);
		window.draw(home1.draw);
		drawWhich(window, settings, mouse);
		drawWhich(window, revision, mouse);
		drawWhich(window, fav, mouse);
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
		int check_search = searching(window, search_status, do_search, mouse, add_status, dataset, event, count, new_word);
		if (check_search == 1)
		{
			// added new word
		}
		else if (check_search > 0)
		{
			// switch to other dictionary
		}
		window.display();
	}
	deallocate(home);
	deallocate(settings);
	deallocate(revision);
	deallocate(fav);
	deallocate(user);
	deallocate(del);
	left_right.deleteLR();
	deallocate(clear);
	deallocate(rem_fav);
	delete word;
	for (int i = 0; i < 5; i++)
	{
		delete border[i], name[i], defi[i], rem[i];
	}
}
