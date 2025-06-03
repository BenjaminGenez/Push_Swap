#include "push_swap.h"

/**
 * Pushes elements from stack A to stack B, leaving only 3 elements in stack A.
 * Uses a strategy to push smaller-indexed elements first (bottom half of sorted range).
 */
static void push_all_save_three(t_stack **stack_a, t_stack **stack_b)
{
	int stack_size;
	int pushed;
	int i;

	stack_size = get_stack_size(*stack_a);
	pushed = 0;
	i = 0;
	// First phase: push roughly half the elements (smaller indices) to stack B
	// Only do this optimization for larger stacks (> 6 elements)
	while (stack_size > 6 && i < stack_size && pushed < stack_size / 2)
	{
		// If current element is in the smaller half (by index), push it to B
		if ((*stack_a)->index <= stack_size / 2)
		{
			do_pb(stack_a, stack_b);
			pushed++;
		}
		else
			do_ra(stack_a); // Otherwise, rotate to check next element
		i++;
	}
	// Second phase: push remaining elements until only 3 are left in stack A
	while (stack_size - pushed > 3)
	{
		do_pb(stack_a, stack_b);
		pushed++;
	}
}

/**
 * Positions the smallest element at the top of stack A by rotating.
 * Chooses the most efficient rotation direction (ra or rra).
 */
static void shift_stack(t_stack **stack_a)
{
	int lowest_pos;
	int stack_size;

	stack_size = get_stack_size(*stack_a);
	lowest_pos = get_lowest_index_position(stack_a);
	// If smallest element is in bottom half, use reverse rotate (rra)
	if (lowest_pos > stack_size / 2)
	{
		while (lowest_pos < stack_size)
		{
			do_rra(stack_a);
			lowest_pos++;
		}
	}
	// If smallest element is in top half, use regular rotate (ra)
	else
	{
		while (lowest_pos > 0)
		{
			do_ra(stack_a);
			lowest_pos--;
		}
	}
}

/**
 * Main sorting function implementing a hybrid approach:
 * 1. Push most elements to stack B, keeping 3 in stack A
 * 2. Sort the 3 remaining elements in stack A
 * 3. Push back elements from B to A in optimal positions
 * 4. Final adjustment to ensure smallest element is at top
 */
void sort(t_stack **stack_a, t_stack **stack_b)
{
	// Phase 1: Move elements to stack B, leave 3 in stack A
	push_all_save_three(stack_a, stack_b);

	// Phase 2: Sort the 3 remaining elements in stack A
	tiny_sort(stack_a);

	// Phase 3: Push back all elements from B to A in sorted order
	while (*stack_b)
	{
		get_target_position(stack_a, stack_b); // Find best position in A for top of B
		get_cost(stack_a, stack_b);			   // Calculate cost of each move
		do_cheapest_move(stack_a, stack_b);	   // Execute the most efficient move
	}

	// Phase 4: Final adjustment - ensure smallest element is at top
	if (!is_sorted(*stack_a))
		shift_stack(stack_a);
}
