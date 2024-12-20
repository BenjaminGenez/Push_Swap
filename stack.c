#include "stack.h"

t_stack *create_stack(void)
{
    t_stack *stack = (t_stack *)malloc(sizeof(t_stack));
    stack->top = NULL;
    return stack;
}

void push(t_stack *stack, int value)
{
    t_node *new_node = (t_node *)malloc(sizeof(t_node));
    new_node->value = value;
    new_node->next = stack->top;
    stack->top = new_node;
}

int pop(t_stack *stack)
{
    if (is_empty(stack))
    {
        return -1;
    }
    t_node *temp = stack->top;
    int value = temp->value;
    stack->top = temp->next;
    free(temp);
    return value;
}

bool is_empty(t_stack *stack)
{
    return stack->top == NULL;
}

void swap(t_stack *stack)
{
    if (stack->top && stack->top->next)
    {
        t_node *first = stack->top;
        t_node *second = stack->top->next;
        first->next = second->next;
        second->next = first;
        stack->top = second;
    }
}

void rotate(t_stack *stack)
{
    if (stack->top && stack->top->next)
    {
        t_node *first = stack->top;
        t_node *last = stack->top;
        while (last->next)
        {
            last = last->next;
        }
        stack->top = first->next;
        first->next = NULL;
        last->next = first;
    }
}

void reverse_rotate(t_stack *stack)
{
    if (stack->top && stack->top->next)
    {
        t_node *prev = NULL;
        t_node *current = stack->top;
        while (current->next)
        {
            prev = current;
            current = current->next;
        }
        current->next = stack->top;
        stack->top = current;
        prev->next = NULL;
    }
}