#include <iostream>
#include "clsLoginScreen.h"
#include "clsTransferScreen.h"
using namespace::std;



int main() {


	while (true) {
		if (!clsLoginScreen::_ShowLoginScreen()) {
			break;
	}
	}

}