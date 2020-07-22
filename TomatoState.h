#ifndef _TOMATO_STATE_H_
#define _TOMATO_STATE_H_

class Dialog;
/*
 * 事件
 */
enum Event
{
    TIME_OUT_5 = 5,
    TIME_OUT_25 = 25,
    TIME_OUT_29 = 29,
    BUTTON = 30
};
/*
 * 接口类
 */
class TomatoState
{
  public:
    virtual void handle(Event event) = 0;
    virtual ~TomatoState() = 0; //必须有函数体
};
/*
 * 具体状态类
 */
class StartState: public TomatoState
{
  private:
    Dialog* _context;

  public:
    StartState(Dialog* context);
    void handle(Event event);
    ~StartState();
};
/*
 * 具体状态类
 */
class CancleState: public TomatoState
{
  private:
    Dialog* _context;

  public:
    CancleState(Dialog* context);
    void handle(Event event);
    ~CancleState();
};
/*
 * 具体状态类
 */
class ProcessState: public TomatoState
{
  private:
    Dialog* _context;

  public:
    ProcessState(Dialog* context);
    void handle(Event event);
    ~ProcessState();
};
/*
 * 具体状态类
 */
class EndState: public TomatoState
{
  private:
    Dialog* _context;

  public:
    EndState(Dialog* context);
    void handle(Event event);
    ~EndState();
};

#endif
