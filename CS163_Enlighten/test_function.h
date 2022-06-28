#pragma once

vector <pair<string, bool>> nullvector();
int likeStatus(string user, vector <pair<string, bool>> list, int& cur_id);
bool like_compare(UserDef x, UserDef y);