# Garden Simulation 
 Project of Computer Graphics

### Project Structure
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

###Implementation

####Sky Sphere
Sky sphere is implemented through sky sphere and texturing. `Point(0, 0, 0)` as center, we draw a sphere with `Radius = 1000`, and render textures directly on the sphere. Compare to Sky Box, sphere looks more natural. As long as the texture is rendered properly, it will avoid the problem of processing borders, which happens more common in Sky Box.

Additionally, the mass calculation of sphere drawing can be eliminated by reducing the value of `slice` parameter in `gluSphere` function. Once the sphere is generated, we can add it to display list to further improve our performance. 

####Flowers and Petals
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







