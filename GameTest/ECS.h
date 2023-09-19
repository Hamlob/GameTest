#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;


typedef std::size_t COMP_TYPE_ID;

inline COMP_TYPE_ID getCOMP_ID() {

	static COMP_TYPE_ID lastID = 0;
	return lastID++;
}
 
/**
 * Function that takes a component and returns the type of the component in form of ID.
 * 
 * \return A component ID, which represents the type of the component (e.g. position, health..)
 */
template <typename T>
inline COMP_TYPE_ID getCOMP_TYPE_ID() noexcept {
	static COMP_TYPE_ID typeID = getCOMP_ID();
	return typeID;
}

//maximum number of components
constexpr COMP_TYPE_ID maxComponents = 32;

/** 
 * bitset stores which of the components are used for a given entity.
 * If the position component has typeID of 0, and an entity has position, the 0th element in this bitset would be true.
*/
typedef std::bitset<maxComponents> COMP_BITSET;

//array holding the pointers to the components of a given entity.
typedef std::array<Component*, maxComponents> COMP_ARRAY;


class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component(){}

};

/**
 * Entity class represents a game objects (player, enemy, item).
 * Its properties and what it is is given by its component (characteristics).
 */
class Entity
{
public:
	
	//Cycles through all components of the entityand updates them
	void update() {
		for (auto& c : _components) c->update();
	}

	//Draws function draws this entity.
	void draw() {
		for (auto& c : _components) c->draw();
	}

	bool isActive() const { return _active; }

	void destroy() { _active = false; }


	//Maybe change the function to take component ID instead of the actual component
	/**
	 * Function to check whether an entity has a given component. 
	 * NOTE: template<typename> is used since COMPONENT can be different types.
	 * 
	 * \return True if it does, False if not.
	 */
	template <typename COMP>
	bool hasComponent() const {
		return _compBitset[getCOMP_TYPE_ID<COMP>()];
	}

	/**
	 * Adds a component to the entity.
	 * NOTE: template <typename> is used because components and their argumentscan be different types
	 * 
	 * \param ...mArgs	Any arguments needed for the creation of a given component.
	 * \return 
	 */
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {

		T* newComp(new T(std::forward<TArgs>(mArgs)...));	//forward is a wrapper for passing typename args as  actual function
		
		newComp->entity = this;	//link the component to this entity

		std::unique_ptr<T> uPtr{ newComp };	//create a unique pointer to the new component

		_components.emplace_back(std::move(uPtr)); //appends the pointer the end of the vector holding component pointers
		
		COMP_TYPE_ID typeID = getCOMP_TYPE_ID<T>();	//check the type id of the new component
		_compArray[typeID] = newComp;			//store the pointer in comp array at corresponding position according to typeID.
		_compBitset[typeID] = true;				//flag that the entity includes the new component of a given type

		newComp->init();

		return *newComp;//why are we returning newComp if we already have it stored in comparray and components_p???
	}

	/**
	 * A function that returns the component Again this should be taking COMP id as input not comp itself.
	 * 
	 * \return 
	 */
	template <typename COMP> 
	COMP& getComponent() const {
		auto ptr(_compArray[getCOMP_TYPE_ID<COMP>()]);	//get the pointer from the comp array, auto keyword is used since we dont know what type COMP is
		return *static_cast<COMP*>(ptr);			//cast the pointer into the corresponding COMP type
	}

private:

	bool _active = true;
	std::vector<std::unique_ptr<Component>> _components;	//vector holding the pointers to all components of the given entity

	COMP_ARRAY _compArray;
	COMP_BITSET _compBitset;

};


class EntityManager
{
public:

	//updates all active entities
	void update() {
		for (auto& e : entities) e->update();
	}

	//draws all active entities
	void draw() {
		for (auto& e : entities) e->draw();
	}

	void refresh() {
		
		//erase function goes through the iterator and removes the elements. 
		//remove_if iterator is used to prevent skipping of elements that happens 
		//when an array is changed while iterating over it.
		entities.erase(		
			std::remove_if		//remove_if returns an iterator for the elements satifsying the condition returned by lambda function
			(
				entities.begin(),	//start for the remove if 
				entities.end(),		//end for the remove if
				[](const std::unique_ptr<Entity>& e) { return false == e->isActive(); }	//lambda function used to satisfy the condition deciding which elements to be removed (true means remove)
			),
			entities.end()		//end of the array
		);
	}
	//https://youtu.be/XsvI8Sng6dk?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&t=1519


	Entity& addEntity() {
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr(e);
		entities.emplace_back(std::move(uPtr));
		return *e;
	}

private:
	std::vector<std::unique_ptr<Entity>> entities;	//vector holding the pointers to all entities
};
