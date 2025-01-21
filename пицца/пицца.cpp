#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

struct Item {
    std::string name;
    double price;
    int count;
};

const std::vector<Item> pizzas = {
    {"Маргарита", 450.0, 0},
    {"Пепперони", 500.0, 0},
    {"Четыре сыра", 550.0, 0},
    {"Гавайская", 480.0, 0},
    {"Мясная", 520.0, 0},
    {"Вегетарианская", 470.0, 0},
    {"Диабло", 530.0, 0}
};

const std::vector<Item> snacks = {
    {"Картофель фри", 120.0, 0},
    {"Куриные наггетсы", 150.0, 0},
    {"Сырные палочки", 140.0, 0},
    {"Кольца кальмара", 170.0, 0}
};

const std::vector<Item> drinks = {
    {"Кола", 100.0, 0},
    {"Фанта", 100.0, 0},
    {"Спрайт", 100.0, 0},
    {"Морс", 190.0, 0},
    {"Сок", 200.0, 0}
};

double calculateDiscounts(const std::vector<Item>& order, double& discount) {
    double total = 0.0;
    int pizzaCount = 0;
    int expensiveDrinksCount = 0;

    for (const auto& item : order) {
        total += item.price * item.count;

        if (std::find_if(pizzas.begin(), pizzas.end(), [&](const Item& pizza) { return pizza.name == item.name; }) != pizzas.end()) {
            pizzaCount += item.count;
        }

        if (std::find_if(drinks.begin(), drinks.end(), [&](const Item& drink) { return drink.name == item.name && drink.price >= 190; }) != drinks.end()) {
            expensiveDrinksCount += item.count;
        }
    }

    if (pizzaCount >= 5) {
        discount += (pizzaCount / 5) * pizzas[0].price; 
    }

    if (expensiveDrinksCount > 4) {
        discount += drinks[3].price; 
    }

    if (total > 1000.0) {
        discount += total * 0.15; 
    }

    return total - discount;
}

void showMenu(const std::string& title, const std::vector<Item>& items) {
    std::cout << "\n" << title << ":\n";
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << ". " << items[i].name << " - " << items[i].price << " рублей\n";
    }
    std::cout << "0. Пропустить\n";
}

void takeOrder(std::vector<Item>& order, const std::vector<Item>& menu) {
    while (true) {
        int choice;
        std::cout << "Введите номер пункта (или 0 для завершения): ";
        std::cin >> choice;

        if (choice == 0) break;

        if (choice > 0 && static_cast<size_t>(choice) <= menu.size()) {
            int count;
            std::cout << "Введите количество: ";
            std::cin >> count;
            if (count > 0) {
                order.push_back({ menu[choice - 1].name, menu[choice - 1].price, count });
            }
        }
        else {
            std::cout << "Некорректный ввод. Попробуйте снова.\n";
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    while (true) {
        std::vector<Item> order;
        double discount = 0.0;

        showMenu("Пиццы", pizzas);
        takeOrder(order, pizzas);

        showMenu("Закуски", snacks);
        takeOrder(order, snacks);

        showMenu("Напитки", drinks);
        takeOrder(order, drinks);

        double total = calculateDiscounts(order, discount);

        std::cout << "\nВаш заказ:\n";
        for (const auto& item : order) {
            std::cout << item.name << " x " << item.count << " = " << item.price * item.count << " рублей\n";
        }

        std::cout << "\nСумма без скидок: " << total + discount << " рублей\n";
        std::cout << "Скидка: " << discount << " рублей\n";
        std::cout << "Итого к оплате: " << total << " рублей\n";

        std::cout << "\nХотите сделать новый заказ? (y/n): ";
        char repeat;
        std::cin >> repeat;

        if (repeat != 'y' && repeat != 'Y') break;

        system("cls");
    }

    system("pause");
    return 0;
}
