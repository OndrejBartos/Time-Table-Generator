#include "Generator.h"
#define clrscr() system("cls");

int main() {
	Generator scheduler;
	bool done = false;
	while (!done) {
		clrscr();
		std::cout << "1) Add group" << std::endl;
		std::cout << "2) Add activity" << std::endl;
		std::cout << "3) Generate time table" << std::endl;
		int option; std::cin >> option;
		
		//braces in case because of variable declaration
		std::string name;
		switch (option) {
		case 1:
			std::cout << "Enter group name: "; std::cin.ignore(); std::getline(std::cin, name);
			scheduler.addGroup(name);
			break;
		case 2:
			std::cout << "Enter activity name: "; std::cin.ignore(); std::getline(std::cin, name);
			scheduler.addActivity(name);
			break;
		case 3:
			scheduler.ScheduleActivities();
			done = true;
			break;
		default:
			std::cout << "Invalid entry" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			break;
		}
	}
	return 0;
}