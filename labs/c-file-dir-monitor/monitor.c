#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <limits.h>
#include "logger.h"

#define BUF_LEN (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

int inotifyFd;

static int display_info(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf){
    int wd = inotify_add_watch(inotifyFd, fpath, IN_CREATE | IN_DELETE | IN_MOVED_FROM | IN_MOVED_TO);
    if (wd == -1){
        errorf("Error in inotify_add_watch \n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

static void displayInotifyEvent(struct inotify_event *i){
    if(i->mask & IN_CREATE){
        if(i->mask & IN_ISDIR){
            infof("[Directory - Create] -");
        }else{
            infof("[File - Create] -");
        }
    }
    else if(i->mask & IN_DELETE){
        if(i->mask & IN_ISDIR){
            infof("[Directory - Removal] -");
        }else{
            infof("[File - Removal] -");
        }
    }
    else if(i->mask & IN_MOVED_FROM){
        if(i->mask & IN_ISDIR){
            infof("[Directory - Rename From] -");
        }else{
            infof("[File - Rename From] -");
        }
    }
    else if(i->mask & IN_MOVED_TO){
        if(i->mask & IN_ISDIR){
            infof("[Directory - Rename To] -");
        }else{
            infof("[File - Rename To] -");
        }
    }

    if(i->len > 1){
        if(i->name != NULL){
            printf("%s\n", i->name);
        }
    }
} 

int main(int argc, char* argv[]){
    // Place your magic here
    if (argc < 2 || argc > 2){
        warnf("Usage: ./monitor {Dir} \n");
        exit(EXIT_FAILURE);
    }
    int nftwTrav;
    int fl = FTW_PHYS;
    char buf[BUF_LEN] __attribute__ ((aligned(8)));
    ssize_t numRead;
    char *p;
    struct inotify_event *event;
    inotifyFd = inotify_init();
    
    if (inotifyFd == -1){
        errorf("Error in inotify_init \n");
        exit(EXIT_FAILURE);
    }

    nftwTrav = nftw(argv[1], display_info, 20, fl);
    if(nftwTrav == -1){
        errorf("Error in nftw init \n");
        exit(EXIT_FAILURE);
    }

    for(;;){

        numRead = read(inotifyFd, buf, BUF_LEN);
        if(numRead == 0){
            panicf("read() from inotifyFd returned 0! \n");
            exit(EXIT_FAILURE);
        }

        if(numRead == -1){
            errorf("Error in read() \n");
            exit(EXIT_FAILURE);
        }

        for(p = buf; p < buf + numRead; ){
            event = (struct inotify_event *) p;
            displayInotifyEvent(event);
            p += sizeof(struct inotify_event *) + event->len;

        }

        nftwTrav = nftw(argv[1], display_info, 20, fl);
        if(nftwTrav == -1){
            errorf("Error in nftw \n");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}