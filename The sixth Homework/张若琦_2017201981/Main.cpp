#include <cstdio>
#include "print.h"

int main()
{
	OString nd = "-23";
	nd.print("%4d\n"); //  " -23"
	nd.print("%2d\n"); //  "-23"
	nd.print("%-4d\n"); //  "-23 "
	nd.print("%-2d\n"); //  "-23"
	nd.print("%04d\n"); // "-023"
	nd.print("%02d\n"); // "-23"
	nd.print("%+04d\n"); // "-023"
	nd.print("%+4d\n"); // " -23"

	nd.print("%6.5d\n"); // "-00023"
	nd.print("%7.5d\n"); // " -00023"

	printf("=====================================\n");

	OString pd = "233";
	pd.print("%4d\n"); // " 233"
	pd.print("%2d\n"); // "233"
	pd.print("%-4d\n"); // "233 "
	pd.print("%-2d\n"); // "233"
	pd.print("%04d\n"); // "0233"
	pd.print("%02d\n"); // "233"
	pd.print("%+04d\n"); // "+233"
	pd.print("%+4d\n"); // "+233"

	pd.print("%6.5d\n"); // " 00233"
	pd.print("%7.5d\n"); // "  00233"

	printf("=====================================\n");

	OString pf = "6.66";
	pf.print("%4.1f\n"); // " 6.7"
	pf.print("%05.1f\n"); // "006.7"
	pf.print("%-5.1f\n"); // "6.7  "
	pf.print("%+5.1f\n"); // " +6.7"
	pf.print("%+05.1f\n"); // "+06.7"
	pf.print("%3.3f\n"); // "6.660"

	printf("=====================================\n");

	OString nf = "-6.66";
	nf.print("%5.1f\n"); // " -6.7"
	nf.print("%06.1f\n"); // "-006.7"
	nf.print("%-6.1f\n"); // "-6.7  "
	nf.print("%+6.1f\n"); // "  -6.7"
	nf.print("%+06.1f\n"); // "-006.7"
	nf.print("%3.3f\n"); // "-6.660"
}