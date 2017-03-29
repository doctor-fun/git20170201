#ifndef WD_SOCKETIO_H
#define WD_SOCKETIO_H

#include "Noncopyable.h"
#include <sys/types.h>

namespace wd
{

class SocketIO : Noncopyable
{
public: 
    explicit SocketIO(int sockfd)
    : sockfd_(sockfd)
    {
    }

    ssize_t readn(char *buf, size_t count);
    ssize_t writen(const char *buf, size_t count);
    ssize_t readline(char *usrbuf, size_t maxlen);
private:
    ssize_t recv_peek(char *buf, size_t len);

    const int sockfd_;
};

}//end namespace wd
#endif //WD_SOCKETIO_H
