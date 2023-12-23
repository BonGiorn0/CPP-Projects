#include "string.h"

#include "Exceptions.hpp"

EmptySet::EmptySet(const char *name){
    strcpy(methodName, name);
}

EmptySet::EmptySet(const EmptySet &other){
    strcpy(methodName, other.methodName);
}

const char *EmptySet::what() const noexcept{
    return "Cannot aply this action to emty set";
}

const char *EmptySet::getMethodName() const{
    return methodName;
}

NoFileFound::NoFileFound(const char *name){
    strcpy(fileName, name);
}

NoFileFound::NoFileFound(const NoFileFound &other){
    strcpy(fileName, other.fileName);
}

const char *NoFileFound::getFileName() const{
    return fileName;
}

const char *NoFileFound::what() const noexcept{
    return "Cannot open file";
}

const char *InputError::what() const noexcept{
    return "Input shoud be only integer numbers\n";
}