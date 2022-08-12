#pragma once
#include "header.h"
#include "test_function.h"
void sleepHere(double s)
{
	vector<int> v;
	for (int i = 0; i < (double)10000000.0 * s; i++) {
		v.push_back(i);
		v.clear();
	}
	cout << "...\n";
	v.clear();
}

void loadingDataset(RenderWindow &window, Enlighten &dataset, int &page, int number_of_dataset)
{
	Object *loading[10];
	for (int i = 0; i < 10; i++)
	{
		loading[i] = createObjectTest("Graphic/" + to_string(i) + ".png", 238.0f, 540.0f);
	}
	Event event;
	Object screen = createObject("Graphic/p1.png");
	int count = 0;
	ifstream dict_name_file(dict_name_path);
	dict_name_file >> number_of_dataset;
	//dict_name_file.ignore('\n');
	while (count < number_of_dataset)
	{
		//playSound("hmc.mp3");
		if (window.pollEvent(event) && event.type == Event::Closed)
		{
			page = -1;
			return;
		}
	
		window.clear();
		window.draw(screen.draw);
		if (count < 10)
			window.draw(loading[count]->draw);
		count++;
		window.display();
		// input text file
		Trie T;
		Trie T_def;
		string dictName, dictPath;
		dict_name_file >> dictName >> dictPath;
		T.name = dictName; 
		T.path = dictPath; 
		readJson(T, dictPath);
		T_def.name = dictName;
		T_def.path = dictPath;
		build_definition_trie(T_def, T);
		


		//sleepHere(3.0);
		T.isChanged = false;
		dataset.user_Trie.push_back(T);
		dataset.def_Trie.push_back(T_def);
	}
	for (int i = count; i < 10; ++i) {
		sleepHere(10.0);
		window.clear();
		window.draw(screen.draw);
		window.draw(loading[i]->draw);
		window.display();
	}
	for (int i = 0; i < 10; i++)
	{
		delete loading[i];
	}
	dict_name_file.close();
}

int checkConfirmation(RenderWindow& window, int& check, const Confirmation& element, Vector2f& mouse)
{
	if (check == 0)
		return 0;
	if (check == -1)
	{
		window.draw(element.board.first->draw);
		drawWhich(window, element.nah, mouse);
		drawWhich(window, element.of_course, mouse);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (isHere(element.nah, mouse)) {
				check = 0;
				return 0;
			}
			else if (isHere(element.of_course, mouse))
			{
				check = 1;
				return -1;
			}
		}
	}
	else if (check == 2)
	{
		window.draw(element.invalid.draw);
		drawWhich(window, element.out, mouse);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (isHere(element.out, mouse))
			{
				check = 0;
				return 0;
			}
		}
	}
	else
	{
		window.draw(element.board.second->draw);
		drawWhich(window, element.out, mouse);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (isHere(element.out, mouse))
			{
				check = 0;
				return 0;
			}
		}
	}
	return 1;
}

int checkConfirmation(RenderWindow& window, Event& event, int& check, const Confirmation& element, Vector2f& mouse)
{
	if (check == 0)
		return 0;
	if (check == -1)
	{
		window.draw(element.board.first->draw);
		drawWhich(window, element.nah, mouse);
		drawWhich(window, element.of_course, mouse);
		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{
			if (isHere(element.nah, mouse)) {
				check = 0;
				return 0;
			}
			else if (isHere(element.of_course, mouse))
			{
				check = 1;
				return -1;
			}
		}
	}
	else if (check == 2)
	{
		window.draw(element.invalid.draw);
		drawWhich(window, element.out, mouse);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (isHere(element.out, mouse))
			{
				check = 0;
				return 0;
			}
		}
	}
	else
	{
		window.draw(element.board.second->draw);
		drawWhich(window, element.out, mouse);
		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{
			if (isHere(element.out, mouse))
			{
				check = 0;
				return 0;
			}
		}
	}
	return 1;
}

