# Automated Vehicle Simulation (WORK UNDER PROGRESS)

AVSIM will be a 2D-Simulation for short-term maneuver planning with automated vehicle systems.

Currently, there are (static) agents, obstacles and the road as well geometric functionality like collision check for rectangular geometries with SAT and bounding boxes.

Next:
- World: integration of agents, obstacles and road network into one class
- Visualization of the world
- Adding dynamics enabling agents to move
- Building open ai gym environment
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
