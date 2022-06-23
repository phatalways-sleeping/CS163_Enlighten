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