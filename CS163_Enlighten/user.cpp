#include "header.h"

//struct Profile {
//	string username;
//	vector<string> dates_login;
//	long level;
//	double scores;
//	bool badges[5];
//};

struct Level
{
	vector<pair<int, int>> require;

	Level(vector<int> s)
	{
		for (int i = 0; i < s.size(); i++)
		{
			require.push_back({ s[i], i + 2 });
		}
	}
};

bool doSthXTimes(vector<string>& input, int x)
{
	return (int)input.size() >= x;
}

void checkAchievements(Enlighten& p)
{
	p.user.badges[0] = (p.user.dates_login.size() >= 3);
	p.user.badges[1] = (p.user.streak >= 5);
	p.user.badges[2] = (p.history.size() >= 100);
	p.user.badges[3] = (p.user.level >= 2);
	p.user.badges[4] = (p.user.level >= 10);
	return;
}

void setLevel(Profile& a, Level& s)
{
	a.level = 1;
	for (int i = 0; i < s.require.size(); i++)
	{
		if (a.scores < s.require[i].first)
		{
			a.level = s.require[i].second - 1;
			break;
		}
		a.level++;
	}
}
