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
 * @file        list.c
 * @date        2014-07-22
 * @author      Chen Yan  <leochenlinux@gmail.com>
 * @brief       Doubly linked list
 * @par         Copyright
 * Copyright (C) Chen Yan 2014 -2016. All rights reserved.
 *****************************************************************************/

/* Includes ---------------------------------------------------------------- */

#include "list.h"
#include "string.h"
#include "stdlib.h"

/* Macro Definitions ------------------------------------------------------- */

#define _HEAD_SIZE   (sizeof(node_head_t))

#define _IS_ENTRY(p)        (((p))&&((p)->m_psList==(p)))
#define _HAS_NODE(p)        (((void*)p)!=((void*)(p)->m_psNext))
#define _IS_NODE(p)         (((p))&&(p->m_psList!=(p)))
#define _IS_IDLE_NODE(p)    ((_IS_NODE(p))&&(!(p)->m_psList))
#define _IS_USED_NODE(p)    ((_IS_NODE(p))&&((p)->m_psList))
#define _NOT_FIRST_NODE(p)  ((_IS_USED_NODE(p))&&((void*)(p)->m_psPrev!=(void*)(p)->m_psList))
#define _NOT_LAST_NODE(p)   ((_IS_USED_NODE(p))&&((void*)(p)->m_psNext!=(void*)(p)->m_psList))
#define _TO_HEAD_ADDR(p)    ((p)?((void*)(p)-_HEAD_SIZE):(NULL))
#define _TO_USER_ADDR(p)    ((void*)(p)+_HEAD_SIZE)

/* Type Definitions -------------------------------------------------------- */

typedef struct _NODE_HEAD_T list_entry_t;
typedef struct _LIST_NODE_T list_node_t;
typedef struct _NODE_HEAD_T node_head_t;

struct _NODE_HEAD_T {
    list_node_t *m_psNext;
    list_node_t *m_psPrev;
    list_entry_t *m_psList;
    uint32_t m_uiSize;
};

struct _LIST_NODE_T {
    node_head_t m_stHead;
    uint8_t m_pData[1];
};

/* Function Definitions ---------------------------------------------------- */

/**************************************************************************//**
 * @fn          list_create
 * @param       None
 * @return      Handle of the created list or NULL if failed
 * @brief       Create a new empty list
 *****************************************************************************/
void *list_create( void )
{
    list_entry_t *psList = malloc( sizeof( list_entry_t ) );
    if( psList ) {
        psList->m_psNext =  (void *)psList;
        psList->m_psPrev =  (void *)psList;
        psList->m_psList =  (void *)psList;
        psList->m_uiSize = 0;
    }
    return _TO_USER_ADDR(psList);
}

/**************************************************************************//**
 * @fn          list_node_alloc
 * @param [in]  uiSize - Expected size of user data field
 * @return      Pointer to the created node or NULL if failed
 * @brief       Create a new element node with specified size of user data field
 *****************************************************************************/
void *list_node_alloc( uint32_t uiSize )
{
    list_node_t *psNode = NULL;
    psNode = malloc( _HEAD_SIZE + uiSize );
    if( psNode ) {
        psNode->m_stHead.m_uiSize  = uiSize;
        psNode->m_stHead.m_psList = NULL;
        return (void *)psNode->m_pData;
    }
    return NULL;
}

/**************************************************************************//**
 * @fn          list_node_free
 * @param [in]  pvNode - Pointer to a node
 * @return      None
 * @brief       Free the memory of the given node
 *****************************************************************************/
void list_node_free( void *pvNode )
{
    node_head_t *psHead = _TO_HEAD_ADDR(pvNode);
    if( _IS_IDLE_NODE(psHead) ) {
        free( psHead );
    }
}

/**************************************************************************//**
 * @fn          list_node_size
 * @param [in]  pvNode - Pointer to a node.
 * @return      The size of user data field
 * @brief       Get the size of user data field within the given node
 *****************************************************************************/
uint32_t list_node_size( void *pvNode )
{
    node_head_t *psHead = _TO_HEAD_ADDR(pvNode);
    return ( (_IS_NODE(psHead))?(psHead->m_uiSize):(0) );
}

/**************************************************************************//**
 * @fn          list_add_rear
 * @param [in]  pvListEntry - List handle
 * @param [in]  pvNode      - Pointer to a node
 * @return      None
 * @brief       Add a node at the end of a list
 *****************************************************************************/
void list_add_rear( void *pvListEntry, void *pvNode )
{
    node_head_t *psHead = _TO_HEAD_ADDR(pvNode);
    list_entry_t *psList = _TO_HEAD_ADDR(pvListEntry);
    if( _IS_ENTRY(psList) && _IS_IDLE_NODE(psHead) ) {
        psHead->m_psList = psList;
        psHead->m_psPrev = psList->m_psPrev;
        psHead->m_psNext = (void *)psList;
        psList->m_psPrev->m_stHead.m_psNext = (void *)psHead;
        psList->m_psPrev = (void *)psHead;
        psList->m_uiSize++;
    }
}

/**************************************************************************//**
 * @fn          list_add_front
 * @param [in]  pvListEntry - List handle
 * @param [in]  pvNode      - Pointer to a node.
 * @return      None
 * @brief       Add a node at the beginning of a list.
 *****************************************************************************/
void list_add_front( void *pvListEntry, void *pvNode )
{
    node_head_t *psHead = _TO_HEAD_ADDR(pvNode);
    list_entry_t *psList = _TO_HEAD_ADDR(pvListEntry);
    if( _IS_ENTRY(psList) && _IS_IDLE_NODE(psHead) ) {
        psHead->m_psList = psList;
        psHead->m_psPrev = (void *)psList;
        psHead->m_psNext = psList->m_psNext;
        psList->m_psNext->m_stHead.m_psPrev = (void *)psHead;
        psList->m_psNext = (void *)psHead;
        psList->m_uiSize++;
    }
}

