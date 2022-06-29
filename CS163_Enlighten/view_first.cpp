#include "header.h"

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
			case Event::TextEntered:
			{
				if (event.text.unicode == 9 || event.text.unicode == 13) {
					page = 2;
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



void setRole(RenderWindow &window, int &page, bool &is_admin, Enlighten &dataset)
{
	bool tab = false;
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
			case Event::TextEntered:
			{
				if (event.text.unicode == 9) { // tab
					is_admin ^= 1;
					tab = true;
				}
				else if (event.text.unicode == 13) { // enter
					page = 3;
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
		if (isHere(admin, mouse)) {
			is_admin = true;
		}
		else if (isHere(user, mouse)) {
			is_admin = false;
		}
		if (tab && !isHere(admin, mouse) && !isHere(user, mouse)) {
			if (is_admin)
			{
				window.draw(admin.second->draw);
			}
			else
			{
				window.draw(user.second->draw);
			}
		}
		window.display();
	}
	deallocate(admin);
	deallocate(user);
	cerr << is_admin << endl;
}




void logIn(RenderWindow& window, int& page, const bool& is_admin, string& user_name, Enlighten& dataset)
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
						if (login(username.s, pw.s, ADMIN, dataset.history, dataset.favorite))
						{
							user_name = username.s;
							page = 4;
						}
						else
							wrong_password = true;
					}
					else
					{
						if (login(username.s, pw.s, USERS, dataset.history, dataset.favorite))
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
				if (login(username.s, pw.s, ADMIN, dataset.history, dataset.favorite))
				{
					user_name = username.s;
					page = 4;
				}
				else
					wrong_password = true;
			}
			else
			{
				if (login(username.s, pw.s, USERS, dataset.history, dataset.favorite))
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