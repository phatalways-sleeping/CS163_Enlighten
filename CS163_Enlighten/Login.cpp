#pragma once
#include "header.h"

bool login(string username, string password, string path, vector<string>& search_history, vector<string>& favorite_list)
{
    fstream file(path, ios::in);
    vector<vector<string>> v;
    vector<string> k;
    string line, word;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            k.clear();
            stringstream s(line);
            while (getline(s, word, ','))
                k.push_back(word);
            v.push_back(k);
        }
    }

    file.close();
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (v[i][0] == username && v[i][1] == password)
        {
            search_history.clear();
            favorite_list.clear();
            unsigned int j = 3;
            while (v[i][j] != "favorite_list") {
                if (v[i][j] != "")
                    search_history.push_back(v[i][j]);
                j++;
            }
            j += 1;
            while (j < v[i].size()) {
                if (v[i][j] != "")
                    favorite_list.push_back(v[i][j]);
                j++;
            }
            return true;
        }
    }
    return false;
}

bool changePassword(string username, string old_pass, string new_pass, string path)
{
    ifstream file(path, ios::in);
    vector<vector<string>> v;
    bool allow_to_modify = false;
    vector<string> k;
    string line, word;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            k.clear();
            stringstream s(line);
            while (getline(s, word, ','))
                k.push_back(word);
            v.push_back(k);
        }
    }
    file.close();
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (v[i][0] == username)
        {
            if (v[i][1] == old_pass) 
            {
                v[i][1] = new_pass;
                allow_to_modify = true;
            }
            break;
        }
    }
    if (allow_to_modify)
    {
        ofstream f(path, ios::out);
        if (f.is_open())
        {
            for (unsigned int i = 0; i < v.size(); i++)
            {
                for (unsigned int j = 0; j < v[i].size(); j++)
                {
                    f << v[i][j] << ',';
                }
                f << '\n';
            }
        }
        f.close();
    }
    return allow_to_modify;
}

bool createNewAccount(string username, string password, string path)
{
    ifstream file(path, ios::in);
    vector<vector<string>> v;
    vector<string> k;
    string line, word;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            k.clear();
            stringstream s(line);
            if (getline(s, word, ',') && word == username)
            {
                file.close();
                return false;
            }
            k.push_back(word);
            while (getline(s, word, ','))
            {
                k.push_back(word);
            }
            v.push_back(k);
        }
    }
    file.close();
    k.clear();
    k.push_back(username);
    k.push_back(password);
    k.push_back("search_history");
    k.push_back("favorite_list");
    v.push_back(k);
    ofstream f(path, ios::out);
    if (f.is_open())
    {
        for (unsigned int i = 0; i < v.size(); i++)
        {
            for (unsigned int j = 0; j < v[i].size(); j++)
            {
                f << v[i][j] << ',';
            }
            f << '\n';
        }
    }
    f.close();
    return true;
}

void update(string username, int CASE, vector<string>& list, string path)
{
    ifstream file(path, ios::in);
    vector<vector<string>> v;
    vector<string> k;
    string line, word;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            k.clear();
            stringstream s(line);
            while (getline(s, word, ','))
                k.push_back(word);
            v.push_back(k);
        }
    }
    file.close();
    ofstream f(path, ios::out);
    switch (CASE)
    {
    case SEARCH_HISTORY:
    {
        if (f.is_open())
        {
            for (unsigned int i = 0; i < v.size(); i++)
            {
                if (v[i][0] == username)
                {
                    f << v[i][0] << ',' << v[i][1] << ',' << "search_history" << ',';
                    for (unsigned int j = 0; j < list.size(); j++) f << list[j] << ",";
                    bool check = false;
                    for (unsigned int j = 3; j < v[i].size(); j++)
                    {
                        if (v[i][j] == "favorite_list")
                            check = true;
                        if (check)
                            f << v[i][j] << ',';
                    }
                }
                else
                {
                    for (unsigned int j = 0; j < v[i].size(); j++)
                    {
                        f << v[i][j] << ',';
                    }
                }
                f << '\n';
            }
        }
        break;
    }
    case FAVORITE_LIST:
    {
        if (f.is_open())
        {
            for (unsigned int i = 0; i < v.size(); i++)
            {
                if (v[i][0] == username)
                {
                    for (unsigned int j = 0; j < v[i].size(); j++)
                    {
                        f << v[i][j] << ',';
                        if (v[i][j] == "favorite_list")
                            break;
                    }
                    for (unsigned int j = 0; j < list.size(); j++) f << list[j] << ",";
                }
                else
                {
                    for (unsigned int j = 0; j < v[i].size(); j++)
                    {
                        f << v[i][j] << ',';
                    }
                }
                f << '\n';
            }
        }
        break;
    }
    default:
        break;
    }
    f.close();
}
void modify_csv(string username, int CASE, vector<string>& list, string path) /// overwrite fav/his list
{
    ifstream file(path, ios::in);
    vector<vector<string>> v;
    vector<string> k;
    string line, word;
    /*if (file.is_open())
    {
        while (getline(file, line))
        {
            k.clear();
            stringstream s(line);
            while (getline(s, word, ','))
                k.push_back(word);
            v.push_back(k);
        }
    }*/
    file.close();
    ofstream f(path, ios::out);
    switch (CASE)
    {
    case SEARCH_HISTORY:
    {
        if (f.is_open())
        {
            for (unsigned int i = 0; i < v.size(); i++)
            {
                if (v[i][0] == username)
                {
                    f << v[i][0] << ',' << v[i][1] << ',' << "search_history" << ',';
                    for (unsigned int j = 0; j < list.size(); j++) f << list[j] << ",";
                    bool check = false;
                    for (unsigned int j = 3; j < v[i].size(); j++)
                    {
                        if (v[i][j] == "favorite_list")
                            check = true;
                        if (check)
                            f << v[i][j] << ',';
                    }
                }
                else
                {
                    for (unsigned int j = 0; j < v[i].size(); j++)
                    {
                        f << v[i][j] << ',';
                    }
                }
                f << '\n';
            }
        }
        else cerr << "Can't open file " << path << endl;
        break;
    }
    case FAVORITE_LIST:
    {
        if (f.is_open())
        {
            for (unsigned int i = 0; i < v.size(); i++)
            {
                if (v[i][0] == username)
                {
                    for (unsigned int j = 0; j < v[i].size(); j++)
                    {
                        f << v[i][j] << ',';
                        if (v[i][j] == "favorite_list")
                            break;
                    }
                    for (unsigned int j = 0; j < list.size(); j++) f << list[j] << ",";
                }
                else
                {
                    for (unsigned int j = 0; j < v[i].size(); j++)
                    {
                        f << v[i][j] << ',';
                    }
                }
                f << '\n';
            }
        }
        else cerr << "Can't open file " << path << endl;
        break;
    }
    default:
        break;
    }
    f.close();
}