// Practice8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <algorithm>

enum class ProductType { Type1, Type2, Type3 };

struct Product {
    int number;
    ProductType type;
    union {
        char color[10];

        double weight;

        struct {
            double height;
            double width;
            double depth;
        } size;
    } details;

    // Конструктор для изделий первого вида (с цветом)
    Product(int num, ProductType t, const char* c) : number(num), type(t) {
        strncpy_s(details.color, c, sizeof(details.color));
    }

    // Конструктор для изделий второго вида (с весом)
    Product(int num, ProductType t, double w) : number(num), type(t) {
        details.weight = w;
    }

    // Конструктор для изделий третьего вида (с размерами)
    Product(int num, ProductType t, double h, double wid, double dep) : number(num), type(t) {
        details.size.height = h;
        details.size.width = wid;
        details.size.depth = dep;
    }

    Product() : number(0), type(ProductType::Type1), details({}) {} 
};

bool compareByWeight(const Product& a, const Product& b) {
    return a.details.weight < b.details.weight;
}

int main() {
    setlocale(LC_ALL, "Rus");

    // Массив изделий
    Product products[] = {
        Product(1, ProductType::Type2, 10.5),
        Product(2, ProductType::Type1, "red"),
        Product(3, ProductType::Type3, 1.5, 2.0, 0.8),
        Product(4, ProductType::Type2, 8.0),
        Product(5, ProductType::Type2, 11.0),
    };

    // Создание массива для изделий второго вида
    Product secondTypeProducts[10];
    int count = 0;
    for (Product& product : products) {
        if (product.type == ProductType::Type2) {
            secondTypeProducts[count++] = product;
        }
    }

    // Сортировка массива изделий второго вида по весу
    std::sort(secondTypeProducts, secondTypeProducts + count, compareByWeight);

    // Вывод отсортированного списка изделий второго вида
    std::cout << "Список изделий второго вида, упорядоченный по весу:" << std::endl;
    for (int i = 0; i < count; ++i) {
        std::cout << "Номер: " << secondTypeProducts[i].number << ", Вес: " << secondTypeProducts[i].details.weight << std::endl;
    }

    return 0;
}