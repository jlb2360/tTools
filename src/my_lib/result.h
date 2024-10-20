// Define a custom Result type

#include <variant>

template <typename T, typename E>
class Result {
public:
    // Store either a value (T) or an error (E)
    std::variant<T, E> result;

    // Constructors for success and error
    Result(T value) : result(value) {}
    Result(E error) : result(error) {}

    // Check if the result is a success
    bool is_ok() const {
        return std::holds_alternative<T>(result);
    }

    // Get the value (if it exists)
    T value() const {
        return std::get<T>(result);
    }

    // Get the error (if it exists)
    E error() const {
        return std::get<E>(result);
    }
};
