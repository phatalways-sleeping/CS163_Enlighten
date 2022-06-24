#pragma once
#include "header.h"

// maximum 10 trees
void Scene1(RenderWindow &window, int &page, Enlighten &dataset)
{
	pair<Object *, Object *> b1 = createElement("p1_search", 478.0f, 540.0f);
	Event event;
	Object screen = createObject("Graphic/p1.png");
	while (page == 1)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				deallocate(b1);
				return;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(b1.first->bound, mouse, 2, page);
				}
				break;
			}
			default:
				break;
			}
		}
		window.clear();
		window.draw(screen.draw);
		drawWhich(window, b1, mouse);
		window.display();
	}
	deallocate(b1);
}

void revision(RenderWindow &window, int &page, Enlighten &dataset)
{
	Object screen = createObject("Graphic/p7.png");
	Object *text = createObjectTest("Graphic/p7_text1.png", 360.0f, 278.0f);
	Object *text2 = createObjectTest("Graphic/p7_text2.png", 360.0f, 278.0f);
	pair<Object *, Object *> b1 = createElement("p7_start", 360.0f, 377.0f);
	Object revision1 = createObject("Graphic/revision1.png", 0.0f, 308.0f);
	pair<Object *, Object *> home = createElement("home", 0.0f, 168.0f);
	pair<Object *, Object *> settings = createElement("settings", 0.0f, 448.0f);
	pair<Object *, Object *> fav = createElement("p4_fav", 963.0f, 31.0f);
	pair<Object *, Object *> user = createElement("p4_user", 1010.0f, 30.0f);
	pair<Object *, Object *> del = createElement("p4_del", 1056.0f, 32.0f);
	pair<Object *, Object *> pLeft = createElement("left", 352.0f, 130.0f);
	pair<Object *, Object *> pRight = createElement("right", 376.0f, 130.0f);
	pair<Object *, Object *> easy = createElement("easy", 360.0f, 360.0f);
	pair<Object *, Object *> medium = createElement("med", 360.0f, 467.0f);
	pair<Object *, Object *> hard = createElement("hard", 360.0f, 574.0f);
	bool difficulty = true;
	Event event;
	while (page == 7)
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
					// switchPage(b1.first->bound, mouse, 2, page);
					switchPage(home.first->bound, mouse, 4, page);

					if (isHere(b1, mouse) && difficulty)
					{
						difficulty = false;
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
		drawWhich(window, del, mouse);
		drawWhich(window, settings, mouse);
		drawWhich(window, fav, mouse);
		drawWhich(window, home, mouse);
		drawWhich(window, user, mouse);
		window.draw(revision1.draw);
		drawWhich(window, b1, mouse);
		drawWhich(window, pLeft, mouse);
		drawWhich(window, pRight, mouse);
		if (!difficulty)
		{
			window.draw(text2->draw);
			drawWhich(window, easy, mouse);
			drawWhich(window, hard, mouse);
			drawWhich(window, medium, mouse);
		}
		else
		{
			drawWhich(window, b1, mouse);
			window.draw(text->draw);
		}
		window.display();
	}
	deallocate(easy);
	deallocate(hard);
	deallocate(medium);
	delete text, text2;
	deallocate(b1);
	deallocate(del);
	deallocate(settings);
	deallocate(fav);
	deallocate(home);
	deallocate(pLeft);
	deallocate(pRight);
	deallocate(user);
}

