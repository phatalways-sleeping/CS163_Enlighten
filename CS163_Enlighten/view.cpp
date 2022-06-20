#pragma once
#include "header.h"

Object createObject(string s, float x, float y)
{
	Object me;
	me.txt.loadFromFile(s);
	me.draw.setTexture(me.txt);
	me.draw.setPosition(x, y);
	me.bound = me.draw.getGlobalBounds();
	return me;
}

Confirmation create()
{
	Confirmation root;
	root.board = createElement("p0", 200.0f, 271.0f);
	root.nah = createElement("p0_nah", 328.0f, 470.0f);
	root.of_course = createElement("p0_of_course", 590.0f, 470.0f);
	root.out = createElement("p0_return", 450.0f, 470.0f);
	return root;
}

Confirmation create(string b1, string o1, string o2, string o3)
{
	Confirmation root;
	root.board = createElement(b1, 200.0f, 271.0f);
	root.nah = createElement(o1, 328.0f, 470.0f);
	root.of_course = createElement(o2, 590.0f, 470.0f);
	root.out = createElement(o3, 450.0f, 470.0f);
	return root;
}

void deallocate(Confirmation &p)
{
	deallocate(p.board);
	deallocate(p.nah);
	deallocate(p.of_course);
	deallocate(p.out);
	return;
}

pair<Object *, Object *> createElement(string s, float x, float y)
{
	Object *a = createObjectTest("Graphic/" + s + ".png", x, y);
	Object *b = createObjectTest("Graphic/" + s + "_here.png", x, y);
	pair<Object *, Object *> cur = {a, b};
	return cur;
}

void deallocate(pair<Object *, Object *> &p)
{
	delete p.first, p.second;
	return;
}

void deallocate(SearchBar& p)
{
	delete p.search_info;
	deallocate(p.change);
	deallocate(p.add);
	deallocate(p.search);
	deallocate(p.search_history);
	deallocate(p.new_word);
}

Object *createObjectTest(string s, float x, float y)
{
	Object *me = new Object;
	me->txt.loadFromFile(s);
	me->draw.setTexture(me->txt);
	me->draw.setPosition(x, y);
	me->bound = me->draw.getGlobalBounds();
	return me;
}

Object createObject(string s)
{
	Object me;
	me.txt.loadFromFile(s);
	me.draw.setTexture(me.txt);
	me.bound = me.draw.getGlobalBounds();
	return me;
}

Object *createObjectTest(string s)
{
	Object *me = new Object;
	me->txt.loadFromFile(s);
	me->draw.setTexture(me->txt);
	me->bound = me->draw.getGlobalBounds();
	return me;
}

bool isHere(FloatRect &bound, Vector2f &mouse)
{
	return bound.contains(mouse);
}

Info createInfo(string s, float x, float y, unsigned int size)
{
	Info a;
	a.font.loadFromFile(s);
	a.text.setFont(a.font);
	a.text.setCharacterSize(size);
	a.text.setPosition(x, y);
	a.text.setFillColor(Color(53, 84, 87, 255));
	a.bound = a.text.getGlobalBounds();
	return a;
}

Info createInfo(string s, string info, float x, float y, unsigned int size)
{
	Info a;
	a.font.loadFromFile(s);
	a.text.setFont(a.font);
	a.text.setCharacterSize(size);
	a.text.setPosition(x, y);
	a.text.setFillColor(Color(53, 84, 87, 255));
	a.text.setString(info);
	a.bound = a.text.getGlobalBounds();
	return a;
}

Info *createInfoTest(string s, string info, float x, float y, unsigned int size)
{
	Info *a = new Info;
	a->font.loadFromFile(s);
	a->text.setFont(a->font);
	a->text.setCharacterSize(size);
	a->text.setPosition(x, y);
	a->text.setFillColor(Color(53, 84, 87, 255));
	a->text.setString(info);
	a->bound = a->text.getGlobalBounds();
	return a;
}

bool drawWhich(RenderWindow &window, Object a, Object b, Vector2f &mouse)
{
	if (isHere(a.bound, mouse))
	{
		window.draw(a.draw);
		return true;
	}
	window.draw(b.draw);
	return false;
}

