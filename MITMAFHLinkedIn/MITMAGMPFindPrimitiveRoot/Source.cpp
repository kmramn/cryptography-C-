#include <Windows.h>
#include <winerror.h>

#include <stdio.h>

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <chrono>
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
#pragma comment(lib, "libprintf.a")
#include <gmpxx.h>
#pragma comment(lib, "libcxx.a")

#pragma comment(lib, "libgcc.a")

#pragma warning(disable : 4700)

class PRTimer
{
	chrono::steady_clock sc;
	chrono::steady_clock::time_point start;
	chrono::steady_clock::time_point end;
public:
	mpz_class n;
	PRTimer()
	{
		start = sc.now();
	}
	~PRTimer()
	{
		end = sc.now();
		auto time_span = static_cast<chrono::duration<double>>(end - start);
		cout << "Prime Factor for p-1 is n: " << n.get_str() << " Operation took: " << time_span.count() << " seconds !!!" << endl;
	}
};

// method to return prime divisor for n
void PollardRhoWithSmallRand(mpz_class& p, mpz_class& d)
{
	// initialize random seed
	srand(time(NULL));
	//gmp_randstate_t rs;
	//gmp_randinit_mt(rs);

	// no prime divisor for 1
	if (p.get_str(10) == "1") return;

	// even number means one of the divisors is 2
	//if (p % 2 == 0) return 2;
	bool bIsEven = false;
	mpz_class r;
	//r = (p % 2);
	while ((r = (p % 2)).get_str(10) == "0")
	{
		p /= 2;
		bIsEven = true;
	}
	if (bIsEven) { d = 2; return; }

	// we will pick from the range [2, p)
	//long long int x = (rand() % (p - 2)) + 2;
	//long long int y = x;
	mpz_class intMax(0xffffffff);
	mpz_class x;
	mpz_class y;
	if (p < intMax)
		x = (rand() % (p - 2)) + 2;
	else
		x = (rand() + 2);
	y = (x);

	// the constant in f(x).
	// * Algorithm can be re-run with a different c
	// * if it throws failure for a composite.
	//long long int c = (rand() % (p - 1)) + 1;
	mpz_class c;
	if (p < intMax)
		c = (rand() % (p - 1)) + 1;
	else
		c = (rand() + 1);

	// Initialize candidate divisor (or result)
	//long long int d = 1;
	d = 1;

	// until the prime factor isn't obtained.
	// If n is prime, return n
	//while (d == 1)
	mpz_class xya;
	while(d == 1)
	{
		// Tortoise Move: x(i+1) = f(x(i))
		//x = (modular_pow(x, 2, p) + c + p) % p;
		x = (((x * x) % p) + c + p) % p;
		//cout << "x:" << x.get_str() << endl;

		// Hare Move: y(i+1) = f(f(y(i)))
		//y = (modular_pow(y, 2, p) + c + p) % p;
		y = (((y * y) % p) + c + p) % p;
		//y = (modular_pow(y, 2, p) + c + p) % p;
		y = (((y * y) % p) + c + p) % p;
		//cout << "y:" << y.get_str() << endl;

		// check gcd of |x-y| and n
		//d = __gcd(abs(x - y), n);
		//d = gcd(abs(x - y), p);
		xya = abs(x - y);
		//cout << "xya:" << xya.get_str() << endl;
		d = gcd(xya, p);
		//cout << "*****d*****" << d.get_str() << endl;

		// retry if the algorithm fails to find prime factor
		// * with chosen x and c
		if (d == p) { PollardRhoWithSmallRand(p, d); return; }
	}

	p = p / d;
	return;
}