// chua co xong nheeeee
void settings(RenderWindow &window, int &page, const bool &is_admin, Enlighten &dataset)
{
	Object screen = createObject("Graphic/border.png");
	pair<Object *, Object *> home = createElement("home", 0.0f, 168.0f);
	pair<Object *, Object *> fav = createElement("p4_fav", 963.0f, 31.0f);
	pair<Object *, Object *> user = createElement("p4_user", 1010.0f, 30.0f);
	pair<Object *, Object *> del = createElement("p4_del", 1056.0f, 32.0f);
	pair<Object *, Object *> pLeft = createElement("left", 352.0f, 130.0f);
	pair<Object *, Object *> pRight = createElement("right", 376.0f, 130.0f);
	Object settings1 = createObject("Graphic/settings1.png", 0.0f, 448.0f);
	pair<Object *, Object *> revision = createElement("revision", 0.0f, 308.0f);
	pair<Object *, Object *> bar[3];
	Info word = createInfo("Graphic/bahnschrift.ttf", "Settings", 402.0f, 127.0f, 21);
	Confirmation confirm = create();
	for (int i = 0; i < 3; i++)
	{
		bar[i] = createElement("p8_" + to_string(i + 1), 360.0f, 267.0f + 125.0f * i);
	}
	Event event;
	int check = 0;
	while (page == 8)
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
					// switchPage(b1.first->bound, mouse, 2, page);
					switchPage(home.first->bound, mouse, 4, page);
					// switchPage(revision.first->bound, mouse, 7, page);
					if (isHere(bar[0], mouse) && check == 0)
					{
						check = -1;
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
		window.draw(word.text);
		drawWhich(window, del, mouse);
		drawWhich(window, revision, mouse);
		drawWhich(window, fav, mouse);
		drawWhich(window, home, mouse);
		drawWhich(window, user, mouse);
		window.draw(settings1.draw);
		if (!check)
		{
			for (int i = 0; i < 3; i++)
			{
				drawWhich(window, bar[i], mouse);
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				window.draw(bar[i].first->draw);
			}
		}
		drawWhich(window, pLeft, mouse);
		drawWhich(window, pRight, mouse);
		checkConfirmation(window, check, confirm, mouse);
		window.display();
	}
	for (int i = 0; i < 3; i++)
	{
		deallocate(bar[i]);
	}
	deallocate(del);
	deallocate(fav);
	deallocate(home);
	deallocate(pLeft);
	deallocate(pRight);
	deallocate(user);
	deallocate(confirm);
}

void setRole(RenderWindow &window, int &page, bool &is_admin, Enlighten &dataset)
{
	Object screen = createObject("Graphic/p3.png");
	pair<Object *, Object *> admin = createElement("p3_admin", 572.0f, 263.0f);
	pair<Object *, Object *> user = createElement("p3_user", 222.0f, 263.0f);
	Event event;
	while (page == 2)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				deallocate(admin);
				deallocate(user);
				window.close();
				return;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(user.first->bound, mouse, 3, page, is_admin, false);
					switchPage(admin.first->bound, mouse, 3, page, is_admin, true);
				}
				break;
			}
			default:
				break;
			}
		}
		window.clear();
		window.draw(screen.draw);
		drawWhich(window, admin, mouse);
		drawWhich(window, user, mouse);
		window.display();
	}
	deallocate(admin);
	deallocate(user);
}

