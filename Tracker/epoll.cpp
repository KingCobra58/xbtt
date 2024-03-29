#include "epoll.h"

#ifndef WIN32
#include <unistd.h>
#endif

Cepoll::~Cepoll()
{
#ifdef EPOLL
  if (m_fd != -1)
    close(m_fd);
#endif
}

int Cepoll::create()
{
#ifdef EPOLL
  return m_fd = epoll_create(1);
#else
  return 0;
#endif
}

int Cepoll::ctl(int op, int fd, int events, void* p)
{
#ifdef EPOLL
  epoll_event e;
  e.data.ptr = p;
  e.events = events;
  return epoll_ctl(m_fd, op, fd, &e);
#else
  return 0;
#endif
}

int Cepoll::wait(epoll_event* events, int maxevents, int timeout)
{
#ifdef EPOLL
  return epoll_wait(m_fd, events, maxevents, timeout);
#else
  return 0;
#endif
}