// -1: added, >0: switch
int searching(RenderWindow &window, int &status, SearchBar &s, Vector2f &mouse, int &add_status, Enlighten &dataset, Event &event, int count, Vocabulary& new_word)
{
	switch (status)
	{
		// searching
	case 1:
	{
		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{
			if (isHere(s.change, mouse))
			{
				status = 3;
				s.search_info->check = false;
				s.search_info->s = "";
			}
			else if (isHere(s.add, mouse))
			{
				status = 2;
				s.search_info->check = false;
				s.search_info->s = "";
				resetInfo(s.enter_defi, "Enter definition");
				resetInfo(s.enter_word, "Enter word");
				resetInfo(s.enter_type, "Enter type of word");
				add_status = -1;
			}
			else if (!isHere(s.search, mouse) && !isHere(s.board.bound, mouse))
			{
				s.search_info->check = false;
				s.search_info->s = "";
				status = 0;
			}
			
		}
		drawWhich(window, s.add, mouse);
		drawWhich(window, s.change, mouse);
		window.draw(s.board.draw);
		window.draw(s.search.second->draw);
		drawWhich(window, s.search_history, mouse);
		for (int i = 0; i < 3; i++)
		{
			drawWhich(window, s.SE[2 - i], mouse);
			window.draw(s.result[2 - i]->text);
		}
		window.draw(s.search_info->text);
		drawText(window, s.search_info);
		if (s.is_normal) window.draw(s.search_normal.draw);
		else window.draw(s.search_defi.draw);
		break;
	}
	// adding
	case 2:
	{
		window.draw(s.add.second->draw);
		window.draw(s.change.first->draw);
		window.draw(s.search.first->draw);
		int temp = checkConfirmation(window, add_status, s.new_word, mouse);
		if (!temp)
		{
			status = 0;
		}
		else if (temp == -1) {
			new_word.read(s.enter_defi.s);
			new_word.word = s.enter_word.s;
			new_word.type = s.enter_type.s;
			for (auto def : new_word.definitions)
				insert(dataset.user_Trie[dataset.cur_id], new_word.word, new_word.type, def);
			return -1;
		}
		else if (add_status == -1)
		{
			window.draw(s.enter_word.text);
			window.draw(s.enter_defi.text);
			window.draw(s.enter_type.text);
			drawText(window, s.enter_word);
			drawText(window, s.enter_type);
			drawText(window, s.enter_defi);
		}
		break;
	}
	// switching
	case 3:
	{
		window.draw(s.add.first->draw);
		window.draw(s.change.second->draw);
		window.draw(s.search.first->draw);
		bool check = false;
		int temp = s.switch_dict.assign(dataset.user_Trie, count, check);
		int k = count > dataset.user_Trie.size() ? dataset.user_Trie.size() : count;
		s.switch_dict.draw(window, temp, mouse, check);
		window.draw(s.switch_dict.button[dataset.cur_id].second->draw);
		window.draw(s.switch_dict.name[dataset.cur_id]->text);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (isHere(s.search, mouse))
			{
				s.search_info->check = true;
				status = 1;
			}
			else if (isHere(s.add, mouse))
			{
				resetInfo(s.enter_defi, "Enter definition");
				resetInfo(s.enter_word, "Enter word");
				resetInfo(s.enter_type, "Enter type of word");
				status = 2;
				add_status = -1;
			}
			else
			{
				int cur_p = (k - 1) / 6;
				for (int i = 0; i < 6; i++)
				{
					int id = i + cur_p * 6;
					if (isHere(s.switch_dict.button[id], mouse))
					{
						// switch dictionary
						dataset.cur_id = id;
						status = 0;
						return 2;
					}
				}
			}
		}
		break;
	}
	default:
	{
		drawWhich(window, s.add, mouse);
		drawWhich(window, s.change, mouse);
		window.draw(s.search.first->draw);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (isHere(s.search, mouse))
			{
				s.search_info->check = true;
				status = 1;
			}
			else if (isHere(s.add, mouse))
			{
				resetInfo(s.enter_defi, "Enter definition");
				resetInfo(s.enter_word, "Enter word");
				resetInfo(s.enter_type, "Enter type of word");
				status = 2;
				add_status = -1;
			}
			else if (isHere(s.change, mouse))
			{
				status = 3;
			}
		}
		break;
	}
	}
	return 0;
}

