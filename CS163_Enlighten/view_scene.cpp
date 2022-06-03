#include "header.h"

void Scene1(RenderWindow &window, int &page)
{
    Object screen = createObject("Graphic/p1.png");
    Object b1 = createObject("Graphic/p1_search.png", 478.0f, 540.0f);
    Object b1_here = createObject("Graphic/p1_search_here.png", 478.0f, 540.0f);
    Event event;
    while (page == 1)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
            {
                window.close();
                return;
            }
            case Event::MouseButtonReleased:
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    switchPage(b1.bound, mouse, 2, page);
                }
                break;
            }
            default:
                break;
            }
        }
        window.clear();
        window.draw(screen.draw);
        drawWhich(window, b1_here, b1, mouse);
        window.display();
    }
}

void setRole(RenderWindow &window, int &page, bool &is_admin)
{
    Object screen = createObject("Graphic/p3.png");
    Object admin = createObject("Graphic/p3_admin.png", 572.0f, 262.0f);
    Object admin_here = createObject("Graphic/p3_admin_here.png", 572.0f, 262.0f);
    Object user = createObject("Graphic/p3_user.png", 222.0f, 262.0f);
    Object user_here = createObject("Graphic/p3_user_here.png", 222.0f, 262.0f);
    Event event;
    while (page == 2)
    {
        Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
            {
                window.close();
                return;
            }
            case Event::MouseButtonReleased:
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    if (isHere(admin.bound, mouse))
                    {
                        page = 3;
                        is_admin = true;
                        return;
                    }
                    if (isHere(user.bound, mouse))
                    {
                        page = 3;
                        is_admin = false;
                        return;
                    }
                }
                break;
            }
            default:
                break;
            }
        }
        window.clear();
        window.draw(screen.draw);
        drawWhich(window, admin_here, admin, mouse);
        drawWhich(window, user_here, user, mouse);
        window.display();
    }
}