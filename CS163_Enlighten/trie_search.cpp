#pragma once
#include "header.h"

vector <string> search_result(Trie T, string keyword, int nums) {
	Node* info = search(T, keyword);
	vector <string> res;
	if (info)
		for (auto s : info->def) {
			res.push_back(s);
			if (res.size() == nums) break;
		}
	return res;
}
vector <string> &search_result(Trie &T, string keyword) {
	Node* info = search(T, keyword);
	vector <string> res;
	if (info)
		return info->def;
	return res;
}

bool search_result(Trie T, string keyword, int nums, vector <string>& res) {
	Node* info = search(T, keyword);
	if (info) {
		res = info->def;
		return true;
	}
	/*for (auto s : info->def) {
		res.push_back(s);
		if (res.size() == nums) break;
	}*/
	return false;
}