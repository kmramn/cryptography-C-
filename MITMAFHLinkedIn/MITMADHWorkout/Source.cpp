// https://math.stackexchange.com/questions/124408/finding-a-primitive-root-of-a-prime-number
// https://stackoverflow.com/questions/38554083/how-can-i-use-a-c-unordered-set-for-a-custom-class
#include <Windows.h>
#include <winerror.h>

#include <stdio.h>

#include <iostream>
using namespace std;

#include <tchar.h>
#include <strsafe.h>

#pragma warning(disable : 4146)
#include <gmp.h>
#pragma comment(lib, "libgmp.a")
#pragma comment(lib, "libmpz.a")
#pragma comment(lib, "libmpf.a")
#pragma comment(lib, "libmpq.a")
#pragma comment(lib, "libmpn.a")

#pragma comment(lib, "libgcc.a")

// https://www.browserling.com/tools/random-bin
// https://www.binaryhexconverter.com/binary-to-hex-converter
void main()
{
    // Random number
    mpz_t r;
    mpz_init(r);
    //mpz_set_str(r, "84F5733EECB08886845FA5F2B39F32098AE6BA6C9FF8C7487EE64E14FE3AEDACC8EF4DC3EEDC9D37FBF973785A2B2965D374D22AC0787BE95058815071E4DBCAF04C71EB1ABBA912F2C7BD4B5716465FE6E603849269E5B5F8D9744090843E93EFA72EBAC2B08F58BF5DF7B3ACB01916C03AD017417C0D5D3A07920B65A204E6E4729A2E068E161489521B868EF5B304FA5DD3EA4A55914C54CF6C5084F9B005DABB6E3779F4BDE1CD234E4FF20794B20B1A3ECDD124AE2F36C33FBD9C0A1AB031DB436F24AD095B7AFE0B0BB3C0A9C7C54E7144A", 16);
	mpz_set_str(r, "E7E94DB309DC10540A75E38BE90C32141ECB958802AE172E09DE549156E028F443EA6F788074E1FEC332703352B376170006F6EF4F4A2FB1D0D943D0BE9A", 16);
	// Or the next prime is 185336037175480251559748847730722000460760653517502598879566856821999692776462322609111579665522032123421931543674620188754864831373380677893731958489(10)
	// or e7e94db309dc10540a75e38be90c32141ecb958802ae172e09de549156e028f443ea6f788074e1fec332703352b376170006f6ef4f4a2fb1d0d943d0bed9(16)

	// Prime p
    mpz_t p;
	mpz_init_set_str(p, "e7e94db309dc10540a75e38be90c32141ecb958802ae172e09de549156e028f443ea6f788074e1fec332703352b376170006f6ef4f4a2fb1d0d943d0bed9", 16);
	//mpz_init_set_str(p, "1589946103", 10);
	//mpz_init(p);
    //mpz_nextprime(p, r);
    char chP[4096];
    SecureZeroMemory(chP, sizeof(chP));
    mpz_get_str(chP, 16, p);
    printf("1. %s\n", chP);

    // Find genaator g
    mpz_t g;
	mpz_init_set_str(g, "2F26760E85950864D1F24421F2AB599A2DE6A4379B86AD5972CA348938B2B25ED6ABF80D03E9BC7C9F54CFDC670B15EC33DDA88CBFFC53F725D779247813", 16);
	//mpz_init_set_str(g, "1154947122", 10);
	SecureZeroMemory(chP, sizeof(chP));
    mpz_get_str(chP, 16, g);
    printf("2. %s\n", chP);
	 
    // Choose x in the range 1 < x < 2^56
    // 1 < x < 72057594037927940
    unsigned long long xdl = 0;
    xdl = 54043195528445955; // ?
    mpz_t x;
	mpz_init_set_str(x, "59810694624132513", 10); // 2^ 56
	//mpz_init_set_str(x, "54043195528445955", 10); // 2 ^ 56
	//mpz_init_set_str(x, "1649267441664", 10);
	//mpz_init_set_str(x, "1073741824", 10); // 2 ^ 32
	//mpz_init_set_str(x, "10796093022208", 10); // ((2 ^ 44) / 2) + 10
	//mpz_init_set_str(x, "1572864", 10); //2 ^ 20
	//mpz_init_set_str(x, "49152", 10); //2 ^ 16
	//mpz_init_set_str(x, "12288", 10); //2 ^ 16
	SecureZeroMemory(chP, sizeof(chP));
    mpz_get_str(chP, 10, x);
    printf("3. %s\n", chP);

    // Calculate h
    mpz_t h;
    mpz_init(h);
    //mpz_powm_ui(h, g, xdl, p);
    mpz_powm(h, g, x, p);
    SecureZeroMemory(chP, sizeof(chP));
    mpz_get_str(chP, 10, h);
    printf("4. %s\n", chP);

    mpz_clear(g);
    mpz_clear(p);
    mpz_clear(r);
}

