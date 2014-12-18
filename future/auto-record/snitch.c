/*
 *	helena	- has confirmation areas
 */

#include <libmv.h>
#include <stdlib.h>
#include <stdio.h>

#define DEBUG

#ifdef DEBUG
	#include <syslog.h>
	#define debugPrint(args...) syslog(LOG_INFO, args)
    #define debug(fmt, args...) debugPrint("[LIBMV] - "fmt"\n", ##args)
#else
    #define debug(fmt, args...)
#endif

#define WIDTH_MB 44
#define HEIGHT_MB 30
#define OFF 0
#define ON 1

// resolution is 704x480
// 704/16 = 44
// 480/16 = 30

 struct mv_context {
 	struct libmv_ops *ops;
 	int open;
 };

 struct motion_vector {
 	int16_t MVx;
 	int16_t MVy;
 	uint32_t SAD;
 };
 struct mv_context mv_ctx;

 int libmv_open(struct libmv_ops *ops)
 {
 	mv_ctx.open = 1;
 	mv_ctx.ops = ops;
 	return 1;
 }
uint8_t once = 0;
 uint16_t framecount = 0;
 void libmv_process(uint8_t *data, uint32_t len)
 {	
 	if (once == 0) {
 		debug("GO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
 		once = 1;
 	}
 	debug("framecount: %d", framecount);
 	if (framecount <= 128){
 		FILE *fp;
 		fp = fopen("/tmp/vectors", "a");
 		fwrite(data, sizeof(uint8_t), len, fp);
 		fclose(fp);
 		framecount ++;
 	} else {
 		debug("STOP!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11");
 	}
 }
