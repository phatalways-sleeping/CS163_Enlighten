#include "header.h"

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