#include "header.h"
//------------------Struct(cont)-------------------------





struct AdminButton
{
	enum class AButton { Add = 1, Rem = 2, Edit = 3, Del = 4 };
	enum class State { Close = 0, Open = 1, DoSth = 2 };
	AButton button = AButton::Add;
	State status = State::Close;
	pair<Object*, Object*> choose = createElement("b_burger", 1058.0f, 340.0f);
	pair<Object*, Object*> add = createElement("b_add", 1070.0f, 295.0f);
	pair<Object*, Object*> rem = createElement("b_rem", 1021.0f, 314.0f);
	pair<Object*, Object*> edit = createElement("b_edit", 1021.0f, 367.0f);
	pair<Object*, Object*> del = createElement("b_del", 1070.0f, 384.0f);
	pair<Object*, Object*> p_add[3], p_del[3], p_push[3], p_rem = createElement("p_del", 1040.0f, 243.0f);
	Object border = createObject("Graphic/b_border.png", 1021.0f, 295.0f);
	Confirmation confirm = create();
	AdminButton()
	{
		for (int i = 0; i < 3; i++)
		{
			// create p_...
			p_add[i] = createElement("p_add", 980.0f, 410.0f + i * 110.0f);
			p_del[i] = createElement("p_del", 980.0f, 410.0f + i * 110.0f);
			p_push[i] = createElement("p_push", 980.0f, 410.0f + i * 110.0f);
		}
	}

	bool draw(RenderWindow& window, Vector2f& mouse, int& check, int count, int& index, Edit& enter_word)
	{
		switch (status)
		{
		default:
			drawWhich(window, choose, mouse);
			if (isHere(choose, mouse))
			{
				status = State::Open;
			}
			return false;
		case State::Open:
			window.draw(choose.second->draw);
			drawWhich(window, add, mouse);
			drawWhich(window, edit, mouse);
			drawWhich(window, rem, mouse);
			drawWhich(window, del, mouse);
			if (!isHere(border.bound, mouse))
			{
				status = State::Close;
			}
			return false;
		case State::DoSth:
			int res = 0;
			if (button == AButton::Add)
			{
				window.draw(add.second->draw);
				window.draw(edit.first->draw);
				window.draw(rem.first->draw);
				window.draw(del.first->draw);
				for (int i = 0; i < count; i++)
				{
					drawWhich(window, p_add[i], mouse);
					if (isHere(p_add[i], mouse))
					{
						check = -1;
						index = i;
					}
				}
				res = checkConfirmation(window, check, confirm, mouse);
			}
			else if (button == AButton::Del)
			{
				window.draw(del.second->draw);
				window.draw(add.first->draw);
				window.draw(rem.first->draw);
				window.draw(edit.first->draw);
				for (int i = 0; i < count; i++)
				{
					drawWhich(window, p_del[i], mouse);
					if (isHere(p_del[i], mouse))
					{
						check = -1;
						index = i;
					}
				}
				res = checkConfirmation(window, check, confirm, mouse);
			}
			else if (button == AButton::Edit)
			{
				window.draw(edit.second->draw);
				window.draw(add.first->draw);
				window.draw(rem.first->draw);
				window.draw(del.first->draw);
				res = checkConfirmation(window, check, enter_word.new_word, mouse);
			}
			else
			{
				window.draw(rem.second->draw);
				window.draw(add.first->draw);
				window.draw(del.first->draw);
				window.draw(edit.first->draw);
				if (isHere(p_rem, mouse))
				{
					check = -1;
					index = -1;
					//index = i;
				}
				res = checkConfirmation(window, check, confirm, mouse);
			}
			if (res == -1)
				return true;
			break;
			return false;
		}
	}
	void deleteButton()
	{
		deallocate(add);
		deallocate(rem);
		deallocate(edit);
		deallocate(del);
		deallocate(confirm);
	}
};
