#include <functional>
#include <iostream>

std::function<int(int)> mult(std::function<int(int)> calc, int multiplier)
{
    return [calc, multiplier](int number)
    {
        return calc(number) * multiplier;
    };
}

std::function<int(int)> add(std::function<int(int)> calc, int term)
{
    return [calc, term](int number)
    {
        return calc(number) + term;
    };
}

std::function<int(int)> square(std::function<int(int)> calc)
{
    return [calc](int number)
    {
        int result = calc(number);
        return result * result;
    };
}

int main()
{
    std::function<int(int)> calc = [](int number)
    {
        return number;
    };

    calc = mult(calc, 3);
    calc = add(calc, 5);
    calc = square(calc);

    std::cout << calc(4) << '\n';

    return 0;
}
