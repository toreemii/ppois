#include "../include/Notification.h"

Notification::Notification(std::string message, std::string type) : message(message), type(type) {}

std::string Notification::getMessage()
{
    return message;
}
std::string Notification::getType()
{
    return type;
}

void Notification::sendNotification(Client *client, std::string message)
{
    std::cout << "Уведомление (" << type << ") отправлено " << client->getClientId()
              << ": " << message << std::endl;
}

void Notification::notifyOrderStatus(Order *order)
{
    sendNotification(
        order->getCustomer(),
        std::string("Заказ ") + order->getOrderId() +
            " статус: " + statusToString(order->getStatus()));
}

std::string Notification::statusToString(OrderStatus status)
{
    return "Pending";
}

void Notification::notifyTicketStatus(Passenger *passenger)
{
    sendNotification(passenger->getOrder()->getCustomer(),
                     "Билет для пассажира " + passenger->getPassengerId() + " статус: " +
                         passenger->getTicket()->getTicketStatus());
}