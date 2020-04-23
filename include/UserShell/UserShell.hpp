/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** TODO: add description
*/

#ifndef CPP_PLAZZA_2019_USERSHELL_HPP
#define CPP_PLAZZA_2019_USERSHELL_HPP

#include <zconf.h>
#include <string>
#include "Error/Error.hpp"

namespace Plazza
{
    class UserShell
    {
        public:
            UserShell();
            ~UserShell() = default;
            UserShell(const UserShell &other) = default;
            UserShell &operator=(const UserShell &rhs) = default;

            bool isShellActive();

            std::string getUserCommand();
            void update();

        private:
            void checkInput();
            void resetCheck();

            void setReadFd(int fd);
            void setExceptFd(int fd);

            bool checkReadFdReady(int fd);
            bool checkExceptFd(int fd);

            void getData();

        private:
            fd_set _readFds;
            fd_set _exceptFds;
            struct timeval _timeout {};
            std::string _buffer;
            bool _active;
    };
}

#endif //CPP_PLAZZA_2019_USERSHELL_HPP
