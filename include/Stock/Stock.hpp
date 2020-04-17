/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_STOCK_HPP
#define CPP_PLAZZA_2019_STOCK_HPP

#include <map>
#include <memory>
#include <chrono>
#include "Pizza/IPizza.hpp"

namespace Plazza
{
    enum Ingredient
    {
        DOE = 0,
        TOMATO,
        GRUYERE,
        HAM,
        MUSHROOMS,
        STEAK,
        EGGPLANT,
        GOAT_CHEESE,
        CHIEF_LOVE,
    };

    static const Ingredient availableIngredients[] = {DOE, TOMATO, GRUYERE, HAM, MUSHROOMS, STEAK, EGGPLANT, GOAT_CHEESE, CHIEF_LOVE};

    class Stock
    {
        public:
            explicit Stock(float regenerateTime);
            ~Stock() = default;
            Stock(const Stock &other) = default;
            Stock &operator=(const Stock &rhs) = default;

            void regenerateIngredient();

            void reserveIngredient(const std::shared_ptr<IPizza> &pizza);

            [[nodiscard]] bool canCookPizza(const std::shared_ptr<IPizza> &pizza) const;

            void setRegenerateTime(float regenerateTime);
            [[nodiscard]] float getRegenerateTime() const;

            [[nodiscard]] const std::map<size_t, size_t> &getStock() const;

        private:
            float _regenerateTime;
            std::chrono::steady_clock::time_point _beginRegeneration;

            std::map<size_t , size_t> _stock;
    };
}

#endif //CPP_PLAZZA_2019_STOCK_HPP
