# FSM

The purpose of this project is to showcase an implementation of a Finite State Machine that is specifically tailored towards open-world games, taking into account the needs and difficulties of big scale productions. This document describes the design of this implementation, as well as the software architecture decisions behind it.

The goals of this implementation are as follows:
- Be easy to extend and maintain behaviors
- Facilitate code reuse
- Be scalable with number of agents

This project focuses on the aspects related to the AI architecture. Consequently, the supporting game systems needed by the FSM have been kept to a minimum. This includes the output of the system being in the form of a text-based console log, in order to avoid the complexities of a full game environment and rendering pipeline.
