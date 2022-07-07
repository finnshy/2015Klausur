
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

double getDouble(char text[], double min, double max);
void tabelleBerechnen(double result[4][101], double c, double r, double v, double t);
void tabelleAusgeben(double result[4][101]);


int main() {
	double result[4][101]; //t,uR,uC,I
	double c = getDouble("Bitte geben Sie den Wert für den Kondensator ein:", 1e-12, 10);
	double r = getDouble("Bitte geben Sie den Wert für den Widerstand ein:", 1, 1e9);
	double u = getDouble("Bitte geben Sie den Wert für die Spannung ein:", 1e-3, 1000);
	double t = getDouble("Bitte geben Sie den Wert für die Zeit ein:", 1e-6, 1000);
	tabelleBerechnen(result, c, r, u, t);
	tabelleAusgeben(result);
}

double getDouble(char text[], double min, double max) // [in] question text for user input, array with already picked values, min and max for userinput
{
	double value; // user input
	int finished = 0; // flag for correct user input
	char ch; // character behind number
	int retVal; // return value of scanf
	do {
		// get user input
		printf("%s", text);
		ch = '\0';
		retVal = scanf("%lf%c", &value, &ch);
		// check for valid user input
		if (retVal != 2) printf("Das war keine korrekte Zahl!\n\n");
		else if (ch != '\n') printf("Unerwartete Zeichen hinter der Zahl!\n\n");
		else if (value > max || value < min) printf("Zahl ausserhalb des Intervals [%lf,%lf]\n\n", min, max);
		else finished = 1;
		// clear input stream
		while (ch != '\n') scanf("%c", &ch);
		// repeat if not finished
	} while (!finished);
	// return user input
	return value;
}

void tabelleBerechnen(double result[4][101], double c, double r, double u, double t) {
	for (int i = 0; i < 101; i++)
	{
		result[0][i] = t * i;
		result[1][i] = u * exp((-result[0][i]) / (r * c));
		result[2][i] = u * (1 - exp(-result[0][i] / (r * c)));
		result[3][i] = (u / r) * exp(-result[0][i] / (r * c));
	}
}

void tabelleAusgeben(double result[4][101]) {
	printf("Zeit         |UR      |UC      |Strom\n");
	for (int i = 0; i < 101; i++)
	{
		printf("%13.6lf|%8.4lf|%8.4lf|%6.6lf\n", result[0][i], result[1][i], result[2][i], result[3][i]);
	}
}