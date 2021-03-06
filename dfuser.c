/* 
 * File:   dfuser.cpp
 * Author: gmc
 *
 * Created on 03 December 2011, 01:13
 * Based on hello.c example by Miklos Szeredi <miklos@szeredi.hu>
 * 
 *     This file is part of dfuser.
 * 
 *     Dfuser is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 * 
 *     Dfuser is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *     You should have received a copy of the GNU General Public License
 *     along with dfuser.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#define FUSE_USE_VERSION 25
#define _FILE_OFFSET_BITS 64

#include <fuse.h>
#include <fuse/fuse_opt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include "fuser.h"

struct options {
  char *repo;
} options;

static char default_repopath[]="~/.dfuser/repo";

#define DFUSER_OPT_KEY(t, p, v) { t, offsetof(struct options, p), v }

static struct fuse_opt dfuser_opts[] = {
	DFUSER_OPT_KEY("repo=%s", repo, 0),
	FUSE_OPT_END
};


static struct fuse_operations dfuser_oper = {
    .getattr	= dfuser_getattr,
    .readdir	= dfuser_readdir,
    .open	= dfuser_open,
    .release    = dfuser_release,
    .read	= dfuser_read,
    .write	= dfuser_write,
    .create     = dfuser_create,
    .unlink     = dfuser_unlink,
    .chmod      = dfuser_chmod,
    .chown      = dfuser_chown,
    .mkdir      = dfuser_mkdir,
};

int main(int argc, char *argv[])
{
    int rv;
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    DIR *repodir;
    struct dirent *entry;

    memset(&options,0,sizeof(struct options));

    if(fuse_opt_parse(&args,&options,dfuser_opts,NULL)==-1) {
	fprintf(stderr,"Unable to parse arguments\n");
	return -1;
    }

    if(options.repo==NULL) options.repo=default_repopath;
    fprintf(stderr,"repo: %s\n",options.repo);
/*   
    repodir=opendir(options.repo);
    while(entry=readdir(repodir)) {
      fprintf(stderr,"- %s %i\n",entry->d_name,entry->d_ino);
    }
    closedir(repodir);
*/

    rv=dfuser_main(options.repo);
    
    rv=fuse_main(args.argc,args.argv,&dfuser_oper);

    fuse_opt_free_args(&args);

    return rv;
}