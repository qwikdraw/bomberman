
#include "voxGL.hpp"

VoxelChunk::VoxelChunk(void)
{
}

VoxelChunk::VoxelChunk(int arr[])
{
	for (int i = 0; i < size * size * size; i++)
	{
		_array[i] = arr[i];
	}
}

VoxelChunk::VoxelChunk(const std::function<int(int, int)> &f)
{
	for (int i = 0; i < size * size * size; i++)
	{
		_array[i] = f(i, size);
	}
}

int	&VoxelChunk::Item(int i, int j, int k)
{	
	return _array[i + size * j + size * size * k];
}

int	&VoxelChunk::Item(int i)
{
	return _array[i];
}

void	VoxelChunk::ApplyMatrix(glm::mat4 m)
{
	_transform *= m;
	_pos = glm::vec3(glm::vec4(_pos, 1) * m);
}

void	VoxelChunk::UseMatrix(glm::mat4 m)
{
	_transform = m;
	_pos = glm::vec3(glm::vec4(_pos, 1) * m);
}

void	VoxelChunk::Load(void)
{
	OcclusionRecolor();

	RemoveHiddenSides();

	GetTriangleData();
	
	glGenBuffers(1, &_triangleBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _triangleBufferID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLfloat) * _triangles.size(),
		     &_triangles[0],
		     GL_STATIC_DRAW);

	glGenBuffers(1, &_normalBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _normalBufferID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLfloat) * _normals.size(),
		     &_normals[0],
		     GL_STATIC_DRAW);

	glGenBuffers(1, &_colorBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, _colorBufferID);
	glBufferData(GL_ARRAY_BUFFER,
		     sizeof(GLfloat) * _colors.size(),
		     &_colors[0],
		     GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void	VoxelChunk::Render(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, _triangleBufferID);	
	glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, _normalBufferID);
	glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, _colorBufferID);	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glDrawArrays(GL_TRIANGLES, 0, _triangles.size() / 3);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void	VoxelChunk::Unload(void)
{
	glDeleteBuffers(1, &_triangleBufferID);
	glDeleteBuffers(1, &_normalBufferID);
	glDeleteBuffers(1, &_colorBufferID);
}

glm::mat4	&VoxelChunk::GetTransform(void)
{
	return _transform;
}

glm::vec3	VoxelChunk::Pos(void)
{
	return _pos;
}

void	VoxelChunk::RemoveHiddenSides(void)
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			for (int z = 0; z < 10; z++)
			{
				if (IsBlock(x + 1, y, z))
				{
					_array[x + y * size + z * size * size] |= right;
				}
				if (IsBlock(x - 1, y, z))
				{
					_array[x + y * size + z * size * size] |= left;
				}
				if (IsBlock(x, y + 1, z))
				{
					_array[x + y * size + z * size * size] |= top;
				}
				if (IsBlock(x, y - 1, z))
				{
					_array[x + y * size + z * size * size] |= bot;
				}
				if (IsBlock(x, y, z + 1))
				{
					_array[x + y * size + z * size * size] |= back;
				}
				if (IsBlock(x, y, z - 1))
				{
					_array[x + y * size + z * size * size] |= front;
				}						
			}
		}
	}
}

bool	VoxelChunk::IsBlock(int x, int y, int z)
{
	if (x <= -1 || x >= 10 || y <= -1 || y >= 10 || z <= -1 || z >= 10)
		return false;

	int block = _array[x + y * size + z * size * size];

	block <<= 8; //check to see if the color value is not 0
	
	if (!block)
		return false;
	return true;
	
}

void	VoxelChunk::OcclusionRecolor(void)
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			for (int z = 0; z < 10; z++)
			{
				float exposedSides = 6;

				if (IsBlock(x, y, z))
				{				
					if (IsBlock(x + 1, y, z))
					{
						exposedSides--;
					}
					if (IsBlock(x - 1, y, z))
					{
						exposedSides--;
					}
					if (IsBlock(x, y + 1, z))
					{
						exposedSides--;
					}
					if (IsBlock(x, y - 1, z))
					{
						exposedSides--;
					}
					if (IsBlock(x, y, z + 1))
					{
						exposedSides--;
					}
					if (IsBlock(x, y, z - 1))
					{
						exposedSides--;
					}
					ShadeColor(_array[x + y * size + z * size * size],
						   exposedSides / 6,
						   0.2);
				}
			}
		}
	}
}

