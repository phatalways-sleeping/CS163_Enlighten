#include "header.h"

void revision(RenderWindow &window, int &page, Enlighten &dataset, int &level, bool difficulty)
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
				page = 0;
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					// switchPage(b1.first->bound, mouse, 2, page);
					switchPage(del.first->bound, mouse, 1, page);
					switchPage(home.first->bound, mouse, 4, page);
					switchPage(fav.first->bound, mouse, 6, page);
					switchPage(user.first->bound, mouse, 11, page);
					switchPage(settings.first->bound, mouse, 8, page);
					if (!difficulty)
					{
						if (isHere(easy, mouse))
						{
							page = 9;
							level = 1;
						}
						else if (isHere(medium, mouse))
						{
							page = 9;
							level = 2;
						}
						else if (isHere(hard, mouse))
						{
							page = 9;
							level = 3;
						}
					}
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

void testQA(RenderWindow &window, int &page, Enlighten &dataset, int level, bool& difficulty)
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
	Info *info[4], *info_done[4];
	Info question = createInfo("Graphic/Oswald-Light.ttf", "demo question here", 362.0f, 270.0f, 30);
	Info number = createInfo("Graphic/bahnschrift.ttf", "100", 360.0f, 184.0f, 30);
	Info point = createInfo("Graphic/bahnschrift.ttf", to_string(level * 100), 360.0f, 184.0f, 64);
	Info result_here = createInfo("Graphic/Oswald-Regular.ttf", 560.0f, 410.0f, 35);
	vector<vector<string>> listQuestion = revisionWord(dataset.user_Trie[dataset.cur_id], level, dataset.history, dataset.favorite);
	pair<Object *, Object *> tryAgain = createElement("p9_try", 590.0f, 470.0f);
	pair<Object *, Object *> cancel = createElement("p0_cancel", 328.0f, 470.0f);
	Object bar_done = createObject("Graphic/p9_total.png", 200.0f, 271.0f);
	int curQuestion = 0;
	int correctAnswer = 0;
	for (int i = 0; i < 4; i++)
	{
		bar[i] = createElement("bar", 360.0f, 320.0f + 98.0f * i);
		is_true[i] = createElement("true", 360.0f, 320.0f + 98.0f * i);
		info[i] = createInfoTest("Graphic/Oswald-Medium.ttf", "demo information here", 390.0f, 350.0f + 98.0f * i, 24);
		info_done[i] = createInfoTest("Graphic/Oswald-Medium.ttf", "demo information here", 390.0f, 350.0f + 98.0f * i, 24);
		info_done[i]->text.setFillColor(Color::White);
	}
	bool new_question = true, check_answer = false, is_correct = true, done = false, flag = false;
	int answer = 0, total_point = 0; 
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
				page = 0;
				break;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					switchPage(del.first->bound, mouse, 1, page);
					switchPage(user.first->bound, mouse, 11, page);
					switchPage(home.first->bound, mouse, 4, page);
					if (curQuestion < (int)listQuestion.size())
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
					else
					{
						if (isHere(cancel, mouse))
						{
							page = 7;
							difficulty = false;
						}
						else if (isHere(tryAgain, mouse))
						{
							page = 0;
							flag = true;
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
		left_right.draw(window, mouse, 0);
		drawWhich(window, settings, mouse);
		drawWhich(window, home, mouse);
		drawWhich(window, fav, mouse);
		drawWhich(window, user, mouse);
		drawWhich(window, del, mouse);
		window.draw(number.text);
		window.draw(point.text);
		window.draw(question.text);
		if (new_question && curQuestion < (int)listQuestion.size())
		{
			// generate new question
			number.s = to_string(curQuestion + 1) + "/10";
			number.text.setString(number.s);
			changePos(number, 1038.0f - round(number.bound.width), 128.0f);
			question.text.setString(listQuestion[curQuestion][0]);
			for (int i = 0; i < 4; i++)
			{
				info[i]->text.setString(listQuestion[curQuestion][i + 2]);
				info_done[i]->text.setString(listQuestion[curQuestion][i + 2]);
				if (listQuestion[curQuestion][i + 2] == listQuestion[curQuestion][1])
				{
					correctAnswer = i;
				}
			}
			new_question = false;
		}

		if (check_answer)
		{
			if (answer == correctAnswer)
			{
				is_correct = true;
				total_point += (level * 100);
			}
			else
			{
				is_correct = false;
			}
			check_answer = false;
			done = true;
		}

		if (curQuestion == (int)listQuestion.size())
		{
			if (done)
			{
				if (is_correct)
				{
					window.draw(is_true[answer].first->draw);
					window.draw(info_done[answer]->text);
					for (int i = 0; i < 4; i++)
					{
						if (i == answer)
							continue;
						window.draw(bar[i].first->draw);
						window.draw(info[i]->text);
					}
				}
				else
				{
					window.draw(is_true[answer].second->draw);
					window.draw(is_true[correctAnswer].first->draw);
					window.draw(info_done[answer]->text);
					window.draw(info_done[correctAnswer]->text);
					for (int i = 0; i < 4; i++)
					{
						if (i == answer || i == correctAnswer)
							continue;
						window.draw(bar[i].first->draw);
						window.draw(info[i]->text);
					}
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					window.draw(bar[i].first->draw);
					window.draw(info[i]->text);
				}
			}
			window.draw(bar_done.draw);
			drawWhich(window, cancel, mouse);
			drawWhich(window, tryAgain, mouse);
			result_here.text.setString("Your point is " + to_string(total_point));
			changePos(result_here, 560.0f - round(result_here.bound.width / 2), 410.0f);
			window.draw(result_here.text);
		}
		else
		{
			if (done)
			{
				if (is_correct)
				{
					window.draw(is_true[answer].first->draw);
					window.draw(info_done[answer]->text);
					for (int i = 0; i < 4; i++)
					{
						if (i == answer)
							continue;
						drawWhich(window, bar[i], mouse);
						window.draw(info[i]->text);
					}
				}
				else
				{
					window.draw(is_true[answer].second->draw);
					window.draw(is_true[correctAnswer].first->draw);
					window.draw(info_done[answer]->text);
					window.draw(info_done[correctAnswer]->text);
					for (int i = 0; i < 4; i++)
					{
						if (i == answer || i == correctAnswer)
							continue;
						drawWhich(window, bar[i], mouse);
						window.draw(info[i]->text);
					}
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					drawWhich(window, bar[i], mouse);
					window.draw(info[i]->text);
				}
			}
		}
		
		window.display();

		if (done)
		{
			sleepHere(100.0);
			done = false;
			new_question = true;
			curQuestion++;
		}
	}
	deallocate(home);
	deallocate(settings);
	deallocate(fav);
	deallocate(user);
	deallocate(del);
	deallocate(cancel);
	deallocate(tryAgain);
	left_right.deleteLR();
	for (int i = 0; i < 4; i++)
	{
		delete info[i], info_done[i];
		deallocate(bar[i]);
		deallocate(is_true[i]);
	}
	if (flag)
	{
		page = 9;
	}
}
