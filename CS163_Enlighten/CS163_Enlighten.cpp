#pragma once
#include "header.h"

int main()
{
    // trie_revision_testing("Datasets5000.txt");
    // trie_autocorrect("Datasets5000.txt");
    Enlighten dataset;
    string username;

    RenderWindow window;
    window.create(VideoMode(1112, 769), "CS163-Project");
    int page = 1;
    bool is_admin = false, is_fav = true;
    loadingDataset(window, dataset, page);

    while (window.isOpen())
    {
        switch (page)
        {
        case 1:
            // load Trie
            Scene1(window, page);
            break;
        case 2:
            setRole(window, page, is_admin);
            break;
        case 3:
            dataset.history.clear();
            dataset.favorite.clear();
            logIn(window, page, is_admin, username, dataset.favorite, dataset.history);
            break;
        case 4:
            home(window, page, is_admin, username, is_fav, dataset.history);
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
            window.close();
            return 0;
        }
    }
    return 0;
}