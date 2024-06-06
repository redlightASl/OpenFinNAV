/**
 * @file fin_list.h
 * @brief 
 * @author RedlightASl (dddbbbdd@foxmail.com)
 * @version 1.0
 * @date 2024-04-06
 * 
 * @copyright Copyright (c), 2009-2023, OurEDA Underwater Robot Team, DLUT.
 * This file is part of FinNAV LibROV.
 * @note This implementation of list is just modified from RT-Thread!
 * Copyright is as follows:
 * /*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-16     Bernard      the first version
 * 2006-09-07     Bernard      move the kservice APIs to rtthread.h
 * 2007-06-27     Bernard      fix the rt_list_remove bug
 * 2012-03-22     Bernard      rename kservice.h to rtservice.h
 * 2017-11-15     JasonJia     Modify rt_slist_foreach to rt_slist_for_each_entry.
 *                             Make code cleanup.
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date    <th>Version  <th>Author     <th>Description
 * <tr><td>2024-04-06  <td>1.0      <td>RedlightASl   <td>Content
 * </table>
 */
#pragma once

/**
 * @brief 双向链表
 */
struct rov_list_node{
    struct rov_list_node *prev;
    struct rov_list_node *next;
};
typedef struct rov_list_node rov_list_t;

/**
 * @brief 当ptr是结构体类型的成员时, 返回结构体的起始地址
 * @param ptr 结构体类型的成员指针
 * @param type 结构体类型
 * @param member 结构体中链表结构体成员的名称
 */
#define ROV_CONTAINER_OF(ptr, type, member) \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

/**
 * @brief 初始化链表实例
 */
#define ROV_LIST_INST_INIT(object) { &(object), &(object) }

/**
 * @brief 得到链表对象
 * @param node 链表入口节点
 * @param type 该链表对象的类型
 * @param member 该链表对应的对象
 */
#define ROV_LIST_ENTRY(node, type, member) \
    ROV_CONTAINER_OF(node, type, member)

/**
 * @brief 遍历链表
 * @param _pos 用于循环迭代的链表指针
 * @param _list 待遍历的链表头
 */
#define ROV_LIST_FOR_EACH(_pos, _list) \
    for (_pos = (_list)->next; _pos != (_list); _pos = _pos->next)

/**
 * @brief 遍历由给定对象组成的链表
 * @param _pos 用于循环迭代的链表指针
 * @param _list 待遍历的链表头
 * @param _member 结构体中链表结构体成员的名称
 */
#define ROV_LIST_FOR_EACH_ENTRY(_pos, _list, _member) \
    for (_pos = ROV_LIST_ENTRY((_list)->next, typeof(*_pos), _member); \
         &_pos->_member != (_list); \
         _pos = ROV_LIST_ENTRY(_pos->_member.next, typeof(*_pos), _member))

/**
 * @brief 初始化链表
 * @param  list             待初始化的链表
 */
ROV_INLINE void rov_list_init(rov_list_t* list)
{
    list->next = list->prev = list;
}

/**
 * @brief 在链表后插入节点
 * @param  list             链表
 * @param  node             待插入节点
 */
ROV_INLINE void rov_list_head_insert(rov_list_t* list, rov_list_t* node)
{
    list->next->prev = node;
    node->next = list->next;
    list->next = node;
    node->prev = list;
}

/**
 * @brief 在链表前插入节点
 * @param  list             链表
 * @param  node             待插入节点
 */
ROV_INLINE void rov_list_tail_insert(rov_list_t* list, rov_list_t* node)
{
    list->prev->next = node;
    node->prev = list->prev;

    list->prev = node;
    node->next = list;
}

/**
 * @brief 从链表中移除一个节点
 * @param  node             要被移除的节点
 */
ROV_INLINE void rov_list_remove(rov_list_t* node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = node->prev = node;
}

/**
 * @brief 检查链表是否为空
 * @param  list             待检查的链表
 */
ROV_INLINE bool rov_list_isempty(const rov_list_t *list)
{
    return (bool)(list->next == list);
}

/**
 * @brief 遍历以获取链表长度
 * @param  list             待计算长度的链表
 */
ROV_INLINE uint32_t rov_list_len(const rov_list_t *list)
{
    uint32_t len = 0;
    const rov_list_t *temp = list;
    while (temp->next != list)
    {
        temp = temp->next;
        len++;
    }
    return len;
}
