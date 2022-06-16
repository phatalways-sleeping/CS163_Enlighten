#include "header.h"

void Scene1(RenderWindow &window, int &page)
{
	Object screen = createObject("Graphic/p1.png");
	pair<Object *, Object *> b1 = createElement("p1_search", 478.0f, 540.0f);
	Event event;
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

void revision(RenderWindow &window, int &page)
{
	Object screen = createObject("Graphic/p7.png");
	pair<Object *, Object *> b1 = createElement("p7_start", 360.0f, 377.0f);
	Object revision1 = createObject("Graphic/revision1.png", 0.0f, 308.0f);
	pair<Object *, Object *> home = createElement("home", 0.0f, 168.0f);
	pair<Object *, Object *> settings = createElement("settings", 0.0f, 448.0f);
	pair<Object *, Object *> fav = createElement("p4_fav", 963.0f, 31.0f);
	pair<Object *, Object *> user = createElement("p4_user", 1010.0f, 30.0f);
	pair<Object *, Object *> del = createElement("p4_del", 1056.0f, 32.0f);
	pair<Object *, Object *> pLeft = createElement("left", 352.0f, 130.0f);
	pair<Object *, Object *> pRight = createElement("right", 376.0f, 130.0f);

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
		window.display();
	}
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
void settings(RenderWindow &window, int &page, const bool& is_admin)
{
	Object screen = createObject("Graphic/border.png");
	pair<Object *, Object *> b1 = createElement("p7_start", 360.0f, 377.0f);
	pair<Object *, Object *> home = createElement("home", 0.0f, 168.0f);
	pair<Object *, Object *> fav = createElement("p4_fav", 963.0f, 31.0f);
	pair<Object *, Object *> user = createElement("p4_user", 1010.0f, 30.0f);
	pair<Object *, Object *> del = createElement("p4_del", 1056.0f, 32.0f);
	pair<Object *, Object *> pLeft = createElement("left", 352.0f, 130.0f);
	pair<Object *, Object *> pRight = createElement("right", 376.0f, 130.0f);
	Object settings1 = createObject("Graphic/settings1.png", 0.0f, 448.0f);
	pair<Object *, Object *> revision = createElement("revision", 0.0f, 308.0f);
	Info word = createInfo("Graphic/bahnschrift.ttf", "Settings", 402.0f, 127.0f, 21);

	Event event;
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
					switchPage(revision.first->bound, mouse, 7, page);
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
		drawWhich(window, revision, mouse);
		drawWhich(window, fav, mouse);
		drawWhich(window, home, mouse);
		drawWhich(window, user, mouse);
		window.draw(settings1.draw);
		drawWhich(window, b1, mouse);
		drawWhich(window, pLeft, mouse);
		drawWhich(window, pRight, mouse);
		window.display();
	}
	deallocate(b1);
	deallocate(del);
	deallocate(settings);
	deallocate(fav);
	deallocate(home);
	deallocate(pLeft);
	deallocate(pRight);
	deallocate(user);
}

void setRole(RenderWindow &window, int &page, bool &is_admin)
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
					if (isHere(admin, mouse))
					{
						page = 3;
						is_admin = true;
						return;
					}
					if (isHere(user, mouse))
					{
						page = 3;
						is_admin = false;
						return;
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
		drawWhich(window, admin, mouse);
		drawWhich(window, user, mouse);
		window.display();
	}
	deallocate(admin);
	deallocate(user);
}

