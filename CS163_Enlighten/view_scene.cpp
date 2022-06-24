#pragma once
#include "header.h"

void wordDisplay(RenderWindow& window, int& page, const bool& is_admin, bool& is_fav, Enlighten& dataset, string word_here)
{
	Object screen = createObject("Graphic/p5_border.png");
	// Object settings1 = createObject("Graphic/settings1.png", 0.0f, 448.0f);
	// Object revision1 = createObject("Graphic/revision1.png", 0.0f, 308.0f);
	int cur_id = dataset.cur_id;
	vector <string> all_defi = search_result(dataset.user_Trie[cur_id], word_here, 20);
	int defi_id = -1;
	string path;
	if (dataset.is_admin) path = ADMIN;
	else path = USERS;
	string cur_defi = "";
	if (all_defi.size()) {
		cur_defi = all_defi[0];
		defi_id = 0;

	}
	int id_fav_word = -1;
	bool is_fav_word = inVector(word_here, dataset.favorite, id_fav_word);
	Info word = createInfo("Graphic/Roboto-Regular.ttf", word_here, 380.0f, 180.0f, 64);
	Info definition = createInfo("Graphic/Roboto-Regular.ttf", cur_defi, 380.0f, 264.0f, 26);
	Info word_type = createInfo("Graphic/Roboto-Regular.ttf", "(" /*+ "word type" +*/, 390.0f + definition.bound.width, 210.0f, 30);
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
	Object *border[3];
	LeftRight left_right;
	Info *name[3], *defi[3];
	for (int i = 0; i < 3; i++)
	{
		border[i] = createObjectTest("Graphic/p5_info_bar.png", 397.0f, 378.0f + 110.0f * i);
		name[i] = createInfoTest("Graphic/Roboto-Regular.ttf", "demo username", 426.0f, 396.0f + 110.0f * i, 18);
		defi[i] = createInfoTest("Graphic/RobotoCondensed-Bold.ttf", "demo definition here", 426.0f, 420.0f + 110.0f * i, 25);
	}
	Event event;
	changePos(add.second, 260.0f, 26.0f);
	
	definition.s = cur_defi;
	definition.text.setString(definition.s);
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
				}
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
		//window.draw(definition.text);
		for (int i = 0; i < 3; i++)
		{
			window.draw(border[i]->draw);
			window.draw(name[i]->text);
			window.draw(defi[i]->text);
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
	if (dataset.is_admin) path = ADMIN;
	else path = USERS;
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
					{ // del 1 defi
						if (i + cur_page * 5 >= size)
							break;
						if (isHere(rem[i], mouse))
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
			//window.draw(defi[i]->text);
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

