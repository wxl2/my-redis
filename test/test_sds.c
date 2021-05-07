#include "base/sds.h"
#include "base/testhelp.h"
#include <stdio.h>
#include "limits.h"

int main()
{
	sds mm = sdsnew("hello");
	size_t len = sdslen(mm);
	size_t alloc = sdsalloc(mm);
	sdsfree(mm);

	sds x = sdsnew("foo");
	test_cond("Create a string and obtain the length",sdslen(x) == 3 && memcmp(x,"foo\0",4) == 0);
	sdsfree(x);

	x = sdsnewlen("foo",2);
	test_cond("Create a string with specified length", sdslen(x) == 2 && memcmp(x,"fo\0",3) ==0);

	x = sdscat(x,"bar");
	test_cond("Strings concatenation",sdslen(x) == 5 && memcmp(x,"fobar\0",6) == 0);

	x = sdscpy(x,"a");
	test_cond("sdscpy() against an originally longer string",sdslen(x) == 1 && memcmp(x,"a\0",2) == 0);

	x = sdscpy(x,"xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk");
	test_cond("sdscpy() against an originally shorter string",
			sdslen(x) == 33 &&
			memcmp(x,"xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk\0",33) == 0);

	sdsfree(x);

	x =  sdscatprintf(sdsempty(),"%d",123);
	test_cond("sdscatprintf() semms working in the base case",sdslen(x) == 3 && memcmp(x,"123\0",4) == 0);
	sdsfree(x);

	x =  sdsnew("--");
	x = sdscatfmt(x,"%u,%U--",UINT_MAX,ULLONG_MAX);
	test_cond("sdscatfmt() semms working with unsigned numbers",sdslen(x) == 35 && memcmp(x,"--4294967295,18446744073709551615--",35) == 0);
	sdsfree(x);

	x = sdsnew(" x ");
	sdstrim(x," x");
	test_cond("sdstrim() works when all chars match",sdslen(x) == 0);
	sdsfree(x);

	x = sdsnew(" x ");
	sdstrim(x," ");
	test_cond("sdstrim() works when a single char remains",sdslen(x) == 1 && memcmp(x,"x\0",2) == 0);
	sdsfree(x);

	x = sdsnew("xxciaoyyy");
	sdstrim(x,"xy");
	test_cond("sdstrim() correctly trims characters",sdslen(x) == 4 && memcmp(x,"ciao\0",5) == 0);

	sds y = sdsdup(x);
	sdsrange(y,1,1);
	test_cond("sdsrange(...,1,1)",sdslen(y) == 1 && memcmp(y,"i\0",2) == 0);
	sdsfree(y);

	y = sdsdup(x);
	sdsrange(y,1,-1);
	test_cond("sdsrange(...,1,-1)",sdslen(y) == 3 && memcmp(y,"iao\0",4) == 0);
	sdsfree(y);


	y = sdsdup(x);
	sdsrange(y,-2,-1);
	test_cond("sdsrange(...,-2,-1)",sdslen(y) == 2 && memcmp(y,"ao\0",3) == 0);
	sdsfree(y);

	y = sdsdup(x);
	sdsrange(y,2,1);
	test_cond("sdsrange(...,2,1)",sdslen(y) == 0 && memcmp(y,"\0",1) == 0);
	sdsfree(y);


	y = sdsdup(x);
	sdsrange(y,1,100);
	test_cond("sdsrange(...,1,100)",sdslen(y) == 3 && memcmp(y,"iao\0",4) == 0);
	sdsfree(y);


	y = sdsdup(x);
	sdsrange(y,100,100);
	test_cond("sdsrange(...,100,100)",sdslen(y) == 0 && memcmp(y,"\0",1) == 0);
	sdsfree(y);
	sdsfree(x);

	x = sdsnew("foo");
	y = sdsnew("foa");
	test_cond("sdscmp(foo,foa)",sdscmp(x,y) > 0);
	sdsfree(y);
	sdsfree(x);


	x = sdsnew("bar");
	y = sdsnew("bar");
	test_cond("sdscmp(bar,bar)",sdscmp(x,y) == 0);
	sdsfree(y);
	sdsfree(x);


	x = sdsnew("aar");
	y = sdsnew("bar");
	test_cond("sdscmp(aar,bar)",sdscmp(x,y) < 0);
	sdsfree(y);
	sdsfree(x);

	x = sdsnewlen("\a\n\0foo\r",7);
	y = sdscatrepr(sdsempty(),x,sdslen(x));
	test_cond("sdscatrepr(...data...)",memcmp(y,"\"\\a\\n\\x00foo\\r\"",15) == 0);

	{
		unsigned int oldfree;
		char *p;
		int step = 10, j, i;

		sdsfree(x);
		sdsfree(y);
		x = sdsnew("0");
		test_cond("sdsnew() free/len buffers", sdslen(x) == 1 && sdsavail(x) == 0);

		/* Run the test a few times in order to hit the first two
		 *              * SDS header types. */
		for (i = 0; i < 10; i++) {
			int oldlen = sdslen(x);
			x = sdsMakeRoomFor(x,step);
			int type = x[-1]&SDS_TYPE_MASK;

			test_cond("sdsMakeRoomFor() len", sdslen(x) == oldlen);
			if (type != SDS_TYPE_5) {
				test_cond("sdsMakeRoomFor() free", sdsavail(x) >= step);
				oldfree = sdsavail(x);
			}
			p = x+oldlen;
			for (j = 0; j < step; j++) {
				p[j] = 'A'+j;
			}
			sdsIncrLen(x,step);
		}
		test_cond("sdsMakeRoomFor() content",
				memcmp("0ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJ",x,101) == 0);
		test_cond("sdsMakeRoomFor() final length",sdslen(x)==101);

		sdsfree(x);
	}
	test_report();
return 0;
}
