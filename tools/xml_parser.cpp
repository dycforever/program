#include <map>
#include <tinyxml.h>

typedef std::map<std::string, std::string> String2String;

class CommonParser
{
public:
    static bool ParseKeyValue(TiXmlElement *elem, String2String& kvMap);

public:
    static bool ParseChildDoubleValue(TiXmlElement *elem, const char *tagName, double *value);
    static bool ParseChildIntValue(TiXmlElement *elem, const char *tagName, int *value);
    static bool ParseChildStringValue(TiXmlElement *elem, const char *tagName, const char **value);
    static bool ParseChildNotEmptyStringValue(TiXmlElement *elem, const char *tagName, const char **value);
    static bool ParseChildBoolValue(TiXmlElement *elem, const char *tagName, bool& value);

public:
    static bool ParseDoubleValue(TiXmlElement *elem, double *value);
    static bool ParseIntValue(TiXmlElement *elem, int *value);
    static bool ParseStringValue(TiXmlElement *elem, const char **text);
    static bool ParseNotEmptyStringValue(TiXmlElement *elem, const char **text);
    static bool ParseBoolValue(TiXmlElement *elem, bool& value);

public:
    static bool ParseAttrDoubleValue(TiXmlElement *elem, const char *attrName, double *value);
    static bool ParseAttrIntValue(TiXmlElement *elem, const char *attrName, int *value);
    static bool ParseAttrStringValue(TiXmlElement *elem, const char *attrName, const char **text);
    static bool ParseAttrNotEmptyStringValue(TiXmlElement *elem, const char *attrName, const char **text);
    static bool ParseAttrBoolValue(TiXmlElement *elem, const char *attrName, bool& value);

};


bool CommonParser::ParseChildDoubleValue(TiXmlElement *elem, 
        const char *tagName,
        double *value)
{
    if (elem == NULL) {
        return false;
    }
    TiXmlElement *child = elem->FirstChildElement(tagName);
    if (child == NULL) {
        return false;
    }
    return ParseDoubleValue(child, value);
}

bool CommonParser::ParseChildIntValue(TiXmlElement *elem,
                                      const char *tagName,
                                      int *value)
{
    if (elem == NULL) {
        return false;
    }
    TiXmlElement *child = elem->FirstChildElement(tagName);
    if (child == NULL) {
        return false;
    }
    return ParseIntValue(child, value);
}

bool CommonParser::ParseChildStringValue(TiXmlElement *elem,
        const char *tagName,
        const char **value)
{
    if (elem == NULL) {
        return false;
    }
    TiXmlElement *child = elem->FirstChildElement(tagName);
    if (child == NULL) {
        return false;
    }
    return ParseStringValue(child, value);
}

bool CommonParser::ParseChildNotEmptyStringValue(TiXmlElement *elem, 
        const char *tagName, const char **value)
{
    if (elem == NULL) {
        return false;
    }
    TiXmlElement *child = elem->FirstChildElement(tagName);
    if (child == NULL) {
        return false;
    }
    return ParseNotEmptyStringValue(child, value);
}

bool CommonParser::ParseChildBoolValue(TiXmlElement *elem,
                                       const char *tagName,
                                       bool& value)
{
    if (elem == NULL) {
        return false;
    }
    TiXmlElement *child = elem->FirstChildElement(tagName);
    if (child == NULL) {
        return false;
    }
    return ParseBoolValue(child, value);
}

bool CommonParser::ParseDoubleValue(TiXmlElement *elem, double *value)
{
    const char *text = NULL;
    if (!ParseNotEmptyStringValue(elem, &text)) {
        return false;
    }
    if (sscanf(text, "%lf", value) != 1) {
        return false;
    }
    return true;
}

bool CommonParser::ParseBoolValue(TiXmlElement *elem, bool& value)
{
    const char *text = NULL;
    if (!ParseNotEmptyStringValue(elem, &text)) {
        return false;
    }
    if (strcmp(text, "yes") == 0) {
        value = true;
        return true;
    } else if (strcmp(text, "no") == 0) {
        value = false;
        return true;
    }
    return false;
}

bool CommonParser::ParseIntValue(TiXmlElement *elem, int *value)
{
    const char *text = NULL;
    if (!ParseNotEmptyStringValue(elem, &text)) {
        return false;
    }
    if (sscanf(text, "%d", value) != 1) {
        return false;
    }
    return true;
}

bool CommonParser::ParseNotEmptyStringValue(TiXmlElement *elem, const char **text)
{
    const char *value = NULL;
    if (!ParseStringValue(elem, &value)) {
        return false;
    }
    if (strcmp(value, "") == 0) {
        return false;
    }
    *text = value;
    return true;
}

bool CommonParser::ParseStringValue(TiXmlElement *elem, const char **text)
{
    if (elem == NULL) {
        return false;
    }
    const char *strValue = elem->GetText();
    if (strValue == NULL) {
        return false;
    }
    *text = strValue;
    return true;
}

bool CommonParser::ParseAttrDoubleValue(TiXmlElement *elem, const char *attrName, double *value)
{
    const char *text = NULL;
    if (!ParseAttrNotEmptyStringValue(elem, attrName, &text)) {
        return false;
    }
    if (sscanf(text, "%lf", value) != 1) {
        return false;
    }
    return true;
}

bool CommonParser::ParseAttrIntValue(TiXmlElement *elem, const char *attrName, int *value)
{
    const char *text = NULL;
    if (!ParseAttrNotEmptyStringValue(elem, attrName, &text)) {
        return false;
    }
    if (sscanf(text, "%d", value) != 1) {
        return false;
    }
    return true;
}

bool CommonParser::ParseAttrNotEmptyStringValue(TiXmlElement *elem, 
        const char *attrName, const char **text)
{
    const char *value = NULL;
    if (!ParseAttrStringValue(elem, attrName, &value)) {
        return false;
    }
    if (strcmp(value, "") == 0) {
        return false;
    }
    *text = value;
    return true;
}

bool CommonParser::ParseAttrBoolValue(TiXmlElement *elem, const char *attrName, bool& value)
{
    const char *text = NULL;
    if (!ParseAttrNotEmptyStringValue(elem, attrName, &text)) {
        return false;
    }
    if (strcmp(text, "yes") == 0) {
        value = true;
        return true;
    } else if (strcmp(text, "no") == 0) {
        value = false;
        return true;
    }
    return false;
}

bool CommonParser::ParseAttrStringValue(TiXmlElement *elem, const char *attrName,
                                        const char **text)
{
    if (elem == NULL) {
        return false;
    }
    const char *strValue = elem->Attribute(attrName);
    if (strValue == NULL) {
        return false;
    }
    *text = strValue;
    return true;
}

bool CommonParser::ParseKeyValue(TiXmlElement *elem, String2String& kvMap)
{
    if (elem == NULL) {
        return false;
    }
    TiXmlElement *node = elem->FirstChildElement();
    for (; node != NULL; node = node->NextSiblingElement()){
        const char *key = node->Value();
        const char *value = node->GetText();
        value = value == NULL ? "" : value;
        kvMap[key] = value;
    }
    return true;
}

int main() {
        
}
