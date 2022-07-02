#pragma once
#include "header.h"
#include "test_function.h"

int main()
{
    Trie emo;
    //insert(emo, "CMIIW","Correct me if I'm wrong");
    //readJson(emo, "ENLIGHTEN_DATA/DATA/ENGLISH_DEFINITIONS/ENG.json");
    //while (1);
 
    // trie_autocorrect("Datasets5000.txt");
    Enlighten dataset;
    string &username = dataset.username;
    PlaySound(TEXT("hmc.wav"), NULL, SND_LOOP | SND_ASYNC);
    RenderWindow window;
    window.create(VideoMode(1112, 769), "CS163-Project");
    int page = 1, level = 0;
    bool &is_admin = dataset.is_admin, is_fav = true, difficulty = true;
    loadingDataset(window, dataset, page, 1);
    while (window.isOpen())
    {
        switch (page)
        {
        case 1:
            Scene1(window, page, dataset);
            break;
        case 2:
            setRole(window, page, dataset);
            break;
        case 3:
            dataset.history.clear();
            dataset.favorite.clear();
            logIn(window, page, username, dataset);
            break;
        case 4:
            home(window, page, username, is_fav, dataset);
            break;
        case 5:
            wordDisplay(window, page, is_fav, dataset, "nhuvinh");
            break;
        case 6:
            myList(window, page, dataset);
            break;
        case 7:
            revision(window, page, dataset, level, difficulty);
            break;
        case 8:
            settings(window, page, true, dataset);
            break;
        case 9:
            testQA(window, page, dataset, level, difficulty);
            break;
        case 11:
            profile(window, page, dataset);
            break;
        case 12:
            searchResult(window, page, "hello", dataset, is_fav, 1, 1);
            break;
        case 13:
            myList(window, page, dataset);
            break;
        default: {
            saveDatasets(window, dataset);
            window.close();
            break;
        }
        }
    }
    //writeUserProfile(PROFILE, dataset.username, dataset.user);
 
    return 0;
}