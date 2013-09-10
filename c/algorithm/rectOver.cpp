#include <stdio.h>

struct Rectangle
{
	int x, y;
	int height,width;
};

bool inRect(int value, int min, int max)
{
	return (value >= min) && (value <= max);
}

bool RectangleOverlap(const Rectangle& r1, const Rectangle& r2)
{
	bool xOver = inRect(r1.x, r2.x, r2.x + r2.width) || inRect(r2.x, r1.x, r1.x + r1.width);
	bool yOver = inRect(r1.y, r2.y, r2.y + r2.height) || inRect(r2.y, r1.y, r1.y + r1.height);

	return (xOver && xOver);
}

int main()
{
	Rectangle  a = {0, 0, 3, 4};
	Rectangle  b = {1, 1, 3, 3};

	if (RectangleOverlap(a, b))
	{
		printf("a and b touch or overload\n");
	}
	else
	{
		printf("a and b not touch\n");
	}
	return  0;
}
