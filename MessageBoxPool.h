#pragma once

#include <memory>
#include <vector>
#include <thread>
#include <mutex>

#include "MessageBox.h"

typedef std::function<void (MessageBox*)> Deleter;

class MessageBoxPool
{
public:
    template <typename... Args>
    std::unique_ptr<MessageBox, Deleter> get_object(Args... args);

    inline size_t get_pool_size() const
    {
        return m_pool.size();
    }

private:
    std::vector<MessageBox*> m_pool;
    std::mutex m_pool_mutex;
    Deleter m_custom_deleter;

public:
    static MessageBoxPool* get_instance();
    static void remove_instance();

private:
    static MessageBoxPool* s_instance;

    MessageBoxPool();
    ~MessageBoxPool();
    MessageBoxPool(const MessageBoxPool&) = delete;
    MessageBoxPool& operator=(const MessageBoxPool&) = delete;
};

template <typename... Args>
std::unique_ptr<MessageBox, Deleter> MessageBoxPool::get_object(Args... args)
{
    {
        std::lock_guard<std::mutex> lock(m_pool_mutex);
        if (!m_pool.empty()) {
            std::array<std::string, sizeof...(args)> string_args = {args...};
            m_pool.back()->set_title(string_args[0]);
            m_pool.back()->set_text(string_args[1]);
            std::unique_ptr<MessageBox, Deleter> ptr_to_obj(m_pool.back(), m_custom_deleter);
            m_pool.pop_back();
            return ptr_to_obj;
        }
    }
    return std::unique_ptr<MessageBox, Deleter>(new MessageBox(args...), m_custom_deleter);
}

