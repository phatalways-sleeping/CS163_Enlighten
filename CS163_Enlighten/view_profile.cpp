#include "header.h"

void profile(RenderWindow& window, int& page, Enlighten& dataset)
{
	// variables need input data
	string p_username = "Username", p_level = "Level 2 - A Great Explorer";
	int p_low_level = 0, p_high_level = 0, p_score_cur = 2300, p_score_want = 4500;
	int percent = p_score_want / p_score_cur;
	bool badges[5] = { false, true, false, false, true };
	//----

	int check = 0;
	Confirmation confirm_pw = create("change_pw", "p0_cancel", "p0_ok", "p0_return");
	vector<pair<bool, int>> check1, check2;
	for (int i = 0; i < 5; i++)
	{
		if (badges[i])
		{
			check1.push_back({ true, i });
		}
		else
		{
			check2.push_back({ false, i });
		}
	}
	for (int i = 0; i < (int)check2.size(); i++)
	{
		check1.push_back(check2[i]);
	}
	Event event;
	Object screen = createObject("Graphic/p11.png");
	pair<Object*, Object*> settings = createElement("settings", 0.0f, 448.0f);
	pair<Object*, Object*> fav = createElement("p4_fav", 963.0f, 31.0f);
	pair<Object*, Object*> revision = createElement("revision", 0.0f, 308.0f);
	pair<Object*, Object*> user = createElement("p4_user", 1010.0f, 30.0f);
	pair<Object*, Object*> del = createElement("p4_del", 1056.0f, 32.0f);
	pair<Object*, Object*> pLeft = createElement("left", 352.0f, 130.0f);
	pair<Object*, Object*> pRight = createElement("right", 376.0f, 130.0f);
	Object home1 = createObject("Graphic/home1.png", 0.0f, 168.0f);
	Object user_ava = createObject("Graphic/p11_user.png", 397.0f, 195.0f);
	Object score_bar = createObject("Graphic/p11_bar.png", 414.0f, 473.0f);
	Object score_cur_bar = createObject("Graphic/p11_" + to_string(percent) + ".png", 414.0f, 473.0f);
	pair<Object*, Object*> change_pw = createElement("p11_cpw", 676.0f, 346.0f);
	Info username = createInfo("Graphic/Roboto-Regular.ttf", p_username, 672.0f, 233.0f, 52);
	Info level = createInfo("Graphic/Roboto-Regular.ttf", p_level, 675.0f, 305.0f, 26);
	pair<Object*, Object*> edit = createElement("p11_edit", 700.0f + username.bound.width, 250.0f);
	Info low_level = createInfo("Graphic/Roboto-Regular.ttf", "Level " + to_string(p_low_level), 386.0f, 445.0f, 18);
	Info high_level = createInfo("Graphic/Roboto-Regular.ttf", "Level " + to_string(p_high_level), 987.0f, 445.0f, 18);
	Info score_cur = createInfo("Graphic/RobotoCondensed-Bold.ttf", to_string(p_score_cur), 640.0f, 492.0f, 20);
	Info score_want = createInfo("Graphic/RobotoCondensed-Bold.ttf", to_string(p_score_want), 995.0f, 492.0f, 20);
	changePos(score_cur, 414.0f + round(score_cur_bar.bound.width - score_cur.bound.width / 2), 492.0f);
	Object* achievement[5];
	Info text1 = createInfo("Graphic/Oswald-Light.ttf", "Enter old password", 345.0f, 327.0f, 30);
	Info text2 = createInfo("Graphic/Oswald-Light.ttf", "Enter new password", 345.0f, 413.0f, 30);
	Object w1 = createObject("Graphic/w.png", 317.0f, 315.0f);
	Object w2 = createObject("Graphic/t.png", 317.0f, 396.0f);
	for (int i = 0; i < 5; i++)
	{
		if (check1[i].first)
			achievement[i] = createObjectTest("Graphic/a_" + to_string(check1[i].second) + "_here.png", 405.0f + 127.0f * i, 547.0f );
		else 
			achievement[i] = createObjectTest("Graphic/a_" + to_string(check1[i].second) + ".png", 405.0f + 127.0f * i, 547.0f );
	}
	while (page == 11)
	{
		Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
			{
				window.close();
				page = -1;
				return;
			}
			case Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					if (isHere(change_pw, mouse) && check == 0)
						check = -1;
					else if (isHere(w1.bound, mouse))
					{
						text1.check = true;
						text2.check = false;
					}
					else if (isHere(w2.bound, mouse))
					{
						text1.check = false;
						text2.check = true;
					}
					else if (!isHere(w1.bound, mouse) && !isHere(w2.bound, mouse))
					{
						text1.check = false;
						text2.check = false;
					}
				}
				break;
			}
			case Event::TextEntered:
			{
				texting(text2, event.text.unicode, 30);
				texting(text1, event.text.unicode, 30);
				break;
			}
			default:
				break;
			}
		}
		
		window.clear();
		window.draw(screen.draw);
		window.draw(home1.draw);
		window.draw(user_ava.draw);
		drawWhich(window, settings, mouse);
		drawWhich(window, revision, mouse);
		drawWhich(window, user, mouse);
		drawWhich(window, del, mouse);
		drawWhich(window, fav, mouse);
		drawWhich(window, pLeft, mouse);
		drawWhich(window, pRight, mouse);
		if (!check)
		{
			drawWhich(window, edit, mouse);
			drawWhich(window, change_pw, mouse);
		}
		else
		{
			window.draw(edit.first->draw);
			window.draw(change_pw.first->draw);
		}
		for (int i = 0; i < 5; i++)
			window.draw(achievement[i]->draw);
		window.draw(low_level.text);
		window.draw(high_level.text);
		window.draw(score_cur.text);
		window.draw(score_want.text);
		window.draw(username.text);
		window.draw(score_bar.draw);
		window.draw(score_cur_bar.draw);
		window.draw(level.text);
		int res = checkConfirmation(window, check, confirm_pw, mouse);
		if (check == -1)
		{
			window.draw(text1.text);
			window.draw(text2.text);
			drawText(window, text1);
			drawText(window, text2);
		}
		if (res == -1)
		{
			// changepw
		}
		window.display();
	}
	deallocate(settings);
	deallocate(user);
	deallocate(del);
	deallocate(fav);
	deallocate(pLeft);
	deallocate(pRight);
	deallocate(revision);
	deallocate(edit);
	deallocate(change_pw);
	deallocate(confirm_pw);
	for (int i = 0; i < 5; i++)
		delete achievement[i];
}