#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

//parsing not done

int solve(char *s, int *i)
{
	int nums[100];
	int count = 0;
	int n = 0;
	char op = '+';

	while (s[*i] && s[*i] != ')')
	{
		if (s[*i] == '(')
		{
			(*i)++;
			n = solve(s, i);
		}
		else if (isdigit(s[*i]))
			n = s[*i] - '0';

		if (op == '+')
			nums[count++] = n;
		else if (op == '*')
			nums[count - 1] *= n;

		op = s[*i];
		if (s[*i] != '\0' && s[*i] != ')')
			(*i)++;
	}
	if (s[*i] == ')')
		(*i)++;
		
	int k = 0;
	int res = 0;
	while (k < count)
		res += nums[k++];
	return (res);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);

	if (parse(argv[1]))
		return (1);
	int i = 0;
	printf("%d\n", solve(argv[1], &i));
	return (0);
}