void home(RenderWindow &window, int &page, bool &is_admin)
{
	Object screen = createObject("Graphic/p4.png");
	// Object settings1 = createObject("Graphic/settings1.png", 0.0f, 448.0f);
	// Object revision1 = createObject("Graphic/revision1.png", 0.0f, 308.0f);
	Info welcome = createInfo("Graphic/Roboto-Regular.ttf", "Welcome, username", 354.0f, 186.0f, 64);
	Object home1 = createObject("Graphic/home1.png", 0.0f, 168.0f);
	Object search_bar = createObject("Graphic/search_bar.png", 360.0f, 26.0f);
	pair<Object *, Object *> home = createElement("home", 0.0f, 168.0f);
	pair<Object *, Object *> settings = createElement("settings", 0.0f, 448.0f);
	pair<Object *, Object *> revision = createElement("revision", 0.0f, 308.0f);
	pair<Object *, Object *> fav = createElement("p4_fav", 963.0f, 31.0f);
	pair<Object *, Object *> user = createElement("p4_user", 1010.0f, 30.0f);
	pair<Object *, Object *> del = createElement("p4_del", 1056.0f, 32.0f);
	pair<Object *, Object *> search_history = createElement("p4_sh", 364.0f, 434.0f);
	pair<Object *, Object *> add = createElement("add", 308.0f, 26.0f);
	pair<Object *, Object *> change = createElement("switch", 810.0f, 26.0f);
	pair<Object *, Object *> pLeft = createElement("left", 352.0f, 130.0f);
	pair<Object *, Object *> pRight = createElement("right", 376.0f, 130.0f);
	Event event;
	changePos(add.second, 260.0f, 26.0f);
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
					// switchPage(fav.first->bound, mouse, x, page);
					switchPage(del.first->bound, mouse, 1, page);
					// switchPage(search_history.first->bound, mouse, x, page);
					switchPage(revision.first->bound, mouse, 7, page);
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
		drawWhich(window, search_history, mouse);
		drawWhich(window, del, mouse);
		drawWhich(window, pLeft, mouse);
		drawWhich(window, pRight, mouse);
		window.draw(search_bar.draw);
		window.draw(welcome.text);
		window.display();
	}
	deallocate(home);
	deallocate(settings);
	deallocate(revision);
	deallocate(fav);
	deallocate(user);
	deallocate(del);
	deallocate(search_history);
	deallocate(add);
	deallocate(change);
	deallocate(pLeft);
	deallocate(pRight);
}

