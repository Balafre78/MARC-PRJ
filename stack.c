//
// Created by flasque on 19/10/2024.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

/**
 * @brief Function to create a stack
 * @param size : the size of the stack
 * @return the stack
 */
t_stack createStack(int size)
{
    // the size of the stack must be positive
    assert(size > 0);
    t_stack stack;
    stack.size = size;
    stack.nbElts = 0;
    stack.values = (t_node **)malloc(size * sizeof(t_node*));
    return stack;
}

/**
 * @brief Function to push a value in the stack
 * @param stack : the stack
 * @param value : the value to push
 * @return none
 */
void push(t_stack *p_stack, t_node* value)
{
    // the stack must not be full
    assert(p_stack->nbElts < p_stack->size);
    p_stack->values[p_stack->nbElts] = value;
    p_stack->nbElts++;
    return;
}

/**
 * @brief Function to pop a value from the stack
 * @param stack : the stack
 * @return the value popped
 */
t_node* pop(t_stack *p_stack)
{
    // the stack must not be empty
    assert(p_stack->nbElts > 0);
    p_stack->nbElts--;
    return p_stack->values[p_stack->nbElts];
}

/**
 * @brief Function to get the top value of the stack
 * @param stack : the stack
 * @return the top value
 */
t_node* top(t_stack stack)
{
    // the stack must not be empty
    assert(stack.nbElts > 0);
    return stack.values[stack.nbElts - 1];
}

void displayStack(t_stack stack)
{
    if(stack.nbElts == 0) {
        printf("Stack : Empty");
        return;
    }
    printf("Stack : TOP -> ");
    while(stack.nbElts > 0) {
        printf("%d -> ", pop(&stack)->value);
    }
    printf("BOTTOM\n");
}