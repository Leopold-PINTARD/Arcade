/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** DLLoader
*/

#ifndef SRC_DLLOADER_HPP_
    #define SRC_DLLOADER_HPP_

    #include <dlfcn.h>
    #include <memory>
    #include <string>
    #include <vector>

template <typename T>
class DLLoader {
 public:
    DLLoader() = delete;
    explicit DLLoader(std::string path) noexcept(false) {
        _libHandle = dlopen(path.c_str(), RTLD_LAZY);
        if (!_libHandle)
            throw DLLoaderException(dlerror());
    }
    std::unique_ptr<T> &getInstance(void) noexcept(false) {
        std::unique_ptr<T> (*create)(void) = reinterpret_cast<std::unique_ptr<T>
            (*)(void)>(dlsym(_libHandle, "create"));

        if (!create)
            throw DLLoaderException(dlerror());
        if (_instance == nullptr)
            _instance = create();
        return _instance;
    }
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
        const char *what() const noexcept override {
            return _message.c_str();
        }
     private:
        std::string _message;
    };

 private:
    void *_libHandle;
    std::unique_ptr<T> _instance;
};
#endif  // SRC_DLLOADER_HPP_