void home(RenderWindow &window, int &page, bool &is_admin, const string &user_name, bool &is_fav, vector<string> history, Enlighten &dataset)
{
	page = 5;
	return;
	Object screen = createObject("Graphic/p4.png");
	Info *sh[12], welcome = createInfo("Graphic/Roboto-Regular.ttf", "Welcome, " + user_name, 354.0f, 186.0f, 64);
	Object home1 = createObject("Graphic/home1.png", 0.0f, 168.0f);
	pair<Object *, Object *> home = createElement("home", 0.0f, 168.0f);
	pair<Object *, Object *> settings = createElement("settings", 0.0f, 448.0f);
	pair<Object *, Object *> revision = createElement("revision", 0.0f, 308.0f);
	pair<Object *, Object *> fav = createElement("p4_fav", 963.0f, 31.0f);
	pair<Object *, Object *> user = createElement("p4_user", 1010.0f, 30.0f);
	pair<Object *, Object *> del = createElement("p4_del", 1056.0f, 32.0f);
	pair<Object *, Object *> search_history = createElement("p4_sh", 364.0f, 434.0f);

	LeftRight left_right;
	SearchBar do_search;
	for (int i = 0; i < 12; i++)
	{
		if (i >= history.size())
		{
			sh[i] = createInfoTest("Graphic/Oswald-Medium.ttf", "", 464.0f, 510.0f, 20);
			continue;
		}
		sh[i] = createInfoTest("Graphic/Oswald-Medium.ttf", history[i], 464.0f, 510.0f, 20);
		changePos(sh[i], 464.0f + 150.0f * (i >= 6), 480.0f + 44.0f * (i % 6));
	}
	int search_status = 0, add_status = 0, count = 0;
	Event event;
	while (page == 4)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				delete fav.first, fav.second;
				return;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(del.first->bound, mouse, 1, page);
					switchPage(search_history.first->bound, mouse, 6, page, is_fav, false);
					switchPage(do_search.search_history.first->bound, mouse, 6, page, is_fav, false);
					switchPage(fav.first->bound, mouse, 6, page, is_fav, true);
					switchPage(revision.first->bound, mouse, 7, page);
					switchPage(settings.first->bound, mouse, 8, page);
					if (isHere(do_search.switch_dict.left, mouse))
					{
						count = (count == 0 ? 0 : count - 6);
					}
					else if (isHere(do_search.switch_dict.right, mouse))
					{
						count = (count < dataset.dictionary_name.size() - 6 ? count + 6 : count);
					}
				}
				break;
			}
			case Event::TextEntered:
			{
				if (search_status == 1)
				{
					texting(do_search.search_info, event.text.unicode, 30);
					vector<string> completeList = autocomplete(dataset.user_Trie[dataset.cur_id], do_search.search_info->s, 3);
					vector<string> correctList = correct_words(dataset.user_Trie[dataset.cur_id], do_search.search_info->s, 3);
					for (auto s : correctList)
						completeList.push_back(s);
					for (int i = 0; i < 3; i++)
					{
						do_search.result[i]->s = "";
						do_search.result[i]->text.setString("");
					}
					int size = min(3, (int)completeList.size());
					for (int i = 0; i < size; ++i)
					{
						do_search.result[i]->s = completeList[i];
						do_search.result[i]->text.setString(completeList[i]);
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
		drawWhich(window, user, mouse);
		drawWhich(window, search_history, mouse);
		drawWhich(window, del, mouse);
		left_right.draw(window, mouse, 0);
		window.draw(welcome.text);
		for (int i = 0; i < 12; i++)
			window.draw(sh[i]->text);
		searching(window, search_status, do_search, mouse, add_status, dataset, event, count);
		window.display();
	}
	deallocate(home);
	deallocate(settings);
	deallocate(revision);
	deallocate(fav);
	deallocate(user);
	deallocate(del);
	left_right.deleteLR();
	deallocate(do_search);
	for (int i = 0; i < 12; i++)
	{
		delete sh[i];
	}
}

void logIn(RenderWindow &window, int &page, const bool &is_admin, string &user_name, vector<string> &history, vector<string> &favourite, Enlighten &dataset)
{
	Event event;
	bool see = false, entered = false, change = false, wrong_password = false;
	Object screen = createObject("Graphic/p2.png");
	Object l1 = createObject("Graphic/p2_login.png", 458.0f, 516.0f);
	Object l2 = createObject("Graphic/p2_login_here.png", 458.0f, 516.0f);
	Object eye = createObject("Graphic/p2_see_here.png", 708.0f, 440.0f);
	Object close = createObject("Graphic/p2_see.png", 708.0f, 440.0f);
	Object out = createObject("Graphic/del.png", 912.0f, 132.0f);
	Object out_here = createObject("Graphic/del_here.png", 912.0f, 132.0f);
	Info username = createInfo("Graphic/Oswald-Light.ttf", "sample_text", 488.0f, 366.0f, 27);
	Info pw = createInfo("Graphic/Oswald-Light.ttf", "12345678", 488.0f, 438.0f, 27);
	Info pw2 = createInfo("Graphic/Oswald-Light.ttf", "********", 488.0f, 438.0f, 27);
	Info wrong = createInfo("Graphic/Oswald-Light.ttf", "Wrong username/password, please try again!", 404.0f, 480.0f, 21);
	// username.check = true;
	// username.s = "sample_text";
	// username.text.setString(username.s);
	while (page == 3)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				return;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(out.bound, mouse, 2, page);
					wrong_password = false;
					if (isHere(l1.bound, mouse))
					{
						change = true;
					}
					else if (isHere(eye.bound, mouse))
					{
						see = !see;
					}

					if (isHere(username.bound, mouse))
					{
						username.check = true;
						pw.check = false;
						pw2.check = false;
					}
					else if (isHere(pw.bound, mouse))
					{
						pw.check = true;
						pw2.check = true;
						username.check = false;
					}
					else
					{
						// co can k :v
						pw.check = false;
						pw2.check = false;
						username.check = false;
					}
				}

				break;
			}
			case Event::TextEntered:
			{
				if (event.text.unicode == 9)
				{ // tab -> doi nhap user sang pass, nguoc lai
					pw.check ^= 1;
					pw2.check ^= 1;
					username.check ^= 1;
				}
				else if (event.text.unicode == 13 || event.text.unicode == '\n')
				{ // -> enter -> login
					change = false;
					if (is_admin)
					{
						if (login(username.s, pw.s, ADMIN, history, favourite))
						{
							user_name = username.s;
							page = 4;
						}
						else
							wrong_password = true;
					}
					else
					{
						if (login(username.s, pw.s, USERS, history, favourite))
						{
							user_name = username.s;
							page = 4;
						}
						else
							wrong_password = true;
					}
				}
				else if (username.check)
				{
					texting(username, event.text.unicode, 15);
				}
				else if (pw.check && (pw.s.size() < 10 || event.text.unicode == 8))
				{
					if (event.text.unicode == 8)
					{
						if (!pw.s.empty())
						{
							pw.s.pop_back();
							pw2.s.pop_back();
						}
					}
					else
					{
						pw.s += event.text.unicode;
						pw2.s += "*";
					}
					pw.text.setString(pw.s);
					pw2.text.setString(pw2.s);
				}
				if (pw.check == username.check && pw.check == 1)
				{
					pw.check ^= 1;
					pw2.check ^= 1;
				}
				break;
			}
			default:
				break;
			}
		}

		window.clear();
		window.draw(screen.draw);
		drawText(window, username);
		// window.draw(username.text);
		if (isHere(l1.bound, mouse) || entered)
			window.draw(l2.draw);
		else
			window.draw(l1.draw);

		if (see)
		{
			// window.draw(pw.text);
			drawText(window, pw);
			window.draw(eye.draw);
		}
		else
		{
			// window.draw(pw2.text);
			drawText(window, pw2);
			window.draw(close.draw);
		}

		if (change && !wrong_password)
		{
			cerr << "here\n";
			if (is_admin)
			{
				if (login(username.s, pw.s, ADMIN, history, favourite))
				{
					user_name = username.s;
					page = 4;
				}
				else
					wrong_password = true;
			}
			else
			{
				if (login(username.s, pw.s, USERS, history, favourite))
				{
					user_name = username.s;
					page = 4;
				}
				else
					wrong_password = true;
			}
		}
		else if (wrong_password)
		{
			change = false;
			window.draw(wrong.text);
		}
		drawWhich(window, out_here, out, mouse);
		window.display();
	}
}

