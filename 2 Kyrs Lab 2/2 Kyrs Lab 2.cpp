#include "DynamicArray.h"
#include <iostream>
#include <string>
#include <utility>
#include <locale.h>

static void printSection(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

int main() {
    setlocale(LC_ALL, "RUS");
    printSection("1. Конструктор по умолчанию и += элемента");
    DynamicArray a;
    a += 5;
    a += 3;
    a += 8;
    a += 1;
    std::cout << "a = " << a << '\n';
    std::cout << "size = " << a.size() << '\n';

    // ------------------------------------------------------------
    printSection("2. Конструктор из обычного массива");
    int raw[] = { 10, 20, 30, 40 };
    DynamicArray b(raw, 4);
    std::cout << "b = " << b << '\n';

    // ------------------------------------------------------------
    printSection("3. Конструктор копирования и оператор ==");
    DynamicArray c(b);
    std::cout << "c = " << c << '\n';
    std::cout << "b == c ? " << (b == c) << '\n';
    std::cout << "a != c ? " << (a != c) << '\n';

    // ------------------------------------------------------------
    printSection("4. Оператор [] и присваивание копированием");
    b[0] = 99;
    std::cout << "b после b[0] = 99: " << b << '\n';
    c = b;
    std::cout << "c = b: " << c << '\n';
    std::cout << "b == c ? " << (b == c) << '\n';

    // ------------------------------------------------------------
    printSection("5. Конструктор перемещения и перемещающее =");
    DynamicArray d(std::move(c));

    // Выводим результат ПЕРЕД обращением к пустому 'c', 
    // чтобы анализатор VS не ругался (убираем предупреждение C26800)
    std::cout << "d (перемещён из c) = " << d << '\n';
    std::cout << "c после перемещения: " << c << '\n';
    std::cout << "c.size() = " << c.size() << '\n';

    DynamicArray e;
    e = std::move(d);
    std::cout << "e = move(d) = " << e << '\n';
    std::cout << "d после move-присваивания: " << d << '\n';

    // ------------------------------------------------------------
    printSection("6. swap");
    DynamicArray x, y;
    x += 1; x += 2;
    y += 100; y += 200; y += 300;
    std::cout << "до swap: x = " << x << ", y = " << y << '\n';
    x.swap(y);
    std::cout << "после swap: x = " << x << ", y = " << y << '\n';

    // ------------------------------------------------------------
    printSection("7. find / min / max");
    DynamicArray f;
    f += 7; f += 2; f += 9; f += 4; f += 2;
    std::cout << "f = " << f << '\n';
    std::cout << "find(9) = " << f.find(9) << '\n';
    std::cout << "find(2) = " << f.find(2) << '\n';
    std::cout << "find(42) = " << f.find(42) << '\n';
    std::cout << "max = " << f.max() << '\n';
    std::cout << "min = " << f.min() << '\n';

    // ------------------------------------------------------------
    printSection("8. insertAt / removeAt");
    DynamicArray g;
    g += 10; g += 20; g += 30;
    std::cout << "g = " << g << '\n';
    std::cout << "insertAt(1, 15): " << g.insertAt(1, 15) << '\n';
    std::cout << "g = " << g << '\n';
    std::cout << "insertAt(100, 0): " << g.insertAt(100, 0) << '\n';
    std::cout << "removeAt(2): " << g.removeAt(2) << '\n';
    std::cout << "g = " << g << '\n';
    std::cout << "removeAt(100): " << g.removeAt(100) << '\n';

    // ------------------------------------------------------------
    printSection("9. removeValue / removeAll");
    DynamicArray h;
    h += 1; h += 2; h += 3; h += 2; h += 4; h += 2;
    std::cout << "h = " << h << '\n';
    std::cout << "removeValue(3): " << h.removeValue(3) << '\n';
    std::cout << "h = " << h << '\n';
    std::cout << "removeValue(42): " << h.removeValue(42) << '\n';
    h.removeAll(2);
    std::cout << "h после removeAll(2) = " << h << '\n';

    // ------------------------------------------------------------
    printSection("10. sort");
    DynamicArray s;
    s += 5; s += 1; s += 4; s += 2; s += 3;
    std::cout << "до sort: " << s << '\n';
    s.sort();
    std::cout << "после sort: " << s << '\n';

    // ------------------------------------------------------------
    printSection("11. Итераторы: begin / end");
    int sum = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        sum += *it;
    }
    std::cout << "сумма через итераторы = " << sum << '\n';

    const DynamicArray& cs = s;
    std::cout << "const-обход: ";
    for (auto it = cs.begin(); it != cs.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    // ------------------------------------------------------------
    printSection("12. insert(iterator) / erase(iterator)");
    DynamicArray it;
    it += 10; it += 20; it += 30;
    std::cout << "it = " << it << '\n';
    auto pos = it.begin();
    ++pos;
    it.insert(pos, 15);
    std::cout << "после insert(перед 20, 15): " << it << '\n';

    auto pos2 = it.begin();
    ++pos2;
    it.erase(pos2);
    std::cout << "после erase(15): " << it << '\n';

    // ------------------------------------------------------------
    printSection("13. erase(iterator, iterator) — диапазон [first, last)");
    DynamicArray r;
    r += 1; r += 2; r += 3; r += 4; r += 5; r += 6;
    std::cout << "r = " << r << '\n';
    auto first = r.begin(); ++first;
    auto last = r.begin(); ++last; ++last; ++last;
    r.erase(first, last);
    std::cout << "после erase([1,4)): " << r << '\n';

    // ------------------------------------------------------------
    printSection("14. operator+ (элемент) и operator+ (массив)");
    DynamicArray p;
    p += 1; p += 2;
    DynamicArray q = p + 3;
    std::cout << "p = " << p << '\n';
    std::cout << "p + 3 = " << q << '\n';
    std::cout << "p после + не изменился: " << p << '\n';

    DynamicArray u, v;
    u += 1; u += 2;
    v += 3; v += 4;
    DynamicArray w = u + v;
    std::cout << "u + v = " << w << '\n';
    u += v;
    std::cout << "u += v -> u = " << u << '\n';

    // ------------------------------------------------------------
    printSection("15. Потоковый ввод");
    DynamicArray in;
    std::cin >> in;
    std::cout << "введено: " << in << '\n';

    return 0;
}