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