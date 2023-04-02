#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <fuse.h>
#include "../libWad/Wad.h"

Wad* fileData;

static int wadfs_getattr(const char* path, struct stat* stbuf) {
	memset(stbuf, 0, sizeof(struct stat));
	if (strcmp(path, "/") == 0 || fileData->isDirectory(string(path))) {
		stbuf->st_mode = S_IFDIR | 0555;
		stbuf->st_nlink = 2;
		return 0;
	}

	if (fileData->isContent(path)) {
		stbuf->st_mode = S_IFREG | 0444;
		stbuf->st_nlink = 1;
		stbuf->st_size = fileData->getSize(string(path));
		return 0;
	}
	return -ENOENT;
}

static int wadfs_open(const char* path, struct fuse_file_info* fi) {
	return 0;
}

static int wadfs_read(const char* path, char* buf, size_t size, off_t offset, struct fuse_file_info* fi) {
	string _path = string(path);
	if (fileData->isContent(_path)) {
		size_t sz = fileData->getSize(_path);
		if (offset >= sz) {
			return 0;
		}
		else if (offset + size > sz) {
			fileData->getContents(_path, buf, sz - offset, offset);
			return sz - offset;
		}
		else {
			fileData->getContents(_path, buf, size, offset);
			return size;
		}
	}
	return -ENOENT;
}

static int wadfs_readdir(const char* path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi) {
	(void) offset;
	(void) fi;
	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);
	vector<string> entries;
	if (fileData->isDirectory(string(path))) {
		fileData->getDirectory(string(path), &entries);
	}
	for (string entry : entries) {
		filler(buf, entry.c_str(), NULL, 0);
	}
	return 0;
}

void wadfs_destroy(void* private_data) {
        delete fileData;
}

static struct fuse_operations wad_ops = {
	.getattr = wadfs_getattr,
	.open = wadfs_open,
	.read = wadfs_read,
	.readdir = wadfs_readdir,
	.destroy = wadfs_destroy,
};

int main(int argc, char *argv[]) {
	if (argc < 3) {
                cout << "Usage: wadfs <target wad> <mount directory>\n";
                return -1;
        }
        //fileData = Wad::loadWad("../sample1.wad");
	fileData = Wad::loadWad(argv[1]);
	argv[1] = argv[2];
	argv[2] = NULL;
	argc--;
	return fuse_main(argc, argv, &wad_ops, NULL);
}
