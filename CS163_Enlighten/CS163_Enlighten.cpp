#pragma once
#include "header.h"

int main()
{
    // trie_revision_testing("Datasets5000.txt");
    // trie_autocorrect("Datasets5000.txt");
    Enlighten dataset;
    string username;
    dataset.dictionary_name.push_back("Eng/Vie");
    dataset.dictionary_name.push_back("Vie/Eng");
    dataset.dictionary_name.push_back("Eng/Eng");
    dataset.dictionary_name.push_back("Slang");
    dataset.dictionary_name.push_back("Emoji");
    RenderWindow window;
    window.create(VideoMode(1112, 769), "CS163-Project");
    int page = 1;
    bool is_admin = false, is_fav = true;
    loadingDataset(window, dataset, page, 3);

    while (window.isOpen())
    {
        switch (page)
        {
        case 1:
            // load Trie
            Scene1(window, page, dataset);
            break;
        case 2:
            setRole(window, page, is_admin, dataset);
            break;
        case 3:
            dataset.history.clear();
            dataset.favorite.clear();
            logIn(window, page, is_admin, username, dataset.favorite, dataset.history, dataset);
            break;
        case 4:
            home(window, page, is_admin, username, is_fav, dataset.history, dataset);
            break;
        case 5:
            wordDisplay(window, page, is_admin, is_fav, dataset);
            break;
        case 6:
            myList(window, page, is_fav, dataset);
            break;
        case 7:
            revision(window, page, dataset);
            break;
        case 8:
            settings(window, page, true, dataset);
            break;

        default:
            window.close();
            return 0;
        }
    }
    return 0;
}