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

XMLNode::~XMLNode()
{
}

