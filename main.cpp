#include <iostream>

#include "MessageBoxPool.h"

int main()
{
    auto pool = MessageBoxPool::get_instance();

    {
        auto msgbox = pool->get_object("1", "2");
        std::cout << msgbox->get_title() << std::endl;
        std::cout << msgbox->get_text() << std::endl;
    }

    {
        auto msgbox = pool->get_object("3", "4");
        std::cout << msgbox->get_title() << std::endl;
        std::cout << msgbox->get_text() << std::endl;
    }
    pool->remove_instance();
}
