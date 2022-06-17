#include "header.h"

int main()
{

    RenderWindow window;
    window.create(VideoMode(1112, 769), "CS163-Project");
    int page = 6;
    bool is_admin = false;
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
            logIn(window, page, is_admin);
            break;
        case 4:
            home(window, page, is_admin);
            break;
        case 5:
            wordDisplay(window, page, is_admin);
            break;
        case 6:
            myList(window, page, true);
            break;
        case 7:
            revision(window, page);
            break;

        default:
            return 0;
        }
    }
    return 0;
}