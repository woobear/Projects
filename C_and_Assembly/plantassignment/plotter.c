#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <plot.h>

int main(int argc, char** argv) {

	/* plotter device structures */
  	plPlotter *plotter;
  	plPlotterParams *plotterParams;

  	/* create a plotter parametric structure */
  	plotterParams = pl_newplparams();
  	pl_setplparam(plotterParams, "BITMAPSIZE", "750x750");
  	pl_setplparam(plotterParams, "USE_DOUBLE_BUFFERING", "no");
	pl_setplparam(plotterParams, "BG_COLOR", "black");

	/* create the plotter device and open it */
  	if ((plotter = pl_newpl_r("X", stdin, stdout, stderr, plotterParams)) == NULL) {
    		fprintf(stderr, "Couldn't create Xwindows plotter\n");
    		exit(1);
  	} else if (pl_openpl_r(plotter) < 0) {
    		fprintf(stderr, "Couldn't open Xwindows plotter\n");
    		exit(1);
  	}

	/* set our coordinate space in the plotter window */
	pl_fspace_r(plotter, -100.0, -100.0, 100.0, 100.0);

	/* pick a type for the pen and the fill */
	pl_pentype_r(plotter,1);
	pl_filltype_r(plotter,1);

	/* set some colors and draw a circle */
	pl_pencolorname_r(plotter,"white");
	pl_fillcolorname_r(plotter, "blue");
	pl_fcircle_r(plotter, 0.0, 0.0, 25.0);
	pl_fillcolorname_r(plotter,"red");
	pl_fcircle_r(plotter, 50.0, 50.0, 15.0);
			
	/* close and cleanup the plotter stuff */
  	if (pl_closepl_r(plotter) < 0) {
    		fprintf(stderr, "Couldn't close plotter\n");
  	} else if (pl_deletepl_r(plotter) < 0) {
    		fprintf(stderr, "Couldn't delete plotter\n");
  	}
	return 0;
}
