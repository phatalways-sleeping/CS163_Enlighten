#include "header.h"

bool login(string username, string password, string path, Node *&search_history, Node *&favorite_list)
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
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i][0] == username && v[i][1] == password)
        {
            int j = 3;
            while (v[i][j] != "favorite_list")
                insert(search_history, v[i][j++]);
            j += 1;
            while (j < v[i].size())
                insert(favorite_list, v[i][j++]);
            return true;
        }
    }
    return false;
}

void changePassword(string username, string new_pass, string path)
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
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i][0] == username)
        {
            v[i][1] = new_pass;
            break;
        }
    }
    file.close();
    ofstream f(path, ios::out);
    if (f.is_open())
    {
        for (int i = 0; i < v.size(); i++)
        {
            for (int j = 0; j < v[i].size(); j++)
            {
                f << v[i][j] << ',';
            }
            f << '\n';
        }
    }
    f.close();
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
        for (int i = 0; i < v.size(); i++)
        {
            for (int j = 0; j < v[i].size(); j++)
            {
                f << v[i][j] << ',';
            }
            f << '\n';
        }
    }
    f.close();
    return true;
}

void update(string username, int CASE, Node *list, string path)
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
            for (int i = 0; i < v.size(); i++)
            {
                if (v[i][0] == username)
                {
                    f << v[i][0] << ',' << v[i][1] << ',' << "search_history" << ',';
                    while (list)
                    {
                        f << list->data << ',';
                        list = list->next;
                    }
                    bool check = false;
                    for (int j = 3; j < v[i].size(); j++)
                    {
                        if (v[i][j] == "favorite_list")
                            check = true;
                        if (check)
                            f << v[i][j] << ',';
                    }
                }
                else
                {
                    for (int j = 0; j < v[i].size(); j++)
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
            for (int i = 0; i < v.size(); i++)
            {
                if (v[i][0] == username)
                {
                    for (int j = 0; j < v[i].size(); j++)
                    {
                        f << v[i][j] << ',';
                        if (v[i][j] == "favorite_list")
                            break;
                    }
                    while (list)
                    {
                        f << list->data << ',';
                        list = list->next;
                    }
                }
                else
                {
                    for (int j = 0; j < v[i].size(); j++)
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