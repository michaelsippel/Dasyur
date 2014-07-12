/**
 *  xml/xml.cpp
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

XMLParam::XMLParam()
{
    this->name = NULL;
    this->value = NULL;
}

XMLParam::XMLParam(const char *name_, const char *value_)
{
    this->name = (char*) name_;
    this->value = (char*) value_;
}

XMLParam::XMLParam(const char *name_, char *value_)
    : value(value_)
{
    this->name = (char*) name_;
}

XMLParam::XMLParam(char *name_, const char *value_)
    : name(name_)
{
    this->value = (char*) value_;
}

XMLParam::XMLParam(char *name_, char *value_)
    : name(name_), value(value_)
{
}

XMLParam::~XMLParam()
{
}


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

char *XMLNode::parse(char *str)
{
#define STATUS_TEXT 0
#define STATUS_TAG_NAME 1
#define STATUS_PARAM_NAME 2
#define STATUS_PARAM_VALUE 3
#define STATUS_TAG_END 4

    int i = 0;
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
                    compare_name[i] == '\0';
                    i = 0;

                    if(this->name != NULL)
                    {
                        if(strcmp(compare_name, this->name) == 0)
                        {
                            //						printf("return from %s\n", this->name);
                            return ++str;
                        }
                    }
                }
                else if(status != STATUS_TEXT && subnode != NULL)
                {
                    subnode->name[i] = '\0';
                    //				printf("enter subnode %s\n", subnode->name);

                    str = subnode->parse(++str);
                    this->subnodes->add(subnode, subnode->name);
                    //				printf("added %s\n", subnode->name);

                    subnode = NULL;
                    i = 0;
                    status = STATUS_TEXT;
                }
                else
                {
                    status = STATUS_TEXT;
                }
                break;
        }

        if(status == STATUS_TEXT)
        {
            //		printf("copy %c\n", *str);
            this->text[j++] = *str++;
        }
        else if(status == STATUS_TAG_NAME)
        {
            if(subnode != NULL)
            {
                subnode->name[i++] = *str++;
            }
            else
            {
                printf("something went wrong.\n");
            }
        }
        else if(status == STATUS_TAG_END)
        {
            compare_name[i++] = *str++;
        }
    }

    return str;
}

