#include "header.h"

int main()
{

    RenderWindow window;
    window.create(VideoMode(1112, 769), "CS163-Project", Style::Close);

    int page = 1;
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
        default:
            return 0;
        }
    }
    return 0;
}