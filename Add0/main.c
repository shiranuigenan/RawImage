#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <malloc.h>

void main()
{
	int n = 256;//max 2048
	int w = 1920, h = 1080;
	int wn = w * n, hn = h * n;
	unsigned long long* b = malloc(w << 3);//128kb
	unsigned short* c = malloc(w << 1);//32kb

	unsigned long long max = 0;
	for (int j = hn - n; j < hn; j++)
		for (int i = wn - n; i < wn; i++)
			max += i * 9 + j * 16;

	max = (max >> 16) + 1;

	FILE* r;
	r = fopen("256.raw", "wb");
	if (r == NULL) return;

	int progress = hn / 10;
	for (int j = 0; j < hn; j++)
	{
		if (j % n == 0)
			memset(b, 0, w << 3);

		for (int i = 0; i < wn; i++)
			b[i / n] += i * 9 + j * 16;

		if (j % n == n - 1)
		{
			for (int i = 0; i < w; i++)
				c[i] = b[i] / max;

			fwrite(c, 2, w, r);

		}

		if (j % progress == 0)
			printf("%d ", j / progress);
	}
	fclose(r);
}
