#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

static const struct option engine_options[] = {
  { "update", optional_argument, NULL, 'u' },
  { "version_url", required_argument, NULL, 'v' + 'u' },
  { "image_url", required_argument, NULL, 'i' + 'u'},
  { "check", required_argument, NULL, 'c' },
  { "misc", required_argument, NULL, 'm' },
  { "partition", required_argument, NULL, 'p' },
  { "reboot", no_argument, NULL, 'r' },
  { "help", no_argument, NULL, 'h' },
  { "pipefd", required_argument, NULL, 'p' + 'f' },
  { "savepath", required_argument, NULL, 's'},
  { NULL, 0, NULL, 0 },
};

void display() {
	printf("This is dispaly function.\n");
}

int main(int argc, char* argv[])
{
	int arg;
    char *image_url = NULL;
    char *version_url = NULL;
    char *misc_func = NULL;
    char *save_path = NULL;
    char *partition = NULL;
    bool is_update = false;
    bool is_reboot = false;
    int pipefd = -1;
    int is_sdboot = false;

    while ((arg = getopt_long(argc, argv, "", engine_options, NULL)) != -1) {
        switch (arg) {
            case 'u':
                printf("optarg: %s\n", optarg);
                is_update = true;
                if(optarg != NULL)
                    is_sdboot = true;
                continue;
            case 'c':
                printf("optarg: %s\n", optarg);
                version_url = optarg;
                continue;
            case 'm':
                printf("optarg: %s\n", optarg);
                misc_func = optarg;
                continue;
            case 'p':
                printf("optarg: %s\n", optarg);
                partition = optarg;
                continue;
            case 's':
                printf("optarg: %s\n", optarg);
                save_path = optarg;
                continue;
            case 'r':
                printf("optarg: %s\n", optarg);
                is_reboot = true;
                continue;
            case 'v' + 'u':
                printf("optarg: %s\n", optarg);
                version_url = optarg;
                continue;
            case 'i' + 'u':
                printf("optarg: %s\n", optarg);
                image_url = optarg;
                continue;
            case 'p' + 'f':
                printf("optarg: %s\n", optarg);
                pipefd = atoi(optarg);
                continue;
            case 'h':
                printf("optarg: %s\n", optarg);
                display();
                break;
            case '?':
                printf("Invalid command argument\n");
                continue;
        }
    }

    if ( is_update ) {
        int res = 0x3F00;
        if (partition != NULL) {
            printf("partition = %s\n", partition);
            printf("partition+2 = %s\n", partition+2);
            res = strtol(partition+2, NULL, 16);
            //res = strtol(partition, NULL, 16);
        }
        printf("res = %x\n", res);
    }


    return 0;
}