void logIn(RenderWindow &window, int &page, bool is_admin)
{
	Event event;
	bool see = false, entered = false, change = false, wrong_password = true;
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
					}
					else if (isHere(pw.bound, mouse))
					{
						pw.check = true;
						username.check = false;
					}
					else
					{
						pw.check = false;
						username.check = false;
					}
				}

				break;
			}
			case Event::TextEntered:
			{
				texting(username, event.text.unicode, 15);

				if (pw.check && (pw.s.size() < 10 || event.text.unicode == 8))
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
				break;
			}
			default:
				break;
			}
		}

		window.clear();
		window.draw(screen.draw);
		window.draw(username.text);
		if (isHere(l1.bound, mouse) || entered)
			window.draw(l2.draw);
		else
			window.draw(l1.draw);

		if (see)
		{
			window.draw(pw.text);
			window.draw(eye.draw);
		}
		else
		{
			window.draw(pw2.text);
			window.draw(close.draw);
		}

		if (change && !wrong_password)
		{
			// if (is_staff)
			// {
			// 	user = searchStudentNode(staff_list, username.s);
			// 	if (user && user->student.password == pw.s)
			// 	{
			// 		page = 4;
			// 		wrong_password = false;
			// 	}
			// 	else
			// 		wrong_password = true;
			// }
			// else
			// {
			// 	check_class = class_list;
			// 	user = nullptr;
			// 	while (!user && check_class)
			// 	{
			// 		user = searchStudentNode(check_class->my_class.student_list, username.s);
			// 		check_class = check_class->next;
			// 	}
			// 	if (user && user->student.password == pw.s)
			// 	{
			// 		wrong_password = false;
			// 		page = 3;
			// 	}
			// 	else
			// 		wrong_password = true;
			// }
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

void wordDisplay(RenderWindow &window, int &page, const bool &is_admin)
{
	Object screen = createObject("Graphic/p5_border.png");
	// Object settings1 = createObject("Graphic/settings1.png", 0.0f, 448.0f);
	// Object revision1 = createObject("Graphic/revision1.png", 0.0f, 308.0f);
	Info word = createInfo("Graphic/Roboto-Regular.ttf", "demo word here", 380.0f, 180.0f, 64);
	Info definition = createInfo("Graphic/Roboto-Regular.ttf", "demo definition here", 380.0f, 264.0f, 26);
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
	pair<Object *, Object *> pLeft = createElement("left", 352.0f, 130.0f);
	pair<Object *, Object *> pRight = createElement("right", 376.0f, 130.0f);
	pair<Object *, Object *> qLeft = createElement("left1", 1005.0f, 195.0f);
	pair<Object *, Object *> qRight = createElement("right1", 1035.0f, 195.0f);
	pair<Object *, Object *> rLeft = createElement("left1", 688.0f, 717.0f);
	pair<Object *, Object *> rRight = createElement("right1", 718.0f, 717.0f);
	pair<Object *, Object *> add_to_fav = createElement("p5_add_fav", 886.0f, 115.0f);
	pair<Object *, Object *> rem_fav = createElement("p5_rem_fav", 886.0f, 115.0f);
	Object *border[3];
	Info *name[3], *defi[3];
	bool is_fav = true;
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
		drawWhich(window, pLeft, mouse);
		drawWhich(window, pRight, mouse);
		drawWhich(window, qLeft, mouse);
		drawWhich(window, qRight, mouse);
		drawWhich(window, rLeft, mouse);
		drawWhich(window, rRight, mouse);
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
	deallocate(pLeft);
	deallocate(pRight);
	deallocate(qLeft);
	deallocate(qRight);
	deallocate(rLeft);
	deallocate(rRight);
	deallocate(add_to_fav);
	deallocate(rem_fav);
	for (int i = 0; i < 3; i++)
	{
		delete border[i], name[i], defi[i];
	}
}

void myList(RenderWindow &window, int &page, bool is_fav)
{
	Object screen = createObject("Graphic/border.png");
	// Object settings1 = createObject("Graphic/settings1.png", 0.0f, 448.0f);
	// Object revision1 = createObject("Graphic/revision1.png", 0.0f, 308.0f);
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
	pair<Object *, Object *> pLeft = createElement("left", 352.0f, 130.0f);
	pair<Object *, Object *> pRight = createElement("right", 376.0f, 130.0f);
	pair<Object *, Object *> rLeft = createElement("left1", 660.0f, 726.0f);
	pair<Object *, Object *> rRight = createElement("right1", 690.0f, 726.0f);
	pair<Object *, Object *> clear = createElement("clear", 886.0f, 120.0f);
	pair<Object *, Object *> rem_fav = createElement("p5_rem_fav", 886.0f, 115.0f);
	Object *border[5];
	pair<Object *, Object *> rem[5];
	Info *name[5], *defi[5];
	for (int i = 0; i < 5; i++)
	{
		rem[i] = createElement("del", 980.0f, 210.0f + 110.0f * i);
		border[i] = createObjectTest("Graphic/bar.png", 360.0f, 178.0f + 110.0f * i);
		name[i] = createInfoTest("Graphic/Roboto-Medium.ttf", "demo username", 390.0f, 190.0f + 110.0f * i, 23);
		defi[i] = createInfoTest("Graphic/RobotoCondensed-Regular.ttf", "demo definition here", 390.0f, 225.0f + 110.0f * i, 17);
	}
	Event event;
	changePos(add.second, 260.0f, 26.0f);
	while (page == 6)
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
					switchPage(revision.first->bound, mouse, 7, page);

					// switchPage(search_history.first->bound, mouse, x, page);
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
		drawWhich(window, pLeft, mouse);
		drawWhich(window, pRight, mouse);
		drawWhich(window, rLeft, mouse);
		drawWhich(window, rRight, mouse);
		drawWhich(window, clear, mouse);
		window.draw(search_bar.draw);
		for (int i = 0; i < 5; i++)
		{
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
	deallocate(pLeft);
	deallocate(pRight);
	deallocate(rLeft);
	deallocate(rRight);
	deallocate(clear);
	deallocate(rem_fav);
	delete word;
	for (int i = 0; i < 5; i++)
	{
		delete border[i], name[i], defi[i], rem[i];
	}
}