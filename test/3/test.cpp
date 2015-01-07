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

	while (1) {
		i = $0xFF18;
		
		$0xFF00 = fib(i);
	}
}