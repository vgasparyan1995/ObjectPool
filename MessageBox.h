#pragma once

#include <string>

class Widget
{
public:
    virtual ~Widget() {}
};

class MessageBox : Widget
{
public:
    MessageBox();
    MessageBox(const std::string& title, const std::string& text);
    MessageBox(const MessageBox&) = delete;
    MessageBox& operator=(const MessageBox&) = delete;
    ~MessageBox();

    void set_text(const std::string& text);
    const std::string& get_text() const;
    void set_title(const std::string& title);
    const std::string& get_title() const;

private:
    std::string m_title;
    std::string m_text;
    Widget* m_okBtn;
};
