#include "BinomialTree.h"
#include "TreeAmerican.h"
#include "TreeEuropean.h"
#include "BlackScholesFormulas.h"
#include "PayOffForward.h"
#include <cmath>
#include <iostream>

using namespace std;

int main()
{
	double Expiry, Strike, Spot, Vol, r, d;
	unsigned long Steps;

	cout << "\nEnter expiry\n";
	cin >> Expiry;
	cout << "\nStrike\n";
	cin >> Strike;
	cout << "\nEnter spot\n";
	cin >> Spot;
	cout << "\nEnter vol\n";
	cin >> Vol;
	cout << "\nEnter r\n";
	cin >> r;
	cout << "\nEnter d\n";
	cin >> d;
	cout << "\nNumber of Steps\n";
	cin >> Steps;

	PayOffCall thePayOff(Strike);

	ParametersConstant rParam(r);
	ParametersConstant dParam(d);

	TreeEuropean europeanOption(Expiry, thePayOff);
	TreeAmerican americanOption(Expiry, thePayOff);

	SimpleBinomialTree theTree(Spot, rParam, dParam, Vol, Steps, Expiry);

	double euroPrice = theTree.GetThePrice(europeanOption);
	double americanPrice = theTree.GetThePrice(americanOption);

	cout << "euro price: " << euroPrice << "\namer price: " << americanPrice << "\n";

	double BSPrice = BlackScholesCall(Spot, Strike, r, d, Vol, Expiry);
	
	cout << "BS formula euro price: " << BSPrice << "\n";

	PayOffForward forwardPayOff(Strike);
	TreeEuropean forward(Expiry, forwardPayOff);

	double forwardPrice = theTree.GetThePrice(forward);
	cout << "forward price by tree: " << forwardPrice << "\n";

	double actualForwardPrice = exp(-r*Expiry)*(Spot*exp((r - d)*Expiry) - Strike);
	cout << "forward price: " << actualForwardPrice << "\n";



	++Steps;
	SimpleBinomialTree theNewTree(Spot, rParam, dParam, Vol, Steps, Expiry);

	double euroNewPrice = theNewTree.GetThePrice(europeanOption);
	double americanNewPrice = theNewTree.GetThePrice(americanOption);

	cout << "euro new price: " << euroNewPrice << "\namer new price: " << americanNewPrice << "\n";

	double forwardNewPrice = theNewTree.GetThePrice(forward);
	cout << "forward new price by tree " << forwardNewPrice << "\n";

	double averageEuro = 0.5*(euroPrice + euroNewPrice);
	double averageAmer = 0.5*(americanPrice + americanNewPrice);
	double averageForward = 0.5*(forwardPrice + forwardNewPrice);

	cout << "euro av price " << averageEuro << "\namer av price " << averageAmer << "\n";

	cout << "av forward " << averageForward << "\n";

	cin.ignore();
	cin.get();
	return 0;

}