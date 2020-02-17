#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
char lines[512][512] = {0};
char line[512];
int occurences[512] = { 0 };
int count, dupe, ignore = 0;

int
ignstrcmp(const char *p, const char *q)
{
  while(*p && (*p == *q || *p + 32 == *q)) //yes, I know this is stupid, but I legitimately am too tired to figure out how to ternary operator my way out of this right now.
    p++, q++;
  return (uchar)*p - (uchar)*q;
}


void
getline(int fd, char* name)
{
	int n;
	int l, c;
	// int dupeI;
	l = c = 0;
	while ((n = read(fd, buf, sizeof(buf))) > 0) {
		for (int i = 0; i < n; i++) {
			if (buf[i] != '\n') {
				line[c] = buf[i];
				c++;
			}
			else { //if (buf[i] == '\n')
				int searchI = -1;
				for (int i = 0; i < 512; i ++) {
					if (strcmp(line, lines[i]) == 0 || (!dupe && ignstrcmp(line, lines[i]) == 0)) {
					searchI = i;
					}
				}

				if (searchI > -1){
					occurences[searchI]++;
				}
				else {
					for (int i = 0; i < c; i++) {
						lines[l][i] = line[i];
					}
					occurences[l] ++;
					lines[l][i] = '\0';
					l++;
				}
				c = 0;
			}
			lines[l][c] = '\0';
		}
	}
	int i = 0;
	while (i < l){
		if (dupe) {
			if (occurences[i] > 1){
				if (count) printf(1, "%d ", occurences[i]);
				printf(1, "%s\n", lines[i]);
			}
		} else {
			if (count) printf(1, "%d ", occurences[i]);
			printf(1, "%s\n", lines[i]);
		}
		i++;
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

	if (argc == 2) {
		for (i = 1; i < argc; i++) {
			if ((fd = open(argv[i], 0)) < 0) {
				printf(1, "getline: cannot open %s\n", argv[i]);
				exit();
			}

			getline(fd, argv[i]);
			close(fd);
		}
	}

	if (argc == 3) {
		if (strcmp(argv[1], "-c") == 0) count = 1;
		else if (strcmp(argv[1], "-d") == 0) dupe = 1;
		else if (strcmp(argv[1], "-i") == 0) ignore = 1;

		for (i = 2; i < argc; i++) {
			if ((fd = open(argv[i], 0)) < 0) {
				printf(1, "getline: cannot open %s\n", argv[i]);
				exit();
			}

			getline(fd, argv[i]);
			close(fd);
		}
	}

	if (argc == 4) {
		if (strcmp(argv[1], "-c") == 0) count = 1;
		else if (strcmp(argv[1], "-d") == 0) dupe = 1;
		else if (strcmp(argv[1], "-i") == 0) ignore = 1;

		if (strcmp(argv[2], "-c") == 0) count = 1;
		else if (strcmp(argv[2], "-d") == 0) dupe = 1;
		else if (strcmp(argv[2], "-i") == 0) ignore = 1;

		for (i = 3; i < argc; i++) {
			if ((fd = open(argv[i], 0)) < 0) {
				printf(1, "getline: cannot open %s\n", argv[i]);
				exit();
			}

			getline(fd, argv[i]);
			close(fd);
		}
	}
	if (argc == 5) {
		if (strcmp(argv[1], "-c") == 0) count = 1;
		else if (strcmp(argv[1], "-d") == 0) dupe = 1;
		else if (strcmp(argv[1], "-i") == 0) ignore = 1;
		
		if (strcmp(argv[2], "-c") == 0) count = 1;
		else if (strcmp(argv[2], "-d") == 0) dupe = 1;
		else if (strcmp(argv[2], "-i") == 0) ignore = 1;

		if (strcmp(argv[3], "-c") == 0) count = 1;
		else if (strcmp(argv[3], "-d") == 0) dupe = 1;
		else if (strcmp(argv[3], "-i") == 0) ignore = 1;

		for (i = 4; i < argc; i++) {
			if ((fd = open(argv[i], 0)) < 0) {
				printf(1, "getline: cannot open %s\n", argv[i]);
				exit();
			}

			getline(fd, argv[i]);
			close(fd);
		}
	}

	exit();
}
