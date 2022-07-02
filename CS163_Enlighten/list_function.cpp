#pragma once
#include "header.h"
#include "test_function.h"
bool inVector(string str, vector <string> list, int& cur_id) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == str) {
			cur_id = i;
			return true;
		}
	}
	return false;
}

int likeStatus(string user, vector <pair<string, bool>> list, int& cur_id) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i].first == user) {
			cur_id = i;
			if (list[i].second == true)
				return 1;
			else
				return -1;
		}
	}
	return 0;
}
vector <pair<string, bool>> nullvector() {
	vector <pair<string, bool>> ret;
	return ret;
}

bool like_compare(UserDef x, UserDef y) {
	return x.like > y.like;
}
string cutWordtype(string x) {
	if (x.size() <= 3) return "";
	if (x[0] != '(') return "";
	string ret = "";
	for (auto ch : x) if (ch != ')') ret.push_back(ch);
	else {
		ret.push_back(')');
		return ret;
	}
	return "";
}
string cutDefinition(string x) {
	if (x.size() == 0) return "";
	if (x[0] != '(') return  x;
	bool flag = false;
	for (int i = 0; i < x.size(); i++) {
		if (x[i] == ')') {
			string ret = "";
			for (int j = i + 1; j < x.size(); j++)
				ret.push_back(x[j]);
			return ret;
		}
	}
	return "";
}
void saveDatasets(RenderWindow& window, Enlighten dataset)
{
	Object* a[3];
	for (int i = 0; i < 3; i++)
	{
		a[i] = createObjectTest("Graphic/e" + to_string(i + 1) + ".png");
	}
	int i = 0;
	
	// save dictionary

	for (Trie T : dataset.user_Trie){
		
		string path = T.path;
		while (path.size() && path.back() != '.') path.pop_back(); // make sure json file
		path += "json";
		clock_t start = clock();
		writeJson(T, path);
		//cout << "Save file " << T.name << ": Ok\n";
		cout << "Save file " << T.name<<  " in " << getTime(start, clock()) / 1000.0 << "s\n";
	}
	for (int loop = 0; loop < 3; loop++) {
		sleepHere(30.0);
		window.clear();
		window.draw(a[(i++) % 3]->draw);
		window.display();
	}
	// save history
	string path;
	if (dataset.is_admin) path = ADMIN;
	else path = USERS;

	update(dataset.username, SEARCH_HISTORY, dataset.history, path);
	// save fav
	
	update(dataset.username, FAVORITE_LIST, dataset.favorite, path);
	for (int i = 0; i < 3; i++)
		delete a[i];
}