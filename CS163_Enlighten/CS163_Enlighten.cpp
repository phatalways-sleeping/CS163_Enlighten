#pragma once
#include "header.h"
int main()
{
    trie_revision_testing("Datasets5000.txt");
    //trie_autocorrect("Datasets5000.txt");
    vector<string> favorite;
    vector<string> history;
    string username;

    RenderWindow window;
    window.create(VideoMode(1112, 769), "CS163-Project");
    int page = 1;
    bool is_admin = false, is_fav = true;

    while (window.isOpen())
    {
        switch (page)
        {
        case 1:
            Scene1(window, page);
            break;
        case 2:
            setRole(window, page, is_admin);
            break;
        case 3:
            logIn(window, page, is_admin, username, favorite, history);
            break;
        case 4:
            home(window, page, is_admin, username, is_fav, history);
            break;
        case 5:
            wordDisplay(window, page, is_admin, is_fav);
            break;
        case 6:
            myList(window, page, is_fav);
            break;
        case 7:
            revision(window, page);
            break;
        case 8:
            settings(window, page, true);

        default:
            return 0;
        }
    }
    return 0;
}