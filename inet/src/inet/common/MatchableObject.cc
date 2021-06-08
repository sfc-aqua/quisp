//
// Copyright (C) OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "inet/common/MatchableObject.h"

namespace inet {

MatchableObject::MatchableObject(Attribute defaultAttribute, const cObject *object)
{
    this->defaultAttribute = defaultAttribute;
    this->object = object;
    classDescriptor = nullptr;
}

void MatchableObject::setObject(const cObject *object)
{
    this->object = object;
    classDescriptor = nullptr;
}

const char *MatchableObject::getAsString() const
{
    switch (defaultAttribute) {
        case ATTRIBUTE_FULLPATH:  attributeValue = object->getFullPath(); return attributeValue.c_str();
        case ATTRIBUTE_FULLNAME:  return object->getFullName();
        case ATTRIBUTE_CLASSNAME: return object->getClassName();
        default: throw cRuntimeError("Unknown setting for default attribute");
    }
}

void MatchableObject::splitIndex(char *indexedName, int& index)
{
    index = 0;
    char *startbracket = strchr(indexedName, '[');
    if (startbracket) {
        char *lastcharp = indexedName + strlen(indexedName) - 1;
        if (*lastcharp != ']')
            throw cRuntimeError("Unmatched '['");
        *startbracket = '\0';
        char *end;
        index = strtol(startbracket+1, &end, 10);
        if (end != lastcharp)
            throw cRuntimeError("Brackets [] must contain numeric index");
    }
}

bool MatchableObject::findDescriptorField(cClassDescriptor *classDescriptor, const char *attribute, int& fieldId, int& index)
{
    // attribute may be in the form "fieldName[index]"; split the two
    char *fieldNameBuf = new char[strlen(attribute)+1];
    strcpy(fieldNameBuf, attribute);
    splitIndex(fieldNameBuf, index);

    // find field by name
    fieldId = classDescriptor->findField(fieldNameBuf);
    delete[] fieldNameBuf;
    return fieldId != -1;
}

const char *MatchableObject::getAsString(const char *attribute) const
{
    if (!classDescriptor) {
        classDescriptor = object->getDescriptor();
        if (!classDescriptor)
            return nullptr;
    }

/*FIXME TBD
    // start tokenizing the path
    cStringTokenizer tokenizer(attribute, ".");
    const char *token;
    void *currentObj = obj;
    cClassDescriptor *currentDesc = desc;
    int currentFieldId = id
    while ((token = tokenizer.nextToken())!=nullptr)
    {
        bool found = findDescriptorField(d, token, fid, index);
        if (!found) return nullptr;
    }
*/

    int fieldId;
    int index;
    bool found = findDescriptorField(classDescriptor, attribute, fieldId, index);
    if (!found)
        return nullptr;

    attributeValue = classDescriptor->getFieldValueAsString((void *)object, fieldId, index);
    return attributeValue.c_str();
}

}  // namespace inet

