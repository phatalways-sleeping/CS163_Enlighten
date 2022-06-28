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
vector <pair<string, bool>> nullvector() {
	vector <pair<string, bool>> ret;
	return ret;
}