// method to return prime divisor for n
// https://stackoverflow.com/questions/30942413/c-gmp-generating-random-number
void makeprime()
{
	// *********************** VARIABLE DECLARATION *********************** //
	// initilize the variables as gmp class instances
	mpz_t l1, rand1;
	mpz_init(l1);
	mpz_init(rand1);
	unsigned long seed = 0;;
	// perform inits to create variable pointers with 0 value
	//mpz_init(rand);

	// calculate the random number floor
	//mpz_ui_pow_ui(l1, 2, 199);
	mpz_ui_pow_ui(l1, 2, (time(NULL) % 199));
	mpz_class prbu(l1);
	cout << "prbu1 " << prbu.get_str() << endl;

	// initilze the state object for the random generator functions
	gmp_randstate_t rstate;
	// initialize state for a Mersenne Twister algorithm. This algorithm is fast and has good randomness properties.
	gmp_randinit_mt(rstate);

	// create the generator seed for the random engine to reference 
	gmp_randseed_ui(rstate, seed);

	/*
	Function:
	int mpz_probab_prime_p (const mpz_t n, int reps)

	Determine whether n is prime. Return 2 if n is definitely prime, return 1 if n is probably prime (without being certain),
	or return 0 if n is definitely composite.
	*/
	do {
		// return a uniformly distributed random number in the range 0 to n-1, inclusive.
		mpz_urandomb(rand1, rstate, 310);
		//mpz_t sol;
		//mpz_init_set_ui(sol, 310);
		//mpz_urandomm(rand1, rstate, sol);
		mpz_class prbu(rand1);
		cout << "prbu2 " << prbu.get_str() << endl;

		// add the random number to the low number, which will make sure the random number is between the low and high ranges
		mpz_add(rand1, rand1, l1);

		//gmp_printf("randomly generated number: %Zd\n", rand);
		mpz_class rand2(rand1);
		cout << rand2.get_str() << endl;

	} while (!(mpz_probab_prime_p(rand1, 25)));

	// *********************** GARBAGE COLLECTION *********************** //
	// empty the memory location for the random generator state
	gmp_randclear(rstate);
	// clear the memory locations for the variables used to avoid leaks
	mpz_clear(l1);
	mpz_clear(rand1);
}

mpz_class GeneratorRandom(const int& n)
{
	gmp_randstate_t rs;
	gmp_randinit_default(rs);
	mpz_class lo;
	mpz_ui_pow_ui(lo.get_mpz_t(), 2, time(NULL) % n);

	mpz_class seed;
	mpz_ui_pow_ui(seed.get_mpz_t(), 2, time(NULL) % n); // Using time, r can be pridictable. Use better seed.
	//mpz_ui_pow_ui(seed.get_mpz_t(), 2, 199);
	gmp_randseed(rs, seed.get_mpz_t());
	mpz_class r;
	mpz_urandomb(r.get_mpz_t(), rs, n);
	r += lo;

	gmp_randclear(rs);
	mpz_class cl(r);
	return cl;
}

void PollardRho(mpz_class& p, mpz_class& d, const int& RG)
{
	// initialize random seed
	srand(time(NULL));
	//gmp_randstate_t rs;
	//gmp_randinit_mt(rs);

	// no prime divisor for 1
	if (p.get_str(10) == "1") return;

	// even number means one of the divisors is 2
	//if (p % 2 == 0) return 2;
	bool bIsEven = false;
	mpz_class r;
	//r = (p % 2);
	while ((r = (p % 2)).get_str(10) == "0")
	{
		p /= 2;
		bIsEven = true;
	}
	if (bIsEven) { d = 2; return; }

	// we will pick from the range [2, p)
	//long long int x = (rand() % (p - 2)) + 2;
	//long long int y = x;
	mpz_class intMax(0xffffffff);
	mpz_class x;
	mpz_class y;
	x = (GeneratorRandom(RG) % (p - 2)) + 2;
	y = (x);

	// the constant in f(x).
	// * Algorithm can be re-run with a different c
	// * if it throws failure for a composite.
	//long long int c = (rand() % (p - 1)) + 1;
	mpz_class c;
	c = (GeneratorRandom(RG) % (p - 1)) + 1;

	// Initialize candidate divisor (or result)
	//long long int d = 1;
	d = 1;

	// until the prime factor isn't obtained.
	// If n is prime, return n
	//while (d == 1)
	mpz_class xya;
	while (d == 1)
	{
		// Tortoise Move: x(i+1) = f(x(i))
		//x = (modular_pow(x, 2, p) + c + p) % p;
		x = (((x * x) % p) + c + p) % p;
		//cout << "x:" << x.get_str() << endl;

		// Hare Move: y(i+1) = f(f(y(i)))
		//y = (modular_pow(y, 2, p) + c + p) % p;
		y = (((y * y) % p) + c + p) % p;
		//y = (modular_pow(y, 2, p) + c + p) % p;
		y = (((y * y) % p) + c + p) % p;
		//cout << "y:" << y.get_str() << endl;

		// check gcd of |x-y| and n
		//d = __gcd(abs(x - y), n);
		//d = gcd(abs(x - y), p);
		xya = abs(x - y);
		//cout << "xya:" << xya.get_str() << endl;
		d = gcd(xya, p);
		//cout << "*****d*****" << d.get_str() << endl;

		// retry if the algorithm fails to find prime factor
		// * with chosen x and c
		if (d == p) { PollardRho(p, d, RG); return; }
	}

	p = p / d;
	return;
}