bool drawWhich(RenderWindow &window, Object *a, Object *b, Vector2f &mouse)
{
	if (isHere(a->bound, mouse))
	{
		window.draw(a->draw);
		return true;
	}
	window.draw(b->draw);
	return false;
}

bool switchPage(FloatRect &bound, Vector2f &mouse, int k, int &page)
{
	if (isHere(bound, mouse))
	{
		page = k;
		return true;
	}
	return false;
}

void changePos(Object *a, Object *b, float x, float y)
{
	a->draw.setPosition(x, y);
	a->bound = a->draw.getGlobalBounds();
	b->draw.setPosition(x, y);
	b->bound = b->draw.getGlobalBounds();
}

void changePos(Object *a, float x, float y)
{
	a->draw.setPosition(x, y);
	a->bound = a->draw.getGlobalBounds();
}

void changePos(Info *a, float x, float y)
{
	a->text.setPosition(x, y);
	a->bound = a->text.getGlobalBounds();
}

void texting(Info &text, Uint32 unicode, unsigned int limit)
{
	if (text.check && (text.s.size() < limit || unicode == 8))
	{
		if (unicode == 8)
		{
			if (!text.s.empty())
				text.s.pop_back();
		}
		else
		{
			text.s += unicode;
		}
		text.text.setString(text.s);
	}
}

void texting(Info *&text, Uint32 unicode, unsigned int limit)
{
	if (text->check && (text->s.size() < limit || unicode == 8))
	{
		if (unicode == 8)
		{
			if (!text->s.empty())
				text->s.pop_back();
		}
		else
		{
			text->s += unicode;
		}
		text->text.setString(text->s);
	}
}

bool isHere(const pair<Object *, Object *> &a, Vector2f &mouse)
{
	return a.first->bound.contains(mouse);
}

bool drawWhich(RenderWindow &window, const pair<Object *, Object *> &a, Vector2f &mouse)
{
	if (isHere(a, mouse))
	{
		window.draw(a.second->draw);
		return true;
	}
	else
	{
		window.draw(a.first->draw);
		return false;
	}
}




void checkConfirmation(RenderWindow &window, int &check, const Confirmation &element, Vector2f &mouse)
{
	if (check == 0)
		return;
	if (check == -1)
	{
		window.draw(element.board.first->draw);
		drawWhich(window, element.nah, mouse);
		drawWhich(window, element.of_course, mouse);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (isHere(element.nah, mouse))
				check = 0;
			else if (isHere(element.of_course, mouse))
			{
				// do some thing here;
				check = 1;
			}
		}
	}
	else
	{
		window.draw(element.board.second->draw);
		drawWhich(window, element.out, mouse);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (isHere(element.out, mouse))
				check = 0;
		}
	}
	return;
}




void searching(RenderWindow &window, int &status, const SearchBar &s, Vector2f &mouse, int& add_status)
{
	switch (status)
	{
	case 1:
	{
		drawWhich(window, s.add, mouse);
		drawWhich(window, s.change, mouse);
		window.draw(s.board.draw);
		window.draw(s.search.second->draw);
		window.draw(s.search_info->text);
		drawWhich(window, s.search_history, mouse);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (!isHere(s.search, mouse))
			{
				status = 0;
			}
			if (isHere(s.add, mouse))
			{
				status = 2;
				add_status = -1;
			}
		}
		break;
	}
	case 2:
	{
		window.draw(s.add.first->draw);
		window.draw(s.change.first->draw);
		checkConfirmation(window, add_status, s.new_word, mouse);
		if (add_status == -1)
		{
			window.draw(s.enter_word.text);
			window.draw(s.enter_defi.text);
		}
	}
	default:
	{
		drawWhich(window, s.add, mouse);
		drawWhich(window, s.change, mouse);
		window.draw(s.search.first->draw);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (isHere(s.search, mouse))
			{
				status = 1;
			}
			if (isHere(s.add, mouse))
			{
				status = 2;
				add_status = -1;
			}
		}
		break;
	}
	}
}
