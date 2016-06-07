#include "MessageBox.h"

#include <iostream>

MessageBox::MessageBox()
    : m_okBtn(new Widget())
{
    std::cout << "Default ctor\n";
}

MessageBox::MessageBox(const std::string& title, const std::string& text)
    : m_title(title)
    , m_text(text)
    , m_okBtn(new Widget())
{
    std::cout << "Custom ctor\n";
}

MessageBox::~MessageBox()
{
    delete m_okBtn;
    m_okBtn = nullptr;
    std::cout << "dtor\n";
    std::cout << "title: " << m_title << std::endl;
    std::cout << "text: " << m_text << std::endl;
}

void MessageBox::set_text(const std::string& text)
{
    m_text = text;
}

const std::string& MessageBox::get_text() const
{
    return m_text;
}

void MessageBox::set_title(const std::string& title)
{
    m_title = title;
}

const std::string& MessageBox::get_title() const
{
    return m_title;
}