int searching(int is_okay, RenderWindow& window, int& status, SearchBar& s, Vector2f& mouse, int& add_status, Enlighten& dataset, Event& event, int count, Vocabulary& new_word)
{
		switch (status)
		{
			// searching
		case 1:
		{
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (isHere(s.change, mouse))
				{
					status = 3;
					s.search_info->check = false;
					s.search_info->s = "";
				}
				else if (isHere(s.add, mouse))
				{
					status = 2;
					s.search_info->check = false;
					s.search_info->s = "";
					resetInfo(s.enter_defi, "Enter definition");
					resetInfo(s.enter_word, "Enter word");
					resetInfo(s.enter_type, "Enter type of word");
					add_status = -1;
				}
				else if (!isHere(s.search, mouse) && !isHere(s.board.bound, mouse))
				{
					s.search_info->check = false;
					s.search_info->s = "";
					status = 0;
				}

			}
			drawWhich(window, s.add, mouse);
			drawWhich(window, s.change, mouse);
			window.draw(s.board.draw);
			window.draw(s.search.second->draw);
			drawWhich(window, s.search_history, mouse);
			for (int i = 0; i < 3; i++)
			{
				drawWhich(window, s.SE[2 - i], mouse);
				window.draw(s.result[2 - i]->text);
			}
			window.draw(s.search_info->text);
			drawText(window, s.search_info);
			if (s.is_normal) window.draw(s.search_normal.draw);
			else window.draw(s.search_defi.draw);
			break;
		}
		// adding
		case 2:
		{
			window.draw(s.add.second->draw);
			window.draw(s.change.first->draw);
			window.draw(s.search.first->draw);
			int temp = checkConfirmation(window, add_status, s.new_word, mouse);
			if (!temp)
			{
				status = 0;
			}
			else if (temp == -1) {
				new_word.read(s.enter_defi.s);
				new_word.word = s.enter_word.s;
				new_word.type = s.enter_type.s;
				for (auto def : new_word.definitions)
					insert(dataset.user_Trie[dataset.cur_id], new_word.word, new_word.type, def);
				return -1;
			}
			else if (add_status == -1)
			{
				window.draw(s.enter_word.text);
				window.draw(s.enter_defi.text);
				window.draw(s.enter_type.text);
				drawText(window, s.enter_word);
				drawText(window, s.enter_type);
				drawText(window, s.enter_defi);
			}
			break;
		}
		// switching
		case 3:
		{
			window.draw(s.add.first->draw);
			window.draw(s.change.second->draw);
			window.draw(s.search.first->draw);
			bool check = false;
			int temp = s.switch_dict.assign(dataset.user_Trie, count, check);
			int k = count > dataset.user_Trie.size() ? dataset.user_Trie.size() : count;
			s.switch_dict.draw(window, temp, mouse, check);
			window.draw(s.switch_dict.button[dataset.cur_id].second->draw);
			window.draw(s.switch_dict.name[dataset.cur_id]->text);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (isHere(s.search, mouse))
				{
					s.search_info->check = true;
					status = 1;
				}
				else if (isHere(s.add, mouse))
				{
					resetInfo(s.enter_defi, "Enter definition");
					resetInfo(s.enter_word, "Enter word");
					resetInfo(s.enter_type, "Enter type of word");
					status = 2;
					add_status = -1;
				}
				else
				{
					int cur_p = (k - 1) / 6;
					for (int i = 0; i < 6; i++)
					{
						int id = i + cur_p * 6;
						if (isHere(s.switch_dict.button[id], mouse))
						{
							// switch dictionary
							dataset.cur_id = id;
							status = 0;
							return 2;
						}
					}
				}
			}
			break;
		}
		default:
		{
			drawWhich(window, s.add, mouse);
			drawWhich(window, s.change, mouse);
			window.draw(s.search.first->draw);
			if (Mouse::isButtonPressed(Mouse::Left) && !is_okay)
			{
				if (isHere(s.search, mouse))
				{
					s.search_info->check = true;
					status = 1;
				}
				else if (isHere(s.add, mouse))
				{
					resetInfo(s.enter_defi, "Enter definition");
					resetInfo(s.enter_word, "Enter word");
					resetInfo(s.enter_type, "Enter type of word");
					status = 2;
					add_status = -1;
				}
				else if (isHere(s.change, mouse))
				{
					status = 3;
				}
			}
			break;
		}
		}
	return 0;
}
