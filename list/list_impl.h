/**
 *  include/list_impl.h
 *
 *  Copyright (C) 2014 Michael Sippel
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @author Michael Sippel <michamimosa@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

template <typename T>
List<T>::List()
{
    this->head = NULL;
    this->current = NULL;
    this->size = 0;
}

template <typename T>
List<T>::~List()
{
}

template <typename T>
void List<T>::add(ListEntry<T> *entry)
{
    entry->next = NULL;
    entry->prev = this->current;

    if(this->current != NULL)
    {
        this->current->next = entry;
    }
    this->current = entry;
    if(this->head == NULL)
    {
        this->head = entry;
    }

    this->size++;
}

template <typename T>
void List<T>::remove(ListEntry<T> *entry)
{
    if(entry->prev != NULL)
    {
        entry->prev->next = entry->next;
    }
    else
    {
        this->head = entry->next;
    }

    if(entry->next != NULL)
    {
        entry->next->prev = entry->prev;
    }
    else
    {
        this->current = entry->prev;
    }
}

template <typename T>
void List<T>::join(List<T> *list)
{
    if(list != NULL)
    {
        if(this->head == NULL)
        {
            this->head = list->head;
            this->current = list->current;
        }
        else
        {
            if(this->current != NULL)
            {
                this->current->next = list->head;
            }

            if(list->head != NULL)
            {
                list->head->prev = this->current;
            }
        }
    }
}

template <typename T>
int List<T>::getSize(void)
{
    return this->size;
}

