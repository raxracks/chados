#include "taskbar/windows/TaskManager.h"
#include "taskbar/widgets/CPUGraph.h"
#include "taskbar/widgets/ProcessTable.h"
#include "taskbar/widgets/RAMGraph.h"

using namespace Widget;

namespace Taskbar
{

Taskbar::Taskbar() : Window(WINDOW_RESIZABLE)
{
    _model = make<TaskModel>();

    _update = own<Async::Timer>(1000, [this] {
        _model->update();
    });

    _update->start();
}

RefPtr<Element> Taskbar::build()
{
    // clang-format off

    return min_size({700, 500},
        vflow({
            //titlebar(Graphic::Icon::get("memory"), "Task Manager"),
            fill(process_table(_model)),
            separator(),
            min_height(128,
                panel(
                    hflow({
                        fill(cpu_graph(_model)),
                        separator(),
                        fill(ram_graph(_model)),
                    })
                )
            ),
        })
    );

    // clang-format on
}

} // namespace TaskManager
