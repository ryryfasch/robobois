#ifndef COMMAND_STACK
#define COMMAND_STACK

#define STACK_SIZE 250

struct CommandItem
{
    char command;
    long length;

    CommandItem(char instruction, long time)
    {
        command = instruction;
        length = time;
    }
    CommandItem()
    {
        command = ' ';
        length = -1;
    }
};

class CommandStack
{
public:
    CommandStack();
    ~CommandStack();

    void push(CommandItem item);
    CommandItem pop();

    int getSize();

    bool isEmpty();

private:
    int _currentPos;
    CommandItem itemArray[STACK_SIZE];
};

CommandStack::CommandStack()
{
    _currentPos = 0;
}

CommandStack::~CommandStack()
{
}

void CommandStack::push(CommandItem item)
{
    itemArray[_currentPos++] = item;
}

CommandItem CommandStack::pop()
{
    if(_currentPos > 0) {
        CommandItem item = itemArray[_currentPos-1];
        _currentPos--;
        return item;
    }
    
    return CommandItem();
}

int CommandStack::getSize()
{
    return _currentPos;
}

bool CommandStack::isEmpty()
{
    return _currentPos == 0;
}

#endif
