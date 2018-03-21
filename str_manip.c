#include "shell.h"

int _strlen(char *str)
{
	int i = 0;

	while (*str != '\0')
	{
		i++;
		str++;
	}

	return (i);
}

char *_strdup(char *src)
{
	int len = _strlen(src);
	char *dest = NULL;
	char *ptr;

	dest = malloc(len + 1);
	if (dest == NULL)
		exit(EXIT_FAILURE);

	ptr = dest;

	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	*ptr = '\0';

	return (dest);
}

char *str_search(char *needle, char *haystack)
{
	char *h_ptr = haystack;
	char *n_ptr;

	while (*haystack != '\0')
	{
		n_ptr = needle;
		h_ptr = haystack;
		while (*n_ptr == *h_ptr && *h_ptr != '\0')
		{
			h_ptr++;
			n_ptr++;
		}
		if (*n_ptr == '\0')
			return (haystack);

		haystack++;
	}

	return (NULL);
}

void _strconcat(char **buffer, char *str1, char *str2)
{
	char *ptr = *buffer;

	while (*str1 != '\0')
	{
		*ptr = *str1;
		ptr++;
		str1++;
	}

	while (*str2 != '\0')
	{
		*ptr = *str2;
		ptr++;
		str2++;
	}

	*ptr = '\0';
}

int str_compare(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (FALSE);

		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (FALSE);

	return (TRUE);
}
