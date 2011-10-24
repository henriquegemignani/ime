class Lazy {
	public static void print(int number) {
		System.out.println("Nah...");
	}
	public static void main(String[] args) {
		int z = 1 / 0;
		print(z);
		return 0;
	}
}