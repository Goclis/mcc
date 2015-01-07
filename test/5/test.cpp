int main(void)
{
	int i;
	int arr[128];

	int t;
	t = 0;
	while (t < 128) {
		arr[t] = t;
		t = t + 1;
	}

	while (1) {
		i = $0xFF10 & 127;
		$0xFF00 = arr[i];
	}

	return 0;
}
