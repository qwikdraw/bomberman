# API documentation

__

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