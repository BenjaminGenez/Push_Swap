#include "push_swap.h"

void get_cost(t_stack **stack_a, t_stack **stack_b)
{
    t_stack *tmp_a;
    t_stack *tmp_b;
    int size_a;
    int size_b;

    tmp_a = *stack_a;
    tmp_b = *stack_b;
    size_a = get_stack_size(tmp_a);
    size_b = get_stack_size(tmp_b);
    while (tmp_b)
    {
        tmp_b->cost_b = tmp_b->pos;
        if (tmp_b->pos > size_b / 2)
            tmp_b->cost_b = (size_b - tmp_b->pos) * -1;
        tmp_b->cost_a = tmp_b->target_pos;
        if (tmp_b->target_pos > size_a / 2)
            tmp_b->cost_a = (size_a - tmp_b->target_pos) * -1;
        tmp_b = tmp_b->next;
    }
}
