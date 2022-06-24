#pragma once
#include "header.h"

void resetInfo(Info& a, string s)
{
	a.s = "";
	a.text.setString(s);
	a.check = false;
}



void resetInfo(Info*& a, string s)
{
	a->s = "";
	a->text.setString(s);
	a->check = false;
}

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
	root.nah = createElement("p0_cancel", 328.0f, 470.0f);
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

Confirmation create(string b1, string o1, string o2, string o3, int x)
{
	Confirmation root;
	root.board = createElement(b1, 200.0f, 271.0f);
	root.nah = createElement(o1, 328.0f, 534.0f);
	root.of_course = createElement(o2, 590.0f, 534.0f);
	root.out = createElement(o3, 450.0f, 470.0f);
	changePos(root.board.first, 200.0f, 150.0f);
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

void deallocate(SearchBar &p)
{
	delete p.search_info;
	deallocate(p.change);
	deallocate(p.add);
	deallocate(p.search);
	deallocate(p.search_history);
	deallocate(p.new_word);
	for (int i = 0; i < 3; i++)
	{
		deallocate(p.SE[i]);
		delete p.result[i];
	}
	p.switch_dict.deallocateDic();
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

void drawText(RenderWindow &window, Info a)
{
	if (a.check)
	{
		a.s += '|';
		a.text.setString(a.s);
		window.draw(a.text);
		a.s.pop_back();
		a.text.setString(a.s);
	}
	else
		window.draw(a.text);
}

void drawText(RenderWindow &window, Info *a)
{
	if (a->check)
	{
		a->s += '|';
		a->text.setString(a->s);
		window.draw(a->text);
		a->s.pop_back();
		a->text.setString(a->s);
	}
	else
		window.draw(a->text);
}

void drawLongText(RenderWindow& window, Info a) {
	drawLongText(window, a, 50);
}

void drawLongText(RenderWindow& window, Info a, int max_size) {
	if (a.s.size() <= max_size) {
		a.text.setString(a.s);
		window.draw(a.text);
	}
	else {
		a.text.setString(a.s.substr(0, max_size) + "...");
		window.draw(a.text);
		a.text.setString(a.s);
	}
}

void drawLongText(RenderWindow& window, Info a, bool show_full, int max_size) { 
	if (!show_full) {
		drawLongText(window, a, max_size);
	}
	vector <string> words = splitword(a.s);
	int cur_size = 0;
	string str = "";
	for (auto s: words){
		if (cur_size + s.size() > max_size) {
			str.push_back('\n');
			cur_size = 0;
			
		}
		cur_size += s.size() + 1;
		str += s;
		str.push_back(' ');
	}
	a.text.setString(str);
	window.draw(a.text);
	a.text.setString(a.s);
}
void drawLongText(RenderWindow& window, Info *a) {
	drawLongText(window, a, 50);
}

void drawLongText(RenderWindow& window, Info *a, int max_size) {
	if (a->s.size() <= max_size) {
		a->text.setString(a->s);
		window.draw(a->text);
	}
	else {
		a->text.setString(a->s.substr(0, max_size) + "...");
		window.draw(a->text);
		a->text.setString(a->s);
	}
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

bool switchPage(FloatRect &bound, Vector2f &mouse, int k, int &page, bool &change, bool true_or_false)
{
	if (isHere(bound, mouse))
	{
		page = k;
		change = true_or_false;
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
	if (unicode == 9)
		return;
	if (unicode == 13 || unicode == '\n')
		return;
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
	if (unicode == 9)
		return;
	if (unicode == 13 || unicode == '\n')
		return;
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

int checkString(Info a)
{
	int res = 0;
	while (!a.s.empty() && a.s.back() != '\n')
	{
		res++;
		a.s.pop_back();
	}
	return res;
}


void texting_endl(Info& text, Uint32 unicode, unsigned int limit)
{
	if (unicode == 9)
		return;
	if (text.check)
	{
		int res = checkString(text);
		if (checkString(text) % limit == 0 && res && unicode != 8)
		{
			text.s += "\n";
		}
		if (unicode == 8)
		{
			if (!text.s.empty())
				text.s.pop_back();
		}
		else if (unicode == 13)
		{
			text.s += "\n";
		}
		else
		{
			text.s += unicode;
		}
		text.text.setString(text.s);
	}
}
void texting_endl(Info*& text, Uint32 unicode, unsigned int limit)
{
	if (unicode == 9)
		return;
	if (text->check && (text->s.size() < limit || unicode == 8))
	{
		if (unicode == 8)
		{
			if (!text->s.empty())
				text->s.pop_back();
		}
		else if (unicode == 13)
		{
			text->s += "\n";
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

void LeftRight::draw(RenderWindow &window, Vector2f &mouse)
{
	for (int i = 0; i < 3; i++)
	{
		drawWhich(window, left[i], mouse);
		drawWhich(window, right[i], mouse);
	}
}

void LeftRight::draw(RenderWindow &window, Vector2f &mouse, int x)
{
	drawWhich(window, left[x], mouse);
	drawWhich(window, right[x], mouse);
}

void LeftRight::deleteLR()
{
	for (int i = 0; i < 3; i++)
	{
		deallocate(left[i]);
		deallocate(right[i]);
	}
}

LeftRight::LeftRight()
{
	left[0] = createElement("left", 352.0f, 130.0f);
	right[0] = createElement("right", 376.0f, 130.0f);
	left[1] = createElement("left1", 1005.0f, 195.0f);
	right[1] = createElement("right1", 1035.0f, 195.0f);
	left[2] = createElement("left1", 688.0f, 717.0f);
	right[2] = createElement("right1", 718.0f, 717.0f);
}
LeftRight::LeftRight(int x)
{
	left[0] = createElement("left", 352.0f, 130.0f);
	right[0] = createElement("right", 376.0f, 130.0f);
	left[1] = createElement("left1", 1005.0f, 195.0f);
	right[1] = createElement("right1", 1035.0f, 195.0f);
	left[2] = createElement("left1", 660.0f, 726.0f);
	right[2] = createElement("right1", 690.0f, 726.0f);
}