/**************************************************************************//**
 * @fn          list_node_del
 * @param [in]  pvNode - Pointer to a node.
 * @return      None
 * @brief       Delete a node from list. Note the node will not be freed.
 *****************************************************************************/
void list_node_del( void *pvNode )
{
    node_head_t *psHead = _TO_HEAD_ADDR(pvNode);
    if( _IS_USED_NODE(psHead) ) {
        psHead->m_psPrev->m_stHead.m_psNext = psHead->m_psNext;
        psHead->m_psNext->m_stHead.m_psPrev = psHead->m_psPrev;
        psHead->m_psList->m_uiSize--;
        psHead->m_psList = NULL;
    }
}

/**************************************************************************//**
 * @fn          list_node_swap
 * @param [in]  pvNodeA - Pointer to a node.
 * @param [in]  pvNodeB - Pointer to another node.
 * @return      None
 * @brief       Swap two nodes
 *****************************************************************************/
void list_node_swap( void *pvNodeA, void *pvNodeB )
{
    node_head_t sTmp;
    node_head_t *psHeadA = _TO_HEAD_ADDR(pvNodeA);
    node_head_t *psHeadB = _TO_HEAD_ADDR(pvNodeB);
    if( _IS_NODE(psHeadA) && _IS_NODE(psHeadB) ) {
        sTmp = *psHeadA;
        *psHeadA = *psHeadB;
        *psHeadB = sTmp;
    }
}

/**************************************************************************//**
 * @fn          list_node_first
 * @param [in]  pvListEntry  - List handle
 * @return      Pointer to the node or NULL if not founded
 * @brief       Get the node at the beginning of the specified list.
 *****************************************************************************/
void *list_node_first( void *pvListEntry )
{
    list_entry_t *psList = _TO_HEAD_ADDR(pvListEntry);
    return (_IS_ENTRY(psList)&&_HAS_NODE(psList))?_TO_USER_ADDR(psList->m_psNext):NULL;
}

/**************************************************************************//**
 * @fn          list_node_last
 * @param [in]  pvListEntry - List handle
 * @return      Pointer to the node or NULL if not founded
 * @brief       Get the node at the end of the specified list.
 *****************************************************************************/
void *list_node_last( void *pvListEntry )
{
    list_entry_t *psList = _TO_HEAD_ADDR(pvListEntry);
    return (_IS_ENTRY(psList)&&_HAS_NODE(psList))?_TO_USER_ADDR(psList->m_psPrev):NULL;
}

/**************************************************************************//**
 * @fn          list_node_next
 * @param [in]  pvNode - Pointer to a node.
 * @return      Pointer to the the next node
 * @brief       Get next node or NULL if reach the end of list
 *****************************************************************************/
void *list_node_next( void *pvNode )
{
    node_head_t *psHead = _TO_HEAD_ADDR(pvNode);
    return _NOT_LAST_NODE(psHead)?_TO_USER_ADDR(psHead->m_psNext):NULL;
}

/**************************************************************************//**
 * @fn          list_node_prev
 * @param [in]  pvNode - Pointer to a node.
 * @return      Pointer to the the previous node
 * @brief       Get next node or NULL if reach the beginning of list
 *****************************************************************************/
void *list_node_prev( void *pvNode )
{
    node_head_t *psHead = _TO_HEAD_ADDR(pvNode);
    return _NOT_FIRST_NODE(psHead)?_TO_USER_ADDR(psHead->m_psPrev):NULL;
}

/**************************************************************************//**
 * @fn          list_flush
 * @param [in]  pvListEntry - List handle
 * @return      None
 * @brief       Flush a list. All nodes in list will be deleted and freed
 *****************************************************************************/
void list_flush( void *pvListEntry )
{
    list_entry_t *psList = _TO_HEAD_ADDR(pvListEntry);
    node_head_t *psHead;
    if( _IS_ENTRY(psList) ) {
        while( _HAS_NODE(psList) ) {
            psHead = (void *)psList->m_psNext;
            psHead->m_psNext->m_stHead.m_psPrev = (void *)psList;
            psList->m_psNext = psHead->m_psNext;
            psList->m_uiSize--;
            free( psHead );
        }
    }
}

/**************************************************************************//**
 * @fn          list_destroy
 * @param [in]  pvListEntry - List handle
 * @return      None
 * @brief       Free the list including all nodes in it.
 *****************************************************************************/
void list_destroy( void *pvListEntry )
{
    list_entry_t *psList = _TO_HEAD_ADDR(pvListEntry);
    node_head_t *psHead;
    if( _IS_ENTRY(psList) ) {
        while( _HAS_NODE(psList) ) {
            psHead = (void *)psList->m_psNext;
            psHead->m_psNext->m_stHead.m_psPrev = (void *)psList;
            psList->m_psNext = psHead->m_psNext;
            psList->m_uiSize--;
            free( psHead );
        }
    }
    free( psList );
}

/**************************************************************************//**
 * @fn          list_length
 * @param [in]  pvListEntry - List handle
 * @return      The number of nodes in the list.
 * @brief       Get the number of nodes in a list.
 *****************************************************************************/
uint32_t list_length( void *pvListEntry )
{
    list_entry_t *psList = _TO_HEAD_ADDR(pvListEntry);
    return _IS_ENTRY(psList)?psList->m_uiSize:0;
}

/******************************************************************************
 *                              End of File
 *****************************************************************************/