struct hash2
{
	size_t operator()(const mpz_class& x) const
	{
		return x.get_mpz_t()[0]._mp_size != 0 ?
			static_cast<size_t>(x.get_mpz_t()[0]._mp_d[0]) : 0;
	}
};
// Function to find smallest primitive root of n
void findSmallestPrimitive(const mpz_class& p, vector<mpz_class>& vecPriRoot, const int& GR)
{
	unordered_set<mpz_class, hash2> s;

	int nPrrobablePrimeCount = 10;
	// Check if n is prime or not
	int nIsPrime = 0;
	while ((nIsPrime = mpz_probab_prime_p(p.get_mpz_t(), nPrrobablePrimeCount)) == 1)
	{
		nPrrobablePrimeCount++;
		if (nPrrobablePrimeCount > 50) break;
	}
	//nPrrobablePrimeCount = 10;
	if (nIsPrime == 0) // Definitly not prime
		return;

	// Find value of Euler Totient function of n
	// Since n is a prime number, the value of Euler
	// Totient function is n-1 as there are n-1
	// relatively prime numbers.
	mpz_class phi(p - 1);

	//unsigned long long int n = 10967535067;
	//unsigned long long int n = 271;
	//printf("One of the divisors for %lld is %lld.", n, PollardRho(n));
	while (true)
	{
		//long long int d;
		mpz_class d(0);
		{
			PRTimer PRT1;
			//PollardRhoWithSmallRand(phi, d);
			PollardRho(phi, d, GR);
			PRT1.n = d;
		}
		s.insert(d);
		//phi /= d;
		//if (isPrime(phi, 10)) { s.insert(phi); break; }
		int nIsPrime = mpz_probab_prime_p(phi.get_mpz_t(), nPrrobablePrimeCount);
		if (nIsPrime == 1 | nIsPrime == 2) { s.insert(phi);
			break; }
	}

	phi = p - 1;

	mpz_class pow1;
	mpz_class ispr;

	// Check for every number from 2 to phi
	//for (int r = 2; r <= phi; r++)
	//for (int r = phi; r >= 2; r--)
	mpz_class r;
	for (r = 2; r <= phi; r++)
	{
		// Iterate through all prime factors of phi.
		// and check if we found a power with value 1
		bool flag = false;
		for (auto it = s.begin(); it != s.end(); it++)
		{

			// Check if r^((phi)/primefactors) mod p
			// is 1 or not
			//if (power(r, phi / (*it), p) == 1)
			pow1 = phi / *it;
			mpz_powm(ispr.get_mpz_t(), r.get_mpz_t(), pow1.get_mpz_t(), p.get_mpz_t());
			if (ispr.get_str() == "1")
			{
				flag = true;
				break;
			}
		}

		// If there was no power with value 1.
		if (flag == false)
		{
			vecPriRoot.push_back(r);
			return;
		}
	}

	// If no primitive root found
	return;
}

