//该程序所有图的邻接表定义均使用李春葆《数据结构教程》第五版
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stats.h"
#include "stats.c"
#include "search.h"
#include "search.c"

extern AdjGraph map;				//图的全局变量
extern int maxdegree;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("\nno argv receive,please check it\n\n");
		return 0;
	}
	if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		printf("\n  1. -g/--graph FILE_PATH -s/--stats STATS_PARAMS\n");
		printf("      显示以 FILE_PATH 为输入文件的图的统计信息\n");
		printf("\n  2. -g/--graph FILE_PATH -sp/--shortestpath SEARCH_PARAMS -u STARTING_POINT -v TARGET_POINT\n");
		printf("      显示以 FILE_PATH 为输入文件的图中 从开始点 u 到 终点 v 的用 SEARCH_PARAMS蒜出来的最短路径\n");
		printf("\n  3. -j\n      蒜头君的独家私密照片\n");
		printf("\n  4.  其他功能有待开发\n\n");
	}
	if (strcmp(argv[1], "-g") == 0 || strcmp(argv[1], "--graph") == 0) {
		//initmaps(argv[2]);
		if (strcmp(argv[3], "-s") == 0 || strcmp(argv[3], "--stats") == 0) {
			if (strcmp(argv[4], "edges") == 0) {
				printf("%d\n", numberOfEdges(argv[2]));
			}
			else if (strcmp(argv[4], "vertices") == 0) {
				printf("%d\n", numberOfVertices(argv[2]));
			}
			else if (strcmp(argv[4], "freeman") == 0) {
				printf("%lf\n", freemanNetworkCentrality(argv[2]));
			}
			else if (strcmp(argv[4], "betweenness") == 0) {
				printf("there is no answer here");
			}
			else if (strcmp(argv[4], "closeness") == 0) {
				if(strcmp(argv[5], "-u") == 0) {
				printf("%lf\n", closenessCentrality(argv[2],argv[6]));
				}
				else {
					printf("\nformat error, please check it ,error id argv[5]\n\n");
				}
			}
			else if (strcmp(argv[4], "eigenvector") == 0) {
				printf("there is no answer here");
			}
			else {
				printf("\nformat error, please check it,error id argv[4]\n\n");
			}
		}
		else if (strcmp(argv[3], "-sp") == 0 || strcmp(argv[3], "--shortestpath") == 0) {
			initmaps(argv[2]);
			char SearchParams[5][10] = { "DFS","BFS","Dijkstra","SPFA","Astar" };
			int start = atoi(argv[6]);
			int end = atoi(argv[8]);
			if (strcmp(argv[4], SearchParams[0]) == 0) {
				if (strcmp(argv[5], "-u") == 0 && strcmp(argv[7], "-v") == 0) {
					for (int i = 0; DFS(&map, start, end)[i] != -1; i++) {
						printf("%d ", DFS(&map, start, end)[i]);
					}
					printf("\n");
				}
				else {
					printf("\nformat error, please check it,error id argv[5]or[7]\n\n");
				}
			}
			else if (strcmp(argv[4], SearchParams[1]) == 0) {
				if (strcmp(argv[5], "-u") == 0 && strcmp(argv[7], "-v") == 0) {
					for(int i = 0; BFS(&map, start, end)[i] != -1; i++) {
						printf("%d ",BFS(&map, start, end)[i]);
					}
					printf("\n");
				}
				else {
					printf("\nformat error, please check it,error id argv[5]or[7]\n\n");
				}
			}
			else if (strcmp(argv[4], SearchParams[2]) == 0) {
				if (strcmp(argv[5], "-u") == 0 && strcmp(argv[7], "-v") == 0) {
					Dijkstra(&map,start,end);
				}
				else {
					printf("\nformat error, please check it,error id argv[5]or[7]\n\n");
				}
			}
			else if (strcmp(argv[4], SearchParams[3]) == 0) {
				if (strcmp(argv[5], "-u") == 0 && strcmp(argv[7], "-v") == 0) {
					for(int i=0; SPFA(&map, start, end)[i] != -1; i++) {
						printf("%d ",SPFA(&map, start, end)[i]);
					}
					printf("\n");
				}
				else {
					printf("\nformat error, please check it,error id argv[5]or[7]\n\n");
				}
			}
			else if (strcmp(argv[4], SearchParams[4]) == 0) {
				if (strcmp(argv[5], "-u") == 0 && strcmp(argv[7], "-v") == 0) {
					//SPFA(&map, start,end);
					printf("there is nothing");
				}
				else {
					printf("\nformat error, please check it,error id argv[5]or[7]\n\n");
				}
			}
			else {
				printf("\nformat error, please check it,error id argv[4]\n\n");
			}

		}
		else {
			printf("\nformat error, please check it,error id argv[3]\n\n");
		}
	}
	if (strcmp(argv[1], "-j") == 0) {
		printf(" OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOOOOOOOOO[[[]]]OOOOOOOOOOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOOOOOOOOO^    .OOOOOOOOOOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOOOOOO`.,^    .O.=OOOOOOOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOOOOOO. .^    .o. =OOOOOOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOOOOOO.       .o. .OOOOOOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOOOOO  ..     .\\. .OOOOOOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOOO^   =^      .=. .\\OOOOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOO/.  ,*.       =`.  ,OOOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOO`  .=`         =^   ,OOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOO`..^.   .O.          .O^    \\.\\OOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOO/[. .,/`    .O[.           \\O.    ,,.  ,[OOOOOOOOOOOO \n");
		printf(" OOOOOOOO^.   ./O.     ,O^              .OO`     .O\\    \\OOOOOOOO \n");
		printf(" OOOOOO.    .//`      =O^                .OO`      ,O`.   \\OOOOOO \n");
		printf(" OOO^      .O`       ./^.                  =^        =\\     .OOOO \n");
		printf(" OO^.    .,O.       .OO.                   =O^       .\\      \\O00 \n");
		printf(" OO^     .OO.       .O`.                    ,^        .O^      =O \n");
		printf(" O^.     .o.        .O.   yisiliu❤ xiaohei  .^         .O.     .O \n");
		printf(" O`      .o          O.                     .^         .o.     .O \n");
		printf(" OO.     .o         .O.                     ,^         .o.     =O \n");
		printf(" OO^     .O.        .Oo.                   .=^         ..      =O \n");
		printf(" OO\\      o.        ,O.                   =^         =^      =OOO \n");
		printf(" OOO^      =.         =O`                .=O`        ./^     .OOO \n");
		printf(" OOOOO]   ./O\\        =^                ,O.        ,/O^   .]OOOOO \n");
		printf(" OOOOOOOOOOOOOO^       ,O\\             .O/.      .OOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOO\\.    ,OOO`.         ,OOOO.    ,OOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOOOOOOOO`..  ...OOOOOOOOOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO \n");
		printf(" OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO \n");
	}
	return 0;
}
