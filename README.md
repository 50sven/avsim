# Automated Vehicle Simulation (WORK UNDER PROGRESS)

AVSIM will be a 2D-Simulation for short-term maneuver planning with automated vehicle systems.

Currently, the world is represented by a static road network and obstacles as well as dynamic agents. Collision checking for rectangular geometries with SAT is provided to validate the world state. Additionaly, rendering is possible with a set of debug colors. \
Functionalities can be exported as shared library to be accessible with python (exports are finalized when c++ implementation is done).

Next:
- Building state spaces for agents to synchronize world state
- Adding polynomial trajectory planning
- Finalize the visualization of the world
- Finalize python exports
- Creating open ai gym environment
- ...

## Building AVSIM

1\. Clone this repository to your local machine:

```bash
git clone https://github.com/50sven/avsim.git
```

2\. Run [`build.sh`](./build.sh):

Use the `--BUILD_PYTHON` flag to build a shared library for usability in python:

```bash
cd avsim
./build.sh
```
