#pragma once
#include "types.h"
#include "stat.h"
#include "user.h"

char buf[4096];
char line[4096];
char* dupes[8192];
int occurences[8192] = { 0 };

int
strnsrch(const char* t, const char* region[], uint n)
{
	for (int i = 0; i < sizeof(*region); i ++) {
		if (strncmp(t, region[i],  n) == 0) {
			return i;
		}
	}

	return -1;
}


void
getline(int fd, char* name)
{
	int i, n;
	int l, c;
	int dupeI;
	l = c = 0;

	while ((n = read(fd, buf, sizeof(buf))) > 0) {
		for (i = 0; i < n; i++) {
			if (buf[i] == '\n') {
				strncpy(dupes[l], line, c);
				dupeI = strnsrch(line, dupes[], c);

				if (dupeI > -1) {
					occurences[dupeI] ++;
					dupeI++;
				} else {
					occurences[l] ++;
					l++;
				}

				c = 0;
			} else {
				line[c] = buf[i];
				c++;
			}
		}
	}

	if (n < 0) {
		printf(1, "getline: read error\n");
		exit();
	}
}

int
main(int argc, char* argv[])
{
	int fd, i;

	if (argc <= 1) {
		getline(0, "");
		exit();
	}

	for (i = 1; i < argc; i++) {
		if ((fd = open(argv[i], 0)) < 0) {
			printf(1, "getline: cannot open %s\n", argv[i]);
			exit();
		}

		getline(fd, argv[i]);
		close(fd);
	}

	exit();
}
