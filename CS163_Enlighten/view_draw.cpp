#pragma once
#include "header.h"

void sleep(double s)
{
	vector<int> v;
	for (int i = 0; i < (double)10000000.0 * s; i++)
		v.push_back(i);
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
	while (count < number_of_dataset)
	{
		if (window.pollEvent(event) && event.type == Event::Closed)
		{
			window.close();
			page = -1;
			return;
		}
		// input text file
		Trie T;
		inputTxtFile(T, "Data/ENGLISH_TO_VIETNAMESE/Datasets5000.txt");

		sleep(1.0);
		dataset.user_Trie.push_back(T);
		count++;
		window.clear();
		window.draw(screen.draw);
		if (count < 10)
			window.draw(loading[count]->draw);
		else
			window.draw(loading[9]->draw);
		window.display();
	}

	for (int i = 0; i < 10; i++)
	{
		delete loading[i];
	}
}

bool checkConfirmation(RenderWindow &window, int &check, const Confirmation &element, Vector2f &mouse)
{
	if (check == 0)
		return false;
	if (check == -1)
	{
		window.draw(element.board.first->draw);
		drawWhich(window, element.nah, mouse);
		drawWhich(window, element.of_course, mouse);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (isHere(element.nah, mouse)) {
				check = 0;
				return false;
			}
			else if (isHere(element.of_course, mouse))
			{
				// do some thing here;
				check = 1;
				return true;
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
				return false;
			}
		}
	}
	return true;
}

void searching(RenderWindow &window, int &status, SearchBar &s, Vector2f &mouse, int &add_status, Enlighten &dataset, Event &event, int count)
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
				add_status = -1;
			}
			else if (!isHere(s.search, mouse))
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
		break;
	}
	// adding
	case 2:
	{
		window.draw(s.add.second->draw);
		window.draw(s.change.first->draw);
		window.draw(s.search.first->draw);
		if (!checkConfirmation(window, add_status, s.new_word, mouse))
		{
			status = 0;
		}
		else if (add_status == -1)
		{
			window.draw(s.enter_word.text);
			window.draw(s.enter_defi.text);
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
		int temp = s.switch_dict.assign(dataset.dictionary_name, count, check);
		int k = count > dataset.dictionary_name.size() ? dataset.dictionary_name.size() : count;
		s.switch_dict.draw(window, temp, mouse, check);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (isHere(s.search, mouse))
			{
				s.search_info->check = true;
				status = 1;
			}
			else if (isHere(s.add, mouse))
			{
				status = 2;
				add_status = -1;
			}
			else
			{
				for (int i = (int(k - 1) / 6 ) * 6; i < k; i++)
				{
					if (isHere(s.switch_dict.button[k], mouse))
					{
						// switch dictionary
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
}
