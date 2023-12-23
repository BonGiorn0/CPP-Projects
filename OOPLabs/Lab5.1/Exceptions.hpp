#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>

class EmptySet : public std::exception{
public:
    EmptySet() = delete;
    EmptySet(const char *name);
    EmptySet(const EmptySet &other);

    const char *what() const noexcept;
    const char *getMethodName() const;
private:
    char methodName[50];
};

class NoFileFound : public std::exception{
public:
    NoFileFound() = delete;
    NoFileFound(const char *name);
    NoFileFound(const NoFileFound &other);

    const char *what() const noexcept;
    const char *getFileName() const;
private:
    char fileName[50];
};

class InputError : public std::exception{
public:
    InputError() = default;
    InputError(const InputError &other) = default;
    const char *what() const noexcept;
};
#endif
