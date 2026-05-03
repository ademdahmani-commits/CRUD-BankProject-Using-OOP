#include <iostream>
#include "clsLoginScreen.h"
#include "clsMoneyTransfer.h"
using namespace::std;



int main() {


	//clsMoneyTransfer::ShowMoneyTransferScreen();

	while (true) {
		if (!clsLoginScreen::_ShowLoginScreen()) {
			break;
	}
	}

}