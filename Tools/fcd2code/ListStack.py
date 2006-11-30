
class ListStack:
    """ A simple stack based implementation based on lists.
    """

    def __init__(self):
        """Creates a new empty stack.
        """
        self.m_stack = [];

    def push(self, obj):
        """Adds obj to the top of the stack.
        """
        self.m_stack.append(obj);

    def pop(self):
        """Removes the obj on the top of the stack.
        """
        if not self.empty():
            self.m_stack = self.m_stack[:-1];

    def top(self):
        """Returns the obj on top of the stack.
        """
        return self.m_stack[len(self.m_stack) - 1];

    def empty(self):
        """Returns True if the stack is empty, False otherwise.
        """
        return len(self.m_stack) == 0;

    def clear(self):
        """Removes all elements from the stack.
        """
        self.m_stack = [];
    
