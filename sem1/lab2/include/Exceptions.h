#pragma once
#include <stdexcept>

class CapacityExceededException : public std::exception
{
public:
    const char *what() const noexcept override { return "Вместимость склада превышена"; }
};

class InvalidWeightException : public std::exception
{
public:
    const char *what() const noexcept override { return "Недопустимый вес груза"; }
};

class PassengerLimitException : public std::exception
{
public:
    const char *what() const noexcept override { return "Лимит пассажиров превышен"; }
};

class UnloadErrorException : public std::exception
{
public:
    const char *what() const noexcept override { return "Невозможно выгрузить больше, чем доступно"; }
};

class HazardousCargoException : public std::exception
{
public:
    const char *what() const noexcept override { return "Обнаружен опасный груз"; }
};

class InvalidStatusException : public std::exception
{
public:
    const char *what() const noexcept override { return "Неверный статус транспортного средства"; }
};

class FuelErrorException : public std::exception
{
public:
    const char *what() const noexcept override { return "Неверное количество топлива"; }
};

class DriverAssignmentException : public std::exception
{
public:
    const char *what() const noexcept override { return "Ошибка назначения драйвера"; }
};

class RoutePlanningException : public std::exception
{
public:
    const char *what() const noexcept override { return "Планирование маршрута не удалось"; }
};

class ShipmentErrorException : public std::exception
{
public:
    const char *what() const noexcept override { return "Операция по доставке не удалась"; }
};

class OrderValidationException : public std::exception
{
public:
    const char *what() const noexcept override { return "Проверка заказа не удалась"; }
};

class FreightDimensionException : public std::exception
{
public:
    const char *what() const noexcept override { return "Недопустимые размеры груза"; }
};

class InvalidPaymentException : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Недопустимый тип оплаты";
    }
};

class InvalidArgumentException : public std::runtime_error
{
public:
    InvalidArgumentException(const std::string &message = "Недопустимый аргумент")
        : std::runtime_error(message) {}
};
