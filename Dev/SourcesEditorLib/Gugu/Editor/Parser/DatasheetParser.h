#pragma once

////////////////////////////////////////////////////////////////
// Includes

#include <string>
#include <vector>

////////////////////////////////////////////////////////////////
// Forward Declarations

namespace gugu
{
    class FileInfo;
    class VirtualDatasheet;
}

////////////////////////////////////////////////////////////////
// File Declarations

namespace gugu {

class DatasheetParser
{
public:

    struct EnumDefinition;
    struct ClassDefinition;
    struct DataMemberDefinition;

    struct EnumDefinition
    {
        std::string name;
        std::vector<std::string> values;
    };

    struct DataMemberDefinition
    {
        enum Type
        {
            Unknown,
            Bool,
            Int,
            Float,
            String,
            Enum,
            ObjectInstance,
            ObjectReference,
        };

        std::string name;
        DataMemberDefinition::Type type = DataMemberDefinition::Unknown;
        bool isArray = false;
        ClassDefinition* objectDefinition = nullptr;
        EnumDefinition* enumDefinition = nullptr;

        bool defaultValue_bool = false;
        int defaultValue_int = 0;
        float defaultValue_float = 0.f;
        std::string defaultValue_string;

        // TODO: enum value (reuse string ?).
        // TODO: object instance value (always null in definition).
        // TODO: object reference value (always null in definition).
        // TODO: array of MemberValue (always empty in definition).
    };

    struct ClassDefinition
    {
        std::string m_name;
        std::string baseName;
        ClassDefinition* baseDefinition = nullptr;
        std::vector<DataMemberDefinition*> dataMembers;

        DataMemberDefinition* GetDataMemberDefinition(const std::string& name) const;
    };

public:

    DatasheetParser();
    ~DatasheetParser();

    bool ParseBinding(const std::string& pathDatasheetBinding);
    void ClearBinding();

    bool IsDatasheet(const FileInfo& fileInfo) const;
    bool GetEnumDefinition(const std::string& name, EnumDefinition*& enumDefinition) const;
    bool GetClassDefinition(const std::string& name, ClassDefinition*& classDefinition) const;

    VirtualDatasheet* InstanciateDatasheetResource(const std::string& resourceID);

private:

    std::vector<EnumDefinition*> m_enumDefinitions;
    std::vector<ClassDefinition*> m_classDefinitions;
};

}   //namespace gugu