/*// C++ program to find primitive root of a
// given number n
#include <Windows.h>
#include <winerror.h>

#include <stdio.h>

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
//#include <bits/stdc++.h>
using namespace std;

#include <tchar.h>
#include <strsafe.h>

// Returns true if n is prime
bool isPrime(int n)
{
	// Corner cases
	if (n <= 1) return false;
	if (n <= 3) return true;

	// This is checked so that we can skip
	// middle five numbers in below loop
	if (n % 2 == 0 || n % 3 == 0) return false;

	for (int i = 5; i * i <= n; i = i + 6)
		if (n % i == 0 || n % (i + 2) == 0)
			return false;

	return true;
}

// Iterative Function to calculate (x^n)%p in
// O(logy)
int power(int x, unsigned int y, int p)
{
	int res = 1;	 // Initialize result

	x = x % p; // Update x if it is more than or
	// equal to p

	while (y > 0)
	{
		// If y is odd, multiply x with result
		if (y & 1)
			res = (res * x) % p;

		// y must be even now
		y = y >> 1; // y = y/2
		x = (x * x) % p;
	}
	return res;
}

// Utility function to store prime factors of a number
void findPrimefactors(unordered_set<int>& s, int n)
{
	// Print the number of 2s that divide n
	while (n % 2 == 0)
	{
		s.insert(2);
		n = n / 2;
	}

	// n must be odd at this point. So we can skip
	// one element (Note i = i +2)
	for (int i = 3; i <= sqrt(n); i = i + 2)
	{
		// While i divides n, print i and divide n
		while (n % i == 0)
		{
			s.insert(i);
			n = n / i;
		}
	}

	// This condition is to handle the case when
	// n is a prime number greater than 2
	if (n > 2)
		s.insert(n);
}

// Function to find smallest primitive root of n
int findPrimitive(int n, vector<int>& vecPriRoot)
{
	unordered_set<int> s;

	// Check if n is prime or not
	if (isPrime(n) == false)
		return -1;

	// Find value of Euler Totient function of n
	// Since n is a prime number, the value of Euler
	// Totient function is n-1 as there are n-1
	// relatively prime numbers.
	int phi = n - 1;

	// Find prime factors of phi and store in a set
	findPrimefactors(s, phi);

	// Check for every number from 2 to phi
	//for (int r = 2; r <= phi; r++)
	for (int r = phi; r >= 2; r--)
	{
		// Iterate through all prime factors of phi.
		// and check if we found a power with value 1
		bool flag = false;
		for (auto it = s.begin(); it != s.end(); it++)
		{

			// Check if r^((phi)/primefactors) mod n
			// is 1 or not
			if (power(r, phi / (*it), n) == 1)
			{
				flag = true;
				break;
			}
		}

		// If there was no power with value 1.
		if (flag == false)
		{
			//return r;
			vecPriRoot.push_back(r);
		}
	}

	// If no primitive root found
	return -1;
}

// Driver code
int main()
{
	int n = 761;
	//cout << " Gratest primitive root of " << n << " is " << findPrimitive(n);
	vector<int> vecPriRoot;
	findPrimitive(n, vecPriRoot);
	sort(vecPriRoot.begin(), vecPriRoot.end());
	for (auto n : vecPriRoot)
		wprintf(L"%d, ", n);
	return 0;
}
*/
// C++ program to find a prime factor of composite using
//   Pollard's Rho algorithm
/*#include <Windows.h>
#include <winerror.h>

#include <stdio.h>

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
//#include <bits/stdc++.h>
#include <numeric>
using namespace std;

#include <tchar.h>
#include <strsafe.h>

// Function to calculate (base^exponent)%modulus
long long int modular_pow(long long int base, int exponent,
	long long int modulus)
{
	// initialize result
	long long int result = 1;

	while (exponent > 0)
	{
		// if y is odd, multiply base with result
		if (exponent & 1)
			result = (result * base) % modulus;

		// exponent = exponent/2
		exponent = exponent >> 1;

		// base = base * base
		base = (base * base) % modulus;
	}
	return result;
}

int gcd(int a, int b) {
	while (b != 0) {
		int t = b;
		b = a % b;
		a = t;
	}
	return a;
}

// method to return prime divisor for n
long long int PollardRho(long long int n)
{
	// initialize random seed
	srand(time(NULL));

	// no prime divisor for 1
	if (n == 1) return n;

	// even number means one of the divisors is 2
	if (n % 2 == 0) return 2;

	// we will pick from the range [2, N)
	long long int x = (rand() % (n - 2)) + 2;
	long long int y = x;

	// the constant in f(x).
	// * Algorithm can be re-run with a different c
	// * if it throws failure for a composite.
	long long int c = (rand() % (n - 1)) + 1;

	// Initialize candidate divisor (or result)
	long long int d = 1;

	// until the prime factor isn't obtained.
	   If n is prime, return n
	while (d == 1)
	{
		// Tortoise Move: x(i+1) = f(x(i))
		x = (modular_pow(x, 2, n) + c + n) % n;

		// Hare Move: y(i+1) = f(f(y(i)))
		y = (modular_pow(y, 2, n) + c + n) % n;
		y = (modular_pow(y, 2, n) + c + n) % n;

		// check gcd of |x-y| and n 
		//d = __gcd(abs(x - y), n);
		d = gcd(abs(x - y), n);

		// retry if the algorithm fails to find prime factor
		// * with chosen x and c
		if (d == n) return PollardRho(n);
	}

	return d;
}

// driver function
int main()
{
	//unsigned long long int n = 10967535067;
	unsigned long long int n = 271;
	printf("One of the divisors for %lld is %lld.",
		n, PollardRho(n));
	return 0;
}
*/

