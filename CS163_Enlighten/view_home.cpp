#include "header.h"

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
	Object w = createObject("Graphic/w.png", 317.0f, 196.0f);
	Object t = createObject("Graphic/t.png", 317.0f, 272.0f);
	Object d = createObject("Graphic/d.png", 317.0f, 348.0f);
	LeftRight left_right;
	SearchBar do_search;
	Vocabulary new_word;
	for (int i = 0; i < 12; i++)
	{
		if (i >= history.size())
		{
			sh[i] = createInfoTest("Graphic/Oswald-Medium.ttf", "", 464.0f, 510.0f, 20);
			continue;
		}
		sh[i] = createInfoTest("Graphic/Oswald-Medium.ttf", history[i], 464.0f, 510.0f, 20);
		changePos(sh[i], 464.0f + 150.0f * (i >= 6) - round(sh[i]->bound.width / 2), 480.0f + 44.0f * (i % 6));
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
					else if (search_status == 2)
					{
						if (isHere(d.bound, mouse)) {
							do_search.enter_defi.check = true;
							do_search.enter_type.check = false;
							do_search.enter_word.check = false;
						}
						if (isHere(w.bound, mouse))
						{
							do_search.enter_defi.check = false;
							do_search.enter_word.check = true;
							do_search.enter_type.check = false;
						}
						if (isHere(t.bound, mouse))
						{
							do_search.enter_defi.check = false;
							do_search.enter_word.check = false;
							do_search.enter_type.check = true;
						}
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
					vector <string> correctList = correct_words(dataset.user_Trie[dataset.cur_id], do_search.search_info->s, 3);
					for (auto s : correctList) completeList.push_back(s);
					for (int i = 0; i < 3; i++)
					{
						do_search.result[i]->s = "";
						do_search.result[i]->text.setString("");
					}
					int size = min(3, (int)completeList.size());
					for (int i = 0; i < size; ++i) {
						do_search.result[i]->s = completeList[i];
						do_search.result[i]->text.setString(completeList[i]);
					}
				}
				else if (search_status == 2)
				{
					texting_endl(do_search.enter_defi, event.text.unicode, 36);
					texting(do_search.enter_word, event.text.unicode, 30);
					texting(do_search.enter_type, event.text.unicode, 30);
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
		searching(window, search_status, do_search, mouse, add_status, dataset, event, count, new_word);
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