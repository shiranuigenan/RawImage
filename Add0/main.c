#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <malloc.h>

void main()
{
	int w = 43680, h = 24570;
	unsigned short* c = malloc(w << 1);
	if (c == NULL) return;

	for (int i = 0; i < w; i++)
		c[i] = i;

	FILE* r;
	r = fopen("1.raw", "wb");
	if (r == NULL) return;

	for (int j = 0; j < h; j++)
	{
		fwrite(c, 2, w, r);

		for (int i = 0; i < w; i++)
			c[i] += 2;;
	}
	fclose(r);
}