void findNPrimitive(int nCount, const mpz_class& p, vector<mpz_class>& vecPriRoot)
{
	mpz_class min1(vecPriRoot[0]);
	mpz_class nCoPrime(2);
	mpz_class phi = p - 1;
	mpz_class gcd1;
	mpz_class pr;
	while (nCount != 0)
	{
		//if (gcd(nCoPrime++, p - 1) == 1)
		gcd1 = gcd(nCoPrime, phi);
		if (gcd1.get_str() == "1")
		{
			mpz_powm(pr.get_mpz_t(), min1.get_mpz_t(), nCoPrime.get_mpz_t(), p.get_mpz_t());
			vecPriRoot.push_back(pr);
			nCount--;
		}
		nCoPrime++;
	}
}

mpz_class findAllPrimitive(const mpz_class& p, vector<mpz_class>& vecPriRoot)
{
	mpz_class min1(vecPriRoot[0]);
	mpz_class nCoPrime;
	mpz_class phi = p - 1;
	mpz_class gcd1;
	mpz_class pr;
	mpz_class retCount(1);
	for (nCoPrime = 2; nCoPrime < p; nCoPrime++)
	{
		//if (gcd(nCoPrime++, p - 1) == 1)
		gcd1 = gcd(nCoPrime, phi);
		if (gcd1.get_str() == "1")
		{
			mpz_powm(pr.get_mpz_t(), min1.get_mpz_t(), nCoPrime.get_mpz_t(), p.get_mpz_t());
			vecPriRoot.push_back(pr);
			retCount++;
		}
	}
	return retCount;
}

/*template<class T1, class U1>
class ClassSomeTemp
{
public:
	T1 abc;
	U1 def;
	struct HashFunction
	{
		size_t operator()(const ClassSomeTemp& point) const
		{
			size_t xHash = std::hash<int>()(point.x);
			size_t yHash = std::hash<int>()(point.y) << 1;
			return xHash ^ yHash;
		}
	};
};
typedef ClassSomeTemp<int, int> ClassSomeTemp1;*/

