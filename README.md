# Automated Vehicle Simulation (WORK UNDER PROGRESS)

AVSIM will be a 2D-Simulation for short-term maneuver planning with automated vehicle systems.

Currently, there is a (static) world containing agents, obstacles and the road. Geometric functionality like collision check for rectangular geometries with SAT and bounding boxes are also provided. \
Everything can be exported as shared library to be accessible with python.

Next:
- Visualization of the world (for general visualization and debugging)
- Adding dynamics enabling agents to move (basic functionality including polynomial trajectory planning)
- Building state spaces for agents
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