void wordDisplay(RenderWindow& window, int& page, const bool& is_admin, bool& is_fav, Enlighten& dataset, string word_here)
{
	Object screen = createObject("Graphic/p5_border.png");
	// Object settings1 = createObject("Graphic/settings1.png", 0.0f, 448.0f);
	// Object revision1 = createObject("Graphic/revision1.png", 0.0f, 308.0f);
	int cur_id = dataset.cur_id;
	Node* defi_info = search(dataset.user_Trie[cur_id], word_here);
	Info word = createInfo("Graphic/Roboto-Regular.ttf", word_here, 380.0f, 180.0f, 64);
	Info definition = createInfo("Graphic/Roboto-Regular.ttf", defi_info -> def[0], 380.0f, 264.0f, 26);
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
					// switchPage(fav.first->bound, mouse, x, page);
					switchPage(del.first->bound, mouse, 1, page);
					// switchPage(search_history.first->bound, mouse, x, page);
					switchPage(revision.first->bound, mouse, 7, page);
				}
				if (isHere(rem_fav.first->bound, mouse))
				{
					is_fav = !is_fav;
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
		if (is_fav)
		{
			drawWhich(window, add_to_fav, mouse);
		}
		else
		{
			drawWhich(window, rem_fav, mouse);
		}
		window.draw(search_bar.draw);
		window.draw(word.text);
		window.draw(definition.text);
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
			window.draw(defi[i]->text);
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

void testQA(RenderWindow &window, int &page, Enlighten &dataset, int level)
{
	Object screen = createObject("Graphic/p9.png");
	Object search_bar = createObject("Graphic/search_bar.png", 360.0f, 26.0f);
	pair<Object *, Object *> home = createElement("home", 0.0f, 168.0f);
	pair<Object *, Object *> settings = createElement("settings", 0.0f, 448.0f);
	Object revision1 = createObject("Graphic/revision1.png", 0.0f, 308.0f);
	pair<Object *, Object *> fav = createElement("p4_fav", 963.0f, 31.0f);
	pair<Object *, Object *> user = createElement("p4_user", 1010.0f, 30.0f);
	pair<Object *, Object *> del = createElement("p4_del", 1056.0f, 32.0f);
	pair<Object *, Object *> bar[4], is_true[4];
	LeftRight left_right;
	Info *info[4];
	Info question = createInfo("Graphic/Oswald-Light.ttf", "demo question here", 362.0f, 270.0f, 30);
	Info number = createInfo("Graphic/bahnschrift.ttf", "100", 360.0f, 184.0f, 64);
	for (int i = 0; i < 4; i++)
	{
		bar[i] = createElement("bar", 360.0f, 320.0f + 98.0f * i);
		is_true[i] = createElement("true", 360.0f, 320.0f + 98.0f * i);
		info[i] = createInfoTest("Graphic/Oswald-Medium.ttf", "demo information here", 390.0f, 350.0f + 98.0f * i, 24);
	}
	bool new_question = false, check_answer = false;
	int answer = 0;
	Event event;
	while (page == 9)
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
					for (int i = 0; i < 4; i++)
					{
						if (isHere(bar[i], mouse))
						{
							answer = i;
							check_answer = true;
						}
					}
				}
				break;
			}
			default:
			{
				break;
			}
			}
		}
		window.clear();
		window.draw(screen.draw);
		window.draw(revision1.draw);
		if (new_question)
		{
			// generate new question
		}

		if (check_answer)
		{
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				drawWhich(window, bar[i], mouse);
				window.draw(info[i]->text);
			}
		}
		left_right.draw(window, mouse, 0);
		drawWhich(window, settings, mouse);
		drawWhich(window, home, mouse);
		drawWhich(window, fav, mouse);
		drawWhich(window, user, mouse);
		drawWhich(window, del, mouse);
		window.draw(number.text);
		window.draw(question.text);
		window.display();
	}
	deallocate(home);
	deallocate(settings);
	deallocate(fav);
	deallocate(user);
	deallocate(del);
	left_right.deleteLR();
	for (int i = 0; i < 4; i++)
	{
		delete info[i];
		deallocate(bar[i]);
		deallocate(is_true[i]);
	}
}