// mpz_probab_prime_p
// mpz_gcd
// mpz_urandomb
int main()
{
	/*mpz_class a("755677");
	a = (a * a) % 81;
	wprintf(L"%S\n", a.get_str().c_str());
	return 0;*/

	/*mpz_class a("8");
	a = (a ^ 2);
	wprintf(L"%S\n", a.get_str().c_str());
	return 0;*/

	/*ClassSomeTemp1 ghi;
	unordered_set<ClassSomeTemp1, ClassSomeTemp1::HashFunction> jkl1;
	return 0;*/

	/*mpz_class p1(760);
	mpz_class r;
	r = p1 % 2;
	cout << r.get_str().c_str() << endl;
	return 0;*/
	/*mpz_t x;
	mpz_init_set_str(x, "678766786876", 10);
	signed long int ex;
	const double di = mpz_get_d_2exp(&ex, x);
	double d1 = log(di) + log(2) * (double)ex;*/

	/*makeprime();
	return 0;*/

	/*mpz_class r = GeneratorRandom(1210);
	cout << r.get_str() << endl;
	mpz_class p1("29273167435619875865648635574214463921301073660463254408453331850401657956983537871787113609292615794062203509616835173757634929204648986253320335067363537346974880192601710607509298307716746218004361136134358473506342760986595032228188627696801089373330585170010488176393659806562392542974720770277547459350895538966336339097331021919348216767110579418607554641860403061482744502133517219269921108961049865670520752589149396650766533592202331766023286364589443152588748580046154633824567218845887105251274070051", 10);
	cout << p1.get_str() << endl;
	return 0;*/

	/*mpz_t n;
	mpz_init(n);
	mpz_init_set_str(n, "874375034634239102401912938438", 10);

	gmp_randstate_t rs;
	//gmp_randinit_mt(rs);
	gmp_randinit_default(rs);

	mpz_t s;
	mpz_init(s);
	mpz_init_set_str(s, "0", 10);
	gmp_randseed(rs, s);
	//unsigned long l = 786786;
	//gmp_randseed_ui(rs, l);

	mpz_t r;
	mpz_init(r);

	mpz_urandomm(r, rs, n);
	//mpz_urandomb(r, rs, 1000);

	char szBuf[255];
	SecureZeroMemory(szBuf, sizeof(szBuf));
	mpz_get_str(szBuf, 10, r);
	printf("%s\n", szBuf);

	mpz_urandomm(r, rs, n);
	//mpz_urandomb(r, rs, 1000);

	SecureZeroMemory(szBuf, sizeof(szBuf));
	mpz_get_str(szBuf, 10, r);
	printf("%s\n", szBuf);

	mpz_clear(r);
	gmp_randclear(rs);
	return 0;*/

	vector<mpz_class> vecPriRoot;

	//mpz_class p(271);
	mpz_class p(761);
	cout << "Prime p: " << p.get_str() << endl;
	findSmallestPrimitive(p, vecPriRoot, 10);
	mpz_class retCount = findAllPrimitive(p, vecPriRoot);
	cout << "Primitive Root Count: " << retCount.get_str() << endl;
	cout << "Primitive Root: " << endl << "Smallest Primitive Root is ";
	sort(vecPriRoot.begin(), vecPriRoot.end());
	for (auto n : vecPriRoot)
	{
		wprintf(L"%S, ", n.get_str().c_str());
	}
	cout << endl << endl;

	vecPriRoot.clear();
	p = "1589946103";
	cout << "Prime p: " << p.get_str() << endl;
	findSmallestPrimitive(p, vecPriRoot, 100);
	findNPrimitive(100, p, vecPriRoot);
	cout << "Primitive Root: " << endl << "Smallest Primitive Root is ";
	sort(vecPriRoot.begin(), vecPriRoot.end());
	for (auto n : vecPriRoot)
	{
		wprintf(L"%S, ", n.get_str().c_str());
	}
	cout << endl << endl;

	vecPriRoot.clear();
	p = mpz_class("e7e94db309dc10540a75e38be90c32141ecb958802ae172e09de549156e028f443ea6f788074e1fec332703352b376170006f6ef4f4a2fb1d0d943d0bed9", 16);
	cout << "Prime p: " << p.get_str() << endl;
	findSmallestPrimitive(p, vecPriRoot, 100);
	findNPrimitive(100, p, vecPriRoot);
	cout << "Primitive Root: " << endl << "Smallest Primitive Root is ";
	//sort(vecPriRoot.begin(), vecPriRoot.end());
	for (auto n : vecPriRoot)
	{
		wprintf(L"%S, \n", n.get_str().c_str());
	}

	//mpz_class p("29273167435619875865648635574214463921301073660463254408453331850401657956983537871787113609292615794062203509616835173757634929204648986253320335067363537346974880192601710607509298307716746218004361136134358473506342760986595032228188627696801089373330585170010488176393659806562392542974720770277547459350895538966336339097331021919348216767110579418607554641860403061482744502133517219269921108961049865670520752589149396650766533592202331766023286364589443152588748580046154633824567218845887105251274070051", 10);
	//cout << p.get_str() << endl;
	//cout << " Gratest primitive root of " << n << " is " << findPrimitive(n);
	//vecPriRoot.clear();
	// Used for generating variable length random numbers. Larger the value longer the random number
	//findSmallestPrimitive(p, vecPriRoot, 1200);
	//findNPrimitive(100, p, vecPriRoot);
	//mpz_class retCount = findAllPrimitive(p, vecPriRoot);
	//cout << retCount.get_str() << endl;
	//sort(vecPriRoot.begin(), vecPriRoot.end());
	//for (auto n : vecPriRoot)
	//{
	//	wprintf(L"%S, ", n.get_str().c_str());
	//}

	return 0;
}
