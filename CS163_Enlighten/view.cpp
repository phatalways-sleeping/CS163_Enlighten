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
