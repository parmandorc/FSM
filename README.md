# FSM

The purpose of this project is to showcase an implementation of a Finite State Machine (FSM) that is specifically tailored towards open-world games, taking into account the needs and difficulties of big scale productions. This document describes the design of this implementation, as well as the software architecture decisions behind it.

The goals of this implementation are as follows:
- Be easy to extend and maintain behaviors
- Facilitate code reuse
- Be scalable with number of entities

This project focuses on the aspects related to the AI architecture. Consequently, the supporting game systems needed by the FSM architecture and by the behaviors have been kept to a minimum, with some of the logic being simply simulated by random chance (instead of implementing full game systems for elements such as in-world positions, health and resources, or raycasts for line of sight checks). This also includes the output of the system being in the form of a text-based console log, in order to avoid the complexities of a full game environment and rendering pipeline.

### State design pattern

Some common FSM implementations are based on the use of enums to determine the current state and execute the logic that is specific to that state. Even if this is the fastest way to implement an FSM, its main disadvantage is that it often leads to the full state machine logic being defined in a single file, which quickly becomes incredibly complex to maintain.

A better solution would be to have the logic specific to each state in a separate class, and just store a pointer to the current state object. By adhering to the single responsibility principle, this makes it much easier to fix issues related to a specific state. Additionally, this makes it easier to reuse code, as the same state logic can now be used by different state machines for different behaviors.

### Separation of state and transition logic

An important element of this implementation is the separation of state logic and transition logic into different classes. The state classes only contain the logic about what each state does (the effects of a state on the entity and the actions to be carried out), without defining the transitions to other states, which are only specified in the FSM classes. By removing any explicit references to other states, the same state class can be used in different state machines to build different behaviors, which facilitates code reuse.

Another benefit of this is that the cost of potentially transforming the current architecture into a Behavior Tree (BT) is greatly reduced. By understanding that BTs and FSMs are just different methods of describing transitions between behavior nodes, the state classes could with little change be used as nodes of a BT. The main piece of work would only be implementing a different interface for specifying the transition logic in the form of a tree via sequence and selector nodes.

### Single shared instances

One key aspect of this architecture is the existence of a unique instance of each state and FSM class that is reused for all entities in the world, instead of each entity having a full copy of its state machine. This solution offers minimal memory cost in games with a large number of entities.

To accommodate for this design, state classes must not store any data as member variables, but instead save any state information directly in the entity or any of its components (preferrably a blackboard data structure). Consequently, the entity whose behavior is being updated is passed as a parameter in all the methods of the interface of both the state and FSM classes, but never stored and accessed as a member variable. Additionally, due to the instances of each class remaining constant, they can be kept alive through the lifetime of the application, which makes it safe to reference them through simple pointers (for example, when storing the current state for an entity).

### Type as key and templates

The single common instances of the states and FSMs are kept in their respective container classes, and they are stored in a map data structure with their class type as key (by making use of `std::type_index`). This makes it possible to access the state and FSM instances by passing the class as argument in a templated function. In a project where the FSM logic is fully in code, this leads to less errors compared to referring to states and FSMs by their names as strings (which cannot be statically checked).

However, in a production-level project where data-driven solutions are preferred, it would be nice to at least move the definition of FSMs (transition logic between states) to data files. For this, it would be simple enough to modify the existing container classes to support accessing states and FSMs by their name as a string (instead of or in addition to by their class type).

### Hierarchical Finite State Machines

One common problem of FSMs is the maintainability of complex transition networks, which can often become incredibly entangled and hard to debug. This can be mitigated with the use of Hierarchical FSMs (HFSMs). The main scenario that HFSMs attempt to solve is the case where a big number of states all have transitions to the same target state, which leads to a big number of similar transitions being defined. To solve this, it is possible to group all the origin states together into a child FSM, and define one single transition from the sub-FSM as a whole to the target state, which greatly reduces the number of transitions and reduces complexity.

For this, it must be possible to use FSMs as states themselves in a parent FSM, so that transitions can be defined from a sub-FSM to another state (or another sub-FSM). In this implementation, this is achieved with the `FSMHierarchicalState` class, which acts as a wrapper of an FSM instance and correctly maps all the methods in the state class to the relevant methods of the FSM class.

Note that in other implementations that do not separate state and transition logic, HFSMs are often accomplished by making all the origin states classes inherit from a parent state class where the common transitions are defined. Nevertheless, this increases the complexity of the code, especially with hierarchies that are multiple levels deep (which would translate to multiple levels of inheritance).

One problem with the current implementation, however, is that it would currently be possible to define a transition to a parent FSM (or one that is higher in the hierarchy), which would introduce a logic infinite loop. This could be solved relatively easily by introducing a validation step that checks against cycles in the transtion hierarchy.

### Stack-based Finite State Machines

One limitation of regular FSMs is a lack of memory, that is, the inability to know the state that was previously running before the current one. A typical solution to this problem is the use of Stack-based FSMs (SFSMs), where the pointer to the current state is replaced with a stack of states. This introduces push-pop semantics to the transition logic, and makes it possible for the state machine to return to the previously running state after the current one is popped from the stack, thus resuming previous behavior.

In addition to this, this implementation offers transition callbacks that are specific to stack-based transitions, in order for states to fully benefit from the stack semantics and be able to resume previous behavior. For this, state classes can override the `OnResume` and `OnPause` methods, which act as stack-specific equivalents of the `OnEnter` and `OnExit` methods, respectively. Note that if the stack-specific methods are not overridden, the regular transtion callbacks will be called by default.
