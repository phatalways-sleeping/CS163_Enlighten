#include "header.h"

void settings(RenderWindow &window, int &page, const bool &is_admin, Enlighten &dataset)
{
	Object screen = createObject("Graphic/border.png");
	pair<Object *, Object *> home = createElement("home", 0.0f, 168.0f);
	pair<Object *, Object *> fav = createElement("p4_fav", 963.0f, 31.0f);
	pair<Object *, Object *> user = createElement("p4_user", 1010.0f, 30.0f);
	pair<Object *, Object *> del = createElement("p4_del", 1056.0f, 32.0f);
	Object settings1 = createObject("Graphic/settings1.png", 0.0f, 448.0f);
	pair<Object *, Object *> revision = createElement("revision", 0.0f, 308.0f);
	pair<Object *, Object *> bar[3], next_bar[3];
	Info word = createInfo("Graphic/bahnschrift.ttf", "Settings", 402.0f, 127.0f, 21);
	Confirmation confirm = create(), confirm_pw = create("change_pw", "p0_cancel", "p0_ok", "p0_return");
	LeftRight left_right(1);
	Info text1 = createInfo("Graphic/Oswald-Light.ttf", "Enter old password", 345.0f, 327.0f, 30);
	Info text2 = createInfo("Graphic/Oswald-Light.ttf", "Enter new password", 345.0f, 413.0f, 30);
	Object w1 = createObject("Graphic/w.png", 317.0f, 315.0f);
	Object w2 = createObject("Graphic/t.png", 317.0f, 396.0f);
	for (int i = 0; i < 3; i++)
	{
		bar[i] = createElement("p8_" + to_string(i + 1), 360.0f, 267.0f + 125.0f * i);
		next_bar[i] = createElement("p8_1_" + to_string(i + 1), 360.0f, 267.0f + 125.0f * i);
	}
	Event event;
	int check = 0;
	string c1 = "", c2 = "";
	Status button = ResetDict;
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
					switchPage(del.first->bound, mouse, 1, page);
					switchPage(fav.first->bound, mouse, 6, page);
					switchPage(home.first->bound, mouse, 4, page);
					switchPage(revision.first->bound, mouse, 7, page);
					if (check == 0)
					{
						if (is_admin)
						{
							if ((int)button < 4)
							{
								if (isHere(bar[0], mouse))
								{
									button = ResetDict;
									check = -1;
								}
								else if (isHere(bar[1], mouse))
								{
									button = ResetAllDict;
									check = -1;
								}
							}
							else
							{
								if (isHere(bar[0], mouse))
								{
									button = ChangeData;
									c1 = "Enter dictionary";
									c2 = "Enter path";
									changeInfo(text1, text2, c1, c2);
									check = -1;
								}
								else if (isHere(bar[1], mouse))
								{
									button = ImportNew;
									c1 = "Enter dictionary";
									c2 = "Enter path";
									changeInfo(text1, text2, c1, c2);
									check = -1;
								}
								else if (isHere(bar[2], mouse))
								{
									button = RemDict;
									c1 = "Enter dictionary";
									c2 = "Enter reason";
									changeInfo(text1, text2, c1, c2);
									check = -1;
								}
							}
							if ((int)button > 3 && isHere(left_right.left[2], mouse))
							{
								button = ChangePw;
							}
							else if ((int)button < 4 && isHere(left_right.right[2], mouse))
							{
								button = RemDict;
							}
						}
						if (isHere(bar[2], mouse) && (int)button < 4)
						{
							button = ChangePw;
							c1 = "Enter old password";
							c2 = "Enter new password";
							changeInfo(text1, text2, c1, c2);
							check = -1;
						}
					}
					else if (check == -1)
					{
						if (isHere(w1.bound, mouse))
						{
							text1.check = true;
							text2.check = false;
							text1.text.setString(text1.s);
							if (text2.s == "") text2.text.setString(c2);
						}
						else if (isHere(w2.bound, mouse))
						{
							text2.check = true;
							text1.check = false;
							text2.text.setString(text2.s);
							if (text1.s == "") text1.text.setString(c1);
						}
						else
						{
							text1.check = false;
							text2.check = false;
							if (text1.s == "") text1.text.setString(c1);
							if (text2.s == "") text2.text.setString(c2);
						}
					}
				}
				break;
			}
			case Event::TextEntered:
			{
				texting(text2, event.text.unicode, 30);
				texting(text1, event.text.unicode, 30);
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
			if ((int)button < 4)
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
					drawWhich(window, next_bar[i], mouse);
				}
			}
			left_right.draw(window, mouse, 2);
		}
		else
		{
			if ((int)button < 4)
			{
				for (int i = 0; i < 3; i++)
				{
					window.draw(bar[i].first->draw);
				}
			}
			else
			{
				for (int i = 0; i < 3; i++)
				{
					window.draw(next_bar[i].first->draw);
				}
			}
			window.draw(left_right.left[2].first->draw);
			window.draw(left_right.right[2].first->draw);
		}
		int res;
		if (button == ResetAllDict || button == ResetDict || button == RemDict)
		{
			res = checkConfirmation(window, check, confirm, mouse);
		}
		else
		{
			res = checkConfirmation(window, check, confirm_pw, mouse);
		}
		if (button == ChangePw)
		{
			if (res == 1 && check == -1)
			{
				window.draw(text1.text);
				window.draw(text2.text);
				drawText(window, text1);
				drawText(window, text2);
			}
			else if (res == -1)
			{
				if (changePassword(dataset.username ,text1.s, text2.s, ADMIN)) 
				{
					// successfully change the password
				}
				else
				{
					// 
					check = 2;
				}
			}
		}
		else if (is_admin) 
		{
			if (res == -1)
			{
				if (button == ResetAllDict)
				{
					duplicateOriginalData(original_data_path, use_data);
				}
				else if (button == ResetDict)
				{
					string name = dataset.user_Trie[dataset.cur_id].path.substr(dataset.user_Trie[dataset.cur_id].path.find_last_of("\\//") + 1);
					int i = name.find_last_of(".");
					string folder = upper(name.substr(0, i));
					if (resetCurrentDataset(use_data, folder, original_data_path)) 
					{
						// successfully reset
					}
					else
					{
						check = 2;
					}
				}
				else if (button == ChangeData)
				{
					int i = dataset.user_Trie[dataset.cur_id].path.find_last_of("\\//");
					string folderpath = dataset.user_Trie[dataset.cur_id].path.substr(0, i);
					if (changeDataset(text2.s, folderpath)) { // text2.s only be the path to the FOLDER contains the datasets

					}
					else {
						check = 2;
					}
				}
				else if (button == RemDict)
				{
					int index_of_split = dataset.user_Trie[dataset.cur_id].path.find_last_of("\\//");
					string name = dataset.user_Trie[dataset.cur_id].path.substr(index_of_split + 1);
					if (removeDatasets(use_data + "//" + name) && removeDatasets(original_data_path + "//" + name)) {
						// successfully removed
					}
					else
					{
						check = 2;
					}
				}
				else if (button == ImportNew)
				{
					if (addNewDataSets(text2.s, original_data_path)) 
					{
						// successfully added
					}
					else
					{
						check = 2;
					}
				}
			}
			else if (res == 1 && button != ResetAllDict && button != ResetDict && button != RemDict && check == -1)
			{
				window.draw(text1.text);
				window.draw(text2.text);
				drawText(window, text1);
				drawText(window, text2);
			}
		}
		left_right.draw(window, mouse, 0);
		window.display();
	}
	for (int i = 0; i < 3; i++)
	{
		deallocate(bar[i]);
		deallocate(next_bar[i]);
	}
	deallocate(del);
	deallocate(fav);
	deallocate(home);
	deallocate(user);
	deallocate(confirm);
	deallocate(confirm_pw);
	left_right.deleteLR();
}