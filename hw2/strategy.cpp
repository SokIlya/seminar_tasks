#include <functional>
#include <iostream>

int calc_travel_time(int distance, std::function<int(int)> strategy)
{
    return strategy(distance);
}

int main()
{
    std::function<int(int)> walk = [](int distance)
    {
        return distance * 12;
    };

    std::function<int(int)> bicycle = [](int distance)
    {
        return distance * 4;
    };

    std::function<int(int)> bus = [](int distance)
    {
        return distance * 2 + 10;
    };

    int distance = 5;

    std::cout << calc_travel_time(distance, walk) << '\n';
    std::cout << calc_travel_time(distance, bicycle) << '\n';
    std::cout << calc_travel_time(distance, bus) << '\n';

    return 0;
}
