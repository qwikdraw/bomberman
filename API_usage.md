# API documentation

## VoxObject - included with "voxGL.hpp"

### VoxObject(std::string filepath)

create a VoxObject by passing a valid path to a .voxobj file

### void	Load(void)

prepares the object for drawing. Should only be called once

### void	Unload(void)

call when you are finished with object.

### void	SetTransform(glm::mat4)

Change the transform matrix used by the object. Used to rotate the model.
Can also be used to move model but its better to use SetPos. Transform matrix is initially
set to the identity.

### glm::mat4	GetTransform(void)

retrieve the transform currently being used.

### void	SetPos(glm::vec3)

Change the position of the object. Initially set to (0, 0, 0).

### glm::vec3	GetPos(void)

retrieve the position being used.

### void	Move(glm::vec3)

update the position of object by amount specified.

## VoxRenderer - included with "voxGL.hpp"

### VoxRenderer(void)

### void	AttachObject(VoxObject *object)

add a **Loaded** VoxObject to the VoxRenderer

### void	DettachObject(VoxObject *object)

remove the object from the VoxRenderer

### void	Render(void)

render all loaded VoxObjects

### void	NewPerspective(glm::mat4)

Use the new perspective matrix when rendering the object. Discards previous perspectives.
**Must be used before rendering!**

## Window - included with "voxGL.hpp"

### Window(int x, int y, std::string name)

create the window with x width, y height, with name as the title.

### bool	IsOpen(void)

tells you if window is open.

### void	SetRenderZone(float x, float y, float width, float height)

specify the area of the screen you wish to draw to. (x, y) is the coordinate of the bottom left part
of the rectangle you wish to draw to. Width and Height specify the height of the rectangle you wish
to draw to.

initially set to x = 0, y = 0, width = 1, height = 1. aka - entire screen is being drawn to.

### void	ClearRenderZone(void)

clear your current render zone.

### void	UpdateEntireWindow(void)

update the entire window. Must be called for the changes to become visable.

### void	EventListen(void)

lets the window start processing events like keystrokes

### bool	&KeyOn(int)

returns the status of a particular key being held on, based on keycode.

## Time - included with "voxGL.hpp"

### Time(void)

### void	Fix(void)

fixes the time value to the time when this function was called and allows it to be read from GetTime()
and GetDeltaTime().

### void	Reset(void)

resets the timer to 0 seconds

### float	GetTime(void)

returns the time elapsed from class creation / Reset() was called, to the most recent Fix() being called.
Time is returned in seconds.

### float	GetDeltaTime(void)

returns the time elapsed between the current Fix() and the previous one.

## Camera - included with "voxGL.hpp". Implementation will change soonTM

### Camera(void)

### void	Move(glm::vec3 amount)

move the position of camera by amount

### void	Rotate(glm::vec3 axis, float degrees)

rotate camera about axis by degrees.

### void	TrackEvents(Window*)

Track events for the camera. Must be called - currently at least.

### void	Update(void)

updates the camera based on key inputs

### bool	JustMoved(void)

reveals if the camera has moved between now and the previous time you called this function.

### glm::mat4	Perspective(void)

returns the perspective matrix generated from the camera. This is essential and the whole reason you
have a camera so use it.


## Grid - included with "debug.hpp"

### Grid(float squareSize = 1, float squareLen = 100, glm::vec3 center = glm::vec3(0, 0, 0),
glm::mat4 transform = glm::mat4(1))

squareSize is the size of a grid square, squareLen is the number of squares the edge of the Grid is
made of. Center is the position the Grid is in, and transform is the orientation the Grid is in.

### void	NewPerspective(glm::mat4)

the grid will be drawn with this perspective matrix. Must be called once.

### void	Render(void)

render the grid