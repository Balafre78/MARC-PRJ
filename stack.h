//
// Created by flasque on 19/10/2024.
//

#ifndef UNTITLED1_STACK_H
#define UNTITLED1_STACK_H

#include "node.h"

/**
 * @brief Structure for the stack of t_node*
 */
typedef struct s_stack
{
    t_node **values;
    int size;
    int nbElts;
} t_stack;

/**
 * @brief Function to create a stack
 * @param size : the size of the stack
 * @return the stack
 */
t_stack createStack(int);

/**
 * @brief Function to push a value in the stack
 * @param pointer to the stack
 * @param value : the value to push
 * @return none
 */
void push(t_stack *, t_node *);

/**
 * @brief Function to pop a value from the stack
 * @param : pointer to the stack
 * @return the value popped
 */
t_node* pop(t_stack *);

/**
 * @brief Function to get the top value of the stack
 * @param stack : the stack
 * @return the top value
 */
t_node* top(t_stack);

/**
 * @brief Display the stack nodes value
 * @param stack : the stack
 * @return none
 */
void displayStack(t_stack);


#endif //UNTITLED1_STACK_H
