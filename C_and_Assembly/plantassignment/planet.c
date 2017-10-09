//Robert Wooner
//CS 261
//assignment 6
#define _GNU_SOURCE
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <plot.h>
plPlotter *plotter;
plPlotterParams *plotterParams;

typedef struct list {
	char *name;
	char *color;
	double size;
	double mass;
	double xPosition;
	double yPosition;
	double xVelocity;
	double yVelocity;
	double xForce;
	double yForce;
	int count;
	int rotations;
	struct list *next;
} List;

//constructor!
List *getVariables() {
    List *page = (List*)malloc(sizeof(List));
    page->name = NULL;
    page->color = NULL;
    page->size = 0.0;
    page->mass = 0.0;
    page->xPosition = 0.0;
    page->yPosition = 0.0;
    page->xVelocity = 0.0;
    page->yVelocity = 0.0;
    page->xForce = 0.0;
    page->yForce = 0.0;
		page->count = 0;
		page->rotations = 0;
    page->next = NULL;
    return page;
	}

//makes the planets disapper
void blackPlanet(List *page, int planNum, plPlotter *plotter) {
	int i = 0;
	List *hodor;
	hodor = page;
	while (i < planNum ){
	pl_pencolorname_r(plotter,"black");
	pl_fillcolorname_r(plotter,"black");
	pl_fcircle_r(plotter, page->xPosition/2500000000, page->yPosition/2500000000, page->size*100);
	i++;
	page = page->next;
	}
	page = hodor;
	return;
}

//produces the planets for plot
void colorPlanet(List *page, int planNum, plPlotter *plotter) {
	int i = 0;
	List *hodor;
	hodor = page;
	while (i < planNum ){
		pl_pencolorname_r(plotter,"black");
		pl_fillcolorname_r(plotter, page->color);
		pl_fcircle_r(plotter, page->xPosition/2500000000, page->yPosition/2500000000, page->size*100);
		i++;
		page = page->next;
	}
	page = hodor;
	return;
}

//puts the information on the page
List *makePage(List *page, char str[]) {
	char *name = malloc(sizeof(char));
	char *color = malloc(sizeof(char));
	page = getVariables();
	sscanf(str, "%s %s %lf %lf %lf %lf %lf %lf",name,color,&page->size,&page->mass,&page->xPosition,&page->yPosition,&page->xVelocity,&page->yVelocity);
	page->name = name;
	page->color = color;
	return page;
}

//prints planet information
void pagePrint(List *page) {
    while (page != NULL) {
        printf("Name = %s\n, color = %s\n, size = %lf, mass = %lf\n, xposition = %lf, yposition = %lf\n, xvelocity = %lf, yvelocity = %lf\n",page->name,page->color,page->size,page->mass,page->xPosition,page->yPosition,page->xVelocity,page->yVelocity);
        page = page->next;
    }
}

//Calculates the gravitational force on a planet
void  force(List *page, List *otherPage) {
    double G = 6.67428e-11;
    double px = page->xPosition;
    double py = page->yPosition;
    double ox = otherPage->xPosition;
    double oy = otherPage->yPosition;
    double dx = (ox - px);
    double dy = (oy - py);
    double d = sqrt (pow(dx,2) + pow(dy,2));
    double fx = ((G * dx * otherPage->mass) / pow(d,3));
    double fy = ((G * dy * otherPage->mass) / pow(d,3));
    page->xForce += fx;
    page->yForce += fy;
}

int plotSpot(List *page) {
    if (page->xPosition > 0 && page->yPosition > 0) {
			return 1;
    }else if (page->xPosition > 0 && page->yPosition < 0) {
			return 4;
    }else if (page->xPosition < 0 && page->yPosition > 0) {
			return 3;
    }else {
			return 2;
    }
}

void movingPlanets(List *page) {
	//struct timespec time, time2;
	//time.tv_sec = 0;
	//time.tv_nsec = 10000;
	List *page1, *page2;
	int step = 0;
	double timestep = (24 * 3600);
	while (step < 10000) {
			step++;
			//printf("day %d\n",step);
			page1 = page;
			//nanosleep(&time, &time2);
			while (page1 != NULL) {
					page1->xForce = 0.0;
					page1->yForce = 0.0;
					page2 = page;
					while (page2 != NULL) {
							if (page1->mass == page2->mass) {
								page2 = page2->next;
								if (page2 == NULL) break;
							}
							force(page1, page2);
							page2 = page2->next;
					} 
					page1 = page1->next;
			}
			page1 = page;
			//blackPlanet(page, 6, plotter);
			pl_erase_r(plotter);
			while (page1 != NULL) {
					page1->xVelocity += (page1->xForce * timestep);
					page1->yVelocity += (page1->yForce * timestep);
					int quad = plotSpot(page1);
					page1->xPosition += (page1->xVelocity * timestep);
					page1->yPosition += (page1->yVelocity * timestep);
					int quad2 = plotSpot(page1);
					if (quad == 4 && quad2 == 1 && step > 1){
						page1->rotations += 1;
						page1->count = (step/page1->rotations);
					}
					page1 = page1->next;
			}
			colorPlanet(page, 6, plotter);
			usleep(1);
	}
	while (page != NULL) {
			printf("%s orbits in %d days\n",page->name,page->count);
			page = page->next;
	}
}


void freePage(List *page) {
    while (page != NULL) {
        free(page);
        page = page->next;
    }
}

int main( int argc, char *argv[]) {				
	List *page = NULL;
	List *frontPage = NULL;
	List *newPage = NULL;
	FILE *fd = fopen(argv[1],"r");
	char str[200] ;
	if (fd == NULL) {
		fprintf(stderr, "This file has nothing in it");
	}else {
        while (! feof(fd)){
            if (fgets(str, 201,fd) != NULL){
                if (str[0] == 35 || isspace(str[0])){
                    continue;
                }
                if (page == NULL){
                  page = makePage(page,str);
                    frontPage = page;
                }else {
                    newPage = getVariables();
                    newPage = makePage(newPage,str);
                    page->next = newPage;
                    page = newPage;
                }
            }
        }
        pagePrint(frontPage);
	}
  	/* create a plotter parametric structure */
  	plotterParams = pl_newplparams();
  	pl_setplparam(plotterParams, "BITMAPSIZE", "750x750");
  	pl_setplparam(plotterParams, "USE_DOUBLE_BUFFERING", "yes");
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
	
    movingPlanets(frontPage);


  	if (pl_closepl_r(plotter) < 0) {
        fprintf(stderr, "Couldn't close plotter\n");
  	} else if (pl_deletepl_r(plotter) < 0) {
        fprintf(stderr, "Couldn't delete plotter\n");
  	}
		freePage(page);
return 0;
}
