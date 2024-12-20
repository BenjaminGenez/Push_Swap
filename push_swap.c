#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void print_stack(t_stack *stack)
{
    t_node *current = stack->top;
    while (current)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return 0;
    }

    t_stack *a = create_stack();
    t_stack *b = create_stack();

    for (int i = 1; i < argc; i++)
    {
        push(a, atoi(argv[i]));
    }

    swap(a);
    print_stack(a);
    push(b, pop(a));
    print_stack(a);
    print_stack(b);

    // to-do: Implement sorting algorithm 🤨😕

    // Free memory
    while (!is_empty(a))
    {
        pop(a);
    }
    while (!is_empty(b))
    {
        pop(b);
    }
    free(a);
    free(b);

    return 0;
}