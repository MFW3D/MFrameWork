#include "fsm.hpp"
#include "timer.h"
#include <thread>

//#define FSM_BUILD_SAMPLE2
#ifdef FSM_BUILD_SAMPLE1

// basic fsm, CD player sample

#include <iostream>

// custom states (gerunds) and actions (infinitives)

enum {
	opening,
	closing,
	waiting,
	playing,

	open,
	close,
	play,
	stop,
	insert,
	eject,
};

struct cd_player {

	// implementation variables
	bool has_cd;

	// implementation conditions / guards
	bool good_disk_format() { return true; }

	// implementation actions
	void open_tray()      { std::cout << "opening tray" << std::endl; }
	void close_tray()     { std::cout << "closing tray" << std::endl; }
	void get_cd_info()    { std::cout << "retrieving CD info" << std::endl; }
	void start_playback(const std::string &track) { std::cout << "playing track #" << track << std::endl; }

	// the core
	fsm::stack fsm;

	cd_player() : has_cd(false)
	{
		// define fsm transitions: on(state,trigger) -> do lambda
		fsm.on(opening, close) = [&](const fsm::args &args) {
			printf("opening, close\n");
			close_tray();
			if (!has_cd) {
				fsm.set(closing);
			}
			else {
				get_cd_info();
				fsm.set(waiting);
			}
		};
		fsm.on(opening, insert) = [&](const fsm::args &args) {
			printf("opening, insert\n");
			has_cd = true;
			fsm.set(opening);
		};
		fsm.on(opening, eject) = [&](const fsm::args &args) {
			printf("opening, eject\n");
			has_cd = false;
			fsm.set(opening);
		};

		fsm.on(closing, open) = [&](const fsm::args &args) {
			printf("closing, open\n");
			open_tray();
			fsm.set(opening);
		};

		fsm.on(waiting, play) = [&](const fsm::args &args) {
			printf("waiting, play\n");
			if (!good_disk_format()) {
				fsm.set(waiting);
			}
			else {
				start_playback(args[0]);
				fsm.set(playing);
			}
		};
		fsm.on(waiting, open) = [&](const fsm::args &args) {
			printf("waiting, open\n");
			open_tray();
			fsm.set(opening);
		};

		fsm.on(playing, open) = [&](const fsm::args &args) {
			printf("playing, open\n");
			open_tray();
			fsm.set(opening);
		};
		fsm.on(playing, stop) = [&](const fsm::args &args) {
			printf("playing, stop\n");
			fsm.set(waiting);
		};

		// set initial fsm state
		fsm.set(opening);
	}
};

// usage

int main() {
	cd_player cd;

	for (;;) {
		std::cout << "[" << cd.fsm.get_state() << "] ";
		std::cout << "(o)pen lid/(c)lose lid, (i)nsert cd/(e)ject cd, (p)lay/(s)top cd? ";

		char cmd;
		std::cin >> cmd;

		switch (cmd) {
		case 'p': cd.fsm.command(play, 1 + rand() % 10); break;
		case 'o': cd.fsm.command(open); break;
		case 'c': cd.fsm.command(close); break;
		case 's': cd.fsm.command(stop); break;
		case 'i': cd.fsm.command(insert); break;
		case 'e': cd.fsm.command(eject); break;
		default: std::cout << "what?" << std::endl;
		}
	}
}

#endif

#ifdef FSM_BUILD_SAMPLE2

// basic hfsm sample

#include <iostream>

// custom states (gerunds) and actions (infinitives)

enum {
	walking = 'WALK',
	defending = 'DEFN',

	tick = 'tick',
};

struct ant_t {
	fsm::stack fsm;
	int health, distance, flow;

	ant_t() : health(0), distance(0), flow(1) {
		// define fsm transitions: on(state,trigger) -> do lambda
		fsm.on(walking, 'init') = [&](const fsm::args &args) {
			std::cout << "initializing" << std::endl;
		};
		fsm.on(walking, 'quit') = [&](const fsm::args &args) {
			std::cout << "exiting" << std::endl;
		};
		fsm.on(walking, 'push') = [&](const fsm::args &args) {
			std::cout << "pushing current task." << std::endl;
		};
		fsm.on(walking, 'back') = [&](const fsm::args &args) {
			std::cout << "back from another task. remaining distance: " << distance << std::endl;
		};
		fsm.on(walking, tick) = [&](const fsm::args &args) {
			std::cout << "\r" << "\\|/-"[distance % 4] << " walking " << (flow > 0 ? "-->" : "<--") << " ";
			distance += flow;
			if (1000 == distance) {
				std::cout << "at food!" << std::endl;
				flow = -flow;
			}
			if (-1000 == distance) {
				std::cout << "at home!" << std::endl;
				flow = -flow;
			}
		};
		fsm.on(defending, 'init') = [&](const fsm::args &args) {
			health = 1000;
			std::cout << "somebody is attacking me! he has " << health << " health points" << std::endl;
		};
		fsm.on(defending, tick) = [&](const fsm::args &args) {
			std::cout << "\r" << "\\|/-$"[health % 4] << " health: (" << health << ")   ";
			--health;
			if (health < 0) {
				std::cout << std::endl;
				fsm.pop();
			}
		};

		// set initial fsm state
		fsm.set(walking);
	}
};

void _timer()
{
	while (1)
	{
		Timer::getInstance()->updateTimer();
	}
}

int timer_test()
{
	printf("\007The current date/time is: %s", asctime(&Timer::getInstance()->getSystemLocalTime()));

	Timer::getInstance()->initTimer();
	std::thread  thd(_timer);

	printf("start time: %lld\n", Timer::getInstance()->getStartTime());
	char* str[] = {
		"this is timeout one",
		"this is timeout two",
		"this is timeout three",
		"this is timeout four",
		"this is timeout five",
		nullptr,
	};

	for (int i = 0; str[i] != nullptr; i++)
	{
		if (0 != Timer::getInstance()->addTimeout((i + 1) * 100, str[i], strlen(str[i]) + 1))
		{
			printf("error....\n");
		}
		else
		{
			printf("add timeout success %d\n", i);
		}
	}

	thd.join();
	return 0;
}

int main() {

	try
	{
		csv::Parser file = csv::Parser("../../CSVparser-master/files/readme.csv");

		std::cout << file[0][0] << std::endl; // display : 1997
		std::string a = file[0][0];
		std::cout << file[0] << std::endl; // display : 1997 | Ford | E350

		std::cout << file[1]["Model"] << std::endl; // display : Cougar

		std::cout << file.rowCount() << std::endl; // display : 2
		std::cout << file.columnCount() << std::endl; // display : 3

		std::cout << file.getHeaderElement(2) << std::endl; // display : Model
	}
	catch (csv::Error &e)
	{
		std::cerr << e.what() << std::endl;
	}

	

	ant_t ant;
	for (int i = 0; i < 4; ++i) {
		if (0 == rand() % 2) {
			ant.fsm.push(defending);
		}
		ant.fsm.command(tick);
	}

	timer_test();
}

#endif