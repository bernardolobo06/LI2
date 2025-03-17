int fact(int n) { 
	int res = 1;
	while (n > 0) {
		res *= n;
		n--;
	}
	return res;
}

double pot(double x, int n) {
 	double res = 1;
	while (n > 0) {
		res *= x;
		n--;
	}
 	return res;
}

// \sum_{n=0}^{\infty} \frac{(2n)!}{4^n(n!)^2(2n+1)} x^{2n+1} 
double serie(double x, int n) {
	double res = 0;
	while (n >= 0) {
		double num = fact(2 * n);
		double den = (pot(4, n)) * (pot(fact(n), 2)) * ((2 * n) + 1);
		double mul = pot(x, (2 * n) + 1);
		
		res += (num / den) * mul;
		n--;	
	}
	return res;
}
