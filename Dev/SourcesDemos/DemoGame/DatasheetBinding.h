#pragma once

////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/Resources/Datasheet.h"

#include <vector>

namespace demoproject {

////////////////////////////////////////////////////////////////
// Forward Declarations

class DS_SpriteInfo;
class DS_Character;
class DS_Hero;
class DS_Enemy;
class DS_Skill;
class DS_Effect;
class DS_EffectArea;
class DS_EffectProjectile;
class DS_EffectDamage;
class DS_EffectHeal;

////////////////////////////////////////////////////////////////
namespace EEffectCenter {
    enum Type
    {
        Caster,
        Target,
        Affected,
    };

    gugu::DatasheetEnum* GetDatasheetEnum();
    void GetEnumValues(std::vector<EEffectCenter::Type>& enumValues);
    size_t GetSize();

    void Register();
}
////////////////////////////////////////////////////////////////
namespace EProjectileAim {
    enum Type
    {
        Direction,
        Cursor,
    };

    gugu::DatasheetEnum* GetDatasheetEnum();
    void GetEnumValues(std::vector<EProjectileAim::Type>& enumValues);
    size_t GetSize();

    void Register();
}

////////////////////////////////////////////////////////////////
class DS_SpriteInfo : public gugu::Datasheet
{
public:

    DS_SpriteInfo();
    virtual ~DS_SpriteInfo();

public:

    std::string imageSet;
    std::string animSet;

protected:

    virtual void ParseMembers (gugu::DatasheetParserContext& context) override;
};

////////////////////////////////////////////////////////////////
class DS_Character : public gugu::Datasheet
{
public:

    DS_Character();
    virtual ~DS_Character();

public:

    std::string name;
    float health;
    float speed;
    DS_SpriteInfo* sprite;

protected:

    virtual void ParseMembers (gugu::DatasheetParserContext& context) override;
};

////////////////////////////////////////////////////////////////
class DS_Hero : public DS_Character
{
public:

    DS_Hero();
    virtual ~DS_Hero();

public:

    float stamina;
    float staminaRecovery;
    float staminaRecoveryDelay;
    float mana;
    float manaRecovery;

protected:

    virtual void ParseMembers (gugu::DatasheetParserContext& context) override;
};

////////////////////////////////////////////////////////////////
class DS_Enemy : public DS_Character
{
public:

    DS_Enemy();
    virtual ~DS_Enemy();

public:

protected:

    virtual void ParseMembers (gugu::DatasheetParserContext& context) override;
};

////////////////////////////////////////////////////////////////
class DS_Skill : public gugu::Datasheet
{
public:

    DS_Skill();
    virtual ~DS_Skill();

public:

    std::string name;
    float staminaCost;
    float manaCost;
    bool useAttackSpeed;
    float cooldown;
    std::vector< DS_Effect* > effects;

protected:

    virtual void ParseMembers (gugu::DatasheetParserContext& context) override;
};

////////////////////////////////////////////////////////////////
class DS_Effect : public gugu::Datasheet
{
public:

    DS_Effect();
    virtual ~DS_Effect();

public:

    EEffectCenter::Type center;

protected:

    virtual void ParseMembers (gugu::DatasheetParserContext& context) override;
};

////////////////////////////////////////////////////////////////
class DS_EffectArea : public DS_Effect
{
public:

    DS_EffectArea();
    virtual ~DS_EffectArea();

public:

    bool excludeCaster;
    bool excludeTarget;
    float maxRadius;
    float angleFromDirection;
    std::vector< DS_Effect* > effectsOnHit;

protected:

    virtual void ParseMembers (gugu::DatasheetParserContext& context) override;
};

////////////////////////////////////////////////////////////////
class DS_EffectProjectile : public DS_Effect
{
public:

    DS_EffectProjectile();
    virtual ~DS_EffectProjectile();

public:

    EProjectileAim::Type aim;
    float speed;
    float lifetime;
    int maximumHits;
    std::vector< DS_Effect* > effectsOnHit;
    std::vector< DS_Effect* > effectsOnDestination;

protected:

    virtual void ParseMembers (gugu::DatasheetParserContext& context) override;
};

////////////////////////////////////////////////////////////////
class DS_EffectDamage : public DS_Effect
{
public:

    DS_EffectDamage();
    virtual ~DS_EffectDamage();

public:

    float damage;

protected:

    virtual void ParseMembers (gugu::DatasheetParserContext& context) override;
};

////////////////////////////////////////////////////////////////
class DS_EffectHeal : public DS_Effect
{
public:

    DS_EffectHeal();
    virtual ~DS_EffectHeal();

public:

    float heal;

protected:

    virtual void ParseMembers (gugu::DatasheetParserContext& context) override;
};

////////////////////////////////////////////////////////////////
void DatasheetBinding_Register();

////////////////////////////////////////////////////////////////
gugu::Datasheet* DatasheetBinding_InstanciateDatasheet(const std::string& classType);

} // namespace demoproject
