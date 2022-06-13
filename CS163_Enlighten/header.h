#pragma once

#include "struct_and_dependencies.h"

//------------------Login Functions---------------------
bool login(string username, string password, string path, Node *&search_history, Node *&favorite_list);
void changePassword(string username, string new_pass, string path);
bool createNewAccount(string username, string password, string path);
void update(string username, int CASE, Node *list, string path);

bool contains(Node *head, string value);
void insert(Node *&head, string value);
void remove(Node *&head, string value);


//-------------------Objects/Text to draw---------------
Object createObject(string s, float x, float y);
Object *createObjectTest(string s, float x, float y);
Object createObject(string s);
Object *createObjectTest(string s);
Info createInfo(string s, float x, float y, unsigned int size);
Info createInfo(string s, string info, float x, float y, unsigned int size);
Info *createInfoTest(string s, string info, float x, float y, unsigned int size);
pair<Object *, Object *> createElement(string s, float x, float y);
void deallocate(pair<Object *, Object *> &p);
//-------------------Features--------------------------
bool isHere(FloatRect &bound, Vector2f &mouse);
bool isHere(const pair<Object *, Object *> &a, Vector2f &mouse);
bool drawWhich(RenderWindow &window, const pair<Object *, Object *> &a, Vector2f &mouse);
bool drawWhich(RenderWindow &window, Object a, Object b, Vector2f &mouse);
bool drawWhich(RenderWindow &window, Object *a, Object *b, Vector2f &mouse);
bool switchPage(FloatRect &bound, Vector2f &mouse, int k, int &page);
void changePos(Object *a, Object *b, float x, float y);
void changePos(Object *a, float x, float y);
void changePos(Info *a, float x, float y);
void texting(Info &text, Uint32 unicode, unsigned int limit);
void texting(Info *&text, Uint32 unicode, unsigned int limit);

//---------------------Scene--------------------------
void Scene1(RenderWindow &window, int &page);
void setRole(RenderWindow &window, int &page, bool &is_admin);
void logIn(RenderWindow &window, int &page, bool is_admin);
void home(RenderWindow &window, int &page, bool &is_admin);
