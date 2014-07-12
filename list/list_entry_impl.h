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
ListEntry<T>::ListEntry()
{
    this->element = NULL;
    strcpy(this->name, "");
    this->prev = NULL;
    this->next = NULL;
}

template <typename T>
ListEntry<T>::ListEntry(T *element_)
    : element(element_)
{
    strcpy(this->name, "");
    this->prev = NULL;
    this->next = NULL;
}

template <typename T>
ListEntry<T>::ListEntry(T *element_, char *name_)
    : element(element_)
{
    if(name_ != NULL)
    {
        strcpy(this->name, name_);
    }
    else
    {
        strcpy(this->name, "");
    }
    this->prev = NULL;
    this->next = NULL;
}

template <typename T>
ListEntry<T>::~ListEntry()
{
}

template <typename T>
ListEntry<T> *List<T>::add(T *element)
{
    ListEntry<T> *entry = new ListEntry<T>(element);
    this->add(entry);

    return entry;
}

template <typename T>
ListEntry<T> *List<T>::add(T *element, const char *name)
{
    return this->add(element, (char*) name);
}

template <typename T>
ListEntry<T> *List<T>::add(T *element, char *name)
{
    ListEntry<T> *entry = new ListEntry<T>(element, name);
    this->add(entry);

    return entry;
}

template <typename T>
ListEntry<T> *List<T>::getEntry(const char *name_)
{
    return this->getEntry((char*) name_);
}

template <typename T>
ListEntry<T> *List<T>::getEntry(char *name_)
{
    if(name_ == NULL)
    {
        return NULL;
    }

    ListEntry<T> *entry = this->head;
    while(entry != NULL)
    {
        if(strcmp(entry->name, name_) == 0)
        {
            return entry;
        }
        entry = entry->next;
    }

    return NULL;
}

template <typename T>
ListEntry<T> *List<T>::getHead(void)
{
    return this->head;
}

template <typename T>
ListEntry<T> *List<T>::getCurrent(void)
{
    return this->current;
}

template <typename T>
ListEntry<T> *ListEntry<T>::getPrev(void)
{
    return this->prev;
}

template <typename T>
ListEntry<T> *ListEntry<T>::getNext(void)
{
    return this->next;
}

