#pragma once

#include <libio/Connection.h>
#include <libio/Handle.h>

namespace IO
{

class Socket :
    public RawHandle
{
private:
    RefPtr<Handle> _handle;

    __nonmovable(Socket);

public:
    RefPtr<Handle> handle() { return _handle; }

    Socket(String &path, OpenFlag flags)
        : _handle{make<Handle>(path, flags)}
    {
    }

    static ResultOr<Connection> Socket::connect(String path)
    {
        int hnd;
        TRY(hj_handle_connect(&hnd, path.cstring(), path.length()));
        return Connection{make<Handle>(hnd)};
    }

    ResultOr<Connection> Socket::accept()
    {
        auto accept_result = _handle->accept();
        TRY(accept_result);
        return Connection{*accept_result};
    }
};

} // namespace IO
