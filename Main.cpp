#include <cstdlib>
#include <iostream>
#include <limits>
#include <iomanip>

#ifdef X64
typedef long double dbl_max;
typedef unsigned long long int uint_max;
#else
typedef double dbl_max;
typedef unsigned long int uint_max;
#endif

int _cdecl main(int argc, char *params[])
{
	uint_max length{ 0 };
	switch (argc)
	{
	case 1:
		std::cout << "Enter # of terms to sum:";
		std::cin >> length;
		break;
	default:
		std::cout << "Error: you passed too many parameters; Using 1st acceptable one.\n";
	case 2:
	{
		auto param{ params + 1 };
		do length = atoi(*param++);
		while (!length && param < params + argc);
	}
	}
	while (!length)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Error: input is not a number.\n"
			"Enter # of terms to sum:";
		std::cin >> length;
	}
	if (std::numeric_limits<decltype(length)>::max() == length)
		std::cout << "Too many terms requested.  Using " << --length << " instead.\n";

	// pi/4=sum(k=1..., (-1)^(k+1)/(2k-1))
	// reversed to reduce loss of significance
	dbl_max pi{ 0.0 };
	for (auto k{ length }; k >= 1; --k)
		pi += (k % 2 ? 1 : -1) / (decltype(pi){2.0} *k - 1);
	pi *= 4;
	std::cout << "Pi = " << std::setprecision(std::numeric_limits<decltype(pi)>::digits10 + 1) << pi << '\n';
	//system("Pause");
}