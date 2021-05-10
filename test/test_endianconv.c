#include "utils/endianconv.h"

int main()
{
	char buf[32];


	sprintf(buf,"ciaoroma");
	memrev16(buf);
	printf("%s\n", buf);

	sprintf(buf,"ciaoroma");
	memrev32(buf);
	printf("%s\n", buf);

	sprintf(buf,"ciaoroma");
	memrev64(buf);
	printf("%s\n", buf);

	return 0;
}
