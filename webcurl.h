#ifndef __WEBCURL_H
#define __WEBCURL_H
#ifdef __cplusplus
extern "C" {
#endif
	struct wd_in {
	  size_t size;
	  size_t len;
	  char *data;
	};

	char * getWebPage();
#ifdef __cplusplus
}
#endif
#endif