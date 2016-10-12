#include "compress.h"
#include "descompress.h"

void main()
{
	int desejo;

	scanf("%d", &desejo);

	if(desejo)
	{
		start_compress();
	}

	else
	{
		start_descompress();
	}
}
