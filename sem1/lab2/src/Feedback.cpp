#include "../include/Feedback.h"

Feedback::Feedback(int rating, std::string comment, Client *client, Order *order)
    : rating(rating), comment(comment), client(client), feedbackOrder(order) {}

int Feedback::getRating()
{
    return rating;
}

void Feedback::submitFeedback(Order *order, int rate, std::string comment)
{
    feedbackOrder = order;
    std::cout << "Отзыв на заказ отправлен" << order->getOrderId() << ": Отзыв " << rate << std::endl;
}
void Feedback::escalateToManager(Manager *manager)
{
    std::cout << "Отзыв передан менеджеру" << manager->getEmployeeId() << std::endl;
}
