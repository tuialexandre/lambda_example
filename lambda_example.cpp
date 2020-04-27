#include <iostream>
#include <limits>

using namespace std;

template <typename Fn, typename In, typename Out>
constexpr Out fold(Fn function, In* input, size_t length, Out initial) {
    Out result = initial;
    for(size_t i{}; i < length; i++){
        result = function(result, input[i]);
    }
    return result;
}

template <typename Fn, typename In>
constexpr bool all(Fn function, In* input, size_t length) {
    bool result = true;
    for(size_t i{}; i < length; i++){
        result = result && function(input[i]);
    }
    return result;
}

int main() {
    int data[]{ 100, 200, 300, 400, 500 };
    size_t data_len = sizeof(data)/ sizeof(data[0]);
    
    auto sum = fold([](auto x, auto y) { return x + y; }, data, data_len, 0);
    cout << "Sum: " << sum << endl;

    auto max = fold([](auto x, auto y) { return x > y ? x : y; }, data, data_len, numeric_limits<int>::min());
    cout << "Max: " << max << endl;

    auto min = fold([](auto x, auto y) { return x < y ? x : y; }, data, data_len, numeric_limits<int>::max());
    cout << "Min: " << min << endl;

    int greater_than = 200;
    auto greater = fold([greater_than](auto x, auto y) { return y > greater_than ? ++x : x; }, data, data_len, 0);
    cout << "Greater than " << greater_than << ": " << greater << endl;

    auto all_gt100 = all([](auto x) { return x > 100; }, data, data_len);
    cout << "All elements greater than 100? " << all_gt100 << endl;

    auto all_gt50 = all([](auto x) { return x > 50; }, data, data_len);
    cout << "All elements greater than 50? " << all_gt50 << endl;
    return 0;
}
