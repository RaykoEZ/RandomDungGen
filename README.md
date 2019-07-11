# Random Dungeon Generation (RandomDungGen)
____

This project is a WIP for a pure C++ plugin to procedurally generate 2D square-grid floor maps for a dungeon crawler game made in Unreal Engine 4 (Maybe other engines in the future).

The method of construction paths is agent-based, choatic results are acknowledged and appreciated in this project. 

More will be added as I progress through the development.
____

## Prerequisites

- Unreal project is based on Unreal Engine 4.22
- Source code is based on Visual Studio 2017 (15.9.13)
- Unreal SDK package required
____

## Current Results & Usage

- Room allocation accepts overlapping to create a chaotic environment (And to save some time on not checking for overlapping/merging rooms).

- Only one floor is rendered in the scene at a time whilst many floors can be pre-generated.

- For the DungeonInfo actor in project (not the plugin) does not require the user to construct their own FDungeonProperties and UInstanceStaticMeshComponent. 

- For now, the coordinate output fits assets with 1x1 size (a 1x1 box engine asset is used in the project for now).

- Currently, modifying the dungeon properties (**M_Prop** under **DungeonInfo**'s **Dungeon Info**) in the **Details Panel** automatically regenerates the floors.

____
## Pending Improvements & Future Works

- Only the floor tile positions are rendered right now, future updates may output the wall tiles from another function. Maybe more than just walls~

- Details Panel lacks a "(Re)Generate Dungeon" button, will include the feature in the future.

- Code optimization is far from over, some processes can be parallelized if Unreal does not fully handle it.

- Future update may allow inputs of custom asset dimensions.

- May allow custom state machines for path-tracing in the future
____
## Images

![Iamge 1](https://github.com/RaykoEZ/RandomDungGen/blob/master/Images/Example_Bigger.png)

![Image 2](https://github.com/RaykoEZ/RandomDungGen/blob/master/Images/Example_Small.png)

____
## Current References

- [Unreal Engine Training Livestream - Procedural Room Creation, commentary from Ian Shadden and Chance Ivey, 2015](https://www.youtube.com/watch?v=mI7eYXMJ5eI)

- [Forum-linked Document for a Procedural Dungeon generator in a Blueprint, by Forum User - Shining Pear](https://docs.google.com/document/d/1fNG02ujyfAc45we_ZICmcs8sHBnCseV8GJXWi9I6C3g/edit)

- [Rooms and Mazes: A Procedural Dungeon Generator, by Bob Nystrom](https://journal.stuffwithstuff.com/2014/12/21/rooms-and-mazes/)

- [Constructive generation methods for dungeons and levels, by Noor Shaker, Rafael Bidarra and 3 more, published at ResearchGate, 2016](https://www.researchgate.net/publication/309279824)