/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Order
*/

#include "Order/Order.hpp"
#include "Error/Error.hpp"
#include <algorithm>
#include <iostream>

using namespace Plazza;

Order::Order(const std::string &order) : _order(order)
{
    static int id = 0;
    std::string tmpOrder = order;

    _id = id++;
    try {
        while (1)
            nextPizza(tmpOrder);
    } catch(const OrderError &e) {
    } catch(const ParserError &e) {
        throw e;
    }
}

Order::~Order()
{
}

const std::string Order::nextWord(std::string &order) const
{
    size_t i = 0;
    std::string word = "";

    for (; order[i] && (order[i] == ';' || order[i] == ' ' || order[i] == '\t'); i++);
    for (; order[i] && order[i] != ' ' && order[i] != ';' && order[i] != '\t'; i++) {
        word += order[i];
    }
    for (; order[i] && (order[i] == ';' || order[i] == ' ' || order[i] == '\t'); i++);
    order.erase(0, i);
    return (word);
}

void Order::nextPizza(std::string &order)
{
    std::map<std::string, IPizza::PizzaType> types = {
        {"regina", IPizza::Regina},
        {"margarita", IPizza::Margarita},
        {"americana", IPizza::Americana},
        {"fantasia", IPizza::Fantasia},
    };

    std::map<std::string, IPizza::PizzaSize> sizes = {
        {"S", IPizza::S},
        {"M", IPizza::M},
        {"L", IPizza::L},
        {"XL", IPizza::XL},
        {"XXL", IPizza::XXL},
    };

    std::string typeWord = nextWord(order);
    std::string sizeWord = nextWord(order);
    std::string numberWord = nextWord(order);
    IPizza::PizzaType type;
    IPizza::PizzaSize size;
    int nb = 0;

    try {
        type = types[typeWord];
        size = sizes[sizeWord];
    } catch(const std::exception& e) {
        throw ParserError("Wrong command", "nextPizza");
    }

    if (numberWord[0] != 'x')
        throw ParserError("Wrong argument, cannot find the number", "nextPizza");
    std::string tmpNumber = "";
    for (size_t i = 1; numberWord[i]; i++) {
        tmpNumber += numberWord[i];
    }
    try {
        nb = std::stoi(tmpNumber);
    } catch(const std::exception& e) {
        throw ParserError("Wrong argument, wrong number", "nextPizza");
    }
    for (int i = 0; i < nb; i++) {
        _pizzas.push_back(std::make_tuple(type, size, false, false));
    }
    if (order.size() == 0)
        throw OrderError("No more pizza");
}

std::unique_ptr<IPizza> Order::getNextPizza() const
{
    auto pizza = std::find_if_not(_pizzas.begin(), _pizzas.end(), [](const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza) {
        return (std::get<3>(pizza));
    });

    if (pizza == _pizzas.end())
        throw OrderError("No more pizza");
    std::map<IPizza::PizzaType, std::unique_ptr<IPizza> (Order::*)(IPizza::PizzaSize) const> pizzas;

    pizzas[IPizza::Americana] = &Order::createAmericana;
    pizzas[IPizza::Fantasia] = &Order::createFantasia;
    pizzas[IPizza::Margarita] = &Order::createMargarita;
    pizzas[IPizza::Regina] = &Order::createRegina;
    return ((this->*pizzas[std::get<0>(*pizza)])(std::get<1>(*pizza)));
}

void Order::addPizzaFinish(IPizza::PizzaType type, IPizza::PizzaSize size)
{
    if (isFinish())
        throw OrderError("Unable to add pizza", "addPizzaFinish");
    auto pizza = std::find_if(_pizzas.begin(), _pizzas.end(), [&type, &size](const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza) {
        if (std::get<2>(pizza))
            return (false);
        if (std::get<0>(pizza) == type && std::get<1>(pizza) == size)
            return (true);
        return (false);
    });

    std::get<2>(*pizza) = true;
}

void Order::pack()
{
}

bool Order::isFinish() const
{
    auto pizza = std::find_if_not(_pizzas.begin(), _pizzas.end(), [](const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza) {
        return (std::get<2>(pizza));
    });

    return (pizza == _pizzas.end());
}

std::unique_ptr<IPizza> Order::createMargarita(IPizza::PizzaSize size) const
{
    return (std::make_unique<Margarita>(size));
}

std::unique_ptr<IPizza> Order::createAmericana(IPizza::PizzaSize size) const
{
    return (std::make_unique<Americana>(size));
}

std::unique_ptr<IPizza> Order::createRegina(IPizza::PizzaSize size) const
{
    return (std::make_unique<Regina>(size));
}

std::unique_ptr<IPizza> Order::createFantasia(IPizza::PizzaSize size) const
{
    return (std::make_unique<Fantasia>(size));
}

int Order::getId() const
{
    return (_id);
}

const std::vector<std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t>> &Order::getPizzas() const
{
    return (_pizzas);
}

std::ostream &operator<<(std::ostream &os, const std::unique_ptr<Plazza::Order> &order)
{
    std::map<IPizza::PizzaType, std::string> types = {
        {IPizza::Regina, "regina"},
        {IPizza::Margarita, "margarita"},
        {IPizza::Americana, "americana"},
        {IPizza::Fantasia, "fantasia"},
    };

    std::map<IPizza::PizzaSize, std::string> sizes = {
        {IPizza::S, "S"},
        {IPizza::M, "M"},
        {IPizza::L, "L"},
        {IPizza::XL, "XL"},
        {IPizza::XXL, "XXL"},
    };

    const std::vector<std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t>> pizzas = order->getPizzas();

    os << "----------------Order " << order->getId() << "----------------" << std::endl;
    std::for_each(pizzas.begin(), pizzas.end(), [&os, &types, &sizes](const std::tuple<IPizza::PizzaType, IPizza::PizzaSize, finish_t, send_t> &pizza) {
        os << "1 " << types[std::get<0>(pizza)] << " of size " << sizes[std::get<1>(pizza)] << std::endl;
    });
    return (os);
}