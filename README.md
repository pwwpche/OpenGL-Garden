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






