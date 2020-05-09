#include <iostream>
bool ColorEnabled = false;

void RenderColor(int codefg = 0, int codebg = 0, int actbit = -1) {
	
	if (codefg == 0 && codebg == 0 && actbit == 1)
		ColorEnabled = true;
	else if (codefg == 0 && codebg == 0 && actbit == 0)
		ColorEnabled = false;

	if (ColorEnabled == true) {
		if (codefg == 0 && codebg == 0) {
			std::cout << "\x1b[0m";
		}
		else {
			if (codefg != 0) {
				std::cout << "\x1b[" << codefg << "m";

				if (codebg != 0)
					std::cout << "\x1b[" << codebg << "m";
			}
		}
	}
	
}

bool GetColorMode() {
	return ColorEnabled;
}