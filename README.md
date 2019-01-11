# X0-Compiler
This is a compiler written by c++ for x0-language which is a kind of programming language like c. You can also use its GUI in [X0-Compiler-GUI](https://github.com/GooCoder/X0-Compiler-GUI) .

## Installation

Clone the repository to your computer and open the `X0-Compiler.sln` with **visual studio 2017**.

## Grammar

The grammar of x0-language is defined in [x0-grammar.ebnf](https://github.com/GooCoder/X0-Compiler/blob/master/X0-Compiler/x0-grammar/x0-grammar.ebnf) which is described with EBNF. You can also see the syntax diagram in [x0-grammar.pdf](https://github.com/GooCoder/X0-Compiler/blob/master/X0-Compiler/x0-grammar/x0-grammar.pdf).

## Supports

|                     Module                     | Status |
| :--------------------------------------------: | :----: |
|                    if-else                     |   Y    |
|                      for                       |   Y    |
|                  switch-case                   |   Y    |
|                    do-while                    |   Y    |
|                  repeat-until                  |   Y    |
|                     while                      |   Y    |
|             break, continue, exit              |   Y    |
|       data type: int, double, char, bool       |   Y    |
|                    constant                    |   Y    |
|                 all operators                  |   Y    |
|               n-dimension array                |   Y    |
| function call with return value and parameters |   Y    |
|      function call with address parameter      |   N    |

## Examples

Calculate the GCD(greatest common divisor) between two numbers.

```c++
int GCD(int x, int y)
{
	if (x % y == 0)
	{
		return y;
	}
	else
	{
		return GCD(y, x % y);
	}
}

main()
{
	int a;
	int b;
	read a;
	read b;
	write GCD(a, b);
}
```

Calculate 1 + 2 + ... + 10.

```c++
main()
{
	int i;
	int sum;
	sum = 0;
	for (i = 1; i <= 10; i++)
	{
		sum = sum + i;
	}
	write sum;
}
```

Find primes between 1 and n with sieve method.

```c++
void FindPrime(int n)
{
	int isPrime[100];
	int i;
	int j;
	for (i = 2; i <= n; i++)
	{
		isPrime[i] = 0;
	}
	for (i = 2; i <= n; ++i)
	{
  		if (!isPrime[i])
  		{
			write i;
  		}
  		for (j = 2 * i; j <= n; j = j + i)
  		{
			isPrime[j] = 1;
  		}
	}
}

main()
{
	int n;
	read n;
	FindPrime(n);
}
```
## Help

If you have some problems can't be solved, please contact the author by email: **zjli1997@qq.com**.
