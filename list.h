/*
 ******************************************************************************
 *                                                                            *
 *                      Copyright (C) 2014 Chen Yan                           *
 *                     Licensed under the MIT license                         *
 *                                                                            *
 *                         The MIT License (MIT)                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    *
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        *
 * DEALINGS IN THE SOFTWARE.                                                  *
 *                                                                            *
 ******************************************************************************
 */

/**************************************************************************//**
 * @file        list.h
 * @date        2014-07-22
 * @author      Chen Yan  <leochenlinux@gmail.com>
 * @brief       Doubly linked list
 * @par         Copyright
 * Copyright (C) Chen Yan 2014 -2016. All rights reserved.
 *****************************************************************************/

#ifndef _LIST_H_
#define _LIST_H_

/* Includes ---------------------------------------------------------------- */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* External Interfaces ----------------------------------------------------- */

/**************************************************************************//**
 * @fn          list_create
 * @param       None
 * @return      Handle of the created list or NULL if failed
 * @brief       Create a new empty list
 *****************************************************************************/
void *list_create( void );

/**************************************************************************//**
 * @fn          list_node_alloc
 * @param [in]  uiSize - Expected size of user data field
 * @return      Pointer to the created node or NULL if failed
 * @brief       Create a new element node with specified size of user data field
 *****************************************************************************/
void *list_node_alloc( uint32_t uiSize );

/**************************************************************************//**
 * @fn          list_node_free
 * @param [in]  pvNode - Pointer to a node
 * @return      None
 * @brief       Free the memory of the given node
 *****************************************************************************/
void list_node_free( void *pvNode );

/**************************************************************************//**
 * @fn          list_node_size
 * @param [in]  pvNode - Pointer to a node.
 * @return      The size of user data field
 * @brief       Get the size of user data field within the given node
 *****************************************************************************/
uint32_t list_node_size( void *pvNode );

/**************************************************************************//**
 * @fn          list_add_rear
 * @param [in]  pvListEntry - List handle
 * @param [in]  pvNode      - Pointer to a node
 * @return      None
 * @brief       Add a node at the end of a list
 *****************************************************************************/
void list_add_rear( void *pvListEntry, void *pvNode );

/**************************************************************************//**
 * @fn          list_add_front
 * @param [in]  pvListEntry - List handle
 * @param [in]  pvNode      - Pointer to a node.
 * @return      None
 * @brief       Add a node at the beginning of a list.
 *****************************************************************************/
void list_add_front( void *pvListEntry, void *pvNode );

/**************************************************************************//**
 * @fn          list_node_del
 * @param [in]  pvNode - Pointer to a node.
 * @return      None
 * @brief       Delete a node from list. Note the node will not be freed.
 *****************************************************************************/
void list_node_del( void *pvNode );

/**************************************************************************//**
 * @fn          list_node_swap
 * @param [in]  pvNodeA - Pointer to a node.
 * @param [in]  pvNodeB - Pointer to another node.
 * @return      None
 * @brief       Swap two nodes
 *****************************************************************************/
void list_node_swap( void *pvNodeA, void *pvNodeB );

/**************************************************************************//**
 * @fn          list_node_first
 * @param [in]  pvListEntry  - List handle
 * @return      Pointer to the node or NULL if not founded
 * @brief       Get the node at the beginning of the specified list.
 *****************************************************************************/
void *list_node_first( void *pvListEntry );

/**************************************************************************//**
 * @fn          list_node_last
 * @param [in]  pvListEntry - List handle
 * @return      Pointer to the node or NULL if not founded
 * @brief       Get the node at the end of the specified list.
 *****************************************************************************/
void *list_node_last( void *pvListEntry );

/**************************************************************************//**
 * @fn          list_node_next
 * @param [in]  pvNode - Pointer to a node.
 * @return      Pointer to the the next node
 * @brief       Get next node or NULL if reach the end of list
 *****************************************************************************/
void *list_node_next( void *pvNode );

/**************************************************************************//**
 * @fn          list_node_prev
 * @param [in]  pvNode - Pointer to a node.
 * @return      Pointer to the the previous node
 * @brief       Get next node or NULL if reach the beginning of list
 *****************************************************************************/
void *list_node_prev( void *pvNode );

/**************************************************************************//**
 * @fn          list_flush
 * @param [in]  pvListEntry - List handle
 * @return      None
 * @brief       Flush a list. All nodes in list will be deleted and freed
 *****************************************************************************/
void list_flush( void *pvListEntry );

/**************************************************************************//**
 * @fn          list_destroy
 * @param [in]  pvListEntry - List handle
 * @return      None
 * @brief       Free the list including all nodes in it.
 *****************************************************************************/
void list_destroy( void *pvListEntry );

/**************************************************************************//**
 * @fn          list_length
 * @param [in]  pvListEntry - List handle
 * @return      The number of nodes in the list.
 * @brief       Get the number of nodes in a list.
 *****************************************************************************/
uint32_t list_length( void *pvListEntry );

#endif /* _LIST_H_ */
/******************************************************************************
 *                              End of File
 *****************************************************************************/
