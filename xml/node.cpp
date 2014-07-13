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

char *XMLNode::parse(char *str)
{
#define STATUS_TEXT 0
#define STATUS_TAG_NAME 1
#define STATUS_PARAM_NAME 2
#define STATUS_PARAM_VALUE 3
#define STATUS_TAG_END 4

    int m = 0, n = 0;
    int j = 0;
    char *start = str;
    int end = strlen(str);

    int status = STATUS_TEXT;
    this->text = (char*) malloc(end);

    XMLNode *subnode = NULL;
    char compare_name[256]; // TODO: dynamic

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
        }

        if(status == STATUS_TEXT)
        {
            //printf("%c", *str);
            this->text[j++] = *str++;
        }
        else if(status == STATUS_TAG_NAME)
        {
            if(subnode != NULL)
            {
                subnode->name[m++] = *str++;
            }
            else
            {
                printf("something went wrong.\n");
            }
        }
        else if(status == STATUS_TAG_END)
        {
            compare_name[n++] = *str++;
        }
    }

    return str;
}

