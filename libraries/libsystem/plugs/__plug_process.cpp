
#include <abi/Syscalls.h>

#include <libsystem/Assert.h>
#include <libsystem/core/CString.h>
#include <libsystem/core/Plugs.h>
#include <libutils/Path.h>

static int _cached_this = -1;

int __plug_process_this()
{
    if (_cached_this == -1)
    {
        assert(hj_process_this(&_cached_this) == SUCCESS);
    }

    return _cached_this;
}

static bool _has_cached_name = false;

static char _cached_name[PROCESS_NAME_SIZE];

const char *__plug_process_name()
{
    if (!_has_cached_name)
    {
        assert(hj_process_name(_cached_name, PROCESS_NAME_SIZE) == SUCCESS);
    }

    return _cached_name;
}

Result __plug_process_launch(Launchpad *launchpad, int *pid)
{
    return hj_process_launch(launchpad, pid);
}

void __plug_process_exit(int code)
{
    hj_process_exit(code);

    ASSERT_NOT_REACHED();
}

Result __plug_process_cancel(int pid)
{
    return hj_process_cancel(pid);
}

Result __plug_process_sleep(int time)
{
    return hj_process_sleep(time);
}

Result __plug_process_wait(int pid, int *exit_value)
{
    return hj_process_wait(pid, exit_value);
}
