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
	Info welcome = createInfo("Graphic/bahnschrift.ttf", "Welcome, username", 354.0f, 186.0f, 64);
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
	pair<Object *, Object *> left = createElement("left", 352.0f, 130.0f);
	pair<Object *, Object *> right = createElement("right", 376.0f, 130.0f);
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
					//switchPage(fav.first->bound, mouse, x, page);
					switchPage(del.first->bound, mouse, 1, page);
					//switchPage(search_history.first->bound, mouse, x, page);
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
		// draw left-right
		//
		drawWhich(window, settings, mouse);
		drawWhich(window, revision, mouse);
		drawWhich(window, fav, mouse);
		drawWhich(window, change, mouse);
		drawWhich(window, add, mouse);
		drawWhich(window, user, mouse);
		drawWhich(window, search_history, mouse);
		drawWhich(window, del, mouse);
		drawWhich(window, left, mouse);
		drawWhich(window, right, mouse);
		window.draw(search_bar.draw);
		window.draw(welcome.text);
		window.display();
	}
	// delete ;
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