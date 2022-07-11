#include "header.h"
#include "test_function.h"

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
	dataset.user_Trie[cur_id].isChanged = true;
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
	pair<Object*, Object*> add_to_fav = createElement("p5_add_fav", 886.0f, 115.0f);
	pair<Object*, Object*> rem_fav = createElement("p5_rem_fav", 886.0f, 115.0f);
	pair<Object*, Object*> deleteB[3];
	pair<Object*, Object*> like[3];
	pair<Object*, Object*> dislike[3];
	int like_status[3] = { 0, 0, 0 };
	Object w = createObject("Graphic/w.png", 317.0f, 196.0f);
	Object t = createObject("Graphic/t.png", 317.0f, 272.0f);
	Object d = createObject("Graphic/d.png", 317.0f, 348.0f);
	Edit edit_word(word_here, word_type.text.getString());
	Vocabulary existed_word;
	Object* border[3];
	LeftRight left_right;
	Info* name[3], * defi[3];
	Info* like_count[3];
	Info* like_count_here[3];
	Info* dislike_count[3];
	Info* dislike_count_here[3];
	Object* special[3];
	SearchBar do_search;
	Vocabulary new_word;
	int index = 0;
	for (int i = 0; i < 3; i++)
	{
		deleteB[i] = createElement("del", 980.0f, 410.0f + 110.0f * i);
		like[i] = createElement("like", 873.0f, 417.0f + 110.0f * i);
		dislike[i] = createElement("dislike", 926.0f, 417.0f + 110.0f * i);
		like_count[i] = createInfoTest("Graphic/VNI-Vari.TTF", "0", 900.0f, 417.0f + 110.0f * i, 17);
		like_count_here[i] = createInfoTest("Graphic/VNI-Vari.TTF", "0", 900.0f, 417.0f + 110.0f * i, 17);
		dislike_count[i] = createInfoTest("Graphic/VNI-Vari.TTF", "0", 952.0f, 417.0f + 110.0f * i, 17);
		dislike_count_here[i] = createInfoTest("Graphic/VNI-Vari.TTF", "0", 952.0f, 417.0f + 110.0f * i, 17);

		border[i] = createObjectTest("Graphic/p5_info_bar.png", 397.0f, 378.0f + 110.0f * i);
		name[i] = createInfoTest("Graphic/Roboto-Regular.ttf", "demo username", 426.0f, 396.0f + 110.0f * i, 18);
		defi[i] = createInfoTest("Graphic/RobotoCondensed-Bold.ttf", "demo definition here", 426.0f, 420.0f + 110.0f * i, 25);
		like_count[i]->text.setFillColor(Color(113, 171, 177, 255));
		like_count_here[i]->text.setFillColor(Color(73, 101, 104, 255));
		dislike_count[i]->text.setFillColor(Color(113, 171, 177, 255));
		dislike_count_here[i]->text.setFillColor(Color(73, 101, 104, 255));
		special[i] = createObjectTest("Graphic/p_top.png", 375.0f, 375.0f + 110.0f * i);

	}
	Event event;

	bool flag = false, is_fixed = false, is_okay = false;
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
					if (isHere(edit_word.fixed.bound, mouse))
						is_fixed ^= 1;
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
					for (int i = 0; i < 3; i++)
					{
						int id = i + user_cur_page * 3;
						if (id >= user_defi.size())
							break;
						//if (isHere(deleteB[i], mouse) && (is_admin || user_defi[id].username == dataset.username))
						//{
						//	// delete user_definition
						//	sort_user_list = true;
						//	user_defi.erase(user_defi.begin() + id);
						//	if (!writeJson(dataset.user_Trie[cur_id], JSONPATH))
						//		cout << "Can't write file " << JSONPATH << endl;
						//	else {
						//		cout << "Update " << JSONPATH << ": OK\n";
						//	}
						//}
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
					if (admin.status == Admin::State::Open)
					{
						admin.status = Admin::State::DoSth;
						if (isHere(admin.add, mouse) && user_cur_page * 3 < (int)user_defi.size())
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
						else if (isHere(admin.del, mouse) && user_cur_page * 3 < (int) user_defi.size())
						{
							admin.button = Admin::AButton::Del;
						}
						else
						{
							admin.status = Admin::State::Open;
						}
					}
					else if (admin.status == Admin::State::DoSth)
					{
						if (isHere(admin.choose, mouse))
						{
							admin.status = Admin::State::Open;
						}
						switch (admin.button)
						{
						case Admin::AButton::Add:
							for (int i = 0; i < 3; i++)
							{
								int id_c = i + user_cur_page * 3;
								if (id_c >= user_defi.size())
									break;
								if (isHere(admin.p_add[i], mouse))
								{
									check = -1;
									index = i;
								}
							}
							break;
						case Admin::AButton::Del:
							for (int i = 0; i < 3; i++)
							{
								int id_c = i + user_cur_page * 3;
								if (id_c >= user_defi.size())
									break;
								if (isHere(admin.p_del[i], mouse))
								{
									check = -1;
									index = i;
								}
							}
							break;
						case Admin::AButton::Rem:
							if (isHere(admin.p_rem, mouse))
							{
								check = -1;
								index = -1;
								//index = i;
							}
							break;
						default:
							break;
						}
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
			case Event::KeyPressed:
			{
				if ((event.key.code == Keyboard::LControl || event.key.code == Keyboard::RControl) && admin.status == Admin::State::Close)
				{
					admin.status = Admin::State::Open;
					is_okay = true;
				}

				break;
			}
			case Event::KeyReleased:
			{
				if (event.key.code == Keyboard::Backspace || event.key.code == Keyboard::Delete)
				{
					if ((int)admin.status == 2 && check == 0)
						admin.status = Admin::State::Close;
				}
				else if (event.key.code == Keyboard::F && search_status < 1 && admin.status == Admin::State::Close)
				{
					search_status = 1;
					do_search.search_info->check = true;
				}
				else if (event.key.code == Keyboard::Escape && admin.status == Admin::State::Close)
				{
					search_status = 0;
					do_search.search_info->s = "";
					do_search.search_info->text.setString("");
				}
				else if ((event.key.code == Keyboard::LControl || event.key.code == Keyboard::RControl))
				{
					is_okay = false;
				}
				else if (admin.status == Admin::State::Open)
				{
					admin.status = Admin::State::DoSth;
					if (event.key.code == Keyboard::Num1 && user_cur_page * 3 < (int)user_defi.size())
					{
						admin.button = Admin::AButton::Add;
					}
					else if (event.key.code == Keyboard::Num2)
					{
						admin.button = Admin::AButton::Edit;
						flag = true;
						edit_word.reset(existed_word);
						check = -1;
					}
					else if (event.key.code == Keyboard::Num3)
					{
						admin.button = Admin::AButton::Rem;
					}
					else if (event.key.code == Keyboard::Num4 && user_cur_page * 3 < (int)user_defi.size())
					{
						admin.button = Admin::AButton::Del;
					}
					else
					{
						admin.status = Admin::State::Open;
					}
				}
				break;
			}
			
			default:
				break;
			}
			if (isBreak) break;
		}
		if (isBreak) break;
		window.clear();
		window.draw(screen.draw);
		window.draw(home1.draw);
		if (admin.status == Admin::State::Close)
		{
		drawWhich(window, settings, mouse);
		drawWhich(window, revision, mouse);
		}
		else
		{
			window.draw(settings.first->draw);
			window.draw(revision.first->draw);
		}
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
		window.draw(search_bar.draw);
		window.draw(word.text);
		if (all_defi.empty() || defi_id == -1) {
			defi_id = -1;
			definition.s = "";
			definition.text.setString(definition.s);
		}
		else if (defi_id >= 0 && defi_id < all_defi.size()) {
			definition.s = all_defi[defi_id];
			definition.text.setString(definition.s);
		}
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
			/*if (is_admin || user_defi[id].username == dataset.username)
				drawWhich(window, deleteB[i], mouse);*/

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
		int check_me = edit_word.draw(window, mouse, flag, check, existed_word, true, is_fixed);

		if (check_me == 1)
		{
			if (!edit_word.enter_type.s.empty() && edit_word.enter_type.s[0] != '(')
				edit_word.enter_type.s = '(' + edit_word.enter_type.s + ") ";
			user_defi.push_back(UserDef(dataset.username, edit_word.enter_type.s + edit_word.enter_defi.s));
			// them dinh nghia cua nguoi dung
			// sua file data ?
			/*if (!writeJson(dataset.user_Trie[cur_id], JSONPATH))
				cout << "Can't write file " << JSONPATH << endl;
			else {
				cout << "Update " << JSONPATH << ": OK\n";
			}*/
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
			defi_id = all_defi.size() - 1;
			word_type.s = existed_word.type;
			definition.text.setString(definition.s);
			word_type.text.setString(word_type.s);
			
			// sua file data here
			/*if (!writeJson(dataset.user_Trie[cur_id], JSONPATH))
				cout << "Can't write file " << JSONPATH << endl;
			else {
				cout << "Update " << JSONPATH << ": OK\n";
			}*/
		}
		bool done = admin.draw(is_okay, window, mouse, check, (int)user_defi.size(), user_cur_page, index, flag);
		if (done) cout << " ok\n";
		if (done)
		{
			// index: index cua user_def can thao tac
			switch (admin.button)
			{
			case Admin::AButton::Add:{
				if (index < user_defi.size())
				{
					string insert_word = word_here;
					string insert_type = cutWordtype(user_defi[index].definition);
					string insert_defi = cutDefinition(user_defi[index].definition);
					insert(dataset.user_Trie[cur_id], insert_word, insert_type, insert_defi);
					defi_id = all_defi.size() - 1;
					/*word_type.s = existed_word.type;
					definition.text.setString(definition.s);
					word_type.text.setString(word_type.s);*/
					// sua file data
					/*if (!writeJson(dataset.user_Trie[cur_id], JSONPATH))
						cout << "Can't write file " << JSONPATH << endl;
					else {
						cout << "Update " << JSONPATH << ": OK\n";
					}*/
				}
				break;
			}
			case Admin::AButton::Del:{
				if (index < user_defi.size())
				{

					int id = index;
					sort_user_list = true;
					user_defi.erase(user_defi.begin() + id);
					// sua file data
					/*if (!writeJson(dataset.user_Trie[cur_id], JSONPATH))
						cout << "Can't write file " << JSONPATH << endl;
					else {
						cout << "Update " << JSONPATH << ": OK\n";
					}*/

					/*for (int i = 0; i < 3; i++)
					{
						int id = i + user_cur_page * 3;
						if (id >= user_defi.size())
							break;
						if (event.mouseButton.button == Mouse::Left && isHere(deleteB[i], mouse))
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
					}*/
				}
				break;
			}
			case Admin::AButton::Rem:
			{
				/*string remove_word = word_here;
				string remove_type = cutWordtype(user_defi[index].definition);
				string remove_defi = cutDefinition(user_defi[index].definition);*/

				//  ham remove definition khoi trie ?
				//	insert(dataset.user_Trie[cur_id], insert_word, insert_type, insert_defi);
				if (all_defi.size() && defi_id >= 0 && defi_id < all_defi.size()) {
					all_defi.erase(all_defi.begin() + defi_id);
					//defi_id = 0;
					if (defi_id >= all_defi.size()) defi_id--;
					//cout << all_defi.size() << endl;
					// sua file data
						/*if (!writeJson(dataset.user_Trie[cur_id], JSONPATH))
							cout << "Can't write file " << JSONPATH << endl;
						else {
							cout << "Update " << JSONPATH << ": OK\n";
						}*/
				}
				else {
					// invalid   
				}
				break;
			}
			default:
				break;
			}
		}
		int check_search = searching((int)admin.status, window, search_status, do_search, mouse, add_status, dataset, event, count, new_word);
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
	admin.deleteButton();
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