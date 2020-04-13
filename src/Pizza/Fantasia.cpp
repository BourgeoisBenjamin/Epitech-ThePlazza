/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Fantasia
*/

#include "Stock/Stock.hpp"
#include "Pizza/Fantasia.hpp"

using namespace Plazza;

Fantasia::Fantasia(PizzaSize size, long cookingMultiplier) :
    APizza(PizzaType::Fantasia, size, cookingMultiplier)
{
    _ingredients[Ingredient::DOE] = 1;
    _ingredients[Ingredient::TOMATO] = 1;
    _ingredients[Ingredient::EGGPLANT] = 1;
    _ingredients[Ingredient::GOAT_CHEESE] = 1;
    _ingredients[Ingredient::CHIEF_LOVE] = 1;
}

bool Fantasia::cook() const
{
    std::this_thread::sleep_for(std::chrono::seconds(4 * _cookingMultiplier));
    return true;
}
