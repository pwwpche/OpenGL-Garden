# Garden Simulation 
 Project of Computer Graphics


## Classes
| Class | Description  |
| ----- |:------------:|
|MainWindow| Main window of the program, receive user's input, outputs  | 
|QGLWidget | Holds an OpenGL Widget, process mousing and keyboard events, initialize the program. Drawing methods of all classes must be invoked in this function so that the actual object can be drawn.       |
|Camera    | Control user's viewpoint. It can control the direction, position of the viewpoint. User can change viewpoint position, look up/down and left/right, and even jump(just for fun :D).     |
|TextureManager	|Load and store all the textures into memory. Texture rendering is managed by this class.|
|Sky	|A sky sphere covers the whole sky. The sphere is constantly rotating, thus simulate the moving clouds. |
|Ground	|There are two kind of textures, one is grassland, another is snowland. Heightmap is used to simulate the ups and downs. |
|Fence	|Drawing the fence. Viewpoint cannot leave the fence area. |
|Snow	|Drawing snow. User can control the snow area, as well as the number of flakes in the snow. |
|Flake	|Flakes in the snow, just used to store the position of each flake. |
|Fog	|Fogging weather, implemented but not used here. |
|Wind|Control the direction and strength of wind. Wind can affect the track of falling flake. |
|Flower	|User can control the color, levels, shape of the flower, and each patel is generated using elliptic surface. |
|Tree|User can also draw trees. The branches and leaves of tree are rendered in different textures. |

##Implementation

###Sky Sphere
======
Sky sphere is implemented through sky sphere and texturing. `Point(0, 0, 0)` as center, we draw a sphere with `Radius = 1000`, and render textures directly on the sphere. Compare to Sky Box, sphere looks more natural. As long as the texture is rendered properly, it will avoid the problem of processing borders, which happens more common in Sky Box.

Additionally, the mass calculation of sphere drawing can be eliminated by reducing the value of `slice` parameter in `gluSphere` function. Once the sphere is generated, we can add it to display list to further improve our performance. 

###Flowers and Petals
======
Flowers and petals are implemented using ecliptic surfaces, and user can set the shape and number of petals himself. Changes to the color of the flower can be reflected by using different texture. 

Ecliptic surface is suitable for simulating the curving of petals. We first tilt the coordinating system, and use `X` - `Z` as our plane on which we draw the eclipse. We add some curving functions to `Y` axis, then we can achieve the curving effect on the petals. 

As for redundant trigonometric function invoking, we store the value of each radius value from `0` to `pi`, with an interval of `0.01`. This is because we do not require our trigonometric function to be accurate. Rough estimation is enough for drawing our petals and flowers. This optimization eliminates huge function invoking time. Before optimizing, rendering a flower with 20 flakes only achieves 2-3 fps, and if we add this optimization, we not only achieve the almost same effect, but the refreshing frequency is also significantly improved to 60fps. 

The parametric equation of our ecliptic surface is:
```
 x = a*cos(theta)
 y = 0.1*sin((x+a)*pi/a)
 z = b*sin(theta)
```
In which the larger `a` is, the longer the petals and leaves will be; the larger `b` is, the wider the petals and leaves will be.


###Ground
======
Terrain effect is achieved by adopting `HeightMap` to the ground. A height map stores height value of each point on the ground. When we draw the terrain, for each slice of the terrain sized `MAP_SIZE * MAP_SIZE`, we use two triangles to cover it, and add some texturing on it. After drawing these numerous triangles, we store the whole terrain to display list. User can still arise the height of some point on the ground, and after modifying, the modified version of terrain will be updated in the display list. 

###Interaction with user 
======
The graphic user interfaced is written in C++ Qt. Mouse events and keyboard events are monitored by `MainWindow`, and passed to `QGLWidget`, which is the holder of OpenGL window. User can also save the settings of flowers and trees to data file on disk, and restore the data from disk, and load them into our garden one by one. 

###Simulation of snow
======
Polygon simulation was not adopted, since it takes huge CPU work, and since there might be at least thousands of flakes falling simultaneously from the sky, this method will not work. Instead, we use the `Point Sprite` system supported by OpenGL, and perform perspective transformation so that the flakes closer will seems larger. Using Point Sprite is similar to using `glPoint`, and thus it saves lots of time calculating each point in the flake polygon. If we enable texturing on the point sprite, and enable mixture of sprites with background, we can keep FPS up to 60 and achieve the hexagon effect on the flakes at the same time. 

As for each plant (trees and flowers), when plant itself is set up, the height map of this plant is calculated at the same time. The height map stores the highest point of the plant to the ground. As for the implementation, when the plant is created, a 2d array of `SIZE * SIZE` (SIZE is the unit size of the ground, in my code, SIZE is set to 0.5) is also created. Thus we can record how many flakes have fallen onto each `0.5*0.5` grid. When snowing, we first determine whether this flake is above some plant, and then determine whether this flake collapse with this plant, by comparing the height of the flake to the ground and the height of the plant at this point. If flake falls lower than the height of the plant, it must have fallen onto our plant. Then we record the index of this point, and draw a flake on the plant at this point. 

###Optimization of terrian
======
I usually adapt display list to store the terrain, but hereby in order to simulate the piling of snow, height of the terrain keeps changing, and this changing value cannot be optimized by using display list. Thus `Vertex Buffer` is adopted here.`(X, Y, Z)` values of each point is stored into vertex buffer, and each vertex is used to generate the triangle of terrain. At the same time, values of each texturing vertex are also buffered into vertex buffer. When drawing terrain, we first enable the corresponding buffer, then we only need to invoke `glDrawElements` once. Lots of function invoking is eliminated by this optimization. 

Moreover, when drawing slices of terrain, we first get the number of flakes fallen onto this slice, then use multi-texturing two color the ground. By adjusting the ratio of grassland texture and the snow texture, snowing effect can be simulated more naturally, and at the same time still maintain a high rendering FPS. 

When drawing the ground, we first get the position and height of each vertex, and then scale the ground to avoid to have cliffs on the ground. Each square of the ground is composed by two triangles:
```
V3------V2
|    /  |
|   /   |
|  /    |
V0------V1
Triangle1 : V0 -> V3 -> V1
Triangle1: V0 -> V2 -> V3
```

Finally, each vertex is normalized, and `colorBuffered` is adopted at the same time, in which RGB channel is used store the percentage of grassland to the snow land, and Alpha channel to store the percentage of snow texture. 








