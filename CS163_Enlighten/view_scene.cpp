#include "header.h"

void Scene1(RenderWindow &window, int &page)
{
    Object screen = createObject("Graphic/p1.png");
    Object b1 = createObject("Graphic/p1_search.png", 478.0f, 540.0f);
    Object b1_here = createObject("Graphic/p1_search_here.png", 478.0f, 540.0f);
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
                return;
            }
            case Event::MouseButtonReleased:
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    switchPage(b1.bound, mouse, 2, page);
                }
                break;
            }
            default:
                break;
            }
        }
        window.clear();
        window.draw(screen.draw);
        drawWhich(window, b1_here, b1, mouse);
        window.display();
    }
}

void setRole(RenderWindow &window, int &page, bool &is_admin)
{
    Object screen = createObject("Graphic/p3.png");
    Object admin = createObject("Graphic/p3_admin.png", 572.0f, 262.0f);
    Object admin_here = createObject("Graphic/p3_admin_here.png", 572.0f, 262.0f);
    Object user = createObject("Graphic/p3_user.png", 222.0f, 262.0f);
    Object user_here = createObject("Graphic/p3_user_here.png", 222.0f, 262.0f);
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
                window.close();
                return;
            }
            case Event::MouseButtonReleased:
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (isHere(admin.bound, mouse))
                    {
                        page = 3;
                        is_admin = true;
                        return;
                    }
                    if (isHere(user.bound, mouse))
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
        drawWhich(window, admin_here, admin, mouse);
        drawWhich(window, user_here, user, mouse);
        window.display();
    }
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