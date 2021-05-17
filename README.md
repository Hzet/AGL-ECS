# About
AGL ECS is a very simplified implementation of an entity-component-system written in C++17. The library is not **YET** thread-safe!

# Code example
```c++
#include <iostream>
#include "../src/entity.hpp"

struct SPosition
{
	int x;
	int y;
};

struct SAcceleration
{
	int x;
	int y;
};

agl::CRegistry registry;

void update()
{
	// Get view containing every entity that has at least these components attached.
	auto view = registry.view<SPosition, SAcceleration>();

	// Use forward iterators to iterate over the components of entities.
	for (auto[pos, acc] : view)
	{
		/* ... */
	}
}

int main()
{
	for (std::uint64_t i = 0ul; i < AGL_MAX_ENTITIES; i++)
	{
		// Register an entity
		agl::IEntity entity = registry.create();

		// Attach default initialized components in bulk
		entity.attachComponent<SPosition, SAcceleration>();

		/*
		// Alternatively one can attach components initialized from values, which is unfortunately slower
		entity.attachComponent<SPosition>(1, 1);
		entity.attachComponent<SAcceleration>(2, 2);
		*/
	}

	update();
}
```

# Performance
### Time complexity
##### O(1)
Attaching, detaching and getting the component from an entity.
##### O(n)
Getting the view of entities with given signature is a bit more demanding since the registry has to iterate through all the entities and compare its signature. 
To compare two signatures the system has to iterate through every  bit of the signature and compare it with coresponding bit of the other signature.
### Space complexity
Unfortunately the space complexity is not as nice as time complexity. Each component array that has been used at least once creates an array of 'AGL_MAX_ENTITIES' elements, which can be enormously huge when the component has relatively big size.

### Numeric values
|  Entities count / component count  | Create  | Attach with value  | Attach default initialized  | Attach default initialized (bulk)  | Detach  | Detach (bulk)  | Get and iterate through the view  |
| :------------: | :------------: | :------------: | :------------: | :------------: | :------------: | :------------: | :------------: |
|  1.000.000 / 3 | 15.2ms  | 63.7ms  | 20.1ms  | 16.6ms  | 11.6ms  | 10.8ms  | 2.5ms  |

Test machine: 8GB, i5 4590

# How it works?
### Basic information
First of all, to set the total number of available entities and components there are two macro defines:
 - AGL_MAX_ENTITIES - total number of available entities
 - AGL_MAX_COMPONENTS - total number of different component types
 
Each entity can be associated with only one component per component type.
Each component can be associated with only one entity.
### Implementation details
I will start unwraping the implementation from the class that is used by the user most often, down to the classes implementing the real functionalities.

##### CRegistry
Is a main coordinator between the user and the AGLECS. The registry is a global variable, that can be accessed from anywhere in the user's code. From the user's perspective the registry provides only three methods:
- **create** - registers an entity
- **destroy** - unregisters an entity
- **view** - returns the view

From the library's perspective it is the main communication service between the entity and the components. Under the hood it has methods to attach, detach and get components associated with given entity.

The registry is a facade build atop of two classes:
- **IRegistryComponent** - a sub-coordinator dedicated to supervise the association of entities and components
- **IRegistryEntity** - a sub-coordinator dedicated to supervise the creation and destruction of entities.

Therefore the CRegistry class is just a supervisor and coordinator of actions taken on entities and components.

##### IEntity
Is a class representing the entity. Besides the attach, detach and get methods, it also provides two important features:
- The entity's unique identifier
- The signature of associated components

When calling for attach, detach and get methods, the entity delegates these operations and calls 'registry' object coordinator to apply them.

##### TComponentArray
This is the place in which the components are stored and it's relation with the entity is established. The relation is implemented such way, that the entity's unique identifier is used as an index to a component.
Component arrays are inheriting from **IComponentArray** which is an abstract, polymorphic base to store the arrays in supervising object (**IRegistryComponent**).

# Future plans
- Provide an alternative to **TComponentArray** which uses less memory.
- Make the library thread-safe
