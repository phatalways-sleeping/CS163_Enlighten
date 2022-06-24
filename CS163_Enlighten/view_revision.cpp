#include "header.h"

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
	vector<vector<string>> listQuestion = revisionWord(dataset.user_Trie[dataset.cur_id], level, dataset.history, dataset.favorite);
	int curQuestion = 0;
	int correctAnswer = 0;
	for (int i = 0; i < 4; i++)
	{
		bar[i] = createElement("bar", 360.0f, 320.0f + 98.0f * i);
		is_true[i] = createElement("true", 360.0f, 320.0f + 98.0f * i);
		info[i] = createInfoTest("Graphic/Oswald-Medium.ttf", "demo information here", 390.0f, 350.0f + 98.0f * i, 24);
	}
	bool new_question = true, check_answer = false;
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
			if (curQuestion >= (int)listQuestion.size()) {
				break;
			}
			question.text.setString(listQuestion[curQuestion][0]);
			for (int i = 0; i < 4; i++) {
				info[i]->text.setString(listQuestion[curQuestion][i + 2]);
				if (listQuestion[curQuestion][i + 2] == listQuestion[curQuestion][1]) {
					correctAnswer = i;
				}
			}
			new_question = false;
			curQuestion++;
		}

		if (check_answer)
		{
			if (answer == correctAnswer) {
				cerr << "Correct\n";
			}
			else {
				cerr << "Incorrect, answer is: " << char(correctAnswer + 'A') << '\n';
			}
			new_question = true;
			check_answer = false;
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
