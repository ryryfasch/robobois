#ifndef COMMAND_STACK_H
#define COMMAND_STACK_H

#define STACK_SIZE 100

struct CommandItem
{
    char command;
    unsigned long cmd_length;

    CommandItem(char instruction, long time)
    {
        command = instruction;
        cmd_length = time;
    }
    CommandItem()
    {
        command = ' ';
        cmd_length = -1;
    }
};

class CommandStack
{
public:
    CommandStack();
    ~CommandStack();

    void push(CommandItem item);
    void push(char command);
    CommandItem pop();
    CommandItem* back();

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

void CommandStack::push(char command)
{
    CommandItem item(command, -1);
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

CommandItem* CommandStack::back()
{
    return &itemArray[_currentPos-1];
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


