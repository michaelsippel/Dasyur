/**
 *  include/xml.h
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
#ifndef _DASYUR_XML_H
#define _DASYUR_XML_H

#include "list.h"

class XMLParam
{
    public:
        XMLParam();

        XMLParam(const char *name, const char *value);
        XMLParam(const char *name, char *value);
        XMLParam(char *name, const char *value);
        XMLParam(char *name, char *value);

        ~XMLParam();

        char *name;
        char *value;
};

class XMLNode
{
    public:
        XMLNode();
        XMLNode(char *text_);
        XMLNode(const char *path);
        ~XMLNode();

        char *name;
        char *text;

        List<XMLParam> *params;
        List<XMLNode> *subnodes;
        XMLNode *parent;

        char *parse(char *str);
};

#endif

