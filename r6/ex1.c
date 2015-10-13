#include <stdio.h>
#include <stdlib.h>

char *
get_str1()
{
	char str[20] = "hello world";
	return str;
}

char *
get_str2()
{
	static char str[20] = "hello world";
	return str;
}

char *
get_str3()
{
	char *str = "hello world";
	return str;
}

char *
get_str4()
{
	char *dst = (char *)malloc(sizeof(100));
	char *src = "hello world";
	for (int i = 0; i < 12; i++) {
		dst[i] = src[i];
	}
	return dst;
}

void main() {

	char *s1, *s2, *s3, *s4;
	s1 = get_str1();
	s2 = get_str2();
	s3 = get_str3();
	s4 = get_str4();

	printf("s1=%s s2=%s s3=%s s4=%s\n", s1, s2, s3, s4);

}
