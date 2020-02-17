#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
char lines[512][512] = {0};
char line[512];
int occurences[512] = { 0 };


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
					if (strcmp(line, lines[i]) == 0) {
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
		printf(1, "%d: ", lines[i]);
		printf(1, "%s", lines[i]);
		printf(1, "\n");
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
