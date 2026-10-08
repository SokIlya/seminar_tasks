#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <thread>

struct PaymentResult
{
    bool success;
    double cashback;
};

int random_delay(int minimum, int maximum)
{
    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(minimum, maximum);
    return distribution(generator);
}

PaymentResult pay_by_card(double amount)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(random_delay(300, 700)));
    std::cout << "Payment by card\n";
    return {true, amount * 0.03};
}

PaymentResult pay_by_cash(double)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(random_delay(100, 300)));
    std::cout << "Payment by cash\n";
    return {true, 0};
}

PaymentResult pay_by_sbp(double amount)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(random_delay(150, 450)));
    std::cout << "Payment by SBP\n";
    return {true, amount * 0.01};
}

std::function<PaymentResult(double)> check_balance(
    std::function<PaymentResult(double)> payment, double& balance)
{
    return [payment, &balance](double amount)
    {
        if (amount <= 0)
        {
            std::cout << "Invalid amount\n";
            return PaymentResult{false, 0};
        }

        if (amount > balance)
        {
            std::cout << "Not enough money\n";
            return PaymentResult{false, 0};
        }

        PaymentResult result = payment(amount);
        if (result.success)
        {
            balance -= amount;
        }
        return result;
    };
}

std::function<PaymentResult(double)> measure_time(
    std::function<PaymentResult(double)> payment)
{
    return [payment](double amount)
    {
        auto start = std::chrono::steady_clock::now();
        PaymentResult result = payment(amount);
        auto finish = std::chrono::steady_clock::now();

        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
        std::cout << "Payment time: " << milliseconds.count() << " ms\n";
        return result;
    };
}

std::function<PaymentResult(double)> add_cashback(
    std::function<PaymentResult(double)> payment, double& cashback_balance)
{
    return [payment, &cashback_balance](double amount)
    {
        PaymentResult result = payment(amount);
        if (result.success)
        {
            cashback_balance += result.cashback;
            std::cout << "Cashback: " << result.cashback << '\n';
        }
        return result;
    };
}

int main()
{
    double balance = 5000;
    double cashback_balance = 0;
    double amount;
    int payment_type;

    std::cout << "1 - card, 2 - cash, 3 - SBP\n";
    std::cin >> payment_type;
    std::cout << "Amount: ";
    std::cin >> amount;

    std::function<PaymentResult(double)> payment;

    if (payment_type == 1)
    {
        payment = pay_by_card;
    }
    else if (payment_type == 2)
    {
        payment = pay_by_cash;
    }
    else if (payment_type == 3)
    {
        payment = pay_by_sbp;
    }
    else
    {
        std::cout << "Unknown payment type\n";
        return 0;
    }

    payment = check_balance(payment, balance);
    payment = measure_time(payment);
    payment = add_cashback(payment, cashback_balance);

    PaymentResult result = payment(amount);

    if (result.success)
    {
        std::cout << "Balance: " << balance << '\n';
        std::cout << "Cashback balance: " << cashback_balance << '\n';
    }

    return 0;
}
