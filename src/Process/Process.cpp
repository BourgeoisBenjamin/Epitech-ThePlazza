/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Process
*/

#include "Process/Process.hpp"
#include "Error/Error.hpp"
#include "Factory/Factory.hpp"
#include <sys/types.h>
#include <sys/wait.h>

#include <signal.h>

using namespace Plazza;

Process::Process() : _pid(fork())
{
    if (_pid == -1)
        throw ProcessError("Fail to fork", "Process");
}

Process::Process(std::shared_ptr<IIPC> &ipc) : _ipc(ipc), _pid(fork())
{
    if (_pid == -1)
        throw ProcessError("Fail to fork", "Process");
}

Process::~Process()
{
    if (!isAlive())
        return;
    kill(_pid, SIGKILL);
}

pid_t Process::getPid() const
{
    return (_pid);
}

bool Process::isAlive() const
{
    if (!_ipc->exist())
        return (false);
    waitpid(_pid, NULL, WNOHANG);
    return kill(_pid, 0) == 0;
}

bool Process::isInChild() const
{
    return ((!_pid));
}

bool Process::read()
{
    return (_ipc->read());
}

bool Process::send()
{
    return (_ipc->send());
}

bool Process::send(const std::string &data)
{
    _ipc->send(data);
    return (true);
}

const std::string Process::getData()
{
    return (_ipc->getData());
}

void Process::createIPC(int arg1, int arg2, IIPC::IPCType type)
{
    Factory factory(arg1, arg2, type);

    _ipc = factory.createIPC();
}

std::shared_ptr<IIPC> Process::getIpc() const
{
    return (_ipc);
}