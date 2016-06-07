#include "MessageBoxPool.h"

MessageBoxPool* MessageBoxPool::s_instance = nullptr;

MessageBoxPool::MessageBoxPool()
{
    m_custom_deleter = [this] (MessageBox* ptr) {
        std::lock_guard<std::mutex> lock(this->m_pool_mutex);
        this->m_pool.push_back(ptr);
    };
}

MessageBoxPool::~MessageBoxPool()
{
    for (auto ptr : m_pool) {
        delete ptr;
        ptr = nullptr;
    }
    m_pool.clear();
}

MessageBoxPool* MessageBoxPool::get_instance()
{
    if (!s_instance) {
        s_instance = new MessageBoxPool();
    }
    return s_instance;
}

void MessageBoxPool::remove_instance()
{
    delete s_instance;
    s_instance = nullptr;
}
