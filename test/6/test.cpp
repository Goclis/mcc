// 测试逻辑符号的正确性

int main(void)
{
	int i;
	int a;
	int b;

	while (1) {
		i = $0xFF10;

		a = i & 1; // 最后一位
		b = i & 2; // 倒数第二

		// ba
		if (0 == b && 0 == a) {
			$0xFF00 = i; // 00时触发
			$0xFF08 = i;
		} else if (a && b) {
			// $0xFF00 = i - 1; // 10时触发
			$0xFF08 = i + 3;
		} else if (0 == b || 1 == a) {
			$0xFF00 = i * 2; // 0X或X1时
			$0xFF08 = i * 2;
		} 
	}
}