export module ecs.EntityContainer;
import <cstddef>;
import <bitset>;
import <vector>;
import <numeric>;
import ecs.Def;
export namespace ecs {
    template<std::size_t ComponentCount, std::size_t SystemCount>
    class EntityContainer
    {
    public:
        void reserve(std::size_t size);
        std::vector<std::bitset<ComponentCount>>& getEntityToBitset();
        const std::bitset<ComponentCount>& getBitset(Entity entity) const;
        Entity create();
        void remove(Entity entity);
    private:
        std::vector<std::bitset<ComponentCount>> mEntityToBitset;
        std::vector<Entity> mFreeEntities;
    };
};
using namespace ecs;
template<std::size_t ComponentCount, std::size_t SystemCount>
void EntityContainer<ComponentCount, SystemCount>::reserve(std::size_t size)
{
    mFreeEntities.resize(size);
    std::iota(std::begin(mFreeEntities), std::end(mFreeEntities), 0);
    mEntityToBitset.resize(size);
}

template<std::size_t ComponentCount, std::size_t SystemCount>
std::vector<std::bitset<ComponentCount>>& EntityContainer<ComponentCount, SystemCount>::getEntityToBitset()
{
    return mEntityToBitset;
}

template<std::size_t ComponentCount, std::size_t SystemCount>
const std::bitset<ComponentCount>& EntityContainer<ComponentCount, SystemCount>::getBitset(Entity entity) const
{
    return mEntityToBitset[entity];
}

template<std::size_t ComponentCount, std::size_t SystemCount>
Entity EntityContainer<ComponentCount, SystemCount>::create()
{
    auto entity = Entity();
    if (mFreeEntities.empty())
    {
        entity = static_cast<Entity>(mEntityToBitset.size());
        mEntityToBitset.emplace_back();
    }
    else
    {
        entity = mFreeEntities.back();
        mFreeEntities.pop_back();
        mEntityToBitset[entity].reset();
    }
    return entity;
}

template<std::size_t ComponentCount, std::size_t SystemCount>
void EntityContainer<ComponentCount, SystemCount>::remove(Entity entity)
{
    mFreeEntities.push_back(entity);
}
