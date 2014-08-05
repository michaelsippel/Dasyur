/**
 *  xml/node.cpp
 *
 *  (C) Copyright 2014 Michael Sippel
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
#include "xml.h"
#include <stdio.h>

XMLNode::XMLNode()
{
    this->name = NULL;
    this->text = NULL;
    this->params = new List<XMLParam>();
    this->subnodes = new List<XMLNode>();
    this->parent = NULL;
}

XMLNode::XMLNode(char *text_)
{
    this->name = NULL;
    this->text = NULL;
    this->params = new List<XMLParam>();
    this->subnodes = new List<XMLNode>();
    this->parent = NULL;
    this->parse(text_);
}

XMLNode::XMLNode(const char *path)
{
    this->name = NULL;
    this->text = NULL;
    this->params = new List<XMLParam>();
    this->subnodes = new List<XMLNode>();
    this->parent = NULL;

    FILE *f = fopen(path, "r");
    if(f == NULL)
    {
        printf("couldn't open %s\n", path);
        return;
    }

    fseek(f, 0, SEEK_END);
    int len = ftell(f);

    fseek(f, 0, SEEK_SET);

    char *buf = (char*) malloc(len + 1);
    fread(buf, len, 1, f);
    buf[len] = '\0';

    this->parse(buf);

    fclose(f);
}

XMLNode::~XMLNode()
{
}

XMLNode *XMLNode::getSubnode(const char *name_)
{
    return this->getSubnode((char*) name_);
}

XMLNode *XMLNode::getSubnode(char *name_)
{
    return this->subnodes->getElement(name_);
}

XMLNode *XMLNode::getSubnode(const char *name_, const char *value_)
{
    return this->getSubnode((char*) name_, (char*) value_);
}

XMLNode *XMLNode::getSubnode(const char *name_, char *value_)
{
    ListEntry<XMLNode> *entry = this->subnodes->getHead();
    while(entry != NULL)
    {
        XMLNode *node = entry->element;
        if(node != NULL)
        {
            char *value = node->params->getElement(name_)->value;
            if(strcmp(value_, value) == 0)
            {
                return node;
            }
        }
        entry = entry->getNext();
    }
}

XMLParam *XMLNode::getParam(const char *name_)
{
    return this->getParam((char*) name_);
}

XMLParam *XMLNode::getParam(char *name_)
{
    return this->params->getElement(name_);
}

char *XMLNode::parse(char *str)
{
#define STATUS_TEXT 0
#define STATUS_TAG_NAME 1
#define STATUS_TAG_SPACE 2
#define STATUS_PARAM_NAME 3
#define STATUS_PARAM_VALUE 4
#define STATUS_TAG_END 5

    int m = 0, n = 0;
    int j = 0;
    char *start = str;
    int end = strlen(str);

    int status = STATUS_TEXT;
    this->text = (char*) malloc(end);

    XMLNode *subnode = NULL;
    char compare_name[256]; // TODO: dynamic

    XMLParam *param = NULL;

    while(*str != '\0')
    {
        switch(*str)
        {
            case '<':
                if(status == STATUS_TEXT)
                {
                    str++;
                    if(*str == '/')
                    {
                        status = STATUS_TAG_END;
                        str++;
                    }
                    else
                    {
                        subnode = new XMLNode();
                        subnode->name = (char*) malloc(256); // TODO: dynamic
                        status = STATUS_TAG_NAME;
                    }
                }
                break;
            case '>':
                if(status == STATUS_TAG_END)
                {
                    compare_name[n] = '\0';
                    n = 0;
                    str++;

                    if(this->name != NULL)
                    {
                        if(strcmp(compare_name, this->name) == 0)
                        {
                            //printf("</%s>", this->name);
                            return str;
                        }
                        else
                        {
                            //printf("</CLOSE: %s, expected %s>", compare_name, this->name);
                        }
                    }
                    status = STATUS_TEXT;
                }
                else if(status != STATUS_TEXT && subnode != NULL)
                {
                    subnode->name[m] = '\0';
                    m = 0;
                    //printf("<%s>", subnode->name);

                    str = subnode->parse(++str);
                    this->subnodes->add(subnode, subnode->name);

                    subnode = NULL;
                    status = STATUS_TEXT;
                    continue;
                }
                break;
            case ' ':
                if(status == STATUS_TAG_NAME || status == STATUS_TAG_SPACE)
                {
                    str++;
                    if(*str != ' ')
                    {
                        status = STATUS_PARAM_NAME;
                        param = new XMLParam();
                        param->name = (char*) malloc(256); // TODO: DYNAMIC!!!
                        param->value = (char*) malloc(256); //  TODO: DYNAMICCC!!!!!!!!
                    }
                    else
                    {
                        status = STATUS_TAG_SPACE;
                    }
                }
                break;
            case '=':
                if(status == STATUS_PARAM_NAME)
                {
                    str++;
                    if(*str == '\"')
                    {
                        param->name[n] = '\0';
                        n = 0;

                        str++;
                        status = STATUS_PARAM_VALUE;
                    }
                }
                break;
            case '\"':
                if(status == STATUS_PARAM_VALUE)
                {
                    param->value[n] = '\0';
                    n = 0;
                    subnode->params->add(param, param->name);

                    status = STATUS_TAG_SPACE;
                    str++;
                }
                break;
        }

        switch(status)
        {
            case STATUS_TEXT:
                //printf("%c", *str);
                this->text[j++] = *str++;
                break;
            case STATUS_TAG_NAME:
                if(subnode != NULL)
                {
                    subnode->name[m++] = *str++;
                }
                else
                {
                    printf("something went wrong.\n");
                }
                break;
            case STATUS_PARAM_NAME:
                if(param != NULL)
                {
                    param->name[n++] = *str++;
                }
                break;
            case STATUS_PARAM_VALUE:
                if(param != NULL)
                {
                    param->value[n++] = *str++;
                }
                break;
            case STATUS_TAG_END:
                compare_name[n++] = *str++;
                break;
        }
    }

    return str;
}

