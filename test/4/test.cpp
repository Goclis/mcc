int fib(int num) 
{
	if (num < 0) {
		return 0;
	} else if (0 == num || 1 == num) {
		return 1;
	} else {
		return fib(num - 1) + fib(num - 2);
	}
}

void main(void) 
{
	int i;
	int j;

	i = -1;
	while (1) {
		j = $0xFF18;
		
		if (j != i) {
			i = j;
			$0xFF00 = fib(i);
		}
	}
}