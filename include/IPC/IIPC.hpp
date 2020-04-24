/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** IIPC
*/

#ifndef IIPC_HPP_
#define IIPC_HPP_

#include <string>

namespace Plazza
{
    class IIPC {
        public:
            enum IPCType {
                SOCKET,
                PIPE
            };

            enum Relation {
                PARENT = 0,
                CHILD
            };

        public:
            virtual ~IIPC() = default;

            virtual bool read() = 0;
            virtual const std::string getData() = 0;

            virtual bool send() = 0;
            virtual void send(const std::string &msg) = 0;
            [[nodiscard]] virtual bool exist() const = 0;
            virtual void setRelation(Relation relation) = 0;
            virtual Relation getRelation() const = 0;
            virtual const std::string &getBuffer() const = 0;

        private:
    };

} // namespace Plazza

#endif /* !IIPC_HPP_ */