void	VoxelChunk::ShadeColor(int &col, float factor, float contrast)
{
	float shadeAmount = (factor - 0.5) * contrast * 255;

	float blue = static_cast<float>( col % 256 );
	float green = static_cast<float>( (col / 256) % 256 );
	float red = static_cast<float>( (col / (256 * 256)) % 256 );
	
	blue += shadeAmount;
	green += shadeAmount;
	red += shadeAmount;
	
	int iblue = std::max(0.0f, std::min(blue, 255.0f));
	int igreen = std::max(0.0f, std::min(green, 255.0f));
	int ired = std::max(0.0f, std::min(red, 255.0f));
	
	col = iblue + igreen * 256 + ired * 256 * 256;
}

void	VoxelChunk::GetTriangleData(void)
{

	glm::vec3 vtop = {0, 1, 0};
	glm::vec3 vbot = {0, -1, 0};
	glm::vec3 vleft = {-1, 0, 0};
	glm::vec3 vright = {1, 0, 0};
	glm::vec3 vfront = {0, -1, 0};
	glm::vec3 vback = {0, 1, 0};
			  
	
	for (int i = 0; i < size * size * size; i++)
	{
		if (!IsBlock(i % 10, (i / 10) % 10, (i / 100) % 10))
			continue;
		glm::vec3 p;

		p.x = i % 10 - 4.5;
		p.y = (i / 10) % 10 - 4.5;
		p.z = (i / 100) % 10 - 4.5;

		glm::vec3 v000 = p + glm::vec3(0, 0, 0);
		glm::vec3 v001 = p + glm::vec3(0, 0, 1);
		glm::vec3 v010 = p + glm::vec3(0, 1, 0);
		glm::vec3 v011 = p + glm::vec3(0, 1, 1);
		glm::vec3 v100 = p + glm::vec3(1, 0, 0);
		glm::vec3 v101 = p + glm::vec3(1, 0, 1);
		glm::vec3 v110 = p + glm::vec3(1, 1, 0);
		glm::vec3 v111 = p + glm::vec3(1, 1, 1);

		glm::vec3 col = { static_cast<float>( ((_array[i] / (256 * 256)) % 256 )) / 255,
				  static_cast<float>( ((_array[i] / 256) % 256 )) / 255,
				  static_cast<float>( (_array[i] % 256 )) / 255 };

//		glm::vec3 col = {1, 1, 1};
		
		if (!(_array[i] & top))
		{
			_triangles.insert(_triangles.end(), &v010.x, &v010.x + 3);
			_triangles.insert(_triangles.end(), &v110.x, &v110.x + 3);
			_triangles.insert(_triangles.end(), &v011.x, &v011.x + 3);
			_triangles.insert(_triangles.end(), &v110.x, &v110.x + 3);
			_triangles.insert(_triangles.end(), &v111.x, &v111.x + 3);
			_triangles.insert(_triangles.end(), &v011.x, &v011.x + 3);
			
			_normals.insert(_normals.end(), &vtop.x, &vtop.x + 3);
			_normals.insert(_normals.end(), &vtop.x, &vtop.x + 3);
			_normals.insert(_normals.end(), &vtop.x, &vtop.x + 3);
                        _normals.insert(_normals.end(), &vtop.x, &vtop.x + 3);
			_normals.insert(_normals.end(), &vtop.x, &vtop.x + 3);
                        _normals.insert(_normals.end(), &vtop.x, &vtop.x + 3);
			
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
                        _colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
                        _colors.insert(_colors.end(), &col.x, &col.x + 3);
		}
		if (!(_array[i] & bot))
		{
			_triangles.insert(_triangles.end(), &v000.x, &v000.x + 3);
			_triangles.insert(_triangles.end(), &v001.x, &v001.x + 3);
			_triangles.insert(_triangles.end(), &v100.x, &v100.x + 3);
			_triangles.insert(_triangles.end(), &v001.x, &v001.x + 3);
			_triangles.insert(_triangles.end(), &v101.x, &v101.x + 3);
			_triangles.insert(_triangles.end(), &v100.x, &v100.x + 3);
			
			_normals.insert(_normals.end(), &vbot.x, &vbot.x + 3);
			_normals.insert(_normals.end(), &vbot.x, &vbot.x + 3);
			_normals.insert(_normals.end(), &vbot.x, &vbot.x + 3);
                        _normals.insert(_normals.end(), &vbot.x, &vbot.x + 3);
			_normals.insert(_normals.end(), &vbot.x, &vbot.x + 3);
                        _normals.insert(_normals.end(), &vbot.x, &vbot.x + 3);
			
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
                        _colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
                        _colors.insert(_colors.end(), &col.x, &col.x + 3);
		}
		if (!(_array[i] & left))
		{
			_triangles.insert(_triangles.end(), &v010.x, &v010.x + 3);
			_triangles.insert(_triangles.end(), &v011.x, &v011.x + 3);
			_triangles.insert(_triangles.end(), &v000.x, &v000.x + 3);
			_triangles.insert(_triangles.end(), &v011.x, &v011.x + 3);
			_triangles.insert(_triangles.end(), &v001.x, &v001.x + 3);
			_triangles.insert(_triangles.end(), &v000.x, &v000.x + 3);
			
			_normals.insert(_normals.end(), &vleft.x, &vleft.x + 3);
			_normals.insert(_normals.end(), &vleft.x, &vleft.x + 3);
			_normals.insert(_normals.end(), &vleft.x, &vleft.x + 3);
                        _normals.insert(_normals.end(), &vleft.x, &vleft.x + 3);
			_normals.insert(_normals.end(), &vleft.x, &vleft.x + 3);
                        _normals.insert(_normals.end(), &vleft.x, &vleft.x + 3);
			
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
                        _colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
                        _colors.insert(_colors.end(), &col.x, &col.x + 3);
		}
		if (!(_array[i] & right))
		{
			_triangles.insert(_triangles.end(), &v110.x, &v110.x + 3);
			_triangles.insert(_triangles.end(), &v100.x, &v100.x + 3);
			_triangles.insert(_triangles.end(), &v111.x, &v111.x + 3);
			_triangles.insert(_triangles.end(), &v100.x, &v100.x + 3);
			_triangles.insert(_triangles.end(), &v101.x, &v101.x + 3);
			_triangles.insert(_triangles.end(), &v111.x, &v111.x + 3);
			
			_normals.insert(_normals.end(), &vright.x, &vright.x + 3);
			_normals.insert(_normals.end(), &vright.x, &vright.x + 3);
			_normals.insert(_normals.end(), &vright.x, &vright.x + 3);
                        _normals.insert(_normals.end(), &vright.x, &vright.x + 3);
			_normals.insert(_normals.end(), &vright.x, &vright.x + 3);
                        _normals.insert(_normals.end(), &vright.x, &vright.x + 3);
			
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
                        _colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
                        _colors.insert(_colors.end(), &col.x, &col.x + 3);
		}
		if (!(_array[i] & front))
		{
			_triangles.insert(_triangles.end(), &v000.x, &v000.x + 3);
			_triangles.insert(_triangles.end(), &v100.x, &v100.x + 3);
			_triangles.insert(_triangles.end(), &v010.x, &v010.x + 3);
			_triangles.insert(_triangles.end(), &v100.x, &v100.x + 3);
			_triangles.insert(_triangles.end(), &v110.x, &v110.x + 3);
			_triangles.insert(_triangles.end(), &v010.x, &v010.x + 3);
			
			_normals.insert(_normals.end(), &vfront.x, &vfront.x + 3);
			_normals.insert(_normals.end(), &vfront.x, &vfront.x + 3);
			_normals.insert(_normals.end(), &vfront.x, &vfront.x + 3);
                        _normals.insert(_normals.end(), &vfront.x, &vfront.x + 3);
			_normals.insert(_normals.end(), &vfront.x, &vfront.x + 3);
                        _normals.insert(_normals.end(), &vfront.x, &vfront.x + 3);
			
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
                        _colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
                        _colors.insert(_colors.end(), &col.x, &col.x + 3);
		}
		if (!(_array[i] & back))
		{
			_triangles.insert(_triangles.end(), &v001.x, &v001.x + 3);
			_triangles.insert(_triangles.end(), &v011.x, &v011.x + 3);
			_triangles.insert(_triangles.end(), &v101.x, &v101.x + 3);
			_triangles.insert(_triangles.end(), &v011.x, &v011.x + 3);
			_triangles.insert(_triangles.end(), &v111.x, &v111.x + 3);
			_triangles.insert(_triangles.end(), &v101.x, &v101.x + 3);
			
			_normals.insert(_normals.end(), &vback.x, &vback.x + 3);
			_normals.insert(_normals.end(), &vback.x, &vback.x + 3);
			_normals.insert(_normals.end(), &vback.x, &vback.x + 3);
                        _normals.insert(_normals.end(), &vback.x, &vback.x + 3);
			_normals.insert(_normals.end(), &vback.x, &vback.x + 3);
                        _normals.insert(_normals.end(), &vback.x, &vback.x + 3);
			
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
                        _colors.insert(_colors.end(), &col.x, &col.x + 3);
			_colors.insert(_colors.end(), &col.x, &col.x + 3);
                        _colors.insert(_colors.end(), &col.x, &col.x + 3);
		}
	}
}

void	VoxelChunk::print(void)
{
	for (int i = 0; i < _triangles.size(); i++)
	{
		if (i % 3 == 0)
			std::cout << std::endl;
		if (i % 9 == 0)
			std::cout << std::endl;
		std::cout << _triangles[i] << " ";
	}
}
