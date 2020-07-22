#include "Dialog.h"
#include "TomatoState.h"

class Dialog;
TomatoState::~TomatoState()
{
}
/*
 * 开始状态
 */
StartState::StartState(Dialog* context)
    :_context(context) 
{
    _context->changeUiStart();
}
  
void StartState::handle(Event event)
{
    if (event == BUTTON)
    {
        _context->setState(new ProcessState(_context));
    }
    else if (event == TIME_OUT_5)
    {
        _context->setState(new CancleState(_context));
    }
    else
    {
    }
}

StartState::~StartState()
{
}
/*
 * 取消状态
 */
CancleState::CancleState(Dialog* context)
    :_context(context) 
{
    _context->changeUiCancle();
}
  
void CancleState::handle(Event event)
{
    if (event == TIME_OUT_29)
    {
        _context->show();
        _context->setState(new StartState(_context));
    }
}

CancleState::~CancleState()
{
}

/*
 * 进行中状态
 */
ProcessState::ProcessState(Dialog* context)
    :_context(context) 
{
    _context->changeUiProcess();
}
  
void ProcessState::handle(Event event)
{
    if (event == TIME_OUT_25)
    {
        //TODO 番茄计数+1
        _context->show();
        _context->setState(new EndState(_context));
    }
}

ProcessState::~ProcessState()
{
}

/*
 * 结束(休息)状态
 */
EndState::EndState(Dialog* context)
  :_context(context) 
{
  _context->changeUiEnd();
}
  
void EndState::handle(Event event)
{
    if (event == TIME_OUT_29)
    {
        _context->show();
        _context->setState(new StartState(_context));
    }

}

EndState::~EndState()
{
}