/*// C++ program to find primitive root of a
// given number n
#include <Windows.h>
#include <winerror.h>

#include <stdio.h>

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
//#include <bits/stdc++.h>
using namespace std;

#include <tchar.h>
#include <strsafe.h>

// Iterative Function to calculate (x^n)%p in
// O(logy)
int power(int x, unsigned int y, int p)
{
	int res = 1;	 // Initialize result

	x = x % p; // Update x if it is more than or
	// equal to p

	while (y > 0)
	{
		// If y is odd, multiply x with result
		if (y & 1)
			res = (res * x) % p;

		// y must be even now
		y = y >> 1; // y = y/2
		x = (x * x) % p;
	}
	return res;
}

// This function is called for all k trials. It returns
// false if n is composite and returns true if n is
// probably prime.
// d is an odd number such that  d*2 = n-1
// for some r >= 1
bool miillerTest(int d, int n)
{
	// Pick a random number in [2..n-2]
	// Corner cases make sure that n > 4
	int a = 2 + rand() % (n - 4);

	// Compute a^d % n
	int x = power(a, d, n);

	if (x == 1 || x == n - 1)
		return true;

	// Keep squaring x while one of the following doesn't
	// happen
	// (i)   d does not reach n-1
	// (ii)  (x^2) % n is not 1
	// (iii) (x^2) % n is not n-1
	while (d != n - 1)
	{
		x = (x * x) % n;
		d *= 2;

		if (x == 1)      return false;
		if (x == n - 1)    return true;
	}

	// Return composite
	return false;
}

// It returns false if n is composite and returns true if n
// is probably prime.  k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
bool isPrime(int n, int k)
{
	// Corner cases
	if (n <= 1 || n == 4)  return false;
	if (n <= 3) return true;

	// Find r such that n = 2^d * r + 1 for some r >= 1
	int d = n - 1;
	while (d % 2 == 0)
		d /= 2;

	// Iterate given number of 'k' times
	for (int i = 0; i < k; i++)
		if (!miillerTest(d, n))
			return false;

	return true;
}

// Function to calculate (base^exponent)%modulus
long long int modular_pow(long long int base, int exponent,
	long long int modulus)
{
	// initialize result
	long long int result = 1;

	while (exponent > 0)
	{
		// if y is odd, multiply base with result
		if (exponent & 1)
			result = (result * base) % modulus;

		// exponent = exponent/2
		exponent = exponent >> 1;

		// base = base * base
		base = (base * base) % modulus;
	}
	return result;
}

int gcd(long long int a, long long int b) {
	while (b != 0) {
		int t = b;
		b = a % b;
		a = t;
	}
	return a;
}

// method to return prime divisor for n
long long int PollardRho(unordered_set<int>& s, long long int n)
{
	// initialize random seed
	srand(time(NULL));

	// no prime divisor for 1
	if (n == 1) return n;

	// even number means one of the divisors is 2
	if (n % 2 == 0) return 2;

	// we will pick from the range [2, N)
	long long int x = (rand() % (n - 2)) + 2;
	long long int y = x;

	// the constant in f(x).
	// * Algorithm can be re-run with a different c
	// * if it throws failure for a composite.
	long long int c = (rand() % (n - 1)) + 1;

	// Initialize candidate divisor (or result)
	long long int d = 1;

	// until the prime factor isn't obtained.
	// If n is prime, return n
	while (d == 1)
	{
		// Tortoise Move: x(i+1) = f(x(i))
		x = (modular_pow(x, 2, n) + c + n) % n;

		// Hare Move: y(i+1) = f(f(y(i)))
		y = (modular_pow(y, 2, n) + c + n) % n;
		y = (modular_pow(y, 2, n) + c + n) % n;

		// check gcd of |x-y| and n
		//d = __gcd(abs(x - y), n);
		d = gcd(abs(x - y), n);

		// retry if the algorithm fails to find prime factor
		// * with chosen x and c
		if (d == n) return PollardRho(s, n);
	}

	return d;
}

// Function to find smallest primitive root of n
int findPrimitive(int n, vector<int>& vecPriRoot)
{
	unordered_set<int> s;

	// Check if n is prime or not
	if (isPrime(n, 10) == false)
		return -1;

	// Find value of Euler Totient function of n
	// Since n is a prime number, the value of Euler
	// Totient function is n-1 as there are n-1
	// relatively prime numbers.
	int phi = n - 1;

	//unsigned long long int n = 10967535067;
	//unsigned long long int n = 271;
	//printf("One of the divisors for %lld is %lld.", n, PollardRho(n));
	while (true)
	{
		long long int d = PollardRho(s, phi);
		s.insert(d);
		phi /= d;
		if (isPrime(phi, 10)) { s.insert(phi); break; }
	}

	phi = n - 1;

	// Check for every number from 2 to phi
	for (int r = 2; r <= phi; r++)
	//for (int r = phi; r >= 2; r--)
	{
		// Iterate through all prime factors of phi.
		// and check if we found a power with value 1
		bool flag = false;
		for (auto it = s.begin(); it != s.end(); it++)
		{

			// Check if r^((phi)/primefactors) mod n
			// is 1 or not
			if (power(r, phi / (*it), n) == 1)
			{
				flag = true;
				break;
			}
		}

		// If there was no power with value 1.
		if (flag == false)
		{
			vecPriRoot.push_back(r);
			return r;
		}
	}

	// If no primitive root found
	return -1;
}

void findNPrimitive(int nCount, int p, vector<int>& vecPriRoot)
{
	int nMin = vecPriRoot[0];
	int nCoPrime = 2;
	while (nCount != 0)
	{
		if (gcd(nCoPrime++, p - 1) == 1)
		{
			vecPriRoot.push_back(power(nMin, nCoPrime, p));
			nCount--;
		}
	}
}

// Driver code
int main()
{
	int n = 761;
	//cout << " Gratest primitive root of " << n << " is " << findPrimitive(n);
	vector<int> vecPriRoot;
	findPrimitive(n, vecPriRoot);
	findNPrimitive(10, n, vecPriRoot);
	sort(vecPriRoot.begin(), vecPriRoot.end());
	for (auto n : vecPriRoot)
		wprintf(L"%d, ", n);

	return 0;
}*/
