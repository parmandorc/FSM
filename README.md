# FSM

The purpose of this project is to showcase an implementation of a Finite State Machine that is specifically tailored towards open-world games, taking into account the needs and difficulties of big scale productions. This document describes the design of this implementation, as well as the software architecture decisions behind it.

The goals of this implementation are as follows:
- Be easy to extend and maintain behaviors
- Facilitate code reuse
- Be scalable with number of agents

This project focuses on the aspects related to the AI architecture. Consequently, the supporting game systems needed by the FSM have been kept to a minimum. This includes the output of the system being in the form of a text-based console log, in order to avoid the complexities of a full game environment and rendering pipeline.

### State design pattern

Some common FSM implementations are based on the use of enums to determine the current state and execute the logic that is specific to that state. Even if this is the fastest way to implement an FSM, its main disadvantage is that it often leads to the full state machine logic being defined in a single file, which quickly becomes incredibly complex to maintain.

A better solution would be to have the logic specific to each state in a separate class, and just store a pointer to the current state object. By adhering to the single responsibility principle, this makes it much easier to fix issues related to a specific state. Additionally, this makes it easier to reuse code, as the same state logic can now be used by different state machines for different behaviors.
