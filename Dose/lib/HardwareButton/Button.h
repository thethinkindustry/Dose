
enum ButtonMode
{
    PullUp,
    PullDown
};

enum ButtonState
{
    Pressed,
    Released
};


class ButtonFunc
{
    private:
    void* (*func) (void*) = nullptr;

    public:
    ButtonFunc();
    
    ButtonFunc(void* (*f)(void*));



    void* operator()(void* data);
};

class Button
{
    protected:
    ButtonMode mode;
    ButtonState state;
    ButtonFunc** pressTasks;
    ButtonFunc** releaseTasks;

    int pool_size = 5;
    int index = 0;
    
    public:
    void addPressTask(ButtonFunc* func);
    void addReleaseTask(ButtonFunc* func);
    void removePressTask(ButtonFunc* func);
    void removeReleaseTask(ButtonFunc* func);

    ButtonState checkState();

    virtual void update(int logic) = 0;


};
