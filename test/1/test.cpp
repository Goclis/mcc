// 本测试用例定义多参数的方法，测试多参方法调用

// return arr[i] + arr[j]
int multiparam(int arr[100], int i, int j)
{
	return arr[i] + arr[j];
}

int i; // 全局变量

void main(void)
{
	int j;
	int arr[128];

	// 用于迭代设置初值	
	int t;
	t = 0;
	while (t < 128) {
		arr[t] = t;
		t = t + 1;
	}

	while (1) {
		i = $0xFF10 & 127; // switch
		j = $0xFF18 & 127; // keyboard

		$0xFF00 = multiparam(arr, i, j);
	}
}