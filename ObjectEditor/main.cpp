
#include <iostream>
#include <string>

int	main(void)
{
	int arr[10][10][10];
	
	for (int ix = 0; ix < 10; ix++)
	{
		for (int iy = 0; iy < 10; iy++)
		{
			for (int iz = 0; iz < 10; iz++)
			{
				arr[ix][iy][iz] = 0;
				
				//write code here:
				
				float x = ix - 4.5;
				float y = iy - 4.5;
				float z = iz - 4.5;
				
				if (x * x + y * y + z * z <= 20)
				{
					arr[ix][iy][iz] = 0xff0077;
				}
			}
		}
	}


	for (int ix = 0; ix < 10; ix++)
	{
		for (int iy = 0; iy < 10; iy++)
		{
			for (int iz = 0; iz < 10; iz++)
			{
				std::cout << arr[ix][iy][iz] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}	
}
