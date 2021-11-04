module;

export import client;
import server;

#include <coroutine>
#include <stdlib.h>

export module test_module;

export class promise_type
{
public:
    /**
     * @brief Метод, определяющий, остановим ли мы корутину при старте
     * @return std::suspend_never{}
     */
    auto initial_suspend()noexcept
    {
        return std::suspend_never{};
    }
    /**
     * @brief Метод, определяющий, остановим ли мы корутину в конце
     * @return std::suspend_always{}
     */
    auto final_suspend()noexcept
    {
        return std::suspend_always{};
    }
    /**
     * @brief Метод, вызываемый корутиной
     * @returт coroutine_handle::from_promise
     */
    auto get_return_object()
    {
        return std::coroutine_handle<promise_type>::from_promise(*this);
    }
    /**
     * @brief Метод, определяющий, что делаем при возврате void
     */
    void return_void()
    {

    }
    /**
     * @brief Метод, определяющий, что делаем при необработаном исключении
     */
    void unhandled_exception()
    {
        exit(9);
    }
};

export void double_minus(int& a, int b)
{
    a -= b * 2;
}
