/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** DLLoader
*/

#ifndef SRC_DLLOADER_HPP_
#define SRC_DLLOADER_HPP_

#include <dlfcn.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

template <typename T>
class DLLoader {
 public:
    DLLoader() = delete;
    // Opens a shared library
    // Throws a DLLoaderException if the library cannot be opened
    explicit DLLoader(std::string path) noexcept(false) {
        _libHandle = dlopen(path.c_str(), RTLD_LAZY);
        if (!_libHandle) throw DLLoaderException(dlerror());
    }
    // Returns an instance of the class defined in the shared library
    // Throws a DLLoaderException if the function creating the instance
    // is not found
    std::unique_ptr<T> &getInstance(std::string entrypoint) noexcept(false) {
        std::unique_ptr<T> (*create)(void) =
            reinterpret_cast<std::unique_ptr<T> (*)(void)>(
                dlsym(_libHandle, entrypoint.c_str()));

        if (create == NULL) throw DLLoaderException(dlerror());
        if (_instance == nullptr) _instance = create();
        return _instance;
    }
    // Switches the library to a new one
    // Throws a DLLoaderException if the previous library cannot be closed or if
    // the new library cannot be opened
    void switchLib(std::string path) noexcept(false) {
        _instance.reset(nullptr);
        if (dlclose(_libHandle) != 0) {
            _libHandle = NULL;
            throw DLLoaderException(dlerror());
        }
        _libHandle = dlopen(path.c_str(), RTLD_LAZY);
        if (!_libHandle) throw DLLoaderException(dlerror());
    }
    // Closes the shared library
    // Throws a DLLoaderException if the library cannot be closed
    ~DLLoader() noexcept(false) {
        _instance.reset(nullptr);
        if (dlclose(_libHandle) != 0) {
            _libHandle = NULL;
            throw DLLoaderException(dlerror());
        }
    }
    class DLLoaderException : public std::exception {
     public:
        explicit DLLoaderException(std::string message) noexcept
            : _message(message) {}
        ~DLLoaderException() noexcept {}
        const char *what() const noexcept override { return _message.c_str(); }

     private:
        std::string _message;
    };

 private:
    void *_libHandle;
    std::unique_ptr<T> _instance;
};
#endif  // SRC_DLLOADER_HPP_
