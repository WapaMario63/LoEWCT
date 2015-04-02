#include "loewct.h"

void Threads::runLoginServThread()
{
    win.startLoginServer(true);

    emit loggedConsole(win.logMsgFromThread);
}
